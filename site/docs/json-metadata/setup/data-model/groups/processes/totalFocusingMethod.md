# **totalFocusingMethod** Object

The **totalFocusingMethod** object serves as a total focusing method (TFM) process description.

| Property                       | Type    | Unit | Description                                                              |
| :----------------------------- | :------ | :--: | :----------------------------------------------------------------------- |
| **id** `required`              | integer |  -   | Unique id for the totalFocusingMethod object within the process          |
| **name**                       | string  |  -   | Custom name of the totalFocusingMethod object                            |
| **signalSource**               | string  |  -   | Signal used to compute the TFM, either: `Analytic` or `Real`              |
| **gain** `required`            | number  |  dB  | Gain applied to the TFM image                                            |
| **referenceAmplitude**         | number  |  %   |                                                                          |
| **referenceGain**              | number  |  dB  |                                                                          |
| **rectangularGrid** `required` | object  |  -   | [rectangularGrid](#rectangulargrid-object) object                        |
| **fmcPulserIds**               | array   |  -   | Array listing the ids of the pulsers used to compute the TFM image       |
| **fmcReceiverIds**             | array   |  -   | Array listing the ids of the receivers used to compute the TFM image     |
| **pathName** `required`        | string  |  -   | Wave path name, often referred to as a "mode" or "view" (e.g.: "T-T", "LL-T") |
| **waveSet** `required`         | object  |  -   | [waveSet](#waveset-object) object                                        |
| **columns**                    | array   |  -   | [columns](#columns-array) array                                          |


## **rectangularGrid** object 

The **rectangularGrid** object describes the dimensions of the region of interest (ROI) used to compute the TFM.

| Property                      | Type   | Description                   |
| :---------------------------- | :----- | :---------------------------- |
| **yImagingLimits** `required` | object | [range](#range-object) object |
| **zImagingLimits** `required` | object | [range](#range-object) object |

### **range** object 

| Property                  | Type   | Unit | Description                   |
| :------------------------ | :----- | :--: | ----------------------------- |
| **min** `required`        | number |  m   | Starting position of the grid |
| **max** `required`        | number |  m   | Ending position of the grid   |
| **resolution** `required` | number |  m   | Resolution of the grid        |

```json title="Example"
"rectangularGrid": {
    "yImagingLimits": {
        "min": 0.001,
        "max": 0.025,
        "resolution": 5.1E-05
    },
    "zImagingLimits": {
        "min": 1E-05,
        "max": 0.025,
        "resolution": 8.2E-05
    }
}
```

## **waveSet** object 

The **waveSet** object describes the pathName in more details, listing the modes (or views) of the wave paths.

| Property                  | Type  | Description                                                                                                       |
| :------------------------ | :---- | :---------------------------------------------------------------------------------------------------------------- |
| **pulsings** `required`   | array | Array containing the list of modes (or views) for the forward path, either: `Longitudinal`or `TransversalVertical`  |
| **receivings** `required` | array | Array containing the list of modes (or views) for the backward path, either: `Longitudinal`or `TransversalVertical` |

```json title="Example"
"waveSet": {
    "pulsings": [
        "TransversalVertical",
        "TransversalVertical"
    ],
    "receivings": [
        "Longitudinal"
    ]
}
```

## **columns** array 

The **columns** array describes the time-corrected gain (TCG) parameters used for each column of the TFM image 

| Property               | Type    | Description                                                |
| :--------------------- | :------ | :--------------------------------------------------------- |
| **id** `required`      | integer | Unique column id of the TFM image                          |
| **gainMap** `required` | object  | An object containing TCG [**points**](#points-array) array |

### **gainMap** object

The **gainMap** contain the information related to the gain applied to the TFM image for the TCG.

| Property              | Type  | Description                           |
| :-------------------- | :---- | :------------------------------------ |
| **points** `required` | array | TCG [**points**](#points-array) array |

#### **points** array

The **points** array lists the time-corrected gain (TCG) points, with the corresponding gain to apply for a given position in the column of the TFM image. 

| Property                | Type   | Unit | Description                                   |
| :---------------------- | :----- | :--: | :-------------------------------------------- |
| **position** `required` | number |  m   | Vertical position of the point in the TFM ROI |
| **gain** `required`     | number |  dB  | Gain in decibels                               |


```json title="Example"
"columns": [
    {
    "id": 0,
    "gainMap": {
        "points": [
        {
            "position": 0.0,
            "gain": 0.0
        },
        {
            "position": 0.0080,
            "gain": 28.8
        },
        {
            "position": 0.0150,
            "gain": 33.9
        }
        ]
    }
    },
    {
    "id": 1,
    "gainMap": {
        "points": [
        {
            "position": 0.0,
            "gain": 0.0
        },
        {
            "position": 0.0080,
            "gain": 29.3
        },
        {
            "position": 0.0151,
            "gain": 34.7
        }
        ]
    }
    },
    ...
]
```

## Example

```json
"totalFocusingMethod": {
    "id": 0,
    "name": "TT-L View",
    "signalSource": "Analytic",
    "gain": 20.0,
    "referenceAmplitude": 80.0,
    "referenceGain": 0.0,
    "rectangularGrid": {
        "yImagingLimits": {
            "min": 0.001,
            "max": 0.025,
            "resolution": 5.1E-05
        },
        "zImagingLimits": {
            "min": 1E-05,
            "max": 0.025,
            "resolution": 8.2E-05
        }
    },
    "fmcPulserIds": [
        0,
        1,
        2,
        3,
        4,
        ...
    ],
    "fmcReceiverIds": [
        0,
        1,
        2,
        3,
        4,
        ...
    ],
    "pathName": "TT-L",
    "waveSet": {
        "pulsings": [
            "TransversalVertical",
            "TransversalVertical"
        ],
        "receivings": [
            "Longitudinal"
        ]
    },
    "columns": [
        {
        "id": 0,
        "gainMap": {
            "points": [
            {
                "position": 0.0,
                "gain": 0.0
            },
            {
                "position": 0.0080,
                "gain": 28.8
            },
            {
                "position": 0.0150,
                "gain": 33.9
            }
            ]
        }
        },
        {
        "id": 1,
        "gainMap": {
            "points": [
            {
                "position": 0.0,
                "gain": 0.0
            },
            {
                "position": 0.0080,
                "gain": 29.3
            },
            {
                "position": 0.0151,
                "gain": 34.7
            }
            ]
        }
        },
    ...
}
```