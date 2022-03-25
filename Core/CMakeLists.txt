cmake_minimum_required(VERSION 3.13)  # CMake version check
project(CodeEditorCpp)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 17)            # Enable c++14 standard

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES main.cpp)

FILE (GLOB SOURCE Source/*.cpp)

add_executable(CodeEditorCpp ${SOURCE} main.cpp)

SET(TARGET_H

    Headers/TStack.h
    Headers/TDataCom.h
    Headers/TDataValue.h
    Headers/TText.h
    Headers/TTextLink.h 

)

SET(TARGET_SRC

    Source/TDataCom.cpp
    Source/TDataValue.cpp
    Source/TTextLink.cpp
    Source/TText.cpp

)



# target_include_directories(CodeEditorCore PUBLIC include)

# Add executable target with source files listed in SOURCE_FILES variable

