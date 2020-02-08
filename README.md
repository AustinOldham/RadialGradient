### Warning: This guide is currently out of date. It will be updated soon.

# RadialGradient

A C++ class used to generate a variety of radial gradients. This was created as part of another one of my projects and is not polished yet.

## Tutorial:

`#include "RadialGradient.h"`

Create the radial gradient object:
`RadialGradient myGradient;`

Create the gradient:
`myGradient.normalRadialGradient(500, 500);`

Other options exist such as specifying the largest and smallest values allowed in the gradient and values used in formulas:
`otherGradient.decreasingRadialGradient(500, 1000, 10, 100, 12);`

The gradient can be modified after it is created:
`myGradient.invert();`

The gradient can be output as a grayscale PPM file which can either be opened in a program such as GIMP or converted to a PNG file with [Netpbm](http://netpbm.sourceforge.net/doc/index.html):
`myGradient.grayscaleGradientToPPM("myfile");`

![Output](https://i.imgur.com/pVzmbA6.png)
