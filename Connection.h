#include <vector>
#include "asio.hpp"
#include "httprequest.h"
#include "httpresponse.h"

using asio::ip::tcp;

class Connection {
public:
    void connection_receive(tcp::socket socket, asio::io_context &io);
    asio::awaitable<void> connection_handle(tcp::socket socket);
    void run();

private:
    asio::io_context io_;

};





