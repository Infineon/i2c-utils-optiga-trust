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

#ifndef _TRUSTX_REG_H_
#define _TRUSTX_REG_H_

#include <stdio.h>
#include <stdint.h>

// Macro
//REG set
#define	TRUSTX_REG_DATA				(uint8_t)0x80u	//
#define	TRUSTX_REG_DATA_REG_LEN		(uint8_t)0x81u	//
#define	TRUSTX_REG_I2C_STATE		(uint8_t)0x82u	//
#define	TRUSTX_REG_BASE_ADDR		(uint8_t)0x83u	//
#define	TRUSTX_REG_MAX_SCL_FREQU	(uint8_t)0x84u	//
#define	TRUSTX_REG_GUARD_TIME		(uint8_t)0x85u	//
#define	TRUSTX_REG_TRANS_TIMEOUT	(uint8_t)0x86u	//
#define	TRUSTX_REG_PWR_SAVE_TIMEOUT	(uint8_t)0x87u	//
#define	TRUSTX_REG_SOFT_RESET		(uint8_t)0x88u	//
#define	TRUSTX_REG_I2C_MODE			(uint8_t)0x89u	//
#define	TRUSTX_REG_APP_STATE_0		(uint8_t)0x90u	//
#define	TRUSTX_REG_APP_STATE_1		(uint8_t)0x91u	//
#define	TRUSTX_REG_APP_STATE_2		(uint8_t)0x92u	//
#define	TRUSTX_REG_APP_STATE_3		(uint8_t)0x93u	//
#define	TRUSTX_REG_APP_STATE_4		(uint8_t)0x94u	//
#define	TRUSTX_REG_APP_STATE_5		(uint8_t)0x95u	//
#define	TRUSTX_REG_APP_STATE_6		(uint8_t)0x96u	//
#define	TRUSTX_REG_APP_STATE_7		(uint8_t)0x97u	//
#define	TRUSTX_REG_APP_STATE_8		(uint8_t)0x98u	//
#define	TRUSTX_REG_APP_STATE_9		(uint8_t)0x99u	//
#define	TRUSTX_REG_APP_STATE_A		(uint8_t)0x9Au	//
#define	TRUSTX_REG_APP_STATE_B		(uint8_t)0x9Bu	//
#define	TRUSTX_REG_APP_STATE_C		(uint8_t)0x9Cu	//
#define	TRUSTX_REG_APP_STATE_D		(uint8_t)0x9Du	//
#define	TRUSTX_REG_APP_STATE_E		(uint8_t)0x9Eu	//
#define	TRUSTX_REG_APP_STATE_F		(uint8_t)0x9Fu	//
#define	TRUSTX_REG_FOR_IFX_USE_1	(uint8_t)0xA0u	//
#define	TRUSTX_REG_FOR_IFX_USE_2	(uint8_t)0xA1u	//

#endif	// _TRUSTX_REG_H_
