# Setup

``` mermaid
flowchart LR
  .nde[**.nde**]:::root --> Public["/Public*"]:::group
  Public["/Public*"] --> Setup["/Setup*"]:::dataset
  .nde@{ shape: text}
  click Public "public-group"
  classDef root fill:#fff
  classDef group fill:#ffc72c,stroke:#000000,color:#000000
  classDef dataset fill:#fff,stroke:#000000,color:#000000
```

The Setup dataset is **mandatory** and located inside the Public group of the .nde file HDF5 structure. It contains all the metadata useful to retrieve the acquisition context and to read or process the acquired datasets (probes, specimens, acquisitions units etc.) and is formatted in a JSON. 

The structure of the formatted JSON included in the **Setup** dataset can be validated against [a dedicated JSON schema](../setup/schema_doc.md). 

The [data model](data-model/index.md) related to the Properties dataset details the different JSON objects and arrays with their expected values, associated description and examples. 


``` mermaid
classDiagram
   Setup --> "1" version
   Setup --> "1" scenario
   Setup --> "1..n" groups
   Setup --> "1..n" acquisitionUnits
   Setup --> "1..n" motionDevices
   Setup --> "1..n" dataMappings
   Setup --> "1..n" probes
   Setup --> "1..n" wedges
   class Setup
   class version
   class scenario
   class groups
   class acquisitionUnits
   class motionDevices
   class dataMappings
   class probes
   class wedges
   style Setup fill:#fff,stroke:#000000,color:#000000
   style version fill:#fff,stroke:#000000,color:#000000
   style scenario fill:#fff,stroke:#000000,color:#000000
   style groups fill:#fff,stroke:#000000,color:#000000
   style acquisitionUnits fill:#fff,stroke:#000000,color:#000000
   style motionDevices fill:#fff,stroke:#000000,color:#000000
   style dataMappings fill:#fff,stroke:#000000,color:#000000
   style probes fill:#fff,stroke:#000000,color:#000000
   style wedges fill:#fff,stroke:#000000,color:#000000
```