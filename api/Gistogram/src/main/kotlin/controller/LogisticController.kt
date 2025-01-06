package com.tech.controller

import com.tech.data.City
import com.tech.data.Road
import com.tech.service.LogisticService
import org.springframework.http.HttpStatus
import org.springframework.http.ResponseEntity
import org.springframework.web.bind.annotation.*
import org.springframework.web.multipart.MultipartFile
import java.nio.file.Path

@RestController
@RequestMapping("/api/logistics")
class LogisticController(private val service: LogisticService) {

    @GetMapping("/greeting")
    fun getGreeting(): String = service.getGreeting()

    @PostMapping("/logistic")
    @ResponseStatus(HttpStatus.CREATED)
    fun createLogistic(
        @RequestParam resultFilePath: String,
        @RequestParam cityAmount: Int,
        @RequestParam roadAmount: Int,
        @RequestParam cargo: Int
    ) {
        service.buildLogistic(resultFilePath, cityAmount, roadAmount, cargo)
    }


    @PostMapping("/logistic/from-file")
    fun createLogisticFromFile(
        @RequestParam(required = false) dataFilePath: String?,
        @RequestParam(required = false) dataFile: MultipartFile?,
        @RequestParam resultFilePath: String,
        @RequestParam startCity: String,
        @RequestParam endCity: String,
        @RequestParam cargo: Int
    ): ResponseEntity<Path> {
        val resultPath = service.buildLogisticFromFile(dataFilePath, dataFile, resultFilePath, startCity, endCity, cargo)
        return ResponseEntity.ok(resultPath)
    }

    @PostMapping("/histogram/from-file")
    fun buildHistogramFromFile(
        @RequestParam path: String,
        @RequestParam(required = false) filePath: String?,
        @RequestParam(required = false) file: MultipartFile?,
        @RequestParam option: String,
        @RequestParam amount: Int,
        @RequestParam enableStatistic: Int,
        @RequestParam filter1: Int,
        @RequestParam filter2: Int,
        @RequestParam filter3: Int,
        @RequestParam filter4: Int,
        @RequestParam birthYear: Int,
        @RequestParam cityStartsWith: String
    ): ResponseEntity<Path> {
        val resultPath = service.buildHistogramFromFile(path, filePath, file, option, amount, enableStatistic, filter1, filter2, filter3, filter4, birthYear, cityStartsWith)
        return ResponseEntity.ok(resultPath)
    }

    @PostMapping("/bag")
    fun buildBag(
        @RequestParam path: String,
        @RequestParam amount: Int,
        @RequestParam maxCapacity: Int,
        @RequestParam maxVolume: Int
    ): ResponseEntity<Path> {
        service.buildBag(path, amount, maxCapacity, maxVolume)
        return ResponseEntity.ok(Path.of(path))
    }

    @PostMapping("/city")
    fun saveCity(@RequestBody city: City): City = service.saveCity(city)

    @PostMapping("/road")
    fun saveRoad(@RequestBody road: Road): Road = service.saveRoad(road)

    @GetMapping("/cities")
    fun getCities(): List<City> = service.getCities()

    @GetMapping("/roads")
    fun getRoads(): List<Road> = service.getRoads()

    @DeleteMapping("/city/{name}")
    @ResponseStatus(HttpStatus.NO_CONTENT)
    fun deleteCity(@PathVariable name: String) {
        service.deleteCity(name)
    }

    @PostMapping("/logistic/vertex")
    fun createLogisticVertex(
        @RequestParam(required = false) resultFilePath: String?,
        @RequestParam(required = false) resultFile: MultipartFile?,
        @RequestParam cityAmount: Int,
        @RequestParam roadAmount: Int
    ): ResponseEntity<Path> {
        val filePath = service.buildLogisticVertex(resultFilePath, resultFile, cityAmount, roadAmount)
        return ResponseEntity.ok(filePath)
    }

    @PostMapping("/histogram")
    fun buildHistogram(
        @RequestParam(required = false) path: String?,
        @RequestParam(required = false) file: MultipartFile?,
        @RequestParam option: String,
        @RequestParam amount: Int,
        @RequestParam enableStatistic: Int,
        @RequestParam filter1: Int,
        @RequestParam filter2: Int,
        @RequestParam filter3: Int,
        @RequestParam filter4: Int,
        @RequestParam birthYear: Int,
        @RequestParam cityStartsWith: String
    ): ResponseEntity<Path> {
        val resultPath = service.buildHistogram(path, file, option, amount, enableStatistic, filter1, filter2, filter3, filter4, birthYear, cityStartsWith)
        return ResponseEntity.ok(resultPath)
    }

}
