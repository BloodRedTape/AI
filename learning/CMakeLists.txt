cmake_minimum_required(VERSION 3.10)

add_executable(Twice "sources/twice.cpp")
target_link_libraries(Twice PUBLIC AICore)

add_executable(Gates "sources/gates.cpp")
target_link_libraries(Gates PUBLIC AICore)
