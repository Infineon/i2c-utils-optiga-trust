# I2C Utilities for OPTIGA™ Trust secure IC
by Timothy Yong

* [About](#about)
  * [Prerequisites](#prerequisites)
  * [Contents of the package](#contents_of_package)
  * [Getting Started](#getting_started)
* [Usage](#usage)
  * [trustx_reg](#reg)
  * [trustx_scan](#scan)
  * [trustx_softreset](#softreset)
  * [trustx_w_addr](#w_addr)
* [Known issues](#known_issues)
* [Registers](#registers)
* [License](#license)

## <a name="about"></a>About

This is a simple test tools for OPTIGA™ Trust I2C interface on Linux platform.
    
**_WARNING! This program can confuse your I2C bus, cause data loss and worse!_**

It will send a I2C read command from address 0x00 to 0x7F.
    
When probing I2C address, the program will send three attempt read command at the interval of 500us before moving to the next address.
A detect is flag when there is an ackonwlegde from the slave.   

### <a name="prerequisites"></a>Prerequisites

To build and run the tools you need GCC and a Linux system

Tested platforms:
  - Raspberry PI 3 on kernal 4.14

### <a name="contents_of_package"></a>Contents of Package

This tools consists of the following files & directory:

	.
	├── bin	                           /* all executable file is store here	            */ 	       
	├── lib                            /* Library Component for Trust X                 */
	│   ├── common                     /* Common files used by others library component */
	│   │   ├── include                /* Common include directory                      */
	│   │   │   ├── trustx_debug.h     // Header for Debuging 
	│   │   │   ├── trustx_error.h     // Header for Error code
	│   │   │   ├── trustx_platform.h  // Header related to platform 
	│   │   │   ├── trustx_reg.h       // Header related to Trust X register
	│   │   │   └── trustx_util.h      // Header for helper rountine 
	│   │   └── trustx_util.c          // Helper rountine
	│   └── interface                  /* Interface library component                   */   
	│       ├── include                /* Interface include directory                   */
	│       │   └── trustx_interface.h // Header for Trust X interface rountine         */
	│       └── TrustX_Interface.c     // Trust X interface rountine                    */
	├── Makefile                       // Makefile
	├── README.md                      // Markdown read me file
	├── README.txt                     // Text read me file (this file)
	└── sample                         /* All sample executeable source code            */
	    ├── trustx_reg.c               // read register source
	    ├── trustx_scan.c              // scan i2c source
	    ├── trustx_softreset.c         // Softreset source
	    └── trustx_w_addr.c            // change i2c address source

### <a name="getting_started"></a>Getting Started

In order to used the tools, you need to compile it first:
1. Switch to the directory with the Makefile
2. Compile the source code by typing the following command:
```console
$ make
```
3. On sucessful build the executeable is store in bin directory   
4. To clear up the project used the following command:
```console
$ make clean
```

## <a name="usage"></a>Usage
### <a name=reg></a>trustx_reg
Read/Write to register 

```
option:-
    -a Set I2C Address (Default 0x30) 
    -b Set I2C bus (Default /dev/i2c-1) 
    -w <filename> 
    -r <0xnn> Select Register
    -R Read all register (except DATA[0x80]) 
    -h Print is help menu
```
    
### <a name=scan></a>trustx_scan

Scan I2C address from 0x00 to 0x7F

```
option:-
    -b Set I2C bus (Default /dev/i2c-1) 
    -h Print is help menu
```

**_WARNING! This program can confuse your I2C bus, cause data loss and worse!_**

It will send a I2C read command from address 0x00 to 0x7F.
    
When probing I2C address, the program will send three attempt read command at the interval of 500us before moving to the next address.
A detect is flag when there is an ackonwlegde from the slave. 

### <a name=softreset></a>trustx_softreset
Send a soft reset command to Trust X

```
option:- 
    -a Set I2C Address (Default 0x30) 
    -b Set I2C bus (Default /dev/i2c-1)  
    -h Print this help menu
```

### <a name=w_addr></a>trustx_w_addr

Change Trust X I2C address

```
option:- 
    -a Set I2C Address (Default 0x30) 
    -b Set I2C bus (Default /dev/i2c-1) 
    -n Set New I2C Address (Default 0x30)
    -p Set New I2C Address persistent  
    -h Print this help menu
```
### <a name="known_issues"></a> Known issues
* `trustx_w_addr` sometime return fail but address is changes.
* `trustx_reg` option -w <filename> not tested

## <a name="registers"></a> Registers

Below you can find a table of Infineon standard register set. For details plese have a look on Infineon I2C protocol specification [ver. 1.65](https://github.com/Infineon/Assets/raw/master/PDFs/IFXI2CProtocol_v1.65.pdf) (PDF)

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

## <a name="license"></a> License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
