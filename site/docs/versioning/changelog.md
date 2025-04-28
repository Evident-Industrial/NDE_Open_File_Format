---
toc_depth: 3
---

# CHANGELOG

All notable changes to the .nde file format will be documented on this page. It is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/) and adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

### [4.1.0] - <small>April 23, 2025</small> { id="4.1.0" }

#### Added
- Support of phased array angle beam raster scanning through a 4D dataset. 
    - The [Setup JSON Schema](../json-metadata/setup/schema_doc.md) was updated accordingly to support this type of datasets. 
    - An [example](../examples/example-files/index.md#semiautomated-weld-raster-scanning-using-phased-array-ultrasonic-testing-paut) was added and [supported datasets page](../json-metadata/setup/data-model/groups/datasets.md#phased-array-ultrasonic-testing-paut) updated accordingly. 
- Support of scanning against $V$ axis instead of $U$ for specific configurations, such as ToFD parallel scanning and Raster scanning at 0°.
    - The [Setup JSON Schema](../json-metadata/setup/schema_doc.md) was updated accordingly to support this type of datasets. 
    - Example files were added for [ToFD parallel scanning](../examples/example-files/index.md#manual-weld-scanning-using-parallel-time-of-flight-diffraction-tofd) and Raster scanning at 0°.
  
#### Changed
- Light corrections en enhancements to the documentation, see [the dedicated changelog](./documentation-updates.md). 
- Remove pocketDepth property from [fluidColumn](../json-metadata/setup/data-model/wedges.md#fluidcolumn-object) object in the [Setup JSON Schema](../json-metadata/setup/schema_doc.md) as it was not relevant.

See also: [Documentation updates](../versioning/documentation-updates.md#april-23-2025). 

### [4.0.0] - <small>November 12, 2024</small> { id="4.0.0" }

The 4.0.0 version is a big leap and the changes are described [in a dedicated section](version-4.0/whats-new-4.0.md). 

---

### [3.3.0] - <small>January 16, 2024</small> { id="3.3.0" }

#### Added
- The Pipe specimen now includes angularOpening, which is used to describe a curved part section.

### [3.2.0] - <small>September 28, 2023</small> { id="3.2.0" }

#### Changed
- elementQuantity property refers to a uniform definition of quantity using an integer data type.

#### Added
- New planeWaveCapture group configuration.
- New tandem PAUT group configuration.
- Experimental elementary A-scan dataset using StackedAScan axis.
- Experimental utMatrixCapture group with fullMatrixCapture configuration.
- Improved object description reused for documentation.
- Add id property to beams and dimensions array.

### [3.1.1] - <small>July 10, 2023</small> { id="3.1.1" }

#### Added
- Schema reorganization including new id reference.

### [3.1.0] - <small>April 21, 2023</small> { id="3.1.0" }

#### Added
- name and softwareProcess gain for tfmDescription.
- uCoordinateOrientation for discreteGrid.
- PCS for TOFD configuration.
- customOverlay2D for plateGeometry and pipeGeometry.

#### Removed
- exclusiveMinimum for longitudinal and transversal vertical wave attenuationCoefficient.
- gateCscans dataset.
- Undefined elementaryAscan dataset.

### [3.0.1] - <small>January 17, 2023</small> { id="3.0.1" }

#### Added
- Coherence data value unit for PCI.

#### Deprecated
- gateCscans dataset.
- Undefined elementaryAscan dataset.

### [3.0.0] - <small>December 20, 2022</small> { id="3.0.0" }
- Initial schema version supported.


