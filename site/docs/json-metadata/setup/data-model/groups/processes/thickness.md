# **thickness** object

The **thickness** object serves as thickness measurement process description.

| Property   | Type   | Unit | Description           |
| :--------- | :----- | :--: | :-------------------- |
| **min***   | number |  m   |                       |
| **max***   | number |  m   |                       |
| **gates*** | array  |  -   | [gates](#gates-array) |


## **gates** array

The **gates** array lists the different gates used for the thickness measurement. 

| Property           | Type   | Description                                                                       |
| :----------------- | :----- | :-------------------------------------------------------------------------------- |
| **id***            | number | The unique id of the gate                                                         |
| **gateDetection*** | string | Type of gate detection, one of `Crossing`, `MaximumPeak`, `FirstPeak`, `LastPeak` |


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

