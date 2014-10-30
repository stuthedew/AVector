#AVector

Vector class for **`Arduino`** based on **`Processing`**'s [PVector class](https://github.com/processing/processing/blob/44248a80d111b1710a4781739327afa18d3593fa/core/src/processing/core/PVector.java) by Dan Shiffman, Ben Fry and Casey Reas.
My inspiration for writing this is Dan Shiffman's awesome book [The Nature of Code](http://natureofcode.com), which he has graciously [posted on his website](http://natureofcode.com/book/) in its entirety. It's definitely worth buying a [print edition](http://www.amazon.com/gp/product/0985930802/ref=as_li_tf_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=0985930802&linkCode=as2&tag=natureofcode-20) though. You wont regret it!

## Installation

1. [Download](https://github.com/stuthedew/AVector/releases) the Latest release from gitHub.
2. Unzip and modify the Folder name to "AVector" (Remove the '-version')
3. Paste the modified folder on your Library folder (On your `Libraries` folder inside Sketchbooks or Arduino software).

## Getting started

### `AVector` class

A class that describes a 2D vector. This can be used to describe a vector like velocity or acceleration, or used to describe a position. 

This class also includes common vector operations (addition/subtraction, rotation, dot product etc).

#### To declare an AVector object:
```c++
//Simple AVector instance
AVector myVector(x, y);

//This will declare an AVector with x = 0 and y = 0:
AVector myVector(); // == AVector myVector(0, 0)
```

#### Working with AVector components:
```c++
//Simple AVector instance
AVector myVector(4, 5);

//To access stored component values:
myVector.x(); // returns 4
myVector.y(); // returns 5

//To change stored component values:
myVector.set(8, 10);
myVector.x(); // returns 8
myVector.y(); // returns 10

// Also can be set from existing AVector object
AVector newVector(9, 12);

myVector.set(&newVector);
myVector.x(); // returns 9
myVector.y(); // returns 12
```

--------------------------------

##Libary Reference
### `AVector` Class

#####Initialize:
- `AVector::AVector(int x = 0, int y = 0)` Initialize new AVector object

#####Access Component Values:
- `int` `AVector::x()` - return x component
- `int` `AVector::y()` - return y component

#####Set Component Values:
- `AVector` `AVector::set(int x, int y)` - set x,y coordinates from integer values and return new AVector object
- `AVector` `AVector::set(AVector *otherVector)` - set x,y coordinates from AVector object and return new AVector object

#####Vector Operations:
- `AVector` `AVector::add(int x, int y)` - add integer components to AVector object and return new AVector object
- `AVector` `AVector::add(AVector *otherVector)` - add components of two AVector objects and return new AVector object
- `AVector` `AVector::sub(int x, int y)` - subtract integer components from AVector object and return new AVector object
- `AVector` `AVector::sub(AVector *otherVector)` - subtract components of two AVector objects and return new AVector object
- `AVector` `AVector::mult(int scaler)` - multiply (or scale) vector by arbitrary integer value and return new AVector object
- `AVector` `AVector::div(int scaler)` - divide (or scale) vector by arbitrary integer value and return new AVector object
- `AVector` `AVector::setMag(float newMagnitude)` - set component values from vector magnitude (hypotenuse) and return new AVector object
