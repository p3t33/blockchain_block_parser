#!/bin/bash
g++ -std=c++11 -pedantic-errors -Wall -Wextra -g -o block_parser_test.out \
block_parser_test.cpp \
../block_parser.cpp \
../block_header.cpp \
../auxiliary.cpp \
../transaction_input.cpp \
../transaction_output.cpp \
../transaction.cpp
