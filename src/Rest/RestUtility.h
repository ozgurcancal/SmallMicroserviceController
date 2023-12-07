//
// Created by özgür yalçın on 4.12.2023.
//

#ifndef C_TEXT_EDIT_RESTUTILITY_H
#define C_TEXT_EDIT_RESTUTILITY_H

#include "RestCommon.h"

class RestUtility {
public:
    // The following code dumps a json to the Console...
    static void  DisplayJSON(web::json::value const & jvalue);

// A Workhorse routine to perform an action on the request data type
// takes a lambda as parameter along with request type
// The Lambda should contain the action logic...whether it is PUT,POST or DELETE
    static void RequestWorker(
            web::http::http_request& request,std::function<void(web::json::value const &, web::json::value &)> handler);
};

#endif //C_TEXT_EDIT_RESTUTILITY_H
