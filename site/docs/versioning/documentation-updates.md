# Documentation Updates

All notable changes to the .nde file format documentation will be documented on this page.

### <small>June 15, 2026</small>

Update to documentation for [NDE file format version 4.3](../versioning/changelog.md#4.3.0), comprising:

- New [What's new in 4.3](version-4.3/whats-new-4.3.md) page detailing Eddy Current modality support.
- New [eddyCurrentProbe](../json-metadata/setup/data-model/probes.md#eddycurrentprobe) probe type documentation.
- New [EC wedge](../json-metadata/setup/data-model/wedges.md) type documentation.
- New ET process pages: [eddyCurrent](../json-metadata/setup/data-model/groups/processes/eddyCurrent.md), [impedanceTransformation](../json-metadata/setup/data-model/groups/processes/impedanceTransformation.md), [eddyCurrentMix](../json-metadata/setup/data-model/groups/processes/eddyCurrentMix.md), [conductivity](../json-metadata/setup/data-model/groups/processes/conductivity.md), [layerDetection](../json-metadata/setup/data-model/groups/processes/layerDetection.md), [mapToDescrete](../json-metadata/setup/data-model/groups/processes/mapToDescrete.md), and filter processes.
- New [allCycle](../json-metadata/setup/data-model/data-mappings.md#allcycle) and [Polar](../json-metadata/setup/data-model/data-mappings.md#polar) data mapping documentation.
- New [nomenclature](../json-metadata/setup/nomenclature.md) page covering UT/PAUT and ET/ECA terminology.
- New [Eddy Current Testing Example Files](../examples/example-files/index.md#eddy-current-testing-examples) covering the general mapping scenario.
- Updated [conventions](../json-metadata/setup/conventions.md) page to cover ET modality (axes, probe coordinate systems, storage modes).
- Updated [datasets](../json-metadata/setup/data-model/groups/datasets.md) page with ET data classes and supported dataset configurations.
- Updated [specimens](../json-metadata/setup/data-model/specimens.md) page with the new `unspecifiedGeometry` specimen type.

### <small>January 9, 2026</small>

- Update [OmniScan MXU](../supporting-software/evident/omniscan-mxu.md) changelog
- Correct various errors throughout the documentation

### <small>October 16, 2025</small>

Update to documentation for [NDE file format version 4.2](../versioning/changelog.md#4.2.0), comprising:

- New `SynchroGateRelative` mode for [TCG](../json-metadata/setup/data-model/groups/processes/ultrasonicPhasedArray.md#tcg) 
- New `inverted` parameter for [encoder](../json-metadata/setup/data-model/motion-devices.md#encoder) description 

### <small>September 9, 2025</small>

- Update [OmniScan MXU](../supporting-software/evident/omniscan-mxu.md) changelog
- Correct various errors throughout the documentation

### <small>April 23, 2025</small>

General update to documentation, comprising:

- Update [wedges](../json-metadata/setup/data-model/wedges.md) to add information about the fluidColumn object.
- New [NDE Concept and Structure](../getting-started/nde-concept-and-structure.md) page. 
- New [raster UT example file](../examples/example-files/index.md#corrosion-inspection-using-conventional-ultrasonic-testing-ut). 

Update to documentation for [NDE file format version 4.1](../versioning/changelog.md#4.1.0), comprising:

- Update [datasets](../json-metadata/setup/data-model/groups/datasets.md) page with new 4D dataset and rework of supported datasets description.
- Update [example files](../examples/example-files/index.md) page with new examples for ToFD parallel scanning and phased array angle beam raster scanning.

### <small>November 20, 2024</small>

Update documentation for NDE file format version 4.0.

### <small>April 19, 2024</small>

Migrate documentation from Just The Docs theme for Jekyll to Material for MkDocs.

### <small>January 15, 2024</small>

Update documentation for NDE file format version 3.3.

### <small>September 28, 2023</small>

Initial publication of the NDE File Format Documentation. 