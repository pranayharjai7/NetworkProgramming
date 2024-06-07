# server/CMakeLists.txt
add_executable(server src/ServerMain.cpp)

# Link necessary libraries for the server
target_link_libraries(server ws2_32)
