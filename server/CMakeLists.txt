# server/CMakeLists.txt
add_executable(server src/ServerMain.cpp
        src/ClientHandler.h
        src/ClientHandler.cpp
        src/Server.h
        src/Server.cpp
        ../Utils/GameUtils.h
        ../Utils/GameUtils.cpp)

# Link necessary libraries for the server
target_link_libraries(server ws2_32)
