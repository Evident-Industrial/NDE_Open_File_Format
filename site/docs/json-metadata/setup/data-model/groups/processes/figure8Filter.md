# **figure8Filter**
<span class="badge-et">ET</span>
<!-- md:json_type object -->
<!-- md:version 4.3.0 -->

The **figure8Filter** process is a specialized digital signal processing filter used in eddy current inspection systems, applied to data with constant sampling frequency (spatial in `PerMeter` or temporal in `Hz`).

| Property                       | Type   | Description                                      |
| :----------------------------- | :----- | :----------------------------------------------- |
| **cutoffFrequency** `required` | number | Filter cutoff frequency                          |
| **cutoffUnits** `required`     | string | Unit of the cutoff frequency: `Hz` or `PerMeter` |

## Example

```json
"figure8Filter": {
    "cutoffFrequency": 83.3,
    "cutoffUnits": "Hz"
}
```
