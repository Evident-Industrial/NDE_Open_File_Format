# NDE-Open-File-Format

1. [General Info](#general-info)
2. [Technologies](#technologies)
4. [Collaboration](#collaboration)
5. [FAQs](#faqs)

## General Info
The .nde open file is a unified and open file format for nondestructive testing (NDT).

The file format supports the industry’s NDE 4.0 initiatives by increasing data accessibility, flexibility, and customization potential. The aim of this file format is to facilitate sharing NDT data between multiple stakeholders. Data is stored using the HDF5 file format combined with a JSON text format to describe the associated metadata.

Please refer to this documentation to learn more about the file format: https://evident-industrial.github.io/NDE_Open_File_Format/


## Technologies 
The **NDE open file** format is base on HDF5. To learn more about HDF5, visit: https://www.hdfgroup.org/solutions/hdf5/. 

To help you navigate NDE files, you can download the HDFView tool: https://www.hdfgroup.org/downloads/hdfview/ or use the online HDF5 tool: https://myhdf5.hdfgroup.org/

The **examples** folder of this repository https://github.com/Evident-Industrial/NDE_Open_File_Format/tree/main/examples are based on C++17 and Python examples of how to use HDF5. 

The C++ examples can be run with [CMake](https://cmake.org/) version >= 3.12. See the Code Samples section for more info: https://evident-industrial.github.io/NDE_Open_File_Format/docs/code-samples/code-samples.html

## Collaboration
If you have any questions, contact Evident at nde_support@evidentscientific.com

## FAQs
1. **What does NDE stand for?**

Non destructive evaluation 

2. **What technology does the NDE open file format use ?** 

HDF5 : https://www.hdfgroup.org/solutions/hdf5/

