# webserver
###  基于ASIO的异步webserver(协程实现），施工中。
- 利用asio的Proactor模型完成对到来的连接的监听
- 利用协程来运行监听socket
- 对每个连接开启一个协程处理到达的数据
- 模仿One loop per thread实现不同的工作io_context运行在不同的线程上
- 采用RR的方式将到达的连接分配给不同的io_context
- 心跳包，时间堆控制连接，支持HTTP（未完成）
