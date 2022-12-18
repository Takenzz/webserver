#include <unordered_map>
#include <string>
#include "asio.hpp"
#include <vector>

class reply {
public:
    std::unordered_map<int, std::string> response_status{
            {200, "OK"},
            {404, "Not Found"},
            {400, "Bad Request"}
    };

    enum status_code {
        ok = 200,
        NotFound = 404,
        BadRequest = 400,
    } code ;

    struct head{
        std::string name;
        std::string value;
    } ;

    std::vector<char> name_value_separator = { ':', ' ' };
    std::vector<char> crlf = { '\r', '\n' };

    const std::string status_200 = "HTTP/1.0 200 OK\r\n";
    const std::string status_400 = "HTTP/1.0 400 Bad Request\r\n";
    const std::string status_404 = "HTTP/1.0 404 Not Found\r\n";


    bool isKeepAlive = true;
    std::string status;
    std::vector<head> header;
    std::string http_version = "HTTP/1.1";
    std::string body;

    std::vector<asio::const_buffer> to_buffer();
    void clear(){
        status.clear();
        header.clear();
        body.clear();
        code = status_code::ok;
        isKeepAlive = true;
    }

};
