#include "Connection.h"
#include <iostream>
#include <thread>

asio::awaitable<void>    Connection::connection_handle(tcp::socket socket) {
    try {
        char data[1024];
        std::string src = "C:\\webserver";
        request req;
        reply rep;
        request_parse request_parse;
        response response_parse(src);
        while (true) {
            std::size_t n = co_await socket.async_read_some(asio::buffer(data), asio::use_awaitable);
            auto state = request_parse.parse(req, data, data + n);
            if (state == request_parse::parse_ok) {
                response_parse.request_handle(req, rep);
                co_await asio::async_write(socket, rep.to_buffer(), asio::use_awaitable);
                if(req.header.count("connection") == 0) {
                    asio::error_code ignored_ec;
                    socket.shutdown(asio::ip::tcp::socket::shutdown_both, ignored_ec);
                    socket.close(ignored_ec);
                    co_return ;
                }
                rep.clear();
                continue;
            }
            if (state == request_parse::parse_indeterminate) {
                continue;
            }
            if (state == request_parse::parse_error) {
                co_await socket.async_write_some(asio::buffer("error"), asio::use_awaitable);
            }
        }
    }
    catch (std::exception& e){
        //std::printf("web Exception: %s\n", e.what());
        asio::error_code ignored_ec;
        socket.shutdown(asio::ip::tcp::socket::shutdown_both, ignored_ec);
        socket.close(ignored_ec);
    }
}

void    Connection::connection_receive(tcp::socket socket) {
    asio::co_spawn(io_pool.getIo(), connection_handle(std::move(socket)),asio::detached);
}


