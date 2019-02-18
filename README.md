# I2C Utilities for OPTIGA™ Trust secure IC

This repositiry provides a set of utilities to easier an interaction with a OPTIGA™ Trust device.
These utilities interact with registers of a OPTIGA™ Trust secure IC.

# Supported options

* Perform a software reset
* Scan i2c bus to find a security IC
* Assign a new address to a security IC
* Update a register value

# Usage examples

# Registers

Below you can find a table of Infineon standard register set. For details plese have a look on Infineon I2C protocol specification [ver. 1.65](https://github.com/ayushev/optiga-trust-m/blob/master/documents/Infineon_I2C_Protocol_v2.02.pdf) (PDF)

| Register Address  | Name  | Size in Bytes  | Description  |  Master Access |
|---|---|---|---|---|
| 0x80  | DATA  | DATA_REG_LEN   | This is the location where data shall be read from or written to the I2C slave | Read/Write |
| 0x81  | DATA_REG_LEN  |  2 | This register holds the maximum data register (Addr 0x80) length. The allowed values are 0x0010 up to 0xFFFF. After writing the new data register length it becomes effective with the next I2C master access. However, in case the slave could not accept the new length it indicates its maximum possible length within this register. Therefore it is recommended to read the value back after writing it to be sure the I2C slave did accept the new value. _Note: the value of MAX_PACKET_SIZE is derived from this value or vice versa (MAX_PACKET_SIZE= DATA_REG_LEN-5)_  | Read/Write |
| 0x82  |  I2C_STATE |  4 |  Bits 31:24 of this register provides the I2C state in regards to the supported features (e.g. clock stretching …) and whether the device is busy executing a command and/or ready to return a response etc. Bits 15:0 defining the length of the response data block at the physical layer. | Read only  |
| 0x83  |  BASE_ADDR |  2 | This register holds the I2C base address as specified by Table 2-2. If not differently defined by a particular project the default value at reset is 0x20. After writing a different address the new address become effective with the next I2C master access. In case the bit 15 is set in addition to the new address (bit 6:0) it becomes the new default address at reset (persistent storage).  |  Write Only |
| 0x84  | MAX_SCL_FREQU  | 4  | This register holds the maximum clock frequency in KHz supported by the I2C slave. The value gets adjusted to the register I2C_Mode setting. Fast Mode (Fm): The allowed values are 50 up to 400. Fast Mode (Fm+): The allowed values are 50 up to 1000.  |  Read |
|  0x85 | GUARD_TIME*  |  4 | For details refer to Table ‘List of protocol variations’   | Read only  |
| 0x86  |  TRANS_TIMEOUT* | 4  | For details refer to Table ‘List of protocol variations’  |  Read only |
| 0x87  |  PWR_SAVE_TIMEOUT* |  4 | This optional register holds the minimum timeout [ms] after which the device enters power save mode. This timeout gets retriggered with any valid slave address. Once the power save state is initiated the addressing of the slave terminates it and the device returns to normal operation. The new value becomes effective with the next addressing of the slave. However, in case the slave could not accept the new value it indicates its maximum (the new value is too high to be accepted) or minimum (the new value is too low to be accepted) possible value within this register. Therefore it is recommended to read the value back after writing it to be sure the slave did accept the new value.  |  Read/write |
| 0x88  |  SOFT_RESET | 2  | Writing to this register will cause a device reset. This feature is optional  | Write only  |
| 0x89  | I2C_MODE  |  2 | This register holds the current I2C Mode as defined by Table 2-3. The default mode is SM & FM (011B).  |  Read/Write |
|  0x90 | APP_STATE_0  |  4 |  This register holds application specific information (definition of content and behavior is up to the application). The default value at reset is 0x00000000. This register is bound to the application which is linked to by channel 0 (default) of the network layer |  Read only |
| 0x9X  | APP_STATE_X  | 4  | This register holds application specific information (definition of content and behavior is up to the application). The default value at reset is 0x00000000. This register is bound to the application which is linked to by channel X (X = 0x1 … 0xf) of the network layer.   | Read only  |
|  0xA0 | FOR_IFX_USE_1  | 4  | This register can be used for IFX specific purpose during development and evaluation. The content doesn’t impact the protocol execution. For Product releases this register is RFU.  |  Read/Write |
| 0xA0  |  FOR_IFX_USE_2 | 4  |  Refer to register 0xA0 | Read/Write  |


GUARD_TIME* - 
In case the register returns 0xFFFFFFFF the register is not supported and the default values specified in Table ‘List of
protocol variations’ shall be applied.

TRANS_TIMEOUT*, PWR_SAVE_TIMEOUT* - In case the register returns 0xFFFFFFFF the register and its functionality is not supported.

# License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
