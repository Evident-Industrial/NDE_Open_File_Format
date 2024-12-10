---
icon: material/file-question
---

# Frequently Asked Questions (FAQs)

Can't find the answer to your question? Need support? [**Please reach out to us**](mailto:nde_support@evidentscientific.com). 

## General questions

??? question "Is there a review and release process like with other standards?"

    Every 3 months, a new version of the JSON Schemas and updated documentation is published on our GitHub repository and page. Each version is carefully reviewed by our software developers, engineers, and scientists. 

??? question "Is there an standards organization that administers/manages the releases and associated documentation?"
    
    Evident currently controls the specifications of the .nde format/standard and its releases, while remaining open to collaboration to extend it to other modalities or add new features. Since the format is based on open-source technologies, anyone is free to reuse or modify it for their own purposes. We have been approached by one standardization body, but further work is needed to determine whether the .nde format will be adopted as a standard. 

    Other organizations such as EPRI and COFREND have started to incorporate HDF5 into their own standards. However, combining and focusing our efforts could expedite the NDT industry’s objective to establish and maintain a unified and open file format. Our .nde open-sourced-based file format is well positioned to meet this need as it has already been implemented and is fully supported. As Evident invests significant resources and effort to provide comprehensive support and development, any new collaborator or contributor should be prepared to dedicate substantial time and effort to uphold the same standards of testing and documentation that we currently maintain.

??? question "How often does it get updated and will software using the .nde format have to be adapted each time?"

    Updates are released every 3 months to introduce new features or correct errors. If a new version does not introduce breaking changes but only adds new functionalities, your software does not need to be updated unless the new functionality could benefit your application. An application should however be updated if bugs have been fixed.

??? question "Are there any IP rights on the .nde format and if so, who is holding those?"

    There are no IP rights on the .nde file format. The content hosted on our GitHub repository is published under an MIT license.
    
??? question "Although the .nde file format is currently open source, what ensures that it will not be changed to a licensed model later?"

    With the .nde format, we didn't develop a software, rather, we are describing how to store data in a standardized way for our industry, using existing open-source technologies. It wouldn’t make sense to charge you for access to this description as you are free to use your own descriptions. This approach aligns with the principle of enabling you to access your data (making it ready for EU Data Act compliance). This was also the case with our previous proprietary format and OpenView SDK.


## Evident products

??? question "Regarding .nde files produced by Evident instruments, will I still be able to use OpenViewSDK?"

    Evident will end support of OpenViewSDK after the release of the .nde file format version 4.0. Hence, OpenViewSDK won't be compatible with .nde 4.0 files. 

??? question "Will Evident software still support previous versions of .nde files?"

    Evident software will ensure backward compatibility with previous versions of .nde files saved with their corresponding instruments. Please note that Evident software applications listed below do not **currently** support .nde files produced by third parties. 

    | Software   | NDE file compatibility                         |
    | ---------- | ------------------------------------------------ |
    | OmniPC&trade;     | 2.X, 3.X, and 4.X **saved on OmniScan units (MXU)** |
    | WeldSight&trade;  | 2.X, 3.X, and 4.X **saved on OmniScan units (MXU)** |
    | PipeWIZARD&trade; | 2.X, 3.X, and 4.X **saved on PipeWIZARD units**     |

??? question "Why are Evident software applications only compatible with .nde files saved with their corresponding instruments?"

    The .nde open file format was designed to provide access to the data and as such the public section of the .nde files contain all the necessary information for post-processing your data. New UNIS-based software applications from Evident will natively support the .nde file format. However, for Evident software applications that existed prior to introducing the .nde open file format, the support is currently limited.

??? question "Will Evident charge its customers to access their data and read .nde files in the future?"

    **No**. The NDE file format is built on an open-source mindset and technical foundations (including [HDF5](https://www.hdfgroup.org/) and [JSON](https://www.json.org/)). Therefore, access to the data stored in .nde files will always be free and open (with the exception of the private section of the file under "/Applications," which is neither documented nor standardized). Our users own their data and are free to use it as they want.

## DICONDE

??? question "What is the difference between DICONDE and the NDE file format?" 

    DICONDE is primarily an archiving format based on the DICOM standard for medical imaging, focusing on storing digital images with a standardized structure and communication protocol. It has been widely used for the X-ray modality and is defined by the [ASTM Committee 07](https://www.astm.org/committee-e07), which limits its flexibility for specific inspection setups and complex data types (which should be supported soon). In contrast, the .nde format, with specifications currently managed by Evident, is a native file format for use directly on instruments or any other software. It is built on HDF and JSON for modular data storage, allowing customization and real-time access to data. Thus, .nde is more suited for practical use and on-device interaction.

??? question "The DICONDE standard defines mature, secure, and efficient peer-to-peer network services to connect compliant devices with data consumer or providers. This avoids erroneous file transfer actions since data is communicated directly, helps ensure that data is understood between sender and receiver, and facilitates building digital NDE 4.0 workflows. When using the .nde format, will I have to implement all data transfers (presumably based on file objects) from scratch in each of my NDE projects?"

    Yes, the NDE format standard and documentation do not address data transfers. Instead, existing HDF5 backends and associated libraries must be used for that purpose. Additionally, since data owners may have vastly different infrastructures, ranging from small local storage to large-scale data lakes, this approach enables them to adopt solutions tailored to their specific needs and desired level of security.

??? question "By design, DICONDE data objects remain backward compatible and readable for decades, and it is officially recognized as a long-term storage format. How can we be certain that NDE files will still be readable 30 years from now?"

    It depends on several factors:

    - HDF5 has been in existence for over 20 years and is widely used across the scientific community and by many industries. We rely on The HDF Group to continue supporting this format for many years.
    - Previous, current, and future versions of the .nde format/standard are all available on GitHub. While we cannot guarantee that this repository won’t be moved in 30 years, you are free to make your own copy of its content.
    - In the worst-case scenario, in 30 years, you can use a backup of the current HDF5 libraries combined with a copy of our GitHub repository, and you will have all the tools required to read an .nde file.

    Although the NDE file format is still evolving, as we continually develop functionalities and information that its lacking, we feel that we have a robust approach. Based on our experience during its development and client feedback after its release, and on the 4.0 version—which introduces greater flexibility for new features—we believe that we've built a strong foundation for years to come. 