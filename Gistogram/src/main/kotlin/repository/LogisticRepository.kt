package com.tech.repository

import com.tech.data.City
import com.tech.data.Road
import com.tech.nativelib.NativeLib
import org.springframework.stereotype.Repository
import org.springframework.transaction.annotation.Transactional

@Repository
@Transactional
class LogisticRepository(private val cityRepository: CityJpaRepository, private val roadRepository: RoadJpaRepository) {

    private val nativeLib = NativeLib()

    fun getNativeGreeting(): String {
        return nativeLib.stringFromJNI()
    }

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

    fun saveCity(city: City): City {
        return cityRepository.save(city)
    }

    fun saveRoad(road: Road): Road {
        return roadRepository.save(road)
    }

    fun getAllCities(): List<City> {
        return cityRepository.findAll()
    }

    fun getAllRoads(): List<Road> {
        return roadRepository.findAll()
    }

    fun deleteCityByName(name: String) {
        cityRepository.deleteByName(name)
    }
}
