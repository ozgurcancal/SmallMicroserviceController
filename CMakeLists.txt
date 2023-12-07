cmake_minimum_required(VERSION 3.1)

project(SmallMicroserviceController)

if(NOT WIN32)
	string(ASCII 27 Esc)
	set(ColourReset "${Esc}[m")
	set(Magenta     "${Esc}[35m")
	set(BoldRed     "${Esc}[1;31m")
endif()

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

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
	message(FATAL_ERROR "
	${BoldRed}Error:${ColourReset} In-source builds are not allowed. You should create separate directory for build files.
    ${Magenta}CMAKE_BINARY_DIR${ColourReset}(${CMAKE_SOURCE_DIR}) must be different from ${Magenta}CMAKE_SOURCE_DIR${ColourReset}(${CMAKE_BINARY_DIR})")
endif ()

add_subdirectory(src)

