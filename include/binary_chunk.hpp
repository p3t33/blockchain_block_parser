#ifndef _BINARY_CHUNK_
#define _BINARY_CHUNK_
/*******************************************************************************
*                            binary chunk - used as uint256_t
*                       =====================
* File Name: block_parser.hpp
* Related files: block_parser.cpp block_parser_test.cpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 9.10.19
* Last update: 10.10.19
*******************************************************************************/


/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
#include <stdint.h> // uint32_t
#include <iostream> // size_t

/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "auxiliary.hpp"

/*============================================================================*/
namespace hrd9
{

template <unsigned int BYTES_NUMBER>
class Chunk
{
    public:
    Chunk();
    Chunk(Chunk<BYTES_NUMBER>& other);
    Chunk(Chunk<BYTES_NUMBER>&& other);


    size_t get_size_of_chunk();
    uint8_t& operator[](uint32_t byte_number);
    Chunk& operator<<(uint8_t byte);
    
    // pointer to the start of first element of the raw data
    uint8_t* first_element(); 
    
    std::string get_hex_string() const;
    
    private:
    uint8_t m_raw_data[BYTES_NUMBER];
};

/*============================================================================*/
/*                                  Class Chunk                               */
/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                               special functions                            */
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                                                         Constructor / ctor */
/*                                                         ~~~~~~~~~~~~~~~~~~ */
template <unsigned int BYTES_NUMBER>
Chunk<BYTES_NUMBER>::Chunk()
{
    for (size_t i = 0; i < BYTES_NUMBER; ++i)
    {
        m_raw_data[i] = 0;
    }
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                   Copy Constructor / cctor */
/*                                                   ~~~~~~~~~~~~~~~~~~~~~~~~ */
template <unsigned int BYTES_NUMBER>
Chunk<BYTES_NUMBER>::Chunk(Chunk<BYTES_NUMBER>& other)
{
    for (size_t i = 0; i < BYTES_NUMBER; ++i)
    {
        m_raw_data[i] = other.m_raw_data[i];
    }
} 

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                           move Constructor */
/*                                                           ~~~~~~~~~~~~~~~~ */
template <unsigned int BYTES_NUMBER>
Chunk<BYTES_NUMBER>::Chunk(Chunk<BYTES_NUMBER>&& other)
{
    for (size_t i = 0; i < BYTES_NUMBER; ++i)
    {
        m_raw_data[i] = other.m_raw_data[i];
    }
} 
                                                                    
/*============================================================================*/
/*                     API functions / Public member functions                */
/*============================================================================*/
/*                                                          get_size_of_chunk */
/*                                                          ~~~~~~~~~~~~~~~~~ */
template <unsigned int BYTES_NUMBER>
size_t Chunk<BYTES_NUMBER>::get_size_of_chunk()
{
    return (BYTES_NUMBER);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                 operator[] */
/*                                                                 ~~~~~~~~~~ */
template <unsigned int BYTES_NUMBER>
uint8_t& Chunk<BYTES_NUMBER>::operator[](uint32_t byte_number)
{
    return (m_raw_data[byte_number]);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                 operator<< */
/*                                                                 ~~~~~~~~~~ */
template <unsigned int BYTES_NUMBER>
Chunk<BYTES_NUMBER>& Chunk<BYTES_NUMBER>::operator<<(uint8_t byte)
{
    for (size_t i = 1; i < BYTES_NUMBER; i++)
    {
        m_raw_data[i - 1] = m_raw_data[i];
    }
    
    m_raw_data[BYTES_NUMBER - 1] = byte;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                      first */
/*                                                                      ~~~~~ */
template <unsigned int BYTES_NUMBER>
uint8_t* Chunk<BYTES_NUMBER>::first_element()
{
    return (m_raw_data);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                             get_hex_string */
/*                                                             ~~~~~~~~~~~~~~ */
template <unsigned int BYTES_NUMBER>    
std::string Chunk<BYTES_NUMBER>::get_hex_string() const
{
    std::string string;
    for (uint32_t i = 0; i < BYTES_NUMBER; i++)
    {
        string += uint8_to_hexadecimal_top(m_raw_data[i]);
        string += uint8_to_hexadecimal_bot(m_raw_data[i]);
    }
    
    return string;    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                   definition of costum size raw data types                 */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
using uint256_t  = Chunk<32>;

}// namespace hrd9
#endif //_BINARY_CHUNK_