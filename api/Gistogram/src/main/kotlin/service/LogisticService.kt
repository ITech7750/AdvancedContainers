package com.tech.service

import com.tech.data.City
import com.tech.data.Road
import com.tech.repository.LogisticRepository
import org.springframework.stereotype.Service
import org.springframework.web.multipart.MultipartFile
import java.nio.file.Files
import java.nio.file.Path
import java.nio.file.StandardCopyOption

@Service
class LogisticService(private val repository: LogisticRepository) {

    fun getGreeting(): String = repository.getNativeGreeting()

    fun buildLogistic(resultFilePath: String, cityAmount: Int, roadAmount: Int, cargo: Int) {
        repository.createLogistic(resultFilePath, cityAmount, roadAmount, cargo)
    }

    fun buildLogisticFromFile(
        dataFilePath: String?,
        dataFile: MultipartFile?,
        resultFilePath: String,
        startCity: String,
        endCity: String,
        cargo: Int
    ): Path {
        val inputFilePath = dataFilePath ?: saveTempFile(dataFile!!)
        repository.createLogisticFromFile(inputFilePath, resultFilePath, startCity, endCity, cargo)
        return Path.of(resultFilePath)
    }

    fun buildHistogramFromFile(
        path: String,
        filePath: String?,
        file: MultipartFile?,
        option: String,
        amount: Int,
        enableStatistic: Int,
        filter1: Int,
        filter2: Int,
        filter3: Int,
        filter4: Int,
        birthYear: Int,
        cityStartsWith: String
    ): Path {
        val inputFilePath = filePath ?: saveTempFile(file!!)
        repository.buildHistogramFromFile(path, inputFilePath, option, amount, enableStatistic, filter1, filter2, filter3, filter4, birthYear, cityStartsWith)
        return Path.of(path)
    }

    fun buildBag(path: String, amount: Int, maxCapacity: Int, maxVolume: Int) {
        repository.buildBag(path, amount, maxCapacity, maxVolume)
    }

    fun saveCity(city: City): City = repository.saveCity(city)

    fun saveRoad(road: Road): Road = repository.saveRoad(road)

    fun getCities(): List<City> = repository.getAllCities()

    fun getRoads(): List<Road> = repository.getAllRoads()

    fun deleteCity(name: String) = repository.deleteCityByName(name)

    fun buildLogisticVertex(
        resultFilePath: String?,
        resultFile: MultipartFile?,
        cityAmount: Int,
        roadAmount: Int
    ): Path {
        val filePath = resultFilePath ?: saveTempFile(resultFile!!)
        repository.createLogisticVertex(filePath, cityAmount, roadAmount)
        return Path.of(filePath)
    }

    fun buildHistogram(
        path: String?,
        file: MultipartFile?,
        option: String,
        amount: Int,
        enableStatistic: Int,
        filter1: Int,
        filter2: Int,
        filter3: Int,
        filter4: Int,
        birthYear: Int,
        cityStartsWith: String
    ): Path {
        val filePath = path ?: saveTempFile(file!!)
        repository.buildHistogram(filePath, option, amount, enableStatistic, filter1, filter2, filter3, filter4, birthYear, cityStartsWith)
        return Path.of(filePath)
    }


    private fun saveTempFile(file: MultipartFile): String {
        val tempFile = Files.createTempFile("upload_", file.originalFilename)
        Files.copy(file.inputStream, tempFile, StandardCopyOption.REPLACE_EXISTING)
        return tempFile.toString()
    }
}
