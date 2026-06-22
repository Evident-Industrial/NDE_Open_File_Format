# **eddyCurrent**
<span class="badge-et">ET</span>
<!-- md:json_type object -->
<!-- md:version 4.3.0 -->

The **eddyCurrent** object serves as a general purpose eddy current acquisition process.

| Property                      | Type    | Unit | Description                                                                                                            |
| :---------------------------- | :------ | :--: | :--------------------------------------------------------------------------------------------------------------------- |
| **probeId** `required`        | integer |  -   | The id of the probe used                                                                                               |
| **sensorGroupId** `required`  | integer |  -   | The sensor group associated to this process, defined in the corresponding [probe](../../probes.md#sensorgroups) object |
| **driveAmplitude** `required` | number  |  V   | Peak output voltage setting of the acquisition unit                                                                    |
| **frequency** `required`      | number  |  Hz  | Test frequency associated to this group                                                                                |
| **gain**                      | number  |  dB  | Hardware gain applied to all channels                                                                                  |
| **channels** `required`       | array   |  -   | A [**channels**](#channels) array                                                                                      |

!!! info "Drive Amplitude"
    The drive amplitude may differ from the voltage at the coil level since output impedance, load resistors, and multiplexer amplification are not accounted for here.

## **channels**
<span class="badge-et">ET</span>
<!-- md:json_type array -->
<!-- md:version 4.3.0 -->

| Property                | Type    | Description                                                                                                                     |
| :---------------------- | :------ | :------------------------------------------------------------------------------------------------------------------------------ |
| **id** `required`       | integer | Unique id of the channel within the eddyCurrent process                                                                         |
| **sensorId** `required` | integer | The sensor associated to this channel, refers to a sensor defined in the sensorGroup                                            |
| **inputId**             | integer | The analog eddy current signal input associated to this channel acquisition                                                     |
| **timeslot**            | integer | The discrete moment in the multiplexing sequence when a specific sensor is energized and its response is measured                |

## Example

``` json
 "eddyCurrent": {
    "probeId": 0,
    "driveAmplitude": 1.0,
    "gain": 1.0,
    "channels": [
        {
        "id": 0,
        "sensorId": 0,
        "timeslot": 0,
        "inputId": 0
        }
    ],
    "sensorGroupId": 0,
    "frequency": 2000.0
}
```
