---
title: Version Log
layout: default
---

# Version Log

All notable user-facing changes to this project are documented in this file.

### Changelog
All notable changes to the format will be documented in this file.
It is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/), and adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

#### [Unreleased]

#### [3.2.0] - 2023-09-30
#### Added

  
#### Changed

  
#### Removed


#### [3.1.1] - 2022-12-01
#### Added
- [EAB] Schema version 3.0.0-Beta + compatibility code to upgrade from previous version.
- [1] New *dataset* object including an uniform description of each axes.
- [1] *linearPitchCatch, sectorialPitchCatch, compoundPitchCatch* specialization.
- [1] *boxGate* in *fmc/tfm/analysis* object.
- [1] *analysis* object in *ut, paut and fmc/tfm* to include modifications to be applied on original data.
- [1] *mapGain* object in *fmc/tfmConfig*.
- [1] *beams/gain* in *ut/analysis and paut/analysis* object.
- [1] *angle* propertie to *focusing* object.
- [1] *Unfocused* and *Projection* choices added to *focusing/mode* propertie.
- [1] *conventionalSquare* probe object.
- [2] *paut/custom* object to support .law file configuration.
- [2] Custom overlay...
- [2] Thickness parameters...
- [2] *clicker motiondevice*...
- [EAB] Reuse *tcg* object in *ut/analysis and paut/analysis* object. 
- [EAB] Reuse *gates and beams/gates* in *ut/analysis and paut/analysis* object.
  
#### Changed
- [1] *dataGroups* list renamed to *groups*.
- [1] *ascanStart* and *ascanLength* properties moved outside of *ultrasoundAxis*.
- [1] Move acquisition unit properties out of *omniScanX3* and *focusPX* object.
- [MSL] Move specific parameters from *ultrasound/conventionalPulseEcho* to *ut/pulseEcho* object.
- [MSL] Move specific parameters from *ultrasound/conventionalPitchCatch* to *ut/pitchCatch* object.
- [MSL] Move specific parameters from *ultrasound/tofd* to *ut/tofd* object.
- [MSL] *ut* replace *ultrasound/conventionalPulseEcho*, *ultrasound/conventionalPitchCatch* and *ultrasound/tofd*.
- [MSL] Move specific parameters from *ultrasound/sectorialPulseEcho* to *paut/sectorialPulseEcho* object.
- [MSL] Move specific parameters from *ultrasound/linearPulseEcho* to *paut/linearPulseEcho* object.
- [MSL] Move specific parameters from *ultrasound/compoundPulseEcho* to *paut/compoundPulseEcho* object.
- [MSL] *paut* replace *ultrasound/sectorialPulseEcho*, *ultrasound/linearPulseEcho* and *ultrasound/compoundPulseEcho*.
- [MSL] *fullMatrixCapture* object renamed to *fmc*.
- [MSL] *fullMatrixCapture/tfmDescription* renamed *fmc/tfmConfig*.
- [EAB] Code examples updated.
  
#### Removed
- [1] *datasets* list from any configuration specialization.
- [1] *ultrasoundAxis* including *ascanResolution* from beam object.
- [1] *amplitudePercentAxis* from any configuration specialization.
- [1] *analysisBeamGain* from *processes* list.
