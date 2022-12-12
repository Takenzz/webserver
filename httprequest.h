#ifndef WEBSERVER_HTTPREQUEST_H
#define WEBSERVER_HTTPREQUEST_H
#include "request.h"
#include <string>

class request_parse {
public:
    enum parse_state{parse_ok, parse_error, parse_indeterminate};

    request_parse() : status(parse_part::start){}

    parse_state parse(request &req,char *start,char *end);

private:
    enum parse_part{
        start,
        method,
        uri,
        version_H,
        version_T,
        version_T2,
        version_P,
        version_slash,
        version_number,
        newline,
        header_name,
        header_value,
        newline2,
        body,
        body_ready,
    } status;

};


#endif //WEBSERVER_HTTPREQUEST_H
