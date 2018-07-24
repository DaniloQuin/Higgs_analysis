// Dear emacs, this is -*- c++ -*-
#ifndef FULLEXAMPLE_MYLIBRARY_H
#define FULLEXAMPLE_MYLIBRARY_H

// Local include(s):
#include "enums.h"

// ROOT includes(s):
#include "TMath.h"
#include "TTree.h"
#include "TFile.h"
#include "TSystem.h"
#include "TChain.h"

// Boost include(s):
#include <boost/program_options.hpp>
#include <boost/progress.hpp>

// Text include(s):
#include <fstream>

class diHiggsbbyyTreeInput {

public:
  
  diHiggsbbyyTreeInput(Option Sample,long num_threads,long thread);
  ~diHiggsbbyyTreeInput();
  Double_t deltaR(Double_t eta1, Double_t eta2, Double_t phi1, Double_t phi2);
  void addBranches(std::string signal,std::string name);
  void initialize(bool nathan);
  void finalize();
  void execute(int cut);

private:

  long n_thread;
  long thread;

  bool nathan_analysis,multiple_file;
  Option option_;
  long n_events_;
  TFile *output;
  TTree *tree_out;
  TFile *input;
  TTree *tree_in;
  TChain *tree_in_chain;
  boost::progress_display * show_progress = NULL;
 
  // File name
  TString fname;
  TString outname;
  
  // Tree input variables 
  Float_t dijetsMass, dijetsDeltaR, dijetsPt, diphotonsMass, diphotonsDeltaR;
  Float_t diphotons1bDeltaR, diphotons2bDeltaR, diphotons3bDeltaR, diphotons4bDeltaR; 
  Float_t diphotonsPt, diphotonspTt, leading_photonEt, subleading_photonEt;
  Float_t leading_jetEt, subleading_jetEt, photonpt1frac, photonpt2frac;
  Float_t diphoton_diBjetsMass, diphoton_diBjetsPt;
  Int_t   nb_jets, nb_muons, nb_electrons, nb_trigger_photons;
  Int_t   nb_photons, nb_photons_overhighpT, nb_bjets, nb_bjets_overhighpT;
  Float_t weight_finalState, weight_perEvent;

  //Tree input nathan variables 
  Double_t b1M, b1Pt, b1Eta, b1Phi, b2M, b2Pt, b2Eta, b2Phi;
  Double_t y1Pt, y1Eta, y1Phi, y2Pt, y2Eta, y2Phi;
  Int_t b1Source, b2Source;
  Int_t y1Source, y2Source;
  Double_t bbM, bbPt, bbEta, bbPhi, bbDr, yyM, yyPt, yyEta, yyPhi, yyDr;
  Double_t bb_cosTSBranch,yy_cosTSBranch,bbyy_cosTSBranch,bbyy_m,bbyy_pt;
    
  Double_t finalStateWeight, totalWeight,scaledWeight3000fb,temp;

  bool passallcut;

  // Number of events
  long n_events;
  long accepted_events;
  
  // Counters
  double count[19];
  std::ofstream cutFlow;

  // Tree files folder
  TString filesFolder = "/home/mhaacke/Data/ntuples/";
  TString fileFolder = "/data2/Higgs/diHiggs/samples/samplesNathan/";
  TString fileFolder_v2 = "/data2/Higgs/diHiggs/samples/samplesNathan/v2/";
  TString outputFolder = "/data1/Higgs/diHiggs/samples/MichaSamples/samples";

  TString fileFolder_v3 = "/data1/Higgs/diHiggs/samples/NathanSamples/PixelTDR/";
  TString nathan_sgn_yybb_f_v3 = fileFolder_v3 + "MadGraphPythia8EvtGen_A14NNPDF23LO_sm_hh_yybb.merge.DAOD_TRUTH1V3/";
  TString nathan_bkg_ybbj_f_v3 = fileFolder_v3 + "MadGraphPythia8EvtGen_A14NNPDF23LO_ybbj.merge.DAOD_TRUTH3V3/";
  TString nathan_bkg_yccj_f_v3 = fileFolder_v3 + "MadGraphPythia8EvtGen_A14NNPDF23LO_yccj.merge.DAOD_TRUTH3V3/";
  TString nathan_bkg_yybb_f_v3 = fileFolder_v3 + "MadGraphPythia8EvtGen_A14NNPDF23LO_yybb.merge.DAOD_TRUTH3V3/";
  TString nathan_bkg_yycc_f_v3 = fileFolder_v3 + "MadGraphPythia8EvtGen_A14NNPDF23LO_yycc.merge.DAOD_TRUTH3V3/";
  TString nathan_bkg_yyjj_f_v3 = fileFolder_v3 + "MadGraphPythia8EvtGen_A14NNPDF23LO_yyjj.merge.DAOD_TRUTH3V3/";
  TString nathan_bkg_yyZbb_f_v3 = fileFolder_v3 + "MadGraphPythia8EvtGen_A14NNPDF23LO_yyZbb.merge.DAOD_TRUTH3V3/";
  TString nathan_bkg_bbH_f_v3 = fileFolder_v3 + "Pythia8EvtGen_A14NNPDF23LO_bbH125_gamgam.merge.DAOD_TRUTH3V3/";
  TString nathan_bkg_ttH_f_v3 = fileFolder_v3 + "Pythia8EvtGen_A14NNPDF23LO_ttH125_gamgam.merge.DAOD_TRUTH3V3/";
  TString nathan_bkg_ZH_f_v3 = fileFolder_v3 + "Pythia8EvtGen_A14NNPDF23LO_ZH125_gamgam.merge.DAOD_TRUTH3V3/";
  TString nathan_bkg_tt_f_v3 = "/data2/Higgs/diHiggs/samples/samplesNathan/PixelTDR/PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.DAOD_TRUTH3V3/";
  TString nathan_bkg_bbjj_f_v3 = fileFolder_v3 + "MadGraphPythia8EvtGen_A14NNPDF23LO_bbjj_plus0jet.merge.DAOD_TRUTH3V3/";
  TString nathan_bkg_ggh_f_v3 = fileFolder_v3 + "PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_ggH125_gamgam.merge.DAOD_TRUTH3V3/";
  TString nathan_bkg_tty_f_v3 = "/data2/Higgs/diHiggs/samples/samplesNathan/PixelTDR/MadGraphPythia8_AU2CTEQ6L1_ttgamma.merge.DAOD_TRUTH3V3/";


  // Selection cuts
  int nb_trigger_photons_min = 2;
  int nb_photons_min = 2;
  int nb_photons_max = 99999;
  int nb_photons_overhighpT_min = 1;
  int nb_jets_min = 2;
  int nb_jets_max = 6;
  int nb_bjets_min = 2;
  int nb_bjets_max = 99999;
  int nb_bjets_overhighpT_min = 1;
  int nb_electrons_max = 0;
  int nb_muons_max = 0;
  double m_dR_Hbb_min           = 0.4;
  double m_dR_Hbb_max           = 2.0;
  double m_dR_Hyy_min           = 0.4;
  double m_dR_Hyy_max           = 2.0;
  double m_dR_H_yb_min          = 0.4;
  double m_dR_H_leadings_yb_min = 0.;
  double m_mHyy_min             = 122.; // default: 123. 
  double m_mHyy_max             = 128.; // default: 127.   
  double m_mHyy_large_min       = 120.;
  double m_mHyy_large_max       = 130.;    
  double m_mHbb_min             = 100.; // default: 95.
  double m_mHbb_max             = 150.; // default: 135.
  double m_H_pt_cut             = 80.;
  
};

#endif
