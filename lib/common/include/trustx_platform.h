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

#ifndef _TRUSTX_PLATFORM_H_
#define _TRUSTX_PLATFORM_H_

// Linux I2C interface 
#include <unistd.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>

#define PLATFORM_I2C_NAME	"/dev/i2c-1"

// Timing Related Setting
#define TRUSTX_TIME_WAKEUP	10
#define TRUSTX_TIME_POWERUP	100
#define TRUSTX_TIME_RESET	60000
#define	TRUSTX_TIME_READ	60000
#define	TRUSTX_TIME_WRITE	60000

#endif	// _TRUSTX_PLATFORM_H_
