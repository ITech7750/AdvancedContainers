package com.tech.controller

import com.tech.data.City
import com.tech.data.Road
import com.tech.service.LogisticService
import org.springframework.http.HttpStatus
import org.springframework.web.bind.annotation.*

@RestController
@RequestMapping("/api/logistics")
class LogisticController(private val service: LogisticService) {

    @GetMapping("/greeting")
    fun getGreeting(): String {
        return service.getGreeting()
    }

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
        @RequestParam dataFilePath: String,
        @RequestParam resultFilePath: String,
        @RequestParam startCity: String,
        @RequestParam endCity: String,
        @RequestParam cargo: Int
    ) {
        service.buildLogisticFromFile(dataFilePath, resultFilePath, startCity, endCity, cargo)
    }

    @PostMapping("/city")
    fun saveCity(@RequestBody city: City): City {
        return service.saveCity(city)
    }

    @PostMapping("/road")
    fun saveRoad(@RequestBody road: Road): Road {
        return service.saveRoad(road)
    }

    @GetMapping("/cities")
    fun getCities(): List<City> {
        return service.getCities()
    }

    @GetMapping("/roads")
    fun getRoads(): List<Road> {
        return service.getRoads()
    }

    @DeleteMapping("/city/{name}")
    @ResponseStatus(HttpStatus.NO_CONTENT)
    fun deleteCity(@PathVariable name: String) {
        service.deleteCity(name)
    }
}
