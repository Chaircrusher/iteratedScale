#
iteratedScale Simple SCALA Scale Generator based on iterated
polynomial functions.


Usage: iteratedScale scaleName coeff1 coeff2 ...

This generates each note of the scale by calculating a
polynomial from the previous notes of the scale.

Example:

iteratedScale "My First iteratedScale" 1.08 0.05

produces this Scala file:
test
7
! 1.08
96.00
! 1.2164
259.68
! 1.36771
441.254
! 1.53795
645.539
! 1.72937
875.245
! 1.94462
1133.54
! octave
1200.00


