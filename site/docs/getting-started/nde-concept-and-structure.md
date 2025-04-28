# NDE Concept and Structure

## Purpose of the NDE Open File Format

The NDE Open File Format is designed to store nondestructive testing (NDT) data in a platform-independent and modality-agnostic manner. By utilizing the [Hierarchical Data Format version 5 (HDF5)](https://www.hdfgroup.org/), it ensures efficient storage, management, and access to large and complex datasets. This open format facilitates data compatibility, accessibility, and long-term archiving, addressing the industry's need for a universal standard to overcome challenges posed by proprietary file formats.

## Rationale Behind the File Structure

The NDE file structure is intentionally designed for simplicity and standardization, comprising two main components:

- **[Private Container](../hdf5-structure/private-group.md)**: This section allows proprietary acquisition and analysis software to store specific information, such as setup parameters or customized data. It is structured according to the software's specifications and is not intended for use by general NDE readers.

- **[Public Container](../hdf5-structure/public-group.md)**: This standardized section includes datasets and contextual information described in an embedded JSON file. It ensures consistency and interoperability across different platforms and applications, facilitating seamless data sharing and analysis.

By organizing data into these containers, the NDE format maintains a balance between accommodating proprietary needs and promoting standardization, thereby enhancing data compatibility and future-proofing.

## Conceptual Framework of the NDE Format

The NDE Open File Format operates on a conceptual framework that emphasizes openness, flexibility, and industry advancement:

- **Openness**: As an open file format, .nde files can be accessed without proprietary software, reducing barriers for custom or third-party software development and fostering innovation within the NDT community.

- **Flexibility**: The use of HDF5 and JSON allows the format to support various NDT modalities, such as ultrasonic testing (UT) and eddy current testing (ET), making it adaptable to evolving technologies and complex solutions.

- **Industry Advancement**: By adopting a universal open file format, the NDT industry can enhance data sharing, integrate advanced technologies like artificial intelligence, and streamline workflows, thereby accelerating progress in the era of NDE 4.0.
