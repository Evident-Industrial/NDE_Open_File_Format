# **Setup** data model

This page and its subsections detail the different JSON objects and arrays with their expected values, associated description and examples related to the **Setup** JSON formatted dataset. 

The data model presented in this page sub-sections follows the hierarchical structure of the **Setup** JSON formatted dataset:

``` json
{
"$schema": "./Setup-Schema-4.0.0.json",
"version": "4.0.0",
"scenario": "...",
"groups": [],
"acquisitionUnits": [],
"motionDevices": [],
"dataMappings": [],
"specimens": [],
"probes": [],
"wedges": [],
}
```


Note that: 

- Most of the objects have an ‘id’ attribute
- Arrays are expressed with a 's' (even if there's only one object)
- Reference to an array item is made by expressing the name of the array (without the 's') + 'Id' 
  - For example a reference to an object in the probes list would be `probeId`