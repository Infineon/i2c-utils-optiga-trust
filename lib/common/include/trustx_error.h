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
#ifndef _TRUSTX_ERROR_H_
#define _TRUSTX_ERROR_H_

// Common Return Code
#define	SUCCESS_BASE				0x0000

// Interface layer Return Code
#define INTERFACE_BASE				0x0100
#define INTERFACE_SUCCESS			SUCCESS_BASE 
#define INTERFACE_ERR_BUS_OPEN		INTERFACE_BASE+0x01
#define	INTERFACE_ERR_SLAVE_ADDR	INTERFACE_BASE+0x02
#define	INTERFACE_ERR_READ			INTERFACE_BASE+0x03
#define INTERFACE_ERR_WRITE			INTERFACE_BASE+0x04
#define INTERFACE_ERR_UNKNOWN		INTERFACE_BASE+0XFF

// Marco for Try Block
#define ON_ERROR(ERR)				if(ERR != SUCCESS_BASE){break;}


#endif	// _TRUSTX_ERROR_H_
