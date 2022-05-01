CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
PROJECT(UDPDataCom)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

link_directories(${OpenCV_LIBRARY_DIRS})

add_executable(server sender.cpp udp.cpp)
target_link_libraries(server ${OpenCV_LIBS})

add_executable(client receiver.cpp udp.cpp)
target_link_libraries(client ${OpenCV_LIBS})