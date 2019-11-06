/*******************************************************************************
*                            block parser
*                       =====================
* File Name: block_parser_test.cpp
* Related files: block_parser.cpp block_parser.hpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 8.10.19
* Last update: 10.10.19
*******************************************************************************/

/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
#include <iostream> // std::cout
#include <stdio.h> /* printf */
#include <vector> // vector
/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "../include/block_parser.hpp"
using namespace hrd9;

/*============================================================================*/
/*                             ~~~~~~~~~~~~~~~~~~~                            */
/*                             Forward declaration                            */
/*                             ~~~~~~~~~~~~~~~~~~~                            */
/*                                                                 Unit tests */
/*                                                                 ~~~~~~~~~~ */
static void unit_parse_block(void);

/*============================================================================*/

int main()
{
    unit_parse_block();

  
    return (0);
}

/*============================================================================*/
/*                                 unit_test_s                                */
/*============================================================================*/
/*                                                                  unit_parse_block */
/*                                                                  ~~~~~~~~~ */

static void unit_parse_block(void)
{  
    std::cout << "================ unit_parse_block =============="<< std::endl;

    BlockParser block_parser;

    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "~~~~~~~~~~~~~~~~~~~~ binary dump ~~~~~~~~~~~~~~~"<< std::endl;
    block_parser.print_binary_dump();
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;

    block_parser.print_header_data();

    std::cout << std::endl;

    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;
    printf("Block Transactions count %u \n",
            block_parser.get_transaction_count());
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< std::endl;

    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "================ transactions =================="<< std::endl;
    block_parser.get_transactions()[0].print_transaction();
    block_parser.get_transactions()[100].print_transaction();
 
    std::cout << "================================================"<< std::endl;
}
