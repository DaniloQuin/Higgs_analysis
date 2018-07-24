#!/usr/bin/env python
import sys
import time
from ROOT import *

luminosity = 3000


if __name__ == '__main__':

	file = TFile(sys.argv[1])
	# file.cutflow.GetEntry(0)
	entries = file.diHiggs.GetEntriesFast()
	tree_res = file.diHiggs.GetEntry(0)
	# tree_res1 = file.crossSection.GetEntry(0)
	suma2 = 0
	suma1 = 0
	# cross = file.crossSection.xsec
	# print(cross,entries)
	
	# setup toolbar
	toolbar_width = 100
	sys.stdout.write("[%s]" % (" " * toolbar_width))
	sys.stdout.flush()
	sys.stdout.write("\b" * (toolbar_width+1)) # return to start of line, after '['
	temp = entries/toolbar_width
	#end setup toolbar
	
	for event in xrange(entries):
		tree_res = file.diHiggs.GetEntry(event)
		if not (file.diHiggs.bb_cosTSBranch >0 and file.diHiggs.bb_cosTSBranch<1):
			print(file.diHiggs.bb_cosTSBranch,file.diHiggs.bbyy)
		if event%temp ==0:
			sys.stdout.write("-")
			sys.stdout.flush()
		# if file.finalSelection.passAllCuts == True:
		# 	#suma1 += file.finalSelection.finalStateWeight*file.crossSection.xsec*luminosity/file.cutflow.All #file.finalSelection.finalStateWeight*
		# 	suma1 += file.finalSelection.scaledWeight3000fb
		# suma2 += file.finalSelection.scaledWeight3000fb

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


