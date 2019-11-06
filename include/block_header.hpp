#ifndef _BLOCK_HEADER_
#define _BLOCK_HEADER_
/*******************************************************************************
*                            block header
*                       =====================
* File Name: block_header.hpp
* Related files: block_heade.cpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 9.10.19
* Last update: 10.10.19
*******************************************************************************/


#include <fstream> // std::ifstream
#include "binary_chunk.hpp"

namespace hrd9
{

class BlockHeader
{
    public:

    BlockHeader(std::ifstream &file);
    BlockHeader();

    BlockHeader(BlockHeader&) = delete;
    BlockHeader& operator=(BlockHeader&) = delete;
    BlockHeader(BlockHeader&&) = delete;
    BlockHeader& operator=(BlockHeader&&) = delete;

    //interface
    int32_t get_version() const;
    uint256_t get_previous_block();
    uint256_t get_merkle_root();
    int32_t get_timestamp() const;
    int32_t get_bits() const;
    int32_t get_nonce() const;

    private:
    // ctor auxiliary function
    void initialize_header(std::ifstream &raw_data);

    uint32_t m_version; // 4 bytes (little endian).
    uint256_t m_previous_block; // 32 bytes  (little endian).
    uint256_t m_merkle_root; // 32 bytes  (little endian).
    uint32_t m_timestamp; // 4 bytes (little endian).
    uint32_t m_bits; // proof-of-work related, 4 bytes.
    uint32_t m_nonce; // 4 bytes.
};

} // namespace hrd9
#endif // _BLOCK_PARSER_
