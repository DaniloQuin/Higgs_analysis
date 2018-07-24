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
		Total_Entries =13260814

	file = TFile(sys.argv[1])
	entries = file.diHiggs.GetEntriesFast()
	tree_res = file.diHiggs.GetEntry(0)
	

	# setup toolbar
	print("The number of events is : " + str(entries))
	toolbar_width = 100
	sys.stdout.write("[%s]" % (" " * toolbar_width))
	sys.stdout.flush()
	sys.stdout.write("\b" * (toolbar_width+1)) # return to start of line, after '['
	temp = entries/toolbar_width
	#end toolbar setup

	if not Nathan_Analisys:
		if tree_res >= 0:
			print("----------------------------------------------------------------------")
			print("               original |   nathan  with finalstate  | nathan|")
			print("----------------------------------------------------------------------")
			print("{} :{}".format(title,file.diHiggs.weight_perEvent*int(entries)/Total_Entries))
			print("----------------------------------------------------------------------")
		else: print("The file is empty")
	else:
		suma2 = 0
		suma1 = 0
		for event in xrange(entries):
			if event%temp ==0:		
				sys.stdout.write("-")
				sys.stdout.flush()
			tree_res = file.diHiggs.GetEntry(event)
			suma1 += file.diHiggs.scaledWeight3000fb

		print("----------------------------------------------------------------------")
		print("|  {} |".format(suma1))
		print("----------------------------------------------------------------------")		

"""
			  		original 		|	 nathan      |
----------------------------------------------------------------------
Signal Hbbyy 	:  25.1614			|  25.2697500677 |
background bbyj :  10928.0212022	|  17184.9525035 |
background bbyy :  10928.6659699	|  11863.3912488 |
background ccyy :  7147.02827904	|  5290.01756554 |
background jjyy :  2374.9691384		|  2448.02572617 |
background bbh  :					|  4.71068900968 |
background tth  : 					|  151.304963538 |
background yccj :					|  5290.01756554 |
background yyZbb:					|  293.047802277 |
background ZH   :					|  33.6011470712 |




"""


