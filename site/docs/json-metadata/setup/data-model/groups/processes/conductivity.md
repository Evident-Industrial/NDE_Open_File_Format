# **conductivity**
<span class="badge-et">ET</span>
<!-- md:json_type object -->
<!-- md:version 4.3.0 -->

The **conductivity** process converts complex impedance measurements into material electrical conductivity values and probe lift-off distances.

| Property                  | Type  | Description                           |
| :------------------------ | :---- | :------------------------------------ |
| **references** `required` | array | A [**references**](#references) array |

## **references**
<!-- md:json_type array -->
<!-- md:version 4.3.0 -->

| Property                    | Type    | Unit | Description                                                                     |
| :-------------------------- | :------ | :--: | :------------------------------------------------------------------------------ |
| **id** `required`           | integer |  -   | Unique id of the reference acquisition for conductivity and lift evaluation     |
| **conductivity** `required` | number  | S/m  | Conductivity associated to the impedance measurement                            |
| **lift** `required`         | number  |  m   | Lift associated to the impedance measurement                                    |
| **impedance** `required`    | object  |  -   | An [**impedance**](#impedance) object                                           |

### **impedance**
<!-- md:json_type object -->
<!-- md:version 4.3.0 -->

| Property                 | Type   |   Unit    | Description                                             |
| :----------------------- | :----- | :-------: | :------------------------------------------------------ |
| **real** `required`      | number | bit count | Real amplitude recorded on the reference point          |
| **imaginary** `required` | number | bit count | Imaginary amplitude recorded on the reference point     |

## Example

``` json
"conductivity": {
    "references": [
        {
            "id": 0,
            "conductivity": 31876345,
            "lift": 0.0,
            "impedance": {
                "real": 187665,
                "imaginary": 87664
            }
        },
        {
            "id": 1,
            "conductivity": 43987542,
            "lift": 0.0,
            "impedance": {
                "real": 76553728,
                "imaginary": 12857
            }
        }
    ]
}
```
