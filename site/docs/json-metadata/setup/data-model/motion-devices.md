# Motion Devices

<!-- md:json_type array -->

The **motionDevices** array lists the motion devices used to move the probe(s) over the specimen.

## **motionDevices**
<!-- md:json_type array -->

| Property               | Type    | Description                                                                                                            |
| :--------------------- | :------ | :--------------------------------------------------------------------------------------------------------------------- |
| **id** `required`      | integer | Unique motion device id, referenced in the `dimensions` array of [discreteGrid](data-mappings.md#discretegrid) and [allCycle](data-mappings.md#allcycle) objects |
| **name**               | string  | Name of the motion device                                                                                              |
| **encoder** `required` | object  | An [encoder](#encoder) object                                                                                          |

**Related objects**: [UCoordinate](data-mappings.md#ucoordinate), [VCoordinate](data-mappings.md#vcoordinate), [Polar](data-mappings.md#polar), [allCycle datasets](data-mappings.md#datasets)

## **encoder**
<!-- md:json_type object -->

The **encoder** object describes a generic encoder used to register the position of a motion device.

| Property                      | Type    | Description                                                                                                                        |
| :---------------------------- | :------ | :--------------------------------------------------------------------------------------------------------------------------------- |
| **serialNumber**              | string  | Serial number of the encoder                                                                                                       |
| **mode** `required`           | string  | Encoder pulse mode: `Quadrature`, `ClockDir`, `PulseUp`, `PulseDown`, `Tach`, or `Index`                                          |
| **stepResolution** `required` | number  | Resolution of the encoder in steps per unit (meter or revolution depending on `unit`)                                              |
| **unit**                      | string  | Unit of `stepResolution`: `StepPerMeter` for linear encoders or `StepPerRevolution` for rotary encoders                           |
| **preset**                    | number  | Preset value                                                                                                                       |
| **inverted**                  | boolean | Whether the encoder counting direction was reversed                                                                                |

**Rotary encoder modes**
<!-- md:version 4.3.0 -->

- `Tach` — Each encoder step corresponds to a partial rotation. `stepResolution` defines the number of steps per revolution.
- `Index` — Each encoder step corresponds to one complete revolution. `stepResolution` is typically `1.0`.

## Examples

=== "Linear encoder"
    ``` json
    "motionDevices": [
      {
        "id": 0,
        "name": "Scan",
        "encoder": {
          "mode": "Quadrature",
          "stepResolution": 12000.0,
          "unit": "StepPerMeter",
          "preset": 0.0
        }
      }
    ]
    ```

=== "Rotary encoder"
    ``` json
    "motionDevices": [
      {
      "id": 0,
      "encoder": {
        "preset": 0,
        "inverted": false,
        "unit": "StepPerRevolution",
        "mode": "Index",
        "stepResolution": 1.0,
      }
      },
      {
        "id": 1,
        "encoder": {
          "preset": 0,
          "inverted": false,
          "unit": "StepPerRevolution",
          "mode": "Tach",
          "stepResolution": 4.0,
        }
      }
    ]
    ```
