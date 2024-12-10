---
icon: material/code-json
---

In an .nde file, all metadata are stored within JSON formatted datasets. The two main ones are the Properties and Setup datasets. Each JSON formatted dataset can be validated against a JSON Schema for automatic structure verification.

<div class="grid cards" markdown>

-   :material-file-cog:{ .lg .middle } __[Properties]__

    ---

    Contain metadata relative to the properties of the file as well as generic information useful for indexing and classifying different .nde files

-   :material-toy-brick:{ .lg .middle } __[Setup]__

    ---

    Contain all the metadata useful for retrieving the acquisition context and reading or processing the acquired datasets.

</div>

  [Properties]: properties/index.md
  [Setup]: setup/index.md