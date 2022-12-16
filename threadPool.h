#include <thread>
#include <vector>
#include "asio.hpp"

class threadPool {
    using Work = asio::executor_work_guard<asio::any_io_executor>;
    using Work_ptr = std::shared_ptr<Work>;
public:
    threadPool(int num = 2 * std::thread::hardware_concurrency());
    ~threadPool();
    asio::io_context& getIo();

private:
    std::vector<asio::io_context> io;
    std::vector<Work_ptr> work;
    std::vector<std::thread> thread;
    int k = 0; //轮询
};