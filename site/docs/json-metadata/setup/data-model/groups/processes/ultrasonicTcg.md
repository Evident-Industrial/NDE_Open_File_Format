# **ultrasonicTcg**
<span class="badge-ut">UT</span>
<!-- md:json_type object -->

The **ultrasonicTcg** object serves as a Time Corrected Gain (TCG) process description. This software process applies time-dependent gain correction to compensate for signal attenuation as ultrasonic waves propagate through the specimen. 

| Property              | Type   | Description                                                      |
| :-------------------- | :----- | :--------------------------------------------------------------- |
| **synchroMode**       | string | Either: `Pulse`, `AscanSynchroRelative` or `SynchroGateRelative` |
| **points** `required` | array  | A TCG [**points**](#points) array                                |

## **points**
<span class="badge-ut">UT</span>
<!-- md:json_type array -->

| Property            | Type   | Unit | Description               |
| :------------------ | :----- | :--: | :------------------------ |
| **time** `required` | number |  s   | Time increment in seconds |
| **gain** `required` | number |  dB  | Gain in decibels          |

## Example

```json
"ultrasonicTcg": {
    "points": [
        {
        "gain": 5,
        "time": -1e-8
        },
        {
        "gain": 10,
        "time": 0.00000168
        },
        {
        "gain": 15,
        "time": 0.00000336
        }
    ]
}
```
