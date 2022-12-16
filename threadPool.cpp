#include "threadPool.h"


threadPool::threadPool(int num) :io(num), work(num) {
    for(int i = 0; i < num; i++) {
        work[i] = std::make_shared<Work>(io[i].get_executor());
    }
    for(int i = 0; i < num; i++) {
        thread.emplace_back(std::thread([this,i](){ io[i].run();}));
    }
}

threadPool::~threadPool() {
    for(auto &i : work) {
        i->reset();
    }
    for(auto &i:thread) {
        i.join();
    }
}

asio::io_context &threadPool::getIo() {
    auto &res = io[k++];
    if(k == io.size()) k = 0;
    return  res;
}
