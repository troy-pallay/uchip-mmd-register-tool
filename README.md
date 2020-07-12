# uchip-mmd-register-tool
This repository holds a C program designed to translate MMD register interactions into SPI data. It was specifically written for use with the KSZ9896C, but I believe would also work for the KSZ9897 family of devices.

It is pretty rough in its current state, but the program can translate a text file with mmd, address, and data into a .vhd file filled with the binary that should be clocked over the MOSI line to manage the switch.

I will continue to make changes to the program in order to clean it up and add more functionality.

## Using the program
You can download and compile using gcc:
> gcc -o mmd mmd.c

Before running the program, know that it will attempt to read the file named "mmd_data.txt" and will attempt to write to "buffer.vhd" Make sure that these are available in the same directory that the compiled program is located in.

And example for how "mmd_data.txt" should be formatted is given. It requires 'r'(read) or 'w'(write) as the first character on each line. _**Only mmd writes are currently implemented, and these writes happen on all ports 1-5.**_ The device address must be a 2 digit hex value. The register address must be a 2 digit hex value. The data must be a 4 digit hex value. An example output "buffer.vhd" is also given.

Run:
> ./mmd

You will then be asked to input the number of lines in "mmd_data.txt" After entering the number, press enter for the program to translate.

## To-Do

*Separate main into more easily understood functions and consolidate repetitive code into loops
*Allow user to specify port when performing mmd reads and writes
*Add capability to translate mmd reads
*Add capability to translate standard register reads and writes
