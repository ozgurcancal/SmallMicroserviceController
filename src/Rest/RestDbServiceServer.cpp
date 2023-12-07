//
// Created by özgür yalçın on 19.11.2023.
//

#include "RestDbServiceServer.h"

RestDbServiceServer::RestDbServiceServer(utility::string_t url) : m_listener(url)
{
    m_listener.support(web::http::methods::GET, std::bind(&RestDbServiceServer::HandleGet,
                                               this, std::placeholders::_1));
    m_listener.support(web::http::methods::PUT, std::bind(&RestDbServiceServer::HandlePut,
                                               this, std::placeholders::_1));
    m_listener.support(web::http::methods::POST, std::bind(&RestDbServiceServer::HandlePost,
                                                this, std::placeholders::_1));
    m_listener.support(web::http::methods::DEL, std::bind(&RestDbServiceServer::HandleDelete,
                                               this, std::placeholders::_1));
}

RestDbServiceServer::~RestDbServiceServer()
{

}

//Lists all the key/value pairs in the storage. The response will be in the { key:value,key:value} format.
void RestDbServiceServer::HandleGet(web::http::http_request message)
{
    ucout<< " the message is: " << message.to_string();
    g_dbengine.GetHandler(message);
}

// Inserts a collection of key/value pairs into the storage.
// The request should be in the {key:value,key:value} format.
void RestDbServiceServer::HandlePut(web::http::http_request message)
{
    ucout<< " the message is: " << message.to_string();
    g_dbengine.PutHandler(message);
}
// Retrieves values corresponding to an array of keys. The request should be in the [key1,...,keyn] format.
// The response will be in the {key:value,key:value....} format.
void RestDbServiceServer::HandlePost(web::http::http_request message)
{
    ucout<< " the message is: " << message.to_string();
    g_dbengine.PostHandler(message);
}
// Deletes an array of keys and their corresponding values from the storage.
// The request should be in the [key,key] format.
void RestDbServiceServer::HandleDelete(web::http::http_request message)
{
    ucout<< " the message is: " << message.to_string();
    g_dbengine.DelHandler(message);
}
