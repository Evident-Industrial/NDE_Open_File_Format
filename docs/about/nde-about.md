---
layout: default
title: What is the .nde format? 
parent: About the .nde format 
nav_order: 1
---

# What is the .nde format 

The .nde file format is a modality agnostic file format for storage of non-destructive testing data. It provides a relatively simple file structure for most supported use cases while enabling more complex future solutions. The file is associated wit a standardized referential system related to the inspection componennt as well as standradized definitions for scenarios and objects. Data is stored using the HDF5 file format combined with a JSON text format to describe the associated metadata. 

Combining simplicity while enabling complex use cases is achieved by the following two constructs: 
- **Scenarios**, which define by convention some aspects of the configuration
- **Objects**, which describe physical components at the appropriate level of complexity

Each file is structured with two sections: 
- **Applications**: A proprietary acquisition software-specific section. This section is not meant for use by .nde readers. 
- **Domain**: Includes the standardized dataset information and standardized objects described in an embedded JSON file. 