# **eddyCurrentMix**
<span class="badge-et">ET</span>
<!-- md:json_type object -->
<!-- md:version 4.3.0 -->

The **eddyCurrentMix** describes how two data streams are combined. This process is typically used to remove a known perturbation from a signal built from the effects of multiple sources. In this representation, $Z_1$ typically carries the useful signal along with the perturbation wile $Z_2$ mostly carries the perturbation alone.

The mixing formula is applied independently per channel:

$$
Z_{mix} = Z_1 + (k1 + \mathrm{i}\,k3)\cdot\Re(Z_2) + (k2 + \mathrm{i}\,k4)\cdot\Im(Z_2)
$$

where $Z$ denotes Impedance, $\Re$ the real part, and $\Im$ the imaginary part.

| Property                 | Type    | Description                                                                                 |
| :----------------------- | :------ | :------------------------------------------------------------------------------------------ |
| **z1InputId** `required` | integer | Id of the process input providing the $Z_1$ impedance data                                  |
| **z2InputId** `required` | integer | Id of the process input providing the $Z_2$ impedance data                                  |
| **channels** `required`  | array   | A [channels](#channels) array defining the mixing coefficients for each acquisition channel |

## **channels**
<!-- md:json_type array -->

Each entry in the **channels** array specifies the four mixing coefficients applied to a single acquisition channel.

| Property          | Type    | Description                            |
| :---------------- | :------ | :------------------------------------- |
| **id** `required` | integer | Unique channel id within the mix       |
| **k1** `required` | number  | Real scaling factor of $\Re(Z_2)$      |
| **k2** `required` | number  | Real scaling factor of $\Im(Z_2)$      |
| **k3** `required` | number  | Imaginary scaling factor of $\Re(Z_2)$ |
| **k4** `required` | number  | Imaginary scaling factor of $\Im(Z_2)$ |

## Examples

``` json
"eddyCurrentMix": {
    "z1InputId": 0,
    "z2InputId": 1,
    "channels": [
        {
            "id": 0,
            "k1": 1.0,
            "k2": 0.0,
            "k3": 0.0,
            "k4": 1.0
        },
        {
            "id": 1,
            "k1": -0.8,
            "k2": 0.2,
            "k3": 0.1,
            "k4": -0.9
        }
    ]
}
```
