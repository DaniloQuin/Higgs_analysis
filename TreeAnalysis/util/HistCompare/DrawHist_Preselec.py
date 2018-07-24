import ROOT 
ROOT.gROOT.SetBatch(True)

stylepath = '/home/saolivap/WorkArea/GitLab/diHiggsbbyyAnalysis/TreeAnalysis/util/HistCompare/AtlasStyle/'

ROOT.gROOT.LoadMacro( stylepath + "AtlasStyle.C")
ROOT.gROOT.LoadMacro( stylepath + "AtlasLabels.C")
ROOT.gROOT.LoadMacro( stylepath + "AtlasUtils.C")
ROOT.SetAtlasStyle()
from ROOT import gPad

#Flags
doLogX = False
doLogY = False

basepath = '/home/saolivap/WorkArea/GitLab/diHiggsbbyyAnalysis/samples/'
tree = 'diHiggs'
hists = ["dijets_mass", "dijets_DeltaR", "dijets_Pt", "nb_jets", "diphotons_mass", "diphotons_DeltaR", "diphotons_Pt", "diphotons_pTt", "leading_photon_Et", "subleading_photon_Et", "leading_jet_Et", "subleading_jet_Et", "nb_electrons", "nb_muons", "photonpt1frac", "photonpt2frac", "diphoton_diBjets_mass", "diphoton_diBjets_Pt"]

samples = {
    'sgn': [basepath + 'diHiggs_sgn_Hbbyy_Tree.root'],
    'bkg': [basepath + 'diHiggs_bkg_bbyy_Tree.root'],
    'bkg_ybbj': [basepath + 'diHiggs_bkg_bbyj_Tree.root'],
    'bkg_yycc': [basepath + 'diHiggs_bkg_ccyy_Tree.root'],
    'bkg_yyjj': [basepath + 'diHiggs_bkg_jjyy_Tree.root'],
}

outfile = ROOT.TFile('/home/saolivap/WorkArea/GitLab/diHiggsbbyyAnalysis/TreeAnalysis/util/HistCompare/plots/hists.root','RECREATE')

# CREATING HISTOGRAMS
h = {}
for sample in samples.keys():
    h[sample] = {}

    for hist in hists:
        h[sample][hist] = {}

        n = 'h_%s_%s' % (sample, hist)

        if hist == 'dijets_DeltaR' or hist == 'diphotons_DeltaR' or hist == 'photonpt1frac' or hist == 'photonpt2frac':
            h[sample][hist] = ROOT.TH1F(n, n + "; %s_%s [GeV]" % (hist, sample), 10000, 0, 1000)
        elif hist == 'diphotons_mass':
            h[sample][hist] = ROOT.TH1F(n, n + "; %s_%s [GeV]" % (hist, sample), 2000, 0, 1000)
        elif hist == 'nb_jets' or hist == 'nb_electrons' or hist == 'nb_muons':
            h[sample][hist] = ROOT.TH1F(n, n + "; %s_%s [GeV]" % (hist, sample), 1000, 0, 1000)
        else:
            h[sample][hist] = ROOT.TH1F(n, n + "; %s_%s [GeV]" % (hist, sample), 100, 0, 1000)

        h[sample][hist].SetDirectory(outfile)
    
# FILLING
for hist in hists:
    print 'processing histogram: %s' % hist

    for sample in samples.keys():
        print 'processing sample: %s' % sample
        l = samples[sample]

        for fname in l:
            print '            > %s' % fname
            f = ROOT.TFile.Open(fname)
            t = f.Get(tree)

            if hist == 'dijets_DeltaR' or hist == 'diphotons_DeltaR' or hist == 'photonpt1frac' or hist == 'photonpt2frac':
                n = 'htmp(10000,0,1000)'
            elif hist == 'diphotons_mass':
                n = 'htmp(2000,0,1000)'
            elif hist == 'nb_jets' or hist == 'nb_electrons' or hist == 'nb_muons':
                n = 'htmp(1000,0,1000)'
            else:
                n = 'htmp(100,0,1000)'

            if t.Draw('%s>>%s' % (hist, n),
                      'weight_perEvent*weight_finalState', 
                      'goff'
            ):
                h[sample][hist].Add(ROOT.gDirectory.Get('htmp'), 1.)
                
del f

# NORMALIZE & CONFIG
for sample in samples:
    for hist in hists:

        # Histogram normalization
        norm = 1;
        scale = norm/h[sample][hist].Integral()
        h[sample][hist].Scale(scale)

        # Line width
        h[sample][hist].SetLineWidth(4)

# PLOTTING
for hist in hists:

    # Style and colour
    h['sgn'][hist].SetLineColor(ROOT.kRed)
    h['sgn'][hist].SetLineStyle(1)    
    h['bkg'][hist].SetLineColor(ROOT.kGreen)
    h['bkg'][hist].SetLineStyle(2)
    h['bkg_ybbj'][hist].SetLineColor(ROOT.kBlue)
    h['bkg_ybbj'][hist].SetLineStyle(3)
    h['bkg_yycc'][hist].SetLineColor(ROOT.kMagenta)
    h['bkg_yycc'][hist].SetLineStyle(4)    
    h['bkg_yyjj'][hist].SetLineColor(ROOT.kCyan)
    h['bkg_yyjj'][hist].SetLineStyle(5)

    # Tex in canvas
    tex = ROOT.TLatex(0.52, 0.88, "#sqrt{s} = 14 TeV, < #mu > = 200")
    tex.SetName('tex')
    tex.SetNDC(True)
    tex.SetTextSize(0.04)
    texATLAS = ROOT.TLatex(0.42, 0.2, "#bf{#it{ATLAS}} Work in progress") #was 0.63, 0.12
    texATLAS.SetName('texATLAS')
    texATLAS.SetNDC(True)
    texATLAS.SetTextSize(0.05)

    #legend configuration
    xmin = 0.60
    xmax = 0.75
    ymin = 0.55
    ymax = 0.80
    
    legend = ROOT.TLegend(xmin, ymin, xmax, ymax) 
    legend.SetFillColor(0)
    legend.SetBorderSize(0)
    legend.SetTextFont(42)
    legend.SetTextSize(0.05) 
    legend.SetName('diHiggs')
    legend.SetShadowColor(0)
    
    legend.AddEntry(h['sgn'][hist],'HH #rightarrow bb#gamma#gamma', 'l')
    legend.AddEntry(h['bkg'][hist],'bb#gamma#gamma', 'l')
    legend.AddEntry(h['bkg_ybbj'][hist],'bbj#gamma', 'l')
    legend.AddEntry(h['bkg_yycc'][hist],'cc#gamma#gamma', 'l')
    legend.AddEntry(h['bkg_yyjj'][hist],'jj#gamma#gamma', 'l')

    # THStack
    hs  = ROOT.THStack("hsStack","Histogram Comparison")
    hs.Add(h['sgn'][hist])
    hs.Add(h['bkg'][hist])
    hs.Add(h['bkg_ybbj'][hist])
    hs.Add(h['bkg_yycc'][hist])
    hs.Add(h['bkg_yyjj'][hist])
                    
    c = ROOT.TCanvas('c', 'c', 800, 800)
    if doLogY == True: c.SetLogy()
    if doLogX == True: c.SetLogx()
    
    hs.Draw('nostack, hist')
    hs.GetYaxis().SetTitle('Normalise Events')
    # X-axis title
    if hist == 'dijets_DeltaR':
        hs.GetXaxis().SetTitle('#Delta R(jj)')
    elif hist == 'diphotons_DeltaR':
        hs.GetXaxis().SetTitle('#Delta R(#gamma#gamma)')
    elif hist == 'photonpt1frac':
        hs.GetXaxis().SetTitle('leading photon #frac{p_{T}#gamma}{m_{#gamma#gamma}}')
    elif hist == 'photonpt2frac':
        hs.GetXaxis().SetTitle('sub-leading photon #frac{p_{T}#gamma}{m_{#gamma#gamma}}')
    elif hist == 'nb_jets':
        hs.GetXaxis().SetTitle('Jet multiplicity')
    elif hist == 'nb_electrons':
        hs.GetXaxis().SetTitle('Electron multiplicity')
    elif hist == 'nb_muons':
        hs.GetXaxis().SetTitle('Muon multiplicity')
    elif hist == 'dijets_Pt':
        hs.GetXaxis().SetTitle('p_{T}(jj) [GeV]')
    elif hist == 'diphotons_Pt':
        hs.GetXaxis().SetTitle('p_{T}(#gamma#gamma) [GeV]')
    elif hist == 'diphoton_diBjets_Pt':
        hs.GetXaxis().SetTitle('p_{T}(jj#gamma#gamma) [GeV]')
    elif hist == 'dijets_mass':
        hs.GetXaxis().SetTitle('m_{jj} [GeV]')
    elif hist == 'diphotons_mass':
        hs.GetXaxis().SetTitle('m_{#gamma#gamma} [GeV]')
    elif hist == 'diphoton_diBjets_mass':
        hs.GetXaxis().SetTitle('m_{jj#gamma#gamma} [GeV]')
    elif hist == 'diphoton_pTt':
        hs.GetXaxis().SetTitle('p_{Tt}(#gamma#gamma) [GeV]')
    elif hist == 'leading_jet_Et':
        hs.GetXaxis().SetTitle('leading jet E_{T} [GeV]')
    elif hist == 'subleading_jet_Et':
        hs.GetXaxis().SetTitle('sub-leading jet E_{T} [GeV]')
    elif hist == 'leading_photon_Et':
        hs.GetXaxis().SetTitle('leading photon E_{T} [GeV]')
    elif hist == 'subleading_photon_Et':
        hs.GetXaxis().SetTitle('sub-leading photon E_{T} [GeV]')
    else:
        hs.GetXaxis().SetTitle('default')
    # X-axis range
    if hist == 'dijets_DeltaR' or hist == 'diphotons_DeltaR' or hist == 'photonpt1frac' or hist == 'photonpt2frac':
        hs.GetXaxis().SetRangeUser(0,5)
    elif hist == 'nb_jets' or hist == 'nb_electrons' or hist == 'nb_muons':
        hs.GetXaxis().SetRangeUser(0,10)
    elif hist == 'dijets_Pt' or hist == 'diphotons_Pt' or hist == 'diphoton_diBjets_Pt':
        hs.GetXaxis().SetRangeUser(0,700)
    elif hist == 'dijets_mass':
        hs.GetXaxis().SetRangeUser(0,700)
    elif hist == 'diphotons_mass':
        hs.GetXaxis().SetRangeUser(70,250)
    elif hist == 'diphoton_diBjets_mass':
        hs.GetXaxis().SetRangeUser(0,1000)
    else:
        hs.GetXaxis().SetRangeUser(0,700)

    legend.Draw()
    tex.Draw()
    texATLAS.Draw()
    c.Update()
    c.SaveAs('/home/saolivap/WorkArea/GitLab/diHiggsbbyyAnalysis/TreeAnalysis/util/HistCompare/plots/%s.png' % (hist))


