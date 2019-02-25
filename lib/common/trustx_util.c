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

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "trustx_util.h"

void trustX_Util_Delay(uint16_t cnt)
{
	uint16_t i;
	for (i=0;i<cnt;i++);
}

void trustX_Util_Printbuffer(uint8_t *pData, uint16_t uLen)
{
	uint16_t i,j;
	
	j=0;
	for(i = 0; i < uLen; i++)
	{
		printf("0x%.2x ",*(pData+i));
		if (j == 15)
		{
			printf("\n");
			j=0;
		}
		else
			j++;
	} 
	printf("\n");

}

uint32_t trustX_ParseHexorDec(const char *aArg)
{
	uint32_t value;

	if (strncmp(aArg, "0x",2) == 0)
		sscanf(aArg,"%x",&value);
	else
		sscanf(aArg,"%d",&value);

	return value;
}

void dwordToByte(uint32_t *input, uint8_t inputLen, uint8_t **output, uint8_t *outputLen)
{
	uint8_t i;

	*output=(uint8_t*)malloc(inputLen*4);
	*outputLen = inputLen*4;
	for(i=0;i<inputLen;i++)
	{
		*(*output+(i*4))= (uint8_t)(*(input+i) & 0x000000ff);
		*(*output+((i*4)+1))= (uint8_t)((*(input+i) >> 8) & 0x000000ff);
		*(*output+((i*4)+2))= (uint8_t)((*(input+i) >> 16) & 0x000000ff);
		*(*output+((i*4)+3))= (uint8_t)((*(input+i) >> 24) & 0x000000ff);
	}
}

void byteToDword(uint8_t *input, uint8_t inputLen, uint32_t *output, uint8_t *outputLen)
{
	uint8_t	i;

	*outputLen = inputLen/4;

	for(i=0;i<(*outputLen);i++)
	{
		output[i]=0x00000000;
		output[i]+= (input[i*4] & 0x000000ff);
		output[i]+= ((input[(i*4)+1] & 0x000000ff) << 8);
		output[i]+= ((input[(i*4)+2] & 0x000000ff) << 16);
		output[i]+= ((input[(i*4)+3] & 0x000000ff) << 24);
	}
}
