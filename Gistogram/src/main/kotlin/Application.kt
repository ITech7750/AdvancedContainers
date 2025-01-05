package com.tech

import org.springframework.boot.autoconfigure.SpringBootApplication
import org.springframework.boot.runApplication

@SpringBootApplication
class NativeLibraryApplication

fun main(args: Array<String>) {
    runApplication<NativeLibraryApplication>(*args)
}
