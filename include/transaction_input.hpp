#ifndef _TRANSACTION_INPUT_
#define _TRANSACTION_INPUT_
/*******************************************************************************
*                         transaction input
*                       =====================
* File Name: transaction_input.hpp
* Related files: transaction_input.cpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 9.10.19
* Last update: 10.10.19
*******************************************************************************/

#include <vector>
#include <stdint.h>
#include <fstream>

#include "binary_chunk.hpp" //uint256_t
#include "auxiliary.hpp"

namespace hrd9
{

class TInput
{
    public:
    TInput(std::ifstream& raw_data);

    // interface
    uint32_t get_tx_out_index() const;
    uint32_t get_sequence_number() const;
    uint256_t get_previous_transaction();
    void print_inputs();

    private:
    void parse_input(std::ifstream& raw_data); // ctor auxiliary function
    void print_m_scriptsig();

    uint256_t m_previous_transaction; // 32 bytes  (little endian).
    uint32_t m_tx_out_index; // 4 bytes (little endian).
    uint64_t m_script_length; // defined by varint
    uint32_t m_sequence_number; // 4 bytes
    
    std::vector<uint8_t> m_scriptsig;
};

}// namespace hrd9
#endif //_TRANSACTION_INPUT_