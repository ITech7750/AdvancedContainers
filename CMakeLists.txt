cmake_minimum_required(VERSION 3.26)
project(Pointers)

set(CMAKE_CXX_STANDARD 17)

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
)
