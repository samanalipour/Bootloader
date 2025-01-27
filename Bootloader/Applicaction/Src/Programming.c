/*
 * Programming.c
 *
 *  Created on: Jan 26, 2025
 *      Author: saman
 */
#include "Programming.h"
FATFS FatFs;
FIL Fil;
FRESULT FR_Status;

//uint32_t address; // Offset address
//uint8_t data[256]; // Data to be written
//size_t data_len; // Length of the data
void program(void){

  //------------------[ Mount The SD Card ]--------------------
  FR_Status = SD_Mount(&FatFs);
  if (FR_Status != FR_OK)
  {
    DEBUG_PRINT("Error! While Mounting SD Card\r\n");
  }else{
    DEBUG_PRINT("SD Card Mounted Successfully! \r\n");
  }
  //------------------[ Writting flash memory ]--------------------
  uint16_t Line_Num = 1;
  char IntelHex[200];
  char TxBuffer[200];
  HexLine Result;
  uint32_t BaseAddress=0;
  uint8_t SectorNum = 2;
  uint32_t SectorBase=0;
  uint32_t SectorOffset=0;
  bool base_flag = 0;
  while(1){//Line_Num<6
    SD_Read_Line(Line_Num,IntelHex, sizeof(IntelHex));
    DEBUG_PRINT("Line num %d\r\n",Line_Num);
    //DEBUG_PRINT(IntelHex);
    Parser_status Current_status;
    Current_status =  parse_hex_line(IntelHex, &Result);
    //printArray("DATA ", Result.data,Result.data_len);
    if(Current_status == DATA_RECORD ){
      printArray("DATA",Result.data,Result.data_len);
      DEBUG_PRINT("Address offset is %x\r\n",(unsigned int)Result.address);
      uint32_t Address = BaseAddress | Result.address;
      DEBUG_PRINT("Address is %x\r\n",(unsigned int)Address);
      if(base_flag==1){
        if(Address == 0x08008000)SectorNum = 2;
        if(Address == 0x0800C000)SectorNum = 3;
        if(Address == 0x08010000)SectorNum = 4;
        if(Address == 0x08020000)SectorNum = 5;
        DEBUG_PRINT("Sector number is %d\r\n",SectorNum);
        SectorBase = Address;
        DEBUG_PRINT("Address is %x\r\n",(unsigned int)SectorBase);
        MY_FLASH_SetSectorAddrs(SectorNum,SectorBase);
        //MY_FLASH_SetSectorAddrs(2,0x08008000);
        MY_FLASH_EraseSector();
        base_flag=0;
      }
      SectorOffset = Address - SectorBase;
      DEBUG_PRINT("SectorOffset is %d\r\n",(unsigned int)SectorOffset);
      MY_FLASH_WriteN(SectorOffset,Result.data,Result.data_len,DATA_TYPE_8);
    }
    else if(Current_status == BASE_ADDRESS ){
      for(int i=0;i<Result.data_len;i++){
        BaseAddress |= Result.data[i];
        BaseAddress <<= 8;
      }
      BaseAddress <<= 8;
      base_flag = 1;
      DEBUG_PRINT("Base address is %x\r\n",(unsigned int)BaseAddress);
    }
    else if(Current_status == END_OF_FILE ){printf("End of the HEX file\r\n");break;}
    else if(Current_status == INVALID_FORMAT ){sprintf(TxBuffer, "Error! While Parsing line %d, Error Code: (%i)\r\n",Line_Num, Current_status);printf(TxBuffer);}
    else if(Current_status == INVALID_CHECKSUM ){sprintf(TxBuffer, "Error! While Parsing line %d, Error Code: (%i)\r\n",Line_Num, Current_status);printf(TxBuffer);}
    else if(Current_status == UNSUPPORTED ){sprintf(TxBuffer, "Error! While Parsing line %d, Error Code: (%i)\r\n",Line_Num, Current_status);printf(TxBuffer);}
    Line_Num++;
  }
  //------------------[ Unmount The SD Card ]--------------------
  FR_Status = SD_Umount();
  if (FR_Status != FR_OK)
  {
    DEBUG_PRINT("Error! While Un-mounting SD Card\r\n");
  } else{
    DEBUG_PRINT("SD Card Un-mounted Successfully! \r\n");
  }

}

void jump_to_user_code(void){
  __disable_irq();
  SysTick->CTRL = 0;
  HAL_RCC_DeInit();
  for (uint8_t i = 0; i < (102 + 31u) / 32; i++)
  {
    NVIC->ICER[i]=0xFFFFFFFF;
    NVIC->ICPR[i]=0xFFFFFFFF;
  }
  __enable_irq();
  uint32_t msp_value = *(volatile uint32_t *)0x0800C000;
  __set_MSP(msp_value);
  SCB->VTOR = 0x0800C000;
  void (*Application_reset_handler)(void);
  uint32_t resethandler_address = *(volatile uint32_t *)(0x0800C004);
  Application_reset_handler = (void *) resethandler_address;
  Application_reset_handler();
}
