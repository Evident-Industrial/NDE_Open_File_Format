# Acquisition Units

<!-- md:json_type array -->

The **acquisitionUnits** array lists the acquisition units used for the capture of the datasets and their parameters.

## **acquisitionUnits** 
<!-- md:json_type array -->

| Property                       | Type    | Unit | Description                                                                             |
| :----------------------------- | :------ | :--: | :-------------------------------------------------------------------------------------- |
| **id** `required`              | integer |  -   | Unique acquisition unit id, referenced in the [elements](probes.md#elements) of a probe |
| **platform** `required`        | string  |  -   | Name of the acquisition unit platform                                                   |
| **model** `required`           | string  |  -   | Model of the acquisition unit                                                           |
| **serialNumber**               | string  |  -   | Serial number of the acquisition unit                                                   |
| **name**                       | string  |  -   | Name of the acquisition unit                                                            |
| **acquisitionRate** `required` | number  |  Hz  | Acquisition rate of the acquisition unit                                                |

**Related objects**: [probes](probes.md#probes), [elements](probes.md#elements)

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
    },
    {
      "id": 0,
      "model": "N700",
      "platform": "Nortec 700",
      "acquisitionRate": 4000
    }
]
```
