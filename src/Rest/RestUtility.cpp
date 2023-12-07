//
// Created by özgür yalçın on 4.12.2023.
//

#include "RestUtility.h"

void RestUtility::DisplayJSON(const web::json::value &jvalue)
{
    ucout << jvalue.serialize();
}

void RestUtility::RequestWorker(web::http::http_request &request,
                                std::function<void(const web::json::value &, web::json::value &)> handler)
{
    auto result = web::json::value::object();

    request.extract_json().then([&result, &handler](pplx::task<web::json::value> task) {
        try{
            auto const & jvalue = task.get();
            if (!jvalue.is_null()) {
                handler(jvalue, result); // invoke the lambda
            }
        }
        catch (web::http::http_exception const & e) {
            std::wcout << L"Exception ->" << e.what() <<'\n';
        }
    }).wait();

    request.reply(web::http::status_codes::OK, result);
}
