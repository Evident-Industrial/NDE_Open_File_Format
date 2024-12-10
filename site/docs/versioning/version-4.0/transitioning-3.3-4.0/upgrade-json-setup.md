Numerous changes have been made to the JSON Setup dataset, especially within the groups object. This page presents all the modifications impacting each one of the higher level objects in the JSON file hierarchy, which are represented below. Note that only the name of the dataEncodings object was updated to dataMappings at this level:


=== "4.0"

    ``` json
    {
    "$schema": "...",
    "version": "...",
    "scenario": "...",
    "groups": [],
    "acquisitionUnits": [],
    "motionDevices": [],
    "dataMappings": [],
    "specimens": [],
    "probes": [],
    "wedges": [],
    }
    ```

=== "3.3"

    ``` json
    {
    "$schema": "...",
    "version": "...",
    "scenario": "...",
    "groups": [],
    "acquisitionUnits": [],
    "motionDevices": [],
    "dataEncodings": [],
    "specimens": [],
    "probes": [],
    "wedges": [],
    }
    ```

## $schema

This key needs to be updated to the latest version of the JSON schema, which is version 4.0.0

=== "4.0"

    ``` json
    {
    "$schema": "./NDE-FileFormat-Schema-4.0.0.json",
    }
    ```

=== "3.3"

    ``` json
    {
    "$schema": "./NDE-FileFormat-Schema-3.3.0.json",
    }
    ```

## version

This key needs to be updated to the latest version of the .nde standard, which is 4.0.0.

=== "4.0"

    ``` json
    {
    "version": "4.0.0",
    }
    ```

=== "3.3"

    ``` json
    {
    "version": "3.3.0",
    }
    ```

## scenario

No modifications were made to this object so far. The official release of .nde version 4.0 will confirm whether this object can be duplicated safely from 3.3. to 4.0. 

## groups

The overal groups structure needs to be upgraded with the following modifications that will be detailed below:

| Property          |           Version 4.0           |    Version 3.3     | Comment                                                                                         |
| ----------------- | :-----------------------------: | :----------------: | ----------------------------------------------------------------------------------------------- |
| id [number]       |       :white_check_mark:        | :white_check_mark: | Unchanged                                                                                       |
| name [string]     |       :white_check_mark:        | :white_check_mark: | Unchanged                                                                                       |
| usage [string]    |       :white_check_mark:        | :white_check_mark: | Unchanged                                                                                       |
| dataset [object]  | :x: :twisted_rightwards_arrows: | :white_check_mark: | Now defined in the [datasets](#converting-dataset-object-properties-to-datasets-array) array    |
| ut [object]       | :x: :twisted_rightwards_arrows: | :white_check_mark: | Replaced by the [ultrasonicConventional](#ultrasonicconventional-process)  processes array item |
| paut [object]     | :x: :twisted_rightwards_arrows: | :white_check_mark: | Replaced by the [ultrasonicPhasedArray](#ultrasonicphasedarray-process)  processes array item   |
| fmc [object]      | :x: :twisted_rightwards_arrows: | :white_check_mark: | Replaced by the [ultrasonicMatrixCapture and totaFocusingMethod](#ultrasonicmatrixcapture-and-totalfocusingmethod-processes)  processes array items   |
| datasets [array]  |    :white_check_mark: :new:     |         -          | New [datasets array](#converting-dataset-object-properties-to-datasets-array) array             |
| processes [array] |    :white_check_mark: :new:     |         -          | New [processes array](#converting-ut-paut-and-fmc-objects-to-processes-array-items) array           |

:white_check_mark: = property conserved | :white_check_mark: :new: = new property | :x: :twisted_rightwards_arrows: = property removed and replaced

### Converting **dataset** object properties to **datasets** array

Converting previous **dataset** objects to new **datasets** array items require some important modifications. Please refer to the following tables for correlations between previous properties and new ones. 

Previous **dataset** object in version 3.3:

| Property                       | JSON Depth | Comment                                                                                                                               |
| ------------------------------ | :--------: | ------------------------------------------------------------------------------------------------------------------------------------- |
| ascan [object]                 |     0      | :fontawesome-solid-divide: Divided into a [AScanAmplitude](#ascanamplitude-datasets) and [AScanStatus](#ascanstatus-datasets) dataset |
| ascan{velocity} [number]       |     1      | :arrow_right: Moved to the [ultrasonicPhasedArray](#ultrasonicphasedarray-process) process                                            |
| ascan{skewAngle} [number]      |     1      | :x: Removed as already found in the paut object                                                                                       |
| ascan{refractedAngle} [number] |     1      | :x: Removed as already found in the paut object                                                                                       |
| ascan{amplitude} [object]      |     1      | :x: :twisted_rightwards_arrows: Replaced by a [AScanAmplitude](#ascanamplitude-datasets) dataset                                      |
| ascan{status} [object]         |     1      | :x: :twisted_rightwards_arrows: Replaced by a [AScanStatus](#ascanstatus-datasets) dataset                                            |
| firingSource [object]          |     0      | :x: :twisted_rightwards_arrows: Replaced by a [FiringSource](#firingsource-datasets) dataset                                          |
| storageMode [string]           |     0      | :arrow_right: Moved inside each datasets item definition                                                                              |
| dataSampling [object]          |     2      | :material-merge: Merged with the dataValue object                                                                                     |
| dataValue [object]             |     2      | :arrow_right: Moved with its child components inside each datasets item definition                                                              |
| path [string]                  |     2      | :arrow_right: Moved with its child components inside each datasets item definition                                                              |
| dimensions  [object]           |     2      | :arrow_right: Moved with its child components inside each datasets item definition                                                              |
| overwriteCriteria [string]     |     0      | :x: Removed as not necessary                                                                                                          |

   
New **datasets** array in version 4.0: 

| Property                                  | JSON Depth | Comment                                                                                      |
| ----------------------------------------- | :--------: | -------------------------------------------------------------------------------------------- |
| id [number]                               |     0      | :new: Needs to be unique within a group                                                      |
| dataTransformations [array]               |     0      | :new: References the process chains in charge of processing the dataset                      |
| dataTransformations[{processId}] [number] |     1      | :new: The processId of the last process in the chain                                         |
| dataTransformations[{groupId}] [number]   |     1      | :new: The groupId of the last process in the chain (not required if in the same group)       |
| dataClass [string]                        |     0      | :new:                                                                                        |
| storageMode [string]                      |     0      | Same as storageMode in version 3.3                                                           |
| dataValue [object]                        |     0      | Same as dataValue in version 3.3                                                             |
| path [string]                             |     0      | Same as path in version 3.3                                                                  |
| dimensions [object]                       |     0      | Same as dimensions object in version 3.3                                                     |


#### AScanAmplitude datasets

The following example shows how a version 3.3 ascan{amplitude} dataset can be converted to a AScanAmplitude datasets item in version 4.0:

This notation is used to define and object{and a child} inside the JSON hierarchy. 

=== "4.0"

    ``` json
    "datasets": [
        {
        "id": 0,
        "dataTransformations":[
          {
            "processId": 0
          }
        ],
        "dataClass": "AScanAmplitude",
        "storageMode": "Paintbrush",
        "dataValue": {
            "min": 0, // (1)!
            "max": 32767, // (2)!
            "unitMin": 0.0, // (3)!
            "unitMax": 200.0, // (4)!
            "unit": "Percent"
        },
        "path": "/Public/Groups/0/Datasets/0-AScanAmplitude",
        "dimensions": [
            {
            "axis": "UCoordinate",
            "offset": 0.0,
            "quantity": 351,
            "resolution": 0.001
            },
            {
            "axis": "VCoordinate",
            "offset": -0.07455,
            "quantity": 114,
            "resolution": 0.001
            },
            {
            "axis": "Ultrasound",
            "offset": 0.0,
            "quantity": 568,
            "resolution": 2E-08
            }
        ],
        }
    ]
    ```

    1.  Corresponds to the **min** value previously stored in the dataSampling objects
    2.  Corresponds to the **max** value previously stored in the dataSampling objects
    3.  Corresponds to the previous **min** value of the dataValue object
    4.  Corresponds to the previous **max** value of the dataValue object

=== "3.3"

    ``` json
    "dataset": {
        "ascan": {
          "velocity": 2700.0,
          "skewAngle": 0.0,
          "refractedAngle": 0.0,
          "amplitude": {
            "dataSampling": {
              "min": 0,
              "max": 32767
            },
            "dataValue": {
              "min": 0,
              "max": 200,
              "unit": "Percent"
            },
            "path": "/Domain/DataGroups/0/Datasets/0/Amplitude",
            "dimensions": [
                {
                "axis": "UCoordinate",
                "offset": 0.0,
                "quantity": 351,
                "resolution": 0.001
                },
                {
                "axis": "VCoordinate",
                "offset": -0.07455,
                "quantity": 114,
                "resolution": 0.001
                },
                {
                "axis": "Ultrasound",
                "offset": 0.0,
                "quantity": 568,
                "resolution": 2E-08
                }
            ]
          }
        },
        "overwriteCriteria": "Last",
        "storageMode": "Paintbrush"
    }
    ```

#### AScanStatus datasets

!!! note
    This type of dataset is specific to the files saved with an Evident instrument and may be different with other vendors.

The following example shows how a version 3.3 ascan{status} dataset can be converted to a AScanStatus datasets item in version 4.0:

=== "4.0"

    ``` json
    "datasets": [
        {
        "id": 1,
        "dataTransformations":[
          {
            "processId": 0
          }
        ],
        "dataClass": "AScanStatus",
        "storageMode": "Paintbrush",
        "dataValue": {
            "hasData": 1,
            "saturated": 2,
            "noSynchro": 4,
            "unit": "Bitfield"
        },
        "path": "/Public/Groups/0/Datasets/1-AScanStatus",
        "dimensions": [
            {
            "axis": "UCoordinate",
            "offset": 0.2,
            "quantity": 301,
            "resolution": 0.001
            },
            {
            "axis": "VCoordinate",
            "offset": 0.0,
            "quantity": 155,
            "resolution": 0.001
            }
        ],
        }
    ]
    ```

=== "3.3"

    ``` json
    "dataset": {
        "ascan": {
            "velocity": 2700.0,
            "skewAngle": 0.0,
            "refractedAngle": 0.0,
            "status": {
            "dataValue": {
                "hasData": 1,
                "saturated": 2,
                "noSynchro": 4,
                "unit": "Bitfield"
            },
            "path": "/Domain/DataGroups/0/Datasets/0/Status",
            "dimensions": [
                {
                "axis": "UCoordinate",
                "offset": 0.2,
                "quantity": 301,
                "resolution": 0.001
                },
                {
                "axis": "VCoordinate",
                "offset": 0.0,
                "quantity": 155,
                "resolution": 0.001
                }
            ]
            }
        },
        "overwriteCriteria": "Last",
        "storageMode": "Paintbrush"
    }
    ```

#### FiringSource datasets

!!! note
    This type of dataset is specific to the files saved with an Evident instrument and may be different with other vendors. 

This example shows how a version 3.3 firingSource dataset can be converted to a FiringSource datasets item in version 4.0:

=== "4.0"

    ``` json
    "datasets": [
        {
        "id": 2,
        "dataTransformations":[
          {
            "processId": 0
          }
        ],
        "dataClass": "FiringSource",
        "storageMode": "Paintbrush",
        "dataValue": {
            "min": 0,
            "max": 64,
            "unit": "BeamId"
        },
        "path": "/Public/Groups/0/Datasets/2-FiringSource",
        "dimensions": [
            {
            "axis": "UCoordinate",
            "offset": 0.2,
            "quantity": 301,
            "resolution": 0.001
            },
            {
            "axis": "VCoordinate",
            "offset": 0.0,
            "quantity": 155,
            "resolution": 0.001
            }
        ],
        }
    ]
    ```
    
=== "3.3"

    ``` json
    "dataset": {
        "firingSource": {
            "path": "/Domain/DataGroups/0/Datasets/1/FiringSource",
            "dataValue": {
                "min": 0,
                "max": 64,
                "unit": "BeamId"
            },
            "dimensions": [
                {
                "axis": "UCoordinate",
                "offset": 0.2,
                "quantity": 301,
                "resolution": 0.001
                },
                {
                "axis": "VCoordinate",
                "offset": 0.0,
                "quantity": 155,
                "resolution": 0.001
                }
            ]
        },
        "overwriteCriteria": "Last",
        "storageMode": "Paintbrush"
    }
    ```


### Converting **ut**, **paut**, and **fmc** objects to processes array items

Each new processes array item has the same basic structure: 

| Property                | Comment                                                                                                      |
| :---------------------- | :----------------------------------------------------------------------------------------------------------- |
| id* [integer]           | The unique process id in the JSON structure                                                                  |
| implementation [string] | The process implementation type, which can be `Software` or `Hardware`                                             |
| inputs [object]         | An inputs array describing the different inputs of the process                                               |
| outputs [object]        | An outputs array describing the different outputs of the process                                             |
| dataMappingId [number]  | Previously found inside a paut, ut, or tfmDescription object, refers to the corresponding dataMapping object Id |
| One of the following subobjects: <ul><li>ultrasonicConventional</li><li>ultrasonicPhasedArray</li><li>ultrasonicMatrixCapture</li><li>totalFocusingMethod</li><li>tfmBoxGates</li><li>thickness</li><li>gain</li></ul> |              |                                                              


Converting previous **ut**, **paut**, **fmc**, and **tfmDescriptions** objects to new **processes** array items require some slight modifications. Please refer to the following tables for correspondance between previous properties and new ones. 

#### ultrasonicPhasedArray process

Most of the previous **paut** object properties remain unchanged in the new ultrasonicPhasedArray object, which is now found inside the processes array. 


| Property                        | :nde-4-0: ultrasonicPhasedArray{} |  :nde-3-3: paut{}  | Comment                                                                 |
| ------------------------------- | :-------------------------------: | :----------------: | ----------------------------------------------------------------------- |
| dataEncodingId [number]         |  :x: :twisted_rightwards_arrows:  | :white_check_mark: | Moved to datasets array item as dataMappingId                           |
| pulseEcho [object]              |        :white_check_mark:         | :white_check_mark: |                                                                         |
| waveMode [string]               |        :white_check_mark:         | :white_check_mark: |                                                                         |
| velocity [number]               |        :white_check_mark:         | :white_check_mark: |                                                                         |
| focusing [object]               |        :white_check_mark:         | :white_check_mark: |                                                                         |
| beams [array]                   |        :white_check_mark:         | :white_check_mark: |                                                                         |
| pulse [object]                  |        :white_check_mark:         | :white_check_mark: |                                                                         |
| gates [array]                   |        :white_check_mark:         | :white_check_mark: |                                                                         |
| rectification [string]          |        :white_check_mark:         | :white_check_mark: |                                                                         |
| digitizingFrequency [number]    |        :white_check_mark:         | :white_check_mark: |                                                                         |
| ascanSynchroMode [string]       |        :white_check_mark:         | :white_check_mark: |                                                                         |
| ascanCompressionFactor [number] |        :white_check_mark:         | :white_check_mark: |                                                                         |
| gain [number]                   |        :white_check_mark:         | :white_check_mark: |                                                                         |
| wedgeDelay [number]             |        :white_check_mark:         | :white_check_mark: |                                                                         |
| ultrasoundMode [string]         |        :white_check_mark:         | :white_check_mark: |                                                                         |
| highAmplitude [number]          |                :x:                | :white_check_mark: | Removed as it was a redundant with the dataset dataValue object content |
| referenceAmplitude [number]     |        :white_check_mark:         | :white_check_mark: |                                                                         |
| referenceGain [number]          |        :white_check_mark:         | :white_check_mark: |                                                                         |
| digitalBandPassFilter [object]  |        :white_check_mark:         | :white_check_mark: |                                                                         |
| smoothingFilter [number]        |        :white_check_mark:         | :white_check_mark: |                                                                         |
| averagingFactor [number]        |        :white_check_mark:         | :white_check_mark: |                                                                         |
| softwareProcess [object]        |  :x: :twisted_rightwards_arrows:  | :white_check_mark: | Moved to a dedicated **ultrasonicThickness** processes array item       |

Additionally, please note that some irrelevant parameters associated with the instrument configuration were removed: 

- Removed from the **gates** array: **produceCscanData**, **peakDetection** and **timeSelection**
- Removed from the **tcg** object (inside the **beams** array): **enabled**
  
The following shows how a version 3.3 **paut** object can be converted to a **ultrasonicPhasedArray** processes array item in version 4.0:

=== "4.0"

    ``` json
    "processes": [
      {
        "inputs": [],
        "outputs": [
          {
            "id": 0,
            "datasetId": 0,
            "dataClass": "AScanAmplitude"
          },
          {
            "id": 1,
            "datasetId": 1,
            "dataClass": "AScanStatus"
          }
        ],
        "id": 0, // (1)!
        "dataMappingId": 0,
        "implementation": "Hardware",
        "ultrasonicPhasedArray": { // (2)!
          "pulseEcho": {},
          "waveMode": "TransversalVertical",
          "velocity": 3100.0,
          "focusing": {},
          "beams": [],
          "pulse": {},
          "gates": [],
          "rectification": "Full",
          "digitizingFrequency": 100000000.0,
          "ascanSynchroMode": "Pulse",
          "ascanCompressionFactor": 6,
          "gain": 33.1,
          "wedgeDelay": 0.0,
          "ultrasoundMode": "TrueDepth",
          "referenceAmplitude": 80.0,
          "referenceGain": 33.1,
          "digitalBandPassFilter": {},
          "averagingFactor": 1,
          "calibrationStates": []
        }
      },
      {
        "inputs": [
          {
            "processId": 0
          }
        ],
        "outputs": [],
        "id": 1,
        "dataMappingId": 0,
        "implementation": "Software",
        "thickness": { // (3)!
          "min": 0.0065000000000000006,
          "max": 0.0273,
          "gates": [
            {
              "id": 1,
              "gateDetection": "MaximumPeak"
            }
          ]
        }
      }
    ]
    ```

    1. As per convention, a process with an Id = 0 defines the group. This group is hence a "Phased Array" group.  
    2. This object is almost identical to the previous *paut* object.
    3. This process replaces the previous **softwareProcess** inside the **paut** object.

=== "3.3"

    ``` json
    "paut": {
        "dataEncodingId": 0,
        "pulseEcho": {},
        "waveMode": "TransversalVertical",
        "velocity": 3100.0,
        "focusing": {},
        "beams": [],
        "pulse": {},
        "gates": [],
        "rectification": "Full",
        "digitizingFrequency": 100000000.0,
        "ascanSynchroMode": "Pulse",
        "ascanCompressionFactor": 6,
        "gain": 33.1,
        "wedgeDelay": 0.0,
        "ultrasoundMode": "TrueDepth",
        "highAmplitude": 200.0,
        "referenceAmplitude": 80.0,
        "referenceGain": 33.1,
        "digitalBandPassFilter": {},
        "averagingFactor": 1,
        "calibrationStates": [],
        "softwareProcess": {
          "thickness": {
            "min": 0.0065000000000000006,
            "max": 0.0273,
            "gates": [
              {
                "id": 1,
                "timeSelection": "Peak"
              }
            ]
          }
        }
    }
    ```

#### ultrasonicConventional process


Most of the previous **ut** object properties remain unchanged in the new ultrasonicConventional object now found inside the processes array.

| Property                                                   | :nde-4-0: ultrasonicConventional{} |   :nde-3-3: ut{}   | Comment                                                         |
| ---------------------------------------------------------- | :--------------------------------: | :----------------: | --------------------------------------------------------------- |
| dataEncodingId [number]                                    |  :x: :twisted_rightwards_arrows:   | :white_check_mark: | Moved to datasets array item as dataMappingId                   |
| pulseEcho [object] or pitchCatch [object] or tofd [object] |         :white_check_mark:         | :white_check_mark: |                                                                 |
| waveMode [string]                                          |         :white_check_mark:         | :white_check_mark: |                                                                 |
| velocity [number]                                          |         :white_check_mark:         | :white_check_mark: |                                                                 |
| refractedAngle [number]                                    |  :x: :twisted_rightwards_arrows:   | :white_check_mark: | Moved inside the beams array                                    |
| wedgeDelay [number]                                        |         :white_check_mark:         | :white_check_mark: |                                                                 |
| ascanStart [number]                                        |  :x: :twisted_rightwards_arrows:   | :white_check_mark: | Moved inside the beams array                                    |
| ascanLength [number]                                       |  :x: :twisted_rightwards_arrows:   | :white_check_mark: | Moved inside the beams array                                    |
| pulse [object]                                             |         :white_check_mark:         | :white_check_mark: |                                                                 |
| gates [array]                                              |         :white_check_mark:         | :white_check_mark: |                                                                 |
| rectification [string]                                     |         :white_check_mark:         | :white_check_mark: |                                                                 |
| digitizingFrequency [number]                               |         :white_check_mark:         | :white_check_mark: |                                                                 |
| ascanSynchroMode [string]                                  |         :white_check_mark:         | :white_check_mark: |                                                                 |
| ascanCompressionFactor [number]                            |         :white_check_mark:         | :white_check_mark: |                                                                 |
| gain [number]                                              |         :white_check_mark:         | :white_check_mark: |                                                                 |
| ultrasoundMode [string]                                    |         :white_check_mark:         | :white_check_mark: |                                                                 |
| referenceAmplitude [number]                                |         :white_check_mark:         | :white_check_mark: |                                                                 |
| referenceGain [number]                                     |         :white_check_mark:         | :white_check_mark: |                                                                 |
| digitalBandPassFilter [object]                             |         :white_check_mark:         | :white_check_mark: |                                                                 |
| smoothingFilter [number]                                   |         :white_check_mark:         | :white_check_mark: |                                                                 |
| averagingFactor [number]                                   |         :white_check_mark:         | :white_check_mark: |                                                                 |
| softwareProcess [object]                                   |  :x: :twisted_rightwards_arrows:   | :white_check_mark: | Moved to a dedicated **thickness** processes array item         |
| recurrence [number]                                        |  :x: :twisted_rightwards_arrows:   | :white_check_mark: | Moved inside the beams array                                    |
| tcg [object]                                               |  :x: :twisted_rightwards_arrows:   | :white_check_mark: | Moved inside the beams array                                    |
| calibrationStates [array]                                  |         :white_check_mark:         | :white_check_mark: |                                                                 |
| beams [array]                                              |               :new:                |                    | New array for uniformity with the ultrasonicPhasedArray process |

Additionally, please note that some irrelevant parameters associated with the instrument configuration were removed: 

- Removed from the **gates** array: **produceCscanData**, **peakDetection** and **timeSelection**
- Removed from the **tcg** object: **enabled**
  
The following shows how a version 3.3 **ut** object can be converted to a **ultrasonicConventional** processes array item in version 4.0:

=== "4.0"

    ``` json
    "processes": [
      {
        "inputs": [],
        "outputs": [
          {
            "id": 0,
            "datasetId": 0,
            "dataClass": "AScanAmplitude"
          },
          {
            "id": 1,
            "datasetId": 1,
            "dataClass": "AScanStatus"
          }
        ],
        "id": 0, // (1)!
        "dataMappingId": 0,
        "implementation": "Hardware",
        "ultrasonicConventional": { // (2)!
          "pulseEcho": {
            "probeId": 0
          },
          "waveMode": "TransversalVertical",
          "velocity": 3100.0,
          "wedgeDelay": 6.4799999999999989E-06,
          "digitizingFrequency": 100000000.0,
          "pulse": {},
          "gates": [],
          "rectification": "Full",
          "ascanCompressionFactor": 6,
          "gain": 50.0,
          "ultrasoundMode": "TrueDepth",
          "referenceAmplitude": 80.0,
          "referenceGain": 0.0,
          "digitalBandPassFilter": {},
          "smoothingFilter": 5000000.0,
          "averagingFactor": 1,
          "beams": [
            {
              "id": 0,
              "refractedAngle": 60.0,
              "ascanStart": 0.0,
              "ascanLength": 3.408E-05
            }
          ]
        }
      },
      {
        "inputs": [
          {
            "processId": 0
          }
        ],
        "outputs": [],
        "id": 1,
        "dataMappingId": 0,
        "implementation": "Software",
        "thickness": { // (3)!
          "min": 0.00375,
          "max": 0.01575,
          "gates": [
            {
              "id": 1,
              "gateDetection": "MaximumPeak"
            }
          ]
        }
      }
    ]
    ```
    
    1. As per convention, a process with an Id = 0 defines the group. This group is hence a "Ultrasonic Conventional" group.  
    2. This object is almost identical to the previous *ut* object.
    3. This process replaces the previous **softwareProcess** inside the **ut** object.

=== "3.3"

    ``` json
    "ut": {
      "dataEncodingId": 0,
      "pulseEcho": {
        "probeId": 0
      },
      "waveMode": "TransversalVertical",
      "velocity": 3100.0,
      "refractedAngle": 60.0,
      "wedgeDelay": 6.4799999999999989E-06,
      "ascanStart": 0.0,
      "digitizingFrequency": 100000000.0,
      "ascanLength": 3.408E-05,
      "pulse": {},
      "gates": [],
      "rectification": "Full",
      "ascanCompressionFactor": 6,
      "gain": 50.0,
      "ultrasoundMode": "TrueDepth",
      "highAmplitude": 200.0,
      "referenceAmplitude": 80.0,
      "referenceGain": 0.0,
      "digitalBandPassFilter": {},
      "smoothingFilter": 5000000.0,
      "averagingFactor": 1,
      "softwareProcess": {
        "thickness": {
          "min": 0.00375,
          "max": 0.01575,
          "gates": [
            {
              "id": 1,
              "timeSelection": "Peak"
            }
          ]
        }
      }
    }
    ```

#### ultrasonicMatrixCapture and totalFocusingMethod processes

Previously, a TFM was described by a **fmc** object in which a **tfmDescriptions** was nested. These are now two different processes in two different groups that are interconnected. 

Converting previous **fmc** objects to new **ultrasonicMatrixCapture** array items require some significant modifications. Please refer to the following tables for correspondance between previous properties and new ones. 

Previous **fmc** object in version 3.3:

| Property                     | JSON Depth | Comment                                                                               |
| ---------------------------- | :--------: | ------------------------------------------------------------------------------------- |
| dataEncoding [integer]       |     0      | :arrow_right: Moved one layer above in the general structure of the process           |
| probeId [number]             |     0      | :arrow_right: Moved inside each beams[{pulsers[]}] and beams[{pulsers[]}] array items |
| pulse [object]               |     0      | :arrow_right: Moved inside the waveforms object                                       |
| pulserFrequency [number]     |     0      | :arrow_right: Moved inside the ultrasonicMatrixCapture object                         |
| digitizingFrequency [number] |     0      | :arrow_right: Moved inside the ultrasonicMatrixCapture object                         |
| pulsers [object]             |     0      | :arrow_right: Moved inside the ultrasonicMatrixCapture{beams[]} array                 |
| receivers [object]           |     0      | :arrow_right: Moved inside the ultrasonicMatrixCapture{beams[]} array                 |
| tfmDescriptions [object]     |     0      | :x: :twisted_rightwards_arrows: Replaced by the totalFocusingMethod process           |

New **ultrasonicMatrixCapture** object in version 4.0: 

| Property                       | JSON Depth | Comment                                                                                                   |
| ------------------------------ | :--------: | --------------------------------------------------------------------------------------------------------- |
| acquisitionPattern [string]    |     0      | :new: Indicates which type of acquisition pattern is used, such as `FMC`, `PWI`, or `Sparse`                |
| digitizingFrequency [number]   |     0      | Same as digitizingFrequency in version 3.3                                                                |
| pulserFrequency [number]       |     0      | Same as pulserFrequency in version 3.3                                                                    |
| digitalBandPassFilter [number] |     0      | Same as digitalBandPassFilter found in tfmDescriptions array in version 3.3                               |
| waveforms [array]              |     0      | :new: Describes any type of waveform that could be used for firing a transducer element                    |
| waveforms[{pulse}] [object]    |     1      | Same as pulse in version 3.3                                                                              |
| beams [array]                  |     0      | :new: Lists all the different beams used for acquisitions, in a similar structure as ultrasonicPhasedArray |

The following shows how a version 3.3 **fmc** object can be converted to **ultrasonicMatrixCapture** and **fullMatrixCapture** processes in version 4.0:

=== "4.0"

    ``` json
    "groups": [
    {
      "id": 0,
      "processes": [
        {
          "inputs": [],
          "outputs": [],
          "id": 0,
          "dataMappingId": 0,
          "implementation": "Hardware",
          "ultrasonicMatrixCapture": {
            "acquisitionPattern": "FMC",
            "digitalBandPassFilter": {},
            "digitizingFrequency": 80000000.0,
            "pulserFrequency": 5000000.0,
            "waveforms": [
              {
                "id": 0,
                "pulse": {
                  "width": 1.0000000000000001E-07,
                  "voltage": 40.0,
                  "polarity": "Bipolar"
                }
              }
            ],
            "beams": [
              {
                "id": 0,
                "pulsers": [
                  {
                    "id": 0,
                    "probeId": 0, // (1)!
                    "elementId": 0, 
                    "waveformId": 0 // (2)!
                  }
                ],
                "receivers": [
                  {
                    "id": 0,
                    "probeId": 0,
                    "elementId": 0,
                    "ascanStart": 0.0, // (3)!
                    "ascanLength": 0.00020480000000000002 // (4)!
                  },
                  {
                    "id": 1,
                    "probeId": 0,
                    "elementId": 1,
                    "ascanStart": 0.0,
                    "ascanLength": 0.00020480000000000002
                  }
                  {...}
                ]
              }
            ]
          }
        }
      ]
    },
    {
      "id": 1,
      "processes": [
        {
          "inputs": [
            {
              "processId": 0,
              "groupId": 0
            }
          ],
          "outputs": [
            {
              "id": 0,
              "datasetId": 0,
              "dataClass": "TfmValue"
            }
          ],
          "id": 0,
          "dataMappingId": 0,
          "implementation": "Hardware",
          "totalFocusingMethod": {} // (5)!
        }
      ]
    }
    ]
    ```

    1. The **probeId** was added to each pulsers and/or receivers array items to cover more advanced cases.
    2. The **waveformId** was added to each pulsers array items to cover more advanced cases.
    3. The **ascanStart** was added to each receivers array items to cover more advanced cases.
    4. The **ascanLength** was added to each receivers array items to cover more advanced cases.
    5. The **totalFocusingMethod** parameters are now described in a dedicated process (see below).

=== "3.3"

    ``` json
    "groups": [
    {
      "id": 0,
      "fmc": {
        "dataEncodingId": 0,
        "probeId": 0,
        "pulse": {
          "width": 1.0000000000000001E-07,
          "voltage": 40.0,
          "polarity": "Bipolar"
        },
        "pulserFrequency": 5000000.0,
        "digitizingFrequency": 80000000.0,
        "pulsers": [
          {
            "id": 0,
            "elementId": 0
          },
          {...}
        ],
        "receivers": [
          {
            "id": 0,
            "elementId": 0
          },
          {
            "id": 1,
            "elementId": 1
          },
          {...}
          ],
        "tfmDescriptions": []
      }
    }
    ]
    ```

Most of the previous **tfmDescriptions** object properties remain unchanged in the new **totalFocusingMethod** object now found inside the processes array.

| Property                       | :nde-4-0: totalFocusingMethod{} | :nde-3-3: tfmDescriptions{} | Comment                                                       |
| ------------------------------ | :-----------------------------: | :-------------------------: | ------------------------------------------------------------- |
| id [integer]                   |               :x:               |     :white_check_mark:      | Removed as it was not necessary                               |
| name [string]                  |               :x:               |     :white_check_mark:      | Removed as it can be specified directly in the group name     |
| signalSource [string]          |       :white_check_mark:        |     :white_check_mark:      |                                                               |
| gain [number]                  |       :white_check_mark:        |     :white_check_mark:      |                                                               |
| referenceAmplitude [number]    |       :white_check_mark:        |     :white_check_mark:      |                                                               |
| referenceGain [number]         |       :white_check_mark:        |     :white_check_mark:      |                                                               |
| rectangularGrid [object]       |       :white_check_mark:        |     :white_check_mark:      |                                                               |
| fmcPulserIds [array]           |       :white_check_mark:        |     :white_check_mark:      |                                                               |
| fmcReceiverIds [array]         |       :white_check_mark:        |     :white_check_mark:      |                                                               |
| pathName [string]              |       :white_check_mark:        |     :white_check_mark:      |                                                               |
| waveSet [object]               |       :white_check_mark:        |     :white_check_mark:      |                                                               |
| digitalBandPassFilter [object] |        :x: :arrow_right:        |     :white_check_mark:      | Moved to the **ultrasonicMatrixCapture** processes array item |
| columns [array]                |       :white_check_mark:        |     :white_check_mark:      |                                                               |
| softwareProcess [object]       | :x: :twisted_rightwards_arrows: |     :white_check_mark:      | Moved to a dedicated **tfmBoxGates** processes array item     |
  
The following shows how a version 3.3 **tfmDescriptions** object can be converted to a **totalFocusingMethod** processes array item in version 4.0:


=== "4.0"

    ``` json
    "totalFocusingMethod": {
        "signalSource": "Analytic",
        "gain": 22.0,
        "referenceAmplitude": 80.0,
        "referenceGain": 0.0,
        "rectangularGrid": {},
        "fmcPulserIds": [],
        "fmcReceiverIds": [],
        "pathName": "L-L",
        "waveSet": {}
    }
    ```

=== "3.3"

    ``` json
    "tfmDescriptions": [
      {
        "id": 0,
        "name": "GR-1",
        "signalSource": "Analytic",
        "gain": 22.0,
        "referenceAmplitude": 80.0,
        "referenceGain": 0.0,
        "rectangularGrid": {},
        "fmcPulserIds": [],
        "fmcReceiverIds": [],
        "pathName": "L-L",
        "waveSet": {},
        "digitalBandPassFilter": {},
        "softwareProcess": {
          "boxGates": []
        }
      }
    ]
    ```

## dataMappings

The **dataEncodings** object is renamed **dataMappings** to avoid confusion with other types of encoding.

The following properties need to be moved up one level in the JSON structure: *specimenId* and *surfaceId*.

The terms `ScanLength`, `ScanWidth`, `ScanAlong` and `ScanAround`  used for the **uCoordinatedOrientation** parameter were renamed `Length`, `Width`, `Along` and `Around` respectively to remove the notion of scan axis from this parameter. 

The following shows how a version 3.3 **dataEncodings** object can be converted to a **dataMappings** object in version 4.0:

=== "4.0"

    ``` json
    "dataMappings": [
    {
      "id": 0,
      "specimenId": 0,
      "surfaceId": 0,
      "discreteGrid": {
        "scanPattern": "OneLineScan",
        "uCoordinateOrientation": "Length",
        "dimensions": [
            {
            "axis": "UCoordinate",
            "name": "Scan",
            "offset": 0.0,
            "quantity": 301,
            "resolution": 0.001
            }
        ]}
    }]
    ```

=== "3.3"

    ``` json
    "dataEncodings": [
    {
      "id": 0,
      "discreteGrid": {
        "specimenId": 0,
        "surfaceId": 0,
        "scanPattern": "OneLineScan",
        "uCoordinateOrientation": "ScanLength",
        "dimensions": [
            {
            "axis": "UCoordinate",
            "name": "Scan",
            "offset": 0.0,
            "quantity": 301,
            "resolution": 0.001
            }
        ]}
    }]
    ```

## probes

No modifications were made to this object so far. The official release of .nde 4.0 will confirm whether this object can be duplicated safely from 3.3. to 4.0. 

## wedges

No modifications were made to this object so far. The official release of .nde 4.0 will confirm whether this object can be duplicated safely from 3.3. to 4.0. 

## specimens

No modifications were made to this object so far. The official release of .nde 4.0 will confirm whether this object can be duplicated safely from 3.3. to 4.0. 

## acquisitionUnits

No modifications were made to this object so far. The official release of .nde 4.0 will confirm whether this object can be duplicated safely from 3.3. to 4.0. 

## motionDevices

Note that the unit of the **stepResolution** parameter was converted from step/mm to step/m in version 4.0 to be consistent with the rest of the units used in the file. 

=== "4.0"

    ``` json
    "motionDevices": [
    {
      "id": 0,
      "name": "Glider",
      "encoder": {
        "mode": "Quadrature",
        "stepResolution": 13000.0,
        "preset": 0.0,
        "acquisitionDirection": "Bidirectional"
      }
    },
    {
      "id": 1,
      "name": "Glider",
      "encoder": {
        "mode": "Quadrature",
        "stepResolution": 13000.0,
        "preset": 0.0,
        "acquisitionDirection": "Bidirectional"
      }
    }
    ]
    ```

=== "3.3"

    ``` json
    "motionDevices": [
    {
      "id": 0,
      "name": "Glider",
      "encoder": {
        "mode": "Quadrature",
        "stepResolution": 13.0,
        "preset": 0.0,
        "acquisitionDirection": "Bidirectional"
      }
    },
    {
      "id": 1,
      "name": "Glider",
      "encoder": {
        "mode": "Quadrature",
        "stepResolution": 13.0,
        "preset": 0.0,
        "acquisitionDirection": "Bidirectional"
      }
    }
    ]
    ```
