---
layout: default
title: Scenarios
parent: General Concepts
nav_order: 3
---

# Scenarios
Scenarios introduce a set of conventions specific to a given use case enabling a simple description of the specimen and associated probe and wedge positioning. 

Many non-destructive inspection scan plan are referenced to the surface of a specimen. Scenarios corresponding to those use cases link the probe or wedge positionning through (u,v) surface coordinates. 

## "General Mapping" Scenario
- Hypothesis:
    - This scenario uses $(U,V)$ surface coordinates.

    - The probe positioning vs the related specimen surface is constant for all $(U,V)$ position (skew angle,lift-off, etc) or automatically compensated (i.e. adaptive acoustic, lift-off compensation, electronic)

    - The $U$ axis is the principal scan axis and is typically colinear with a physical encoder device.

    - The $V$ axis is orthogonal to the $U$ axis and may either be associated to a secondary physical encoder, an electronic scan or both (for paint brush raster scan)

    - The $(0,0)$ position on the surface is arbitrarily defined by the user.

| ![AxisReferential-Raster_Plate.png](/NDE_Open_File_Format/assets/images/conventions/AxisReferential-Raster_Plate.png){:width="25%"} |
|:---------------------------------------------------------------------------------------------------------------------:|
| *Raster example with the $U$ and $V$ axis.*                                                                |


## "General Weld" scenario
- Hypothesis:
    - This scenario uses $(U,V)$ surface coordinates.

    - The scenario relates to the inspection of a single straight or curved weld or join.

    - The surface line $(U,0)$ is colinear with the center of said weld or join.

    - The probe positioning vs the related specimen surface is constant for all $(U,V)$ position (skew angle,lift-off, etc) or automatically compensated (i.e. adaptive acoustic, lift-off compensation, electronic).

    -  For pipe geometry, the orientation of the weld is defined in relation to the pipe axis. With an angle of 0° for an axial weld and 90° for a circumferential one. Any angle in between describes a helix weld.

    -  Scan pattern can be entirely described on the surface of specimen as a set of orthogonal axes parallel and orthogonal to the weld.

| ![AxisReferential-PipeAxialWeld.png](/NDE_Open_File_Format/assets/images/conventions/AxisReferential-PipeAxialWeld.png){:width="50%"} | 
| ![AxisReferential-PipeCircWeld.png](/NDE_Open_File_Format/assets/images/conventions/AxisReferential-PipeCircWeld.png){:width="50%"} | 
|:-----------------------------------------------------------------------------------------------------------------------------------:| 
| *The weld angle is defined in relation to the pipe axis.*                                                                |
