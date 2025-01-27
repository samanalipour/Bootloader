/*
 * SD.h
 *
 *  Created on: Jan 25, 2025
 *      Author: saman
 */

#ifndef INC_SD_H_
#define INC_SD_H_

#include "fatfs.h"
#include <stdio.h>

//FATFS FatFs1;

FRESULT   SD_Mount(FATFS *FatFs);
FRESULT   SD_Umount(void);
uint32_t  SD_Num_Of_Line(void);
int SD_Read_Line(uint32_t line, char *Data, size_t bufferSize);
#endif /* INC_SD_H_ */
