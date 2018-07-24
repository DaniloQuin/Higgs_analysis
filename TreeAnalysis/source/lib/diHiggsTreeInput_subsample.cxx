// System include(s):
#include <iostream>
#include <iomanip>

// Local include(s):
#include "diHiggsTreeInput_subsample.h"
#include "TChain.h"

float subsamplesize = 1000000;
float signal_factor = 4;
const int v2 = false;
const int v3 = true;


diHiggsTreeInput_subsample::diHiggsTreeInput_subsample(Option option)
{
  std::cout << std::endl;
  std::cout << "--- diHiggsbbyyTreeInput :: Generating model option " << option;

  if ( option_ == sgn_higgs ) std::cout << ": H->bbyy signal sample" <<std::endl;
  if ( option_ == bkg_bbyy )  std::cout << ": bbyy background sample" <<std::endl;
  if ( option_ == bkg_bbyj )  std::cout << ": bbyj background sample" <<std::endl;
  if ( option_ == bkg_ccyy )  std::cout << ": ccyy background sample" <<std::endl;
  if ( option_ == bkg_jjyy )  std::cout << ": jjyy background sample" <<std::endl;
  option_ = option;
  if (option == nathan_sgn_yybb){subsamplesize =  signal_factor* subsamplesize;}
}

diHiggsTreeInput_subsample::~diHiggsTreeInput_subsample()
{
    delete tree_in;
    delete input;
}

void diHiggsTreeInput_subsample::initialize(bool nathan)
{
  nathan_analysis = nathan;

    // Tree events (witeut rerun)
  n_events = 0;
  // Events after cuts (with rerun)
  accepted_events = 0;

  // Tree variables 

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
    bb_cosTSBranch = 0;
    yy_cosTSBranch = 0;
    bbyy_cosTSBranch = 0;
    bbyy_m = 0;
    bbyy_pt = 0;
        // counter
    // text files
  
}

void diHiggsTreeInput_subsample::addBranches(std::string name)
{
  if ( option_ == nathan_sgn_yybb ) outname = "diHiggs_nathan_sgn_yybb_Tree_sub.root";
  if ( option_ == nathan_bkg_ybbj ) outname = "diHiggs_nathan_bkg_ybbj_Tree_sub.root";
  if ( option_ == nathan_bkg_yccj ) outname = "diHiggs_nathan_bkg_yccj_Tree_sub.root";
  if ( option_ == nathan_bkg_yybb ) outname = "diHiggs_nathan_bkg_yybb_Tree_sub.root";
  if ( option_ == nathan_bkg_yycc ) outname = "diHiggs_nathan_bkg_yycc_Tree_sub.root";
  if ( option_ == nathan_bkg_yyjj ) outname = "diHiggs_nathan_bkg_yyjj_Tree_sub.root";
  if ( option_ == nathan_bkg_yyZbb ) outname = "diHiggs_nathan_bkg_yyZbb_Tree_sub.root";
  if ( option_ == nathan_bkg_bbH ) outname = "diHiggs_nathan_bkg_bbH_Tree_sub.root";
  if ( option_ == nathan_bkg_ttH ) outname = "diHiggs_nathan_bkg_ttH_Tree_sub.root";
  if ( option_ == nathan_bkg_ZH ) outname = "diHiggs_nathan_bkg_ZH_Tree_sub.root";
  if ( option_ == nathan_bkg_tt ) outname = "diHiggs_nathan_bkg_tt_Tree_sub.root";
  if ( option_ == nathan_bkg_bbjj ) outname = "diHiggs_nathan_bkg_bbjj_Tree_sub.root";
  if ( option_ == nathan_bkg_ggh ) outname = "diHiggs_nathan_bkg_ggh_Tree_sub.root";


  outputFolder =  name ;
  output = new TFile( outputFolder + outname , "RECREATE");
  tree_out = new TTree("diHiggs", "diHiggs");
  tree_out->Branch("b1_m",&b1M);
  tree_out->Branch("b1_pt",&b1Pt);
  tree_out->Branch("b1_eta",&b1Eta);
  tree_out->Branch("b1_phi",&b1Phi);
  tree_out->Branch("b1_source",&b1Source);
  tree_out->Branch("b2_m",&b2M);
  tree_out->Branch("b2_pt",&b2Pt);
  tree_out->Branch("b2_eta",&b2Eta);
  tree_out->Branch("b2_phi",&b2Phi);
  tree_out->Branch("b2_source",&b2Source);
  tree_out->Branch("y1_pt",&y1Pt);
  tree_out->Branch("y1_eta",&y1Eta);
  tree_out->Branch("y1_phi",&y1Phi);
  tree_out->Branch("y1_source",&y1Source);
  tree_out->Branch("y2_pt",&y2Pt);
  tree_out->Branch("y2_eta",&y2Eta);
  tree_out->Branch("y2_phi",&y2Phi);
  tree_out->Branch("y2_source",&y2Source);
  tree_out->Branch("bb_m",&bbM);
  tree_out->Branch("bb_pt",&bbPt);
  tree_out->Branch("bb_eta",&bbEta);
  tree_out->Branch("bb_phi",&bbPhi);
  tree_out->Branch("bb_dr",&bbDr);
  tree_out->Branch("yy_m",&yyM);
  tree_out->Branch("yy_pt",&yyPt);
  tree_out->Branch("yy_eta",&yyEta);
  tree_out->Branch("yy_phi",&yyPhi);
  tree_out->Branch("yy_dr",&yyDr);
  tree_out->Branch("finalStateWeight",&finalStateWeight);
  tree_out->Branch("bb_cosTSBranch",&bb_cosTSBranch);
  tree_out->Branch("yy_cosTSBranch",&yy_cosTSBranch);
  tree_out->Branch("bbyy_cosTSBranch",&bbyy_cosTSBranch);
  tree_out->Branch("bbyy_m",&bbyy_m);
  tree_out->Branch("bbyy_pt",&bbyy_pt);
  tree_out->Branch("scaledWeight3000fb",&scaledWeight3000fb);

  if ( option_ == nathan_sgn_yybb ) fname = outputFolder + "diHiggs_nathan_sgn_yybb_Tree.root";
  if ( option_ == nathan_bkg_ybbj ) fname = outputFolder + "diHiggs_nathan_bkg_ybbj_Tree.root";
  if ( option_ == nathan_bkg_yccj ) fname = outputFolder + "diHiggs_nathan_bkg_yccj_Tree.root";
  if ( option_ == nathan_bkg_yybb ) fname = outputFolder + "diHiggs_nathan_bkg_yybb_Tree.root";
  if ( option_ == nathan_bkg_yycc ) fname = outputFolder + "diHiggs_nathan_bkg_yycc_Tree.root";
  if ( option_ == nathan_bkg_yyjj ) fname = outputFolder + "diHiggs_nathan_bkg_yyjj_Tree.root";
  if ( option_ == nathan_bkg_yyZbb ) fname = outputFolder + "diHiggs_nathan_bkg_yyZbb_Tree.root";
  if ( option_ == nathan_bkg_bbH ) fname = outputFolder + "diHiggs_nathan_bkg_bbH_Tree.root";
  if ( option_ == nathan_bkg_ttH ) fname = outputFolder + "diHiggs_nathan_bkg_ttH_Tree.root";
  if ( option_ == nathan_bkg_ZH ) fname = outputFolder + "diHiggs_nathan_bkg_ZH_Tree.root";
  if ( option_ == nathan_bkg_tt ) fname = outputFolder + "diHiggs_nathan_bkg_tt_Tree.root";
  if ( option_ == nathan_bkg_bbjj ) fname = outputFolder + "diHiggs_nathan_bkg_bbjj_Tree.root";
  if ( option_ == nathan_bkg_ggh ) fname = outputFolder + "diHiggs_nathan_bkg_ggh_Tree.root";
  
  if (!gSystem->AccessPathName( fname )  ){input = TFile::Open( fname );}
  if (!input) 
    {
    std::cout << "ERROR: could not open data file"<< fname << std::endl;
    exit(1);
    }
  
  tree_in = (TTree*)input->Get("diHiggs");
    
  
  std::cout << "--- Using input file: " << input->GetName() << std::endl;
  
  if ( option_ == nathan_sgn_yybb ) std::cout << "--- Select nathan signal sample" << std::endl;
  if ( option_ == nathan_bkg_ybbj ) std::cout << "--- Select nathan ybbj background sample" << std::endl;
  if ( option_ == nathan_bkg_yccj ) std::cout << "--- Select nathan yccj background sample" << std::endl;
  if ( option_ == nathan_bkg_yybb ) std::cout << "--- Select nathan yybb background sample" << std::endl;
  if ( option_ == nathan_bkg_yycc ) std::cout << "--- Select nathan yycc background sample" << std::endl;
  if ( option_ == nathan_bkg_yyjj ) std::cout << "--- Select nathan yyjj background sample" << std::endl;
  if ( option_ == nathan_bkg_yyZbb ) std::cout << "--- Select nathan yyZbb background sample" << std::endl;
  if ( option_ == nathan_bkg_bbH ) std::cout << "--- Select nathan bbH background sample" << std::endl;
  if ( option_ == nathan_bkg_ttH ) std::cout << "--- Select nathan ttH background sample" << std::endl;
  if ( option_ == nathan_bkg_ZH ) std::cout << "--- Select nathan ZH background sample" << std::endl;
  if ( option_ == nathan_bkg_tt ) std::cout << "--- Select nathan tt background sample" << std::endl;
  if ( option_ == nathan_bkg_bbjj ) std::cout << "--- Select nathan bbjj background sample" << std::endl;
  if ( option_ == nathan_bkg_ggh ) std::cout << "--- Select nathan ggh background sample" << std::endl;

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
  tree_in->SetBranchAddress("finalStateWeight",&finalStateWeight);
  tree_in->SetBranchAddress("scaledWeight3000fb",&scaledWeight3000fb);   
  tree_in->SetBranchAddress("bb_cosTSBranch",&bb_cosTSBranch);
  tree_in->SetBranchAddress("yy_cosTSBranch",&yy_cosTSBranch);
  tree_in->SetBranchAddress("bbyy_m",&bbyy_m);
  tree_in->SetBranchAddress("bbyy_pt",&bbyy_pt);
  tree_in->SetBranchAddress("bbyy_cosTSBranch",&bbyy_cosTSBranch);

}

void diHiggsTreeInput_subsample::finalize()
{
  // counter
  std::cout << "--- Yields" <<std::endl;
  // Write and close output file
  output->Write();
  output->Close();
  // finalize
  std::cout << "--- Finalize. " <<std::endl;
}

void diHiggsTreeInput_subsample::execute()
{
  srand (static_cast <unsigned> (time(0)));
  n_events = tree_in->GetEntries(); 
  std::cout << "--- Processing: " << n_events << " events" << std::endl;
  show_progress = new boost::progress_display( n_events );
  prob = subsamplesize/n_events;
  std::cout << "The prob is : " << prob <<  std::endl;
  for (Long64_t ievt=0; ievt < n_events ;ievt++) 
  {
    ++(*show_progress);
    //if random bla
    tree_in->GetEntry(ievt);
    // No cuts
    if ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX) )<= prob){tree_out->Fill();}
  }
  std::cout << "--- End of event loop " <<std::endl; 
}

