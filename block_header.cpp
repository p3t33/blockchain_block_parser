/*******************************************************************************
*                            block header
*                       =====================
* File Name: block_header.cpp
* Related files: block_header.hpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: *.10.19
* Last update: 10.10.19
*******************************************************************************/


/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "./include/block_header.hpp"

/*============================================================================*/
namespace hrd9
{

/*============================================================================*/
/*                               Class BlockHeader                            */
/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                               special functions                            */
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                                                         Constructor / ctor */
/*                                                         ~~~~~~~~~~~~~~~~~~ */
BlockHeader::BlockHeader(std::ifstream &file)
{
    initialize_header(file);    
}

BlockHeader::BlockHeader():
                                                           m_version(0),
                                                           m_previous_block({}),
                                                           m_merkle_root({}),
                                                           m_bits(0),
                                                           m_nonce(0)
{
    
}

/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~                             */
/*                               member functions                             */
/*                               ~~~~~~~~~~~~~~~~                             */


/*============================================================================*/
/*                     API functions / Public member functions                */
/*============================================================================*/
/*                                                                get_version */
/*                                                                ~~~~~~~~~~~ */
int32_t BlockHeader::get_version() const
{
    return (m_version);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                         get_previous_block */
/*                                                         ~~~~~~~~~~~~~~~~~~ */
uint256_t BlockHeader::get_previous_block()
{
    return (m_previous_block);        
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                            get_merkle_root */
/*                                                            ~~~~~~~~~~~~~~~ */
uint256_t BlockHeader::get_merkle_root()
{
    return (m_merkle_root);    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                              get_timestamp */
/*                                                              ~~~~~~~~~~~~~ */
int32_t BlockHeader::get_timestamp() const
{
    return (m_timestamp);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                   get_bits */
/*                                                                   ~~~~~~~~ */
int32_t BlockHeader::get_bits() const
{
    return (m_bits);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  get_nonce */
/*                                                                  ~~~~~~~~~ */  
int32_t BlockHeader::get_nonce() const
{
    return(m_nonce);
}

/*============================================================================*/
/*                        Auxiliary / private member functions                */
/*============================================================================*/
/*                                                          initialize_header */
/*                                                          ~~~~~~~~~~~~~~~~~ */
void BlockHeader::initialize_header(std::ifstream &raw_data)
{
    // ff end of file was reached a flag will be set, it will prevent "seekg"
    // function from seting desired position. "clear" will unset
    // the flag.
    raw_data.clear();

    // Traverse to the beginning of the header.
    raw_data.seekg(27);

    raw_data.read((char*)(&(m_version)), 4);
    raw_data.read((char*)(m_previous_block.first_element()), 32);    
    raw_data.read((char*)(m_merkle_root.first_element()), 32);
    raw_data.read((char*)(&m_timestamp), 4);
    raw_data.read((char*)(&m_bits), 4);
    raw_data.read((char*)(&m_nonce), 4);
}

} // namespace hrd9
