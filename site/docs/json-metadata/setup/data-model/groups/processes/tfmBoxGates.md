# **tfmBoxGates** array

The **tfmBoxGates** array serves as a box-type gate process description for a TFM image

| Property        | Type    | Unit | Description                                                       |
| :-------------- | :------ | :--: | :---------------------------------------------------------------- |
| **id***         | integer |  -   | Unique id for the TfmBoxGates item within the TfmBoxGates process |
| **threshold**   | number  |  %   | Threshold level on the TFM image dynamic range                    |
| **yImagingMin** | number  |  m   | The start position of the box gate against the y axis             |
| **yImagingMax** | number  |  m   | The end position of the box gate against the y axis               |
| **zImagingMin** | number  |  m   | The start position of the box gate against the z axis             |
| **zImagingMax** | number  |  m   | The end position of the box gate against the z axis               |

```json
"tfmBoxGates": [
    {
        "id": 1,
        "threshold": 10.0,
        "yImagingMin": 0.0022,
        "yImagingMax": 0.0238,
        "zImagingMin": 0.0012595000000000002,
        "zImagingMax": 0.0237505
    }
]

```