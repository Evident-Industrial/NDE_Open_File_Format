# Data Mapping Related Arrays and Objects

Independently of the nondestructive evaluation method, there's always a need to relate acquisition data to the inspected specimen in terms of positioning. There exist, however, diametrically opposed use cases calling for adapted methods to achieve this relationship. For example, most PAUT weld inspections with scanners will relate the data positioning relative to the surface itself with a constant resolution. 

On the other hand, one could acquire and store phased array acquisition data with a 6-axis robot and use complex post-processing methods to achieve inspection data positioning. The **dataMappings** array specifies how inspection data relates to the specimen. 

## **dataMappings** array

The **dataMappings** array describes the relationship between data and the specimen through the scenario coordinate system.

| Property                    | Type    | Description                                      |
| :-------------------------- | :------ | :----------------------------------------------- |
| **id** `required`           | integer | The unique data mapping id in the JSON structure |
| **specimenId** `required`   | integer | A unique specimen id in the JSON structure       |
| **surfaceId** `required`    | integer | A unique surface id in the JSON structure        |
| **discreteGrid** `required` | object  | A [discreteGrid](#discretegrid-object) object    |

### **discreteGrid** object

The **discreteGrid** object describes the properties of the scanning grid and its dimensions. 

| Property                              |  Type  | Description                                                                                             |
| :------------------------------------ | :----: | :------------------------------------------------------------------------------------------------------ |
| **scanPattern** `required`            | string | One of the following scan patterns: `OneLineScan` or `RasterScan`                                          |
| **uCoordinateOrientation** `required` | string | One of the following U coordinate orientations: `Around`, `Along`, `Width`, or `Length`                     |
| **dimensions** `required`             | array  | An array of [UCoordinate](#ucoordinate-object) and/or [VCoordinate](#vcoordinate-object) axis object(s) |

**Related objects**: [specimens](specimens.md#specimens-array), [surfaces](specimens.md#surfaces-array)

#### **UCoordinate** object

The **UCoordinate** object describes the discrete grid U dimension. 

| Property                  | Type    | Unit | Description                                                                                                                                          |
| :------------------------ | :------ | :--: | :--------------------------------------------------------------------------------------------------------------------------------------------------- |
| **axis** `required`       | string  |  -   | The name of the axis, necessarily `UCoordinate`                                                                                                      |
| **quantity** `required`   | integer |  -   | The size of the grid against the U axis                                                                                                              |
| **resolution** `required` | number  |  m   | The resolution along this axis                                                                                                                       |
| **offset**                | number  |  m   | The axis offset                                                                                                                                      |
| **motionDeviceId**        | integer |  -   | Reference to the unique Id of a [motionDevice](motion-devices.md#motiondevices-array) object                                                         |
| **name**                  | string  |  -   | The name or reference of this dimension.                                                                                                             |
| **lastCellRewrited**      | integer |  -   | When the acquisition is performed in Time mode (no encoder), this axis is a circular buffer in which the first position is given in lastCellRewrited |

**Related objects**: [motionDevice](motion-devices.md#motiondevices-array)

#### **VCoordinate** object

The **VCoordinate** object describes the discrete grid V dimension. 

| Property                  | Type    | Unit | Description                                                                                  |
| :------------------------ | :------ | :--: | :------------------------------------------------------------------------------------------- |
| **axis** `required`       | string  |  -   | The name of the axis, necessarily `VCoordinate`                                              |
| **quantity** `required`   | integer |  -   | The size of the grid against the U axis                                                      |
| **resolution** `required` | number  |  m   | The resolution along this axis                                                               |
| **offset**                | number  |  m   | The axis offset                                                                              |
| **motionDeviceId**        | integer |  -   | Reference to the unique Id of a [motionDevice](motion-devices.md#motiondevices-array) object |
| **name**                  | string  |  -   | The name or reference of this dimension.                                                     |

**Related objects**: [motionDevice](motion-devices.md#motiondevices-array)

## Example

```json
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
}
]
```