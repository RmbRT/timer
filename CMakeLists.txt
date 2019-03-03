cmake_minimum_required(VERSION 2.6)
project(timer)

file(COPY "src/" DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/timer/ FILES_MATCHING PATTERN "*.hpp" PATTERN "*.inl")
file(COPY "LICENSE" DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/timer/)