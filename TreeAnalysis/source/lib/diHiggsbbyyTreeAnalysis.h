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

// Text include(s):
#include <fstream>

class diHiggsbbyyTreeAnalysis {

public:
  
  diHiggsbbyyTreeAnalysis(Option option);
  ~diHiggsbbyyTreeAnalysis();
  Double_t deltaR(Double_t eta1, Double_t eta2, Double_t phi1, Double_t phi2);
  void addBranches(std::string name);
  void initialize(bool nathan,float bd,std::vector<float> *vect);
  void finalize();
  void execute();

private:

  Option option_;
  int n_events_;
  bool nathan_analysis ;
  TFile *output;
  TTree *tree_out;
  TFile *input;
  TTree *tree_in;
  float BDT_CUT;
  int thread;
 
  // model parameters
  Double_t dijets_mass_out; 
  Double_t dijets_mass_in;

  // File name
  TString fname;
  TString outname;

  // Tree files folder
  TString inputFolder = "/data1/Higgs/diHiggs/samples/MichaSamples/samples/";
  TString inputFolder_v2 = "/data1/Higgs/diHiggs/samples/MichaSamples/samples/"; 
  
   // Tree input variables
  Float_t dijetsMass, dijetsDeltaR, dijetsPt, diphotonsMass, diphotonsDeltaR;
  Float_t diphotonsPt, diphotonspTt, leading_photonEt, subleading_photonEt;
  Float_t leading_jetEt, subleading_jetEt, photonpT1frac, photonpT2frac;
  Float_t diphoton_diBjetsMass, diphoton_diBjetsPt;
  Int_t Njets, Nmuons, Nelectrons, Nphotons, Ntrigger_photons, Nphotons_overhighpT, Nbjets, Nbjets_overhighpT;
  Float_t diphotons1b_DeltaR, diphotons2b_DeltaR, diphotons3b_DeltaR, diphotons4b_DeltaR;

  //Tree input nathan variables 
  Double_t b1M, b1Pt, b1Eta, b1Phi, b2M, b2Pt, b2Eta, b2Phi;
  Double_t y1Pt, y1Eta, y1Phi, y2Pt, y2Eta, y2Phi;
  Int_t b1Source, b2Source;
  Int_t y1Source, y2Source;
  Double_t bbM, bbPt, bbEta, bbPhi, bbDr, yyM, yyPt, yyEta, yyPhi, yyDr;
  
  Double_t finalStateWeight, totalWeight,    scaledWeight3000fb ;

  // MVA Discriminator
  Float_t BDT_response;

  // Number of events   
  long n_events;
  int accepted_events;
  float weight_perEvent;
  float weight_finalState;

  // Counters
  std::vector<float> *count;
  std::ofstream cutFlow;

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
  double m_mHyy_min             = 122.;
  double m_mHyy_max             = 128.;
  double m_mHyy_large_min       = 120.;
  double m_mHyy_large_max       = 130.;
  double m_mHbb_min             = 100.;
  double m_mHbb_max             = 150.; 
  double m_H_pt_cut             = 150.;
  
};

#endif
