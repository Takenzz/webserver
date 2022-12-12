#include "response.h"
#include <iostream>

std::vector<asio::const_buffer> reply::to_buffer() {
    std::vector<asio::const_buffer> buffers;
    std::string head_line;
    switch (code) {
        case 200 :
            buffers.push_back(asio::buffer(status_200));
            break;
        case 400 :
            buffers.push_back(asio::buffer(status_400));
            break;
        case 404 :
            buffers.push_back(asio::buffer(status_404));
            break;
    }
    for(auto &it:header) {
        buffers.push_back(asio::buffer(it.name));
        buffers.push_back(asio::buffer(name_value_separator));
        buffers.push_back(asio::buffer(it.value));
        buffers.push_back(asio::buffer(crlf));
    }
    buffers.push_back(asio::buffer(crlf));
    buffers.push_back(asio::buffer(body));
    return buffers;
}