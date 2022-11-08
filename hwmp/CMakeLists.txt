cmake_minimum_required(VERSION 3.23)
project(hwmp)

set(CMAKE_CXX_STANDARD 14)

find_package(MPI REQUIRED)

add_executable(hwmp main.cpp)
add_executable(task1 tasks/task1.cpp)
add_executable(task2 tasks/task2.cpp)
add_executable(task3 tasks/task3.cpp)
add_executable(task4 tasks/task4.cpp)
add_executable(task5 tasks/task5.cpp)
add_executable(task6 tasks/task6.cpp)
add_executable(task7 tasks/task7.cpp)
add_executable(task8 tasks/task8.cpp)
add_executable(task9 tasks/task9.cpp)
add_executable(task10 tasks/task10.cpp)
add_executable(task11 tasks/task11.cpp)
add_executable(task12 tasks/task12.cpp)
add_executable(task13 tasks/task13.cpp)
add_executable(task14 tasks/task14.cpp)

target_link_libraries(task1 PUBLIC MPI::MPI_CXX)
target_link_libraries(task2 PUBLIC MPI::MPI_CXX)
target_link_libraries(task3 PUBLIC MPI::MPI_CXX)
target_link_libraries(task4 PUBLIC MPI::MPI_CXX)
target_link_libraries(task5 PUBLIC MPI::MPI_CXX)
target_link_libraries(task6 PUBLIC MPI::MPI_CXX)
target_link_libraries(task7 PUBLIC MPI::MPI_CXX)
target_link_libraries(task8 PUBLIC MPI::MPI_CXX)
target_link_libraries(task9 PUBLIC MPI::MPI_CXX)
target_link_libraries(task10 PUBLIC MPI::MPI_CXX)
target_link_libraries(task11 PUBLIC MPI::MPI_CXX)
target_link_libraries(task12 PUBLIC MPI::MPI_CXX)
target_link_libraries(task13 PUBLIC MPI::MPI_CXX)
target_link_libraries(task14 PUBLIC MPI::MPI_CXX)



# Include MPI includes
include_directories(${MPI_INCLUDE_PATH})
if(MPI_COMPILE_FLAGS)
    set_target_properties(mainExec PROPERTIES
            COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()
if(MPI_LINK_FLAGS)
    set_target_properties(mainExec PROPERTIES
            LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()
