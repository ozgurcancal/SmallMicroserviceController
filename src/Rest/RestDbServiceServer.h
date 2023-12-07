//
// Created by ozgur yalcin on 19.11.2023.
//

#ifndef RESTDBSERVICESERVER_H
#define RESTDBSERVICESERVER_H

//temporary
#include "HttpKeyValueDbEngine.h"

class RestDbServiceServer{
public:
    RestDbServiceServer(utility::string_t uri);
    ~RestDbServiceServer();
    //Manage asyncronous operations via parallel patterns library
    pplx::task<void> Open(){ return m_listener.open(); };
    pplx::task<void> Close(){ return m_listener.close(); };

private:
    // Handlers for HTTP verbs
    void HandleGet(web::http::http_request message);
    void HandlePut(web::http::http_request message);
    void HandlePost(web::http::http_request message);
    void HandleDelete(web::http::http_request message);
    // The  HTTP listener class
    web::http::experimental::listener::http_listener m_listener;
    // Instantiates an instance of mock database
    HttpKeyValueDbEngine g_dbengine;
};

#endif //RESTDBSERVICESERVER_H
