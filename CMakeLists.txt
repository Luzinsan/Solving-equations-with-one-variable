cmake_minimum_required(VERSION 3.21)
project(Solving_equations_with_one_variable)

set(CMAKE_CXX_STANDARD 14)

include_directories("Solving equations with one variable")

add_executable(Solving_equations_with_one_variable
        "Solving equations with one variable/EquationScalar.h"
        "Solving equations with one variable/IInputDevice.cpp"
        "Solving equations with one variable/IInputDevice.h"
        "Solving equations with one variable/main.cpp"
        "Solving equations with one variable/PolStr.h"
        "Solving equations with one variable/Timer.cpp"
        "Solving equations with one variable/Timer.h")
