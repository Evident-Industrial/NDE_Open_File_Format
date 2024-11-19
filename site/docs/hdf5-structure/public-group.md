# **Public** group

``` mermaid
flowchart LR
  .nde[**.nde**]:::root --> Public["/Public*"]:::group
  Public["/Public*"] --> Setup["/Setup*"]:::dataset
  Public["/Public*"] --> Groups["/Groups"]:::group
  .nde@{ shape: text}
  classDef root fill:#fff
  classDef group fill:#ffc72c,stroke:#000000,color:#000000
  classDef dataset fill:#fff,stroke:#000000,color:#000000
```

The **Public** HDF5 group is **mandatory** and the structure of its subgroups is considered as standardized information (which structure is described in the present documentation).

## **Setup** dataset 

The [**Setup**](../json-metadata/setup/index.md) HDF5 dataset is **mandatory** and contains all the **metadata** useful to retrieve the acquisition context and to read or process the acquired datasets (probes, specimens, acquisitions units etc.). This dataset is a string structured in a JSON format. 

## **Groups** group and subgroups

!!! warning "Avoid the confusion"

    The **Groups** designation could be quite confusing, hence please pay special attention to the difference betwen an HDF5 group (the equivalent of a folder in a filesystem) and the .NDE **Groups** structure layer, which is the name of a specific HDF5 group defined in the .NDE file format data model that can be access under the /Public/Groups path.

The **Groups** HDF5 group may contain inspection data but also other contextual information divided by inspection groups. An inspection group corresponds to the combination of one or several probes and an acquisition strategy (such as a Linear Array and TFM for UT). 

Datasets, that contain inspection data, are stored hierarchically using the following logic:

``` mermaid
flowchart LR
  Groups["/Groups"]:::group --> GroupId["/[GroupId]"]
  GroupId["/[GroupId]"]:::group --> Datasets["/Datasets"]
  Datasets["/Datasets"]:::group --> DatasetId-DataClass["/[DatasetId-DataClass]"]:::dataset
  classDef root fill:#005cb9,stroke:#000000,color:#fff
  classDef group fill:#ffc72c,stroke:#000000,color:#000000
  classDef dataset fill:#fff,stroke:#000000,color:#000000
```

- **GroupId** must be a unique integer identifying an inspection group.

- **DatasetId** must be a unique integer within a group identifying a specific dataset. 

- **DataClass** must be a string taking one of the supported values: `AScanAmplitude`, `AScanStatus`, `TFMValue` and `TFMStatus`. It allows to quickly identify the type of data associated with a Dataset. The additional `FiringSource` data class can be found in some Evident .NDE files but this type of dataset is only used internally for the moment.

**Note that the Groups HDF5 group structure matches the description of [groups in the JSON formatted Setup dataset](../json-metadata/setup/data-model/groups/index.md). Please refer to this section for more information on datasets structure.**

## Example 

It results in the following structure in a typical case where the acquisition was performed with an OmniScan X3 or X4. See also the [example files page](../examples/example-files/index.md).

``` mermaid
flowchart LR
  Groups["/Groups"]:::group --> 0["/0"]
  0["/0"]:::group --> Datasets["/Datasets"]
  Datasets["/Datasets"]:::group --> 0-AScanAmplitude["/0-AScanAmplitude"]:::dataset
  Datasets["/Datasets"]:::group --> 1-AScanStatus["/1-AScanStatus"]:::dataset
  classDef root fill:#005cb9,stroke:#000000,color:#fff
  classDef group fill:#ffc72c,stroke:#000000,color:#000000
  classDef dataset fill:#fff,stroke:#000000,color:#000000
```

