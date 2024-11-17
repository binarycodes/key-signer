cmake_minimum_required(VERSION 3.31)

set(C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 23)

project(KeySigner VERSION 1.0.0)

add_library(KeySignerCommonLibs SHARED)
target_sources(KeySignerCommonLibs PRIVATE logger.c common.c)

add_executable(key-signerd server.c)
add_dependencies(key-signerd KeySignerCommonLibs)
target_link_libraries(key-signerd PUBLIC KeySignerCommonLibs)

add_executable(key-signer-client client.c)
add_dependencies(key-signer-client KeySignerCommonLibs)
target_link_libraries(key-signer-client PUBLIC KeySignerCommonLibs)
