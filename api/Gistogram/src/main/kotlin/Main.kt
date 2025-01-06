package com.tech

import com.tech.nativelib.NativeLib


fun main() {
    val nativeLib = NativeLib()
    val result = nativeLib.stringFromJNI()
    println(result)
}