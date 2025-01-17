FROM gradle:8.5-jdk17 AS builder
WORKDIR /app
COPY --chown=gradle:gradle settings.gradle.kts build.gradle.kts gradle* /app/
RUN gradle dependencies --no-daemon --build-cache --quiet
COPY --chown=gradle:gradle src /app/src
RUN gradle clean bootJar -x test --no-daemon --build-cache --quiet && ls -l /app/build/libs

FROM eclipse-temurin:17-jre-alpine AS runtime
WORKDIR /app
RUN apk add --no-cache libstdc++ libgcc
COPY --from=builder /app/build/libs/gistogram-service-0.0.1.jar /app/gistogram-service.jar
COPY libNativeLib.so /app/libNativeLib.so
EXPOSE 8080
ENTRYPOINT ["java", "-jar", "/app/gistogram-service.jar"]
