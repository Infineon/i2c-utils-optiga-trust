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
	uint16_t	readall		: 1;
	uint16_t	reg			: 1;
	uint16_t	write		: 1;
	uint16_t	i2cbus		: 1;
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
	printf("\nHelp menu: trustx_reg <option> ...<option>\n");
	printf("option:- \n");
	printf("-a Set I2C Address (Default 0x%X) \n",0x30);
	printf("-b Set I2C bus (Default %s) \n",pTrustX_I2C_Bus);	
	printf("-w <filename> \n");	
	printf("-r <0xnn> Select Register\n");	
	printf("-R Read all register (except DATA[0x80]) \n");	
	printf("-h Print is help menu\n");
}

static uint16_t _readFrom(uint8_t *data, char *filename)
{
	
	FILE *datafile;
	uint16_t len;
	uint8_t buf[2048];
	uint16_t ret;

	//open 
	datafile = fopen((const char *)filename,"rb");
	if (!datafile)
	{
		return 1;
	}

	//Read file
	len = fread(buf, 1, sizeof(buf), datafile); 
	if (len > 0)
	{
		ret = len;
		memcpy(data,buf,len);
	}

	fclose(datafile);

	return ret;

}

static void _reg_print(uint8_t reg)
{
	// Readable Register, except DATA[0x80]
	switch(reg)
	{
		case TRUSTX_REG_DATA:
			printf("DATA             ");
			break;		
		case TRUSTX_REG_BASE_ADDR:
			printf("BASE_ADDR        ");
			break;		
		case TRUSTX_REG_DATA_REG_LEN:		
			printf("DATA_REG_LEN     ");
			break;		
		case TRUSTX_REG_I2C_MODE:
			printf("I2C_MODE         ");
			break;		
		case TRUSTX_REG_I2C_STATE:		
			printf("I2C_STATE        ");
			break;		
		case TRUSTX_REG_MAX_SCL_FREQU:	
			printf("MAX_SCL_FREQU    ");
			break;		
		case TRUSTX_REG_GUARD_TIME:		
			printf("GUARD_TIME       ");
			break;		
		case TRUSTX_REG_TRANS_TIMEOUT:	
			printf("TRANS_TIMEOUT    ");
			break;		
		case TRUSTX_REG_PWR_SAVE_TIMEOUT:
			printf("PWR_SAVE_TIMEOUT ");
			break;		
		case TRUSTX_REG_APP_STATE_0:		
			printf("APP_STATE_0      ");
			break;		
		case TRUSTX_REG_APP_STATE_1:		
			printf("APP_STATE_1      ");
			break;		
		case TRUSTX_REG_FOR_IFX_USE_1:	
			printf("FOR_IFX_USE_1    ");
			break;		
		case TRUSTX_REG_FOR_IFX_USE_2:
			printf("FOR_IFX_USE_2    ");
			break;
		default:
			printf("UNKNOWN          ");
	}	
	printf("[0x%.2X] : ",reg);
}

int main(int argc, char **argv)
{
	int16_t ret;
	int option = 0;                    // Command line option.
	uint8_t i2c_address = TRUSTX_I2C_ADDR;
	uint8_t pData[2048];
	uint16_t dataLen;
	uint8_t reg;
	char *infile = NULL;
	uint16_t i;
	
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
        while (-1 != (option = getopt(argc, argv, "a:b:w:r:Rh")))
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
				case 'w': // Write info
					uOptFlag.flags.write = 1;			
					infile = optarg; 	
					break;
				case 'r': // Register to used
					uOptFlag.flags.reg = 1;			
					reg = trustX_ParseHexorDec(optarg); 	
					break;
				case 'R': // Set I2C ADDRESS
					uOptFlag.flags.readall = 1;			
					break;
				case 'h': // Print Help Menu
				default:  // Any other command Print Help Menu
					helpmenu();
					exit(0);
					break;
			}
		}
    } while (0); // End of DO WHILE FALSE loop.
 
	printf("\n");
    printf("i2c address     : 0x%.4X \n",i2c_address);
    printf("i2c bus         : %s \n",pTrustX_I2C_Bus);    

	ret = trustX_I2C_Open(i2c_address);
	if (ret != INTERFACE_SUCCESS)
	{
		printf("Interface Open error!!!\n");
		return -1;
	}
  
	printf("------------------------------------------------------\n");
	printf("\n");
	
	if (uOptFlag.flags.readall == 1)
	{
		for (i=0x80;i<0xA2;i++)
		{
			switch(i)
			{
				case TRUSTX_REG_DATA_REG_LEN:		
				case TRUSTX_REG_I2C_MODE:
				case TRUSTX_REG_I2C_STATE:		
				case TRUSTX_REG_MAX_SCL_FREQU:	
				case TRUSTX_REG_GUARD_TIME:		
				case TRUSTX_REG_TRANS_TIMEOUT:	
				case TRUSTX_REG_PWR_SAVE_TIMEOUT:
				case TRUSTX_REG_APP_STATE_0:		
				case TRUSTX_REG_FOR_IFX_USE_1:	
				case TRUSTX_REG_FOR_IFX_USE_2:
					reg = i;
					_reg_print(i);
					ret = trustX_Reg_Read(reg,pData,&dataLen);
					if(ret != INTERFACE_SUCCESS)
						printf("error!!! \n");
					else
						trustX_Util_Printbuffer(pData,dataLen);
					break;
			}
		}
	}
	else
	{
		if (uOptFlag.flags.reg == 1)
		{
			if (uOptFlag.flags.write == 1)
			{
				dataLen = _readFrom(pData, infile);
				if (dataLen > TRUSTX_I2C_MAX_BUF_LEN)
				{
					printf("Error file too big!!!!! Max : %d\n", TRUSTX_I2C_MAX_BUF_LEN);
				}
				else
				{
					switch(reg)
					{
						case TRUSTX_REG_DATA:
							dataLen = TRUSTX_I2C_MAX_BUF_LEN;
							break;						
						case TRUSTX_REG_DATA_REG_LEN:		
						case TRUSTX_REG_BASE_ADDR:
						case TRUSTX_REG_I2C_MODE:
							dataLen = 2;
							break;		
						case TRUSTX_REG_I2C_STATE:		
						case TRUSTX_REG_MAX_SCL_FREQU:	
						case TRUSTX_REG_GUARD_TIME:		
						case TRUSTX_REG_TRANS_TIMEOUT:	
						case TRUSTX_REG_PWR_SAVE_TIMEOUT:
						case TRUSTX_REG_APP_STATE_0:		
						case TRUSTX_REG_APP_STATE_1:		
						case TRUSTX_REG_APP_STATE_2:		
						case TRUSTX_REG_APP_STATE_3:		
						case TRUSTX_REG_APP_STATE_4:		
						case TRUSTX_REG_APP_STATE_5:		
						case TRUSTX_REG_APP_STATE_6:		
						case TRUSTX_REG_APP_STATE_7:		
						case TRUSTX_REG_APP_STATE_8:		
						case TRUSTX_REG_APP_STATE_9:		
						case TRUSTX_REG_APP_STATE_A:		
						case TRUSTX_REG_APP_STATE_B:		
						case TRUSTX_REG_APP_STATE_C:		
						case TRUSTX_REG_APP_STATE_D:		
						case TRUSTX_REG_APP_STATE_E:		
						case TRUSTX_REG_APP_STATE_F:		
						case TRUSTX_REG_FOR_IFX_USE_1:	
						case TRUSTX_REG_FOR_IFX_USE_2:
							dataLen = 4;
							break;
						default:
							dataLen = 0;
					}

					_reg_print(reg);
					ret = trustX_Reg_Write(reg,pData,dataLen);
					if(ret != INTERFACE_SUCCESS)
						printf("error!!! \n");
					else
						printf("Write success.\n");			
				}
				
			}
			else
			{
				printf("\n");
				_reg_print(reg);
				ret = trustX_Reg_Read(reg,pData,&dataLen);
				if(ret != INTERFACE_SUCCESS)
					printf("error!!! \n");
				else
					trustX_Util_Printbuffer(pData,dataLen);
			}
		}
		else
		{
			printf("No register input!!\n");
		}
	}
	trustX_I2C_Close();	
	return ret;
}


