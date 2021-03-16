import tpsa
from math import *

tpsa.da_init(4,3,400)
da = tpsa.base()

x1 = da[0] + 2*da[1] + 3*da[2];
x2 = tpsa.sin(x1);
x1 = tpsa.cos(x1);

x3 = 0.5*da[0] + 4*da[1] + 2.7*da[2];
x4 = tpsa.sin(x3);
x3 = tpsa.cos(x3);

y1 = tpsa.complex(x1, x2);
y2 = tpsa.complex(x3, x4);

mmap = tpsa.assign(2)
mmap[0] = x1
mmap[1] = x2

c1 = complex(4.2, 0.3)
c2 = complex(1/3.0, sqrt(2))
c3 = complex(sin(0.7), cos(0.4))

nmap = [c1, c2, c3]


