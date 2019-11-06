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


/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "./include/transaction.hpp"

/*============================================================================*/
namespace hrd9
{

/*============================================================================*/
/*                               Class Transaction                            */
/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                               special functions                            */
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                                                         Constructor / ctor */
/*                                                         ~~~~~~~~~~~~~~~~~~ */

Transaction::Transaction(std::ifstream& raw_data):
                                                       m_transaction_offset(),
                                                       m_version(0),
                                                       m_inputs_counter(0),
                                                       m_inputs(),
                                                       m_outputs_counter(0),
                                                       m_outputs(),
                                                       m_lockTime(0)
{
    parse_transaction(raw_data);    
}

/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~                             */
/*                               member functions                             */
/*                               ~~~~~~~~~~~~~~~~                             */

/*============================================================================*/
/*                     API functions / Public member functions                */
/*============================================================================*/
/*                                                          get_outputs_value */
/*                                                          ~~~~~~~~~~~~~~~~~ */
uint64_t Transaction::get_outputs_value() const
{
    uint64_t outputs_value = 0;
    
    for (const auto & single_output : m_outputs)
    {
        outputs_value += single_output.get_value();
    }
    
    return (outputs_value);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                           get_inputs_count */
/*                                                           ~~~~~~~~~~~~~~~~ */
uint32_t Transaction::get_inputs_count() const
{
    return (m_inputs.size());
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                          get_outputs_count */
/*                                                          ~~~~~~~~~~~~~~~~~ */
uint32_t Transaction::get_outputs_count() const
{
    return (m_outputs.size());
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                             get_all_inputs */
/*                                                             ~~~~~~~~~~~~~~ */
std::vector<TInput>& Transaction::get_all_inputs()
{
    return (m_inputs);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                            get_all_outputs */
/*                                                            ~~~~~~~~~~~~~~~ */
std::vector<TOutput>& Transaction::get_all_outputs()
{
    return (m_outputs);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                 get_offset */
/*                                                                 ~~~~~~~~~~ */
int* Transaction::get_offset()
{
    return(m_transaction_offset);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                          print_transaction */
/*                                                          ~~~~~~~~~~~~~~~~~ */
void Transaction::print_transaction()
{
    std::cout << std::endl;
    std::cout << "=========== Transaction information ===========" << std::endl;

    std::cout << "version: ";
    std::cout << std::hex << m_version << std::endl;

    std::cout << "input counter: ";
    std::cout << std::hex << m_inputs_counter << std::endl;
    m_inputs.data()->print_inputs();

    std::cout << "output counter: ";
    std::cout << std::hex << m_outputs_counter << std::endl;
    m_outputs.data()->print_outputs();

    std::cout << "lock time: ";
    std::cout << m_lockTime << "\n"; 

    std::cout << "===============================================" << std::endl;    
}
/*============================================================================*/
/*                            Auxiliary private functions                     */
/*============================================================================*/
/*                                                          parse_transaction */
/*                                                          ~~~~~~~~~~~~~~~~~ */
void Transaction::parse_transaction(std::ifstream& raw_data)
{
    m_transaction_offset[START] = raw_data.tellg();

    raw_data.read((char *)(&(m_version)), 4);
    m_inputs_counter = read_varint(raw_data);
    
    for (size_t i = 0; i < m_inputs_counter; ++i) 
    {
        m_inputs.push_back(TInput(raw_data));
    }

    m_outputs_counter = read_varint(raw_data);
    
    for (size_t i = 0; i < m_outputs_counter; ++i)
    {
        m_outputs.push_back(TOutput(raw_data));
    }
    
    raw_data.read((char *)(&(m_lockTime)), 4); 

    m_transaction_offset[END] = raw_data.tellg();
}

} // namespace hrd9
