plugins {
    alias(libs.plugins.android.library)
    id("maven-publish")
}

android {
    namespace = "org.auvlas.androidEasy"
    compileSdk = 35

    defaultConfig {
        minSdk = 24

        externalNativeBuild {
            cmake {
                abiFilters("armeabi-v7a", "arm64-v8a", "x86", "x86_64")
            }
        }

        ndk {
            abiFilters.addAll(setOf("armeabi-v7a", "arm64-v8a", "x86", "x86_64"))
        }
    }

    externalNativeBuild {
        cmake {
            path = file("src/main/cpp/CMakeLists.txt")
            version = "3.22.1"
        }
    }

    splits {
        abi {
            isEnable = false
            isUniversalApk = false
        }
    }

    publishing {
        singleVariant("release")
    }

    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_21
        targetCompatibility = JavaVersion.VERSION_21
    }

    buildTypes {
        getByName("debug") {
            isMinifyEnabled = false

            packaging {
                jniLibs {
                    excludes.add("lib/**/libsapper.so")
                    excludes.add("lib/**/*.so")
                }
            }

            signingConfig = signingConfigs.getByName("debug")
        }
        getByName("release") {
            isMinifyEnabled = false

            packaging {
                jniLibs {
                    excludes.add("lib/**/libsapper.so")
                    excludes.add("lib/**/*.so")
                }
            }

            proguardFiles(getDefaultProguardFile("proguard-android-optimize.txt"), "proguard-rules.pro")
        }
    }
}

afterEvaluate {
    publishing {
        publications {
            create<MavenPublication>("release") {
                from(components["release"])

                groupId = "org.auvlas.androideasy"
                artifactId = "shared-core"
                version = "1.0.0"
            }
        }
    }
}

dependencies {
    implementation(libs.appcompat)
    implementation(libs.material)
    implementation(libs.constraintlayout)
    testImplementation(libs.junit)
    androidTestImplementation(libs.ext.junit)
    androidTestImplementation(libs.espresso.core)

    implementation("androidx.appcompat:appcompat:1.6.1")
}

// --- Бессмертная таска с динамическим поиском манифеста ---
tasks.register("buildSystemApk") {
    group = "build"
    description = "Собирает системный APK-контейнер для эмулятора из классов библиотеки"

    dependsOn("assembleRelease")

    doLast {
        val buildDir = layout.buildDirectory.asFile.get()
        val rAarFile = file("${buildDir}/outputs/aar/library-release.aar")
        val outputDir = file("${buildDir}/outputs/system-apk")

        if (!rAarFile.exists()) {
            throw GradleException("AAR файл не найден! Проверьте имя задачи assembleRelease.")
        }

        outputDir.mkdirs()

        // ДИНАМИЧЕСКИЙ ПОИСК: Ищем скомпилированный манифест в недрах intermediates
        val intermediatesDir = file("${buildDir}/intermediates")
        val packagedManifest = intermediatesDir.walkTopDown().firstOrNull {
            it.name == "AndroidManifest.xml" &&
                    (it.path.contains("manifest") || it.path.contains("release")) &&
                    !it.path.contains("system_manifest") // Исключаем нашу временную папку
        } ?: throw GradleException("Скомпилированный AndroidManifest.xml не найден в папке intermediates! Убедитесь, что assembleRelease прошел успешно.")

        println("🔍 Найден системный манифест: ${packagedManifest.absolutePath}")

        // Извлекаем classes.jar из AAR архива
        val classesJar = zipTree(rAarFile).filter { it.name == "classes.jar" }.singleFile

        // Получаем путь к Android SDK
        val sdkDir = project.providers.gradleProperty("sdk.dir").orNull
            ?: System.getenv("ANDROID_HOME")
            ?: throw GradleException("Android SDK не найден! Задайте ANDROID_HOME в системе.")

        // Ищем актуальную папку build-tools для d8
        val buildToolsDir = file("${sdkDir}/build-tools")
        val latestBuildTools = buildToolsDir.listFiles()
            ?.filter { it.isDirectory }
            ?.maxByOrNull { it.name }
            ?: throw GradleException("Папка build-tools не найдена в SDK!")

        val d8 = file("${latestBuildTools.absolutePath}/d8")

        // 2. Компилируем .jar в .dex через d8
        val dexDir = file("${buildDir}/intermediates/system_dex")
        dexDir.mkdirs()

        val d8Result = ProcessBuilder(
            d8.path, "--output", dexDir.path, classesJar.path
        ).inheritIO().start().waitFor()

        if (d8Result != 0) throw GradleException("Ошибка при компиляции байткода через d8!")

        val finalApkFile = file("${outputDir}/org.auvlas.androidEasy.apk")
        if (finalApkFile.exists()) finalApkFile.delete()

        // 3. Создаем базовый APK-зип архив и упаковываем туда AndroidManifest.xml и classes.dex
        val targetManifest = file("${dexDir.path}/AndroidManifest.xml")
        packagedManifest.copyTo(targetManifest, overwrite = true)

        val isWindows = org.gradle.internal.os.OperatingSystem.current().isWindows
        val zipResult = if (isWindows) {
            ProcessBuilder("tar", "-cf", finalApkFile.absolutePath, "AndroidManifest.xml", "classes.dex")
                .directory(dexDir)
                .start()
                .waitFor()
        } else {
            // Создаем чистый zip-архив с манифестом и dex-файлом
            ProcessBuilder("zip", "-j", finalApkFile.absolutePath, "AndroidManifest.xml", "classes.dex")
                .directory(dexDir)
                .start()
                .waitFor()
        }

        if (zipResult != 0) throw GradleException("Ошибка при упаковке системного APK архиватором!")

        println("🎉 УСПЕХ! Все артефакты готовы:")
        println("📦 AAR для клиентов (compileOnly): ${rAarFile.absolutePath}")
        println("🤖 APK для /system/framework/: ${finalApkFile.absolutePath}")
    }
}