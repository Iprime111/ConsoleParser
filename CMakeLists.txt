cmake_minimum_required (VERSION 3.8 FATAL_ERROR)

project (ConsoleParser)

add_library (${PROJECT_NAME} STATIC src/ConsoleParser.cpp
                                 headers/ConsoleParser.h)

target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers)

add_subdirectory (CustomAssert)
target_link_libraries (${PROJECT_NAME} PRIVATE CustomAssert)



