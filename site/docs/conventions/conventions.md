---
layout: default
title: Conventions
nav_order: 2
has_children: true
---

# Conventions

## Plate Conventions

By the .nde file format’s convention, surface id:0 is the outer surface (or top for plates) and surface id:1 is the inner surface (or bottom for plates). 

### Axis and Coordinate System Definitions 

- **U, V, W**: Local or **surface** coordinate system. It is the main coordinate by which everything is related in each file. It describes positions on the specimen surface *(u, v)* and depth *(w)*. 

    - **origin**: Set on the surface of the specimen and some preferred direction along the surface. For example, U can be set along the center line of a weld. 

    - The **U** axis is defined by the scenario. In a general mapping scenario, it can be described as the "active" axis, which often corresponds to the Scan axis and is the one on which probes are usually swept in one-line scan acquisition. For a weld scenario, **U** is defined along the weld.   

    - The **V** axis is perpendicular to **U**. In most cases, it corresponds to the Index axis in raster acquisition. 

    - The **W** axis is normal to the surface and points inside the material. **W** is particularly useful in total focusing method (TFM) acquisition to position the data. However, in most cases, an **"Ultrasound"** axis is used to describe the data instead.  

    - The **U** and **V** axis properties are given in the **dataEncodings** object of the domain setup.  

- **Xw, Yw, Zw**: The wedge coordinate system.  

    - origin: Located in the middle and at the bottom of its front (blue axis system in the figure). 

- **Xe, Ye, Ze**: The elements coordinate system.  

    - origin: Located in the middle of the first element surface (green axis system in the figure). 

- **X, Y, Z**: Global referential axis. It is independent of the acquisition and serves to position the data on the specimen. These are akin to real-world coordinates defined by the user for the specimen. 

    - **origin**: Arbitrary and stays the same across files for a given specimen. It is usually defined by the user on the specimen with some marking or physical reference in the specimen environment.  

    - <ins>**NOTE**</ins>: Currently, with NDE format version 3.1.0, the **X**, **Y**, and **Z** axis are not used nor defined in the NDE file, but to show inspection results in 3D, one would have to translate everything to this coordinate system.   

- **beams axis**: An axis used in the HDF5 dataset rather than a physical one where each element contains one beam's positions and parameters. It is used in PAUT scenarios when the beams do not fit well in a **U, V** grid. Giving the coordinate by beams simplifies their use in these scenarios. 

- **Ultrasound axis**: Time-based information sampled by an ultrasonic acquisition system and the specified probe/wedge configuration. 


## Wedge 

- The wedge **origin** is centered at the bottom of its front face (blue axis system in the figure). 

- The wedge **skew angle** is defined by the angle between the wedge and **U** axis. 

- Its starting position is given in relation to the **U** and **V** axis with the **uCoordinateOffset** and **vCoordinateOffset** located in the domain setup at **wedges[0].positioning**.   

- The width, height and length of the wedge are found at **wedges[0].angleBeamWedge**. 


## Probes

- Position of the first element is given by; **"primaryOffset"**, **"secondaryOffset"** and **"tertiaryOffset"** found in **wedges[0].angleBeamWedge.mountingLocations**. These three offsets are given in relation to the wedge coordinate system where the primary, secondary, and tertiary offsets are on the **Yw**, **Xw**, and **Zw** axis respectively. 

-  **Reference Position** (.Ref): Probes are referenced to other objects (wedge, specimen, etc.) through this point. The reference position is defined from the position of the first element when the probe skew = 0. 


| ![Figure1-AxisReferential-PlateWeld_2Probres.png](/NDE_Open_File_Format/assets/images/conventions/Figure1-AxisReferential-PlateWeld_2Probres.png) | 
|:--:| 
| *Figure 1 – Example of a typical plate scenario with a weld and two probes in relation to the $U$ and $V$ axis.* |


| ![Figure2-Rster.png](/NDE_Open_File_Format/assets/images/conventions/Figure2-Rster.png) | 
|:--:| 
| *Figure 2 - Raster example with the $U$ and $V$ axis.* |


| ![Figure3-AxisReferential-Wedge_Elements_and_Beam-PAexample.png](/NDE_Open_File_Format/assets/images/conventions/Figure3-AxisReferential-Wedge_Elements_and_Beam-PAexample.png) | 
|:--:| 
| *Figure 3 - Wedge parameters and referential system conventions.* |


| ![Figure4-AxisReferential-Wedge_SkewAngle[TopView].png](/NDE_Open_File_Format/assets/images/conventions/Figure4-AxisReferential-Wedge_SkewAngle[TopView].png) | 
|:--:| 
| *Figure 4 – Top views of different skew angles for reference. The skew angle is taken from the U-axis to the wedge Yw-axis.* |


| ![Figure5-Isometrics-views.png](/NDE_Open_File_Format/assets/images/conventions/Figure5-Isometrics-views.png) | 
|:--:| 
| *Figure 5 – Isometric views of different skew angles for reference. The skew angle is taken from the U-axis to the wedge Yw-axis.* |