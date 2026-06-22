# **mapToDescrete**
<span class="badge-et">ET</span>
<!-- md:json_type object -->
<!-- md:version 4.3.0 -->

The **mapToDescrete** process converts data acquired with an [allCycle](../../data-mappings.md#allcycle) data mapping into a [discreteGrid](../../data-mappings.md#discretegrid) data mapping. It uses the encoder positions recorded during each acquisition cycle to spatially reassign the acquired signals onto a regular positional grid, making the data directly accessible by spatial coordinates rather than by acquisition cycle index.

!!! info
    This process has currently no configuration parameters.
    
## Example

``` json
"mapToDescrete": {}
```
