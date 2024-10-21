---
icon: material/file-question
---

# Frequently Asked Questions (FAQ)

No answer to your question? Need support? [**Please reach out to us**](mailto:nde_support@evidentscientific.com). 

## General questions

??? question "Is there a review & release process like with other standards?"

    Every 3 months, a new version of the JSON Schemas and updated documentation is published on our GitHub repository and page. Each version is carefully reviewed by our software developers, engineers and scientists. 

??? question "Is there an organization that administers/manages the releases and associated documentation?"
    
    As of now, Evident has been approached by one standardization body, but work still needs to be done to see where/if the standardization will land on the .NDE or other open file format inspired by .NDE (HDF5 based). Evident currently controls the specifications of the .NDE format/standard and its releases, while remaining open to collaboration to extend it to other modalities or add new features. Since the format is based on open-source technologies, anyone is free to reuse or modify it for their own purposes.

    Other organizations like EPRI and COFREND have started to incorporate the HDF5 in their own standards. However, this could undermine the principle of maintaining a common file format and dictionary. Moreover, as Evident invests significant resources and effort to provide comprehensive support and development, any new collaborator or contributor should be prepared to dedicate substantial time and effort to achieve the same level of testing and documentation that we currently maintain.

??? question "How often does it get updated and will software using the .NDE have to be adapted each time?"

    Updates are released every 3 months to introduce new features or correct errors. If a new version does not introduce breaking changes but only adds new functionalities, software does not need to be updated, unless the application should support the new functionality. An application should however be updated if errors are corrected.

??? question "Are there any IP rights on the .NDE format and if so, who is holding those?"

    There are no IP rights on the .NDE file format. The content hosted on our GitHub repository is published under an MIT license.
    
??? question "If it is open source, who guarantees that it will not be changed to a licensed model later (e.g. like Oracle did with the Java Runtime and MySQL database)?"

    Our approach is different. We are not developing software in the case of the .NDE format. We are rather describing how to store data in a standardized way for our industry, using existing open-source technologies. It wouldn’t make sense to charge you for access to this description as you are free to use your own descriptions. This approach aligns with the principle of allowing you to access your data. It was also the case with our previous proprietary format and OpenView SDK (this approach is aligned with the upcoming EU Data Act).


## Evident products

??? question "Regarding .nde files produced by Evident instruments, will I still be able to use OpenViewSDK?"

    Evident won't support OpenViewSDK after the release of the .NDE file format version 4.0. Hence, OpenViewSDK won't be compatible with .NDE 4.0 files. 

??? question "Will Evident software still support previous versions of .NDE files?"

    Evident software will ensure backward compatibility with previous versions of .NDE files saved with their corresponding instruments. Please note that Evident software applications listed below do not **currently** support .NDE files produced by third parties. 

    | Software   | .NDE files compatibility                         |
    | ---------- | ------------------------------------------------ |
    | OmniPC     | 2.X, 3.X & 4.X **saved with the Omniscan (MXU)** |
    | WeldSight  | 2.X, 3.X & 4.X **saved with the Omniscan (MXU)** |
    | PipeWIZARD | 2.X, 3.X & 4.X **saved with the PipeWizard**     |

??? question "Why are Evident software applications only compatible with .NDE files saved with their corresponding instruments?"

    The .NDE open file format was designed to provide access to the data and as such the public section of the .NDE files contain all the necessary information for post-processing your data. New UNIS-based software applications from Evident will natively support the .NDE file format. However, for Evident software applications that existed prior to introducing the .NDE open file format, the support is currently limited.

??? question "Will Evident charge its customers to access their data and read .NDE files in the future?"

    **No**. The .NDE file format is built on an open-source mindset and technical foundations (such as [HDF5](https://www.hdfgroup.org/) and [JSON](https://www.json.org/)). Therefore, access to the data stored in .NDE files will always be free and open (with the exception of the private section of the file under "/Applications" which is not documented nor standardized). Our users own their data and should be free to use it as they want.

## DICONDE

??? question "What is the difference between DICONDE and the .NDE file format?" 

    DICONDE is primarily an archiving format based on the DICOM standard for medical imaging, focusing on storing digital images with a standardized structure and communication protocol. It has been widely used for X-ray modality and is defined by the [ASTM Committee 07](https://www.astm.org/committee-e07), which limits its flexibility for specific inspection setups and complex data types (which should be supported soon). In contrast, the .NDE format, with specifications currently led by Evident, is a native file format for use directly on instruments or any other software. It is built on HDF and JSON for modular data storage, allowing customization and real-time access to data. Thus, .NDE is more suited for practical use and on-device interaction.

??? question "The DICONDE standard defines mature, secure and efficient peer-to-peer network services to connect compliant devices with data consumer or providers. This avoids erroneous file transfer actions since data is communicated directly, guarantees that data is understood between sender and receiver and particularly allows for building digital NDE 4.0 workflows. When using the NDE format, will I have to implement all data transfers (presumably based on file objects) from scratch in each of my NDE project?"

    Yes, the .NDE format standard and documentation does not cover data transfers. You would use the existing HDF5 backends and associated libraries for that purpose. Additionally, as data owners can have very different infrastructures (from small local storage to data lakes), this approach allows them to adopt a solution best suited for their needs with the required level of security.

??? question "By design, DICONDE data objects stay backwards compatible and readable for decades and are officially recognised as a long-term storage format. How is it guaranteed one can read NDE files in 30 year from now?"

    It depends on several factors:

    - HDF5 has been in existence for over 20 years and is widely used across the scientific community and by many industries. We rely on The HDF Group to continue supporting this format for many years.
    - Previous, current, and future versions of the .NDE format/standard are all made available on GitHub. While we cannot guarantee that this repository won’t be moved in 30 years, you are free to make your own copy of its content.
    - In the worst-case scenario, in 30 years, you can use a backup of the current HDF5 libraries combined with a copy of our GitHub repository, and you will have all the tools required to read an .NDE file.

    Finally, we acknowledge that the .NDE file format is not perfect and still lacks certain functionalities or information. However, we believe we have a robust approach for the years to come through our experience over the last year and a half, with feedback from our clients, and with the upcoming 4.0 version that will add more flexibility for new features.