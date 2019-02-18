# Infineon I2C Protocol Utilities

This repositiry provides a set of utilities to easier an interaction with a OPTIGA™ Trust device.
These utilities uinteract with the Infineon I2C protocol implementation.

# About the Protocol

The Infineon I2C Protocol is a multilayered protocol stack over an I2C bus used to communicate and transfer commands from host microcontroller to a security IC. It follows the [OSI model](https://en.wikipedia.org/wiki/OSI_model). The protocol is defined for point-to-point connection with low failure rate. It is optimized for minimum RAM usage and minimum overhead to achieve maximum bandwidth, but also offers error handling and flow control.

# Supported options

* Perform a software reset
* Scan i2c bus to find a security IC
* Assign a new address to a security IC
* Update a register value

# License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
