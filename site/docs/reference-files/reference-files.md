---
layout: default
title: Reference Files
nav_order: 6
has_children: false
description: Reference Files
---

# Reference Files

Here are some sample NDE data files

#### Plate Weld Inspection

| File Name                                                                                                                                                                                                                                                                                                           | Phased Array | Ultrasound Conventional | TFM | PCI |
| ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------ | ----------------------- | --- | --- |
| [Plate_Escan.nde](https://github.com/Evident-Industrial/NDE_Open_File_Format/tree/main/Plate_Escan.nde) [[View](https://myhdf5.hdfgroup.org/view?url=https://github.com/Evident-Industrial/NDE_Open_File_Format/blob/b74fae8d51f9a57939c8b72c4a322815d6c48aa9/Plate_Escan.nde)] | &#x2713;     |                         |     |     |
| Plate_Sscan.nde                                                                                                                                                                                                                                                                                                     | &#x2713;     |                         |     |     |
| Plate_Compound.nde                                                                                                                                                                                                                                                                                                  | &#x2713;     |                         |     |     |
| DLA_WeldPlate_2gr.nde                                                                                                                                                                                                                                                                                               | &#x2713;     |                         |     |     |
| DMA_WeldPlate_2gr.nde                                                                                                                                                                                                                                                                                               | &#x2713;     |                         |     |     |

#### Pipe Circumferential Weld Inspection

| File Name                | Phased Array | Ultrasound Conventional | TFM | PCI |
| ------------------------ | ------------ | ----------------------- | --- | --- |
| Pipe_Escan.nde           | ✓            |                         |     |     |
| Pipe_Sscan.nde           | ✓            |                         |     |     |
| Pipe_Compound.nde        | ✓            |                         |     |     |
| AOD_PCI.nde              |              |                         |     | ✓   |
| AOD_PCI_Opposite.nde     |              |                         |     | ✓   |
| Axial_Escan.nde          | ✓            |                         |     |     |
| Axial_Sscan.nde          | ✓            |                         |     |     |
| Axial_Compound.nde       | ✓            |                         |     |     |
| HSMT_AOD_TFM_SKEW90.nde  |              |                         | ✓   |     |
| HSMT_AOD_TFM_SKEW270.nde |              |                         | ✓   |     |
| HSMT_AOD_ToFD+PA.nde     | ✓            | ✓                       |     |     |
| TOFD_PA.nde              |              | ✓                       |     |     |
| TOFD_UT_P1R1.nde         |              | ✓                       |     |     |

#### Pipe Axial Weld Inspection

| File Name                     | Phased Array | Ultrasound Conventional | TFM | PCI |
| ----------------------------- | ------------ | ----------------------- | --- | --- |
| AXSEAM_COD_TFM_4GR_SKEW90.nde |              |                         | ✓   |     |

Feature Specific Examples

| File Name   | Description                              |
| ----------- | ---------------------------------------- |
| Overlay.nde | Demonstrates custom overlay integration. |