---
layout: default
title: Code Samples
nav_order: 5
has_children: false
description: Code Samples
---

# Code Samples

Here are some code samples in C++ and in Python.
Use the CMake file to build the C++ examples. 

They can be tried using gitHub CodeSpaces, running the CMake file. 

### **Setting up a codespaces**

1- In the main repository folder, create a code space.            <img title="" src="/NDE_Open_File_Format/assets/images/code-samples/2023-08-08-10-59-12-image.png" alt="" width="235" data-align="left">

2- Visual Studio Code CodeSpaces environment                    <img title="" src="/NDE_Open_File_Format/assets/images/code-samples/2023-08-08-21-24-55-image.png" alt="" data-align="left" width="501">

3- Install prerequisites / build using cmake 
 
 Install VSC CMake Tools extension or execute the following command: 

```bash
mkdir build
cd build 
cmake ..
make 
```
4- To execute on linux: 

Use VSC CMake Tools option or execute the following command: 
```bash 
./create-file
./read-ascan
./read-setup
./write-ascan
```

### **read-ascan ( c++ )**

File read example.

[read-ascan sample on github.com](https://github.com/Evident-Industrial/NDE_Open_File_Format/tree/master/examples/read-ascan)

### **read-setup ( c++ )**

Read setup example.

[read-setup sample on github.com](https://github.com/Evident-Industrial/NDE_Open_File_Format/tree/master/examples/read-setup)

### **read-setup ( python )**

Read setup example.

[read-python sample on github.com](https://github.com/Evident-Industrial/NDE_Open_File_Format/tree/master/examples/read-python)

### **create-file ( c++ )**

An example on how to create an a-scan dataset and its domain setup json.

[create-file sample on github.com](https://github.com/Evident-Industrial/NDE_Open_File_Format/tree/master/examples/create-file)

### **write-ascan**

File write example

[write-ascan sample on github.com](https://github.com/Evident-Industrial/NDE_Open_File_Format/tree/master/examples/write-ascan)
