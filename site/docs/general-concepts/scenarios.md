---
layout: default
title: Scenarios
parent: General Concepts
nav_order: 3
---

# Scenarios
Scenarios introduce a set of conventions specific to a given use case enabling a simple description of the specimen and associated probe and wedge positioning. 

- **General Mapping**
    - The $(u,v)$ surface coordinates define a position on the surface but do not directly indicate an orientation of the object that is positioned. The orientation and the origin are set by the user (usually with an external reference on the specimen such as a marker.)

| ![AxisReferential-Raster_Plate.png](/NDE_Open_File_Format/assets/images/conventions/AxisReferential-Raster_Plate.png){:width="25%"} |
|:---------------------------------------------------------------------------------------------------------------------:|
| *Raster example with the $U$ and $V$ axis.*                                                                |



- **General Weld** 
    - General weld scenarios are distinct mainly by their reference axis, the **U axis**, located in the middle of the weld.
    - For pipe geometry, the orientation of the weld is defined in relation to the pipe axis. With an angle of 0° for an axial weld and 90° for a circumferential one. Any angle in between describes a helix weld.


| ![AxisReferential-PipeAxialWeld.png](/NDE_Open_File_Format/assets/images/conventions/AxisReferential-PipeAxialWeld.png){:width="50%"} | 
| ![AxisReferential-PipeCircWeld.png](/NDE_Open_File_Format/assets/images/conventions/AxisReferential-PipeCircWeld.png){:width="50%"} | 
|:-----------------------------------------------------------------------------------------------------------------------------------:| 
| *The weld angle is defined in relation to the pipe axis.*                                                                |