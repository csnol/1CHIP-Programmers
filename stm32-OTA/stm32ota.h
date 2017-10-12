/*   
    Copyright (C) 2017  CSNOL  https://github.com/csnol/1CHIP-Programmers

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, 

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef _STM32OTA_H_
#define _STM32OTA_H_
#endif
#include <Arduino.h>

#define STERR     		"ERROR"
#define STM32INIT  		0x7F          // Send Init command 
#define STM32OK  		  0x79          // return ACK
#define STM32ROK  		0x1F          // return NACK
#define STM32GET  		0             // get version command
#define STM32RUN  		0x21          // Restart and Run programm
#define STM32RD  		  0x11          // Read flash command
#define STM32WR  		  0x31          // Write flash command
#define STM32UNPCTWR  0x73          // Unprotest WR command
#define STM32ERASE  	0x43          // Erase flash command
#define STM32ERASEN 	0x44          // Erase extended flash command
#define STM32ID  		  0x02          // get chip ID command
#define STM32STADDR  	0x8000000     // STM32 codes start address
#define STM32ERR  		0x3F
#define F10xx8  "STM32F103x8/B"     //tested
#define F10xx6  "STM32F103x4/6"		
#define F10xxc  "STM32F103xC/D/E"
#define F107    "STM32F105/107"
#define F03x46  "STM32F03xx4/6"		//tested
#define F030xc  "STM32F030xC"
#define F030x8  "STM32F030x8/05x"

void stm32SendCommand(unsigned char commd);
unsigned char stm32Erase();
unsigned char stm32Erasen();
unsigned char stm32Read(unsigned char * rdbuf, unsigned long rdaddress, unsigned char rdlong);
unsigned char stm32Address(unsigned long addr);
unsigned char stm32SendData(unsigned char * data, unsigned char datalen);
unsigned char getChecksum( unsigned char * data, unsigned char len);
String stm32GetId();
char stm32Version();
