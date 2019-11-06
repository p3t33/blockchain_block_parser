# Blockchain Database Parser
This is an implementation of a fully working BitcoinCash block parser, after
parsing is done all transactions are stored in a database.

parser is suitable for any blocks based on Bitcoin protocol with small
modifications.

This is a beta version and I may add some extra features in the future.

### Getting Started
1. clone the project by typing in the command line:
  ```
  git clone https://github.com/p3t33/blockchain_block_parser.git
  ```
2. A row BitcoinCash block is located in ./block 

### Compiling and running the tests
1. Unit test is available for parser.cpp, navigate to ./unit_testing folder and
   run the following script(to compile a binary):
```
./compile_test_files.sh
```
Then run:
```
./block_parser_test.out
```

### Compilers and operating systems
code was compiled with GNU g++ using std=c++11. It was tested on ubuntu 18.04 LTS.
code was tested for memory leaks via valgrind 3.13.0

### Authors

**Kobi Medrish** - *beta version* - [p3t33](https://github.com/p3t33)