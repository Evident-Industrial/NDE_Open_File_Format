# Motion Device Related Arrays and Objects

## **motionDevices** array

This array list the motion devices used to move the probe(s) over the specimen.

| Property               | Type    | Description                                                                                                                                       |
| :--------------------- | :------ | :------------------------------------------------------------------------------------------------------------------------------------------------ |
| **id** `required`      | integer | The unique motion device id in the JSON structure referenced in `dimensions` array of [discreteGrid](data-mappings.md#discretegrid-object) object |
| **name**               | string  | Name of the motion device                                                                                                                         |
| **encoder** `required` | object  | An [encoder](#encoder-object) object                                                                                                              |

**Related objects**: [discreteGrid](data-mappings.md#discretegrid-object), [UCoordinate](data-mappings.md#ucoordinate-object), [VCoordinate](data-mappings.md#vcoordinate-object)

### **encoder** object

This object describes a generic encoder used to register the position of a motion device.

| Property                      | Type   |  Unit  | Description                                                                                                            |
| :---------------------------- | :----- | :----: | :--------------------------------------------------------------------------------------------------------------------- |
| **serialNumber**              | string |   -    | The serial number of the encoder                                                                                       |
| **mode** `required`           | string |   -    | One of the following encoder pulse mode used for recording the position: `Quadrature`,`ClockDir`,`PulseUp`,`PulseDown` |
| **stepResolution** `required` | number | m/step | Resolution of the encoder                                                                                              |
| **preset**                    | number |   -    | Preset value                                                                                                           |

```json title="Example"
"motionDevices": [
    {
      "id": 0,
      "name": "Default",
      "encoder": {
        "mode": "Quadrature",
        "stepResolution": 12.0,
        "preset": 0.0
      }
    }
]
```