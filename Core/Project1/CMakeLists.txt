cmake_minimum_required(VERSION 3.13)  # Проверка версии
project(CodeEditorCpp)                # Название проекта 
set(CMAKE_CXX_STANDARD 17)            # Использовать стандарт С++17

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


