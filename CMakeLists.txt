cmake_minimum_required(VERSION 3.14)
project(cryptotest)

set(CMAKE_CXX_STANDARD 17)
INCLUDE_DIRECTORIES("F:\\cpp_libs\\cpp-taskflow-master\\taskflow")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
add_executable(cryptotest main.cpp Crypto.cpp CryptoString.cpp CryptoString.h CryptoFile.cpp CryptoFile.h)