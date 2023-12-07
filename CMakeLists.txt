cmake_minimum_required(VERSION 3.1)

project(SmallMicroserviceController)

SET(CMAKE_CXX_STANDARD 17)
SET(CPP_STANDARD_REQUIRED True)

# Set custom compiler flags
if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined -g -Wall -Werror -O2")

########
# Please make sure the following packages are installed and found otherwise gives fatal error
########
#add reactive programming features by using rxcpp library
find_package(rxcpp CONFIG REQUIRED)
find_package(Boost REQUIRED)
find_package(cpprestsdk REQUIRED)
find_package(Boost COMPONENTS system filesystem REQUIRED)

add_subdirectory(src)

