// System include(s):
#include <iostream>
#include <iomanip>
#include "string"

// Local include(s):
#include "diHiggsbbyyTreeAnalysis.h"

static const bool v2 = true;

diHiggsbbyyTreeAnalysis::diHiggsbbyyTreeAnalysis(Option option)
{
  std::cout << std::endl;
  std::cout << "--- diHiggsbbyyTreeAnalysis :: Generating model option " << option;

  if ( option_ == sgn_higgs ) std::cout << ": H->bbyy signal sample" <<std::endl;
  if ( option_ == bkg_bbyy )  std::cout << ": bbyy background sample" <<std::endl;
  if ( option_ == bkg_bbyj )  std::cout << ": bbyj background sample" <<std::endl;
  if ( option_ == bkg_ccyy )  std::cout << ": ccyy background sample" <<std::endl;
  if ( option_ == bkg_jjyy )  std::cout << ": jjyy background sample" <<std::endl;

  if ( option_ == nathan_sgn_yybb )  std::cout << ": H->bbyy signal sample" << std::endl;
  if ( option_ == nathan_bkg_ybbj )  std::cout << ": nathan background sample" << std::endl;
  if ( option_ == nathan_bkg_yccj )  std::cout << ": nathan background sample" << std::endl;
  if ( option_ == nathan_bkg_yybb )  std::cout << ": nathan background sample" << std::endl;
  if ( option_ == nathan_bkg_yycc )  std::cout << ": nathan background sample" << std::endl;
  if ( option_ == nathan_bkg_yyjj )  std::cout << ": nathan background sample" << std::endl;
  if ( option_ == nathan_bkg_yyZbb ) std::cout << ": nathan background sample" << std::endl;
  if ( option_ == nathan_bkg_bbH )   std::cout << ": nathan background sample" << std::endl;
  if ( option_ == nathan_bkg_ttH )   std::cout << ": nathan background sample" << std::endl;
  if ( option_ == nathan_bkg_ZH )    std::cout << ": nathan background sample" << std::endl;
  
  option_ = option;
}


diHiggsbbyyTreeAnalysis::~diHiggsbbyyTreeAnalysis()
{
  delete tree_in;
  delete input;
  //delete tree_out;
  //delete output;

}

Double_t diHiggsbbyyTreeAnalysis::deltaR(Double_t eta1, Double_t eta2, Double_t phi1, Double_t phi2)
{
  Double_t deta = eta1 - eta2;
  Double_t dphi = phi1 - phi2;
  return TMath::Sqrt(deta*deta + dphi*dphi);
}
 
void diHiggsbbyyTreeAnalysis::initialize(bool nathan,float bd,std::vector<float> *vect)
{
  BDT_CUT = bd ;
  nathan_analysis = nathan;
  count = vect;
  count->resize(12);

  for (int i = 0; i < 12; ++i){
    (*count)[i] = 0;
  }

  b1M = 0; 
  b1Pt = 0;
  b1Eta = 0;
  b1Phi = 0;
  b1Source = 0;
  b2M = 0;
  b2Pt = 0;
  b2Eta = 0;
  b2Phi = 0;
  b2Source = 0;
  y1Pt = 0;
  y1Eta = 0;
  y1Phi = 0;
  y1Source = 0;
  y2Pt = 0;
  y2Eta = 0;
  y2Phi = 0;
  y2Source = 0;
  bbM = 0;
  bbPt = 0;
  bbEta = 0;
  bbPhi = 0;
  bbDr = 0;
  yyM = 0;
  yyPt = 0;
  yyEta = 0;
  yyPhi = 0;
  yyDr = 0;
  finalStateWeight = 0; 
  totalWeight = 0;
  scaledWeight3000fb = 0;
  BDT_response = -99999;
  // Tree events (without rerun)                                                                                                 
  n_events = 0;
  // Events after cuts (with rerun)                                                                                              
  accepted_events = 0;

  // text files
  TString temp = "nathan_cutFlow_final.dat";
  cutFlow.open(temp );
  
}

void diHiggsbbyyTreeAnalysis::addBranches(std::string name)
{
  //output name
  if ( option_ == nathan_sgn_yybb ) outname =  "diHiggs_nathan_sgn_yybb_Final.root"; 
  if ( option_ == nathan_bkg_ybbj ) outname =  "diHiggs_nathan_bkg_ybbj_Final.root"; 
  if ( option_ == nathan_bkg_yccj ) outname =  "diHiggs_nathan_bkg_yccj_Final.root"; 
  if ( option_ == nathan_bkg_yybb ) outname =  "diHiggs_nathan_bkg_yybb_Final.root"; 
  if ( option_ == nathan_bkg_yycc ) outname =  "diHiggs_nathan_bkg_yycc_Final.root"; 
  if ( option_ == nathan_bkg_yyjj ) outname =  "diHiggs_nathan_bkg_yyjj_Final.root"; 
  if ( option_ == nathan_bkg_yyZbb ) outname = "diHiggs_nathan_bkg_yyZbb_Final.root";
  if ( option_ == nathan_bkg_bbH ) outname =   "diHiggs_nathan_bkg_bbH_Final.root";  
  if ( option_ == nathan_bkg_ttH ) outname =   "diHiggs_nathan_bkg_ttH_Final.root";  
  if ( option_ == nathan_bkg_ZH ) outname =    "diHiggs_nathan_bkg_ZH_Final.root"; 
  if ( option_ == nathan_bkg_tt ) outname =    "diHiggs_nathan_bkg_tt_Final.root"; 
  if ( option_ == nathan_bkg_bbjj ) outname =    "diHiggs_nathan_bkg_bbjj_Final.root"; 
  if ( option_ == nathan_bkg_ggh ) outname =    "diHiggs_nathan_bkg_ggh_Final.root"; 
  
  //input name
  if ( option_ == nathan_sgn_yybb )  fname = name + "diHiggs_nathan_sgn_yybb_BDT.root"; 
  if ( option_ == nathan_bkg_ybbj )  fname = name + "diHiggs_nathan_bkg_ybbj_BDT.root"; 
  if ( option_ == nathan_bkg_yccj )  fname = name + "diHiggs_nathan_bkg_yccj_BDT.root"; 
  if ( option_ == nathan_bkg_yybb )  fname = name + "diHiggs_nathan_bkg_yybb_BDT.root"; 
  if ( option_ == nathan_bkg_yycc )  fname = name + "diHiggs_nathan_bkg_yycc_BDT.root"; 
  if ( option_ == nathan_bkg_yyjj )  fname = name + "diHiggs_nathan_bkg_yyjj_BDT.root"; 
  if ( option_ == nathan_bkg_yyZbb ) fname = name + "diHiggs_nathan_bkg_yyZbb_BDT.root";
  if ( option_ == nathan_bkg_bbH )   fname = name + "diHiggs_nathan_bkg_bbH_BDT.root";  
  if ( option_ == nathan_bkg_ttH )   fname = name + "diHiggs_nathan_bkg_ttH_BDT.root";  
  if ( option_ == nathan_bkg_ZH )    fname = name + "diHiggs_nathan_bkg_ZH_BDT.root"; 
  if ( option_ == nathan_bkg_tt )    fname = name + "diHiggs_nathan_bkg_tt_BDT.root"; 
  if ( option_ == nathan_bkg_bbjj )    fname = name + "diHiggs_nathan_bkg_bbjj_BDT.root"; 
  if ( option_ == nathan_bkg_ggh )    fname = name + "diHiggs_nathan_bkg_ggh_BDT.root"; 
  if ( option_ == nathan_bkg_tty )    fname = name + "diHiggs_nathan_bkg_tty_BDT.root"; 
  
  // check if file in local directory exists
  if (!gSystem->AccessPathName(fname )) {
    input = TFile::Open(  fname ); 
  }
  if (!input) {
    std::cout << "ERROR: could not open data file" << std::endl;
    exit(1);
  } 

  std::cout << "--- Using input file: " << input->GetName() << std::endl;

  if ( option_ == nathan_sgn_yybb )  std::cout << ": Select H->bbyy signal sample" << std::endl;
  if ( option_ == nathan_bkg_ybbj )  std::cout << ": Select nathan background sample" << std::endl;
  if ( option_ == nathan_bkg_yccj )  std::cout << ": Select nathan background sample" << std::endl;
  if ( option_ == nathan_bkg_yybb )  std::cout << ": Select nathan background sample" << std::endl;
  if ( option_ == nathan_bkg_yycc )  std::cout << ": Select nathan background sample" << std::endl;
  if ( option_ == nathan_bkg_yyjj )  std::cout << ": Select nathan background sample" << std::endl;
  if ( option_ == nathan_bkg_yyZbb ) std::cout << ": Select nathan background sample" << std::endl;
  if ( option_ == nathan_bkg_bbH )   std::cout << ": Select nathan background sample" << std::endl;
  if ( option_ == nathan_bkg_ttH )   std::cout << ": Select nathan background sample" << std::endl;
  if ( option_ == nathan_bkg_ZH )    std::cout << ": Select nathan background sample" << std::endl;
  
  TString temporal = TString("diHiggs") + std::to_string(option_);
  tree_in = (TTree*)input->Get(temporal);
  //tree_in->SetBranchStatus("*",0);
  tree_in->SetBranchAddress("b1_m",&b1M);
  tree_in->SetBranchAddress("b1_pt",&b1Pt);
  tree_in->SetBranchAddress("b1_eta",&b1Eta);
  tree_in->SetBranchAddress("b1_phi",&b1Phi);
  tree_in->SetBranchAddress("b1_source",&b1Source);
  tree_in->SetBranchAddress("b2_m",&b2M);
  tree_in->SetBranchAddress("b2_pt",&b2Pt);
  tree_in->SetBranchAddress("b2_eta",&b2Eta);
  tree_in->SetBranchAddress("b2_phi",&b2Phi);
  tree_in->SetBranchAddress("b2_source",&b2Source);
  tree_in->SetBranchAddress("y1_pt",&y1Pt);
  tree_in->SetBranchAddress("y1_eta",&y1Eta);
  tree_in->SetBranchAddress("y1_phi",&y1Phi);
  tree_in->SetBranchAddress("y1_source",&y1Source);
  tree_in->SetBranchAddress("y2_pt",&y2Pt);
  tree_in->SetBranchAddress("y2_eta",&y2Eta);
  tree_in->SetBranchAddress("y2_phi",&y2Phi);
  tree_in->SetBranchAddress("y2_source",&y2Source);
  tree_in->SetBranchAddress("bb_m",&bbM);
  tree_in->SetBranchAddress("bb_pt",&bbPt);
  tree_in->SetBranchAddress("bb_eta",&bbEta);
  tree_in->SetBranchAddress("bb_phi",&bbPhi);
  tree_in->SetBranchAddress("bb_dr",&bbDr);
  tree_in->SetBranchAddress("yy_m",&yyM);
  tree_in->SetBranchAddress("yy_pt",&yyPt);
  tree_in->SetBranchAddress("yy_eta",&yyEta);
  tree_in->SetBranchAddress("yy_phi",&yyPhi);
  tree_in->SetBranchAddress("yy_dr",&yyDr);
  tree_in->SetBranchStatus("finalStateWeight",1);
  tree_in->SetBranchAddress("finalStateWeight",&finalStateWeight);
  tree_in->SetBranchStatus("scaledWeight3000fb",1);
  tree_in->SetBranchAddress("scaledWeight3000fb",&scaledWeight3000fb);
  tree_in->SetBranchStatus("BDT_response",1);
  tree_in->SetBranchAddress("BDT_response",&BDT_response);
  
}

 void diHiggsbbyyTreeAnalysis::finalize()
{
    // counter
  std::cout << "--- Yields" <<std::endl;
  std::cout << std::endl;
  std::cout << "Variables : " << " " <<  (*count)[0]<<"\n";
  const int ncounters = 9;
  for (int icount=0; icount<ncounters; icount++) 
  {
    TString Name = "Events after ";
    if (icount==0) Name +=  "no cuts                ";
    if (icount==1) Name +=  "angular selection      ";
    if (icount==2) Name +=  "min Myy                ";
    if (icount==3) Name +=  "max Myy                ";
    if (icount==4) Name +=  "min Mbb                ";
    if (icount==5) Name +=  "max Mbb                ";
    if (icount==6) Name +=  "min yy pT              ";
    if (icount==7) Name +=  "min bb pT              ";
    if (icount==8) Name +=  "BDT response           ";

    std::cout<< Name + ": "<<  (*count)[icount] <<std::endl;
    
    // CutFlow
    cutFlow << icount << " " <<  (*count)[icount] <<std::endl;
  }
  cutFlow.close();

  std::cout << std::endl;

  //  std::cout<<" Total number of accepted events: "<< accepted_events <<std::endl;
  //  std::cout<<" Total number of events at 3000 fb^-1: "<< weight_perEvent*(double)accepted_events/(double)n_events <<std::endl;
  
  // Write and close output file
  // output->Write();
  // output->Close();

  // finalize
  std::cout << "--- Finalize. " <<std::endl;
    
    
}

void diHiggsbbyyTreeAnalysis::execute()
{

  n_events_ = tree_in->GetEntries(); 
  std::cout << "--- Processing: " << n_events_ << " events" << std::endl;
  boost::progress_display show_progress( n_events_ );
  for (Long64_t ievt=0; ievt < n_events_ ;ievt++) 
  {
    ++show_progress;
    tree_in->GetEntry(ievt);
    // No cuts
     (*count)[0]+=1*scaledWeight3000fb;
    if( BDT_response < BDT_CUT) continue;
      (*count)[8]+=1*scaledWeight3000fb;

    // Angular selection (DeltaR)
    if( bbDr < m_dR_Hbb_min ) continue;
    if( bbDr > m_dR_Hbb_max ) continue;
    if( yyDr < m_dR_Hyy_min ) continue;
    if( yyDr > m_dR_Hyy_max ) continue;
    if( deltaR(y1Eta,b1Eta,y1Phi,b1Phi) < m_dR_H_yb_min ) continue;
    if( deltaR(y1Eta,b2Eta,y1Phi,b2Phi) < m_dR_H_yb_min ) continue;
    if( deltaR(y2Eta,b1Eta,y2Phi,b1Phi) < m_dR_H_yb_min ) continue;
    if( deltaR(y2Eta,b2Eta,y2Phi,b2Phi) < m_dR_H_yb_min ) continue;
    if( deltaR(y1Eta,b1Eta,y1Phi,b1Phi) < m_dR_H_leadings_yb_min ) continue; 
     (*count)[1]+=1*scaledWeight3000fb;

    // Min Myy
    if( yyM < m_mHyy_min ) continue;
    if( yyM < m_mHyy_large_min ) continue;
     (*count)[2]+=1*scaledWeight3000fb;

    // Max Myy
    if( yyM > m_mHyy_max ) continue;
    if( yyM > m_mHyy_large_max ) continue;
     (*count)[3]+=1*scaledWeight3000fb;

    // Min Mbb
    if( bbM < m_mHbb_min ) continue;
     (*count)[4]+=1*scaledWeight3000fb;
    // Max Mbb
    if( bbM > m_mHbb_max ) continue;
     (*count)[5]+=1*scaledWeight3000fb;
    // Min yy pT
    if( yyPt < m_H_pt_cut ) continue;
     (*count)[6]+=1*scaledWeight3000fb;
    // Min bb pT
    if( bbPt < m_H_pt_cut ) continue;
     (*count)[7]+=1*scaledWeight3000fb;
    //tree_out->Fill();  
  }

  
  std::cout << "--- End of event loop " <<std::endl; 
    
}
