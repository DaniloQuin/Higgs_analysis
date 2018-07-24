#!/usr/bin/env python
import sys
from ROOT import *

luminosity = 30000


if __name__ == '__main__':
	# The first argument of the program will be the file to open
	
	Nathan_Analisys = False
	
	if "nathan" in sys.argv[1]:
		Nathan_Analisys = True

	if  "sgn_hbbyy" in sys.argv[1].lower():
		title = "Signal Hbbyy"
		Total_Entries = 600000
	elif "bkg_bbyy" in sys.argv[1].lower():
		title = "background bbyy"
		Total_Entries = 2500000
	elif "bkg_bbyj"  in sys.argv[1].lower():
		title = "background bbyj"
		Total_Entries = 35000000
	elif "bkg_ccyy" in sys.argv[1].lower():
		title = "background ccyy"
		Total_Entries = 3488450
	elif  "bkg_jjyy" in sys.argv[1].lower():
		title = "background jjyy"
		Total_Entries = 13260814

	file = TFile(sys.argv[1])
	entries = file.diHiggs.GetEntriesFast()
	tree_res = file.diHiggs.GetEntry(0)
	toolbar_width = 100

	# setup toolbar
	sys.stdout.write("[%s]" % (" " * toolbar_width))
	sys.stdout.flush()
	sys.stdout.write("\b" * (toolbar_width+1)) # return to start of line, after '['
	temp = entries/toolbar_width
	#  end toolbar setup

	if not Nathan_Analisys:
		if tree_res >= 0:
			print("----------------------------------------------------------------------")
			print("               original |   nathan  with finalstate  | nathan|")
			print("----------------------------------------------------------------------")
			print("{} :{}".format(title,file.diHiggs.weight_perEvent*int(entries)/Total_Entries))
			print("----------------------------------------------------------------------")
		else: print("The file is empty")
	else:
		#suma1 = 141*luminosity*entries/Total_Entries
	#		suma =file.diHiggs.totalWeight/*entries*Total_Entries
		suma2 = 0
		suma1 = 0
		for event in xrange(entries):
			if event%temp ==0:		
				sys.stdout.write("-")
				sys.stdout.flush()
			tree_res = file.diHiggs.GetEntry(event)
			suma1 += file.diHiggs.totalWeight

		print("----------------------------------------------------------------------")
		print("|  {} |".format(suma1))
		print("----------------------------------------------------------------------")		

"""
----------------------------------------------------------------------
               original |   nathan       | nathan with finalstate
----------------------------------------------------------------------
Signal Hbbyy :10.63975. 
----------------------------------------------------------------------

sgn_yybb_Tree.root 					|  160178 |. |  160178 |
diHiggs_nathan_bkg_bbh_Tree.root    |  1053 |.   |  1053 |
diHiggs_nathan_bkg_ttH_Tree.root.   |  1519972 | |  2994911 |
diHiggs_nathan_bkg_ybbj_Tree.root.  |  171566 |. |  275653 |
diHiggs_nathan_bkg_yccj_Tree.root   |  139820 |	 |  275917 |
diHiggs_nathan_bkg_yybb_Tree.root   |  38952 |
diHiggs_nathan_bkg_yycc_Tree.root   |  117919 |
diHiggs_nathan_bkg_yyjj_Tree.root   |  306434 |
diHiggs_nathan_bkg_yyZbb_Tree.root  |  1742 |
diHiggs_nathan_bkg_ZH_Tree.root 	|  9622 |

FIX
----------------------------------------------------------------------
               original |   nathan  with finalstate  | nathan|
----------------------------------------------------------------------
Signal Hbbyy :25.1614
background bbyj :10928.0212022
background bbyy :10928.6659699
background ccyy :7147.02827904
background jjyy :2374.9691384
sgn_yybb_Tree.root 					|  552.614110294 | 146.633474303 |
diHiggs_nathan_bkg_bbh_Tree.root    |  7.96067993977 | 0.00169073970071 |
diHiggs_nathan_bkg_ttH_Tree.root.   |  125786.260402 | 6.19061993851 |
diHiggs_nathan_bkg_ybbj_Tree.root.  |  9036989.60671 | 0.000540749303148 |
diHiggs_nathan_bkg_yccj_Tree.root   |  30610117.6515 | 4.58105847875e-05 |
diHiggs_nathan_bkg_yybb_Tree.root   |  6634.14850026 | 0.516450434738 |
diHiggs_nathan_bkg_yycc_Tree.root   |  114824.895719 | 2.750631939e-05 |
diHiggs_nathan_bkg_yyjj_Tree.root   |  446089.846577 | 0.432275124661 |
diHiggs_nathan_bkg_yyZbb_Tree.root  |  264.864137844 | 0.0041628635488 |
diHiggs_nathan_bkg_ZH_Tree.root 	|  646.598402832 | 1.03781598786e-07 |

----------------------------------------------------------------------







"""


