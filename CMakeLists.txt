cmake_minimum_required(VERSION 3.26)
project(Pointers)

# Установить стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Проверить минимальную версию компилятора
if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 11.0)
    message(FATAL_ERROR "This project requires a compiler that supports C++20 or higher.")
endif()

# Найти и подключить nlohmann_json
find_package(nlohmann_json 3.2.0 REQUIRED)

# Подключение Java и JNI
find_package(Java REQUIRED)
find_package(JNI REQUIRED)

if (NOT JNI_FOUND)
    message(FATAL_ERROR "JNI not found. Please ensure you have JDK installed and JAVA_HOME set.")
endif()

# Логирование найденных директорий JNI
message(STATUS "JNI Include Directories: ${JNI_INCLUDE_DIRS}")
message(STATUS "JNI Libraries: ${JNI_LIBRARIES}")

# NativeLib
add_library(NativeLib SHARED
        test/loadTests/loadTests.cpp
        test/pointerTests/shrd/shrdPtrTestsAB.cpp
        test/pointerTests/smrt/smrtPtrTestsAB.cpp
        test/pointerTests/unq/unqPtrTestsAB.cpp
        test/loadSeq/loadTestSeq.cpp
        test/mutableListSeq/TestMutableListSequence.cpp
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
        test/array/DynamicArrayTests.cpp
        test/mutableArraySeq/MutableArraySequenceUnqPtrTests.cpp
        jni/SorterServiceJNI.cpp
        jni/nativelib.cpp
        test/pointerTests/weak/WeakPtrTests.cpp
        test/mutableListSeq/MutableListSequenceUnqPtrTests.cpp
        test/pointerTests/unq/UnqPtrLoadTest.cpp
        test/pointerTests/smrt/SmrtPtrLoadTest.cpp
        test/pointerTests/shrd/ShrdPtrLoadTest.cpp
        test/pointerTests/weak/WeakPtrLoadTest.cpp
        test/hashmap/HashMapTests.cpp
        test/hashmap/HashMapTest.cpp
        test/dict/DictionaryTest.cpp
        test/dict/DictionaryTests.cpp
        test/gistogram/GistogramTests.cpp
        test/gistogram/GistogramTests.h
        jni/HashMapJNI.h
        jni/HashMapJNI.cpp
)

target_include_directories(NativeLib PRIVATE ${JNI_INCLUDE_DIRS})
target_link_libraries(NativeLib PRIVATE ${JNI_LIBRARIES})

set_target_properties(NativeLib PROPERTIES
        OUTPUT_NAME "NativeLib"
        PREFIX "lib"
)

# HashMapLibrary
add_library(HashMapLibrary SHARED
        test/loadTests/loadTests.cpp
        test/pointerTests/shrd/shrdPtrTestsAB.cpp
        test/pointerTests/smrt/smrtPtrTestsAB.cpp
        test/pointerTests/unq/unqPtrTestsAB.cpp
        test/loadSeq/loadTestSeq.cpp
        test/mutableListSeq/TestMutableListSequence.cpp
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
        test/array/DynamicArrayTests.cpp
        test/mutableArraySeq/MutableArraySequenceUnqPtrTests.cpp
        jni/SorterServiceJNI.cpp
        jni/nativelib.cpp
        test/pointerTests/weak/WeakPtrTests.cpp
        test/mutableListSeq/MutableListSequenceUnqPtrTests.cpp
        test/pointerTests/unq/UnqPtrLoadTest.cpp
        test/pointerTests/smrt/SmrtPtrLoadTest.cpp
        test/pointerTests/shrd/ShrdPtrLoadTest.cpp
        test/pointerTests/weak/WeakPtrLoadTest.cpp
        test/hashmap/HashMapTests.cpp
        test/hashmap/HashMapTest.cpp
        test/dict/DictionaryTest.cpp
        test/dict/DictionaryTests.cpp
        test/gistogram/GistogramTests.cpp
        test/gistogram/GistogramTests.h
        jni/HashMapJNI.h
        jni/HashMapJNI.cpp
        jni/GistogramJNI.cpp
        jni/GistogramJNI.h

)
add_library(GistogramLibrary SHARED
        test/loadTests/loadTests.cpp
        test/pointerTests/shrd/shrdPtrTestsAB.cpp
        test/pointerTests/smrt/smrtPtrTestsAB.cpp
        test/pointerTests/unq/unqPtrTestsAB.cpp
        test/loadSeq/loadTestSeq.cpp
        test/mutableListSeq/TestMutableListSequence.cpp
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
        test/array/DynamicArrayTests.cpp
        test/mutableArraySeq/MutableArraySequenceUnqPtrTests.cpp
        jni/SorterServiceJNI.cpp
        jni/nativelib.cpp
        test/pointerTests/weak/WeakPtrTests.cpp
        test/mutableListSeq/MutableListSequenceUnqPtrTests.cpp
        test/pointerTests/unq/UnqPtrLoadTest.cpp
        test/pointerTests/smrt/SmrtPtrLoadTest.cpp
        test/pointerTests/shrd/ShrdPtrLoadTest.cpp
        test/pointerTests/weak/WeakPtrLoadTest.cpp
        test/hashmap/HashMapTests.cpp
        test/hashmap/HashMapTest.cpp
        test/dict/DictionaryTest.cpp
        test/dict/DictionaryTests.cpp
        test/gistogram/GistogramTests.cpp
        test/gistogram/GistogramTests.h
        jni/HashMapJNI.h
        jni/HashMapJNI.cpp
        jni/GistogramJNI.cpp
        jni/GistogramJNI.h

)

target_include_directories(GistogramLibrary PRIVATE ${JNI_INCLUDE_DIRS})
target_link_libraries(GistogramLibrary PRIVATE ${JNI_LIBRARIES})

set_target_properties(GistogramLibrary PROPERTIES
        OUTPUT_NAME "GistogramLibrary"
        PREFIX "lib"
)


target_include_directories(HashMapLibrary PRIVATE ${JNI_INCLUDE_DIRS})
target_link_libraries(HashMapLibrary PRIVATE ${JNI_LIBRARIES})

set_target_properties(HashMapLibrary PROPERTIES
        OUTPUT_NAME "HashMapLibrary"
        PREFIX "lib"
)
# SorterService
add_library(SorterService SHARED
        test/loadTests/loadTests.cpp
        test/pointerTests/shrd/shrdPtrTestsAB.cpp
        test/pointerTests/smrt/smrtPtrTestsAB.cpp
        test/pointerTests/unq/unqPtrTestsAB.cpp
        test/loadSeq/loadTestSeq.cpp
        test/mutableListSeq/TestMutableListSequence.cpp
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
        test/array/DynamicArrayTests.cpp
        test/mutableArraySeq/MutableArraySequenceUnqPtrTests.cpp
        jni/SorterServiceJNI.cpp
        test/dict/DictionaryTest.cpp
        test/dict/DictionaryTests.cpp
)

target_include_directories(SorterService PRIVATE ${JNI_INCLUDE_DIRS})
target_link_libraries(SorterService PRIVATE nlohmann_json::nlohmann_json ${JNI_LIBRARIES})

set_target_properties(SorterService PROPERTIES
        OUTPUT_NAME "SorterService"
        PREFIX "lib"
)

# Executable
add_executable(PointersExec
        main.cpp
)

target_link_libraries(PointersExec PRIVATE SorterService NativeLib HashMapLibrary)

# Run target
add_custom_target(run
        COMMAND PointersExec
        DEPENDS PointersExec
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Running the executable..."
)
