---
layout: default
title: Probe, wedge and specimen 
parent: Objects
grand_parent: General Concepts
nav_order: 1
---

# Probe, wedge and specimen 

## Probe definition

Probe elements are distributed on an active surface and the corresponding coordinate system is defined per specific nde probe object. In all case, however, there will be a primary and secondary axis defined to allow positioning of the probe versus other elements and the specimen.

 | ![Figure3.png](/NDE_Open_File_Format/assets/images/general-concepts/Figure3.png) |
| ![Figure3-10.png](/NDE_Open_File_Format/assets/images/general-concepts/Figure3-10.png) |
| ![Figure3-12.png](/NDE_Open_File_Format/assets/images/general-concepts/Figure3-12.png) |
| *Figure 21: Illustration of various PAUT probe design* |


| Object            | Symbol, usual script (common) | .json             | Application, Example, Note    | Units | 
| ---               | ---                           | ---               | ---                           | ---   |
| **Primary Axis**  |                               | "primaryAxis"     | Surface coordinate axis on the probe active surface, defined by probe object type | |
| **Secondary Axis** |                              | "secondaryAxis"   | Surface coordinate axis orthogonal to the primary axis on the probe active surface, defined by probe object type  | |
| **Reference point of the probe** |                | "primaryAxis"/"referencePoint" and "secondaryAxis"/"referencePoint" | Offsets on the primary and secondary axis, starting from the probe first element. Allows the positioning of the probe surface coordinate system to the other objects. Defined from a top view. | | 
| **Porbe skew**    |                               |                   | Rotation axis normal to the probe surface and located at the reference point versus other objects the probe connect to. | | 
| **Origin of the probe** | $O_p$                   |                   | Also referred to as the reference point. This reference point coincides with the wedge reference point $O_w'$ | | 
| **Probe referential** | $(O_p x_p, O_p y_p, O_p z_p)$ |               | The referential of the probe with respect to the $O_p$ orgin. By convention, the position of an element is referred from $O_p$ to the geometrical center of the element. This description is convenient for the ray tracing used in the computation of time of flight. | | 
| **First element offsets** | $x_{p0}$, $y_{p0}$, $z_{p0}$ |            | The distance from the origin of the probe $O_p$ to the first element along the local axes. These are also the distances from the reference point to the first element. | | 
| **Center frequency** | $\nu_0$, $f_0$             | centralFrequency  | Check definition! Depends on model/measurement approach   | [m] |
| **Fractional bandwidth** | $\Delta\nu_0$, $\Delta f_0$, … |           |                               | [Hz] |


| ![Figure23.png](/NDE_Open_File_Format/assets/images/general-concepts/Figure23.png) | 
|:--:| 
| *Figure 23: Illustration of the reference point for a linear probe with “primaryAxis"/"referencePoint" = 0.003m and “secondaryAxis "/"referencePoint"=0.* |


| ![Figure24.png](/NDE_Open_File_Format/assets/images/general-concepts/Figure24.png) | 
|:--:| 
| *Figure 24: Probe referential and first element offsets. The origin of the probe, $O_p$, corresponds to the Reference point and to the translated wedge origin $O_w’$.* |


| ![Figure25.png](/NDE_Open_File_Format/assets/images/general-concepts/Figure25.png) | 
|:--:| 
| *Figure 25: Extract for describing center frequency (fc) and fractional bandwidth (BW) * |


### “phasedArrayLinear” probe object

#### Definition 
Array of identical elements uniformly distributed in a plane along the primary axis and secondary axis. This definition support the following use cases :
- 1D linear array with flat active face. 
- 1D linear array with curved active face along the primary axis (“CC” probes)
- 1D linear array with curved active face along the secondary axis (“CCEV” probes)
- 2D linear array with flat active face. 
- 2D linear array with curved active face along the primary axis (“CC” probes)
- 2D linear array with curved active face along the secondary axis (“CCEV” probes)

| Object                                            | Symbol, usual script (common) | .json     | Application, Example, Note    |Units  | 
| ---                                               | ---                           | ---       | ---                           | ---   |
| **Space/gap between elements on primary axis**    |                               | "primaryAxis"/"elementGap"    |           |       |
| **Space/gap between elements on secondary axis**  |                               | "secondaryAxis"/"elementGap"  |           |       |
| **Pitch along primary axis**                      | $\Lambda_{y_p}$               | N/A : deduced from other variables | Application on a regular grid | [m] |
| **Pitch along secondary axis**                    | $\Lambda_{x_p}$               | N/A : deduced from other variables | Application on a regular grid | [m] | 
| **Element size primary axis**                     | $a$                           | “primaryAxis”/“elementLength” | Rectangular element side length | [m] | 
| **Element size secondary axis**                   | $b$                           | "secondaryAxis"/"elementLength" | Recatngular element side length | [m] | 
| **Element count, primary axis**                   | $N_{y_p}$                     | "primaryAxis"/"elementQuantity" | Application on a rectangular grid | - | 
| **Element count, secondary axis**                 | $N_{x_p}$                     | "secondaryAxis"/"elementQuantity" | Application on a rectangular grid | - | 
| **Element radius of curvature, primary axis**     |                               |           | CCradius; see sign convention | [m]   |
| **Element radius of curvature, secondary axis**   |                               |           | CCEVradius; see sign convention | [m]   |


| ![Figure26.png](/NDE_Open_File_Format/assets/images/general-concepts/Figure26.png) | 
|:--:| 
| *Figure 26: Linear probe example* |


| ![Figure3-40.png](/NDE_Open_File_Format/assets/images/general-concepts/Figure3-40.png) | 
|:--:| 
| *Figure 27: Matrix probe example* |


## Probe plane positioning in the local wedge referential 
This section provides the essential definitions and expressions to relate the orientation of the probe plane to the referential system of the wedge. The justification of the wedge component is solely to orient the acoustic probe’s elements in an appropriate direction with considerations of the application at hand. Therefore, we need to relate the probe position and orientation to the imaging volume in the specimen using the wedge as an intermediate structure. An illustration that summarizes all relations between the different referential frames is presented in Figure 28.
The $(u,v)$ position and local directions on the specimen surface are associated with the acoustic imaging referential in respect to the skew angle. Basically, the imaging referential is rotated of a skew angle amount about the local specimen normal to orient wedge in the required direction. The origin and one axis of the imaging referential are coincident with their counterpart in the wedge local referential. The position and orientation of the probe’s primary and secondary axes are related to the wedge local referential through the wedge standard offsets (primary, secondary, and tertiary) and angles (squint, wedge, and roof).


### Defintions and conventions

| Object                    | Symbol, usual script (common)     | .json | Application, Example, Note                        | Units | 
| ---                       | ---                               | ---   | ---                                               | ---   | 
| **Origin of the wedge/Origin of the imaging** | $O_w$, $O_{\mathrm{im}}$  |   | Common origin to the wedge, imaging, and local $(u,v)$ referentials  | - | 
| **Origin of the deported wedge/Origin of the probe reference point** | $O_w’$, $O_p$ |   | Translation of $O_w$           | -     | 
| **Skew Angle**            | $\theta$                          |       | rotation angle along the local normal $\hat{\mathbf{N}}$ at $O_w$ between the local (u, v) axes directions  and the wedge referential $(O_w x_{\mathrm{im}}, O_w y_{\mathrm{im}}, O_w z_{\mathrm{im}})$ | [deg] | 
| **Imaging referential**   | $(O_w x_{\mathrm{im}}, O_w y_{\mathrm{im}}, O_w z_{\mathrm{im}})$ |   | the coordinates of the volume being imaged by the acoustic system  | [m] | 
| **Wedge referential**     | $(O_w x_w, O_w y_w, O_w z_w)$     |       | $O_w x_w$ superposes on $O_w x_{\mathrm{im}}$, plane $(O_w y_w, O_w z_w)$ is in the $(O_w y_{\mathrm{im}}, O_w z_{\mathrm{im}})$ plane | [m] | 
| **Probe referential**     | $(O_w’ x_p, O_w’ y_p, O_w’ z_p)$  |       | $ O_w’y_p$ is along the probe primary axis $ O_w’x_p$ is along the probe secondary axis $ O_w’z_p$ is along the normal to the probe, pointing toward wedge-specimen contact surface ($\hat{\mathbf{z}}_p\cdot\hat{\mathbf{z}}_w<0$) | [m] | 
| **Probe ref point position** | $\mathbf{r}_{\mathrm{ref}} = (x_{\mathrm{ref}}, y_{\mathrm{ref}}, z_{\mathrm{ref}})$ | | the position of the origin of the deported wedge origin/probe referential origin $O_w’$, in $(O_w x_w, O_w y_w, O_w z_w)$ coordinates | [m] |
| **Primary offset**        | $y_{\mathrm{ref}}$                |       | Measured from $O_w$ to $O_w’$ along $O_w y_w$     | [m]   |
| **Secondary offset**      | $x_{\mathrm{ref}}$                |       | Measured from $O_w$ to $O_w’$ along $O_w x_w$     | [m]   |
| **Tertiary offset**       | $z_{\mathrm{ref}} - z_{w0}$       |       | See $z_{w0}$                                      | [m]   |
| **Wedge base offset**     | $z_{w0}$                          |       | Measured from $z_w=0$ to the apex of wedge-specimen contact surface along $O_w z_w$; implicitly defined, depends on wedge geometry | [m] |
| **Squint angle**          | $\alpha$                          |       | $\alpha\in [-180, \ 180]$ deg                     | [deg] | 
| **wedge angle**           | $\beta$                     | wedge angle | $\beta\in [-90, \ 90]$ deg                        | [deg] | 
| **Roof angle**            | $\gamma$                          |       | $\gamma\in [-90, \ 90]$ deg                       | [deg] |
| **Wedge lenght**          | $L$                               |       | Positive, along $O_w y_w$. Defined on Figure 8.   | [m]   |
| **Wedge width**           | $W$                               |       | Positive, along $O_w x_w$. Defined on Figure 8.   | [m]   |
| **Density**               | $\rho$                            |       | Homogeneous in wedge                              | [kg/$m^3$] | 
| **Transverse speed, Shear wave speed** | $c_S$, $c_T$         |       | Scalar; Medium is homogeneous and Isotropic       | [m/s] |
| **Longitudinal speed, Pression wave speed** | $c_L$, $c_P$    |       | Scalar; Medium is homogeneous and Isotropic       | [m/s] |


| ![Figure8-1.png](/NDE_Open_File_Format/assets/images/general-concepts/Figure8-1.png) | 
| ![Figure8-2.png](/NDE_Open_File_Format/assets/images/general-concepts/Figure8-2.png) |
|:--:| 
| *Figure 8 The $\delta u = \delta v = 0.03$ grid in $(u,v)$ space and mapping onto the $(X,Y,Z)$ space. The reference line defines $v = 0$ (orange line). The finite dimension of the embedding surface and reference line restricts the accessible $(u,v)$ grid values, hence the “sleeveless shirt” look of the $(u,v)$ grid. The $(X,Y,Z)$ coordinates mapping of the grid is almost square near the reference line and non uniformity increases as the distance from the reference line increases.* | 



- A **wedge referential** $(O_w x_w, O_w y_w, O_w z_w)$ is attached to the point of contact with the specimen at $O_w$, and so is **imaging referential** $(O_w x_{\mathrm{im}}, O_w y_{\mathrm{im}}, O_w z_{\mathrm{im}})$, itself being related to the $(u,v)$ surface coordinates system by a rotation of **skew angle** $\theta$, see Figure 7, Figure 7, Figure 6.
    - The skew angle is a rotation of $\theta$ angle from the $(u,v)$ position direction $\hat{\mathbf{u}}$ along the local normal,

    $$
    \left(
    \begin{array}{c}
    \hat{\mathbf{x}}_{\mathrm{im}} \\
    \hat{\mathbf{y}}_{\mathrm{im}} \\
    \end{array}
    \right) 
    =
    \left(
    \begin{array}{cc}
    \sin\theta & -\cos\theta \\
    \cos\theta & \sin\theta \\
    \end{array}
    \right)
    \cdot
    \left(
    \begin{array}{c}
    \hat{\mathbf{u}} \\
    \hat{\mathbf{v}} \\
    \end{array}
    \right) \tag{1}
    $$

    - For a rectangular footprint wedge, the common origin of the wedge referential and imaging referential $O_w$ is set at the center of the wedge width $W$.
	- The wedge specimen contact surface can be curved, but the $(O_w x_w, O_w y_w)$ plane is always flat. 
	- Axis $O_w x_w$ superimposes on the axis $O_w x_{\mathrm{im}}$ and is aligned with the wedge width. 
	- The axis $ O_w y_w$ is along the length of the wedge and is in the plane $(y_{\mathrm{im}}, z_{\mathrm{im}})$. 
	- The axis $O_w z_w$ is in the direction of the vector product of $\hat{\mathbf{z}}_w = \hat{\mathbf{x}}_w \times \hat{\mathbf{y}}_w$. 
- **Wedge radius of curvature**: The surface of the wedge in contact with the specimen may be curved, and a convention regarding the sign of the radius of curvature is necessary. The sign of the radius of curvature is defined with respect to the ray tracing from the element to the surface of the wedge in contact with the specimen, see Figure 8.
- **The wedge referential origin** $O_w$ is translated into the origin $O_w’$, the reference point, by an amount $x_{\mathrm{ref}}, y_{\mathrm{ref}}, z_{\mathrm{ref}}$ to accommodate the description of the probe axes $(O_w’ x_p, O_w’ y_p, O_w’ z_p)$ with usual descriptive angles, see Figure 7 .

    $$x_w’ = x_w – x_{\mathrm{ref}} \tag{2}$$

    $$y_w’ = y_w – y_{\mathrm{ref}} \tag{3}$$

    $$z_w’ = z_w – z_{\mathrm{ref}} \tag{4}$$
	
    
- The reference point itself is defined through a set of usual physical **offsets** used in wedge design : $y_{\mathrm{ref}} = {\textbf{Primary Offset}}$ (along $O_w y_w$), $x_{\mathrm{ref}} = {\textbf{Secondary Offset}}$ (along $O_w x_w$), ${\textbf{Tertiary Offset}}$ (along $O_w z_w$) , see Figure 7. The **tertiary offset**  is defined as the distance along the $O_w z_w$ axis between the apex of the surface of the wedge in contact with the specimen, and the position of the reference point $z_{\mathrm{ref}}$. 
- Since the apex of the contact surface may be above the $(O_w x_p, O_w y_p)$, an additional offset, $z_{w0}$, is required to completely define $z_{\mathrm{ref}}$ value. This offset is implicitly defined by the shape of the wedge-specimen contact interface. At the apex along $O_w z_w$, the local tangent plane is parallel to the $(O_w x_w, O_w y_w)$ plane. Example: For standard COD wedge, the design is such that the apex of the face in contact with the specimen is positioned at the center of the wedge length $L$, see ￼￼￼ . $z_{w0}$ offset in this case is $z_{w0} = R-\sqrt{R^2-(L/2)^2}$￼if $R￼ ￼0$￼ $z_{w0} = 0$ if $R < 0$.  distance $z_{\mathrm{ref}}$ from the $z_w = 0$ mark to the reference point is $z_{\mathrm{ref}} = z_{w0} + {Tertiary Offset}$. Similar expressions are found for the AOD case, again ￼￼￼Figure 9￼.
- From the origin $O_w’$, a probe referential with axes $O_w’ x_p$, $O_w’ y_p$, and $O_w’ z_p$ is defined. The orientation of the probe referential follows the (squint, wedge, roof) angles commonly used in the wedge design, see Figure 10: 
    - The squint angle $\alpha$ defines a rotation along the $O_w’ z_w$ axis (positive angle follows the “right hand rule” around $O_w’ z_w$). The amount of rotation in [deg] follows the cross product between $-\hat{\mathbf{y}}_w$ and the a unit vector defined as the projection of $\hat{\mathbf{y}}_p$ onto the $(O_w’ x_w, O_w’ y_w)$ plane,

    $$
    \sin\alpha = \frac{\hat{\mathbf{y}}_p\cdot\hat{\mathbf{x}}_w }{ \sqrt{ (\hat{\mathbf{y}}_p\cdot \hat{\mathbf{x}}_w)^2 + (\hat{\mathbf{y}}_p\cdot \hat{\mathbf{y}}_w)^2 } } \quad . \tag{5}
    $$

    The angle range is $[-180, \ 180]$ deg. The squint angle is analogous to the more widely known azimuth angle found in spherical coordinates.
	The wedge angle $\beta$ is the angle formed by the primary axis $O_w’ y_p$ and the projection of the primary axis onto the $(O_w’ x_w, O_w’ y_w)$ plane. The amount of rotation in [deg] follows 

    $$
    \begin{equation}
    \sin\beta = \hat{\mathbf{y}}_p \cdot \hat{\mathbf{z}}_w \quad . \tag{6}
    \end{equation}
    $$

    - The wedge angle is positive above the $(O_w’ x_w’, O_w’ y_w’)$ plane, negative otherwise. The angle range is $[-90, \ 90]$ deg. The wedge angle is analogous to the more widely known polar or elevation angle found in spherical coordinates.
	The roof angle $\gamma$ is the angle  that defines a rotation of the $O_w’ x_p$ axis about the $O_w’ y_p$ axis (rotation is positive along the $O_w’ y_p$ axis). The amount of rotation [deg] of the $O_w’ x_p$ is referred to the intersection of the $(O_w’ x_w’, O_w’ y_w’)$ plane with the $(O_w’ x_p, O_w’ z_p)$ plane,

    $$
    \sin\gamma = \frac{\hat{\mathbf{x}}_p\cdot\hat{\mathbf{z}}_w }{\cos \beta} \quad . \tag{7}
    $$

    - The roof angle is $0$ when $O_w’ x_p$ lies in the $(O_w’ x_w’, O_w’ y_w’)$ plane. The roof angle is analogous to the more widely known roll angle.

- The probe referential is oriented using the (squint, wedge, roof) angles, Figure 10:
    - $O_w’ y_p$ aligns the Primary Axis of the probe, the unit vector in $(x_w, y_w, z_w)$ coordinates is 

    $$
    \hat{\mathbf{y}}_p = \left(
    \begin{array}{c}
    \sin\alpha \cos\beta \\
    -\cos\alpha \cos\beta \\
    \sin\beta
    \end{array}
    \right) \quad . \tag{8}
    $$

	- $O_w’ x_p$ aligns the Secondary Axis of the probe, the unit vector in $(x_w, y_w, z_w)$ coordinates is 

    $$
    \hat{\mathbf{x}}_p = \left(
    \begin{array}{c}
    \cos\alpha \cos\gamma - \sin\alpha \sin\beta \sin\gamma \\
    \sin\alpha \cos\gamma + \cos\alpha \sin\beta \sin\gamma \\
    \cos\beta \sin\gamma
    \end{array}
    \right) \quad . \tag{9}
    $$

	- $O_w’ z_p$ aligns the Normal of the probe face, pointing toward the specimen surface, the unit vector in $(x_w, y_w, z_w)$ coordinates is 

    $$
    \hat{\mathbf{z}}_p = \left(
    \begin{array}{c}
    \cos\alpha \sin\gamma + \sin\alpha \sin\beta \cos\gamma \\
    \sin\alpha \sin\gamma - \cos\alpha \sin\beta \cos\gamma \\
    \cos\beta \cos\gamma
    \end{array}
    \right) \quad . \tag{10}
    $$

- The following section provides illustrative examples of application of the squint, wedge and roof angles.

| ![Figure28.png](/NDE_Open_File_Format/assets/images/general-concepts/Figure28.png) | 
|:--:| 
| *Figure 28: The main origins and referentials of the specimen-wedge-probe system.* |