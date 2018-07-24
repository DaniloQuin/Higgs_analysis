#!/usr/bin/env python
import sys
import time
from ROOT import *

luminosity = 3000


if __name__ == '__main__':

	file = TFile(sys.argv[1])
	entries = file.finalSelection.GetEntriesFast()
	tree_res = file.finalSelection.GetEntry(0)
	suma1 = 0
	suma2 = 0
	print(entries)

	# setup toolbar
	toolbar_width = 100
	sys.stdout.write("[%s]" % (" " * toolbar_width))
	sys.stdout.flush()
	sys.stdout.write("\b" * (toolbar_width+1)) # return to start of line, after '['
	temp = entries/toolbar_width
	# end setup toolbar

	for event in xrange(entries):
		tree_res = file.finalSelection.GetEntry(event)
		if event%temp ==0:		
			sys.stdout.write("-")
			sys.stdout.flush()
		suma2 += file.finalSelection.totalWeight

	sys.stdout.write("\n")
	print("----------------------------------------------------------------------")
	print("|  {} | {} |".format(suma2,suma1))
	print("----------------------------------------------------------------------")		

"""
----------------------------------------------------------------------
               original |   nathan       | nathan with finalstate
----------------------------------------------------------------------
Signal Hbbyy :10.63975. 
----------------------------------------------------------------------

sgn_yybb_Tree.root 					|  160178 |. |  160178 |
bkg_bbh.           					|  1053 |.   |  1053 |
diHiggs_nathan_bkg_ttH_Tree.root.   |  1519972 | |  2994911 |
diHiggs_nathan_bkg_ybbj_Tree.root.  |  171566 |. |  275653 |
diHiggs_nathan_bkg_yccj_Tree.root   |  139820 |	 |  275917 |
diHiggs_nathan_bkg_yybb_Tree.root   |  38952 |
diHiggs_nathan_bkg_yycc_Tree.root   |  117919 |
diHiggs_nathan_bkg_yyjj_Tree.root   |  306434 |
diHiggs_nathan_bkg_yyZbb_Tree.root  |  1742 |
diHiggs_nathan_bkg_ZH_Tree.root 	|  9622 |










"""


