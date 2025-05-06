cmake_minimum_required(VERSION 3.28.1)
project(computerClubPrototype)

set(CMAKE_CXX_STANDARD 20)

set(PROCESSING_FILES
        src/processing/clientHandler.h
        src/processing/clientHandler.cpp    
        )

set(PARSER_FILES
        src/parser/parser.h
        src/parser/parser.cpp       
        )

set(SOURCE_FILES
        src/common.h
        ${PARSER_FILES}
        ${PROCESSING_FILES}
        src/clubDriver.h
        src/clubDriver.cpp
        )


add_executable(computerClubPrototype main.cpp
        ${SOURCE_FILES})

