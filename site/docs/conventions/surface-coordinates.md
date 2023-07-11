---
layout: default
title: Surface coordinates
parent: Notation and convention
grand_parent: Conventions
nav_order: 1
---

# Surface coordinates

In scenarios in which probe positioning is in direct relation to the surface, the position on the surface of a specimen, $(X, Y, Z)$ in global coordinates, is transformed in $(u,v)$ surface orthogonal curvilinear coordinates, see Figure 2. The $(u,v)$ coordinates are useful in the context of surface mapping because they allow for regular grid data encoding in $(u,v)$ space onto a non uniform distribution of positions in $(X,Y,Z)$ space. The $(u,v)$ coordinates computed from a reference line also corresponds to lengths measured with a measuring tape directly on the specimen’s surface: the coordinate $u$ is along the reference line (e.g. a weld line) and the coordinate $v$ is along a perpendicular direction to the former. 

The $(u,v)$ formalism can be employed both for linear scans along a weld line, or raster scans on a surface. The use of $(u,v)$ coordinates is enforced as a way to disambiguate the notions of “scan axis” and “index axis” which are arbitrarily interpreted depending on the application. The user can associate the $u$ or $v$ coordinate to “scan” or “index” label at his convenience. See Figure 2 for some illustrations of typical applications.

The direction of the $u$ and $v$ coordinates as they are mapped on the specimen surface is described by local tangent unit vectors $\hat{\mathbf{u}}(u,v)$ and $\hat{\mathbf{v}}(u,v)$ in general coordinates, Figure 3. While these local unit vectors are always orthogonal to each other, they generally change direction in general coordinates, Figure 4. 

The linear evolution of general coordinates values along the $u$ axis is true only on the reference line at $v=0$, Figure 5. The mapping of $u$ at values of $v\neq 0$ are involutes of $v$, and the linearity in general coordinates along these involutes is generally not respected. This is made clear by mapping uniform grids in $(u,v)$ space onto non-planar geometries: the otherwise regular square cell $(u,v)$ grid is affected by local deformations (i.e. compression, stretching and shearing) in the general coordinates space.

The $(u,v)$ coordinates are set according to some $(u, v) = (0,0)$ origin at $(X_0, Y_0, Z_0)$ on the surface of the specimen, and some preferred direction along the surface, Figure 3. For instance, one can set a reference line along the center line of a weld line to define $u$ at $v = 0$. The $u$ coordinate at $v=0$ is always on the reference line. This defines the local vector $\hat{\mathbf{u}}(u,v=0)$ along coordinate $u$, and the perpendicular local vector $\hat{\mathbf{v}}(u,v=0)$ along coordinate $v$. The $\hat{\mathbf{u}}(u,v=0)$ unit vector is always tangent both to the surface of the specimen and the reference line, and the $\hat{\mathbf{v}}(u,v=0)$ unit vector is always tangent to the specimen surface and perpendicular to the reference line.

The mutual orientation of $\hat{\mathbf{u}}$ and $\hat{\mathbf{v}}$ is such that the local surface normal $\hat{\mathbf{N}} = \hat{\mathbf{u}}\times\hat{\mathbf{v}}$ points toward the interior of the part. The direction of $\hat{\mathbf{u}}$ and $\hat{\mathbf{v}}$ define the sign of the corresponding coordinate with respect to the origin $(u,v) = (0,0)$. 

The $(u,v)$ surface coordinates map to global $(X,Y,Z)$ coordinates. Note that multiple $(u,v)$ values may map a single $(X,Y,Z)$ point depending on the choice of reference line (i.e. many to one definition). For instance, if the reference line is a constant pitch helix wrapping around a cylinder, the $v$ axis starting at $u=0$ will cross the reference line periodically along the cylinder axis. To uniquely define $(u,v)$ to $(X,Y,Z)$ coordinates, if that is the preference, one has to choose a special case of reference line, or bound the $(u,v)$ domain on the surface. A situation where one may disregard a non-unique correspondence is for a helix weld line pursuit on a tube section: the reference line in that case is preferably along the center line of the weld since it is the main object of interest, see Figure 3. A situation where one may want a unique correspondence is the surface mapping (e.g. “corrosion mapping”) of a tube: the reference line in that case is preferably along the circumference of the tube or the axis of the tube.

In the coming sections, a general description of the $(u,v)$ coordinates mapping into general coordinates is presented. Then, typical application cases to NDE are presented as examples of increasing complexity. 

To conclude this introduction on surface coordinates, and anticipate coming elements, the $(u,v)$ surface coordinates define a position on the surface but do not directly indicate an orientation of the object that is positioned. In the domain of ultrasonic NDE, the object that needs to be positioned and oriented on the specimen surface is the transducer, the active part of the acoustic probe sensing element(s). In many cases for ultrasonic applications, an intermediate object, a solid wedge made from plastic or glass, or a volume of liquid, stands between the face of the elements and the surface of the specimen. This wedge, solid or liquid, is the one thing the operator positions and orients on the surface of the specimen to obtain acoustic data in a specific direction. The skew angle $\theta$ is the angle between the $O_w y_{\mathrm{im}}$ acoustic imaging axis direction, $\hat{\mathbf{y}}_{\mathrm{im}}$, and the local $u$ axis direction, $\hat{\mathbf{u}}$. The topic of object orientation is further developed in the description of the wedge, starting at page 14.


| ![Figure2-1.png](/NDE_Open_File_Format/assets/images/conventions/Figure2-1.png) | ![Figure2-2.jpg](/NDE_Open_File_Format/assets/images/conventions/Figure2-2.png) | ![Figure2-3.jpg](/NDE_Open_File_Format/assets/images/conventions/Figure2-3.png) | 
|:--:| 
| *Figure 2 The $(u,v)$ coordinates concept on some typical scanning NDE applications.* |


| ![Figure3.jpg](/NDE_Open_File_Format/assets/images/conventions/Figure3.png) | 
|:--:| 
| *Figure 3 Schematics of the $(u,v)$ surface coordinates system. The $u$ ($v=0$) axis lies along a reference line (in orange), itself going through the $(u,v)$ system’s origin.* |


| ![Figure4.jpg](/NDE_Open_File_Format/assets/images/conventions/Figure4.png) | 
|:--:| 
| *Figure 4 The reference line defines the $u$ coordinate at $v=0$. The general coordinates direction of the local vectors $\hat{\mathbf{u}}$ and $\hat{\mathbf{v}}$ generally changes along the reference line.* |


| ![Figure5.jpg](/NDE_Open_File_Format/assets/images/conventions/Figure5.png) | 
|:--:| 
| *Figure 5 A uniform grid in $(u,v)$ space does not remain uniform through the transformation in the general coordinates. The length $\delta l$ along involutes of $v$ measured on the specimen surface generally changes with $v$ although the $u$ value is constant.* |


| (a) ![Figure6-a.jpg](/NDE_Open_File_Format/assets/images/conventions/Figure6-a.png) | 
| (b) ![Figure6-b.jpg](/NDE_Open_File_Format/assets/images/conventions/Figure6-b.png) | 
| (c) ![Figure6-c.jpg](/NDE_Open_File_Format/assets/images/conventions/Figure6-c.png) | 
|:--:| 
| *Figure 6 (a) Non-unique correspondence of $(u,v)$ to $(X,Y,Z)$ coordinates. (b,c) Unique correspondence of $(u,v)$ to $(X,Y,Z)$ coordinates. The reference line (orange) defines the $u$ coordinate.* |

## General procedure regarding the association of the $(u,v)$ coordinates to $(X,Y,Z)$ coordinates

This section is a formal description of the method leading to the computation of the $(u,v)$ coordinates. This section may be skipped as many applications are based on simple geometries and reference lines. Some examples related to common scanning applications are presented in the next section. 

The surface of the specimen $S$ is set in general coordinates $\mathbf{R} = (X,Y,Z)^T$ and we assume a well defined local normal vector $\hat{\mathbf{N}}(\mathbf{R})$ pointing inside the part.
A reference line $\mathcal{l}_{\mathrm{ref}}$ is defined at the surface of the specimen. The length of the reference line may be measured from an arbitrary origin as the sum of the arclengths $dl’$ over the length $l$. This defines the $u$ coordinate for $v=0$,

$$
u(\mathbf{R})-u_0 = \int_{0}^{l} dl' = \int_{\mathbf{R} \in \mathcal{l}_{\mathrm{ref}}} \sqrt{ d{X'}^2+ d{Y'}^2+ d{Z'}^2 }  \tag{1}
$$

where $u_0$ is the arclength at the user defined starting point. Note that the direction of the $u$ coordinate (i.e. the positive direction along the line in general coordinates) is chosen here: depending on the order of appearance of the $(X,Y,Z)$ values defining $\mathcal{l}$ and consequent choice of $u_0$, the $u$ direction along the reference line in the general coordinates will revert.
A unique value of $u$ is obtained from a point $(X,Y,Z) \in$, and the general coordinates along the line can be expressed as functions of $u$; $R(u) = (X(u), Y(u), Z(u))$. The local direction $\hat{\mathbf{u}}$ of the $u$ coordinate at $\mathbf{R}(u) = (X(u),Y(u),Z(u))^T$  is obtained through differentiation,

$$
\hat{\mathbf{u}}(u) = \frac{\partial \mathbf{R}(u)}{ \partial u} / \left| \frac{\partial \mathbf{R}(u)}{ \partial u} \right| \quad .  \tag{2}
$$

The orthogonal direction $\hat{\mathbf{v}}$ is defined as the outer product of the local normal (pointing inside the specimen) with the $\hat{\mathbf{u}}$ direction obtained previously,

$$
\hat{\mathbf{v}}(u) = \hat{\mathbf{N}}(u) \times \hat{ \mathbf{u} }(u) \quad . \tag{3}
$$

An infinitesimal increment of $\delta v$ along direction $\hat{\mathbf{v}}(u)$ for all positions $u$ defines an involute of the coordinate $v$ (the line $\mathcal{l}_{\mathrm{ref}}$ being the initial one), 

$$
\mathbf{R}(u, v=\delta v) = \mathbf{R}(u, v=0) + \delta v \hat{\mathbf{v}} \quad . \tag{4}
$$

Once the new position $\mathbf{R}(u, v=\delta v)$ along $v$ is found, another local direction for $u$ in the general coordinates is computed as in Eq. \ref{eq_uv_001} only this time at $\mathbf{R}(u, v=\delta v)$,

$$
\hat{\mathbf{u}}(u, v=\delta v) = \frac{\partial\mathbf{R}(u, v=\delta v)}{ \partial u} / \left| \frac{\partial \mathbf{R}(u, v=\delta v)}{ \partial u} \right| \quad . \tag{5}
$$ 

The evaluation of the local $\hat{\mathbf{v}}$ follows as in Eq. 3, only with the updated position $\mathbf{R}(u, v=\delta v)$. This iterative scheme produces a succession of involutes of the $u$ coordinate along the $v$ axis. This enables one to associate all positions on the surface in general coordinates to $(u,v)$ surface coordinates. The approach to iteratively construct the $v$ axis and its involutes starting from the reference line is illustrated in Figure 4. Note that multiple $(u,v)$ values may define a single point $(X,Y,Z)$ on the surface. 

A uniformly spaced grid in $(u,v)$ coordinates is unlikely to produce a uniformly spaced grid in coordinates $(X, Y, Z)$. For instance, the arclength segment along the involutes $dl(u,v) = \sqrt{ (\partial X(u,v)/ \partial u)^2 + (\partial Y/\partial u)^2 + (\partial Z/\partial u)^2} du$ may change with $v$. As an illustration, a direct implementation of the method presented above is applied to a parabolic reference line lying on a parabolic shaped surface. The parabolic surface is

$$
\mathcal{S} : \ 
\left(
\begin{array}{c}
X \\
Y \\
Z
\end{array}
\right) 
=
\left(
\begin{array}{c}
X \\
Y \\
-0.8 X^2
\end{array}
\right) . \tag{6}
$$

and the parabolic reference line $\mathcal{l}$ is

$$
\begin{equation}
\mathcal{l} : \ 
\left(
\begin{array}{c}
X \\
Y \\
Z
\end{array}
\right) 
=
\left(
\begin{array}{c}
X \\
X^2 \\
-0.8 X^2
\end{array}
\right) \quad . \tag{7}
\end{equation}
$$

The surface and reference line are limited to a 1 unit x 1 unit square boundary in both $X$ and $Y$. A discrete grid in $(u,v)$ space of $\delta u = delta v = 0.03$ is defined. The $(u,v)$ grid and its mapping to $(X, Y, Z)$ coordinates are presented in Figure 6. The $(u,v)$ mapping of a uniform grid onto $(X,Y,Z)$ space does not lead to a uniform grid in the later. In the case of Figure 6, the parabolic shape of the reference line even creates a converging grid in $(X,Y,Z)$ space that is strongly compressed over the $u$. 
Comment on the numerical implementation: The iterative scheme above relies on the direction of the $\hat{\mathbf{v}}$ vector field to position the next involute. The accuracy of the computation of the surface tangent $\hat{\mathbf{v}}$ vector direction is critical. In the example provided here, the specimen surface $\mathcal{S}$ was sampled and a 2D interpolation scheme was used to approximate the position of arrival of the $\delta v \hat{\mathbf{v}}$ vector on the surface.


| ![Figure7-1.jpg](/NDE_Open_File_Format/assets/images/conventions/Figure7-1.png) | 
| ![Figure7-2.jpg](/NDE_Open_File_Format/assets/images/conventions/Figure7-2.png) |
| ![Figure7-3.jpg](/NDE_Open_File_Format/assets/images/conventions/Figure7-3.png) |
| ![Figure7-4.jpg](/NDE_Open_File_Format/assets/images/conventions/Figure7-4.png) |
|:--:| 
| *Figure 7 The reference line serves as the initial involute along the $v$ axis laid on the surface. From the local direction of axis $u$ on the surface of the part, an orthogonal direction, $\hat{\mathbf{v}}$ is obtained.* |



| ![Figure8-1.jpg](/NDE_Open_File_Format/assets/images/conventions/Figure8-1.png) | 
| ![Figure8-2.jpg](/NDE_Open_File_Format/assets/images/conventions/Figure8-2.png) |
|:--:| 
| *Figure 8 The $\delta u = \delta v = 0.03$ grid in $(u,v)$ space and mapping onto the $(X,Y,Z)$ space. The reference line defines $v = 0$ (orange line). The finite dimension of the embedding surface and reference line restricts the accessible $(u,v)$ grid values, hence the “sleeveless shirt” look of the $(u,v)$ grid. The $(X,Y,Z)$ coordinates mapping of the grid is almost square near the reference line and non uniformity increases as the distance from the reference line increases.* |

