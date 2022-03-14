cmake_minimum_required(VERSION 3.21)
project(NMLab)

set(CMAKE_CXX_STANDARD 20)

add_executable(NMLab main.cpp EquationScalar.h IInputDevice.cpp IInputDevice.h Timer.h)
add_library(PolStr INTERFACE PolStr.dll PolStr.h)

#set_target_properties(PolStr PROPERTIES LINKER_LANGUAGE CXX)

