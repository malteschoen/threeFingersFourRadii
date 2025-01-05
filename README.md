# what is this?
this repo documents the idea of using a profile extrusion die with three vertical fingers and a flat bottom to generate 6 internal corners (two per finger) - see figure 1.

![figure1](https://github.com/malteschoen/threeFingersFourRadii/blob/main/media/figure1.png)

By varying the radii per corner, a wider rate of shear stresses can be achived at a fixed flowrate through the die. If at the same time the flow behaviour or extrudate surface quality per corner is monitored, a lot of data can be gathered in a very short time.

# An example
Let's say that flow is stable for a given corner with a large radius, but anomalous (poor extrudate surface quality) for another corner with a smaller radius.

![figure2](https://github.com/malteschoen/threeFingersFourRadii/blob/main/media/figure2.png)

Our conclusion is hence that the critical shear stress triggering the flow anomaly lies somewhere between the shear stresses calculated for each of the two corners.

# Shear stress and velocity distribution as approximated by OpenFOAM simulation

Figure 3 shows the numerically obtained distribution of shear stress at the approximated melt-steel interface. Note that stress intensity peaks in the corners, but the extent of the peak depends on the radius.
![figure3](https://github.com/malteschoen/threeFingersFourRadii/blob/main/media/figure3.png)

Figure 4 shows that by matching big and small radii at each finger, overall melt velocity distribution is homogenous.
[figure4](https://github.com/malteschoen/threeFingersFourRadii/blob/main/media/figure4.png)


# Some tabulated data 

| Entry no. | x-coordinate [mm] | radius [mm] | shear stress [kPa] |
|---|----|---|------|
| 1 | 10 | 4 | 11.1 |
| 2 | 20 | 1 | 14.5 |
| 3 | 30 | 2 | 10.5 |
| 4 | 40 | 3 | 12.2 |
| 5 | 50 | 5 | 10.5 |
| 6 | 60 |0.5| 11.9 |

# The same data, now graphed
