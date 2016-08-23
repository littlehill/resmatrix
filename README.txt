This should provide a way to generate equations for NxM resistor networks. 
Originally developed for purposes of FEE eForce Prague formula student project. (CTU Prague)
Because some nutshot forgot to connect the resistor network diferently we would originally redo all boards for temperature measurement. 
However we found out we have enough measurement data to calculate each resistor in the network. 
This program should be able to do parametric star-mesh transformations & generate equations which then need more adjustment in maltab or any other sw for equation solving. 

Bellow is shown simple network of 2x2 resistors, with anmed junctions Jsig1,2 & Jgnd1,2 
This program works with networks 3x3 and bigger.
It is designed to ease the hard work of defining equations as single impedance between two nodes (Junctions).
 
Jsig1         Jsig2
 |             |
 .             .
 |\            |\                  
 | R1          | R2
_|__\._________|__\._______Jgnd1
 |             |
 .             .
 |\            |\                  
 | R3          | R4
_|__\._________|__\._______Jgnd2
 |             |