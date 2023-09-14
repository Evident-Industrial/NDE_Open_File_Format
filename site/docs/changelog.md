---
title: CHANGELOG
layout: default
---
# CHANGELOG
All notable changes to the NDE format will be documented in this file.
It is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/), and adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).


## [3.2.0] - 2023-09-28
### Changed
- elementQuantity property refers to a uniform definition of quantity using an integer data type.

### Added
- New planeWaveCapture group configuration.
- New tandem PAUT group configuration.
- Experimental Elementary A-Scan dataset using StackedAScan axis.
- Experimental utMatrixCapture group with fullMatrixCapture configuration.
- Improved object description reused for documentation.
- Add id property to beams and dimensions array.


## [3.1.1] - 2023-07-10
### Added
- Schema reorganization including new id reference.

## [3.1.0] - 2023-04-21
### Added
- name and softwareProcess gain for tfmDescription.
- uCoordinateOrientation for discreteGrid.
- PCS for TOFD configuration.
- customOverlay2D for plateGeometry and pipeGeometry.

### Removed
- exclusiveMinimum for longitudinal and transversal vertical wave attenuationCoefficient.
- gateCscans dataset.
- Undefined elementaryAscan dataset.


## [3.0.1] - 2023-01-17
### Added
- Coherence data value unit for PCI.

### Deprecated
- gateCscans dataset.
- Undefined elementaryAscan dataset.


## [3.0.0] - 2022-12-20
- Initial schema version supported.