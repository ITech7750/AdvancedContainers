package com.tech.service

import com.tech.data.City
import com.tech.data.Road
import com.tech.repository.LogisticRepository
import org.springframework.stereotype.Service

@Service
class LogisticService(private val repository: LogisticRepository) {

    fun getGreeting(): String {
        return repository.getNativeGreeting()
    }

    fun buildLogistic(
        resultFilePath: String,
        cityAmount: Int,
        roadAmount: Int,
        cargo: Int
    ) {
        repository.createLogistic(resultFilePath, cityAmount, roadAmount, cargo)
    }

    fun buildLogisticFromFile(
        dataFilePath: String,
        resultFilePath: String,
        startCity: String,
        endCity: String,
        cargo: Int
    ) {
        repository.createLogisticFromFile(dataFilePath, resultFilePath, startCity, endCity, cargo)
    }

    fun saveCity(city: City): City {
        return repository.saveCity(city)
    }

    fun saveRoad(road: Road): Road {
        return repository.saveRoad(road)
    }

    fun getCities(): List<City> {
        return repository.getAllCities()
    }

    fun getRoads(): List<Road> {
        return repository.getAllRoads()
    }

    fun deleteCity(name: String) {
        repository.deleteCityByName(name)
    }
}
