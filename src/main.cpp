
#include "Rest/MicrosvcController.h"
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

int main() {

    utility::string_t port = U("34567");
    utility::string_t address = U("http://localhost:");
    address.append(port);

    MicrosvcController Server;
    Server.StartServer(address);
    std::cout << "Press ENTER to exit." << std::endl;

    std::string line;
    std::getline(std::cin, line);

    Server.ShutDown();
    return 0;


}
