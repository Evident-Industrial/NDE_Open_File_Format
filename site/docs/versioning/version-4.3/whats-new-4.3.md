# What's new in 4.3

Version 4.3 of the NDE Open File Format introduces native support for **Eddy Current Testing (ECT) and Eddy Current Array (ECA)** modalities. This is an additive release, all files conforming to versions 4.0, 4.1, or 4.2 remain fully valid.

## Motivation

The .nde format was originally designed around ultrasonic testing. Version 4.3 extends the format to cover the eddy current modality, which operates on fundamentally different physical principles: instead of time-of-flight waveforms, EC instruments record complex impedance signals (real and imaginary components) from inductive probes interacting with conductive materials.

Supporting ET/ECA required additions in four areas:

1. A new **probe model** reflecting the sensor-group abstraction of ECA probes
2. A new **acquisition process** capturing EC-specific hardware parameters
3. New **data classes and axes** for impedance datasets
4. New **data mapping and post-processing processes** matching EC scanning workflows

## New probe type: `eddyCurrentProbe`

The [eddyCurrentProbe](../../json-metadata/setup/data-model/probes.md#eddycurrentprobe) organizes sensors into **sensor groups**. Each group corresponds to an independently driven set of coils sharing a common frequency and drive configuration (analogous to a beam group in PAUT). Individual sensors within a group are positioned in a 2D coordinate system co-planar with the specimen surface using `primaryOffset` and `secondaryOffset`.

```
probe
 └── sensorGroups[]
      └── sensors[]
           ├── id
           ├── primaryOffset
           └── secondaryOffset
```

## New wedge type: EC wedge

A new wedge variant for eddy current probes is added to the [wedges](../../json-metadata/setup/data-model/wedges.md) array. EC wedges use the same `positioning` object as UT wedges to describe their position and orientation relative to the specimen surface. The `wedgeAssociation` object now supports four orientation values: `Normal`, `Reverse`, `FlipPrimary`, and `FlipSecondary`.

## New processes

### `eddyCurrent`: hardware acquisition

The [eddyCurrent](../../json-metadata/setup/data-model/groups/processes/eddyCurrent.md) process captures the hardware configuration of an EC acquisition: test frequency, drive amplitude, hardware gain, and the mapping of sensors to acquisition channels (including multiplexing timeslots).

### `impedanceTransformation`: phase and gain normalization

The [impedanceTransformation](../../json-metadata/setup/data-model/groups/processes/impedanceTransformation.md) process applies phase rotation and gain to raw impedance data. It operates at two levels:

- **Per-channel**: individual gain and rotation for inter-channel normalization (e.g. balancing ECA probe channels against a reference notch)
- **Group-level**: shared real gain, imaginary gain, and rotation applied after per-channel normalization

### `eddyCurrentMix`: mixed-frequency processing

The [eddyCurrentMix](../../json-metadata/setup/data-model/groups/processes/eddyCurrentMix.md) process combines two impedance data streams into a mixed output, typically to suppress an unwanted signal (e.g. geometry or support plate response) while retaining defect indications. The two streams ($Z_1$ and $Z_2$) are referenced through the process inputs (`z1InputId`, `z2InputId`), and the four mixing coefficients (`k1`–`k4`) are specified independently per acquisition channel through a `channels` array.

### `conductivity`: material conductivity measurement

The [conductivity](../../json-metadata/setup/data-model/groups/processes/conductivity.md) process converts complex impedance measurements into **material electrical conductivity** and **probe lift-off** using a set of calibration reference points. Each reference point pairs a known conductivity and lift-off value with the corresponding recorded impedance.

### Filter processes

Four filter processes are added for spatial or temporal filtering of ET signals, all configurable with cutoff frequency in `Hz` or `PerMeter`:

| Process | Description |
| :--- | :--- |
| [highPassFilter](../../json-metadata/setup/data-model/groups/processes/highPassFilter.md) | High-pass IIR or FIR filter |
| [lowPassFilter](../../json-metadata/setup/data-model/groups/processes/lowPassFilter.md) | Low-pass IIR or FIR filter |
| [figure6Filter](../../json-metadata/setup/data-model/groups/processes/figure6Filter.md) | Figure-6 band-pass filter |
| [figure8Filter](../../json-metadata/setup/data-model/groups/processes/figure8Filter.md) | Figure-8 band-pass filter |

### `layerDetection`

The [layerDetection](../../json-metadata/setup/data-model/groups/processes/layerDetection.md) process identifies material layer boundaries from impedance data.

### `mapToDescrete`: spatial remapping

The [mapToDescrete](../../json-metadata/setup/data-model/groups/processes/mapToDescrete.md) process converts data acquired with an `allCycle` data mapping into a `discreteGrid` data mapping, using recorded encoder positions to assign each acquisition cycle to its corresponding spatial position on the grid.

## New data mapping strategy: `allCycle`

The existing `discreteGrid` mapping assumes a regular grid of known positions. This does not fit EC acquisitions using a rotary encoder or acquisitions where the spatial grid must be reconstructed in post-processing.

The new [allCycle](../../json-metadata/setup/data-model/data-mappings.md#allcycle) mapping stores **every acquisition cycle individually**, together with its encoder position. A companion encoder-position dataset is created for each motion device. Spatial reconstruction is then performed by the `mapToDescrete` process.

```
allCycle data mapping
 └── datasets[]     ← one encoder-position dataset per motion device
      ├── dataClass: Encoder
      └── dimensions: [AcquisitionCycle]
```

## New `Polar` dimension axis

A new [Polar](../../json-metadata/setup/data-model/data-mappings.md#polar) axis is available in `discreteGrid` dimensions for rotational scanning configurations (e.g. ECT tube inspection with a rotating probe). It behaves like `UCoordinate` or `VCoordinate` but uses angular resolution in degrees.

## New dataset data classes and axes

### ET data classes

Two new `dataClass` values are defined for ET datasets (see [supported datasets](../../json-metadata/setup/data-model/groups/datasets.md#conventional-eddy-current-testing-ect-and-eddy-current-array-eca)):

| dataClass | Description |
| :--- | :--- |
| `Impedance` | Complex impedance samples (strip chart / line scan) |
| `ImpedanceStatus` | Validity/saturation flags per sample |

### New axes

| Axis | Context | Description |
| :--- | :--- | :--- |
| `Channel` | ET | One entry per EC acquisition channel |
| `AcquisitionCycle` | ET | Sequential acquisition cycle index, used in `allCycle` datasets |

## New rotary encoder modes

Two new `mode` values are added to the [encoder](../../json-metadata/setup/data-model/motion-devices.md#encoder) object to support rotary encoders:

| Mode | Description |
| :--- | :--- |
| `Tach` | Each step corresponds to a partial rotation; `stepResolution` gives steps per revolution |
| `Index` | Each step corresponds to one full revolution; `stepResolution` is typically `1.0` |

## New specimen type: `unspecifiedGeometry`

A new [unspecifiedGeometry](../../json-metadata/setup/data-model/specimens.md#unspecifiedgeometry) specimen type is added for acquisitions where the specimen geometry is unknown or not relevant to the recording. Only the inspectable surfaces are declared (by `id`); no dimensions or material are required. This is useful for any context where positioning data is not tied to a fully-described part in a scan plan.
