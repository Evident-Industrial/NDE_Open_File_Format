---
layout: default
title: Reference Files
nav_order: 6
has_children: false
description: Reference Files
---

# Reference Files

Here are some sample NDE data files

### General Mapping
All files are raster scans for corrosion mapping / composite inspection purpose.

| File Name                             | Description 					|
| ------------------------------------- | -----------------------------	|
| DLC.nde           					| PA using DLC probe 			|
| FlexoFORM_Corrosion_0deg.nde  		| PA using FlexoFORM scanner	|
| MapROVER_PA_0deg_Raster_Corrosion.nde	| PA using MapRover scanner  	|
| MapROVER_UT_0deg_Raster_Corrosion.nde | UT using MapRover scanner    	|
| PA_Raster0deg.nde          			| PA 				            |
| TFM_Raster.nde          				| TFM							|
| UT-Dual_Raster.nde       				| UT using Dual UT probe		|


### General Weld

#### Plate Weld Inspection
All files are one line scans for plate weld inspection purpose.

| File Name            	| Description 		|
| --------------------- | -----------------	|
| [Plate_Escan.nde](https://github.com/Evident-Industrial/NDE_Open_File_Format/tree/main/Plate_Escan.nde) [[View](https://myhdf5.hdfgroup.org/view?url=https://github.com/Evident-Industrial/NDE_Open_File_Format/blob/b74fae8d51f9a57939c8b72c4a322815d6c48aa9/Plate_Escan.nde)]      	| PA E-Scan			|
| Plate_Sscan.nde      	| PA S-Scan			|
| Plate_Compound.nde    | PA Compound-Scan	|
| DLA_WeldPlate_2gr.nde	| PA DLA probe		|
| DMA_WeldPlate_2gr.nde	| PA DMA probe		|


#### Pipe Circumferential Weld Inspection
All files are one line scans for pipe circumferential weld inspection purpose.

| File Name                										| Description 			|
| ------------------------------------------------------------- | --------------------- |
| Pipe_Escan.nde           										| PA E-Scan				|
| Pipe_Sscan.nde           										| PA S-Scan       		|
| Pipe_Compound.nde        										| PA Compound-Scan		|
| AOD_PCI.nde              										| TFM PCI				|
| AOD_PCI_Opposite.nde     										| TFM PCI				|
| Axial_Escan.nde          										| PA E-Scan				|
| Axial_Sscan.nde          										| PA S-Scan				|
| Axial_Compound.nde       										| PA Compound-Scan		|
| HSMT_AOD_TFM_SKEW90.nde  										| TFM					|
| HSMT_AOD_TFM_SKEW270.nde 										| TFM					|
| HSMT_AOD_ToFD+PA.nde     										| ToFD+PA				|
| TOFD_PA.nde              										| ToFD on PA connector	|
| TOFD_UT_P1R1.nde         										| ToFD on UT connector	|
| Test circumferential lin-sect 2 probes 4388 manual weld.nde 	| 						|


#### Pipe Axial Weld Inspection
All files are one line scans for pipe axial weld inspection purpose.

| File Name                     | Description	|
| ----------------------------- | ------------- |
| AXSEAM_COD_TFM_4GR_SKEW90.nde | TFM			|


### Feature Specific Examples

| File Name   | Description                              |
| ----------- | ---------------------------------------- |
| Overlay.nde | Demonstrates custom overlay integration. |





??
| Weld_UT_Raster.nde           			| Plate - One line scan - PA E-Scan		|