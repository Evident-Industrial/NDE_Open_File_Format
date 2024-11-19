---
icon: material/code-json
---

In an .NDE file, all metadata are stored within JSON formatted datasets. The two main ones are the Properties and Setup datasets. Each JSON formatted dataset can be validated against a JSON Schema for automatic structure verification.

<div class="grid cards" markdown>

-   :material-file-cog:{ .lg .middle } __[Properties]__

    ---

    Containing metadata relative to the properties of the file as well as generic information useful to index and classify different .NDE files

-   :material-toy-brick:{ .lg .middle } __[Setup]__

    ---

    Containing all the metadata useful to retrieve the acquisition context and to read or process the acquired datasets.

</div>

  [Properties]: properties/index.md
  [Setup]: setup/index.md