#include <iostream>
#include <filesystem>
#include "asio.hpp"
#include "httprequest.h"
#include "server.h"
#include "httpresponse.h"

using asio::ip::tcp;

int main() {

    server ser("192.168.0.105","4444");
    ser.run();
    return 0;
}
