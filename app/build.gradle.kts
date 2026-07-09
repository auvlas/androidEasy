plugins {
    id("com.android.application")
    id("maven-publish")
}

android {
    namespace = "org.auvlas.androidEasy"
    compileSdk {
        version = release(36) {
            minorApiLevel = 1
        }
    }

    defaultConfig {
        minSdk = 24

        versionCode = 1
        versionName = "1.0.0"

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"

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

    splits {
        abi {
            isEnable = false
            isUniversalApk = false
        }
    }

    buildTypes {
        release {
            isMinifyEnabled = false
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
        }
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_21
        targetCompatibility = JavaVersion.VERSION_21
    }

    packaging {
        jniLibs {
            useLegacyPackaging = true
        }
    }
    buildFeatures {
        viewBinding = true
    }

    publishing {
        singleVariant("release")
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
}

dependencies {
    implementation(libs.appcompat)
    implementation(libs.material)
    implementation(libs.constraintlayout)
    implementation(libs.navigation.fragment)
    implementation(libs.navigation.ui)
    testImplementation(libs.junit)
    androidTestImplementation(libs.ext.junit)
    androidTestImplementation(libs.espresso.core)
}