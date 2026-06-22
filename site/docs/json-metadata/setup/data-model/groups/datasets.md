# Datasets

<!-- md:json_type array -->

A dataset is a container for data of a homogeneous nature, characterized by standardized data classes, with its volume necessitating storage within the HDF5 structure. Through the process it originates, the dataset establishes a connection between the data and physical reality (time/space). 

The **datasets** array describes datasets properties and how they relate to the acquisition and post-processing processes.

| Property                  | Type    | Technology | Description                                                                                                                             |
| :------------------------ | :------ | :--------: | :-------------------------------------------------------------------------------------------------------------------------------------- |
| **id**                    | integer | <span class="badge-all">All</span> | The unique dataset id within the group                                                                             |
| **name**                  | string  | <span class="badge-all">All</span> | The name of the dataset                                                                                            |
| **storageMode**           | string  | <span class="badge-ut">UT</span>   | One of `Independent` or `Paintbrush`. See the [storageMode conventions](../../conventions.md#storage-mode).        |
| **dataTransformations**   | array   | <span class="badge-all">All</span> | A [dataTransformations](#datatransformations) array describing the various operations to perform on the dataset    |
| **path**                  | string  | <span class="badge-all">All</span> | The path to the dataset in the HDF5 structure                                                                      |
| **dataClass**             | string  | <span class="badge-all">All</span> | <span class="badge-ut">UT</span> One of: `AScanAmplitude`, `AScanStatus`, `TfmValue`, `TfmStatus`, `FiringSource`, `CScanPeak`, `CScanStatus`, `CScanTime` <br><span class="badge-et">ET</span> One of: `Impedance`, `ImpedanceStatus`  |
| **dataValue** `required`  | object  | <span class="badge-all">All</span> | A [dataValue](#datavalue) object                                                                                    |
| **dimensions** `required` | array   | <span class="badge-all">All</span> | A [dimensions](#dimensions) array. See the [supported datasets](#supported-datasets) section for the possible configurations. |

### **dataTransformations**
<!-- md:json_type array -->

The **dataTransformations** array references the last process of the processes chain to consider for all transformations that should be applied to the dataset. See the [typical groups structure examples](../groups/index.md#examples-of-typical-groups-structures). 

| Property                 | Type    | Description                                                                      |
| :----------------------- | :------ | :------------------------------------------------------------------------------- |
| **processId** `required` | integer | The processId of the last process in the chain                                   |
| **groupId**              | integer | The groupId of the last process in the chain (not required if in the same group) |

``` json title="Example"
"dataTransformations": [
  {
    "processId": 1
  }
]
```

### **dataValue**
<!-- md:json_type object -->

The **dataValue** object describes the range or possible values a dataset can contain. 

**<span class="badge-ut">UT</span> For `AScanAmplitude`, `TfmValue`, `CScanPeak`, and `CScanTime` data classes**

**<span class="badge-et">ET</span> For `Impedance` data class**

| Property               | Type    | Description                                                     |
| :--------------------- | :------ | :-------------------------------------------------------------- |
| **min** `required`     | number  | Minimum value possible of the dataset                           |
| **max** `required`     | number  | Maximum value possible of the dataset                           |
| **unitMin** `required` | integer | Minimum value possible of the dataset in the corresponding unit |
| **unitMax** `required` | integer | Maximum value possible of the dataset in the corresponding unit |
| **unit** `required`    | string  | <span class="badge-ut">UT</span> One of the following: `Percent`, `Coherence`, `Seconds` <br><span class="badge-et">ET</span> One of the following: `Percent`        |

To map a value from the range [min, max] to [unitMin, unitMax], use the following formula:

$$ 
x_{scaled}= \left( \frac{x - \text{min}}{\text{max} - \text{min}} \right) \times (\text{unitMax} - \text{unitMin}) + \text{unitMin} 
$$

!!! info 
    <span class="badge-et">ET</span> Eddy current impedance data is stored as a complex number. The HDF5 dataset uses a compound type with an `r` key for the real component and an `i` key for the imaginary component. The `min`, `max`, `unitMin`, and `unitMax` scaling is applied independently to each component.

``` json title="Example"
"dataValue": {
  "min": 0,
  "max": 32767,
  "unitMin": 0.0,
  "unitMax": 200.0,
  "unit": "Percent"
}
```

**<span class="badge-ut">UT</span> For `AScanStatus`, `TfmStatus`, and `CScanStatus` data classes**

| Property                 | Type    | Description                     |
| :----------------------- | :------ | :------------------------------ |
| **hasData** `required`   | integer | Has data status value           |
| **noSynchro** `required` | integer | No synchronization status value |
| **saturated** `required` | integer | Saturated status value          |
| **unit** `required`      | string  | `Bitfield`              |

**<span class="badge-et">ET</span> For `ImpedanceStatus` data class**

| Property                 | Type    | Description            |
| :----------------------- | :------ | :--------------------- |
| **hasData** `required`   | integer | Has data status value  |
| **saturated** `required` | integer | Saturated status value |
| **unit** `required`      | string  | `Bitfield`             |

!!! note
    A bitfield array is a compact way to store multiple flags using only a few bits per item. Each flag is read or written using bitwise operations on the stored integer value.

=== "UT example"
    ``` json
    "dataValue": {
      "hasData": 1, //(1)!
      "saturated": 2, //(2)!
      "noSynchro": 4, //(3)!
      "unit": "Bitfield"
    }
    ```

    1. **hasData** is encoded on the first bit (binary 001 → decimal 1)
    2. **saturated** is encoded on the second bit (binary 010 → decimal 2)
    3. **noSynchro** is encoded on the third bit (binary 100 → decimal 4)

    So hasData + saturated evaluates to:

    | Flags               | Binary | Decimal |
    | :------------------ | :----: | :-----: |
    | hasData + saturated |  011   |    3    |

=== "ET example"
    ``` json
    "dataValue": {
      "hasData": 1, //(1)!
      "saturated": 2, //(2)!
      "unit": "Bitfield"
    }
    ```

    1. **hasData** is encoded on the first bit (binary 01 → decimal 1)
    2. **saturated** is encoded on the second bit (binary 10 → decimal 2)


### **dimensions**
<!-- md:json_type array -->

The **dimensions** array describes the different dimensions (axes) of the dataset(s).

!!! info "Important"
    **Dimensions are always given in the same order as the HDF5 dataset dimensions.**

**<span class="badge-ut">UT</span> For `UCoordinate`, `VCoordinate`, `WCoordinate`, `Ultrasound`, and `StackedAScan` axes**:

| Property                  | Type    |  Unit  | Description                                                                                    |
| :------------------------ | :------ | :----: | :--------------------------------------------------------------------------------------------- |
| **axis** `required`       | string  |   -    | One of the following: `UCoordinate`, `VCoordinate`, `WCoordinate`, `Ultrasound`,`StackedAScan` |
| **offset**                | number  | m or s | Offset to position the dataset                                                                 |
| **quantity** `required`   | integer |   -    | Size of the dataset against this axis (dimension)                                              |
| **resolution** `required` | number  | m or s | Resolution of the dataset against this axis (dimension)                                        |

``` json title="Example"
"dimensions": [
  {
    "axis": "UCoordinate",
    "offset": 0.0,
    "quantity": 101,
    "resolution": 0.001
  },
  {
    "axis": "VCoordinate",
    "offset": 0.0,
    "quantity": 57,
    "resolution": 0.001
  },
  {
    "axis": "Ultrasound",
    "offset": -1.01E-06,
    "quantity": 364,
    "resolution": 2E-08
  }
]
```

**<span class="badge-ut">UT</span> For the `Beam` axis**:

| Property              | Type   | Description                   |
| :-------------------- | :----- | :---------------------------- |
| **axis** `required`   | string | `Beam`                        |
| **beams**  `required` | array  | A [beams](#beams) array       |

#### **beams**
<span class="badge-ut">UT</span>
<!-- md:json_type array -->

| Property                          | Type    | Unit | Description                                       |
| :-------------------------------- | :------ | :--: | ------------------------------------------------- |
| **id**                            | integer |  -   | The unique beam id within the acquisition process |
| **velocity** `required`           | number  | m/s  | The velocity used to calculate focal laws         |
| **skewAngle** `required`          | number  |  °   | The beam skew angle                               |
| **refractedAngle** `required`     | number  |  °   | The beam refracted angle in the specimen          |
| **uCoordinateOffset**  `required` | number  |  m   | The beam exit point offset w.r.t to $u$ axis      |
| **vCoordinateOffset** `required`  | number  |  m   | The beam exit point offset w.r.t to $v$ axis      |
| **ultrasoundOffset** `required`   | number  |  s   | The beam offset w.r.t to time (ultrasound) axis   |

``` json title="Example"
"dimensions": [
  {
    "axis": "UCoordinate",
    "quantity": 301,
    "resolution": 0.001
  },
  {
    "axis": "Beam",
    "beams": [
      {
        "velocity": 3240.0,
        "skewAngle": 90.0,
        "refractedAngle": 40.0,
        "uCoordinateOffset": 0.0,
        "vCoordinateOffset": -0.03868746281893342,
        "ultrasoundOffset": 0.0
      },
      {
        "velocity": 3240.0,
        "skewAngle": 90.0,
        "refractedAngle": 41.0,
        "uCoordinateOffset": 0.0,
        "vCoordinateOffset": -0.038554784991032057,
        "ultrasoundOffset": 0.0
      },
      {...}]},
  {
    "axis": "Ultrasound",
    "quantity": 1700,
    "resolution": 2E-08
  }
]
```

Note: The **uCoordinateOffset** and **vCoordinateOffset** are only applicable when the surface of the wedge matches the specimen surface on which offsets are referenced. 

**<span class="badge-et">ET</span> For `Channel` and `AcquisitionCycle` axes**:

| Property                | Type    | Description                                         |
| :---------------------- | :------ | :-------------------------------------------------- |
| **axis** `required`     | string  | One of the following: `Channel`, `AcquisitionCycle` |
| **quantity** `required` | integer | Size of the dataset against this axis (dimension)   |

``` json title="Example"
"dimensions": [
  {
    "axis": "Channel",
    "quantity": 16
  },
  {
    "axis": "AcquisitionCycle",
    "quantity": 200
  }
]
```

These dimensions can vary depending on the group and scan types.

## Supported datasets

The datasets shape may vary depending on the type of scanning and data mapping strategy. The following types are defined:

- **One Line Scanning**: The probe is mechanically moved against a single axis on the surface of the specimen.
- **Raster Scanning**: The probe is mechanically moved against two axes on the surface of the specimen.
- <span class="badge-et">ET</span> **All Cycle**: Data is stored cycle by cycle using an [allCycle](../data-mappings.md#allcycle) data mapping, without prior spatial indexing. A subsequent [mapToDescrete](./processes/mapToDescrete.md) process converts it to a spatially-indexed grid.


###  Conventional ultrasonic testing (UT)

For conventional ultrasonic testing (UT), two datasets are supported: one containing the raw A-Scans (`dataClass = AScanAmplitude`), and another containing the status information (`dataClass = AScanStatus`, see above) for each A-Scan. The dimensions of each dataset can be organized as illustrated below. 

![UTDatasets.png](../../../../assets/images/json-metadata/setup/data-model/groups/datasets/UTDatasets.png){ width="350" }

Example files: [Manual weld scanning](../../../../examples/example-files/index.md#manual-weld-scanning-using-conventional-ultrasonic-testing-ut)

###  Phased array ultrasonic testing (PAUT)

For phased array ultrasonic testing (PAUT), two datasets are supported: one containing the raw A-Scans (`dataClass = AScanAmplitude`), and another containing the status information (`dataClass = AScanStatus`, see above) for each A-Scan. The dimensions of each dataset can be organized as illustrated below. Three cases are presented, depending on the type of scanning and [storage mode](../../conventions.md#storage-mode).

=== "One Line Scanning"
    ![PAOneLineScanDatasets.png](../../../../assets/images/json-metadata/setup/data-model/groups/datasets/PAOneLineScanDatasets.png){ width="350" }
    
    Example files: [Manual weld scanning](../../../../examples/example-files/index.md#manual-weld-scanning-using-phased-array-ultrasonic-testing-paut), [Semiautomated weld scanning ](../../../../examples/example-files/index.md#semiautomated-weld-scanning-using-time-of-flight-diffraction-tofd-and-phased-array-ultrasonic-testing-paut)
=== "0° Raster Scanning"
    ![PARasterScanPaintbrushDatasets.png](../../../../assets/images/json-metadata/setup/data-model/groups/datasets/PARasterScanPaintbrushDatasets.png){ width="350" }

    Note that an additional dataset with `dataClass = FiringSource` is also used in this configuration but not documented to date. 

    Example files: [Composite wheel probe scanning](../../../../examples/example-files/index.md#composite-wheel-probe-scanning-using-phased-array-ultrasonic-testing-paut), [Corrosion inspection](../../../../examples/example-files/index.md#corrosion-inspection-using-phased-array-ultrasonic-testing-paut), [Pipe elbow corrosion](../../../../examples/example-files/index.md#pipe-elbow-corrosion-inspection-using-phased-array-ultrasonic-testing-paut)
=== "Angle Beam Raster Scanning"
    ![PARasterScanIndependentDatasets.png](../../../../assets/images/json-metadata/setup/data-model/groups/datasets/PARasterScanIndependentDatasets.png){ width="350" }

    Example files: [Composite wheel probe scanning](../../../../examples/example-files/index.md#composite-wheel-probe-scanning-using-phased-array-ultrasonic-testing-paut)

###  Total focusing method and its derivatives (TFM/PCI/PWI)

For total focusing method and its derivatives (TFM/PCI/PWI), two datasets are supported: one containing the reconstructed images (`dataClass = TfmValue`), and another containing the status information (`dataClass = TfmStatus`, see above) for each image. The dimensions of each dataset can be organized as illustrated below.

![TFMDatasets.png](../../../../assets/images/json-metadata/setup/data-model/groups/datasets/TFMPCIPWIDatasets.png){ width="350" }

Example files: [Manual weld scanning](../../../../examples/example-files/index.md#manual-weld-scanning-using-the-total-focusing-method-tfm), [Girth weld scanning](../../../../examples/example-files/index.md#girth-weld-scanning-using-the-total-focusing-method-tfm),  [Composite X-Y scanning](../../../../examples/example-files/index.md#composite-x-y-scanning-using-the-total-focusing-method-tfm)

###  Full Matrix Capture (FMC)

For Full Matrix Capture (FMC), one dataset type is supported which contains the elementary A-Scans (`dataClass = AScanAmplitude`). The dimensions of the dataset can be organized as illustrated below.

![FMCDatasets.png](../../../../assets/images/json-metadata/setup/data-model/groups/datasets/FMCDatasets.png){ width="350" }

The stackedAScan dimension is organized as illustrated below:

![stackedAScan.png](../../../../assets/images/json-metadata/setup/data-model/groups/datasets/stackedAScan.png){ width="350" }

Example file: [Full matrix capture](../../../../examples/example-files/index.md#full-matrix-capture-fmc-acquisition)

### Conventional Eddy Current Testing (ECT) and Eddy Current Array (ECA)

For Eddy Current Testing (ECT) and Eddy Current Array (ECA), the supported dataset type contains the raw impedance strip charts (`dataClass = Impedance`). The dimensions of the dataset can be organized as illustrated below.

![ETImpedanceDatasets.png](../../../../assets/images/json-metadata/setup/data-model/groups/datasets/ETImpedanceDatasets.png){ width="350" }
