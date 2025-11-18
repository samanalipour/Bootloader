/*
 * SD.c
 *
 *  Created on: Jan 25, 2025
 *      Author: saman
 */
#include "SD.h"

FRESULT SD_Mount(FATFS *FatFs){

  return f_mount(FatFs, "", 1);

}


FRESULT SD_Umount(void){

  return f_mount(NULL, "", 0);

}

uint32_t SD_Num_Of_Line(void){
  FIL Fil;
  FRESULT FR_Status;
  char buffer[128]; // Buffer to store lines
  int lineCount = 0;
  FR_Status = f_open(&Fil, "Application.hex", FA_READ);
  f_lseek(&Fil, 0);
  if(FR_Status != FR_OK)
  {
    DEBUG_PRINT("Error! While Opening (Application.hex) File For Read.. \r\n");
  }else{
    while (f_gets(buffer, sizeof(buffer), &Fil)) {
      lineCount++;
    }
    f_close(&Fil);
    return lineCount;
  }
  f_close(&Fil);
  return 0;
}

int SD_Read_Line(uint32_t line, char *Data, size_t bufferSize) {
    if (line <= 0) {
        return 0; // Invalid line number
    }
    FIL Fil;
    FRESULT FR_Status;
    uint32_t currentLine = 0;

    // Open the file
    FR_Status = f_open(&Fil, "Application.hex", FA_READ);
    f_lseek(&Fil, 0);
    if (FR_Status != FR_OK) {
        DEBUG_PRINT("Error! While opening file (Application2.hex) for reading.\r\n");
        return 0; // File open error
    }

    // Read lines until the requested line is found
    while (f_gets(Data, bufferSize, &Fil)) {
        currentLine++;
        if (currentLine == line) {
            f_close(&Fil);
            return 1; // Line found
        }
    }

    // If we reach here, the line was not found
    f_close(&Fil);
    return 0; // Line not found
}


