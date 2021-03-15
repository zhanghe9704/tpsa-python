# -*- coding: utf-8 -*-
"""
Composition of two function g(x) and f(x) as g(f(x)). 
g(x) should be DA vector(s). f(x) could be float(s) or DA vector(s).
"""

from tpsa import *
from math import *

da_init(4,3,400)
da = base()

x1 = da[0] + 2*da[1] + 3*da[2];
x2 = sin(x1);
x1 = cos(x1);

x3 = 0.5*da[0] + 4*da[1] + 2.7*da[2];
x4 = sin(x3);
x3 = cos(x3);

y1 = complex(x1, x2);
y2 = complex(x3, x4);

mmap = assign(2)
mmap[0] = x1
mmap[1] = x2

c1 = complex(4.2, 0.3)
c2 = complex(1/3.0, sqrt(2))
c3 = complex(sin(0.7), cos(0.4))

nmap = [c1 c2 c3]


