#ifndef _BLOCK_PARSER_
#define _BLOCK_PARSER_
/*******************************************************************************
*                            block parser
*                       =====================
* File Name: block_parser.hpp
* Related files: block_parser.cpp block_parser_test.cpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 8.10.19
* Last update: 10.10.19
*******************************************************************************/

#include <string> // std::string
#include <fstream> // std::ifstream m_block_file
#include <vector>

#include "block_header.hpp"
#include "transaction.hpp"
#include "auxiliary.hpp"

namespace hrd9
{

class BlockParser
{
    public:
        BlockParser(const std::string& block_to_parse = "../block/sample_block_bin");
        ~BlockParser();

        BlockParser(BlockParser&) = delete;
        BlockParser& operator=(BlockParser&) = delete;
        BlockParser(BlockParser&&) = delete;
        BlockParser& operator=(BlockParser&&) = delete;

        //inteface
        // all is printed in little endian, by default only header is printed
        void print_binary_dump(int start_offset = 107,
                               size_t end_offset = 200); 
        void print_header_data();

        uint32_t get_transaction_count() const;
        size_t get_total_output_values() const;
        BlockHeader* get_header();
        std::vector<Transaction>& get_transactions();

    private:
        size_t read_varint();

        // write data from a file and disply it, 2 methods. 
        void write_data(std::string& data, size_t data_size = 4 /* bytes */);
        void print_byte_in_hexadecimal(std::string& data);

        std::ifstream m_block_file;

        // const variables
        static const size_t single_byte_size = sizeof(char);  

        // block header class
        BlockHeader* m_block_header;
        std::vector<Transaction> m_block_transactions;
};

} // namespace hrd9
#endif // _BLOCK_PARSER_
