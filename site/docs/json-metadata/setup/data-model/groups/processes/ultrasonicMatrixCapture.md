# **ultrasonicMatrixCapture** object

The **ultrasonicMatrixCapture** object serves as a generic ultrasonic acquisition process aims at covering simple and advanced cases. It is based on the assumption that the majority of ultrasonic acquisition processes follow an emission/reception sequence where one or several ultrasonic elements are involved. 

Each single emission/reception sequence is described by a [beam](#beams-array) with corresponding pulsers (emitters) and receivers (similar to focal laws). For each beam, an elementaryAScan column is partially filled in the corresponding dataset. When all beams have been fired, a complete elementaryAScan column is filled. The next column is filled using the same sequence but at a different physicial location (like using and encoder). Having a different sequence (i.e. different focal laws) for each physical location is not supported but could be through proper difinition of sequences referencing specific beams elements (let me know if interested ..). 


| Property                                                                                         | Type   | Description                                                                 |
| :----------------------------------------------------------------------------------------------- | :----- | :-------------------------------------------------------------------------- |
| **acquisitionPattern***                                                                          | string | Short description of the pattern used, one of `FMC`, `HMC`, `PWI`, `Sparse` |
| **digitizingFrequency***                                                                         | number | Net Digitizing Frequency used for all frames                                |
| **pulserFrequency***                                                                             | number | Pulser Frequency used for all frames in Hz                                  |
| [**digitalBandPassFilter**](#digitalbandpassfilter-object)                                       | object | A digitalBandPassFilter object describing the applied filters for all beams |
| [**waveforms**](#waveforms-array)*                                                               | array  | An array of waveforms object describing the signal used for a given frame   |
| [**beams**](#beams-array)*                                                                       | array  | An array of beams objects describing a sequence of emission and reception   |
| If applicable, one of the following sub-object: [**planeWaveImaging**](#planewaveimaging-object) | object |                                                                             |



## **digitalBandPassFilter** object 

| Property                  | Type   | Description                                    |
| :------------------------ | :----- | :--------------------------------------------- |
| **filterType***           | string | Type of filter                                 |
| **highCuttOffFrequency*** | number | High cutt-off Frequency of the BP Filter in Hz |
| **lowCuttOffFrequency***  | number | Low cutt-off Frequency of the BP Filter in Hz  |
| **characteristic***       | string | Characteristic of the filter                   |

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
    <td><b>id*</b></td>
    <td>integer</td>
    <td>The unique waveform id in the JSON structure</td>
  </tr>
  <tr>
    <td>One of the following sub-object: 
        <ul>
            <li><b><a href="#pulse-object">pulse*</a></b></li>
        </ul> 
    </td>
    <td>object</td>
    <td></td>
  </tr>
</tbody>
</table>

### **pulse** object

| Property      | Type   | Description                                  |
| :------------ | :----- | :------------------------------------------- |
| **width***    | number | Pulse width in seconds                       |
| **voltage***  | number | Pulse peak-to-peak voltage in volts          |
| **polarity*** | string | Pulse polarity, one of `Unipolar`, `Bipolar` |

## **beams** array 

| Property       | Type   | Description                                                       |
| :------------- | :----- | :---------------------------------------------------------------- |
| **id***        | number | Unique Id of the frame                                            |
| **pulsers***   | array  | Array describing the different pulsers parameters for the frame   |
| **receivers*** | array  | Array describing the different receivers parameters for the frame |

### **pulsers** object 

| Property            | Type   | Description                                  |
| :------------------ | :----- | :------------------------------------------- |
| **id***             | number | Unique Id of the pulser                      |
| **elementId***      | number | Probe element Id used by the pulser          |
| **probeId*** | number | Probe Id acting as the emitter in the frame  |
| **delay***          | number | Delay applied when pulsing with this element |
| **waveformId***     | number | Signal used when pulsing with this element   |

### **receivers** object 

| Property         | Type   | Description                                                    |
| :--------------- | :----- | :------------------------------------------------------------- |
| **id***          | number | Unique Id of the receiver                                      |
| **elementId***   | number | Probe element Id used by the receiver                          |
| **probeId***     | number | Probe Id acting as the receiver in the frame                   |
| **ascanStart***  | number | When recording of the ascan start for this receiver in seconds |
| **ascanLength*** | number | Time extent of the ascan samples saved for this receiver       |

## **planeWaveImaging** object 

| Property          | Type   | Description                                                                         |
| :---------------- | :----- | :---------------------------------------------------------------------------------- |
| **quantityAngle** | number | Number of angle steps (number of beams to be formed)                                |
| **velocity**      | number | Wave velocity used for delay calculation                                            |
| **waveLocation**  | string | In which leg the plane wave must be formed, one of `WEdge`, `FirstLeg`, `SecondLeg` |
| **waveMode**      | string | Wave mode considered for delay calculation (IS IT USEFUL?)                          |
| **startAngle**    | number | Sweeping start angle                                                                |
| **stopAngle**     | number | Sweeping stop angle                                                                 |




