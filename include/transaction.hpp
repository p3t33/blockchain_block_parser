#ifndef _TRANSACTION_
#define _TRANSACTION_
/*******************************************************************************
*                            transaction
*                       =====================
* File Name: transaction.hpp
* Related files: transaction.cpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 9.10.19
* Last update: 10.10.19
*******************************************************************************/
#include <vector>

#include "auxiliary.hpp"
#include "transaction_output.hpp"
#include "transaction_input.hpp"

namespace hrd9
{

class Transaction
{
    enum Position {START, END};

    public:
    Transaction(std::ifstream& raw_data);
    
    // interface
    uint64_t get_outputs_value() const;
    uint32_t get_inputs_count() const;
    uint32_t get_outputs_count() const;
    std::vector<TInput>& get_all_inputs();
    std::vector<TOutput>& get_all_outputs();
    int* get_offset();
    void print_transaction();

    private:
    void parse_transaction(std::ifstream& raw_data); // ctor auxiliary function
    int m_transaction_offset[2]; 

    uint32_t m_version;
    uint64_t m_inputs_counter; // varint
    std::vector<TInput> m_inputs;

    uint64_t m_outputs_counter; // varint 
    std::vector<TOutput> m_outputs;
    uint32_t m_lockTime;
};

} // namespace hrd9
#endif //_TRANSACTION_