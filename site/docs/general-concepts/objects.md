---
hide:
  - toc
---

# Objects

_Objects_ refers to the various entities that can be defined within the file. They can include groups and attributes associated with the objects. Objects are organized in a hierarchical structure, allowing for efficient storage and retrieval of complex data, such as setup parameters and acquisition-related information.

All .nde files regardless of their technology are constructed with the following basic objects : 

- acquisitionUnits
- probes
- wedges
- motionDevices
- dataEncodings
- specimens
- groups

Note that : 

- All objects have an ‘id’ attribute
- In the .json file objects are expressed with a 's' and put in a list (even if there's only one object)
    - In the JSON file list items are in []
- Reference to other objects are made by expressing the name of the object (without the 's') + 'Id' 
    - For example a reference to an object in the probes list would be 'probeId'
- Other objects than the basic objects exist within the file. These objects are included in some specific base object. For example, 'mountingLocation' is an object found in 'wedge' object.
- Object can be either specialized or basic. For example 'phasedArrayLinear' is a specialization of a 'probe' object. Specialized objects retain all the attributes of the source object but add new attributes under the specialization level.

| ![Objects_Basic.png](../assets/images/general-concepts/objects/Objects_Basic.png){width="50%"} |
|:---------------------------------------------------------------------------------------------------------------------:|
| *Example of probe object with basic and specialization attributes.*

| ![Objects_Referencing.png](../assets/images/general-concepts/objects/Objects_Referencing.png){width="50%"} |
|:---------------------------------------------------------------------------------------------------------------------:|
| *Example of probe object with references to associated wedge object and mountingLocations object.*    
