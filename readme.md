# PYTHON TPSA Lib

## Announcement

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## About this code

This code allows users to do computations using Truncated Power Series Algebra (TPSA) and/or Differential Algebra (DA) in python.



For TPSA and DA, please refer to chapter 8 in [*Lecture Notes on Special Topics in Accelerator Physics*](http://inspirehep.net/record/595287/files/slac-pub-9574.pdf)  by  Prof. Alex Chao  and chapter 2 in [*Modern Map Methods in Particle Beam Physics*](http://bt.pa.msu.edu/cgi-bin/display.pl?name=AIEP108book) by Prof. Martin Berz. 



This code is developed  using the C++ tpsa lib (<https://github.com/zhanghe9704/tpsa>) and pybind11 (<https://github.com/pybind/pybind11>). 

## How to compile 

Here I will show you how to compile and use the code in Ubuntu. The following command are tested in Ubuntu 16.04 and WSL Ubuntu 18.04. 

To compile the codes, you will need a C++ compiler that supports C++ 11 standard, make, python3 and pybind11.  If you do not have the above programs in your system, you can install them using the following commands. 

```
sudo apt install build-essential 
sudo apt install python3 python3-dev python3-pip  
pip3 install pybind11 
```



(Note: pybind11 works with python2.7, too. So in principle you can compile the code for python 2.7 and use the lib in python 2.7. However, I have not tried it. )



A makefile is provided and one can compile the codes using  the command "make". Assume I have  cloned or downloaded the codes to the following folder:

**$HOME/tpsa-python**

I should see the "Makefile" inside the folder. Just run

```make```

The following lib is generated: 

**tpsa.cpython-36m-x86_64-linux-gnu.so**

The part after "tpsa" is generated by the following command

`python3-config --extension-suffix`

So it may be different in your system. 



## Use the lib in python3

### DA environment initialization and simple DA computation

To use the shared lib in python3, put it in a directory that python3 can find. Start python3 by

`python3`

In side python, load the lib by

`>>> import tpsa`

Initialize the DA environment by `

```
>>> tpsa.da_init(3, 2, 1000)
0
```

The above command initialize a DA environment that holds at most 1000 DA vectors of two variables up to order three. Then let us define the bases as da:

`>>> da = tpsa.base()`

Each individual base can be accessed by da[i], where i is the index of the base. In the above case, i ranges in [0,1]. For example,`

```
>>> da[3]
<tpsa.DAVector object at 0x7f1ca31921f0>
```

After we defined the bases, we can define other DA vectors and perform computations using the bases. 

 ```
>>> x = 0.5 + da[0] + 2.1*da[1]
>>> y = tpsa.sin(x)
>>> y.print()
          V [27]              Base  [ 10 / 10 ]
----------------------------------------------
   4.794255386042030e-01     0 0     0
   8.775825618903728e-01     1 0     1
   1.842923379969783e+00     0 1     2
  -2.397127693021015e-01     2 0     3
  -1.006793631068826e+00     1 1     4
  -1.057133312622268e+00     0 2     5
  -1.462637603150621e-01     3 0     6
  -9.214616899848915e-01     2 1     7
  -1.935069548968272e+00     1 2     8
  -1.354548684277791e+00     0 3     9
 ```

The list of mathematical operators and functions supported can be found in the following. 



### Substitute for variables in DA vectors

Let us  see a 1D example first. Assume we want to calculate the Taylor expansion of sin(x) at x=1 up to the forth order. We can do it as follows. 

```
>>> from tpsa import *
>>> da_init(4, 1, 100)
>>> da = base()
>>> x = sin(1+da[0])
>>> x.print()
          V [35]              Base  [ 5 / 5 ]
----------------------------------------------
   8.414709848078965e-01     0     0
   5.403023058681398e-01     1     1
  -4.207354924039483e-01     2     2
  -9.005038431135663e-02     3     3
   3.506129103366235e-02     4     4
```

Now if we want to evaluate sin(1.2) using the above extension, we need to substitute 0.2 for the variable (base) in the DA vector x. 

```
>>> y = assign()  #Prepare a DA vector to store the result
>>> da_substitute_const(x, 1, 0.2, y)
>>> y.print()
          V [21]              Base  [ 1 / 5 ]
----------------------------------------------
   9.320377212765296e-01     0     0
```

In the second line, we substitute 0.2 for the 1st variable in x and store the result in y. Generally, y is a DA vector, considering x can have more than one bases. But for this specific case, y is just a real number. 



Besides substitute a real number, we can substitute a DA vector, too. 

```
>>> v = 0.2 + da[0]
>>>  da_substitute(x, 0, v, y)
>>> y.print()
          V [21]              Base  [ 5 / 5 ]
----------------------------------------------
   9.320377212765296e-01     0     0
   3.623240241022748e-01     1     1
  -4.663510131426833e-01     2     2
  -6.200135148442674e-02     3     3
   3.506129103366235e-02     4     4
```

If we have a multiple-dimensional DA vector, we can substitute DA vectors for more than one bases at once. 

```
>>> from tpsa import *
>>> da_init(4, 3, 100)
0
>>> da = base()
>>> x = 1.0 + da[0] + 2*da[1] + 0.2*da[2]
>>> v = assign(2)
>>> v[0] = 1 + 0.5*da[0]+ 3*da[1] + 2*da[2]
>>> v[1] = 2 + da[1] + da[2]
>>> idx = [0,1]
>>> y = assign()
>>> da_substitute(x, idx, v, y)
>>> y.print()
          V [49]              Base  [ 4 / 35 ]
----------------------------------------------
   6.000000000000000e+00     0 0 0     0
   5.000000000000000e-01     1 0 0     1
   5.000000000000000e+00     0 1 0     2
   4.200000000000000e+00     0 0 1     3
```

In the above code, we substitute DA vectors stored in "v" for the bases determined by "idx". Note that the size of "idx" should be equal to the size of "v".  This function can be carried out in bunches, which means "x" and "y" can be a DAVectorLists that store multiple DA vectors. The substitution will be performed on all the DA vectors in "x" and the results are saved into "y".  An example is shown as follows. 

```
>>> from tpsa import *
>>> da_init(4, 3, 100)
0
>>> da = base()
>>> x = assign(2)
>>> x[0] = 1.0 + da[0] + 2*da[1] + 0.2*da[2]
>>> x[1] = 0.5 + da[2]
>>> v = assign(2)
>>> v[0] = 1 + 0.5*da[0]+ 3*da[1] + 2*da[2]
>>> v[1] = 2 + da[1] + da[2]
>>> idx = [0,1]
>>> y = assign(2)
>>> da_substitute(x, idx, v, y)
>>> y[0].print()
          V [68]              Base  [ 4 / 35 ]
----------------------------------------------
   6.000000000000000e+00     0 0 0     0
   5.000000000000000e-01     1 0 0     1
   5.000000000000000e+00     0 1 0     2
   4.200000000000000e+00     0 0 1     3

>>> y[1].print()
          V [70]              Base  [ 4 / 35 ]
----------------------------------------------
   5.000000000000000e-01     0 0 0     0
   1.000000000000000e+00     0 0 1     3
```

Please note that here we use the following  command to create a DAVectorList:

```
>>> v = assign(2)
```

The function assign() without argument create a DA vector and assign(n) with a integer n create a DAVectorList that contains n DA vectors with all coefficients zero. 

 ```
>>> from tpsa import *
>>> da_init(4, 3, 100)
0
>>> da = base()
>>> x = assign(2)
>>> x[0] = 1.0 + da[0] + 2*da[1] + 0.2*da[2]
>>> x[1] = 0.5 + da[2]
>>> v = assign(3)
>>> v[0] = 1 + 0.5*da[0]+ 3*da[1] + 2*da[2]
>>> v[1] = 0.5 + da[2]
>>> v[2] = da[0] + 3.3*da[1]
>>> y = assign(2)
>>> da_composition(x, v, y)
>>> y[0].print()
          V [83]              Base  [ 4 / 35 ]
----------------------------------------------
   3.000000000000000e+00     0 0 0     0
   7.000000000000000e-01     1 0 0     1
   3.660000000000000e+00     0 1 0     2
   4.000000000000000e+00     0 0 1     3

>>> y[1].print()
          V [85]              Base  [ 3 / 35 ]
----------------------------------------------
   5.000000000000000e-01     0 0 0     0
   1.000000000000000e+00     1 0 0     1
   3.300000000000000e+00     0 1 0     2
 ```

In the above example, x, v, and y are DAVectorLists. We substitute the DA vectors in v for the bases in x and save the results in y. The size of v should be equal to the dimension of the DA domain. The size of y should be equal to the size of x. 

We can also substitute numbers for the bases in x. In that case, v should be a list of numbers and the results are numbers, too. 

```
>>> v = [1.0, 2.2, 3]
>>> y = da_composition(x, v)
>>> print(y)
[7.0, 3.5]
```



### Composition of DA vectors

In the n dimensional DA domain, if we want to substitute n DA vectors for all the n  bases in m DA vectors, we can use the function da_composition. 

```
>>> from tpsa import *
>>> da_init(4, 2, 100)
0
>>> da = base()
>>> x = assign(2)
>>> x[0] = 1 + da[0] + 2*da[1]
>>> x[1] = 0.5 + 3*da[0] + da[1]
>>> y = assign(2)
>>> y[0] = 1 + 2*da[0] + da[1]
>>> y[1] = 2 + da[0] + 0.5*da[1]
>>> z = assign(2)
>>> da_composition(x, y, z)
>>> z[0].print()
          V [59]              Base  [ 3 / 15 ]
----------------------------------------------
   6.000000000000000e+00     0 0     0
   4.000000000000000e+00     1 0     1
   2.000000000000000e+00     0 1     2

>>> z[1].print()
          V [61]              Base  [ 3 / 15 ]
----------------------------------------------
   5.500000000000000e+00     0 0     0
   7.000000000000000e+00     1 0     1
   3.500000000000000e+00     0 1     2
```

Besides DA vectors, we can also substitute numbers for the bases and the results are numbers too. 

```
>>> y = [1.0, 2.0]
>>> z = da_composition(x, y)
>>> print(z)
[6.0, 5.5]
```

In both the examples above, the size of the second arguments has to be equal to the dimension of the DA domain. The size of the first arguments can vary and the size of the result is always equal to  the size of the first arguments. 

For more examples of using this lib, please check out the files in the **examples** folder.

### Operators and functions overload

Currently, the tpsa lib supports the following operators and math functions. 

Math operator overloaded

| Left hand | Operator | Right hand |
| :-------: | :------: | :--------: |
| DAVector  |    +     |  DAVector  |
|  double   |    +     |  DAVector  |
| DAVector  |    +     |   float    |
|           |    +     |  DAVector  |
| DAVector  |    -     |  DAVector  |
| DAVector  |    -     |   float    |
|   float   |    -     |  DAVector  |
|           |    -     |  DAVector  |
| DAVector  |    *     |  DAVector  |
| DAVector  |    *     |   float    |
|   float   |    *     |  DAVector  |
| DAVector  |    /     |  DAVector  |
| DAVector  |    /     |   float    |
|   float   |    /     |  DAVector  |
| DAVector  |    =     |  DAVector  |
| DAVector  |    =     |   float    |
| DAVector  |    +=    |  DAVector  |
| DAVector  |    +=    |   float    |
| DAVector  |    -=    |  DAVector  |
| DAVector  |    -=    |   float    |
| DAVector  |    *=    |  DAVector  |
| DAVector  |    *=    |   float    |
| DAVector  |    /=    |  DAVector  |
| DAVector  |    /=    |   float    |

Math functions overloaded:

- sqrt
- exp
- log
- sin
- cos
- tan
- asin
- acos
- atan
- sinh
- cosh
- tanh
- pow
- abs
- erf

## Known issues

1. When some temporary variables in the C++ lib go out of scope, the memory of them are not released immediately as in pure C++ environment, although eventually they will be released a few steps after the function call finishes. This means we may need a larger DA vector pool in Python than in C++. Usually a pool size of a few hundred to a few thousand should be large enough, which is not a problem for a modern personal computer.   



## Acknowledgement

Thanks to Dr. Lingyun Yang for providing his tpsa code. 

Thanks to pybind11 developers.

## Contact

Contact the author by hezhang.AT.jlab.org. 

