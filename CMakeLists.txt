cmake_minimum_required(VERSION 3.26)
project(Pointers)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 11.0)
    message(FATAL_ERROR "This project requires a compiler that supports C++20 or higher.")
endif()

find_package(nlohmann_json 3.2.0 REQUIRED)

add_executable(Pointers
        main.cpp
        test/loadTests/loadTests.cpp
        test/pointerTests/shrd/shrdPtrTestsAB.cpp
        test/pointerTests/smrt/smrtPtrTestsAB.cpp
        test/pointerTests/unq/unqPtrTestsAB.cpp
        test/loadTestSeq.cpp
        test/TestMutableListSequence.cpp
        ui/ui.cpp
        util/random.cpp
        test/pointerTests/unq/UnqPtrTests.cpp
        test/pointerTests/smrt/SmrtPtrTests.cpp
        test/pointerTests/shrd/ShrdPtrTests.cpp
        test/helper/TestHelpers.cpp
        test/helper/TestDataManagerList.cpp
        test/helper/TestDataManagerArray.cpp
        test/sorts/InteractiveTestSuiteList.cpp
        test/sorts/InteractiveTestSuiteArray.cpp
        test/sorts/DataTestSuiteArray.cpp
        test/sorts/DataTestSuiteList.cpp
        test/array/DynamicArrayTests.h
        test/array/DynamicArrayTests.cpp
        test/mutableArraySeq/MutableArraySequenceUnqPtrTests.h
        test/mutableArraySeq/MutableArraySequenceUnqPtrTests.cpp
)

target_link_libraries(Pointers nlohmann_json::nlohmann_json)
