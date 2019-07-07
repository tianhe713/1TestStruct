cmake_minimum_required(VERSION 3.14)
project(1TestStruct C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(1TestStruct
        itcast_asn1_der.c
        itcast_asn1_der.h
        itcastderlog.c
        itcastderlog.h
        test.c)
