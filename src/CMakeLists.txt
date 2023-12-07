
# the only target is affected by target_include_directories command is the target denoted by the first argument.
# For process two targets you need to call target_include_directories twice
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CPPRESTSDK_INCLUDE_DIRS})

set(ASIO_INCLUDE_DIR /Users/ozguryalcin/Documents/projects/sdk/asio/include)

#INTERFACE used when group a set of properties that multiple targets can share
#like compile options, include directories, or other properties that multiple targets in your project need to share
add_library(asio INTERFACE)
# Now, targets can link to the interface library to inherit its properties
target_include_directories(asio INTERFACE ${ASIO_INCLUDE_DIR})
# Link against the system's threading library
find_package(Threads REQUIRED)

set(HEADER ${HEADER}
        ${PROJECT_SOURCE_DIR}/src/Rest/MicrosvcController.h
        ${PROJECT_SOURCE_DIR}/src/Rest/HttpKeyValueDbEngine.h
        ${PROJECT_SOURCE_DIR}/src/Rest/RestCommon.h
        ${PROJECT_SOURCE_DIR}/src/Rest/RestUtility.h
        ${PROJECT_SOURCE_DIR}/src/Rest/RestDbServiceServer.h
)
set(SOURCE ${SOURCE}
        ${PROJECT_SOURCE_DIR}/src/main.cpp
        ${PROJECT_SOURCE_DIR}/src/Rest/MicrosvcController.cpp
        ${PROJECT_SOURCE_DIR}/src/Rest/HttpKeyValueDbEngine.cpp
        ${PROJECT_SOURCE_DIR}/src/Rest/RestUtility.cpp
        ${PROJECT_SOURCE_DIR}/src/Rest/RestDbServiceServer.cpp
)

#do not confuse target name with the project name:
#a target is the one created with add_executable, add_library or add_custom_target.
add_executable(${PROJECT_NAME}
        ${HEADER}
        ${SOURCE}
)

# place target_link_libraries after the add_executable and find_package lines,
# so all linked components are known.
target_link_libraries(asio INTERFACE pthread)
#Link the interface library(asio) to just specified executable target
#Specify the dependency as PRIVATE or none for all of the project !! Otherwise you will receive an error
target_link_libraries(${PROJECT_NAME} PRIVATE asio)
#On linux CMake figures itself that boost_filesystem is linked against boost_system.
#But you have to tell it explicitly on Mac:
if(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
            ${Boost_FILESYSTEM_LIBRARY}
            ${Boost_SYSTEM_LIBRARY}
    )
endif ()
# Link against cpprestsdk libraries
target_link_libraries(${PROJECT_NAME} PRIVATE cpprestsdk::cpprest)
