#!/usr/bin/python

import sys, os
import glob, re

partA = """\
python version %d.%d.%d can't run %s.  Try the alternative(s):

"""
partB = """
Run "man python" for more information about multiple version support in
Mac OS X.
"""

sys.stderr.write(partA % (sys.version_info[:3] + (sys.argv[0],)))

dir, base = os.path.split(sys.argv[0])
specialcase = (base == 'python-config')
if specialcase:
    pat = "python*-config"
else:
    pat = base + '*'
g = glob.glob(os.path.join(dir, pat))
# match a single digit, dot and possibly multiple digits, because we might
# have 2to32.6, where the program is 2to3 and the version is 2.6.
vpat = re.compile("\d\.\d+")
n = 0
for i in g:
    vers = vpat.search(i)
    if vers is None:
	continue
    sys.stderr.write("%s (uses python %s)\n" % (i, i[vers.start():vers.end()]))
    n = 1
if n == 0:
    sys.stderr.write("(Error: no alternatives found)\n")

sys.stderr.write(partB)
sys.exit(1)
