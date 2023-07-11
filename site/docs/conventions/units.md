---
layout: default
title: Units
parent: Conventions
nav_order: 1
---

# Units 

Angles are expressed in degrees, while all other units in the dataset are in International System (SI) units, expressed in meters and seconds unless otherwise indicated by a "unit" key. For example, the "Bitfield" and "Percent" units are used for the ascan in the dataset object. 

## Units, physical quantities, definitions: 

| Quantity                  | Symbol, usual script (common) | Units         |
| ---                       | ---                           | ---           |
| **Distance, positions**   | x, y, z                       | meter [m]     |
| **Time**                  | t                             | second [s]    |
| **Mass**                  | M, m                          | kilogram [kg] |
| **Speed**                 | c, v                          | [m/s]         |
| **Angle**                 | α, β, γ, θ, φ                 | degree [°]    |
| **Density**               | ρ                             | [kg/$m^3$]    |
| **Gain**                  |                               | dB            |
| **Attenuation**           | A                             | dB            |
| **Fractional Bandwidth**  |                               | %             |


| Object                        | Symbol, usual script (common)             | Application, Example, Note                                    |
| ---                           | ---                                       | ---                                                           |
| **Vector (column)**           | $v$, lower case bold, one underbar in hand script ($e.g.\underline{v}$)   | $ v =  \begin{bmatrix}\\ x, y, z\end{bmatrix}^T$, $T$ is the transpose operator (transforms row vector into column vector)|
| **Vector norm (Euclidian)**   | $\|v\|$                                   | $\|v\| = \sqrt{x^2 + y^2 + z^2}$  |
| **Referential origin**        | $O$                                     | Often with a subscript to specify, e.g. $O_w$ , $O_p$      |
| **Point**                     | $(x, y, z)$                             | Single point coordinates                                      |
| **Axe**                       | $Ox$, $Oy$, $Oz$                   | Single axis with respect to some origin. The explicit use of the origin $O$ may be abandoned when the nature of the origin is obvious. |
| **Plane**                     | $(Ox, Oy)$, $(Ox, Oz)$, $(Oy, Oz)$  | Single plane with respect to some origin                      |
| **Referential**               | $(Ox, Oy, Oz)$                          |                                                               |
| **Scalar, inner product**     | .                                         | $x^T \cdot y = z$, $z$ is scalar                              |
| **Vectorial, outer product**  | $\times$                                  | $x\times y = z$, $z$ is vector, perpendicular to $x$ and $y$  |
| **Unit vector**               | $\hat{v}$                                 | $\hat{v} = v / \| v \|$, subject to $\hat{v}^T \cdot \hat{v} = 1$ |
| **Radius of curvature**       | R, r, ρ                                   | Formally positive, *but* in the context of ray tracing will define the interface as being concave (R < 0) or convex (R > 0), see Figure 1 |

| ![Figure1.png](/NDE_Open_File_Format/assets/images/conventions/Figure1.png) | 
|:--:| 
| *Figure 1 The convention regarding the sign of the radius of curvature in the context of ray tracing.* |
