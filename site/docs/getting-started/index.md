# Getting Started

Welcome to the official documentation of the NDE open file format. This page will guide you to quickly find the right resources for your needs.

<figure markdown="span">
  ![NDE Concept](../assets/images/home/nde_concept.png){ width="500" }
</figure>

The **NDE open file format** refers to any data file stored using the [HDF5 container library](https://www.hdfgroup.org/) and [JSON](https://www.json.org/) text format following the [HDF5 Structure](../hdf5-structure/index.md) and [JSON Metadata](../json-metadata/index.md) requirements detailed in this documentation. Such a file should be saved using the **.nde** extension. 

The .nde open file format is designed for storing nondestructive testing (NDT) data. It is platform-independent and modality-agnostic, offering a relatively simple file structure for mainstream NDT applications while supporting future complex solutions and technologies. It currently supports the ultrasonic testing (UT) modality and will soon support the eddy current (ET) modality.

## Learn about the NDE 0pen file format initiative 

You've heard about the .nde open file format, but you're unsure where it originates or whether it's right for you. Here are some interesting resources to help you decide:

<div class="grid cards" markdown>

- :material-layers: [__NDE and UNIS Open Platform__](nde-and-unis.md) – From inception to a complete NDT open platform
- :material-account-group: [__Collaboration__](collaboration.md) – How to contribute to the NDE file format
- :material-file-question: [__FAQs__](../faq/index.md) –  Find answers to frequently asked questions about the .nde format
- :material-license: [__Licensing__](https://raw.githubusercontent.com/Evident-Industrial/NDE_Open_File_Format/refs/heads/main/LICENSE) – The NDE file format content is published under an MIT license. 

</div>


## Read and write .nde files yourself

If you're thinking about developing your own application to read and/or write .nde files or simply want to learn more about the underlying technology, check out the following resources:

<div class="grid cards" markdown>

- :material-file-tree: [__HDF5 Structure__](../hdf5-structure/index.md) – Learn how .nde files should be structured and where to find the datasets containing raw data.
- :material-code-json: [__JSON Metadata__](../json-metadata/index.md) – Learn the data model and [conventions](../json-metadata/setup/conventions.md) used to describe inspection related information.
- :material-cards: [__Example Files__](../examples/example-files/index.md) –  Quickly explore example files through the myHDF5 viewer or use them to prototype your own code.
- :material-code-block-parentheses: [__Python Code Samples__](../examples/code-samples/index.md) –  Learn how you can use the information provided in this documentation for your own application. 

</div>


## Good to know

<div class="grid cards" markdown>

- :material-apps: [__Supporting Software__](../supporting-software/index.md) – Discover the list of software compatible with NDE files. 
- :material-history: [__Changelog__](../versioning/index.md) – Being up to date is important, make sure you bookmark our changelog and versioning pages. 
</div>

