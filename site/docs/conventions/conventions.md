---
layout: default
title: Conventions
parent: General Concepts
nav_order: 2
has_children: false

---

# Conventions

## General Concepts

- By the .nde file format’s convention, surface **id:0** is the outer surface (top of plates and outside of pipes) and surface **id:1** is the inner surface (bottom of plates and inside of pipes). 
- Material is considered homogeneous and isotropic by default
- Coupling layers are incapable of transmitting shears wave by default
- Probe with unique resonant frequency

## Units

Angles are expressed in degrees, while all other units in the dataset are in International System (SI) units, expressed in meters and seconds unless otherwise indicated by a "unit" key. For example, the "Bitfield" and "Percent" units are used for the ascan in the dataset object. 

| Quantity                 | Symbol, usual script (common) | Units         |
| ------------------------ | ----------------------------- | ------------- |
| **Distance, positions**  | x, y, z                       | meter [m]     |
| **Time**                 | t                             | second [s]    |
| **Mass**                 | M, m                          | kilogram [kg] |
| **Speed**                | c, v                          | [m/s]         |
| **Angle**                | α, β, γ, θ, φ                 | degree [°]    |
| **Density**              | ρ                             | [kg/$m^3$]    |
| **Gain**                 |                               | dB            |
| **Attenuation**          | A                             | dB            |
| **Fractional Bandwidth** |                               | %             |

 

## Axes and Coordinate System

- **U, V, W**: Is the **surface** coordinate system and describes positions on the specimen surface *(u, v)* and depth *(w)*. It is the main coordinate by which everything is related in each file and their definition depends on the selected **scenario**. Their orientation respect the right-hand rule to ensure consistency across files. 

  - **Origin**: Set on the surface of the specimen and some preferred direction along the surface. For example, **U** can be set along the center line of a weld.

  - The **U** and **V** axis properties are given in the **dataEncodings** object of the domain setup.  

  - The **U** axis, the **primary axis**, is defined by the scenario and its orientation is given by **"uCoordinateOrientation"** in the **"dataEncodings"** object.  
    
  - The **V** axis, the **secondary axis**, is perpendicular to **U** and its orientation can be infered with the right-hand rule from the cross product of **U** and **W**. 
  
  - The **W** axis is normal to the surface and points inside the material. **W** is particularly useful in total focusing method (TFM) acquisition to position the data. However, in most cases, an **"Ultrasound"** axis is used to describe the data instead.  

- **Xw, Yw, Zw**: The wedge coordinate system.  
  
  - **Origin**: Located in the middle and at the bottom of its front (blue axis system in the figure). 

- **Xe, Ye, Ze**: The elements coordinate system.  
  
  - **Origin**: Located in the middle of the first element surface (green axis system in the figure). 

- **X, Y, Z**: Global referential axis. It is independent of the acquisition and serves to position the data on the specimen. These are akin to real-world coordinates defined by the user for the specimen. 
  
  - **Origin**: Arbitrary and stays the same across files for a given specimen. It is usually defined by the user on the specimen with some marking or physical reference in the specimen environment.  
  
  - <ins>**NOTE**</ins>: Currently, the **X**, **Y**, and **Z** axis are not used nor defined in the NDE file, but to show inspection results in 3D, one would have to translate everything to this coordinate system.   

- **Beams Axis**: An axis used in the HDF5 dataset rather than a physical one where each element contains one beam's positions and parameters. It is used in PAUT scenarios when the beams do not fit well in a **U, V** grid. Giving the coordinate by beams simplifies their use in these scenarios. 

- **Ultrasound Axis**: Time-based information sampled by an ultrasonic acquisition system and the specified probe/wedge configuration. 

- **Encoding Axes**: Relates to encoder displacement and are decoupled from the other axes. These are;
  - **Scan axis**: **primary** encoding axis,
  - **Index axis**: **secondary** encoding axis.  


| ![AxisReferential-Wedge_Elements_and_Beam-PAexample.png](/NDE_Open_File_Format/assets/images/conventions/ReferentialDatasetAxes.png){:width="50%"} |
|:---------------------------------------------------------------------------------------------------------------------------------------------------------------:|
| *Summary of axes and general referential system*                                                                                               |

## Wedge Conventions

- The wedge **origin** is centered at the bottom of its front face (blue axis system in the figure). 

- The wedge **skew angle** is defined by the angle between the wedge and **U** axis. 

- Its starting position is given in relation to the **U** and **V** axis with the **uCoordinateOffset** and **vCoordinateOffset** located in the domain setup at **wedges[0].positioning**.   

- The width, height and length of the wedge are found at **wedges[0].angleBeamWedge**. 

| ![AxisReferential-Wedge_Elements_and_Beam-PAexample.png](/NDE_Open_File_Format/assets/images/conventions/AxisReferential-Wedge_Elements_and_Beam-PAexample.png){:width="50%"} |
|:---------------------------------------------------------------------------------------------------------------------------------------------------------------:|
| *Wedge parameters and referential system conventions.*                                                                                               |


| ![AxisReferential-Wedge_SkewAngle.png](/NDE_Open_File_Format/assets/images/conventions/AxisReferential-Wedge_SkewAngle.png){:width="50%"} |
|:---------------------------------------------------------------------------------------------------------------------------------------------:|
| *Isometric views of different skew angles for reference. The skew angle is taken from the U-axis to the wedge Yw-axis.*            |

## Probe Conventions

- Position of the first element is given by; **"primaryOffset"**, **"secondaryOffset"** and **"tertiaryOffset"** found in **wedges[0].angleBeamWedge.mountingLocations**. These three offsets are given in relation to the wedge coordinate system where the primary, secondary, and tertiary offsets are on the **Yw**, **Xw**, and **Zw** axis respectively. 

- **Reference Position** (.Ref): Probes are referenced to other objects (wedge, specimen, etc.) through this point. The reference position is defined from the position of the first element when the probe skew = 0. 


| ![AxisReferential-PlateWeld_2Probres.png](/NDE_Open_File_Format/assets/images/conventions/AxisReferential-PlateWeld_2Probres.png){:width="50%"} |
|:---------------------------------------------------------------------------------------------------------------------------------:|
| *Example of a typical plate scenario with a weld and two probes in relation to the $U$ and $V$ axis.*                  |

| ![AxisReferential-PipeWeld_2Probres.png](/NDE_Open_File_Format/assets/images/conventions/AxisReferential-PipeWeld_2Probres.png){:width="50%"} |
|:-------------------------------------------------------------------------------------------------------------------------------:|
| *Example general weld scenario with an axial weld on a pipe.*                                                        |


