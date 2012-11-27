#!/usr/bin/env python

import os

res = ""

for root, dirname, files in os.walk( '.' ):
    rr = root.replace('.', '')
    res += '! ' + rr + ' ;\n'
    for fname in files:
        res += '@ ' + fname + ' : ' + os.path.join(rr, fname) + ' ;\n'
    res += '\n'

f = open("resources.src", "w")
f.write(res)
f.close()
