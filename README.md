#AVector

Vector class for **`Arduino`** based on **`Processing`**'s [PVector class](https://github.com/processing/processing/blob/44248a80d111b1710a4781739327afa18d3593fa/core/src/processing/core/PVector.java) by Dan Shiffman, Ben Fry and Casey Reas.
My inspiration for writing this is Dan Shiffman's awesome book [The Nature of Code](http://natureofcode.com), which he has graciously [posted on his website](http://natureofcode.com/book/) in its entirety. It's definitely worth buying a [print edition](http://www.amazon.com/gp/product/0985930802/ref=as_li_tf_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=0985930802&linkCode=as2&tag=natureofcode-20) though. You wont regret it!



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
- `int` `AVector::x()` - return x component
- `int` `AVector::y()` - return y component
- `void` `AVector::set(int x, int y)` - set x,y coordinates from integer values
- `void` `AVector::set(AVector *otherVector)` - set x,y coordinates from AVector object
- `AVector` `AVector::add(int x, int y)` - add integer components to AVector and return new AVector object
- `AVector` `AVector::add(AVector *otherVector)` - add components from two AVector objects and return new AVector object
