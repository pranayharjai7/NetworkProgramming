# client/CMakeLists.txt
add_executable(client src/ClientMain.cpp)

target_link_libraries(client ws2_32)
