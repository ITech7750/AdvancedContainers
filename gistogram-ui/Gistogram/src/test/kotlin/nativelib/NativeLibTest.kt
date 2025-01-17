package com.tech.nativelib

import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Assertions.fail
import org.junit.jupiter.api.Test

class NativeLibTest {

    private val nativeLib = NativeLib()

    @Test
    fun testStringFromJNI() {
        try {
            val result = nativeLib.stringFromJNI()
            assertEquals("Hello from C++", result, "stringFromJNI did not return the expected result")
        } catch (e: Exception) {
            fail("stringFromJNI threw an unexpected exception: ${e.message}")
        }
    }

    @Test
    fun testBuildLogistic() {
        val resultFilePath = "/tmp/result_logistic.txt"
        val cityAmount = 5
        val roadAmount = 10
        val cargo = 20

        try {
            nativeLib.buildLogistic(resultFilePath, cityAmount, roadAmount, cargo)
        } catch (e: Exception) {
            fail("buildLogistic threw an unexpected exception: ${e.message}")
        }
    }

    @Test
    fun testBuildLogisticFromFile() {
        val dataFilePath = "/tmp/input_logistic.txt"
        val resultFilePath = "/tmp/result_logistic.txt"
        val startCity = "CityA"
        val endCity = "CityB"
        val cargo = 30

        try {
            nativeLib.buildLogisticFromFile(dataFilePath, resultFilePath, startCity, endCity, cargo)
        } catch (e: Exception) {
            fail("buildLogisticFromFile threw an unexpected exception: ${e.message}")
        }
    }

    @Test
    fun testBuildLogisticVertex() {
        val resultFilePath = "/tmp/result_logistic_vertex.txt"
        val cityAmount = 6
        val roadAmount = 12

        try {
            nativeLib.buildLogisticVertex(resultFilePath, cityAmount, roadAmount)
        } catch (e: Exception) {
            fail("buildLogisticVertex threw an unexpected exception: ${e.message}")
        }
    }

    @Test
    fun testBuildLogisticFromFileVertex() {
        val dataFilePath = "/tmp/input_logistic_vertex.txt"
        val resultFilePath = "/tmp/result_logistic_vertex.txt"
        val startCity = "CityA"
        val endCity = "CityC"

        try {
            nativeLib.buildLogisticFromFileVertex(dataFilePath, resultFilePath, startCity, endCity)
        } catch (e: Exception) {
            fail("buildLogisticFromFileVertex threw an unexpected exception: ${e.message}")
        }
    }

    @Test
    fun testBuildLogisticUndirected() {
        val resultFilePath = "/tmp/result_logistic_undirected.txt"
        val cityAmount = 7
        val roadAmount = 15
        val cargo = 25

        try {
            nativeLib.buildLogisticUndirected(resultFilePath, cityAmount, roadAmount, cargo)
        } catch (e: Exception) {
            fail("buildLogisticUndirected threw an unexpected exception: ${e.message}")
        }
    }

    @Test
    fun testBuildLogisticFromFileUndirected() {
        val dataFilePath = "/tmp/input_logistic_undirected.txt"
        val resultFilePath = "/tmp/result_logistic_undirected.txt"
        val startCity = "CityX"
        val endCity = "CityY"
        val cargo = 40

        try {
            nativeLib.buildLogisticFromFileUndirected(dataFilePath, resultFilePath, startCity, endCity, cargo)
        } catch (e: Exception) {
            fail("buildLogisticFromFileUndirected threw an unexpected exception: ${e.message}")
        }
    }

    @Test
    fun testBuildLogisticVertexUndirected() {
        val resultFilePath = "/tmp/result_logistic_vertex_undirected.txt"
        val cityAmount = 8
        val roadAmount = 20

        try {
            nativeLib.buildLogisticVertexUndirected(resultFilePath, cityAmount, roadAmount)
        } catch (e: Exception) {
            fail("buildLogisticVertexUndirected threw an unexpected exception: ${e.message}")
        }
    }

    @Test
    fun testBuildGistogram() {
        val path = "/tmp/gistogram.txt"
        val option = "Person"
        val amount = 50
        val enableStatistic = 1
        val filters = arrayOf(1, 0, 1, 0)
        val birthYear = 1990
        val cityStartsWith = "A"

        try {
            nativeLib.buildGistogram(
                path,
                option,
                amount,
                enableStatistic,
                filters[0],
                filters[1],
                filters[2],
                filters[3],
                birthYear,
                cityStartsWith
            )
        } catch (e: Exception) {
            fail("buildGistogram threw an unexpected exception: ${e.message}")
        }
    }

    @Test
    fun testBuildGistogramFromFile() {
        val path = "/tmp/gistogram_from_file.txt"
        val filePath = "/tmp/input_gistogram.txt"
        val option = "Integer"
        val amount = 100
        val enableStatistic = 1
        val filters = arrayOf(1, 1, 0, 0)
        val birthYear = 1985
        val cityStartsWith = "B"

        try {
            nativeLib.buildGistogramFromFile(
                path,
                filePath,
                option,
                amount,
                enableStatistic,
                filters[0],
                filters[1],
                filters[2],
                filters[3],
                birthYear,
                cityStartsWith
            )
        } catch (e: Exception) {
            fail("buildGistogramFromFile threw an unexpected exception: ${e.message}")
        }
    }

    @Test
    fun testBuildBag() {
        val path = "/tmp/bag.json"
        val amount = 100
        val maxCapacity = 50
        val maxVolume = 200

        try {
            nativeLib.buildBag(path, amount, maxCapacity, maxVolume)
        } catch (e: Exception) {
            fail("buildBag threw an unexpected exception: ${e.message}")
        }
    }
}
