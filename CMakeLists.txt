cmake_minimum_required(VERSION 3.26)
project(Pointers)

set(CMAKE_CXX_STANDARD 17)

add_executable(Pointers
        main.cpp
        test/loadTests/loadTests.cpp
        test/pointerTests/shrdPtrTests.cpp
        test/pointerTests/smrtPtrTests.cpp
        test/pointerTests/unqPtrTests.cpp
        test/loadTestSeq.cpp
        test/TestMutableListSequence.cpp
        ui/ui.cpp
        util/random.cpp
)
