plugins {
    alias(libs.plugins.android.application) // Модуль app является исполняемым приложением
}

android {
    namespace = "org.auvlas.androidEasy.hub"
    compileSdk = 35

    defaultConfig {
        applicationId = "org.auvlas.androidEasy.hub"
        minSdk = 24
        targetSdk = 35
        versionCode = 1
        versionName = "1.0.0"

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
    }

    buildFeatures {
        viewBinding = true
        dataBinding = true
    }

    packaging {
        jniLibs {
            useLegacyPackaging = true
        }
    }
}

dependencies {
    implementation(project(":library"))

    implementation(libs.appcompat)
    implementation(libs.material)
    implementation(libs.constraintlayout)
    implementation(libs.androidx.navigation.fragment)
    implementation(libs.androidx.navigation.ui)
}
