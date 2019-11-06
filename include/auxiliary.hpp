#ifndef _AUXILIARY_
#define _AUXILIARY_
/*******************************************************************************
*                            auxiliary
*                       =====================
* File Name: auxiliary.hpp
* Related files: auxiliary.cpp 
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 9.10.19
* Last update: 9.10.19
*******************************************************************************/


#include <stdint.h>
#include <fstream>
#include <iostream>

#define TOP_4 0xF0
#define BOT_4 0x0F

extern char hexadecimal_table[];

uint64_t read_varint(std::istream &varint);

char uint8_to_hexadecimal_bot(uint8_t hex);

char uint8_to_hexadecimal_top(uint8_t hex);

#endif // _AUXILIARY_
