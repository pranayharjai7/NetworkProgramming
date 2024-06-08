#include "Client.h"

int main(int argc, char *argv[]) {
    Client client("127.0.0.1", 5001);
    client.start();
    client.playGame();
    return 0;
}
