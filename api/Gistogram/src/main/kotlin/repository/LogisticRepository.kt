package com.tech.repository

import com.tech.data.City
import com.tech.data.Road
import com.tech.nativelib.NativeLib
import org.springframework.stereotype.Repository
import org.springframework.transaction.annotation.Transactional

@Repository
@Transactional
class LogisticRepository(
    private val cityRepository: CityJpaRepository,
    private val roadRepository: RoadJpaRepository
) {
    private val nativeLib = NativeLib()

    fun getNativeGreeting(): String = nativeLib.stringFromJNI()

    fun createLogistic(resultFilePath: String, cityAmount: Int, roadAmount: Int, cargo: Int) {
        nativeLib.buildLogistic(resultFilePath, cityAmount, roadAmount, cargo)
    }

    fun createLogisticFromFile(
        dataFilePath: String,
        resultFilePath: String,
        startCity: String,
        endCity: String,
        cargo: Int
    ) {
        nativeLib.buildLogisticFromFile(dataFilePath, resultFilePath, startCity, endCity, cargo)
    }

    fun createLogisticVertex(resultFilePath: String, cityAmount: Int, roadAmount: Int) {
        nativeLib.buildLogisticVertex(resultFilePath, cityAmount, roadAmount)
    }

    fun createLogisticFromFileVertex(
        dataFilePath: String,
        resultFilePath: String,
        startCity: String,
        endCity: String
    ) {
        nativeLib.buildLogisticFromFileVertex(dataFilePath, resultFilePath, startCity, endCity)
    }

    fun createLogisticUndirected(
        resultFilePath: String,
        cityAmount: Int,
        roadAmount: Int,
        cargo: Int
    ) {
        nativeLib.buildLogisticUndirected(resultFilePath, cityAmount, roadAmount, cargo)
    }

    fun createLogisticFromFileUndirected(
        dataFilePath: String,
        resultFilePath: String,
        startCity: String,
        endCity: String,
        cargo: Int
    ) {
        nativeLib.buildLogisticFromFileUndirected(dataFilePath, resultFilePath, startCity, endCity, cargo)
    }

    fun createLogisticVertexUndirected(resultFilePath: String, cityAmount: Int, roadAmount: Int) {
        nativeLib.buildLogisticVertexUndirected(resultFilePath, cityAmount, roadAmount)
    }

    fun createLogisticFromFileVertexUndirected(
        dataFilePath: String,
        resultFilePath: String,
        startCity: String,
        endCity: String
    ) {
        nativeLib.buildLogisticFromFileVertexUndirected(dataFilePath, resultFilePath, startCity, endCity)
    }

    fun buildHistogram(
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
    ) {
        nativeLib.buildGistogram(path, option, amount, enableStatistic, filter1, filter2, filter3, filter4, birthYear, cityStartsWith)
    }

    fun buildHistogramFromFile(
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
    ) {
        nativeLib.buildGistogramFromFile(path, filePath, option, amount, enableStatistic, filter1, filter2, filter3, filter4, birthYear, cityStartsWith)
    }

    fun buildBag(path: String, amount: Int, maxCapacity: Int, maxVolume: Int) {
        nativeLib.buildBag(path, amount, maxCapacity, maxVolume)
    }

    fun saveCity(city: City): City = cityRepository.save(city)

    fun saveRoad(road: Road): Road = roadRepository.save(road)

    fun getAllCities(): List<City> = cityRepository.findAll()

    fun getAllRoads(): List<Road> = roadRepository.findAll()

    fun deleteCityByName(name: String) = cityRepository.deleteByName(name)
}
