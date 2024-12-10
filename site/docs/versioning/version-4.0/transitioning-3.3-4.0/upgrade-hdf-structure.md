## Terminology

Note the correspondance between terms used in version 3.3 and in new terms used in version 4.0. 

| Version 3.3 | Version 4.0 |
| ----------- | ----------- |
| DataGroupId | GroupId     |
| DatasetId   | DatasetId   |
| DatasetType | DataClass   | 

## Convert **DatasetTypes** to **DataClasses**

The following correspondance needs to be made between previous DatasetTypes and new DataClasses:

| :nde-3-3: DatasetType  | :nde-4-0: DataClass |
| ---------------------- | ------------------- |
| Amplitude              | AScanAmplitude      |
| Status                 | AScanStatus         |
| FiringSource           | FiringSource        |
| Value (for TFM Images) | TfmValue            |


## Update datasets paths

Find the correspondance between datasets paths between versions 3.3 and 4.0. Note that TFM datasets were previously stored under a dedicated subpath, which is now removed for standardization. 

| Type | :nde-3-3: Previous datasets path                                                | :nde-4-0: New datasets path                               |
| ---- | ------------------------------------------------------------------------------- | --------------------------------------------------------- |
| PA   | /DataGroups + /[DataGroupId] + /Datasets + /[DatasetId] + /[DatasetType]        | /Groups + /[GroupId] + /Datasets + /[DatasetId-DataClass] |
| TFM  | /DataGroups + /[DataGroupId] + /Datasets + /[DatasetId] + /TFM + /[DatasetType] | /Groups + /[GroupId] + /Datasets + /[DatasetId-DataClass] |

The following **examples** are provided for each supported DatasetType/DataClass for better understanding: 

| :nde-3-3: Previous dataset path           | :nde-4-0: New dataset path          |
| ----------------------------------------- | ----------------------------------- |
| /DataGroups/0/Datasets/0/Amplitude        | /Groups/0/Datasets/0-AScanAmplitude |
| /DataGroups/0/Datasets/0/Status           | /Groups/0/Datasets/1-AScanStatus    |
| /DataGroups/0/Datasets/1/FiringSource     | /Groups/0/Datasets/2-FiringSource   |
| /DataGroups/1/Datasets/0/TFM/Value        | /Groups/1/Datasets/0-TfmValue       |
| /DataGroups/1/Datasets/0/TFM/Status       | /Groups/1/Datasets/1-TfmStatus      |
| /DataGroups/1/Datasets/0/TFM/FiringSource | /Groups/1/Datasets/2-FiringSource   |
