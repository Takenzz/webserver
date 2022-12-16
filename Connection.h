#include <vector>
#include "asio.hpp"
#include "httprequest.h"
#include "httpresponse.h"
#include "threadPool.h"

using asio::ip::tcp;

class Connection {
public:
    void connection_receive(tcp::socket socket);
    asio::awaitable<void> connection_handle(tcp::socket socket);
private:
    threadPool io_pool;
};





