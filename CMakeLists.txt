cmake_minimum_required(VERSION 3.13)
project(Red_belt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-std=c++17")
#set(CMAKE_C_COMPILER /Library/Developer/CommandLineTools/usr/bin/gcc)
#set(CMAKE_CXX_COMPILER /Library/Developer/CommandLineTools/usr/bin/g++)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++")

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -gdwarf-3")
#set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -gdwarf-3")

set(SOURCE_FILES final_red/main.cpp final_red/parse.cpp final_red/search_server.cpp final_red/total_duration.h final_red/synhronized.h final_red/tests.h)
set(PYHON_FILES Solver.py Checker.py)


add_executable(Red_belt ${SOURCE_FILES} ${PYTHON_FILES} final_red/total_duration.h)
target_link_libraries(Red_belt ${PYTHON_LIBRARIES})

include_directories(google_tests)
add_subdirectory(google_tests)
