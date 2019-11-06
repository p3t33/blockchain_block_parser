/*******************************************************************************
*                       transection output
*                      =====================
* File Name: transection_output.hpp
* Related files: transection_output.cpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 9.10.19
* Last update: 10.10.19
*******************************************************************************/


/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "./include/transaction_output.hpp"

/*============================================================================*/
namespace hrd9
{

/*============================================================================*/
/*                                  Class TOutput                             */
/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                               special functions                            */
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                                                         Constructor / ctor */
/*                                                         ~~~~~~~~~~~~~~~~~~ */
TOutput::TOutput(std::ifstream& raw_data):
                                                             m_value(0),
                                                             m_script_length(0),
                                                             m_script()  
{
    parse_output(raw_data);
}

/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~                             */
/*                               member functions                             */
/*                               ~~~~~~~~~~~~~~~~                             */

/*============================================================================*/
/*                     API functions / Public member functions                */
/*============================================================================*/
/*                                                                  get_value */
/*                                                                  ~~~~~~~~~ */
uint64_t TOutput::get_value() const
{
    return(m_value);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                              print_outputs */
/*                                                              ~~~~~~~~~~~~~ */
void TOutput::print_outputs()
{
    std::cout << std::endl;
    std::cout << "-------------------- Outputs ------------------" << std::endl;

    std::cout << "m_value: ";
    std::cout << std::hex << m_value << std::endl;

    std::cout << "m_script_length: ";
    std::cout << std::hex << m_script_length << std::endl;

    std::cout << "m_script: ";
    print_m_script();

    std::cout << "-----------------------------------------------" << std::endl;
}

/*============================================================================*/
/*                            Auxiliary private functions                     */
/*============================================================================*/
/*                                                               parse_output */
/*                                                               ~~~~~~~~~~~~ */
void TOutput::parse_output(std::ifstream& raw_data)
{
    raw_data.read((char *)(&m_value), 8);
        
    m_script_length = read_varint(raw_data);
    
    for (size_t i = 0; i < m_script_length; i++)
    {
        uint8_t single_byte;
        raw_data.read((char *)(&single_byte), 1);    
        m_script.push_back(single_byte);
    }    
}   

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                             print_m_script */
/*                                                             ~~~~~~~~~~~~~~ */
void TOutput::print_m_script()
{
    for (const auto & script : m_script)
    {
        std::cout << std::hex << static_cast<int> (script);
    }

    std::cout << std::endl;
}

} // namespace hrd9
