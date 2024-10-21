# Groups related arrays and objects

A group comprises datasets and processes that are inherently interconnected. Group identity is defined by its first process (processId=0). A dataset invariably originates from a process.

## **groups** array

The **groups** array describes a group comprising datasets and/or processes

| Property          | Type    | Description                                                                         |
| :---------------- | :------ | :---------------------------------------------------------------------------------- |
| **id** `required` | integer | The unique group id in the JSON structure                                           |
| **name**          | string  | The group name                                                                      |
| **usage**         | string  | Additional information concerning the use of the group (for example: CouplingCheck) |
| **datasets**      | array   | One or several datasets among [datasets](datasets.md)                               |
| **processes**     | array   | One or several processes among [processes](processes.md)                            |
