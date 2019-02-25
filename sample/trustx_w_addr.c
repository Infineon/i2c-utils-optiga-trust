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
	uint16_t	new_i2caddr	: 1;
	uint16_t	persistent	: 1;
	uint16_t	i2cbus		: 1;
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
	printf("\nHelp menu: trustx_w_addr <option> ...<option>\n");
	printf("option:- \n");
	printf("-a Set I2C Address (Default 0x%.2x) \n",0x30);
	printf("-b Set I2C bus (Default %s) \n",pTrustX_I2C_Bus);	
	printf("-n Set New I2C Address (Default 0x%.2x) \n",0x30);
	printf("-p Set New I2C Address persistent \n");	
	printf("-h Print this help menu\n");
}

int main(int argc, char **argv)
{
	int16_t ret;
	uint16_t dataLen;
	uint8_t pData[10];
	uint8_t reg;
			
	int option = 0;                    // Command line option.

	uint8_t i2c_address = TRUSTX_I2C_ADDR;
	uint8_t new_i2c_address = TRUSTX_I2C_ADDR;


	uOptFlag.all = 0;

    do // Begin of DO WHILE(FALSE) for error handling.
    {
		// ---------- Check for command line parameters ----------
        if (1 == argc)
			break;

        // ---------- Command line parsing with getopt ----------
        opterr = 0; // Disable getopt error messages in case of unknown parameters

        // Loop through parameters with getopt.
        while (-1 != (option = getopt(argc, argv, "a:b:n:ph")))
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
				case 'n': // New I2C ADDRESS
					uOptFlag.flags.new_i2caddr = 1;				
					new_i2c_address = trustX_ParseHexorDec(optarg);
					break;
				case 'p': // Set persistent
					uOptFlag.flags.persistent = 1;
					break;
				case 'h': // Print Help Menu
				default:  // Any other command Print Help Menu
					helpmenu();
					exit(0);
					break;
			}
		}
    } while (0); // End of DO WHILE FALSE loop.

	if (uOptFlag.all == 0)
	{
		helpmenu();
		exit(0);		
	}

	if (uOptFlag.flags.new_i2caddr == 0)
		new_i2c_address = i2c_address;
 
    //printf("Flags           : 0x%.4x \n",uOptFlag.all);
    printf("i2c address     : 0x%.4X \n",i2c_address);
    printf("New i2c address : 0x%.4X \n",new_i2c_address);
    printf("i2c bus         : %s \n",pTrustX_I2C_Bus);
		
	ret = trustX_I2C_Open(i2c_address);
	if (ret != INTERFACE_SUCCESS)
	{
		printf("I2C Open error!!!\n");
		return -1;
	}

	printf("Write I2C address \n");
	reg = TRUSTX_REG_BASE_ADDR;
	pData[1] = (new_i2c_address & 0x00ff); // Low Address
	
	if (uOptFlag.flags.persistent == 1) // High address
		pData[0] = 0x80;
	else
		pData[0] = 0x00; 
	
	ret = trustX_Reg_Write(reg, pData,2);
	if (ret != INTERFACE_SUCCESS)
		printf("Write I2C address Error!! \n");
	else
	{
		printf("Write I2C address Success. New Address : 0x%.2X\n", new_i2c_address); 
		printf("Closing the I2C and reopening it with new address.\n");
		trustX_I2C_Close();
		ret = trustX_I2C_Open(new_i2c_address);
		if (ret != INTERFACE_SUCCESS)
		{
			printf("I2C Open error!!!\n");
			return -1;
		}

		printf("Read Device Address Register :\n");
		reg = TRUSTX_REG_I2C_STATE;
		ret = trustX_Reg_Read(reg,pData,&dataLen);
		if (ret != INTERFACE_SUCCESS)
			printf("TRUSTX_REG_BASE_ADDR Read Error!! \n");
		else
			printf("TRUSTX_REG_BASE_ADDR [0x%.2X] : 0x%.2X 0x%.2X 0x%.2X 0x%.2X \n",
					reg,pData[0],pData[1],pData[2],pData[3]);
	}
	
	trustX_I2C_Close();
	return 0;
}
