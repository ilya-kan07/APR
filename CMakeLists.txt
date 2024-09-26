cmake_minimum_required(VERSION 3.16)

project(AutomaticPowerReduction
    VERSION 1.0
)

include_directories(include)

# Указание заголовочных файлов
set(HEADER_FILES
    include/Amplifier.h
    include/LosDetector.h
    include/Node.h
    include/NodeTest.h
    include/OSC.h
    include/Receiver.h
    include/ClearConsole.h
    include/FiberFunction.h
    include/Sockets.h
)

set(SOURCE_FILES
    src/Amplifier.cpp
    src/LosDetector.cpp
    src/Node.cpp
    src/NodeTest.cpp
    src/OSC.cpp
    src/Receiver.cpp
)

add_library(MyLib
    ${SOURCE_FILES}
)

add_executable(AutomaticPowerReduction
    src/main.cpp
    ${HEADER_FILES}
)

target_link_libraries(AutomaticPowerReduction
    PRIVATE
    MyLib
)

# Добавление директории включения для заголовочных файлов
target_include_directories(AutomaticPowerReduction PUBLIC "${PROJECT_SOURCE_DIR}/include")
