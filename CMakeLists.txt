cmake_minimum_required(VERSION 3.5.1)
project(MRUSSA)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11 -O2")

set(SOURCE_FILES main.cpp Passageiro.cpp Carro.cpp Parque.cpp)
add_executable(MRUSSA ${SOURCE_FILES})