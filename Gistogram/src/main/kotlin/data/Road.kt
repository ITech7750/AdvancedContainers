package com.tech.data

import jakarta.persistence.*

@Entity
@Table(name = "roads")
data class Road(
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    val id: Long = 0,
    val name: String = "",
    val length: String = "",
    val maxSpeed: String = "",
    @ManyToOne
    @JoinColumn(name = "start_city_id")
    val start: City,
    @ManyToOne
    @JoinColumn(name = "end_city_id")
    val end: City
)
