cmake_minimum_required(VERSION 3.13)
project(Red_belt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-std=c++17")
set(CMAKE_C_COMPILER /Library/Developer/CommandLineTools/usr/bin/gcc)
set(CMAKE_CXX_COMPILER /Library/Developer/CommandLineTools/usr/bin/g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++")

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -gdwarf-3")
#set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -gdwarf-3")


add_executable(Red_belt final_red/main.cpp final_red/parse.cpp final_red/search_server.cpp)
