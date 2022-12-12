#include <iostream>
#include "httprequest.h"

request_parse::parse_state request_parse::parse(request &req, char *start, char *end) {
    char *ch = start;
    parse_state res = parse_state::parse_indeterminate;
    while(ch!=end) {
        switch (status) {
            case parse_part::start:
                if(*ch <='Z' && *ch >= 'A') {
                    req.method.push_back(*ch);
                    ch++;
                    status = parse_part::method;
                }
                else{
                    return parse_state::parse_error;
                }
                break;
            case parse_part::method :
                if(*ch <='Z' && *ch >= 'A') {
                    req.method.push_back(*ch);
                    ch++;
                }
                else if(*ch == ' '){
                    status = parse_part::uri;
                    ch++;
                }
                break;
            case parse_part::uri :
                if(*ch == ' ') {
                    status = parse_part::version_H;
                    ch++;
                } else {
                    req.URI.push_back(*ch);
                    ch++;
                }
                break;
            case parse_part::version_H :
                if(*ch != 'H') {
                    return parse_state::parse_error;
                }
                req.http_version.push_back(*ch);
                ch++;
                status = parse_part::version_T;
                break;
            case parse_part::version_T :
                if(*ch != 'T') {
                    return parse_state::parse_error;
                }
                req.http_version.push_back(*ch);
                ch++;
                status = parse_part::version_T2;
                break;
            case parse_part::version_T2 :
                if(*ch != 'T') {
                    return parse_state::parse_error;
                }
                req.http_version.push_back(*ch);
                ch++;
                status = parse_part::version_P;
                break;
            case parse_part::version_P :
                if(*ch != 'P') {
                    return parse_state::parse_error;
                }
                req.http_version.push_back(*ch);
                ch++;
                status = parse_part::version_slash;
                break;
            case parse_part::version_slash :
                if(*ch != '/') {
                    return parse_state::parse_error;
                }
                req.http_version.push_back(*ch);
                ch++;
                status = parse_part::version_number;
                break;
            case parse_part::version_number :
                if((*ch <= '9' && *ch >='0') || *ch == '.') {
                    req.http_version.push_back(*ch);
                    ch++;
                    status = parse_part::version_number;
                } else if(*ch == '\r') {
                    status = parse_part::newline;
                    ch++;
                }
                break;
            case parse_part::header_name :
                if(*ch == ':') {
                    status = parse_part::header_value;
                    ch++;
                } else if(*ch =='\r') {
                    status = parse_part::newline2;
                    ch++;
                }
                else {
                    req.header_name.push_back(tolower(*ch));
                    ch++;
                }
                break;
            case parse_part::header_value :
                if(*ch == '\r') {
                    status = parse_part::newline;
                    ch++;
                    req.header[req.header_name] = req.header_value;
                    req.header_name.erase(req.header_name.begin(),req.header_name.end());
                    req.header_value.erase(req.header_value.begin(),req.header_value.end());
                } else if(*ch == ' ') {
                    status = parse_part::header_value;
                    ch++;
                } else {
                    req.header_value.push_back(*ch);
                    ch++;
                }
                break;
            case parse_part::body_ready :
                if(req.header.count("content-length") == 0) {
                    ch++;
                    return parse_state::parse_ok;
                } else if(*ch == '\r' || *ch == '\n'){
                    ch++;
                    status = parse_part::body_ready;
                } else {
                    status = parse_part::body;
                }
                break;
            case parse_part::body :
                req.body_num++;
                req.body.push_back(*ch);
                ch++;
                if(req.body_num == std::stoi(req.header["content-length"]) - 1) {
                    return parse_state::parse_ok;
                }
                break;
            case parse_part::newline :
                if(*ch == '\r') {
                    status = parse_part::newline;
                    ch++;
                } else if(*ch == '\n') {
                    status = parse_part::header_name;
                    ch++;
                } else {
                    return parse_error;
                }
                break;
            case parse_part::newline2 :
                if(*ch == '\n') {
                    status = parse_part::body_ready;
                } else {
                    return parse_error;
                }
                break;
        }
    }
    return res;
}