# NDE-Open-File-Format

1. [General Info](#general-info)
2. [Technologies](#technologies)
4. [Collaboration](#collaboration)
5. [FAQs](#faqs)

## General Info
The .nde Open File is a unified and open file format for Non-Destructive Testing.

The file format supports the industry’s NDE 4.0 initiatives by increasing data accessibility, flexibility, and customization potential. This file format aim is to facilitate sharing NDT data between multiple stakeholders. Data is stored using the HDF5 file format combined with a JSON text format to describe the associated metadata.

Please refer to the documentation website to learn more about the file format: https://evident-industrial.github.io/NDE_Open_File_Format/


## Technologies 
**NDE open file** format is base on HDF5. To learn more about hdf5, you can visit this link: https://www.hdfgroup.org/solutions/hdf5/. 

To help you navigate NDE files, you can download the hdfView tool: https://www.hdfgroup.org/downloads/hdfview/ or use the online hdf5 tool: https://myhdf5.hdfgroup.org/

The **examples** folder of this repository: https://github.com/Evident-Industrial/NDE_Open_File_Format/tree/main/examples are based on C++17 and Python examples on how to use HDF5. 

The C++ examples can be run with [CMake](https://cmake.org/) version >= 3.12. See Code Samples section for more info: https://evident-industrial.github.io/NDE_Open_File_Format/docs/code-samples/code-samples.html

## Collaboration
Contact the Evident Industrial organization for any question: nde_support@evidentscientific.com

## FAQs
1. **What does NDE stand for?**

Non Destructive Evaluation 

2. **What technology does NDE open file format use ?** 

HDF5 : https://www.hdfgroup.org/solutions/hdf5/

