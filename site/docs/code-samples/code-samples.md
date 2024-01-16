---
layout: default
title: Code Samples
nav_order: 5
has_children: false
description: Code Samples
---

# Code Samples

Here are some code samples in C++ and in Python.

Use the CMake file to build the C++ examples. The C++ examples use hdf5 1.14.1. You can change the hdf5 version in the CMakeLists.txt. 

You can try them using gitHub CodeSpaces, running the CMake file. 

### **Setting up a codespace**

1. In the main repository folder, create a codespace.            <img title="" src="/NDE_Open_File_Format/assets/images/code-samples/2023-08-08-10-59-12-image.png" alt="" width="235" data-align="left">

2. Open the Visual Studio Code Codespaces environment.                    <img title="" src="/NDE_Open_File_Format/assets/images/code-samples/2023-08-08-21-24-55-image.png" alt="" data-align="left" width="501">

3. Install prerequisites / build using CMake. 
 
 Install VSC CMake Tools extension or execute the following command: 

```bash
mkdir build
cd build 
cmake ..
make 
```

4. Depending on the hdf5 version you may need to upgrade your cmake version. To upgrade codespace cmake version you can execute the following commands: 

```bash
sudo apt purge --autoremove cmake
wget https://github.com/Kitware/CMake/releases/download/v3.20.2/cmake-3.20.2.tar.gz #select your desired cmake version here: https://github.com/Kitware/CMake/releases/download/
tar -zxvf cmake-3.20.2.tar.gz
cd cmake-3.20.2
./bootstrap
make
sudo make install
```

5. To execute on linux: 

Use VSC CMake Tools option or execute the following command: 
```bash 
./create-file
./read-ascan
./read-setup
./write-ascan
```

### **read-ascan ( c++ )**

File read example:

[read-ascan sample on github.com](https://github.com/Evident-Industrial/NDE_Open_File_Format/tree/master/examples/read-ascan)

### **read-setup ( c++ )**

Read setup example:

[read-setup sample on github.com](https://github.com/Evident-Industrial/NDE_Open_File_Format/tree/master/examples/read-setup)

### **read-setup ( python )**

Read setup example.

[read-python sample on github.com](https://github.com/Evident-Industrial/NDE_Open_File_Format/tree/master/examples/read-python)

### **create-file ( c++ )**

An example of how to create an A-scan dataset and its domain setup json:

[create-file sample on github.com](https://github.com/Evident-Industrial/NDE_Open_File_Format/tree/master/examples/create-file)

### **write-ascan**

File write example:

[write-ascan sample on github.com](https://github.com/Evident-Industrial/NDE_Open_File_Format/tree/master/examples/write-ascan)
