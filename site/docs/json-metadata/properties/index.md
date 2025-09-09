# Properties

``` mermaid
flowchart LR
  .nde[**.nde**]:::root --> Properties["/Properties*"]:::dataset
  .nde@{ shape: text}
  classDef root fill:#fff
  classDef group fill:#ffc72c,stroke:#000000,color:#000000
  classDef dataset fill:#fff,stroke:#000000,color:#000000
```

The Properties dataset is **mandatory** and located at the root of the .nde file HDF5 structure. It contains metadata relative to the properties of the file as well as generic information useful for indexing and classifying different .nde files without digging into the details of the inspection and data that can be found in the [Setup](../setup/index.md) dataset. This dataset is formatted in a JSON.   

The structure of the formatted JSON included in the **Properties** dataset can be validated against [a dedicated JSON schema](../properties/schema_doc.md). 

The [data model](data-model.md) related to the **Properties** dataset details the different JSON objects and arrays with their expected values, associated description and examples. 

``` mermaid
classDiagram
   Properties --> "1" file
   Properties --> "1" methods
   class Properties
   class file
   class methods
   style Properties fill:#fff,stroke:#000000,color:#000000
   style file fill:#fff,stroke:#000000,color:#000000
   style methods fill:#fff,stroke:#000000,color:#000000
```


