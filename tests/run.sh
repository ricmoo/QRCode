#!/bin/bash

clang++ run-tests.cpp QrCode.cpp QrSegment.cpp BitBuffer.cpp ../src/qrcode.c -o test && ./test

