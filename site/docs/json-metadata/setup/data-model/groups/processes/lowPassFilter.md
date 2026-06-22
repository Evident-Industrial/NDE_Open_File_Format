# **lowPassFilter**
<span class="badge-et">ET</span>
<!-- md:json_type object -->
<!-- md:version 4.3.0 -->

The **lowPassFilter** object describes a generic low-pass (LP) filter process applied to eddy current data with constant sampling frequency (spatial in `PerMeter` or temporal in `Hz`).

| Property                       | Type   | Description                                      |
| :----------------------------- | :----- | :----------------------------------------------- |
| **cutoffFrequency** `required` | number | Filter cutoff frequency                          |
| **filterType** `required`      | string | Type of filter: `IIR` or `FIR`                   |
| **cutoffUnits** `required`     | string | Unit of the cutoff frequency: `Hz` or `PerMeter` |

## Example

```json
"lowPassFilter": {
    "cutoffFrequency": 0,
    "filterType": "IIR",
    "cutoffUnits": "Hz"
}
```
