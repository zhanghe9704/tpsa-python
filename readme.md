# PYTHON TPSA Lib

## Announcement

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## About this code

This code allows users to do computations using Truncated Power Series Algebra (TPSA) and/or Differential Algebra (DA) in python.



For TPSA and DA, please refer to chapter 8 in [*Lecture Notes on Special Topics in Accelerator Physics*](http://inspirehep.net/record/595287/files/slac-pub-9574.pdf)  by  Prof. Alex Chao  and chapter 2 in [*Modern Map Methods in Particle Beam Physics*](http://bt.pa.msu.edu/cgi-bin/display.pl?name=AIEP108book) by Prof. Martin Berz. 



This code is developed  using the C++ tpsa lib (<https://github.com/zhanghe9704/tpsa>) and pybind11 (<https://github.com/pybind/pybind11>). 

## How to compile and use this code

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



To use the shared lib in python3, put it in a directory that python3 can find. Start python3 by

`python3`

In side python, load the lib by

`>>> import tpsa`

Initialize the DA environment by `

```
>>> tpsa.da_init(3, 4, 1000)
0
```

The above command initialize a DA environment that holds at most 1000 DA vectors of four variables up to order three. Then let us define the bases as da:

`>>> da = tpsa.base()`

Each individual base can be accessed by da[i], where i is the index of the base. In the above case, i ranges in [0,3]. For example,`

```
>>> da[3]
<tpsa.DAVector object at 0x7f1ca31921f0>
```

After we defined the bases, we can define other DA vectors and perform computations using the bases. 

 ```
>>> x = 0.5 + da[0] + 2.1*da[1]
>>> y = tpsa.sin(x)
>>> y.print()
           V[37]               Base  [ 26 / 35 ]
------------------------------------------------ 
   4.794255386042030e-01     0 0 0 0     0
   8.775825618903728e-01     1 0 0 0     1
   1.842923296276988e+00     0 1 0 0     2
  -2.397127693021015e-01     2 0 0 0     5
  -1.006793585347244e+00     1 1 0 0     6
  -1.057133216606947e+00     0 2 0 0     9
  -1.462637603150621e-01     3 0 0 0    15
  -9.214616481384940e-01     2 1 0 0    16
  -1.935069373213407e+00     1 2 0 0    19
  -1.354548499735186e+00     0 3 0 0    25
 ```

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



## Acknowledgement

Thanks to Dr. Lingyun Yang for providing his tpsa code. 

Thanks to pybind11 developers.

## Contact

Contact the author by hezhang.AT.jlab.org. 

