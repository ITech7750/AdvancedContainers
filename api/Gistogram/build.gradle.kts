import org.jetbrains.kotlin.gradle.tasks.KotlinCompile
//import org.springframework.boot.gradle.tasks.bundling.BootJar

object Versions {
    const val ROOT_PROJECT_VERSION = "0.0.1-SNAPSHOT"
    const val SPRING_DOC_VERSION = "2.1.0"
    const val JJWT_API_VERSION = "0.11.5"
    const val JVM_VERSION = "17"
    const val MOCKITO_VERSION = "2.2.0"
}

plugins {
    // плагины для Kotlin
    kotlin("jvm") version "1.9.23"
    kotlin("plugin.spring") version "1.9.22"
    kotlin("plugin.jpa") version "1.9.22"

    // плагины для Spring Boot и управления зависимостями
    id("org.springframework.boot") version "3.2.4"
    id("io.spring.dependency-management") version "1.1.4"
}

group = "com.tech"
version = Versions.ROOT_PROJECT_VERSION

java {
    sourceCompatibility = JavaVersion.VERSION_17
    targetCompatibility = JavaVersion.VERSION_17
}

repositories {
    mavenCentral()
    google()
    gradlePluginPortal()
}

extra["springCloudVersion"] = "2023.0.0"

dependencies {

    // Spring Boot Starters для бд, web безопасности и пр.
    implementation("org.springframework.boot:spring-boot-starter-data-jpa")
    implementation("org.springframework.boot:spring-boot-starter-jdbc")
    implementation("org.springframework.boot:spring-boot-starter-web")
    //implementation("org.springframework.boot:spring-boot-starter-security")
    //implementation("org.springframework.boot:spring-boot-starter-mail")

    // Spring Cloud и Eureka Client
    implementation("org.springframework.cloud:spring-cloud-config-server")
    implementation("org.springframework.cloud:spring-cloud-starter-netflix-eureka-client")
    implementation("org.springframework.cloud:spring-cloud-starter-loadbalancer")

    // JSON Web Tokens (JJWT) для аутентификации и авторизации
    implementation("io.jsonwebtoken:jjwt-api:${Versions.JJWT_API_VERSION}")
    implementation("io.jsonwebtoken:jjwt-impl:${Versions.JJWT_API_VERSION}")
    implementation("io.jsonwebtoken:jjwt-jackson:${Versions.JJWT_API_VERSION}")

    // Jackson для обработки JSON в Kotlin
    implementation("com.fasterxml.jackson.module:jackson-module-kotlin")
    implementation("org.jetbrains.kotlin:kotlin-reflect")

    // SpringDoc для автоматической генерации документации OpenAPI
    implementation("org.springdoc:springdoc-openapi-starter-common:${Versions.SPRING_DOC_VERSION}")
    implementation("org.springdoc:springdoc-openapi-starter-webmvc-ui:${Versions.SPRING_DOC_VERSION}")

    // PostgreSQL драйвер для взаимодействия с базой данных
    implementation("org.postgresql:postgresql:42.2.8")

    // Dotenv для загрузки переменных окружения из .env файла
    implementation("io.github.cdimascio:dotenv-kotlin:6.4.1")

    // Тестовые зависимости
    testImplementation("org.springframework.boot:spring-boot-starter-test")
    //testImplementation("org.springframework.security:spring-security-test")
    testImplementation("com.nhaarman.mockitokotlin2:mockito-kotlin:${Versions.MOCKITO_VERSION}")
}

dependencyManagement {
    imports {
        mavenBom("org.springframework.cloud:spring-cloud-dependencies:${property("springCloudVersion")}")
    }
}

tasks.withType<KotlinCompile> {
    kotlinOptions {
        freeCompilerArgs = listOf("-Xjsr305=strict") // cтрогая обработка аннотаций nullability
        jvmTarget = Versions.JVM_VERSION // версия JVM
    }
}

// Настройки тестовых задач
tasks.withType<Test> {
    useJUnitPlatform()
}

// Конфигурация bootJar
tasks.bootJar {
    archiveBaseName.set("gistogram-service")
    archiveVersion.set("0.0.1")
    mainClass.set("com.tech.ApplicationKt")
}

// Отключение обычного JAR
tasks.jar {
    enabled = false
}