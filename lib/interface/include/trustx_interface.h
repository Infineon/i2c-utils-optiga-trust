/**
* MIT License
*
* Copyright (c) 2019 Infineon Technologies AG
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE

*/
#ifndef _TRUSTX_INTERFACE_H_
#define _TRUSTX_INTERFACE_H_

#include <stdio.h>
#include <stdint.h>

// Macro
// I2C address
#define TRUSTX_I2C_ADDR				0x30
#define TRUSTX_I2C_MAX_BUF_LEN		0x0615

// External
extern char pTrustX_I2C_Bus[100];

//Function Prototyping
uint16_t trustX_I2C_Open(uint8_t i2cAddr); // Open I2C bus
uint16_t trustX_I2C_Close(void); // Close I2C bus
uint16_t trustX_I2C_Write(uint8_t *pData, uint16_t dataLen); // Send Data
uint16_t trustX_I2C_Read(uint8_t *pData, uint16_t dataLen); // Read Data
uint16_t trustX_Reg_Write(uint8_t reg, uint8_t *pData, uint16_t dataLen); // Write Data to Reg
uint16_t trustX_Reg_Read(uint8_t reg, uint8_t *pData, uint16_t *dataLen); // Read Data from Reg

#endif // _TRUSTX_INTERFACE_H_
