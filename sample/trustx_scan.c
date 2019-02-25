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

#include "trustx_interface.h"
#include "trustx_platform.h"
#include "trustx_error.h"
#include "trustx_reg.h"
#include "trustx_debug.h"
#include "trustx_util.h"

typedef struct _OPTFLAG {
	uint16_t	i2cbus		: 1;
	uint16_t	dummy1		: 1;
	uint16_t	dummy2		: 1;
	uint16_t	dummy3		: 1;
	uint16_t	dummy4		: 1;
	uint16_t	dummy5		: 1;
	uint16_t	dummy6		: 1;
	uint16_t	dummy7		: 1;
	uint16_t	dummy8		: 1;
	uint16_t	dummy9		: 1;
	uint16_t	dummy10		: 1;
	uint16_t	dummy11		: 1;
	uint16_t	dummy12		: 1;
	uint16_t	dummy13		: 1;
	uint16_t	dummy14		: 1;
	uint16_t	dummy15		: 1;
}OPTFLAG;

union _uOptFlag {
	OPTFLAG	flags;
	uint16_t	all;
} uOptFlag;


void helpmenu(void)
{
	printf("\nHelp menu: trustx_scan <option> ...<option>\n");
	printf("option:- \n");
	printf("-b Set I2C bus (Default %s) \n",pTrustX_I2C_Bus);
	printf("-h Print is help menu\n");
}

int main(int argc, char **argv)
{
	int16_t ret;
	int option = 0;                    // Command line option.
	uint8_t pData[TRUSTX_I2C_MAX_BUF_LEN];
	uint8_t pDetected[256];
	uint16_t i,j;
	uint8_t ch;
	
	uOptFlag.all = 0;

    do // Begin of DO WHILE(FALSE) for error handling.
    {
		// ---------- Check for command line parameters ----------
        if (1 == argc)
        {
		}

        // ---------- Command line parsing with getopt ----------
        opterr = 0; // Disable getopt error messages in case of unknown parameters

        // Loop through parameters with getopt.
        while (-1 != (option = getopt(argc, argv, "b:h")))
        {
			switch (option)
            {
				case 'b': // Set I2C Bus
					uOptFlag.flags.i2cbus = 1;			
					strcpy(pTrustX_I2C_Bus,optarg);
					break;
				case 'h': // Print Help Menu
					helpmenu();
					exit(0);
				default:  // Any other command Print Help Menu
					helpmenu();
					exit(0);
					break;
			}
		}
    } while (0); // End of DO WHILE FALSE loop.
 
	printf("WARNING! This program can confuse your I2C bus, cause data loss and worse!\n");
	printf("I will probe file %s using read byte commands.\n",pTrustX_I2C_Bus);
	printf("I will probe address range 0x00-0x7F.\n");
	printf("Continue? [Y/n]\n");
	ch = getchar();
	if ((ch == 'n') || (ch == 'N'))
		exit(0);

	printf("------------------------------------------------------\n");

	// Init data
	for(j=0;j<0x80;j++)
	{
		pData[j] = 0x00;
		pDetected[j] = 0x00; 
	}

	// Skip address
	pDetected[0] = 0xff; // General Call Address
	pDetected[1] = 0xff; // CBUS address
	pDetected[2] = 0xff; // RFU
	pDetected[3] = 0xff; // RFU
	pDetected[4] = 0xff; // HS-Mode master code
	pDetected[5] = 0xff; // HS-Mode master code
	pDetected[6] = 0xff; // HS-Mode master code
	pDetected[7] = 0xff; // HS-Mode master code
	
	pDetected[0x7C] = 0xff; // RFU
	pDetected[0x7D] = 0xff; // RFU
	pDetected[0x7E] = 0xff; // RFU
	pDetected[0x7F] = 0xff; // 10-bit slave address
	
	for(j=0;j<0x80;j++)
	{
		if (pDetected[j] == 0xff)
			continue;
			
		ret = trustX_I2C_Open(j);
		if (ret != INTERFACE_SUCCESS)
		{
			printf("Interface Open error!!!\n");
			return -1;
		}

		for(i=0;i<2;i++)
		{
			ret = trustX_I2C_Read(pData,1);
			if(ret != INTERFACE_SUCCESS)
			{
				pDetected[j] = 0x00;
			}
			else
			{
				pDetected[j] = 0x01;
				break;
			}
			usleep(500);
		}

		trustX_I2C_Close();	
	}

	printf("     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f");
	for(j=0;j<0x80;j++)
	{
		if(!(j % 16))
			printf("\n%.2x : ",j);
		
		if (pDetected[j] == 1)
			printf("%.2x ",j);
		else if (pDetected[j] == 0xff)
			printf("   ");
		else
			printf("-- ");
	}
	printf("\n");
	return ret;
}


