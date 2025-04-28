# OmniScan&trade; MXU Software

Specific information related to how the OmniScan X3 and X4 products save .nde files will be documented on this page. 

## CHANGELOG

Any change or correction regarding the way the OmniScan X3 and X4 flaw detectors save data in the .nde format will be logged in this section. 

### [MXU 6.1.0] - <small>April 23, 2025</small> { id="6.1.0" }

#### Added

- New dataset format export for phased array angle beam raster scanning. See [NDE 4.1 changelog](../../versioning/changelog.md#4.1.0) section. 
- Change of scanning axis for specific configurations, such as ToFD parallel scanning and Raster scanning at 0°. See [NDE 4.1 changelog](../../versioning/changelog.md#4.1.0) section. 

#### Fixed

??? "Invalid HDF5 Groups Ids when multiple TFM groups configured"
    
    In some cases, [Groups Ids](../../hdf5-structure/public-group.md#groups-group-and-subgroups) were assigned incorrectly in the HDF5 structure **when multiple TFM groups were configured** (see example below), resulting in a mismatch with the [JSON formatted Setup dataset](../../json-metadata/setup/index.md) information.

    ![invalid_tfm_groups.png](../../assets/images/supporting-software/evident/invalid_tfm_groups.png){ width="500" }

    **Impacted files**

    For files created with **MXU version 6.0.2**, and when multiple TFM groups were configured, you may need to update your file reading routine due to a mismatch between:

    - The group `id`s and dataset `path`s in the [JSON-formatted Setup dataset](../../json-metadata/setup/index.md), and  
    - The actual group `id`s present in the HDF5 structure.

    **Identifying the Issue**

    This mismatch typically appears when [totalFocusingMethod](../../json-metadata/setup/data-model/groups/processes/totalFocusingMethod.md) groups reference group `id`s and dataset `path`s that **do not exist** in the HDF5 file structure. For example, the JSON Setup might refer to the `/Public/Groups/2/Datasets/...` path, while the HDF5 structure only contains `/Public/Groups/1/`, `/Public/Groups/3/`, etc. Note that the groups and datasets appear in the same order in both the HDF5 structure and the JSON Setup, but the group id may not match — which is the root cause of the issue.

    **Workaround**

    As a workaround, you can **remap sequentially the dataset paths** for each [totalFocussingMethod](../../json-metadata/setup/data-model/groups/processes/totalFocusingMethod.md) group, based on their order, to match the correct group `id`s in the HDF5 file structure. This approach ensures that the datasets referenced in the Setup correctly align with those in the HDF5 structure, regardless of mismatched group numbers.

    Example Remapping Table:

    | Groups listed in HDF5 structure | TFM datasets original paths     |  TFM datasets corrected paths   | Comment                                          |
    | :-----------------------------: | :------------------------------ | :-----------------------------: | ------------------------------------------------ |
    |                1                | `/Public/Groups/1/Datasets/...` | `/Public/Groups/1/Datasets/...` | HDF5 Group exists. No path update needed.        |
    |                3                | `/Public/Groups/2/Datasets/...` | `/Public/Groups/3/Datasets/...` | HDF5 Group does not exist. Path update required. |
    |                5                | `/Public/Groups/3/Datasets/...` | `/Public/Groups/5/Datasets/...` | HDF5 Group exists. Path update required.         |
    |               ...               | ...                             |               ...               | ...                                              |

