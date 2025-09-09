# Acquisition Unit Related Arrays and Objects

## **acquisitionUnits** array

The **acquisitionUnits** array lists the acquisitions units used for the capture of the datasets and their parameters.

| Property                       | Type    | Unit | Description                                                                                                                                            |
| :----------------------------- | :------ | :--: | :----------------------------------------------------------------------------------------------------------------------------------------------------- |
| **id** `required`              | integer |  -   | The unique acquisition unit id in the JSON structure referenced in the [elements](probes.md#elements-array) of a [probe](probes.md#probes-array) array |
| **platform** `required`        | string  |  -   | The name of the acquisition unit platform                                                                                                              |
| **model** `required`           | string  |  -   | The model of the acquisition unit                                                                                                                      |
| **serialNumber**               | string  |  -   | The serial number of the acquisition unit                                                                                                              |
| **name**                       | string  |  -   | The name of the acquisition unit                                                                                                                       |
| **acquisitionRate** `required` | number  |  Hz  | The acquisition rate of the acquisition unit                                                                                                           |

**Related objects**: [probe](probes.md#probes-array), [elements](probes.md#elements-array)

## Example

```json
"acquisitionUnits": [
    {
      "id": 0,
      "platform": "OmniScan X4",
      "model": "OmniScan X4 - 64:128PR",
      "serialNumber": "12345XYZ",
      "name": "MXU",
      "acquisitionRate": 120.0
    }
]
```

