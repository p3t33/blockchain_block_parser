/*******************************************************************************
*                            auxiliary
*                       =====================
* File Name: auxiliary.cpp
* Related files: auxiliary.hpp 
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 9.10.19
* Last update: 10.10.19
*******************************************************************************/


#include "./include/auxiliary.hpp"

char hexadecimal_table[] = {'0', '1', '2', '3',
                            '4', '5', '6', '7',
                            '8', '9', 'a', 'b',
                            'c', 'd', 'e', 'f'};

uint64_t read_varint(std::istream &raw_dat)
{
    uint8_t num_of_bytes_to_read = 0;
    uint64_t number = 0;
    
    raw_dat.read((char *)(&num_of_bytes_to_read), 1 /* bytes */);

    switch (num_of_bytes_to_read)
    {
        case 0xFD:
        {
            raw_dat.read((char *)(&number), 2 /* bytes */);
            break;    
        }

        case 0xFE:
        {
            raw_dat.read((char *)(&number), 4 /* bytes */);
            break;
        }
            
        case 0xFF:
        {
            raw_dat.read((char *)(&number), 8 /* bytes */);
            break;
        }

        default:
        {
            number = num_of_bytes_to_read;
            break;
        }
    }
    
    return (number);
}


char uint8_to_hexadecimal_bot(uint8_t hex)
{
    return hexadecimal_table[hex & BOT_4];
}

char uint8_to_hexadecimal_top(uint8_t hex)
{
    return hexadecimal_table[(hex & TOP_4) >> 4];
}
