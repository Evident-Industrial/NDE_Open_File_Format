---
layout: default
title: Discrete Grid Objects 
nav_exclude: true
parent: Data Encoding
grand_parent: General Concepts
nav_order: 1
---

# Discrete Grid Objects 

## Definition  

Data storage grid corresponding to surface coordinates on the specimen. A single set of data is to be saved for each coordinate position. The discreteGrid is a structured Grid (see definition below from  https://www.sciencedirect.com/topics/engineering/structured-grid)

![structure-grid.png](/NDE_Open_File_Format/assets/images/general-concepts/structure-grid.png)

## Limitation 

Only applicable in scenarios where the inspection can be represented entirely by surface positioning.


## Parameters and subcomponents 

- “specimenId” : link to the specimen Id the scan refers to.
- “surfaceId” : link to which surface of the specimen  the scan refers to.
- “storage”/“AcquisitionDirection”:  
    - “Bidirectional” : Data acquisition for each new position
    - “Positive” : Data acquisition when scan is in the positive direction of the primary axis
    - “Negative” : Data acquisition when scan is in the negative direction of the primary axis
- “storage”/“OverwriteCriteria”: 
    - “First” : First data acquired at a grid position is kept
    - “Last” : Last data acquired at a grid position is kept
    - … 
- “storage”/“OverwriteMode”
    - “Independent” 
        - Data stored in dataEncoding “id” are all saved independently. As a result the dataset has dimensions [Np, Ns, Nd, Ne]   (where Np = Number of storage bins in the primary scan axis, Ns = Number of storage bins in the secondary scan axis, Nd = Number of independent datasets, Ne = Number of elementary data, for example ascan for UT). 
        - Data are stored vs encoder reading (not vs the actual probe position)
        - OverwriteCriteria applies when encoder position is repeated.
        - Typical usage for PAUT Weld inspection, where each beam angle is independent.
    - “Merged”
        - Data stored in dataEncoding “id” are saved in a merged dataset with dimensions [Np, Ns, Ne]   (where Np = Number of storage bins in the primary scan axis, Ns = Number of storage bins in the secondary scan axis, Nd = Number of independent datasets, Ne = Number of elementary data, for example ascan for UT).
        - Data are stored vs actual position of each elementary data on the surface, overwriteCriteria applies if two data are located at the same position.
        - Typical usage for PAUT Corrosion, where a single mapping of the surface is the objective.
- Motion type objects (detailed below).


## Motion type objects

- “oneLineScan” : Motion along a single axis
    - “primaryAxis”: defines which axis relates to the motion 
        - “U” 
        - “V” 
        - “Time” : in this case the dims of the grid is in sec
    - “origin” : position of the first data bin on the selected axis
    - “length” : length of the grid
    - “resolution” : resolution of the grid
- “rasterScan” : Motion along two axis
    - “primaryAxis”: : defines which axis is the scan direction (the other being the index)
        - “U” 
        - “V” 
    - “origin” : position of the first data bin on the selected axis
    - “length” : length of the grid
    - “resolution” : resolution of the grid
- “helicoidalScan”
- “freeHand” 
