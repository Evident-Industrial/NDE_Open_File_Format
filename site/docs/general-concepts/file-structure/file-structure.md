---
layout: default
title: File Structure
parent: General Concepts
nav_order: 1
---

# File structure

## *Technologies*

The .nde file format is built on the HDF5 opensource library. Visit
[https://www.hdfgroup.org](https://www.hdfgroup.org) for more information.

The HDF5 data hierarchy is complemented by Java Script Object Notation (JSON) in two
ways:

·        JSON file is embedded directly in the file structure, setup parameters are obtained
in an easy-to-read way and are quick to access.

·        JSON schema files are provided to manage file compatibility.

## *General Structure*

The .nde file format provides a relatively simple file structure with a container for
non-standardized application usage (application) and a standardized container
for the data and setup or contextual information that describes the data
(domain).

| **Applications** |
| --- | --- |
| Description      | A proprietary acquisition software-specific section. This section is not meant for use by .nde readers and can be structured as per the acquisition softwares’ specifications.                                                                                                                                                                                              |
| Open             | No.                                                                                                                                                                                                                                                                                                                                                                         |
| Usage            | Each Application that creates/modifies the data file can add specific information here. This container can be used as deemed necessary by the application software that creates the nde file including but not limited to storing setup information, customized data or metadata, etc… This section is not used for information that should be shared between applications. |

| **Domain** |
| --- | --- |
| Description      | Includes the standardized dataset information and standardized setup information described in an embedded JSON file. |
| Open             | Yes. |
| Usage            | The information in this section is standardized and versioned. |

![GeneralStructure.png](/NDE_Open_File_Format/assets/images/general-concepts/GeneralStructure.png){:width="50%"}

## *Interpreting the data*

Instead of exploiting
HDF5 attributes the contextual or setup information that is essential to
completely interpret the data is contained in the Setup JSON file.

This embedded JSON file provides an easy-to-read way to obtain all setup information
and is quick to access in part due to it’s flat structure as compared to exploiting
the HDF attributes at each level of the data tree.

Each group contains a dataset description and configuration described in the JSON.

JSON Group object example containing dataset and a phased array configuration.

```text
{
 "groups": [
    {
      "id": 0,
      "name": "GR-1",
      "paut": {                   // <---- Phased Array Configuration
        "beams": [
            //...
        ]        
        //...
      },
      "dataset": {                // <---- dataSet Information
        "ascan": {
          "amplitude": {
            "dataSampling": {...},
            "dataValue": {...},
            "path": "/Domain/DataGroups/0/Datasets/0/Amplitude",
            "dimensions": [...]
          },
          "status": {
            "dataValue": {...},
            "path": "/Domain/DataGroups/0/Datasets/0/Status",
            "dimensions": [...]
          }
        },
        "storageMode": "Paintbrush"
      }
    }
  ]
}
```

## *Scenarios and Objects*

Designed to offer both simplicity and extensibility, the nde file format includes the
concepts of scenarios and objects.

[**Scenarios**](/NDE_Open_File_Format/docs/general-concepts/scenarios.html) : define by convention some aspects of the
configuration, notably the reference coordinate system.

[**Objects**](/NDE_Open_File_Format/docs/general-concepts/objects/objects.html) : describe components such as supported probe
types or focal law configurations at the appropriate level of complexity.
