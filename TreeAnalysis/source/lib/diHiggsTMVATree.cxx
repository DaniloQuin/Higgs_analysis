// System include(s):
#include <iostream>
#include <iomanip>
#include "string"

// Local include(s):
#include "diHiggsTMVATree.h"

const int thread_out = 1;
static const bool v2 = true;
static const bool fast = false;


diHiggsTMVATree::diHiggsTMVATree(Option option,long N_thread, long threads)
{
  
  n_thread = N_thread;
  thread = threads; 
    if (thread == thread_out){
  std::cout << std::endl;
  std::cout << "[diHiggsTMVATree :: diHiggsTMVATree] Generating model option " << option;


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
  if ( option_ == nathan_bkg_tt )    std::cout << ": nathan background sample" << std::endl;
  if ( option_ == nathan_bkg_bbjj )    std::cout << ": nathan background sample" << std::endl;
  if ( option_ == nathan_bkg_ggh )    std::cout << ": nathan background sample" << std::endl;
  if ( option_ == nathan_bkg_tty )    std::cout << ": nathan background sample" << std::endl;
  }
    option_ = option;
}


diHiggsTMVATree::~diHiggsTMVATree()
{ 
  delete tree_in;
  delete input;
  delete reader;

}
 
void diHiggsTMVATree::initialize(bool nathan)
{
  nathan_analysis = nathan;
  b1M = 0; 
  b1Pt = 0;
  b1Eta = 0;
  b1Phi = 0;
  b2M = 0;
  b2Pt = 0;
  b2Eta = 0;
  b2Phi = 0;
  y1Pt = 0;
  y1Eta = 0;
  y1Phi = 0;
  y2Pt = 0;
  y2Eta = 0;
  y2Phi = 0;
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
  BDT_response = 0.0;
  bb_cosTSBranch = 0;
  yy_cosTSBranch = 0;
  bbyy_cosTSBranch = 0;
  bbyy_m = 0;
   
}

void diHiggsTMVATree::addBranches(std::string name,int var_cut)
{

  // TMVA Reader
  reader = new TMVA::Reader("!V:Silent=True",false);

  if (var_cut >= 1){reader->AddVariable("b1_m",   &b1_m);}
  else{reader->AddSpectator("b1_m",   &b1_m);}

  if (var_cut >= 2){reader->AddVariable("b1_pt",  &b1_pt);}
  else{reader->AddSpectator("b1_pt",  &b1_pt);}

  if (var_cut >= 3){reader->AddVariable("b1_eta",  &b1_eta);}
  else{reader->AddSpectator("b1_eta",  &b1_eta);}

  if (var_cut >= 4){reader->AddVariable("b1_phi",  &b1_phi);}
  else{reader->AddSpectator("b1_phi",  &b1_phi);}

  if (var_cut >= 5){ reader->AddVariable("b2_m",    &b2_m);}
  else{reader->AddSpectator("b2_m",    &b2_m);}

  if (var_cut >= 6){reader->AddVariable("b2_pt",   &b2_pt);}
  else{reader->AddSpectator("b2_pt",   &b2_pt);}

  if (var_cut >= 7){reader->AddVariable("b2_eta",  &b2_eta);}
  else{reader->AddSpectator("b2_eta",  &b2_eta);}

  if (var_cut >= 8){reader->AddVariable("b2_phi",  &b2_phi);}
  else{reader->AddSpectator("b2_phi",  &b2_phi);}

  if (var_cut >= 9){reader->AddVariable("y1_pt",   &y1_pt);}
  else{reader->AddSpectator("y1_pt",   &y1_pt);}

  if (var_cut >= 10){reader->AddVariable("y1_eta",  &y1_eta);}
  else{reader->AddSpectator("y1_eta",  &y1_eta);}

  if (var_cut >= 11){reader->AddVariable("y1_phi",  &y1_phi);}
  else{reader->AddSpectator("y1_phi",  &y1_phi);}

  if (var_cut >= 12){reader->AddVariable("y2_pt",   &y2_pt);}
  else{reader->AddSpectator("y2_pt",   &y2_pt);}

  if (var_cut >= 13){reader->AddVariable("y2_eta",  &y2_eta);}
  else{reader->AddSpectator("y2_eta",  &y2_eta);}

  if (var_cut >= 14){reader->AddVariable("y2_phi",  &y2_phi);}
  else{reader->AddSpectator("y2_phi",  &y2_phi);}

  if (var_cut >= 15){reader->AddVariable("bb_m",    &bb_m);}
  else{reader->AddSpectator("bb_m",    &bb_m);}

  if (var_cut >= 16){reader->AddVariable("bb_pt",   &bb_pt);}
  else{reader->AddSpectator("bb_pt",   &bb_pt);}

  if (var_cut >= 17){reader->AddVariable("bb_eta",  &bb_eta);}
  else{reader->AddSpectator("bb_eta",  &bb_eta);}

  if (var_cut >= 18){reader->AddVariable("bb_phi",  &bb_phi);}
  else{reader->AddSpectator("bb_phi",  &bb_phi);}

  if (var_cut >= 19){reader->AddVariable("bb_dr",   &bb_dr);}
  else{reader->AddSpectator("bb_dr",   &bb_dr);}

  if (var_cut >= 20){reader->AddSpectator("yy_m",    &yy_m);}
  else{reader->AddSpectator("yy_m",    &yy_m);}

  if (var_cut >= 21){reader->AddVariable("yy_pt",   &yy_pt);}
  else{reader->AddSpectator("yy_pt",   &yy_pt);}

  if (var_cut >= 22){reader->AddVariable("yy_eta",  &yy_eta);}
  else{reader->AddSpectator("yy_eta",  &yy_eta);}

  if (var_cut >= 23){reader->AddVariable("yy_phi",  &yy_phi);}
  else{reader->AddSpectator("yy_phi",  &yy_phi);}

  if (var_cut >= 24){reader->AddVariable("yy_dr",   &yy_dr);}
  else{reader->AddSpectator("yy_dr",   &yy_dr);}

  if (var_cut >= 25){reader->AddVariable("bb_cosTSBranch",&bb_CosTSBranch );}
  else{reader->AddSpectator("bb_cosTSBranch",&bb_CosTSBranch );}

  if (var_cut >= 26){reader->AddVariable("yy_cosTSBranch",&yy_CosTSBranch );}
  else{reader->AddSpectator("yy_cosTSBranch",&yy_CosTSBranch );}

  if (var_cut >= 27){reader->AddVariable("bbyy_cosTSBranch",&bbyy_CosTSBranch );}
  else{reader->AddSpectator("bbyy_cosTSBranch",&bbyy_CosTSBranch);}

  if (var_cut >= 28){reader->AddVariable("bbyy_m",&bbyy_M );}
  else{reader->AddSpectator("bbyy_m",&bbyy_M);}

  if (var_cut >= 29){reader->AddVariable("bbyy_pt",&bbyy_Pt);}
  else{reader->AddSpectator("bbyy_pt",&bbyy_Pt);}

  reader->AddSpectator("scaledWeight3000fb", &scaledweight3000fb);

  reader->BookMVA("BDT method", name + "dataset_na/weights/TMVAClassification_BDT.weights.xml");
  if ( option_ == nathan_sgn_yybb ) outname = "diHiggs_nathan_sgn_yybb_BDT.root";
  if ( option_ == nathan_bkg_ybbj ) outname = "diHiggs_nathan_bkg_ybbj_BDT.root";
  if ( option_ == nathan_bkg_yccj ) outname = "diHiggs_nathan_bkg_yccj_BDT.root";
  if ( option_ == nathan_bkg_yybb ) outname = "diHiggs_nathan_bkg_yybb_BDT.root";
  if ( option_ == nathan_bkg_yycc ) outname = "diHiggs_nathan_bkg_yycc_BDT.root";
  if ( option_ == nathan_bkg_yyjj ) outname = "diHiggs_nathan_bkg_yyjj_BDT.root";
  if ( option_ == nathan_bkg_yyZbb ) outname = "diHiggs_nathan_bkg_yyZbb_BDT.root";
  if ( option_ == nathan_bkg_bbH ) outname = "diHiggs_nathan_bkg_bbH_BDT.root";
  if ( option_ == nathan_bkg_ttH ) outname = "diHiggs_nathan_bkg_ttH_BDT.root";
  if ( option_ == nathan_bkg_ZH ) outname = "diHiggs_nathan_bkg_ZH_BDT.root";
  if ( option_ == nathan_bkg_tt ) outname = "diHiggs_nathan_bkg_tt_BDT.root";
  if ( option_ == nathan_bkg_bbjj ) outname = "diHiggs_nathan_bkg_bbjj_BDT.root";
  if ( option_ == nathan_bkg_ggh ) outname = "diHiggs_nathan_bkg_ggh_BDT.root";

  output = new TFile( name + outname + TString::Itoa(thread,10), "RECREATE");
  TString temporal = TString("diHiggs") + std::to_string(option_);
  tree_out = new TTree(temporal, temporal);

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
  tree_out->Branch("BDT_response",&BDT_response);
  tree_out->Branch("finalStateWeight",&finalStateWeight);
  tree_out->Branch("bb_cosTSBranch",bb_cosTSBranch );
  tree_out->Branch("yy_cosTSBranch",yy_cosTSBranch );
  tree_out->Branch("bbyy_cosTSBranch",bbyy_cosTSBranch );
  tree_out->Branch("bbyy_m",bbyy_m );
  tree_out->Branch("bbyy_pt",bbyy_pt);
  tree_out->Branch("scaledWeight3000fb",&scaledWeight3000fb);

  if ( option_ == nathan_sgn_yybb )  fname = name + "diHiggs_nathan_sgn_yybb_Tree.root"; 
  if ( option_ == nathan_bkg_ybbj )  fname = name + "diHiggs_nathan_bkg_ybbj_Tree.root"; 
  if ( option_ == nathan_bkg_yccj )  fname = name + "diHiggs_nathan_bkg_yccj_Tree.root"; 
  if ( option_ == nathan_bkg_yybb )  fname = name + "diHiggs_nathan_bkg_yybb_Tree.root"; 
  if ( option_ == nathan_bkg_yycc )  fname = name + "diHiggs_nathan_bkg_yycc_Tree.root"; 
  if ( option_ == nathan_bkg_yyjj )  fname = name + "diHiggs_nathan_bkg_yyjj_Tree.root"; 
  if ( option_ == nathan_bkg_yyZbb ) fname = name + "diHiggs_nathan_bkg_yyZbb_Tree.root";
  if ( option_ == nathan_bkg_bbH )   fname = name + "diHiggs_nathan_bkg_bbH_Tree.root";  
  if ( option_ == nathan_bkg_ttH )   fname = name + "diHiggs_nathan_bkg_ttH_Tree.root";  
  if ( option_ == nathan_bkg_ZH )    fname = name + "diHiggs_nathan_bkg_ZH_Tree.root"; 
  if ( option_ == nathan_bkg_tt )    fname = name + "diHiggs_nathan_bkg_tt_Tree.root"; 
  if ( option_ == nathan_bkg_bbjj )    fname = name + "diHiggs_nathan_bkg_bbjj_Tree.root"; 
  if ( option_ == nathan_bkg_ggh )    fname = name + "diHiggs_nathan_bkg_ggh_Tree.root";   
  if ( option_ == nathan_bkg_tty )    fname = name + "diHiggs_nathan_bkg_tty_Tree.root"; 

  if (!gSystem->AccessPathName( fname )) {input = TFile::Open( fname );}
  
  if (!input) 
  {
    std::cout << "ERROR: could not open data file " << fname << std::endl;
    exit(1);
  }

  if (thread == thread_out)
  {
    std::cout << "--- TMVAClassificationApp    : Using input file: " << input->GetName() << std::endl;
    if ( option_ == sgn_higgs ) std::cout << "--- Select signal sample" << std::endl;
    if ( option_ == bkg_bbyy )  std::cout << "--- Select bbyy background sample" << std::endl;
    if ( option_ == bkg_bbyj )  std::cout << "--- Select bbyj background sample" << std::endl;
    if ( option_ == bkg_ccyy )  std::cout << "--- Select ccyy background sample" << std::endl;
    if ( option_ == bkg_jjyy )  std::cout << "--- Select jjyy background sample" << std::endl;

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
    if ( option_ == nathan_bkg_tt )    std::cout << ": Select nathan background sample" << std::endl;
    if ( option_ == nathan_bkg_bbjj )    std::cout << ": Select nathan background sample" << std::endl;
    if ( option_ == nathan_bkg_ggh )    std::cout << ": Select nathan background sample" << std::endl;
    if ( option_ == nathan_bkg_tty )    std::cout << ": Select nathan background sample" << std::endl;
  }
  
  tree_in = (TTree*)input->Get("diHiggs");

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
  tree_in->SetBranchAddress("bb_cosTSBranch",&bb_cosTSBranch );
  tree_in->SetBranchAddress("yy_cosTSBranch",&yy_cosTSBranch );
  tree_in->SetBranchAddress("bbyy_cosTSBranch",&bbyy_cosTSBranch );
  tree_in->SetBranchAddress("bbyy_m",&bbyy_m );
  tree_in->SetBranchAddress("bbyy_pt",&bbyy_pt);
}

void diHiggsTMVATree::execute()
{

  n_events_ = tree_in->GetEntries(); 
  if (thread == thread_out)
  {
  std::cout << "--- Processing: " << n_events_ << " events" << std::endl;
  show_progress = new boost::progress_display( n_events_/n_thread );
  }
  for (Long64_t ievt=thread*n_events_/n_thread; ievt < (thread+1)*n_events_/n_thread ;ievt++) 
  {
    if (thread == thread_out){++(*show_progress);}
    tree_in->GetEntry(ievt);

    b1_m              = (Float_t)b1M;
    b1_pt             = (Float_t)b1Pt;
    b1_eta            = (Float_t)b1Eta;
    b1_phi            = (Float_t)b1Phi;
    b1_source         = (Float_t)b1Source;
    b2_m              = (Float_t)b2M;
    b2_pt             = (Float_t)b2Pt;
    b2_eta            = (Float_t)b2Eta;
    b2_phi            = (Float_t)b2Phi;
    b2_source         = (Float_t)b2Source;
    y1_pt             = (Float_t)y1Pt;
    y1_eta            = (Float_t)y1Eta;
    y1_phi            = (Float_t)y1Phi;
    y1_source         = (Float_t)y1Source;
    y2_pt             = (Float_t)y2Pt;
    y2_eta            = (Float_t)y2Eta;
    y2_phi            = (Float_t)y2Phi;
    y2_source         = (Float_t)y2Source;
    bb_m              = (Float_t)bbM;
    bb_pt             = (Float_t)bbPt;
    bb_eta            = (Float_t)bbEta;
    bb_phi            = (Float_t)bbPhi;
    bb_dr             = (Float_t)bbDr;
    yy_m              = (Float_t)yyM;
    yy_pt             = (Float_t)yyPt;
    yy_eta            = (Float_t)yyEta;
    yy_phi            = (Float_t)yyPhi;
    yy_dr             = (Float_t)yyDr;
    final_stateWeight  = (Float_t)finalStateWeight;
    scaledWeight3000fb = (Float_t)scaledWeight3000fb;
    bb_CosTSBranch     = (Float_t)bb_cosTSBranch;
    yy_CosTSBranch = (Float_t)yy_cosTSBranch ;
    bbyy_CosTSBranch  = (Float_t)bbyy_cosTSBranch ;
    bbyy_M = (Float_t)bbyy_m ;
    bbyy_Pt = (Float_t)bbyy_pt ;
    BDT_response = reader->EvaluateMVA("BDT method");      

    tree_out->Fill();
  }
  if (thread == thread_out)
  {
    std::cout << "--- End of event loop: " <<std::endl; 
    std::cout << "[diHiggsTMVATree :: Finalize]" <<std::endl;
  } 
  output->Write();
  output->Close();
  
}
