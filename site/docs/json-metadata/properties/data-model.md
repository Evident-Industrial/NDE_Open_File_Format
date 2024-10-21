# **Properties** data model

This page details the different JSON objects and arrays with their expected values, associated description and examples related to the **Properties** JSON formatted dataset. 

## **file** object

The **file** object describes generic file creation and modification properties. 

| Property                     | Type   | Description                                                                                                                  |
| :--------------------------- | :----- | :--------------------------------------------------------------------------------------------------------------------------- |
| **createdByAppName**         | string | Name of the application used to create the file                                                                              |
| **createdByAppVersion**      | string | Version of the application used to create the file                                                                           |
| **createdByAppCompany**      | string | Name of the company editing the application used to create the file                                                          |
| **creationDate** `required`  | string | Creation date of the file (date-time as per [RFC 3339](https://datatracker.ietf.org/doc/html/rfc3339#section-5.6))           |
| **creationFormatVersion**    | string | Original File Format Version (X.Y.Z) at the time of creation of the file (in case the file was converted)                    |
| **modifiedByAppName**        | string | Name of the application used to modify the file                                                                              |
| **modifiedByAppVersion**     | string | Version of the application used to modify the file                                                                           |
| **modifiedByAppCompany**     | string | Name of the company editing the application used to modify the file                                                          |
| **modificationDate**         | string | Last modification date of the file  (date-time as per [RFC 3339](https://datatracker.ietf.org/doc/html/rfc3339#section-5.6)) |
| **formatVersion** `required` | string | NDE File Format Version (X.Y.Z)                                                                                              |
| **notice**                   | string | Short string describing the file characteristics (e.g. “Pre-release”)                                                        |
| **description**              | string | A long string describing the file characteristics                                                                            |

Example:

``` json
"file": {
   "createdByAppName": "MXU",
   "createdByAppVersion": "5.17.1.1",
   "createdByAppCompany": "Evident",
   "creationDate": "2024-04-29T14:02:39-04:00",
   "creationFormatVersion": "3.3.0",
   "modifiedByAppName": "MXU",
   "modifiedByAppVersion": "6.0.0",
   "modifiedByAppCompany": "Evident",
   "modificationDate": "2024-10-27T16:15:55-04:00",
   "formatVersion": "4.0.0",
   "notice": "NDE 4.0 Release Version"
},
```

## **methods** array 

The **methods** array lists the NDT methods used in the file. Only the `UT` method is allowed so far. 

Example:

``` json
"methods": ["UT"]
```

---

## Experimental arrays and objects

!!! warning

    The following section contains arrays and objects in an experimental stage. They are not part of an official release yet. They are provided for information only, and we welcome [your feedback](mailto:nde_support@evidentscientific.com). 

### **operators** array 

<!-- md:flag experimental -->

An operator designates anyone interacting with the file. The **operators** array lists the different operators and their properties.

| Property        | Type    | Description                                            |
| :-------------- | :------ | :----------------------------------------------------- |
| **id**          | integer | Unique id of the operator (eg: badge id, employee id…) |
| **name**        | string  | Operator name                                          |
| **role**        | String  | [Inspector, Reviewer, Analyzer, …]                     |
| **companyName** | string  | Company the inspector/operator belongs to              |


``` json
"operator":[
   {
   "id": "hlamb1849",
   "name": "Horace Lamb",
   "role": "inspector",
   "certificationDate": "2022-03-12T20:28:30+01:00",
   "companyName": "Evident" 
   },
   {
   "id": "jfourier1768",
   "name": "Joseph Fourier",
   "role": "reviewer",
   "certificationDate": "1790-03-12T20:28:30+01:00",
   "companyName": "Evident" 
   }
]
```

### **location** object 

<!-- md:flag experimental -->

The **location** object describes the physical location where the acquisition was made. 

| Property        | Type   | Description                                                                                               |
| :-------------- | :----- | :-------------------------------------------------------------------------------------------------------- |
| **companyName** | string | The company/asset owner where the data was collected                                                      |
| **companySite** | string | The specific company site where the data was collected                                                    |
| **gpsLocation** | string | The GPS location where the data was collected (see [ISO6709](https://www.iso.org/fr/standard/75147.html)) |
| **address**     | string | The address where the data was collected                                                                  |
| **city**        | string | The city where the data was collected                                                                     |
| **state**       | string | The state where the data was collected                                                                    |
| **country**     | string | The country where the data was collected                                                                  |

``` json
"location":{
   "companyName": "ACME PETROLEUM",
   "companySite": "ZONE 51",
   "gpsLocation": "48.890451102865384, -122.73358666138213",
   "address": "1751 Rue Richardson suite 7.115",
   "city": "Montreal",
   "state": "QC",
   "country": "Canada" 
}
```

### **component** object

<!-- md:flag experimental -->

The **component** object gives references on the inspected component. 

| Property         | Type   | Description                                    |
| :--------------- | :----- | :--------------------------------------------- |
| **name**         | string | The name of the component under investigation  |
| **model**        | string | The model of the component under investigation |
| **serialNumber** | string | The S/N of the component under investigation   |

``` json
"component":{
   "name": "Crazy_pipe",
   "model": "coated_pipe_300",
   "serialNumber": "CP300-X1524875" 
}
```

### **job** object 

<!-- md:flag experimental -->

The **job** object gives information about the project and business context in which the acquisition was made. 

| Property           | Type   | Description                           |
| :----------------- | :----- | :------------------------------------ |
| **projectName**    | string | The name of the project               |
| **projectId**      | string | The Id or reference of the project    |
| **inspectionName** | string | The name of the inspection            |
| **inspectionId**   | string | The Id or reference of the inspection |

``` json
"job":{
   "projectName": "ACME PIPING",
   "projectId": "KXL_101",
   "inspectionName": "Girth Welds Zone 1",
   "inspectionId": "GW_Z1" 
}
```