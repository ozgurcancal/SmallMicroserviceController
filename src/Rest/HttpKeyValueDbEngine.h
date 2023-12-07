//
// Created by ozgur yalcin on 3.12.2023.
//

#ifndef HTTPKEYVALUEDBENGINE_H
#define HTTPKEYVALUEDBENGINE_H

#include "RestUtility.h"
#include "RestCommon.h"
#include <set>


// A Mock database Engine which Simulates a Key/Value DB
// In Real life, one should use an Industrial strength DB
class HttpKeyValueDbEngine {
    //Map , which we save,retrieve, update and delete data
    std::map<utility::string_t, utility::string_t> storage;

public:
    HttpKeyValueDbEngine();

    // GET - Just Iterates through the Map and Stores
    // the data in a JSon Object. IT is emitted to the response Stream
    void GetHandler(web::http::http_request& request);
    // POST - Retrieves a Set of Values from the DB
    // The PAyload should be in ["Key1" , "Key2"...,"Keyn"] format
    void  PostHandler(web::http::http_request& request);
    // PUT - Updates Data, If new KEy is found
    //       Otherwise, Inserts it
    // REST Payload should be in
    //      { Key1..Value1,...,Keyn,Valuen}  format
    void PutHandler(web::http::http_request& request);
    // DEL - Deletes a Set of Records
    // REST PayLoad should be in
    //      [ Key1,....,Keyn] format
    void DelHandler(web::http::http_request& request);
};

#endif //HTTPKEYVALUEDBENGINE_H
