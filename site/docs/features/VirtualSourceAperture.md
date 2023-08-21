---
layout: default
title: Plane Wave Imaging
nav_exclude: true
description: Plane Wave Imaging Details
---

# Plane Wave Imaging

- The direction of a plane wavefront is controlled by a user and multiple directions are used to image the inspected part. To draw a parallel with a _Phased Array_ focal law, these variations of the direction come down to the creation of a non-focused sectorial focal law (_focusing type Unfocused_). The direction is defined by the angle that the wavefront makes **in the specimen** with respect to the normal at the entry point.

The PWI technique is a type of _Matrix Capture_: that is to say a method of data acquisition (we can use the term _Plane Wave Capture_ for PWI acquisition). It is at the same level as the FMC. In FMC and for transmission, each of the active elements are pulsed one after the other whereas in PWI, all the active elements pulse and it is the angle of the wavefront formed which varies between each shot. In reception, the principle is the same and the signal is detected on each of the elements. The following image shows the relationships between these techniques as well as the _Focusing Method_ types.

![image](/NDE_Open_File_Format/assets/images/VirtualSourceAperture/FMC_PWI_TFM_PCI.png)

In the Scan Plan, _Groups_ tab, selecting a _Law Config._ _TFM_ will show the new list of choices for the type of _TFM_. On the second page, the following settings will be required for PWI:

- The first transmission angle
- The last transmission angle
- The number of transmission angles (number of *beams*)
- Angular resolution (read-only check)

<img title="" src="/NDE_Open_File_Format/assets/images/VirtualSourceAperture/2023-07-28-15-22-31-image.png" alt="" width="226">    <img title="" src="/NDE_Open_File_Format/assets/images/VirtualSourceAperture/2023-07-28-15-23-52-image.png" alt="" width="229">

In the TFM Settings pulser menu, the Pwi beam quantity replaces the sparse configuration.

![](C:\Dev\NDEDocDocker\NDE_Open_File_Format_Private\site\assets\images\VirtualSourceAperture\2023-07-28-15-28-22-image.png)

#### [> To NDE Schema](../../docs/schema_doc.html#tab-pane_groups_items_oneOf_i3)
