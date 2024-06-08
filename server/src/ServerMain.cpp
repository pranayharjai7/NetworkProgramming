#include "Server.h"

int main(int argc, char *argv[]) {
    Server server("127.0.0.1", 5001);
    server.start();
    return 0;
}
