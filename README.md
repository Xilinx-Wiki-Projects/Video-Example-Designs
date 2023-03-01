# Video-Processing-Sub-System-reference-Design
VPSS Reference Design created with HDMI2.1 Solution

/******************************************************************************
* Copyright (C) 2018 – 2021 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/
## Setup and Vitis Project Bring up
1.   After completing bringing up the Vivado project and generating the xsa (*link to vivado github doc*)
2.   Generate a Vitis Project using the resulting xsa
3.   Export the HDMI 2.1 version 2022.1 Example Design ( driver name : v_hdmi_rxss1) 
4.   Once loaded, export files from the src directory to the src directory of the Project. (
     * Note: Extract and copy all the files from static_images.7z to src directory. 
5.   Click on "Yes to All" if prompted to replace the files. 
6.   Clean and build the Build the Project
7.   Run the project using JTAG or use the BOOT.BIN to load the app using SD-card mode.


User can refer the following wiki page for the details of the design and test results

https://confluence.xilinx.com/display/~ashokkum/Video+Processing+Sub+System+Reference+Design
