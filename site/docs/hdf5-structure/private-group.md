# **Private** group

``` mermaid
flowchart LR
  .nde[.nde]:::root --> Private["/Private"]:::group
  classDef root fill:#005cb9,stroke:#000000,color:#fff
  classDef group fill:#ffc72c,stroke:#000000,color:#000000
  classDef dataset fill:#fff,stroke:#000000,color:#000000
```

The **Private** HDF5 group and all of its subgroups are **optional** and considered **proprietary and software-specific data**. This section can be structured as per the acquisition or post-processing software’s specifications.

Each application that creates, read or modifies the file can add specific information here. This container can be used as deemed necessary by the application software that creates the .nde file, including but not limited to storing setup information, customized data, or metadata, etc. 

**Everything under this group is not covered by the present documentation** and should not be used for information that should be shared between different applications. 