#include "server.h"

server::server(const std::string &address, const std::string &port)
    :acceptor(listener),
     socket(listener),
     signal(listener) {
        signal.add(SIGTERM);
        signal.add(SIGINT); //添加SIGINT中断信号，SIGTERM终止信号
        async_stop();   //接受停止信号

        tcp::resolver resolver(listener);
        tcp::endpoint endpoint = *resolver.resolve(address,port).begin(); //解析得到地址和端口的endpoint,包含对应的网络信息
        acceptor.open(endpoint.protocol());    //以对应的协议打开accpetor
        acceptor.set_option(tcp::acceptor::reuse_address(true)); //设置地址复用，可连接绑定多个socket
        acceptor.bind(endpoint);    //与socket编程里面的bind类似
        acceptor.listen();  //监听连接
        asio::co_spawn(listener, do_accept(), asio::detached);//建立协程等待并处理连接

}

asio::awaitable<void> server::do_accept() {
    while(true) {
        tcp::socket s =co_await acceptor.async_accept(asio::use_awaitable);
        distribute(std::move(s));
    }
}

void server::distribute(tcp::socket s) {
    connection.connection_receive(std::move(s));
}

void server::async_stop() {
    signal.async_wait(
            [this](const asio::error_code &, int)
    {
        acceptor.close();
    });
}

void server::run() {
    listener.run();
}