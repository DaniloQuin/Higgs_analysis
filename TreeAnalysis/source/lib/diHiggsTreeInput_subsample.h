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

class diHiggsTreeInput_subsample {

public:
  
  diHiggsTreeInput_subsample(Option Sample);
  ~diHiggsTreeInput_subsample();
  void addBranches(std::string name);
  void initialize(bool nathan);
  void finalize();
  void execute();

private:

  bool nathan_analysis;
  Option option_;
  float prob;
  int n_events_;
  TFile *output;
  TTree *tree_out;
  TFile *input;
  TTree *tree_in;
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
  Double_t bb_cosTSBranch,yy_cosTSBranch,bbyy_cosTSBranch,bbyy_m,bbyy_pt;;
  
  Double_t finalStateWeight, totalWeight,scaledWeight3000fb;

  // Number of events
  int n_events;
  int accepted_events;
  

  // Tree files folder
  TString outputFolder = "/data1/Higgs/diHiggs/samples/MichaSamples/samples/";
};

#endif
