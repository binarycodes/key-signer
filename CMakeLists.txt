cmake_minimum_required(VERSION 3.31)

set(C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 23)

project(KeySigner VERSION 1.0.0)
add_executable(key-signerd server.c logger.c)

add_executable(key-signer-client client.c logger.c)
