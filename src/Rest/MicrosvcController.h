//
// Created by özgür yalçın on 3.12.2023.
//

#ifndef C_TEXT_EDIT_MICROSERVICECONTROLLER_H
#define C_TEXT_EDIT_MICROSERVICECONTROLLER_H

#include "RestDbServiceServer.h"
#include "cpprest/uri.h"

using namespace utility;

class MicrosvcController {

public:
    void StartServer(const string_t& address)
    {
        web::uri_builder uri(address);
        uri.append_path(U("DBDEMO/"));

        auto addr = uri.to_uri().to_string();
        g_http = std::unique_ptr<RestDbServiceServer>(new RestDbServiceServer(addr));
        g_http->Open().wait();
        ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;

        return;
    }

    void ShutDown()
    {
        g_http->Close().wait();
        return;
    }

private:
    std::unique_ptr<RestDbServiceServer> g_http;
};


#endif //C_TEXT_EDIT_MICROSERVICECONTROLLER_H
