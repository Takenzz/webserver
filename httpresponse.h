#ifndef WEBSERVER_HTTPRESPONSE_H
#define WEBSERVER_HTTPRESPONSE_H
#include "response.h"
#include "request.h"

class request;

class response {
public:
    response(std::string &src);
    void request_handle(request &req, reply &rep);
    void add_status(reply::status_code code, reply &rep);
    void add_header(reply &rep);
    void add_body(request &req, reply &rep);
    void error_reply(reply::status_code code, reply &rep);
    std::string find_dateType();

private:
    std::unordered_map<std::string,std::string> data_type{
            { "html",  "text/html" },
            { "xml",   "text/xml" },
            { "xhtml", "application/xhtml+xml" },
            { "txt",   "text/plain" },
            { "rtf",   "application/rtf" },
            { "pdf",   "application/pdf" },
            { "word",  "application/nsword" },
            { "png",   "image/png" },
            { "gif",   "image/gif" },
            { "jpg",   "image/jpeg" },
            { "jpeg",  "image/jpeg" },
            { "au",    "audio/basic" },
            { "mpeg",  "video/mpeg" },
            { "mpg",   "video/mpeg" },
            { "avi",   "video/x-msvideo" },
            { "gz",    "application/x-gzip" },
            { "tar",   "application/x-tar" },
            { "css",   "text/css "},
            { "js",    "text/javascript "},
    };


    const std::string srcDir;
    std::string path;
};





#endif //WEBSERVER_HTTPRESPONSE_H
