#include "httpresponse.h"
#include <fstream>
#include <sstream>
#include <iostream>

response::response(std::string &src) :srcDir(src) {

}

void response::add_status(reply::status_code code, reply &rep) {
    rep.code = code;
    rep.status = rep.response_status[code];
}

void response::add_header(reply &rep) {
    if(rep.isKeepAlive) {
        reply::head h;
        h.name = "Connection";
        h.value = "keep-alive";
        rep.header.push_back(h);
    } else {
        reply::head h;
        h.name = "Connection";
        h.value = "close";
        rep.header.push_back(h);
    }
    reply::head h;
    h.name = "Content-Length";
    h.value = std::to_string(rep.body.size());
    rep.header.push_back(h);
}

void response::add_body(request &req, reply &rep) {
    std::string fullPath =  srcDir + req.URI;

    if(req.URI.empty()) {
        error_reply(rep.BadRequest,rep);
        return;
    }
    if(req.URI[req.URI.size() - 1] == '/') {
        req.URI += "index.html";
    }
    std::fstream is(fullPath.c_str(),std::ios::in | std::ios::binary);
    if(!is) {
        error_reply(rep.NotFound,rep);
        return;
    }
    path = fullPath;
    add_status(reply::status_code::ok, rep);
    char buf[512];
    while(is.read(buf,sizeof(buf)).gcount() > 0) {
        rep.body.append(buf,is.gcount());
    }
    std::string type = find_dateType();
    reply::head h;
    h.name = "Content-Type";
    h.value = type;
    rep.header.push_back(h);
}

void response::request_handle(request &req, reply &rep) {
    add_body(req, rep);
    add_header(rep);
}

void response::error_reply(reply::status_code code, reply &rep) {
    std::string  body;
    body += "<html><title>Error</title>";
    body += "<body bgcolor=\"ffffff\">";
    add_status(code,rep);
    body += std::to_string(code) + " : " + rep.status + "\n";
    body += "<hr><em>TakenzzWebServer</em></body></html>";
    rep.body = body;
    reply::head h;
    h.name = "Content-Length";
    h.value =  std::to_string(rep.body.size());
    rep.header.push_back(h);
}

std::string response::find_dateType() {
    size_t lastPoint = path.find_last_of('.');
    if(lastPoint == std::string::npos) {
        return "text/plain";
    }
    std::string type = path.substr(lastPoint+1);
    if(data_type.count(type) == 1) {
        return data_type[type];
    }
    return "text/plain";
}