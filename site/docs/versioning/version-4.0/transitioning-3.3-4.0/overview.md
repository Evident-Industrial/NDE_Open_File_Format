With the introduction of .nde version 4.0, there are modifications [to the HDF structure](../whats-new-4.0.md#modifications-to-the-hdf-structure)  and [to the JSON Setup dataset](../whats-new-4.0.md#modifications-to-the-json-setup-dataset).  

You may want to upgrade your application so it is compatible with new .nde files. 

## Upgrading your application to read/write NDE files from version 3.3 to version 4.0

We recommend the following procedure to upgrade your application reading and/or writing .nde version 3.3 files to be able to read and/or write .nde version 4.0 files:

- [x] Update the routine in charge of reading/writing the HDF root attributes for the new metadata JSON Properties dataset located under the new **/Properties** path following the [upgrade guide](upgrade-metadata.md).
- [x] Update the routine in charge of reading/writing the HDF datasets currently located under **/Domain/DataGroups**  to the new **/Public/Groups** path following the [upgrade guide](upgrade-hdf-structure.md).
- [x] Update the routine in charge of reading/writing the JSON Setup dataset currently located under **/Domain/Setup**  to the new **/Public/Setup** path following the [upgrade guide](upgrade-json-setup.md). 
- [x] Update any routine in charge of reading/writing data located under **/Applications**  to the new **/Private** path. 




