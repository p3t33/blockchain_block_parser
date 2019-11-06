/*******************************************************************************
*                            block parser
*                       =====================
* File Name: block_parser.cpp
* Related files: block_parser.hpp block_parser_test.hpp block_header.cpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 8.10.19
* Last update: 10.10.19
*******************************************************************************/


/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
#include <iostream> // cout
#include <stdio.h> // printf

/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "./include/block_parser.hpp"
#include "./include/block_header.hpp"

/*============================================================================*/
namespace hrd9
{

/*============================================================================*/
/*                               Class BlockParser                            */
/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                               special functions                            */
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                                                         Constructor / ctor */
/*                                                         ~~~~~~~~~~~~~~~~~~ */
BlockParser::BlockParser(const std::string& block_to_parse):
                                                         m_block_file(),
                                                         m_block_header(nullptr)
{
    m_block_file.open(block_to_parse, std::ios::binary);

    // parse block for header information
    m_block_header = new BlockHeader(m_block_file);

    // parse block for transections 
    while (m_block_file)
    {
        m_block_transactions.push_back(Transaction(m_block_file));
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                          Destructor / dtor */
/*                                                          ~~~~~~~~~~~~~~~~~ */
BlockParser::~BlockParser()
{
    m_block_file.close();
    delete m_block_header;
}

/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~                             */
/*                               member functions                             */
/*                               ~~~~~~~~~~~~~~~~                             */
/*                                                          print_binary_dump */
/*                                                          ~~~~~~~~~~~~~~~~~ */
void BlockParser::print_binary_dump(int start_offset, size_t end_offset)
{
    // if end of file was reached a flag will be set, it will prevent "seekg"
    // function from seting to the beginning of the file. "clear" will unset
    // the flag.
    m_block_file.clear();
    // Go to the beginning of the file.
    m_block_file.seekg(0, std::ios_base::beg); 

    // 27 bytes of "network"
    // 80 bytes of header
    // coinbase transection starts at byte number 108

    m_block_file.seekg(start_offset);

    for (size_t i = 0; i < end_offset; ++i)
    {
        char byte;
        m_block_file.read(&byte, single_byte_size);

        printf("%02hhx", byte);
    }

    std::cout << std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                          print_header_data */
/*                                                          ~~~~~~~~~~~~~~~~~ */
void BlockParser::print_header_data()
{
    std::cout << std::endl;
    std::cout << "============= BitcoinCash Header ==============" << std::endl;

    std::cout << "version: ";
    std::cout << std::hex << m_block_header->get_version() << std::endl;

    std::cout << "previous_block: ";
    std::cout << m_block_header->get_previous_block().get_hex_string() << "\n"; 

    std::cout << "merkle_root: ";
    std::cout << m_block_header->get_merkle_root().get_hex_string() << "\n"; 


    std::cout << "timestamp: ";
    std::cout << std::hex << m_block_header->get_timestamp() << std::endl;
    std::cout << "bits: ";

    std::cout << std::hex << m_block_header->get_bits() << std::endl;;
    std::cout << "nonce: ";
    std::cout << std::hex << m_block_header->get_nonce() << std::endl;

    std::cout << "===============================================" << std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                      get_transaction_count */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
uint32_t BlockParser::get_transaction_count() const
{
    return (m_block_transactions.size());
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                    get_total_output_values */
/*                                                    ~~~~~~~~~~~~~~~~~~~~~~~ */
size_t BlockParser::get_total_output_values() const
{
    size_t size_of_all_transections_in_block = 0;
    
    for (const auto& tx : m_block_transactions)
    {
        size_of_all_transections_in_block += tx.get_outputs_value();
    }
    
    return size_of_all_transections_in_block;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                 get_header */
/*                                                                 ~~~~~~~~~~ */
BlockHeader* BlockParser::get_header()
{
    return (m_block_header);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                           get_transactions */
/*                                                           ~~~~~~~~~~~~~~~~ */
std::vector<Transaction>& BlockParser::get_transactions()
{
    return (m_block_transactions);
}

} // namespace hrd9
