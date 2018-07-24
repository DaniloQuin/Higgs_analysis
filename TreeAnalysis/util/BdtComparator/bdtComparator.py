#!/usr/bin/env python
import sys
import os
import time
from ROOT import *

luminosity = 3000


if __name__ == '__main__':
	files = os.listdir(sys.argv[1])
	c1 = TCanvas( 'c1', 'A Simple Graph Example', 200, 10, 700, 500 )
	histogramas = []
	suma = 0
	leg = TLegend(.5,.5,.99,.99)
	for file in files:
		if "BDT.root" in file:
			suma +=1
			histo = TH1D("histo"+file,file,40,0,0.2)
			leg.AddEntry(histo,file,"l")
			print(file)
			file = TFile(sys.argv[1]+file)
			entries = file.diHiggs.GetEntriesFast()
			tree_res = file.diHiggs.GetEntry(0)
			
			# setup toolbar
			toolbar_width = 100
			sys.stdout.write("[%s]" % (" " * toolbar_width))
			sys.stdout.flush()
			sys.stdout.write("\b" * (toolbar_width+1)) # return to start of line, after '['
			temp = entries/toolbar_width
			#end setup toolbar
			
			for event in xrange(entries):
				tree_res = file.diHiggs.GetEntry(event)
				histo.Fill(file.diHiggs.BDT_response,file.diHiggs.scaledWeight3000fb)
				if event%temp ==0:
					sys.stdout.write("-")
					sys.stdout.flush()
				# if file.finalSelection.passAllCuts == True:
				# 	#suma1 += file.finalSelection.finalStateWeight*file.crossSection.xsec*luminosity/file.cutflow.All #file.finalSelection.finalStateWeight*
				# 	suma1 += file.finalSelection.scaledWeight3000fb
				# suma2 += file.finalSelection.scaledWeight3000fb

			sys.stdout.write("\n")
			histogramas.append(histo)

			
	leg.SetBorderSize(0)
	leg.SetFillColor(0)
	leg.SetFillStyle(0)
	leg.SetTextFont(42)
	leg.SetTextSize(0.035)
	

	histogramas[1].Draw("EHIST")
	histogramas[1].SetLineColor(1)
	histogramas[0].Draw("EHIST same")
	histogramas[0].SetLineColor(1)
	for i in xrange(2,len(histogramas)):
		histogramas[i].Draw("same EHIST")
		if i == 9 :
			histogramas[i].SetLineColor(i+9)
		else: histogramas[i].SetLineColor(i+1)
	leg.Draw()
	input("enter para salir")




