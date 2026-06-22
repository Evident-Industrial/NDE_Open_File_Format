# Data Mappings

<!-- md:json_type array -->

Independently of the nondestructive evaluation method, there is always a need to relate acquisition data to the inspected specimen in terms of positioning. There exist, however, diametrically opposed use cases calling for adapted methods to achieve this relationship.

The **dataMappings** array specifies how inspection data relates to the specimen. Two mapping strategies are supported:

- **discreteGrid** — Data is mapped onto a regular spatial grid defined by U/V coordinates. Suited to scanner-based acquisitions where probe position is known at each acquisition point (e.g. PAUT weld inspections, ECA inspections with embedded encoder).
- **allCycle** <!-- md:version 4.3.0 --> — Every acquisition cycle is stored along with its corresponding encoder position information. Suited to acquisitions where probe trajectory is irregular or must be reconstructed in post-processing (e.g. ECT with rotary encoder, robotic PAUT).

## **dataMappings**
<!-- md:json_type array -->

The **dataMappings** array describes the relationship between data and the specimen through the scenario coordinate system.

<table>
<thead>
  <tr>
    <th>Property</th>
    <th>Type</th>
    <th>Description</th>
  </tr>
</thead>
<tbody>
  <tr>
    <td><b>id</b> <code>required</code></td>
    <td>integer</td>
    <td>Unique data mapping id in the JSON structure</td>
  </tr>
  <tr>
    <td><b>specimenId</b> <code>required</code></td>
    <td>integer</td>
    <td>Unique specimen id in the JSON structure</td>
  </tr>
  <tr>
    <td><b>surfaceId</b> <code>required</code></td>
    <td>integer</td>
    <td>Unique surface id in the JSON structure</td>
  </tr>
  <tr>
    <td>
      One of the following <code>required</code> mapping strategy objects:
      <ul>
        <li><b><a href="#discretegrid">discreteGrid</a></b></li>
        <li><b><a href="#allcycle">allCycle</a></b></li>
      </ul>
    </td>
    <td>object</td>
    <td></td>
  </tr>
</tbody>
</table>

**Related objects**: [specimens](specimens.md#specimens), [surfaces](specimens.md#surfaces)

## **discreteGrid** 
<!-- md:json_type object -->

The **discreteGrid** object describes the properties of the scanning grid and its dimensions.

| Property                              |  Type  | Description                                                                             |
| :------------------------------------ | :----: | :-------------------------------------------------------------------------------------- |
| **scanPattern** `required`            | string | One of the following scan patterns: `OneLineScan` or `RasterScan`                       |
| **uCoordinateOrientation** `required` | string | One of the following U coordinate orientations: `Around`, `Along`, `Width`, or `Length` |
| **dimensions** `required`             | array  | An array of [UCoordinate](#ucoordinate), [VCoordinate](#vcoordinate), and/or [Polar](#polar) axis objects |

**Related objects**: [specimens](specimens.md#specimens), [surfaces](specimens.md#surfaces)

### **UCoordinate**
<!-- md:json_type object -->

The **UCoordinate** object describes the discrete grid U dimension.

| Property                  | Type    | Unit | Description                                                                                                                                          |
| :------------------------ | :------ | :--: | :--------------------------------------------------------------------------------------------------------------------------------------------------- |
| **axis** `required`       | string  |  -   | The name of the axis, necessarily `UCoordinate`                                                                                                      |
| **quantity** `required`   | integer |  -   | Size of the grid against the U axis                                                                                                                  |
| **resolution** `required` | number  |  m   | Space allocated to one data point along this axis                                                                                                    |
| **offset**                | number  |  m   | Axis offset                                                                                                                                          |
| **motionDeviceId**        | integer |  -   | Reference to the unique id of a [motionDevice](motion-devices.md#motiondevices) object                                                         |
| **name**                  | string  |  -   | Name or reference of this dimension                                                                                                                  |
| **unit**                  | string  |  -   | Unit of the axis values, e.g. `Meter`, `Degree`, `Revolution`                                                                                        |
| **lastCellRewrited**      | integer |  -   | When the acquisition is performed in time mode (no encoder), this axis is a circular buffer in which the first position is given in lastCellRewrited |

**Related objects**: [motionDevice](motion-devices.md#motiondevices)

### **VCoordinate**
<!-- md:json_type object -->

The **VCoordinate** object describes the discrete grid V dimension.

| Property                  | Type    | Unit | Description                                                                                  |
| :------------------------ | :------ | :--: | :------------------------------------------------------------------------------------------- |
| **axis** `required`       | string  |  -   | The name of the axis, necessarily `VCoordinate`                                              |
| **quantity** `required`   | integer |  -   | Size of the grid against the V axis                                                          |
| **resolution** `required` | number  |  m   | Space allocated to one data point along this axis                                            |
| **offset**                | number  |  m   | Axis offset                                                                                  |
| **motionDeviceId**        | integer |  -   | Reference to the unique id of a [motionDevice](motion-devices.md#motiondevices) object |
| **name**                  | string  |  -   | Name or reference of this dimension                                                          |
| **unit**                  | string  |  -   | Unit of the axis values, e.g. `Meter`, `Degree`, `Revolution`                                |

**Related objects**: [motionDevice](motion-devices.md#motiondevices)

### **Polar**
<!-- md:json_type object -->
<!-- md:version 4.3.0 -->

The **Polar** object describes a discrete grid angular dimension, used for rotational scanning configurations (e.g. ECT with rotary encoder).

| Property                  | Type    |  Unit  | Description                                                                                  |
| :------------------------ | :------ | :----: | :------------------------------------------------------------------------------------------- |
| **axis** `required`       | string  |   -    | The name of the axis, necessarily `Polar`                                                    |
| **quantity** `required`   | integer |   -    | Size of the grid against the polar axis                                                      |
| **resolution** `required` | number  | degree | Angular space allocated to one data point along this axis                                    |
| **offset**                | number  | degree | Angular axis offset                                                                          |
| **motionDeviceId**        | integer |   -    | Reference to the unique id of a [motionDevice](motion-devices.md#motiondevices) object |
| **name**                  | string  |   -    | Name or reference of this dimension                                                          |
| **unit**                  | string  |   -    | Unit of the axis values, e.g. `Meter`, `Degree`, `Revolution`                                |

**Related objects**: [motionDevice](motion-devices.md#motiondevices)

## **allCycle**
<!-- md:json_type object -->
<!-- md:version 4.3.0 -->

The **allCycle** mapping stores every acquisition cycle individually along with the encoder position recorded at that cycle. Acquisition cycles are uniformly spaced in time at the acquisition rate specified in [acquisitionUnits](./acquisition-units.md). A separate dataset is created for each motion device.

| Property     | Type  | Description                                                       |
| :----------- | :---- | :---------------------------------------------------------------- |
| **datasets** | array | A [datasets](#datasets) array describing encoder positioning data |

### **datasets**
<!-- md:json_type array -->

| Property                  | Type    | Description                                                                      |
| :------------------------ | :------ | :------------------------------------------------------------------------------- |
| **id**                    | integer | Unique dataset id within the `allCycle` object                                   |
| **dataClass**             | string  | Type of data stored, in this case, data class is `Encoder`                       |
| **dataValue** `required`  | object  | A [dataValue](#datavalue) object describing the encoding of stored values        |
| **dimensions** `required` | array   | A [dimensions](#dimensions) array — always a single `AcquisitionCycle` dimension |
| **path**                  | string  | Path to the dataset in the HDF5 structure                                        |

#### **dataValue**
<!-- md:json_type object -->

| Property               | Type    | Description                                                  |
| :--------------------- | :------ | :----------------------------------------------------------- |
| **unit** `required`    | string  | Unit of the stored values, e.g. `Step`, `Meter`, or `Degree` |
| **unitMin** `required` | number  | Minimum value representable in the stored integer unit       |
| **unitMax** `required` | number  | Maximum value representable in the stored integer unit       |
| **min** `required`     | number  | Minimum physical value mapped to `unitMin`                   |
| **max** `required`     | number  | Maximum physical value mapped to `unitMax`                   |

#### **dimensions**
<!-- md:json_type array -->

Because a separate dataset is created for each motion device, `allCycle` datasets are always 1D.

| Property                | Type    | Description                                                                                                                                          |
| :---------------------- | :------ | :--------------------------------------------------------------------------------------------------------------------------------------------------- |
| **axis** `required`     | string  | Always `AcquisitionCycle`                                                                                                                            |
| **quantity** `required` | integer | Total number of cycles in the dataset                                                                                                                |
| **motionDeviceId**      | integer | Reference to the unique id of a [motionDevice](motion-devices.md#motiondevices) used to populate the dataset                                         |
| **orientation**         | string  | Specimen axis on which the encoder is aligned, one of `UCoordinate` or `VCoordinate`                                                                 |
| **lastCellRewrited**    | integer | When the acquisition is performed in time mode (no encoder), this axis is a circular buffer in which the first position is given in lastCellRewrited |

## Examples

=== "discreteGrid"
    ``` json
    "dataMappings": [
      {
        "id": 0,
        "specimenId": 0,
        "surfaceId": 0,
        "discreteGrid": {
          "scanPattern": "OneLineScan",
          "uCoordinateOrientation": "Length",
          "dimensions": [
            {
              "axis": "UCoordinate",
              "motionDeviceId": 0,
              "name": "Scan",
              "offset": 0.042,
              "quantity": 45,
              "resolution": 0.001
            }
          ]
        }
      },
      {
      "id": 1,
      "specimenId": 0,
      "surfaceId": 0,
      "discreteGrid": {
        "scanPattern": "RasterScan",
        "uCoordinateOrientation": "Around",
        "dimensions": [
          {
            "motionDeviceId": 0,
            "axis": "UCoordinate",
            "offset": 0,
            "quantity": 250,
            "resolution": 1,
            "unit": "Revolution"
          },
          {
            "motionDeviceId": 1,
            "axis": "Polar",
            "offset": 0,
            "quantity": 600,
            "resolution": 0.6,
            "unit": "Degree"
          }
        ]
      }
    }
    ]
    ```

=== "allCycle"
    ``` json
    "dataMappings": [
      {
        "id": 0,
        "specimenId": 0,
        "surfaceId": 0,
        "allCycle": {
          "datasets": [
            {
              "id": 0,
              "dataClass": "Encoder",
              "dataValue": {
                "unit": "Step",
                "unitMax": 2147483647,
                "unitMin": -2147483648,
                "max": 2147483647,
                "min": -2147483648
              },
              "dimensions": [
                {
                  "axis": "AcquisitionCycle",
                  "quantity": 5261,
                  "orientation": "UCoordinate",
                  "motionDeviceId": 0
                }
              ],
              "path": "/Public/DataMappings/0/Datasets/0-Encoder"
            }
          ]
        }
      }
    ]
    ```
