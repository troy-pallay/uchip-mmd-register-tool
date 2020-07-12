# uchip-mmd-register-tool
This repository holds a C program designed to translate MMD register interactions into SPI data. It was specifically written for use with the KSZ9896C, but I believe would also work for the KSZ9897 family of devices.

In its rough, current state, the program can translate a text file with mmd, address, and data into a .vhd file filled with the binary that should be clocked over the MOSI line to manage the switch.

I will continue to make changes to the program in order to clean it up and add more functionality.

## Using the program
You can download and compile the 
