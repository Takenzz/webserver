#ifndef WEBSERVER_REQUEST_H
#define WEBSERVER_REQUEST_H
#include <string>
#include <unordered_map>
class request {
public:
    std::string method;
    std::string URI;
    std::string http_version;
    std::string header_name;
    std::string header_value;
    std::unordered_map<std::string, std::string> header;
    std::string body;
    int body_num = 0;
};

#endif //WEBSERVER_REQUEST_H
