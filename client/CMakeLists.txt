# client/CMakeLists.txt
add_executable(client src/ClientMain.cpp
        src/Client.h
        src/Client.cpp
        ../Utils/GameUtils.h
        ../Utils/GameUtils.cpp)

target_link_libraries(client ws2_32)
