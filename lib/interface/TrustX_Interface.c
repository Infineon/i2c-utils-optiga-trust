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
#include <sys/ioctl.h>

#include "trustx_platform.h"
#include "trustx_interface.h"
#include "trustx_error.h"
#include "trustx_debug.h"
#include "trustx_reg.h"
#include "trustx_debug.h"
#include "trustx_util.h"

// Globe Varable
uint16_t pTrustX_I2C_Handle = 0;
char pTrustX_I2C_Bus[100] = PLATFORM_I2C_NAME;

// MACRO
#define TRUSTX_SND(BUF,LEN,RET)	if(write(pTrustX_I2C_Handle, (uint8_t *)BUF, LEN) != LEN){RET = INTERFACE_ERR_WRITE;}
#define TRUSTX_REV(BUF,LEN,RET) if(read(pTrustX_I2C_Handle, (uint8_t *)BUF, LEN) != LEN){RET = INTERFACE_ERR_READ;}

/***********************************************
* trustX_I2C_Open()
* Description :
* Init I2C bus. Modify this function to init
* the i2c according to the platform requirement
*
* in : i2c Address
* ret : 	 INTERFACE_SUCCESS
* on error : INTERFACE_ERR_BUS_OPEN
* 			 INTERFACE_ERR_SLAVE_ADDR
***********************************************/
uint16_t trustX_I2C_Open(uint8_t i2cAddr)
{
	uint16_t ret = INTERFACE_SUCCESS;
	// I2C Open the i2c bus
	if (!(pTrustX_I2C_Handle = open(pTrustX_I2C_Bus, O_RDWR)))
	{
		// Error Handling
		ERRORPRINTINTERFACE("Failed to open i2c bus %s \n", PLATFORM_I2C_NAME);
		ret = INTERFACE_ERR_BUS_OPEN;
		return ret;

	}
	DEBUGPRINTINTERFACE("i2c_handle open Success. \n");

	if (ioctl(pTrustX_I2C_Handle, I2C_SLAVE, i2cAddr) < 0)
	{
		// Error Handling
		ERRORPRINTINTERFACE("Failed to acquire i2c bus access at 0x%.2x \n", i2cAddr);
		return INTERFACE_ERR_SLAVE_ADDR;
	}
	DEBUGPRINTINTERFACE("i2c bus acquire address: 0x%.2x \n", i2cAddr);

	return INTERFACE_SUCCESS;
}


/***********************************************
* trustX_I2C_Close()
* Description :
* Close I2C bus. Modify this function to close
* the i2c according to the platform requirement
*
* in : void
* ret : 	 INTERFACE_SUCCESS
* on error : INTERFACE_ERR_BUS_CLOSED
* 			 INTERFACE_ERR_SLAVE_ADDR
***********************************************/
uint16_t trustX_I2C_Close(void)
{
	close(pTrustX_I2C_Handle);
	pTrustX_I2C_Handle = 0;
	
	return INTERFACE_SUCCESS;
}

/***********************************************
* trustX_Reg_Write()
* Description :
* write to trustX register 
*
* in: register to write
* in: pointer to buffer
* in : Size of buffer
* ret : 	 INTERFACE_SUCCESS
* on error : INTERFACE_ERR_WRITE
***********************************************/
uint16_t trustX_Reg_Write(uint8_t reg, uint8_t *pData, uint16_t dataLen)
{
	uint16_t ret=INTERFACE_SUCCESS;
	uint8_t *pBuffer;
	uint16_t i;
		
	pBuffer = (uint8_t *) malloc(dataLen+1); //
	if (pBuffer == NULL)
	{
		ERRORPRINTINTERFACE("error: malloc fail!! \n");
		return INTERFACE_ERR_WRITE;
	}

	*pBuffer = reg;
	if ((dataLen > 0) && (pData != NULL))
	{
		for (i = 0; i < dataLen+1; i++)
		{
			*(pBuffer+i+1) = *(pData+i);
			DEBUGPRINTINTERFACE("pBuffer[%d] = 0x%.2x \n",i,*(pBuffer+i+1));
		}
	}
	
	for(i=0;i<10;i++)
	{
		ret = trustX_I2C_Write(pBuffer, dataLen+1);
		if (ret != INTERFACE_SUCCESS)
			DEBUGPRINTINTERFACE(".");
		else
		{
			break;
		}
		usleep(500);
	}	
	
	free(pBuffer);
	return ret;	
}

/***********************************************
* trustX_Reg_Read()
* Description :
* Read from trustX register 
*
* in: register to read
* in/out: pointer to buffer
* out : Size of buffer
* ret : 	 INTERFACE_SUCCESS
* on error : INTERFACE_ERR_WRITE
* 			 INTERFACE_ERR_READ
***********************************************/
uint16_t trustX_Reg_Read(uint8_t reg, uint8_t *pData, uint16_t *dataLen)
{
	uint16_t ret=INTERFACE_SUCCESS;
	uint8_t *pBuffer;
	uint16_t bufLen;
	uint16_t i;
		
	switch(reg)
	{
		case TRUSTX_REG_DATA:
			bufLen = TRUSTX_I2C_MAX_BUF_LEN;
			break;						
		case TRUSTX_REG_DATA_REG_LEN:		
		case TRUSTX_REG_BASE_ADDR:
		case TRUSTX_REG_I2C_MODE:
			bufLen = 2;
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
			bufLen = 4;
			break;
		default:
			bufLen = 0;
	}	
	
	pBuffer = (uint8_t *) malloc(bufLen+1); //
	if (pBuffer == NULL)
	{
		ERRORPRINTINTERFACE("error: malloc fail!! \n");
		return INTERFACE_ERR_WRITE;
	}

	*pBuffer = reg;
	for(i=0;i<10;i++)
	{
		ret = trustX_I2C_Write(pBuffer, 1);
		if (ret != INTERFACE_SUCCESS)
			DEBUGPRINTINTERFACE(".");
		else
		{
			DEBUGPRINTINTERFACE("Command sended.\n");
			break;
		}
		usleep(500);			
	}	

	if(ret == INTERFACE_SUCCESS)
	{
		for(i=0;i<10;i++)
		{	
			ret = trustX_I2C_Read(pData, bufLen);
			if(ret != INTERFACE_SUCCESS)
				DEBUGPRINTINTERFACE(".");
			else
			{	
				*dataLen = bufLen;
				break;
			}
		}
	}
	else
	{
		ERRORPRINTINTERFACE("I2C Error!!!!!!\n");
	}
	
	free(pBuffer);
	return ret;	
}

/***********************************************
* trustX_I2C_Write()
* Description :
* I2C bus Send. 
* Modify TRUSTX_SND macro according to platform
*
* in: pointer to buffer
* in : Size of buffer
* ret : 	 INTERFACE_SUCCESS
* on error : INTERFACE_ERR_WRITE
***********************************************/
uint16_t trustX_I2C_Write(uint8_t *pData, uint16_t dataLen)
{
	uint16_t ret=INTERFACE_SUCCESS;
	uint8_t *pBuffer;
	uint16_t i;
	
	pBuffer = (uint8_t *) malloc(dataLen); //
	if (pBuffer == NULL)
	{
		ERRORPRINTINTERFACE("error: malloc fail!! \n");
		return INTERFACE_ERR_WRITE;
	}
	
	for (i = 0; i < dataLen; i++)
	{
		*(pBuffer+i) = *(pData+i);
		DEBUGPRINTINTERFACE("pBuffer[%d] = 0x%.2x \n",i,*(pBuffer+i));
	}	

	TRUSTX_SND((uint8_t *)pBuffer,dataLen,ret);
	
	free(pBuffer);
	return ret;
}

/***********************************************
* trustX_I2C_Read()
* Description :
* I2C bus Receive. 
* Modify TRUSTX_REV macro according to platform
*
* in/out : pointer to pointer buffer
* in : bytes to receive
* ret : 	 INTERFACE_SUCCESS
* on error : INTERFACE_ERR_READ
***********************************************/
uint16_t trustX_I2C_Read(uint8_t *pData, uint16_t dataLen)
{
	uint16_t ret = INTERFACE_SUCCESS;
	uint8_t *pBuffer;
	uint16_t i;
	
	pBuffer = (uint8_t *) malloc(dataLen); // Data
	if (pBuffer == NULL)
	{
		ERRORPRINTINTERFACE("error: malloc fail!! \n");
		return INTERFACE_ERR_READ;
	}

	TRUSTX_REV(pBuffer,dataLen,ret);
	
	for (i = 0; i < dataLen; i++)
	{
		*(pData+i) = *(pBuffer+i);
		DEBUGPRINTINTERFACE("pBuffer[%d] = 0x%.2x \n",i,*(pBuffer+i));
	}	
	
	free(pBuffer);
	return ret;
}
