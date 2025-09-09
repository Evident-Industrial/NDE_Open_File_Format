# **ultrasonicConventional** Object

The **ultrasonicConventional** object serves as a conventional ultrasonic acquisition process.

| Property                   | Type    | Unit | Description                                                                                    |
| :------------------------- | :------ | :--: | :--------------------------------------------------------------------------------------------- |
| **waveMode** `required`    | string  |  -   | Either: `Longitudinal` or `TransversalVertical`                                                |
| **velocity** `required`    | number  | m/s  | Material wave speed corresponding to the specified wave mode (used for beam delay calculation) |
| **wedgeDelay**             | number  |  s   | Delay corresponding to the sound propagation within the wedge                                  |
| **rectification**          | string  |  -   | RF signal rectification type, one of the following: `None`, `Positive`, `Negative`, or `Full`                    |
| **digitizingFrequency**    | number  |  Hz  | Sampling rate of the saved  A-scans                                                            |
| **ascanSynchroMode**       | string  |  -   | Type of A-scan syncrhonization, either: `Pulse` or `SynchroGateRelative`                          |
| **ascanCompressionFactor** | integer |  -   | Compression factor applied to A-scans                                                          |
| **gain**                   | number  |  dB  | Hardware gain applied to all A-scans                                                           |
| **ultrasoundMode**         | string  |  -   | Ultrasound mode, one of the following: `TrueDepth`, `SoundPath`, or `Time`                                       |
| **referenceAmplitude**     | number  |  %   | A-scan full-screen height of the reference amplitude                                           |
| **referenceGain**          | number  |  dB  | Reference gain value from which other gain values will be offset                              |
| **smoothingFilter**        | number  |  Hz  | Characteristic frequency of the smoothing filter                                               |
| **averagingFactor**        | integer |  -   | The averaging ratio                                                                           |
| **beams**                  | array   |  -   | A [**beams**](#beams-array) array                                                              |
| **digitalBandPassFilter**  | object  |  -   | A [**digitalBandPassFilter**](#digitalbandpassfilter-object) object                            |
| **pulse**                  | object  |  -   | A [**pulse**](#pulse-object) object                                                            |
| **gates**                  | object  |  -   | A [**gates**](#gates-object) object                                                            |
| **calibrationStates**      | array   |  -   | A [**calibrationStates**](#calibrationstates-array) array                                      |
| One of the following <code>required</code>  subobjects: <ul><li><b><a href="#pulseecho-object">pulseEcho</a></b></li><li><b><a href="#pitchcatch-object-object">pitchCatch</a></b></li><li><b><a href="#tofd-object">tofd</a></b></li></ul> |         |      |                                                              |

NOTES:

- **Compression**: Currently, the default compression behavior consists in keeping the maximum value of N consecutive acquisition points in time, N being the value stored as the **ascanCompressionFactor**. 

## **pulseEcho** object 

The **pulseEcho** object lists the probe used in an acquisition pattern where the same probe is used at emission and reception.

| Property    | Type    | Description                                                              |
| :---------- | :------ | :----------------------------------------------------------------------- |
| **probeId** | integer | The id of the probe used at emission and reception in a pulse-echo setup |

```json title="Example"
"pulseEcho": {
    "probeId": 0
}
```

## **pitchCatch** object 

The **pitchCatch** object lists the probes used in an acquisition pattern where one probe is used at emission and another at reception.

| Property            | Type    | Description                                                 |
| :------------------ | :------ | :---------------------------------------------------------- |
| **pulserProbeId**   | integer | The id of the probe used at emission in a pitch-catch setup |
| **receiverProbeId** | integer | The id of the probe used at reception in a pitch-catch setup |

```json title="Example"
"pitchCatch": {
    "pulserProbeId": 0,
    "receiverProbeId": 1
}
```

## **tofd** object 

The **tofd** object describes the time-of-flight diffraction (TOFD) technique parameters.

| Property            | Type    | Unit | Description                                                                                                       |
| :------------------ | :------ | :--: | :---------------------------------------------------------------------------------------------------------------- |
| **pulserProbeId**   | integer |  -   | The id of the probe used at emission  in a TOFD setup                                                            |
| **receiverProbeId** | integer |  -   | The id of the probe used at reception in a TOFD setup                                                            |
| **pcs**             | number  |  m   | The probe center separation (PCS) in meters, the distance between the exit points of the two probes used for TOFD |

```json title="Example"
"tofd": {
    "pulserProbeId": 0,
    "receiverProbeId": 1,
    "pcs": 0.090666754842002512
}
```

## **digitalBandPassFilter** object 

The **digitalBandPassFilter** object describes the band-pass filter parameters applied during acquisition.

| Property                           | Type   | Unit | Description                                                           |
| :--------------------------------- | :----- | :--: | :-------------------------------------------------------------------- |
| **filterType** `required`          | string |  -   | The type of filter, one of the following: `None`, `LowPass`, `HighPass`, or `BandPass` |
| **highCutOffFrequency** `required` | number |  Hz  | High cutoff frequency in Hz                                           |
| **lowCutOffFrequency** `required`  | number |  Hz  | Low cutoff frequency in Hz                                            |
| **characteristic** `required`      | string |  -   | Either: `None` or `TOFD`                                                |

```json title="Example"
"digitalBandPassFilter": {
    "filterType": "BandPass",
    "highCutOffFrequency": 8000000.0,
    "lowCutOffFrequency": 2500000.0,
    "characteristic": "None"
}
```

## **pulse** object 

| Property               | Type   | Unit | Description                                                                                                                                                                                         |
| :--------------------- | :----- | :--: | :-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **width** `required`   | number |  s   | Time duration, in seconds, of the high-voltage square pulse used to excite the transducer element                                                                                                   |
| **voltage** `required` | number |  V   | Amplitude, in volts, of the square pulse used to excite the transducer element                                                                                                                      |
| **polarity**           | string |  -   | Polarity of the square pulse used to excite the transducer element, one of the following: `Bipolar`, `UnipolarPositive`, or `UnipolarNegative`. A `Bipolar` pulse is assumed to be negative first and then positive. |

![pulse.png](../../../../../assets/images/json-metadata/setup/data-model/groups/processes/pulse.png){width="50%"}

```json title="Example"
"pulse": {
    "width": 1.425E-07,
    "voltage": 85.0,
    "polarity": "Bipolar"
}
```

## **tcg** object 

The **tcg** object lists the time-corrected gain (TCG) parameters used for the acquisition.

| Property               | Type   | Description                               |
| :--------------------- | :----- | :---------------------------------------- |
| **synchroMode**        | string | Either: `Pulse` or `AscanSynchroRelative` |
| **points**  `required` | array  | A TCG [**points**](#points-array) array   |

### **points** array

The **points** array lists the time-corrected gain (TCG) points, with the corresponding gain to apply for a given time increment. 

| Property            | Type   | Unit | Description               |
| :------------------ | :----- | :--: | :------------------------ |
| **time** `required` | number |  s   | Time increment in seconds |
| **gain** `required` | number |  dB  | Gain in decibels           |


```json title="Example"
"tcg": {
    "points": [
    {
        "time": 0.0,
        "gain": 0.0
    },
    {
        "time": 2.4750000000000002E-05,
        "gain": 35.5
    }
    ]
}
```

## **gates** object 

| Property                         | Type    | Unit | Description                                          |
| :------------------------------- | :------ | :--: | :--------------------------------------------------- |
| **id** `required`                | integer |  -   | Unique id of the gate within the acquisition process |
| **name**                         | string  |  -   | Name of the gate  (e.g., "A", "B", "I" etc.)          |
| **geometry**                     | string  |  -   | Either: `SoundPath` or `TrueDepth`                    |
| **start** `required`             | number  |  s   | Gate starting time                                   |
| **length** `required`            | number  |  s   | Gate time duration                                     |
| **threshold** `required`         | number  |  %   | Threshold level                                      |
| **thresholdPolarity** `required` | string  |  -   | One of the following: `Absolute`, `Positive`, or `Negative`          |
| **synchronization**  `required`  | object  |  -   | A [synchronization](#synchronization-object) object  |

### **synchronization** object 

| Property            | Type    | Description                                                                                                                                                      |
| :------------------ | :------ | :--------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **mode**            | string  | Synchronization mode, either: `Pulse` or `GateRelative`                                                                                                          |
| **triggeringEvent** | string  | When synchronization is performed relative to a gate (`GateRelative`), the synchronization triggering event is either: `Peak` or `Crossing`                            |
| **gateId**          | integer | When synchronization is performed relative to a gate (`GateRelative`), the corresponding gate Id in the ultrasonic acquisition process [gates](#gates-object) object |

```json title="Example"
"gates": [
    {
    "id": 1,
    "name": "Gate A",
    "geometry": "TrueDepth",
    "thresholdPolarity": "Absolute",
    "synchronization": {
        "mode": "Pulse"
    },
    "start": 0.0,
    "length": 3.868E-05,
    "threshold": 25.0
    }
]
```

## **beams** array 

| Property                      | Type    | Unit | Description                                                                      |
| :---------------------------- | :------ | :--: | :------------------------------------------------------------------------------- |
| **id** `required`             | integer |  -   | The unique id of the beam within the ultrasonicPhasedArray process               |
| **refractedAngle** `required` | number  |  °   | The refracted angle of the wavefront in the specimen used for this specific beam |
| **beamDelay** `required`      | number  |  s   |                                                                                  |
| **ascanstart** `required`     | number  |  s   | When recording of the A-scan starts for this beam                                  |
| **acanLength** `required`     | number  |  s   | Time duration of each A-scan for this beam                                         |
| **recurrence**                | number  |      |                                                                                  |
| **tcg**                       | object  |  -   | [tcg](#tcg-object) object                                                        |


```json title="Example"
"beams": [
    {
    "id": 0,
    "refractedAngle": 60.0,
    "ascanStart": 0.0,
    "ascanLength": 3.408E-05
    }
]
```

## **calibrationStates** array 

The **calibrationStates** array lists the calibration status (through a [calibrationState](#calibrationstate-object) object) of a given calibration method, as listed below.  

| Property                      | Type   | Description                                         |
| :---------------------------- | :----- | :-------------------------------------------------- |
| **sensitivityCalibration**    | object | [calibrationState](#calibrationstate-object) object |
| **tcgCalibration**            | object | [calibrationState](#calibrationstate-object) object |
| **velocityCalibration**       | object | [calibrationState](#calibrationstate-object) object |
| **wedgeDelayCalibration**     | object | [calibrationState](#calibrationstate-object) object |
| **dacCalibration**            | object | [calibrationState](#calibrationstate-object) object |
| **dgsCalibration**            | object | [calibrationState](#calibrationstate-object) object |
| **tofdWedgeDelayCalibration** | object | [calibrationState](#calibrationstate-object) object |


### **calibrationState** object

Same structure for **sensitivityCalibration**, **tcgCalibration**, **velocityCalibration**, **wedgeDelayCalibration**, **dacCalibration**, **dgsCalibration**, and **tofdWedgeDelayCalibration**.

| Property                   | Type    | Description                                           |
| :------------------------- | :------ | :---------------------------------------------------- |
| **calibrated**  `required` | Boolean | Indicate whether the calibration was performed or not |



```json title="Example"
"calibrationStates": [
    {
    "sensitivityCalibration": {
        "calibrated": false
    }
    },
    {
    "tcgCalibration": {
        "calibrated": true
    }
    },
    {
    "velocityCalibration": {
        "calibrated": false
    }
    }
]
```

## Example

``` json
"ultrasonicConventional": {
    "pulseEcho": {
        "probeId": 0
    },
    "waveMode": "TransversalVertical",
    "velocity": 3100.0,
    "wedgeDelay": 6.4799999999999989E-06,
    "digitizingFrequency": 100000000.0,
    "pulse": {
        "width": 1.425E-07,
        "voltage": 85.0,
        "polarity": "Bipolar"
    },
    "gates": [
        {
        "id": 1,
        "name": "Gate A",
        "geometry": "TrueDepth",
        "thresholdPolarity": "Absolute",
        "synchronization": {
            "mode": "Pulse"
        },
        "start": 0.0,
        "length": 3.868E-05,
        "threshold": 25.0
        }
    ],
    "rectification": "Full",
    "ascanCompressionFactor": 6,
    "gain": 50.0,
    "ultrasoundMode": "TrueDepth",
    "referenceAmplitude": 80.0,
    "referenceGain": 0.0,
    "digitalBandPassFilter": {
        "filterType": "None",
        "highCutOffFrequency": 25000000.0,
        "lowCutOffFrequency": 250000.0,
        "characteristic": "None"
    },
    "smoothingFilter": 5000000.0,
    "averagingFactor": 1,
    "beams": [
        {
        "id": 0,
        "refractedAngle": 60.0,
        "ascanStart": 0.0,
        "ascanLength": 3.408E-05
        }
    ]
}
```

