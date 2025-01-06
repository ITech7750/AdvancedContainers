FROM gradle:8.5-jdk17 AS builder
WORKDIR /app
COPY --chown=gradle:gradle settings.gradle.kts build.gradle.kts gradle* /app/
RUN gradle dependencies --no-daemon --build-cache --quiet
COPY --chown=gradle:gradle src /app/src
RUN gradle clean bootJar -x test --no-daemon --build-cache --quiet

FROM eclipse-temurin:17-jre-alpine AS runtime
WORKDIR /app
COPY --from=builder /app/build/libs/gistogram-service-0.0.1.jar /app/gistogram-service.jar
EXPOSE 8080
ENTRYPOINT ["java", "-jar", "/app/gistogram-service"]
