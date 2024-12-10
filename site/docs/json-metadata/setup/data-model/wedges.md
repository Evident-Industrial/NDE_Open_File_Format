# Wedge Related Arrays and Objects

**Wedges** are used to direct ultrasonic waves into a test material at a specific angle, enabling the detection of flaws at different orientations. It helps convert wave modes and ensures efficient energy transfer between the probe (transducer) and the test piece.

## **wedges** array

The **wedges** array lists the wedge(s) used with the associated probe(s).

| Property                      | Type    | Description                                                                                                          |
| :---------------------------- | :------ | :------------------------------------------------------------------------------------------------------------------- |
| **id** `required`             | integer | The unique wedge id in the JSON structure referenced in [wedgeAssociation](probes.md#wedgeassociation-object) object |
| **model** `required`          | string  | The wedge model reference                                                                                                          |
| **serie**                     | string  | The wedge series reference                                                                                                          |
| **serialNumber**              | string  | The wedge serial number                                                                                                  |
| **angleBeamWedge** `required` | object  | An [angleBeamWedge](#anglebeamwedge-object) object                                                                   |
| **positioning** `required`    | object  | A [positioning](#positioning-object)  object                                                                         |

**Related objects**: [wedgeAssociation](probes.md#wedgeassociation-object)

### **angleBeamWedge** object

The **angleBeamWedge** object describes an angle beam wedge. 

| Property                            | Type   | Unit | Description                                                          |
| :---------------------------------- | :----- | :--: | :------------------------------------------------------------------- |
| **width** `required`                | number |  m   | The width of the wedge                                               |
| **height** `required`               | number |  m   | The height of the wedge                                              |
| **length** `required`               | number |  m   | The length of the wedge                                              |
| **longitudinalVelocity** `required` | number | m/s  | The ultrasound waves' longitudinal velocity inside the wedge material |
| **mountingLocations** `required`    | array  |  -   | A [mountingLocations](#mountinglocations-array) array                |
| **pocketDepth**                     | number |  m   | The pocket depth of the wedge                                        |

Hypothesis and conventions: 

  - Wedge body and contact surface are considered symmetrical.
  - The wedge contact surface (with the specimen) is flat or curved with a single radius of curvature.
  - The probe(s) contact surface is flat.
  - The positionning of the probe first element on a given wedge, which correspond to the so-called *mounting location*, is standardized (by design of the probe/wedge assembly).
  - The wedge coordinate system $(x_w, y_w, z_w)$ origin is centered at the bottom of its front face (see figure below).
  - The wedge coordinate system orientation is defined so the $(y_w)$ axis is aligned with the wedge length, the $(x_w)$ axis aligned with the wedge width, and the $(z_w)$ axis aligned with the wedge height. 

![angleBeamWedge.png](../../../assets/images/json-metadata/setup/data-model/wedges/angleBeamWedge.png)


**Flat wedges**


- For flat wedges, the application of the above rules is straightforward as there's no ambiguity for the definition of the probe positioning.

**Curved wedges**

 - The application of a wedge on a tubular component  typically involves the use of a wedge with a matching curved surface. Such wedges require additional conventions.

 - Typical configurations are axial outer diameter (AOD) or circumferential outer diameter (COD). Note that a skew angle for outer or inner diameter inspection is also possible in this definition.

- The curved wedge face is handled by redefining the *tertiary offset* and by defining the actual wedge curvature in the wedge object. The tertiary offset is defined for a flat wedge that is machined to the desired curvature.   


#### **mountingLocations** array

The **mountingLocations** array describes the mounting location(s) of the wedge.

| Property                       | Type    | Unit   | Description                                                                            |
| :----------------------------- | :------ | :----- | :------------------------------------------------------------------------------------- |
| **id** `required`              | integer | -      | The mounting location id referenced in [anglebeamWedge](#anglebeamwedge-object) object |
| **wedgeAngle** `required`      | number  | degree | The wedge angle in degrees                                                              |
| **squintAngle**                | number  | degree | The wedge squint angle in degrees                                                       |
| **roofAngle**                  | number  | degree | The wedge roof angle in degrees                                                         |
| **primaryOffset** `required`   | number  | m      | The wedge primary offset                                                               |
| **secondaryOffset** `required` | number  | m      | The wedge secondary offset                                                             |
| **tertiaryOffset** `required`  | number  | m      | The wedge tertiary offset                                                              |

Hypothesis and conventions: 

- A probe is maintained in position on a wedge through an interface face, named the *mounting location*, and its origin $(x_m, y_m, z_m)$ is defined by the aforementionned **primaryOffset**, **secondaryOffset**, and **tertiaryOffset** plus three angles:
  - **wedgeAngle** $\beta$ : Angle between the normal of the interface face, $z_m$, and the $z_w$ axis
  - **squintAngle** $\alpha$ : Angle between the projection of the probe primary axis on the $x_w$/$y_w$ plane, $y_m$, and the $y_w$ axis. 
  - **roofAngle** $\gamma$ : Angle between $x_m$ and $x_w$, defined by a rotation around the probe primary axis.

- The wedge **skew angle** is defined by the angle between the wedge and **u** axis on the surface of the part at the wedge origin.

- Its positioning on the specimen is given in relation to the $(u,v)$ coordinates with the **uCoordinateOffset** and **vCoordinateOffset** located in the Setup JSON formatted dataset at **wedges[x].positioning**.   

- The positioning of the probe $(x_p, y_p, z_p)$ coordinate system is achieved in the $(x_w,y_w,y_w)$ coordinates through the successive application of the **primaryOffset** (on the $(y_w)$ axis), the **secondaryOffset** (on the $(x_w)$ axis), and the **tertiaryOffset** (on the $(y_w)$ axis). The origin of the probe coordinate system is the center of the first probe element.
- The orientation of the probe $(x_p, y_p, z_p)$ coordinate system is achieved in the $(x_w,y_w,y_w)$ coordinates through the successive application of the **wedgeAngle**, **squintAngle**, and **roofAngle**.
- It is possible to have multiple probe **mountingLocations** defined on a single wedge, for example in the case of Dual Linear Array (DLA) or Dual Matrix Array (DMA) probe

![mountingLocations.png](../../../assets/images/json-metadata/setup/data-model/wedges/mountingLocations.png)


### **positioning** object

The **positioning** object describes the wedge position with respect to the specimen and its surface.

| Property                         | Type    | Description                                                       |
| :------------------------------- | :------ | :---------------------------------------------------------------- |
| **specimendId** `required`       | integer | The related specimen id (plate, pipe, bar)                       |
| **surfaceId** `required`         | integer | The related surface id (plate surface, pipe surface, bar surface) |
| **uCoordinateOffset** `required` | number  | The offset relative to the $u$ axis                                       |
| **vCoordinateOffset** `required` | number  | The offset relative to the $v$ axis or coordinate object                  |
| **skewAngle** `required`         | number  | The skew angle in degrees                                         |


**Related objects**: [specimens](specimens.md#specimens-array), [surfaces](specimens.md#surfaces-array)

![positioning.png](../../../assets/images/json-metadata/setup/data-model/wedges/positioning.png){width="500px"}

## Examples

Examples of phased array and single- and dual-element wedge definitions based on specifications in the Evident probe catalog.  

??? example "Phased array wedge examples"

    === "SA32-N55S"
        ``` json
        --8<-- "docs/assets/json/json-metadata/setup/data-model/wedges-SA32-N55S.json"
        ``` 
    === "SA15-N30S-IH 2-3-5"
        ``` json
        --8<-- "docs/assets/json/json-metadata/setup/data-model/wedges-SA15-N30S-IH 2-3-5.json"
        ```
    === "HydroFORM"
        ``` json
        --8<-- "docs/assets/json/json-metadata/setup/data-model/wedges-HydroFORM.json"
        ``` 
    === "SPWZ1-N60L-IHC"
        ``` json
        --8<-- "docs/assets/json/json-metadata/setup/data-model/wedges-SPWZ1-N60L-IHC.json"
        ``` 
    === "SA26-DN55L-FD25-SS-IHC-AOD24"
        ``` json
        --8<-- "docs/assets/json/json-metadata/setup/data-model/wedges-SA26-DN55L-FD25-SS-IHC-AOD24.json"
        ```
    === "SA27-DN55L-FD15-IHC-AOD18"
        ``` json
        --8<-- "docs/assets/json/json-metadata/setup/data-model/wedges-SA27-DN55L-FD15-IHC-AOD18.json"
        ```
    === "Integrated wedge"
        ``` json
        --8<-- "docs/assets/json/json-metadata/setup/data-model/wedges-XAIW-0012.json"
        ```

??? example "Single and dual element wedge examples"

    === "ST1-25L-IHC"
        ``` json
        --8<-- "docs/assets/json/json-metadata/setup/data-model/wedges-ST1-25L-IHC.json"
        ``` 
    === "10CCEV35-32-A15"
        ``` json
        --8<-- "docs/assets/json/json-metadata/setup/data-model/probes-D713.json"
        ```