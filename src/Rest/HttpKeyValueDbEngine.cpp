//
// Created by ozgur yalcin on 3.12.2023.
//

#include "HttpKeyValueDbEngine.h"

using namespace web;
using namespace http;

HttpKeyValueDbEngine::HttpKeyValueDbEngine()
{
    // TO DO: Convert wide character strings to utility::string_t
    storage["Praseed"] = "45";
    storage["Peter"] = "28";
    storage["Andrei"] = "50";
}

void HttpKeyValueDbEngine::GetHandler(http_request &request)
{
    auto resp_obj = json::value::object();
    for (auto const & p : storage)
        resp_obj[p.first] = json::value::string(p.second);
    request.reply(status_codes::OK, resp_obj);
}

void HttpKeyValueDbEngine::PostHandler(http_request &request)
{
    RestUtility::RequestWorker(
            request,
            [&](json::value const & jvalue, json::value & result)
            {
                //---------- Write to the Console for Diagnostics
                RestUtility::DisplayJSON(jvalue);

                for (auto const & e : jvalue.as_array())
                {
                    if (e.is_string())
                    {
                        auto key = e.as_string();
                        auto pos = storage.find(key);

                        if (pos == storage.end())
                        {
                            //--- Indicate to the Client that Key is not found
                            result[key] = json::value::string("notfound");
                        }
                        else
                        {
                            //------------- store the key value pair in the result
                            //------------- json. The result will be send back to
                            //------------- the client
                            result[pos->first] = json::value::string(pos->second);
                        }
                    }
                }
            });


}

void HttpKeyValueDbEngine::PutHandler(http_request &request)
{
    RestUtility::RequestWorker(
            request,
            [&](json::value const & jvalue, json::value & result)
            {
                // DisplayJSON(jvalue);

                for (auto const & e : jvalue.as_object())
                {
                    if (e.second.is_string())
                    {

                        auto key = e.first;
                        auto value = e.second.as_string();

                        if (storage.find(key) == storage.end())
                        {
                            //--- Indicate to the client that we have
                            //--- created a new record
                            result[key] = json::value::string("<put>");
                        }
                        else
                        {
                            //--- Indicate to the client that we have
                            //--- updated a new record
                            result[key] = json::value::string("<updated>");
                        }

                        storage[key] = value;
                    }
                }
            });

}

void HttpKeyValueDbEngine::DelHandler(http_request &request)
{
    RestUtility::RequestWorker(
            request,
            [&](json::value const & jvalue, json::value & result)
            {
                //--------------- We aggregate all keys into this set
                //--------------- and delete in one go
                std::set<utility::string_t> keys;
                for (auto const & e : jvalue.as_array())
                {
                    if (e.is_string())
                    {
                        auto key = e.as_string();

                        auto pos = storage.find(key);
                        if (pos == storage.end())
                        {
                            result[key] = json::value::string("<failed>");
                        }
                        else
                        {
                            result[key] = json::value::string("<deleted>");
                            //---------- Insert in to the delete list
                            keys.insert(key);
                        }
                    }
                }
                //---------------Erase all
                for (auto const & key : keys)
                    storage.erase(key);
            });
}