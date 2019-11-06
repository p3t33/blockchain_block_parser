#ifndef _TRANSACTION_OUTPUT_
#define _TRANSACTION_OUTPUT_
/*******************************************************************************
*                       transaction output
*                      =====================
* File Name: transaction_output.hpp
* Related files: transaction_output.cpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 9.10.19
* Last update: 10.10.19
*******************************************************************************/


#include <vector>
#include "auxiliary.hpp"

namespace hrd9
{

class TOutput
{
    public:
    TOutput(std::ifstream& raw_data);

    // interface
    uint64_t get_value() const;
    void print_outputs();
    
    private:
    void parse_output(std::ifstream& raw_data); // ctor auxiliary function
    void print_m_script();

    uint64_t m_value; // 8 bytes (little endian).
    uint64_t m_script_length;
    std::vector<uint8_t> m_script;
};

} // namespace hrd9
#endif // _TRANSACTION_OUTPUT_