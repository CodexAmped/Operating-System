# Operating System (OS)

This is 64 bit Operating System, an x86 compatible OS which is multiboot2 compliant and can expand to other architectures and bootloaders.
It is primarily written in the C language and in Assembly for hardware specific code.

## Tools
    ~ Docker: To simplify the build process
    ~ Qemu: To emulate operating system
    ~ NSAM: Compile Assembly code
    ~ Grub: Generate ISO file
    ~ Gcc-cross-x86_64 Compiler: Build C files

### Build 

Starting Folder: WORKDIR /root/env

To build the docker image, you can simply run:

```
docker build name_of_your_root_folder -t tagname_of_your_image
```
And to spin up an instance of this image also known as container,
If you are on Mac or Linux, you can run:

```
docker run --rm -it -v $pwd:/root/env tagname_of_your_image
```
If you are on Windows(CMD), you can run:

```
docker run --rm -it -v %cd%:/root/env tagname_of_your_image
```
If you are on Windows(PowerShell), you can run:

```
docker run --rm -it -v "${pwd}:/root/env" tagname_of_your_image
```
NOTE: If you are having a trouble with an unshared drives, ensure your docker daemon has access to the drive your the development environment is in. For Docker Desktop, this is in "Settings > Shared Drives" or "Settings > Resources > File Sharing".

Build for x86:
```
make build-x86_64
```
To leave the build environment, enter `exit`.

# Source Folder

This holds all of the implementation files. The entry point into the operating system is x86_64 assembly code, which is integrated with bootloader2.

## Header File

* header.asm

Inside this assembly file, we needed to add some data(magic data) which is included inside the operating system binary. This magic data is necessary so that bootloaders can understand that we have an operating system that can be run in your computer.

The core responsibilty of bootloader is to locate an operating system to a specific computer, whether on the hard-drive, CD or on the USB-drive. And once the bootloader has found an operating system it will then start. This is because the operating sytem is not the first thing that start in a computer but rather the bootloader.

Here we have followed the bootloader2 specification, which most bootloader supports.

## Main File

* main.asm

This is the entry point to operating system. 

## Linker & Grub Configurations
* linker.ld

We use this file to describe how to link an operating system together. The entry point is defined in the main.asm file, which can be used to link the operating system. And defined sections in the linker file we start with 1M in, and we have multiboot header and all  the CPU instructions.

* grub.cfg

This will create an ISO file out of our operating system kernel binary. An ISO file is a format for holding an operating system. 

# Emulation

Using Qemu, you can simulate operating system(Note: You need to add qemu to your path)
