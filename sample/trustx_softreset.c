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
	uint16_t	i2caddr		: 1;
	uint16_t	i2cbus		: 1;
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
	printf("\nHelp menu: trustx_softrest <option> ...<option>\n");
	printf("option:- \n");
	printf("-a Set I2C Address (Default 0x%.2x) \n",0x30);
	printf("-b Set I2C bus (Default %s) \n",pTrustX_I2C_Bus);
	printf("-h Print this help menu\n");
}

int main(int argc, char **argv)
{
	int16_t ret;
	uint8_t pData[10];
	uint8_t reg;
			
	int option = 0;                    // Command line option.

	uint8_t i2c_address = TRUSTX_I2C_ADDR;

	uOptFlag.all = 0;

    do // Begin of DO WHILE(FALSE) for error handling.
    {
		// ---------- Check for command line parameters ----------
        if (1 == argc)
			break;

        // ---------- Command line parsing with getopt ----------
        opterr = 0; // Disable getopt error messages in case of unknown parameters

        // Loop through parameters with getopt.
        while (-1 != (option = getopt(argc, argv, "a:b:h")))
        {
			switch (option)
            {
				case 'a': // Set I2C ADDRESS
					uOptFlag.flags.i2caddr = 1;				
					i2c_address = trustX_ParseHexorDec(optarg);
					break;
				case 'b': // Set I2C Bus
					uOptFlag.flags.i2cbus = 1;			
					strcpy(pTrustX_I2C_Bus,optarg);
					break;
				case 'h': // Print Help Menu
				default:  // Any other command Print Help Menu
					helpmenu();
					exit(0);
					break;
			}
		}
    } while (0); // End of DO WHILE FALSE loop.
 
    printf("i2c address     : 0x%.4X \n",i2c_address);
    printf("i2c bus         : %s \n",pTrustX_I2C_Bus);
    		
	ret = trustX_I2C_Open(i2c_address);
	if (ret != INTERFACE_SUCCESS)
	{
		printf("I2C Open error!!!\n");
		return -1;
	}

	// printf("Soft Reset \n");
	reg = TRUSTX_REG_SOFT_RESET;
	pData[0] = 0x00;
	pData[1] = 0x00; 
	
	ret = trustX_Reg_Write(reg, pData,2);
	if (ret != INTERFACE_SUCCESS)
		printf("Soft Reset Error!! \n");
	else
		printf("Soft Reset Done. \n");
	
	trustX_I2C_Close();
	return 0;
}
