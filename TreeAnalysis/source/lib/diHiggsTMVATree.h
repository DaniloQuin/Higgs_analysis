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

class diHiggsTMVATree {

public:
  
  diHiggsTMVATree(Option option,long num_threads,long thread);
  ~diHiggsTMVATree();
  void addBranches(std::string name,int var_cut);
  void initialize(bool nathan);
  void execute();

private:

  Option option_;
    boost::progress_display * show_progress = NULL;
  
  long n_thread;
  long thread;
  long n_events_;
  bool nathan_analysis ;

  TFile *output;
  TTree *tree_out;
  TFile *input;
  TTree *tree_in;
 
  // File name
  TString fname;
  TString outname;

  // Tree files folder
  TString filesFolder = "/home/mhaacke/gitlab/diHiggsbbyyAnalysis_V2/TreeAnalysis";
  TString inputFolder = "/data1/Higgs/diHiggs/samples/MichaSamples/samples/";
  TString inputFolder_v2 ="/data1/Higgs/diHiggs/samples/MichaSamples/samples/"; 

  // TMVA
  TMVA::Reader *reader;

  //TMVA input nathan variables 
  Float_t b1_m, b1_pt, b1_eta, b1_phi, b2_m, b2_pt, b2_eta, b2_phi;
  Float_t y1_pt, y1_eta, y1_phi, y2_pt, y2_eta, y2_phi;
  Int_t b1_source, b2_source;
  Int_t y1_source, y2_source;
  Float_t bb_m, bb_pt, bb_eta, bb_phi, bb_dr, yy_m, yy_pt, yy_eta, yy_phi, yy_dr;
  Float_t bb_CosTSBranch,yy_CosTSBranch,bbyy_CosTSBranch,bbyy_M,bbyy_Pt;
  Float_t final_stateWeight, total_weight,scaledweight3000fb;

  //TMVA output nathan variables 
  Double_t b1M, b1Pt, b1Eta, b1Phi, b2M, b2Pt, b2Eta, b2Phi;
  Double_t y1Pt, y1Eta, y1Phi, y2Pt, y2Eta, y2Phi;
  Int_t b1Source, b2Source;
  Int_t y1Source, y2Source;
  Double_t bbM, bbPt, bbEta, bbPhi, bbDr, yyM, yyPt, yyEta, yyPhi, yyDr;
   Double_t bb_cosTSBranch,yy_cosTSBranch,bbyy_cosTSBranch,bbyy_m,bbyy_pt;
  
  Double_t finalStateWeight, totalWeight,scaledWeight3000fb;

  // TMVA input variables
  Float_t dijets_mass, dijets_DeltaR, dijets_Pt, diphotons_mass, diphotons_DeltaR;
  Float_t diphotons_Pt, diphotons_pTt, leading_photon_Et, subleading_photon_Et;
  Float_t leading_jet_Et, subleading_jet_Et, photonpt1frac, photonpt2frac;
  Float_t diphoton_diBjets_mass, diphoton_diBjets_Pt;
  Float_t nb_jets, nb_muons, nb_electrons, nb_photons, nb_trigger_photons, nb_photons_overhighpT, nb_bjets, nb_bjets_overhighpT;
  Float_t diphotons_1b_DeltaR, diphotons_2b_DeltaR, diphotons_3b_DeltaR, diphotons_4b_DeltaR;
  
  // TMVA output variables
  Float_t dijetsMass, dijetsDeltaR, dijetsPt, diphotonsMass, diphotonsDeltaR;
  Float_t diphotonsPt, diphotonspTt, leading_photonEt, subleading_photonEt;
  Float_t leading_jetEt, subleading_jetEt, photonpT1frac, photonpT2frac;
  Float_t diphoton_diBjetsMass, diphoton_diBjetsPt;
  Int_t Njets, Nmuons, Nelectrons, Nphotons, Ntrigger_photons, Nphotons_overhighpT, Nbjets, Nbjets_overhighpT;
  Float_t diphotons1b_DeltaR, diphotons2b_DeltaR, diphotons3b_DeltaR, diphotons4b_DeltaR;
  // MVA Discriminator
  Float_t BDT_response;

  Float_t weight_finalState, weight_perEvent;

};

#endif
