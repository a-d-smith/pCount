import sys
from ROOT import gSystem
gSystem.Load("libpCount_pCountPack")
from ROOT import sample

try:

    print "PyROOT recognized your class %s" % str(sample)

except NameError:

    print "Failed importing pCountPack..."

sys.exit(0)

