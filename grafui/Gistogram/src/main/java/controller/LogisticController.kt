package com.tech.controller

import com.tech.data.City
import com.tech.data.Road
import com.tech.service.LogisticService
import io.swagger.v3.oas.annotations.Operation
import io.swagger.v3.oas.annotations.tags.Tag
import org.springframework.http.HttpStatus
import org.springframework.http.ResponseEntity
import org.springframework.web.bind.annotation.*
import org.springframework.web.multipart.MultipartFile
import java.nio.file.Path

@RestController
@RequestMapping("/api/logistics")
@Tag(
    name = "Сервис управления логистикой",
    description = "Операции по созданию и управлению логистическими данными"
)
class LogisticController(private val service: LogisticService) {

    @GetMapping("/greeting")
    @Operation(summary = "Тест", description = "Возвращает приветственное сообщение от нашей библиотеки")
    fun getGreeting(): String = service.getGreeting()

    @PostMapping("/logistic")
    @ResponseStatus(HttpStatus.CREATED)
    @Operation(summary = "Создать логистику", description = "Создает логистические данные с указанным количеством городов, дорог и грузов")
    fun createLogistic(
        @RequestParam resultFilePath: String,
        @RequestParam cityAmount: Int,
        @RequestParam roadAmount: Int,
        @RequestParam cargo: Int
    ) {
        service.buildLogistic(resultFilePath, cityAmount, roadAmount, cargo)
    }

    @PostMapping("/logistic/from-file")
    @Operation(summary = "Создать логистику из файла", description = "Создает логистические данные на основе данных из файла")
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
    @Operation(summary = "Создать гистограмму из файла", description = "Создает гистограмму на основе данных из файла")
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
    @Operation(summary = "Создать gistoram bag", description = "Создает данные сумки с заданными параметрами")
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
    @Operation(summary = "Сохранить город", description = "Сохраняет информацию о новом городе")
    fun saveCity(@RequestBody city: City): City = service.saveCity(city)

    @PostMapping("/road")
    @Operation(summary = "Сохранить дорогу", description = "Сохраняет информацию о новой дороге")
    fun saveRoad(@RequestBody road: Road): Road = service.saveRoad(road)

    @GetMapping("/cities")
    @Operation(summary = "Получить список городов", description = "Возвращает список всех городов")
    fun getCities(): List<City> = service.getCities()

    @GetMapping("/roads")
    @Operation(summary = "Получить список дорог", description = "Возвращает список всех дорог")
    fun getRoads(): List<Road> = service.getRoads()

    @DeleteMapping("/city/{name}")
    @ResponseStatus(HttpStatus.NO_CONTENT)
    @Operation(summary = "Удалить город", description = "Удаляет город по его имени")
    fun deleteCity(@PathVariable name: String) {
        service.deleteCity(name)
    }

    @PostMapping("/logistic/vertex")
    @Operation(summary = "Создать вершины логистики", description = "Создает логистические вершины с заданным количеством городов и дорог")
    fun createLogisticVertex(
        @RequestParam(required = false) resultFilePath: String?,
        @RequestParam(required = false) resultFile: MultipartFile?,
        @RequestParam cityAmount: Int,
        @RequestParam roadAmount: Int
    ): ResponseEntity<Path> {
        val filePath = service.buildLogisticVertex(resultFilePath, resultFile, cityAmount, roadAmount)
        return ResponseEntity.ok(filePath)
    }

    @PostMapping("/logistic/undirected")
    @Operation(summary = "Создать неориентированную логистику", description = "Создает логистические данные с неориентированными дорогами")
    fun createLogisticUndirected(
        @RequestParam resultFilePath: String,
        @RequestParam cityAmount: Int,
        @RequestParam roadAmount: Int,
        @RequestParam cargo: Int
    ) {
        service.buildLogisticUndirected(resultFilePath, cityAmount, roadAmount, cargo)
    }

    @PostMapping("/logistic/from-file/undirected")
    @Operation(summary = "Создать неориентированную логистику из файла", description = "Создает логистические данные из файла с неориентированными дорогами")
    fun createLogisticFromFileUndirected(
        @RequestParam(required = false) dataFilePath: String?,
        @RequestParam(required = false) dataFile: MultipartFile?,
        @RequestParam resultFilePath: String,
        @RequestParam startCity: String,
        @RequestParam endCity: String,
        @RequestParam cargo: Int
    ): ResponseEntity<Path> {
        val resultPath = service.buildLogisticFromFileUndirected(dataFilePath, dataFile, resultFilePath, startCity, endCity, cargo)
        return ResponseEntity.ok(resultPath)
    }

    @PostMapping("/logistic/vertex/undirected")
    @Operation(summary = "Создать неориентированные вершины логистики", description = "Создает логистические вершины с неориентированными дорогами")
    fun createLogisticVertexUndirected(
        @RequestParam(required = false) resultFilePath: String?,
        @RequestParam(required = false) resultFile: MultipartFile?,
        @RequestParam cityAmount: Int,
        @RequestParam roadAmount: Int
    ): ResponseEntity<Path> {
        val filePath = service.buildLogisticVertexUndirected(resultFilePath, resultFile, cityAmount, roadAmount)
        return ResponseEntity.ok(filePath)
    }

    @PostMapping("/histogram")
    @Operation(summary = "Создать гистограмму", description = "Создает гистограмму на основе предоставленных параметров или загружаемого файла")
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


    @PostMapping("/logistic/from-file/vertex/undirected")
    @Operation(summary = "Создать неориентированные вершины логистики из файла", description = "Создает логистические вершины из файла с неориентированными дорогами")
    fun createLogisticFromFileVertexUndirected(
        @RequestParam(required = false) dataFilePath: String?,
        @RequestParam(required = false) dataFile: MultipartFile?,
        @RequestParam resultFilePath: String,
        @RequestParam startCity: String,
        @RequestParam endCity: String
    ): ResponseEntity<Path> {
        val resultPath = service.buildLogisticFromFileVertexUndirected(dataFilePath, dataFile, resultFilePath, startCity, endCity)
        return ResponseEntity.ok(resultPath)
    }
}
