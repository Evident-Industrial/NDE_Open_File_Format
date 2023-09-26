---
layout: default
title: Conventions
parent: General Concepts
nav_order: 2
has_children: false

---

# Conventions

## Units

Angles are expressed in degrees, while all other units in the dataset are in International System (SI) units, expressed in meters and seconds unless otherwise indicated by a "unit" key. For example, the "Bitfield" and "Percent" units are used for the ascan in the dataset object. 

| Quantity                 | Symbol, usual script (common) | Units         |
| ------------------------ | ----------------------------- | ------------- |
| **Distance, positions**  | X, Y, Z                       | meter [m]     |
| **Time**                 | t                             | second [s]    |
| **Mass**                 | M                          | kilogram [kg] |
| **Speed**                | c                         | [m/s]         |
| **Angle**                | α, β, γ, θ, φ                 | degree [°]    |
| **Density**              | ρ                             | [kg/$m^3$]    |
| **Gain**                 | G                              | dB            |
| **Attenuation**          | A                             | dB            |
| **Fractional Bandwidth** | FBW                              | %             |


## Axes and Coordinate System
### About scenarios

The relationship between objects of the nde file (specimen, probe, wedge, encoder) is defined by inspection scenarios. 

### $(U,V,W)$; surface coordinates and depth

In scenarios in which probe positioning is in direct relation to the surface, the position on the surface of a specimen, $(X, Y, Z)$ in global coordinates, is transformed in $(U,V)$ surface orthogonal curvilinear coordinates. Take note that depending on the scenario the $(U,V)$ may be directly in distance unit (meter) but this is not systematic. 

The use of $(U,V)$ coordinates is enforced as a way to disambiguate the notions of “scan axis” and “index axis” which are interpreted depending on the scenario. 

To the $(U,V)$ surface mapping coordinates a depth axis $W$ is added. The depth $W$ is defined as being normal to the local $(U,V)$ coordinates and follows the right hand rule for sign definition, resulting in a $(U,V,W)$ coordinate system 

- The $W$ axis is normal to the surface and always points inside the material.

- The $U$ axis is defined relative to the specimen's feature (per scenario). Its orientation is arbitrary.

- The $V$ axis is perpendicular to $U$ and its orientation can be infered with the right-hand rule from the cross product of $U$ and $W$. 
  
### Other coodinate systems
- $(X,Y,Z)$: Global referential axis. 
  - It is independent of the acquisition and serves to position the data on the specimen in the real world.
  - *Origin and orientation*: Arbitrary and stays the same across files for a given specimen. It is usually defined by the user on the specimen with some marking or physical reference in the specimen environment.
  - <ins>*NOTE*</ins>: Currently, the $X$, $Y$, and $Z$ axis are not used nor defined in the NDE file, but to show inspection results in 3D, one would have to translate everything to this coordinate system. 

- $(X_w, Y_w, Z_w)$: The wedge coordinate system. 

    - Note that terms *wedge* is used to describe all devices that ensure a constant positionning of a probe relative to an inspected surface. 
    - The wedge is typically positionned directly on the surface $(U,V)$ and thus link the probe position to the part.
    - *Origin and orientation*: See appropriate wedge object conventions with the appropriate technology (ex. UT/PAUT)  for details.

- $(U_e, V_e)$: The probe elements coordinate system
  -  On the probe surface (i.e. they are surface coordinates)
  - *Origin and orientation*: See appropriate probe object conventions with the appropriate technology (ex. UT/PAUT) for details.

- Beams Axis:
    -  An axis used in the HDF5 dataset rather than a physical one where each element contains one beam's positions and parameters. It is used in PAUT scenarios when the beams do not fit well in a $U$, $V$ grid. Giving the coordinate by beams simplifies their use in these scenarios. 

- Ultrasound Axis: 
    - Time-based information sampled by an ultrasonic acquisition system. The positionning in the global coordinate require accounting for ray tracing and part velocities.

- Encoding Axes: 
    - Relates to encoder displacement, coupling to specimen and/or global coordinates is scenario dependant.

## Data mapping versus the specimen (dataEncoding) conventions

### General Concepts

Independantly of the non-destructive evaluation method, there's always a need to relate acquisition data to the inspected specimen in terms of positionning. There exist, however, diametrically opposed use case calling for adapted methods to achieve this relationship. For example, most PAUT weld inspection with scanners will relate the data positionning relative to the surface itself with a constant resolution. On the other hand, one could acquire and store phased array acquisition with a 6 axis robot and use complex post-processing methods to achieve inspection data positionning. The **dataEncoding** object class specify how inspection data relates to the specimen. 

### **DiscreteGrid** object

With **discreteGrid** the relationship between data and the specimen is directly made through the scenario coordinate system (for example $(U,V)$ in the explanations below). Pratically, this is done by adding dimensions to the dataset corresponding to each of the scenario coordinate system axis. 

- Hypothesis:
    - Only one dataset of a given type, for a given group, is saved at each of the scenario coordinates.

#### [**storagemode**](/NDE_Open_File_Format/docs/schema_doc.html#groups_items_oneOf_i1_dataset_storageMode).

There are two disctinct ways to work with **discreteGrid** when storing a given dataset. 

**storageMode:"Independent"** is used to store the complete data acquisition sequence in reference to a $(U,V)$ positionning corresponding to a global acquisition device positionning. For example, a scanner comprizing many different PAUT probes each individually offset relative to the $(U,V)$ reference system could all relate to the same discreteGrid with **independant** storage mode. In this case the positionning of the data on or in the specimen requires some processing of individual beams or sensors position.

**storageMode:"Paintbrush"** is used to store individual beam or sensor information directly on the corresponding $(U,V)$ position. Practically, **Paintbrush** is only possible under some hypothesis:
- All beams or sensors operates under the same condition. For example, paint brush is possible with linear PE PAUT but is not with sectorial PE PAUT.
- All beams or sensors can be associated with a surface position. For example, FMC acquisition can't be stored as Paintbrush because individual ascan of the FMC don't have defined surface positionning.
- Beams or sensors surface positionning should fit perfectly on the underlying coordinate system grid. Accordingly, the **discreteGrid** coordinate system grid typically has to be created according to a probe and scanning system characteristic for a **Painbrush** storage.

The obvious advantage of **Paintbrush** storage is that it natively is mapped on a specimen surface.
  
### **FullCycle** object

In this case, all acquisition cycles are kept and so are the corresponding positionning from all available positionning devices.


## UT/PAUT conventions

### General Concepts and hypothesis

- Material is considered homogeneous and isotropic by default
- Coupling layers are incapable of transmitting shears wave by default
- Probe with unique resonant frequency by default


## UT/PAUT Wedge Conventions
### **angleBeamWedge** object
- Hypothesis: 
    - Wedge body and contact surface is considered symetrical
    - The wedge contact surface (with the specimen) is flat or curved with a simple radius of curvature.
    - The probe(s) surface contact is flat.


- The wedge coordinate system origin is centered at the bottom of its front face (blue axis system in the figure below). 

| ![AxisReferential-Wedge_Elements_and_Beam-PAexample.png](/NDE_Open_File_Format/assets/images/conventions/AxisReferential-Wedge_Elements_and_Beam-PAexample.png){:width="50%"} |
|:---------------------------------------------------------------------------------------------------------------------------------------------:|
| *Flat wedge parameters and referential system examples.*  |

- The wedge coordinate system orientation is defined such as to have the $(Y_w)$ axis aligned with the wedge lenght, the $(X_w)$ axis aligned with the wedge width and the $(Z_w)$ axis aligned with the wedge height

- The wedge **skew angle** is defined by the angle between the wedge and **U** axis on the surface of the part at the wedge origin.

| ![AxisReferential-Wedge_SkewAngle.png](/NDE_Open_File_Format/assets/images/conventions/AxisReferential-Wedge_SkewAngle.png){:width="50%"} |
|:---------------------------------------------------------------------------------------------------------------------------------------------:|
| *Isometric views of different skew angles for reference. The skew angle is taken from the U-axis to the wedge Yw-axis.*  |

- Its positionning on the specimen is given in relation to the $(U,V)$ coordinates with the **uCoordinateOffset** and **vCoordinateOffset** located in the domain setup at **wedges[x].positioning**.   

- The positionning of the probe coordinate system is achieved in the $(X_w,Y_w,Z_w)$ coordinates through the successive application of the *primary offset* (on the $(Y_w)$ axis), the *secondary offset* (on the $(X_w)$ axis) and the *tertiary offset* (on the $(Z_w)$ axis)

### Flat wedges
<!---
to validate (do it cover angleBeamWedge and linear 0 deg as well)
-->

- For flat wedge the application of the above rules is straightforward as there's no ambiguity for the definition of the probe positionning.

### Curved Wedge

 - The application of wedge on tubular component does typically involve the use of wedge with curved matching surfaces. Such wedge requires additional conventions.

 - Typical configuation are axial outer diameter (AOD) or circumferential outer diameter (COD) configurations but it must be considered here that angle skew angle for outer or inner diameter inspection are also possible in this definition.

- Curved wedge face are dealt with by a redefinition of the *tertiary offset* and off course by a definition of the wedge curvature itself in the wedge object. The tertiary offset is defined for a flat wedge that is machined to the desired curvature.   

### **mountingLocations** Concepts and definition

- A probe is maintained in position on a wedge through an interface face defined by the aforementionned **primaryOffset**, **secondaryOffset** and **tertiaryOffset** plus three angles:
  - **wedgeAngle** $\beta$ : Angle between the normal of the interface face vs the $Z_w$ Axis
  - **squintAngle** $\alpha$ : Angle between the projection of the probe primary axis on the $X_w$/$Y_w$ plane and the $Y_w$ axis. 
    - Note : default squint angle is 0 deg
  - **roofAngle** $\gamma$ : Rotation angle around the probe primary axis
    - Note : default roof angle is 0 deg

| ![CoordinateSystemWedge.jpg](/NDE_Open_File_Format/assets/images/conventions/CoordinateSystemWedge.jpg){:width="50%"} |
|:---------------------------------------------------------------------------------------------------------------------------------------------:|
| *Isometric view of the wedge reference system illustrating the positionning of the origin of the probe coordinate system (flat wedge example)*    

  - It is possible to have multiple probe **mountingLocations** defined on a single wedge, for example in the case of Dual Linear Array (DLA) or Dual Matrix Array (DMA). 

 


### **phasedArrayLinear** objects
 - Hypothesis :
     - Constant **elementLenght** and **elementGap** for $(Np)$ **elementQuantity** distributed along a first probe axis. 
      - Constant **elementLenght** and **elementGap** for $(Ns)$ **elementQuantity** distributed along a secondary probe axis. 
      - Probe surface may be curve along the first or secondary probe axis but not both.

  - More specifically, the following use case are covered:
    - 1D linear array with flat active face. 
    - 1D linear array with curved active face along the primary axis (“CC” probes)
    - 1D linear array with curved active face along the secondary axis (“CCEV” probes)
    - 2D linear array with flat active face. 
    - 2D linear array with curved active face along the primary axis (“CC” probes)
    - 2D linear array with curved active face along the secondary axis (“CCEV” probes) 

## Examples UT/PAUT 

| ![AxisReferential-PlateWeld_2Probres.png](/NDE_Open_File_Format/assets/images/conventions/AxisReferential-PlateWeld_2Probres.png){:width="50%"} |
|:---------------------------------------------------------------------------------------------------------------------------------:|
| *Example of a typical plate scenario with a weld and two probes in relation to the $U$ and $V$ axis.*                  |

| ![AxisReferential-PipeWeld_2Probres.png](/NDE_Open_File_Format/assets/images/conventions/AxisReferential-PipeWeld_2Probres.png){:width="50%"} |
|:-------------------------------------------------------------------------------------------------------------------------------:|
| *Example general weld scenario with an axial weld on a pipe.*                                                        |


