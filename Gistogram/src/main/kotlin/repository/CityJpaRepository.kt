package com.tech.repository

import com.tech.data.City
import org.springframework.data.jpa.repository.JpaRepository
import org.springframework.stereotype.Repository

@Repository
interface CityJpaRepository : JpaRepository<City, Long> {
    fun deleteByName(name: String)
}