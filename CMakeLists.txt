cmake_minimum_required (VERSION 2.6)
project (Partio)
add_executable(partio src/main.cpp src/chat.cpp src/lib/network.cpp)
ADD_DEFINITIONS(
    -std=c++11 # Or -std=c++0x
    # Other flags
)
