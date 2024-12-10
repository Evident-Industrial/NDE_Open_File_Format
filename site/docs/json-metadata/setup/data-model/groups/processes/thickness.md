# **thickness** Object

The **thickness** object serves as thickness measurement process description.

| Property             | Type   | Unit | Description           |
| :------------------- | :----- | :--: | :-------------------- |
| **min** `required`   | number |  m   |                       |
| **max** `required`   | number |  m   |                       |
| **gates** `required` | array  |  -   | [gates](#gates-array) |


## **gates** array

The **gates** array lists the different gates used for the thickness measurement. 

| Property                     | Type   | Description                                                                       |
| :--------------------------- | :----- | :-------------------------------------------------------------------------------- |
| **id** `required`            | number | The unique id of the gate                                                         |
| **gateDetection** `required` | string | Type of gate detection, one of the following: `Crossing`, `MaximumPeak`, `FirstPeak`, `LastPeak` |

## Example

```json
"thickness": {
    "min": 0.00375,
    "max": 0.01575,
    "gates": [
        {
        "id": 1,
        "timeSelection": "Peak"
        }
    ]
}
```

