cmake_minimum_required(VERSION 3.25)
project(pidp_lab1)
set(CMAKE_CXX_STANDARD 17)
find_package(MPI REQUIRED)

add_executable(pidp_lab1 lab1/lab1_1.c)
add_executable(pidp_lab1_2 lab1/lab1_2.c)
add_executable(pidp_lab1_3 lab1/lab1_3.c)
add_executable(pidp_lab1_4 lab1/lab1_4.c)

target_link_libraries(pidp_lab1 PRIVATE MPI::MPI_CXX)
target_link_libraries(pidp_lab1_2 PRIVATE MPI::MPI_CXX)
target_link_libraries(pidp_lab1_3 PRIVATE MPI::MPI_CXX)
target_link_libraries(pidp_lab1_4 PRIVATE MPI::MPI_CXX)

