#ifndef WEBSERVER_SERVER_H
#define WEBSERVER_SERVER_H
#include "asio.hpp"
#include "Connection.h"

using asio::ip::tcp;

class server {
public:
    explicit server(const std::string& address,const std::string& port);
    void async_stop();          //异步接受信号停止
    asio::awaitable<void> do_accept();           //listener接受连接并分发连接
    void distribute(tcp::socket s);         //分发到达的连接
    void run();

private:
    asio::io_context listener;
    tcp::acceptor acceptor;
    tcp::socket socket;
    asio::signal_set signal;
    Connection connection;
};

#endif //WEBSERVER_SERVER_H
