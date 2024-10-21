# Properties

``` mermaid
flowchart LR
  .nde[.nde]:::root --> Properties["/Properties*"]:::dataset
  classDef root fill:#005cb9,stroke:#000000,color:#fff
  classDef group fill:#ffc72c,stroke:#000000,color:#000000
  classDef dataset fill:#fff,stroke:#000000,color:#000000
```

The Properties dataset is **mandatory** and located at the root of .NDE file HDF5 structure. It contains metadata relative to the properties of the file as well as generic information useful to index and classify different .NDE files without digging into the details of the inspection and data that can be found in the [Setup](../setup/index.md) dataset. This dataset is formatted in a JSON.   

The structure of the formatted JSON included in the **Properties** dataset can be validated against a dedicated JSON schema than can be downloaded [here](https://github.com/Evident-Industrial/NDE_Open_File_Format/tree/main/schemas). 

The [data model](data-model.md) related to the Properties dataset details the different JSON objects and arrays with their expected values, associated description and examples. 

``` mermaid
classDiagram
   Properties --> "1" file
   Properties --> "1" methods
   class Properties
   class file
   class methods
   style Properties fill:#fff,stroke:#000000,color:#000000
```


