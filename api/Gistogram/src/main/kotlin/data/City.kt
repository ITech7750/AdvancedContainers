package com.tech.data

import jakarta.persistence.*

@Entity
@Table(name = "cities")
data class City(
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    val id: Long = 0,
    val name: String = "",
    val cargoToDrop: Int = 0,
    val x: Float = 0f,
    val y: Float = 0f
)
