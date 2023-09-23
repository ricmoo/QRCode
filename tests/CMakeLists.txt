cmake_minimum_required(VERSION 3.25)
project(qrcode)

add_executable(amd64test
        amd64_test.c
        ../src/qrcode.c
        ../src/qrcode.h
)
