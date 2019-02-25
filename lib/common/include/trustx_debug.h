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
#ifndef _TRUSTX_DEBUG_H
#define _TRUSTX_DEBUG_H

#define DEBUGLEVEL 3

#if DEBUGLEVEL == 3
	#define	DEBUGPRINT(...)		printf(__VA_ARGS__);
	#define DEBUGLABEL(label)	DEBUGPRINT(label);
#endif

#if DEBUGLEVEL == 0
	#define	DEBUGPRINT(...)
	#define DEBUGLABEL(label)
#endif

// TrustC_Interface
//#define _DEBUGINTERFACE
#ifdef _DEBUGINTERFACE
	#define DEBUGPRINTINTERFACE(...)	DEBUGLABEL("[INTERFACE]");DEBUGPRINT(__VA_ARGS__);
	#define ERRORPRINTINTERFACE(...)	DEBUGLABEL("[INTERFACE]");DEBUGPRINT(__VA_ARGS__);
#else
	#define DEBUGPRINTINTERFACE(...)
	#define ERRORPRINTINTERFACE(...)
	//#define ERRORPRINTINTERFACE(...)	DEBUGLABEL("[INTERFACE]");DEBUGPRINT(__VA_ARGS__);
#endif // _DEBUGINTERFACE

// General
#define DEBUGPRINTSPACE		DEBUGPRINT("\n");

#endif // _TRUSTX_DEBUG_H
