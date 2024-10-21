## Convert HDF5 root attributes to the new JSON Properties structure

The following correspondancy can be made between old HDF5 attributes and the new Properties JSON dataset. Note that the **methods** array lists was added to specify the NDT methods covered in the file (as described by [ASNT](https://www.asnt.org/what-is-nondestructive-testing/methods)) and should be set to "UT" for all files in version 3.3. and earlier. 


| :nde-3-3: HDF5 Attributes                               | :nde-4-0: Properties dataset                                     |
| ------------------------------------------------------- | ---------------------------------------------------------------- |
| **Original Application Name** - HDF5 Attribute at /     | **createdByAppName** - in Properties JSON under file object      |
| **Original Application Version** \- HDF5 Attribute at / | **createdByAppVersion** - in Properties JSON under file object   |
| **Original Company Name** \- HDF5 Attribute at /        | **createdByAppCompany** - in Properties JSON under file object   |
| **Date created** \- HDF5 Attribute at /                 | **creationDate** - in Properties JSON under file object          |
| **Original Format Version** \- HDF5 Attribute at /      | **creationFormatVersion** - in Properties JSON under file object |
| **Application Name** - HDF5 Attribute at /              | **modifiedByAppName** - in Properties JSON under file object     |
| **Application Version** \- HDF5 Attribute at /          | **modifiedByAppVersion** - in Properties JSON under file object  |
| **Company Name** \- HDF5 Attribute at /                 | **modifiedByAppCompany** - in Properties JSON under file object  |
| **Date modified** - HDF5 Attribute at /                 | **modificationDate** - in Properties JSON under file object      |
| **Format Version** \- HDF5 Attribute at /               | **formatVersion** \- in Properties JSON under file object        |
| **Notice** \- HDF5 Attribute at /                       | **notice** - in Properties JSON under file object                |
| N/A                                                     | **methods** \- in Properties JSON, methods array                 |


Here is an example of a Properties dataset located at the root of the HDF5 structure. 

``` json
{
   "file":{
      "createdByAppName": "MXU",
      "createdByAppVersion": "5.18.1.0",   
      "createdByAppCompany": "Evident",   
      "creationDate": "2024-03-12T20:28:30+01:00",
      "creationFormatVersion": "4.0.0-Dev",    
      "modifiedByAppName": "MXU",
      "modifiedByAppVersion": "5.18.1.0",   
      "modifiedByAppCompany": "Evident",   
      "modificationDate": "2024-03-12T20:32:30+01:00",
      "formatVersion": "4.0.0-Dev",    
      "notice": "Pre-release Version",
   },
   "methods":["UT"]
}
```