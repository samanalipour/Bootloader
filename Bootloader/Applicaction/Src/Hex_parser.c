/*
 * Hex_parser.c
 *
 *  Created on: Jan 26, 2025
 *      Author: saman
 */



#include "Hex_parser.h"


Parser_status parse_hex_line(const char *line, HexLine *result) {
    if (line[0] != ':') {
        return -1; // Invalid format
    }

    if (!validate_checksum(line)) {
        return -2; // Invalid checksum
    }

    int record_len = 0;
    sscanf(line + 1, "%2x", &record_len);

    uint16_t address = 0;
    sscanf(line + 3, "%4hx", &address);

    int record_type = 0;
    sscanf(line + 7, "%2x", &record_type);

    // Process based on the record type
    switch (record_type) {
        case 0x00: // Data Record
            result->address = address;
            result->data_len = record_len;
            for (int i = 0; i < record_len; i++) {
                unsigned int byte = 0;
                sscanf(line + 9 + (i * 2), "%2x", &byte);
                result->data[i] = (uint8_t)byte;
            }
            return 0;

        case 0x01: // End of File Record
            return 1; // Signal end of file

        //case 0x02: // Extended Segment Address Record
        case 0x04: // Extended Linear Address Record
        {
          result->data_len = record_len;
          for (int i = 0; i < record_len; i++) {
              unsigned int byte = 0;
              sscanf(line + 9 + (i * 2), "%2x", &byte);
              result->data[i] = (uint8_t)byte;
          }
            return 2;
        }

        //case 0x03: // Start Segment Address Record
        case 0x05: // Start Linear Address Record
            // These are optional and depend on your use case.
            // Parse and store the address if needed.
             return 3;
            //break;

        default:
            return -3; // Unsupported or unknown record type
    }

    return -3; // Success
}


// Function to calculate the checksum of a line
int validate_checksum(const char *line) {
    int length = strlen(line);
    uint8_t sum = 0;
    for (int i = 1; i < length - 2; i += 2) { // Skip ':' and checksum at the end
        unsigned int byte = 0;
        sscanf(line + i, "%2x", &byte);
        sum += (uint8_t)byte;
    }
    return (sum == 0); // Return true if the checksum is valid
}
