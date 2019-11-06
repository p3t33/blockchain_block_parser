/*******************************************************************************
*                         transection input
*                       =====================
* File Name: transection_input.hpp
* Related files: transection_input.cpp
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
#include "./include/transaction_input.hpp"

/*============================================================================*/
namespace hrd9
{

/*============================================================================*/
/*                                 Class TInput                               */
/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                               special functions                            */
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                                                         Constructor / ctor */
/*                                                         ~~~~~~~~~~~~~~~~~~ */
TInput::TInput(std::ifstream& raw_data):
                                                     m_previous_transaction({}),
                                                     m_tx_out_index(0),
                                                     m_script_length(0),
                                                     m_sequence_number(0),
                                                     m_scriptsig()
{ 
    parse_input(raw_data);
}

/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~                             */
/*                               member functions                             */
/*                               ~~~~~~~~~~~~~~~~                             */


/*============================================================================*/
/*                     API functions / Public member functions                */
/*============================================================================*/
/*                                                           get_tx_out_index */
/*                                                           ~~~~~~~~~~~~~~~~ */
uint32_t TInput::get_tx_out_index() const
{
    return (m_tx_out_index);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                        get_sequence_number */
/*                                                        ~~~~~~~~~~~~~~~~~~~ */
uint32_t TInput::get_sequence_number() const
{
    return (m_sequence_number);
}
 
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                   get_previous_transaction */
/*                                                   ~~~~~~~~~~~~~~~~~~~~~~~~ */
uint256_t TInput::get_previous_transaction()
{
    return (m_previous_transaction);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                               print_inputs */
/*                                                               ~~~~~~~~~~~~ */
void TInput::print_inputs()
{
    std::cout << std::endl;
    std::cout << "------------------- Inputs --------------------" << std::endl;

    std::cout << "m_previous_transaction: ";
    std::cout << m_previous_transaction.get_hex_string() << std::endl;

    std::cout << "m_tx_out_index: ";
    std::cout << std::hex << m_tx_out_index << std::endl;

    std::cout << "m_script_length: ";
    std::cout << std::hex << m_script_length << std::endl;

    std::cout << "m_scriptsig: ";
    print_m_scriptsig();

    std::cout << "m_sequence_number: ";
    std::cout << std::hex << m_sequence_number << std::endl;

    std::cout << "-----------------------------------------------" << std::endl;
}

/*============================================================================*/
/*                            Auxiliary private functions                     */
/*============================================================================*/
/*                                                                parse_input */
/*                                                                ~~~~~~~~~~~ */
void TInput::parse_input(std::ifstream& raw_data)
{
    raw_data.read((char *)m_previous_transaction.first_element(), 32);
    raw_data.read((char *)(&m_tx_out_index), 4);    
    m_script_length = read_varint(raw_data);
    
    for (size_t i = 0; i < m_script_length; ++i)
    {
        uint8_t single_byte;
        raw_data.read((char *)(&single_byte), 1);
        m_scriptsig.push_back(single_byte);
    }
    
    raw_data.read((char *)(&m_sequence_number), 4); 
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                          print_m_scriptsig */
/*                                                          ~~~~~~~~~~~~~~~~~ */
void TInput::print_m_scriptsig()
{
    for (const auto & script : m_scriptsig)
    {
        std::cout << std::hex << static_cast<int> (script);
    }

    std::cout << std::endl;
}
} // namespace hrd9
