package com.tech.repository

import com.tech.data.Road
import org.springframework.data.jpa.repository.JpaRepository
import org.springframework.stereotype.Repository

@Repository
interface RoadJpaRepository : JpaRepository<Road, Long>