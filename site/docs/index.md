---
hide:
  - toc
---

# Home

The .nde extensible file format is designed for storage of nondestructive testing (NDT) data. It is platform-independent and modality-agnostic. 
It provides a relatively simple file structure for mainstream NDT applications while enabling support for future complex solutions and technologies. The file is associated with a [standardized referential system](general-concepts/conventions.md#axes-and-coordinate-system) related to the inspection component as well as standardized definitions for [scenarios](general-concepts/scenarios.md) and [objects](general-concepts/objects.md). Data is stored using the HDF5 file format combined with a JSON text format describing the associated metadata. 

The .nde file format is one of the primary interfaces of the Unified NDT Inspection Software (UNIS) platform currently being developed by Evident. The .nde file format will be supported by all future NDT software applications developed by Evident.

![UnisInterfaces.png](assets/images/home/UNIS Platform.png){width="30%"}

UNIS is an open platform that can be used by all stakeholders in the NDE world to enable [NDE 4.0 and accelerate software development](https://www.ndt.net/article/ecndt2023/presentation/ECNDT2023_PRESENTATION_364.pdf).

The .nde file format is a work in progress. Evident will be releasing a new version of the file format every 3 months for the foreseeable future. Starting with file version 3.0, which was released in January 2023, the .nde file format will avoid any breaking changes until further notice.

To communicate with the development team for support or to provide feedback, please contact [nde_support@evidentscientific.com](mailto:nde_support@evidentscientific.com).

## About the Project

### License

The NDE format is distributed under an [MIT license](https://github.com/Evident-Industrial/NDE_Open_File_Format/blob/main/LICENSE).

### Support

To communicate with the development team for support or to provide feedback, please contact [nde_support@evidentscientific.com](mailto:nde_support@evidentscientific.com).
