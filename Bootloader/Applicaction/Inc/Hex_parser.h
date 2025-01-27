/*
 * Hex_parser.h
 *
 *  Created on: Jan 26, 2025
 *      Author: saman
 */

#ifndef INC_HEX_PARSER_H_
#define INC_HEX_PARSER_H_

#include "main.h"
typedef enum {
    INVALID_FORMAT = -1,   // Invalid format
    INVALID_CHECKSUM = -2, // Invalid checksum
    UNSUPPORTED = -3,      // Unsupported
    DATA_RECORD = 0,       // Data record
    END_OF_FILE = 1,       // End of file
    BASE_ADDRESS = 2,      // Base address
    Nop = 3                //do nothing
} Parser_status;

Parser_status parse_hex_line(const char *line, HexLine *result);
int validate_checksum(const char *line);


#endif /* INC_HEX_PARSER_H_ */
