# **ultrasonicConventional** object

The **ultrasonicConventional** object serves as a conventional ultrasonic acquisition process.

| Property                                                   | Type    | Unit | Description                                                                                    |
| :--------------------------------------------------------- | :------ | :--: | :--------------------------------------------------------------------------------------------- |
| **waveMode***                                              | string  |  -   | One of: `Longitudinal` or `TransversalVertical`                                                |
| **velocity***                                              | number  | m/s  | Material wave speed corresponding to the specified wave mode (used for beam delay calculation) |
| **wedgeDelay**                                             | number  |  s   | Delay corresponding to the sound propagation within the wedge                                  |
| **rectification**                                          | string  |  -   | RF signal rectification type, one of `None`, `Positive`, `Negative`, `Full`                    |
| **digitizingFrequency**                                    | number  |  Hz  | Sampling rate of the saved  A-Scans                                                            |
| **ascanSynchroMode**                                       | string  |  -   | Type of A-Scan syncrhonisation, one of `Pulse`, `SynchroGateRelative`                          |
| **ascanCompressionFactor**                                 | integer |  -   | Compression factor applied to A-Scans                                                          |
| **gain**                                                   | number  |  dB  | Hardware gain applied to all A-Scans                                                               |
| **ultrasoundMode**                                         | string  |  -   | Ultrasound mode, one of `TrueDepth`, `SoundPath`, `Time`                                       |
| **referenceAmplitude**                                     | number  |  %   | A-Scan Full-Screen height of the reference amplitude                                           |
| **referenceGain**                                          | number  |  dB  | Reference gain value to which other gain values will be offsetted                              |
| **smoothingFilter**                                        | number  |  Hz  | Characteristic frequency of the smoothing filter                                               |
| **averagingFactor**                                        | integer |  -   | Number of averagings                                                                           |
| [**beams**](#beams-array)                                  | array   |  -   | beams array                                                                                    |
| [**digitalBandPassFilter**](#digitalbandpassfilter-object) | object  |  -   | digitalBandPassFilter object                                                                   |
| [**pulse**](#pulse-object)                                 | object  |  -   | pulse object                                                                                   |
| [**gates**](#gates-object)                                 | array   |  -   | gates array                                                                                    |
| [**calibrationStates**](#calibrationstates-array)          | array   |  -   | calibration states array                                                                       |
| One of the following sub-object: <ul><li><b><a href="#pulseecho-object">pulseEcho*</a></b></li><li><b><a href="#pitchcatch-object-object">pitchCatch*</a></b></li><li><b><a href="#tofd-object">tofd*</a></b></li></ul> |         |      |                                                              |

NOTES:

- **Compression**: Currently, the default compression behavior consists in keeping the maximum value of N consecutive acquisition points in time, N being the value store as the **ascanCompressionFactor**. 



## **pulseEcho** object 

The **pulseEcho** object list the probe used in an acquisition pattern where the same probe is used at emission and reception.

| Property    | Type    | Description                                                              |
| :---------- | :------ | :----------------------------------------------------------------------- |
| **probeId** | integer | The id of the probe used at emission and reception in a pulse-echo setup |

## **pitchCatch** object 

The **pitchCatch** object lists the probes used in an acquisition pattern where one probe is used at emission and an other at reception.

| Property            | Type    | Description                                                 |
| :------------------ | :------ | :---------------------------------------------------------- |
| **pulserProbeId**   | integer | The id of the probe used at emission in a pitch-catch setup |
| **receiverProbeId** | integer | The id of the probe used at emission in a pitch-catch setup |

## **tofd** object 

The **tofd** object describes the time-of-flight (TOFD) diffraction technique parameters.

| Property            | Type    | Unit | Description                                                                                                       |
| :------------------ | :------ | :--: | :---------------------------------------------------------------------------------------------------------------- |
| **pulserProbeId**   | integer |  -   | The id of the probe used at emission  in a TOFD setup                                                            |
| **receiverProbeId** | integer |  -   | The id of the probe used at reception in a TOFD setup                                                            |
| **pcs**             | number  |  m   | The probe center separation (PCS) in meters, the distance between the exit points of the two probes used for TOFD |

## **digitalBandPassFilter** object 

The **digitalBandPassFilter** object describes the band-pass filter parameters applied during acquisition.

| Property                 | Type   | Unit | Description                                                           |
| :----------------------- | :----- | :--: | :-------------------------------------------------------------------- |
| **filterType***          | string |  -   | The type of filter, one of: `None`, `LowPass`, `HighPass`, `BandPass` |
| **highCutOffFrequency*** | number |  Hz  | High cutoff frequency in Hz                                           |
| **lowCutOffFrequency***  | number |  Hz  | Low cutoff frequency in Hz                                            |
| **characteristic***      | string |  -   | One of: `None`, `TOFD`                                                |

## **pulse** object 

| Property     | Type   | Unit | Description                                                                                                                                                                                         |
| :----------- | :----- | :--: | :-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **width***   | number |  s   | Time duration, in seconds, of the high-voltage square pulse used to excite the transducer element                                                                                                   |
| **voltage*** | number |  V   | Amplitude, in Volts, of the square pulse used to excite the transducer element                                                                                                                      |
| **polarity** | string |  -   | Polarity of the square pulse used to excite the transducer element, one of: `Bipolar`, `UnipolarPositive`, `UnipolarNegative`. A `Bipolar` pulse is assumed to be negative first and then positive. |

![pulse.png](../../../../../assets/images/json-metadata/setup/data-model/groups/processes/pulse.png){width="50%"}

## **tcg** object 

The **tcg** object lists the Time-Corrected Gain (TCG) parameters used for the acquisition.

| Property                     | Type    | Description                                              |
| :--------------------------- | :------ | :------------------------------------------------------- |
| **synchroMode**              | string  | One of `Pulse` or `AscanSynchroRelative`                 |
| [**points***](#points-array) | array   | TCG [**points**](#points-array) array                    |

### **points** array

The **points** array lists the Time-Corrected Gain (TCG) points, with the corresponding gain to apply for a given time increment. 

| Property  | Type   | Unit | Description               |
| :-------- | :----- | :--: | :------------------------ |
| **time*** | number |  s   | Time increment in seconds |
| **gain*** | number |  dB  | Gain in decibel           |


## **gates** object 

| Property                                        | Type    | Unit | Description                                          |
| :---------------------------------------------- | :------ | :--: | :--------------------------------------------------- |
| **id***                                         | integer |  -   | Unique id of the gate within the acquisition process |
| **name**                                        | string  |  -   | Name of the gate  (e.g. "A", "B", "I" etc.)          |
| **geometry**                                    | string  |  -   | One of `SoundPath` or `TrueDepth`                    |
| **start***                                      | number  |  s   | Gate starting time                                   |
| **length***                                     | number  |  s   | Gate time extent                                     |
| **threshold***                                  | number  |  %   | Threshold level                                      |
| **thresholdPolarity***                          | string  |  -   | One of `Absolute`, `Positive` or `Negative`          |
| [**synchronization***](#synchronization-object) | object  |  -   | [synchronization](#synchronization-object) object    |

## **beams** array 

| Property               | Type    | Unit | Description                                                                      |
| :--------------------- | :------ | :--: | :------------------------------------------------------------------------------- |
| **id***                | integer |  -   | The unique id of the beam within the ultrasonicPhasedArray process               |
| **refractedAngle***    | number  |  °   | The refracted angle of the wavefront in the specimen used for this specific beam |
| **beamDelay***         | number  |  s   |                                                                                  |
| **ascanstart***        | number  |  s   | When recording of the ascan start for this beam                                  |
| **acanLength***        | number  |  s   | Time extent of each A-Scan for this beam                                         |
| **recurrence**         | number  |      |                                                                                  |
| [**tcg**](#tcg-object) | object  |   -   | [tcg](#tcg-object) object                                                        |

### **synchronization** object 

| Property            | Type    | Description                                                                                                                                                      |
| :------------------ | :------ | :--------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **mode**            | string  | Synchronization mode, one of: `Pulse` or `GateRelative`                                                                                                          |
| **triggeringEvent** | string  | When synchronization is performed against a gate (`GateRelative`), the synchronization triggering event, one of: `Peak` or `Crossing`                            |
| **gateId**          | integer | When synchronization is performed against a gate (`GateRelative`), the corresponding gate Id in the ultrasonic acquisition process [gates](#gates-object) object |

## **calibrationStates** array 

The **calibrationStates** array lists the calibration status (through a [calibrationState](#calibrationstate-object) object), of a given calibration method, as listed below.  

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

Same structure for **sensitivityCalibration**, **tcgCalibration**, **velocityCalibration**, **wedgeDelayCalibration**, **dacCalibration**, **dgsCalibration**, **tofdWedgeDelayCalibration**.

| Property        | Type    | Description                                           |
| :-------------- | :------ | :---------------------------------------------------- |
| **calibrated*** | boolean | Indicate whether the calibration was performed or not |




