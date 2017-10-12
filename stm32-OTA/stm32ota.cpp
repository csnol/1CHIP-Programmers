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

#include "stm32ota.h"

void stm32SendCommand(unsigned char commd) {    // Tested
  Serial.write(commd);
  Serial.write(~commd);
}

unsigned char stm32Erase() {     // Tested
  unsigned char eraseflag = 0;
  stm32SendCommand(STM32ERASE);
  while (!Serial.available());
  if (Serial.read() == STM32OK)
  {
    Serial.write(0xFF);
    Serial.write(0x00);
  }
  else return STM32ERR;
  while (!Serial.available());
  eraseflag = Serial.read();
  return eraseflag;
}

unsigned char stm32Erasen() {     // Tested
  unsigned char eraseflag = 0;
  stm32SendCommand(STM32ERASEN);
  while (!Serial.available());
  if (Serial.read() == STM32OK)
  {
    Serial.write(0xFF);
    Serial.write(0xFF);
    Serial.write(0x00);
  }
  else return STM32ERR;
  while (!Serial.available());
  eraseflag = Serial.read();
  return eraseflag;
}

// No test yet
unsigned char stm32Run()   {
  stm32SendCommand(STM32RUN);
  while (!Serial.available());
  if (Serial.read() == STM32OK) {
    stm32Address(STM32STADDR);
    return STM32OK;
  }
  else
    return STM32ERR;
}

// No test yet
unsigned char stm32Read(unsigned char * rdbuf, unsigned long rdaddress, unsigned char rdlong) {
  //unsigned char eraseflag = 0;
  stm32SendCommand(STM32RD);
  while (!Serial.available());
  if (Serial.read() == STM32OK)
    stm32Address(rdaddress);
  else return STM32ERR;
  while (!Serial.available());
  if (Serial.read() == STM32OK)
    stm32SendCommand(rdlong);
  while (!Serial.available());
  size_t rdlen = Serial.available();
  Serial.readBytes(rdbuf, rdlen);
  return STM32OK;
}

unsigned char stm32Address(unsigned long addr) {    // Tested
  unsigned char sendaddr[4];
  unsigned char addcheck = 0;
  sendaddr[0] = addr >> 24;
  sendaddr[1] = (addr >> 16) & 0xFF;
  sendaddr[2] = (addr >> 8) & 0xFF;
  sendaddr[3] = addr & 0xFF;
  for (int i = 0; i <= 3; i++) {
    Serial.write(sendaddr[i]);
    addcheck ^= sendaddr[i];
  }
  Serial.write(addcheck);
  while (!Serial.available());
  return Serial.read();
}

unsigned char stm32SendData(unsigned char * data, unsigned char datalen) {     // Tested
  //int sdata[datalen];
  Serial.write(datalen);
  for (int i = 0; i <= datalen; i++) {
    Serial.write(data[i]);
  }
  Serial.write(getChecksum(data, datalen));
  while (!Serial.available());
  return Serial.read();
}

char stm32Version() {     // Tested
  unsigned char vsbuf[14];
  stm32SendCommand(STM32GET);
  while (!Serial.available());
  vsbuf[0] = Serial.read();
  if (vsbuf[0] != STM32OK)
    return STM32ERR;
  else {
    Serial.readBytesUntil(STM32OK, vsbuf, 14);
    return vsbuf[1];
  }
}

String stm32GetId() {     // Tested
  int getid = 0;
  unsigned char sbuf[5];
  stm32SendCommand(STM32ID);
  while (!Serial.available());
  sbuf[0] = Serial.read();
  if (sbuf[0] == STM32OK) {
    Serial.readBytesUntil(STM32OK, sbuf, 4);
    getid = sbuf[1];
    getid = (getid << 8) + sbuf[2];
    if (getid == 0x410)
      return F10xx8;
    if (getid == 0x412)
      return F10xx6;
    if (getid == 0x418)
      return F107;
    if (getid == 0x444)
      return F03x46;
    if (getid == 0x414)
      return F10xxc;
    if (getid == 0x440)
      return F030x8;
    if (getid == 0x442)
      return F030xc;
  }
  else
    return STERR;
}

unsigned char getChecksum( unsigned char * data, unsigned char len) {    // Tested
  unsigned char lendata = len;
  for (int i = 0; i <= len; i++)
    lendata ^= data[i];
  return lendata;
}



