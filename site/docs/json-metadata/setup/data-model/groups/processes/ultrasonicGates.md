# **ultrasonicGates**
<span class="badge-ut">UT</span>
<!-- md:json_type object -->

The **ultrasonicGates** processes serve as gate definitions for ultrasonic data acquisition and processing. Gates can be defined at a single position (gates per group) or at multiple positions (gates per beam).

**Single Position Gates**

Each gate is defined by a single `start` offset and `length`, both applied to **all beams** in the group.

| Property                         | Type    | Unit | Description                                                |
| :------------------------------- | :------ | :--: | :--------------------------------------------------------- |
| **id** `required`                | integer |  -   | Unique id of the gate within the acquisition process       |
| **name**                         | string  |  -   | Name of the gate  (e.g., "A", "B", "I" etc.)               |
| **geometry** `required`          | string  |  -   | Either: `SoundPath` or `TrueDepth`                         |
| **start** `required`             | number  |  s   | Gate starting time                                         |
| **length** `required`            | number  |  s   | Gate time duration                                         |
| **threshold** `required`         | number  |  %   | Threshold level                                            |
| **thresholdPolarity** `required` | string  |  -   | One of the following: `Absolute`, `Positive` or `Negative` |
| **synchronization** `required`   | object  |  -   | A [synchronization](#synchronization) object               |

**Multi Position Gates**

Each gate is defined by beam-specific `starts` offsets and `lengths`, with **one start–length pair for each beam** in the group. 

| Property                         | Type    | Unit | Description                                                |
| :------------------------------- | :------ | :--: | :--------------------------------------------------------- |
| **id** `required`                | integer |  -   | Unique id of the gate within the acquisition process       |
| **name**                         | string  |  -   | Name of the gate  (e.g., "A", "B", "I" etc.)               |
| **geometry** `required`          | string  |  -   | Either: `SoundPath` or `TrueDepth`                         |
| **starts** `required`            | array   |  -   | Array of gate starting times (one per beam)                |
| **lengths** `required`           | array   |  -   | Array of gate durations (one per beam)                     |
| **threshold** `required`         | number  |  %   | Threshold level                                            |
| **thresholdPolarity** `required` | string  |  -   | One of the following: `Absolute`, `Positive` or `Negative` |
| **synchronization** `required`   | object  |  -   | A [synchronization](#synchronization) object               |


## **synchronization**
<span class="badge-ut">UT</span>
<!-- md:json_type object -->

| Property            | Type    | Description                                                                                                                                 |
| :------------------ | :------ | :------------------------------------------------------------------------------------------------------------------------------------------ |
| **mode** `required` | string  | Synchronization mode, either: `Pulse` or `GateRelative`                                                                                     |
| **triggeringEvent** | string  | When synchronization is performed relative to a gate (`GateRelative`), the synchronization triggering event is either: `Peak` or `Crossing` |
| **gateId**          | integer | When synchronization is performed relative to a gate (`GateRelative`), this is the corresponding gate Id                                    |


## Examples

=== "Single Position Gates"
    ``` json
    "ultrasonicGates": [
        {
            "id": 0,
            "name": "Gate I",
            "geometry": "SoundPath",
            "thresholdPolarity": "Positive",
            "synchronization": {
            "mode": "Pulse"
            },
            "start": 0.0000010200000000000002,
            "length": 0.00000849,
            "threshold": 20.0
        },
        {
            "id": 1,
            "name": "Gate A",
            "geometry": "SoundPath",
            "thresholdPolarity": "Positive",
            "synchronization": {
            "mode": "Pulse"
            },
            "start": 0.0000202,
            "length": 0.00000848,
            "threshold": 19.2000732421875
        },
        {...}
    ]
    ``` 
=== "Multi Position Gates"
    ``` json
    "ultrasonicGates": [
        {
            "id": 0,
            "name": "Gate I",
            "geometry": "SoundPath",
            "thresholdPolarity": "Positive",
            "synchronization": {
            "mode": "Pulse"
            },
            "starts": [0.00001, 0.00002, 0.00003],
            "lengths": [0.0005, 0.0005, 0.0005],
            "threshold": 20.0
        },
        {
            "id": 1,
            "name": "Gate A",
            "geometry": "SoundPath",
            "thresholdPolarity": "Positive",
            "synchronization": {
            "mode": "Pulse"
            },
            "starts": [0.0001, 0.0002, 0.0003],
            "lengths": [0.0005, 0.0005, 0.0005],
            "threshold": 19.2000732421875
        },
        {...}
    ]
    ```