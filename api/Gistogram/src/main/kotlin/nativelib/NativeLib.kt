package com.tech.nativelib

class NativeLib {

    /**
     * Returns a greeting message from native code.
     */
    external fun stringFromJNI(): String

    /**
     * Builds logistic data.
     */
    external fun buildLogistic(
        resultFilePath: String,
        cityAmount: Int,
        roadAmount: Int,
        cargo: Int
    )

    /**
     * Builds logistic data from a file.
     */
    external fun buildLogisticFromFile(
        dataFilePath: String,
        resultFilePath: String,
        startCity: String,
        endCity: String,
        cargo: Int
    )

    /**
     * Builds logistic vertex data.
     */
    external fun buildLogisticVertex(
        resultFilePath: String,
        cityAmount: Int,
        roadAmount: Int
    )

    /**
     * Builds logistic vertex data from a file.
     */
    external fun buildLogisticFromFileVertex(
        dataFilePath: String,
        resultFilePath: String,
        startCity: String,
        endCity: String
    )

    /**
     * Builds undirected logistic data.
     */
    external fun buildLogisticUndirected(
        resultFilePath: String,
        cityAmount: Int,
        roadAmount: Int,
        cargo: Int
    )

    /**
     * Builds undirected logistic data from a file.
     */
    external fun buildLogisticFromFileUndirected(
        dataFilePath: String,
        resultFilePath: String,
        startCity: String,
        endCity: String,
        cargo: Int
    )

    /**
     * Builds undirected logistic vertex data.
     */
    external fun buildLogisticVertexUndirected(
        resultFilePath: String,
        cityAmount: Int,
        roadAmount: Int
    )

    /**
     * Builds undirected logistic vertex data from a file.
     */
    external fun buildLogisticFromFileVertexUndirected(
        dataFilePath: String,
        resultFilePath: String,
        startCity: String,
        endCity: String
    )

    /**
     * Builds a histogram based on input parameters.
     */
    external fun buildGistogram(
        path: String,
        option: String,
        amount: Int,
        enableStatistic: Int,
        filter1: Int,
        filter2: Int,
        filter3: Int,
        filter4: Int,
        birthYear: Int,
        cityStartsWith: String
    )

    /**
     * Builds a histogram from a file.
     */
    external fun buildGistogramFromFile(
        path: String,
        filePath: String,
        option: String,
        amount: Int,
        enableStatistic: Int,
        filter1: Int,
        filter2: Int,
        filter3: Int,
        filter4: Int,
        birthYear: Int,
        cityStartsWith: String
    )

    /**
     * Builds a bag structure with given constraints.
     */
    external fun buildBag(
        path: String,
        amount: Int,
        maxCapacity: Int,
        maxVolume: Int
    )

    companion object {
        private val LIBRARY_PATH = System.getenv("NATIVE_LIB_PATH") ?: "/home/itech/Desktop/University/AdvancedContainers/api/Gistogram/libNativeLib.so"

        init {
            try {
                System.load(LIBRARY_PATH)
                println("Native library loaded successfully from $LIBRARY_PATH")
            } catch (e: UnsatisfiedLinkError) {
                println("Failed to load native library: ${e.message}")
                throw RuntimeException("Could not load native library", e)
            }
        }
    }

}
