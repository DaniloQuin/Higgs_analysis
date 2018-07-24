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

// Boost include(s):
#include <boost/program_options.hpp>
#include <boost/progress.hpp>

// TMVA include(s):
#include <TMVA/Reader.h>
#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"
#include "TMVA/TMVAGui.h"

class diHiggsTMVAClassification {

public:
  
  diHiggsTMVAClassification(bool nathan);
  ~diHiggsTMVAClassification();
  void addMethod(bool fast,std::string name,std::string tree,std::string depth,std::string minnodesize,int var_cut);
  //  void initialize();
  void execute();

private:

  Option option_;
  int n_events_;
  bool nathan_analysis;

  TFile *input_sgn;
  TFile *input_bkg_bbyy;
  TFile *input_bkg_bbyj;
  TFile *input_bkg_ccyy;
  TFile *input_bkg_jjyy;

  TFile *input_nathan_sgn_yybb;
  TFile *input_nathan_bkg_ybbj;
  TFile *input_nathan_bkg_yccj;
  TFile *input_nathan_bkg_yybb;
  TFile *input_nathan_bkg_yycc;
  TFile *input_nathan_bkg_yyjj;
  TFile *input_nathan_bkg_yyZbb;
  TFile *input_nathan_bkg_bbH;
  TFile *input_nathan_bkg_ttH;
  TFile *input_nathan_bkg_ZH;
  TFile *input_nathan_bkg_tt;
  TFile *input_nathan_bkg_bbjj;
  TFile *input_nathan_bkg_ggh;

  TFile *outputFile;

  TTree *signalTree;
  TTree *bkgTree_bbyy;
  TTree *bkgTree_bbyj;
  TTree *bkgTree_ccyy;
  TTree *bkgTree_jjyy;

  TTree *nathan_signalTree_yybb;
  TTree *nathan_bkgTree_ybbj;
  TTree *nathan_bkgTree_yccj;
  TTree *nathan_bkgTree_yybb;
  TTree *nathan_bkgTree_yycc;
  TTree *nathan_bkgTree_yyjj;
  TTree *nathan_bkgTree_yyZbb;
  TTree *nathan_bkgTree_bbH;
  TTree *nathan_bkgTree_ttH;
  TTree *nathan_bkgTree_ZH;
  TTree *nathan_bkgTree_tt;
  TTree *nathan_bkgTree_bbjj;
  TTree *nathan_bkgTree_ggh;

// Tree files folder

  TString fileFolder = "/data1/Higgs/diHiggs/samples/MichaSamples/samples/";
  TString filesFolder = "/data1/Higgs/diHiggs/samples/MichaSamples/samples/";
  TString inputFolder = "/data1/Higgs/diHiggs/samples/MichaSamples/samples/";

  TString fname_sgn_yybb ;
  TString fname_bkg_ybbj ;
  TString fname_bkg_yccj ;
  TString fname_bkg_yybb ;
  TString fname_bkg_yycc ;
  TString fname_bkg_yyjj ;
  TString fname_bkg_yyZbb;
  TString fname_bkg_bbH ;
  TString fname_bkg_ttH ;
  TString fname_bkg_ZH ;
  TString fname_bkg_tt ;
  TString fname_bkg_bbjj ;
  TString fname_bkg_ggh ;

  TString fname_sig ;
  TString fname_bkg_bbyy;
  TString fname_bkg_bbyj;
  TString fname_bkg_ccyy;
  TString fname_bkg_jjyy;  

  // TMVA input variables
  Float_t dijets_mass, dijets_DeltaR, dijets_Pt, diphotons_mass, diphotons_DeltaR;
  Float_t diphotons_Pt, diphotons_pTt, leading_photon_Et, subleading_photon_Et;
  Float_t leading_jet_Et, subleading_jet_Et, photonpt1frac, photonpt2frac;
  Float_t diphoton_diBjets_mass, diphoton_diBjets_Pt;
  Float_t nb_jets, nb_muons, nb_electrons, nb_photons, nb_trigger_photons, nb_photons_overhighpT, nb_bjets, nb_bjets_overhighpT;
  Float_t diphotons_1b_DeltaR, diphotons_2b_DeltaR, diphotons_3b_DeltaR, diphotons_4b_DeltaR;

  Double_t b1_m, b1_pt, b1_eta, b1_phi, b2_m, b2_pt, b2_eta, b2_phi;
  Double_t y1_pt, y1_eta, y1_phi, y2_pt, y2_eta, y2_phi;
  Int_t b1_source, b2_source;
  Int_t y1_source, y2_source;
  Double_t bb_m, bb_pt, bb_eta, bb_phi, bb_dr, yy_m, yy_pt, yy_eta, yy_phi, yy_dr;
  
  Double_t finalStateWeight, totalWeight;
  
  // // TMVA output variables
  // Float_t dijetsMass, dijetsDeltaR, dijetsPt, diphotonsMass, diphotonsDeltaR;
  // Float_t diphotonsPt, diphotonspTt, leading_photonEt, subleading_photonEt;
  // Float_t leading_jetEt, subleading_jetEt, photonpT1frac, photonpT2frac;
  // Float_t diphoton_diBjetsMass, diphoton_diBjetsPt;
  // Int_t Njets, Nmuons, Nelectrons, Nphotons, Ntrigger_photons, Nphotons_overhighpT, Nbjets, Nbjets_overhighpT;
  // Float_t diphotons1b_DeltaR, diphotons2b_DeltaR, diphotons3b_DeltaR, diphotons4b_DeltaR;
  // // MVA Discriminator
  // Float_t BDT_response;

  Float_t weight_finalState, weight_perEvent;

};

#endif
