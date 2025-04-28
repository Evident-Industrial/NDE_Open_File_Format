# **ultrasonicMatrixCapture** Object

The **ultrasonicMatrixCapture** object serves as a generic ultrasonic acquisition process designed to accommodate both simple and advanced use cases. It is based on the assumption that the majority of ultrasonic acquisition processes follow an emission/reception sequence where one or several ultrasonic elements are involved. 

Each single emission/reception sequence is described by a [beam](#beams-array) with corresponding pulsers (emitters) and receivers (similar to focal laws). For each beam, a column is partially filled in the [corresponding dataset](../datasets.md) along a StackedAScan axis. When all beams have been fired, a complete column is filled. The next column is filled using the same sequence but at a different physical location (like using an encoder). 


| Property                                                                                         | Type   | Description                                                                                                      |
| :----------------------------------------------------------------------------------------------- | :----- | :--------------------------------------------------------------------------------------------------------------- |
| **acquisitionPattern** `required`                                                                | string | Short description of the pattern used, one of the following: `FMC`, `HMC`, `PWI`, or `Sparse`                                      |
| **digitizingFrequency** `required`                                                               | number | Net digitizing frequency used for all beams                                                                      |
| **pulserFrequency** `required`                                                                   | number | Pulser frequency used for all beams in Hz                                                                        |
| **digitalBandPassFilter**                                                                        | object | A [**digitalBandPassFilter**](#digitalbandpassfilter-object) object describing the applied filters for all beams |
| **waveforms** `required`                                                                         | array  | An array of [**waveforms**](#waveforms-array) objects describing the signal used for a given beam                |
| **beams**  `required`                                                                            | array  | An array of [**beams**](#beams-array) objects describing a sequence of emission and reception                    |
| If applicable, one of the following subobjects: [**planeWaveImaging**](#planewaveimaging-object) | object |                                                                                                                  |



## **digitalBandPassFilter** object 

| Property                            | Type   | Description                                    |
| :---------------------------------- | :----- | :--------------------------------------------- |
| **filterType** `required`           | string | Type of filter                                 |
| **highCuttOffFrequency** `required` | number | High cutoff frequency of the BP filter in Hz |
| **lowCuttOffFrequency** `required`  | number | Low cutoff frequency of the BP filter in Hz  |
| **characteristic** `required`       | string | Characteristic of the filter                   |

## **waveforms** array 

Arbitrary waveforms will be introduced later.

<table>
<thead>
  <tr>
    <th>Property</th>
    <th>Type</th>
    <th>Description</th>
  </tr>
</thead>
<tbody>
  <tr>
    <td><b>id</b>  <code>required</code> </td>
    <td>integer</td>
    <td>The unique waveform id in the JSON structure</td>
  </tr>
  <tr>
    <td>The following subobject: 
        <ul>
            <li><b><a href="#pulse-object">pulse </a></b>  <code>required</code></li>
        </ul> 
    </td>
    <td>object</td>
    <td></td>
  </tr>
</tbody>
</table>

### **pulse** object

| Property                | Type   | Description                                  |
| :---------------------- | :----- | :------------------------------------------- |
| **width** `required`    | number | Pulse width in seconds                       |
| **voltage** `required`  | number | Pulse peak-to-peak voltage in volts          |
| **polarity** `required` | string | Pulse polarity, either: `Unipolar` or `Bipolar` |

## **beams** array 

| Property                 | Type   | Description                                                      |
| :----------------------- | :----- | :--------------------------------------------------------------- |
| **id** `required`        | number | Unique Id of the beam                                            |
| **pulsers** `required`   | array  | Array describing the different pulsers parameters for the beam   |
| **receivers** `required` | array  | Array describing the different receivers parameters for the beam |

### **pulsers** object 

| Property                  | Type   | Description                                  |
| :------------------------ | :----- | :------------------------------------------- |
| **id** `required`         | number | Unique Id of the pulser                      |
| **elementId** `required`  | number | Probe element Id used by the pulser          |
| **probeId** `required`    | number | Probe Id acting as the emitter in the beam   |
| **delay** `required`      | number | Delay applied when pulsing with this element |
| **waveformId** `required` | number | Signal used when pulsing with this element   |

### **receivers** object 

| Property                   | Type   | Description                                                    |
| :------------------------- | :----- | :------------------------------------------------------------- |
| **id** `required`          | number | Unique Id of the receiver                                      |
| **elementId** `required`   | number | Probe element Id used by the receiver                          |
| **probeId** `required`     | number | Probe Id acting as the receiver in the beam                   |
| **ascanStart** `required`  | number | When recording of the A-scan starts for this receiver in seconds |
| **ascanLength** `required` | number | Time duration of the A-scan samples saved for this receiver       |

## **planeWaveImaging** object 

| Property          | Type   | Description                                                                         |
| :---------------- | :----- | :---------------------------------------------------------------------------------- |
| **quantityAngle** | number | Number of angle steps (number of beams to be formed)                                |
| **velocity**      | number | Wave velocity used for the delay calculation                                            |
| **waveLocation**  | string | In which leg the plane wave must be formed, one of the following: `Wedge`, `FirstLeg`, or `SecondLeg` |
| **waveMode**      | string | Wave mode considered for the delay calculation                                          |
| **startAngle**    | number | Sweeping start angle                                                                |
| **stopAngle**     | number | Sweeping stop angle                                                                 |


## Examples

??? quote "ultrasonicMatrixCapture processes examples for different configurations"

    === "FMC"
        ``` json
        --8<-- "docs/assets/json/json-metadata/setup/data-model/ultrasonicMatrixCapture-FMC.json"
        ``` 
    === "PWI"
        ``` json
        --8<-- "docs/assets/json/json-metadata/setup/data-model/ultrasonicMatrixCapture-PWI.json"
        ```

