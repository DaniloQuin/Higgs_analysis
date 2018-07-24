// System include(s):
#include <iostream>
#include <iomanip>

// Local include(s):
#include "diHiggsbbyyTreeInput.h"
#include "TChain.h"

const int thread_out = 0;
const float luminosity = 3000;

diHiggsbbyyTreeInput::diHiggsbbyyTreeInput(Option option,long N_thread, long threads)
{
  multiple_file = false;
  n_thread = N_thread;
  thread = threads; 
  if (thread == thread_out){
  std::cout << std::endl;
  std::cout << "--- diHiggsbbyyTreeInput :: Generating model option " << option;

  if ( option_ == sgn_higgs ) std::cout << ": H->bbyy signal sample" <<std::endl;
  if ( option_ == bkg_bbyy )  std::cout << ": bbyy background sample" <<std::endl;
  if ( option_ == bkg_bbyj )  std::cout << ": bbyj background sample" <<std::endl;
  if ( option_ == bkg_ccyy )  std::cout << ": ccyy background sample" <<std::endl;
  if ( option_ == bkg_jjyy )  std::cout << ": jjyy background sample" <<std::endl;
  }
  option_ = option;
}


diHiggsbbyyTreeInput::~diHiggsbbyyTreeInput()
{
 
  if (!multiple_file){
    delete tree_in;
    delete input;
  } 

}

Double_t diHiggsbbyyTreeInput::deltaR(Double_t eta1, Double_t eta2, Double_t phi1, Double_t phi2)
{
  Double_t deta = eta1 - eta2;
  Double_t dphi = phi1 - phi2;
  return TMath::Sqrt(deta*deta + dphi*dphi);
}
 
void diHiggsbbyyTreeInput::initialize(bool nathan)
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
  passallcut = false;
  // counter
  const int ncounters = 19;
  for (int icount=0; icount<ncounters; icount++) 
  {
    count[icount] = 0.0;
  }

  // text files
  TString temp = TString("nathan_cutFlow_Tree_")+ TString::Itoa(option_,10) + TString(".dat");;
  cutFlow.open(temp + TString::Itoa(thread,10));

}

void diHiggsbbyyTreeInput::addBranches(std::string  signal,std::string name)
{
  if ( option_ == nathan_sgn_yybb ) outname = "diHiggs_nathan_sgn_yybb_Tree.root";
  if ( option_ == nathan_bkg_ybbj ) outname = "diHiggs_nathan_bkg_ybbj_Tree.root";
  if ( option_ == nathan_bkg_yccj ) outname = "diHiggs_nathan_bkg_yccj_Tree.root";
  if ( option_ == nathan_bkg_yybb ) outname = "diHiggs_nathan_bkg_yybb_Tree.root";
  if ( option_ == nathan_bkg_yycc ) outname = "diHiggs_nathan_bkg_yycc_Tree.root";
  if ( option_ == nathan_bkg_yyjj ) outname = "diHiggs_nathan_bkg_yyjj_Tree.root";
  if ( option_ == nathan_bkg_yyZbb ) outname = "diHiggs_nathan_bkg_yyZbb_Tree.root";
  if ( option_ == nathan_bkg_bbH ) outname = "diHiggs_nathan_bkg_bbH_Tree.root";
  if ( option_ == nathan_bkg_ttH ) outname = "diHiggs_nathan_bkg_ttH_Tree.root";
  if ( option_ == nathan_bkg_ZH ) outname = "diHiggs_nathan_bkg_ZH_Tree.root";
  if ( option_ == nathan_bkg_tt ) outname = "diHiggs_nathan_bkg_tt_Tree.root";
  if ( option_ == nathan_bkg_bbjj ) outname = "diHiggs_nathan_bkg_bbjj_Tree.root";
  if ( option_ == nathan_bkg_ggh ) outname = "diHiggs_nathan_bkg_ggh_Tree.root";
  if ( option_ == nathan_bkg_tty ) outname = "diHiggs_nathan_bkg_tty_Tree.root";
    outputFolder = name ;  

  output = new TFile( outputFolder + outname + TString::Itoa(thread,10), "RECREATE");
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

  if ( option_ == nathan_sgn_yybb ) fname = signal;

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  //some inputs do not have the same format
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 
  if ( option_ == nathan_bkg_ybbj ) {
    fname = nathan_bkg_ybbj_f_v3 + "*mc15_14TeV.344461.MadGraphPythia8EvtGen_A14NNPDF23LO_ybbj.merge.DAOD_TRUTH3.e5319_p2768_FinalV3.root";
    multiple_file = true;
  }

  if ( option_ == nathan_bkg_yccj ) {
    fname = nathan_bkg_yccj_f_v3 + "*mc15_14TeV.344464.MadGraphPythia8EvtGen_A14NNPDF23LO_yccj.merge.DAOD_TRUTH3.e5319_p2768_FinalV3.root";
    multiple_file = true;
  }

  if ( option_ == nathan_bkg_yybb ) fname = nathan_bkg_yybb_f_v3 + "mc15_14TeV.344460.MadGraphPythia8EvtGen_A14NNPDF23LO_yybb.merge.DAOD_TRUTH3.e5319_p2768_FinalV3.root";
  
  if ( option_ == nathan_bkg_yycc ) fname = nathan_bkg_yycc_f_v3 + "mc15_14TeV.344463.MadGraphPythia8EvtGen_A14NNPDF23LO_yycc.merge.DAOD_TRUTH3.e5319_p2768_FinalV3.root";
  
  if ( option_ == nathan_bkg_yyjj ){ 
    fname = nathan_bkg_yyjj_f_v3 + "*mc15_14TeV.344462.MadGraphPythia8EvtGen_A14NNPDF23LO_yyjj.merge.DAOD_TRUTH3.e5319_p2768_FinalV3.root";
    multiple_file = true;
  }

  if ( option_ == nathan_bkg_yyZbb ) fname = nathan_bkg_yyZbb_f_v3 + "mc15_14TeV.361599.MadGraphPythia8EvtGen_A14NNPDF23LO_yyZbb.merge.DAOD_TRUTH3.e5342_p2768_FinalV3.root";
  
  if ( option_ == nathan_bkg_bbH ) fname = nathan_bkg_bbH_f_v3 + "mc15_14TeV.344466.Pythia8EvtGen_A14NNPDF23LO_bbH125_gamgam.merge.DAOD_TRUTH3.e5342_p2768_FinalV3.root";
  
  if ( option_ == nathan_bkg_ttH ){ 
    fname = nathan_bkg_ttH_f_v3 + "*mc15_14TeV.341069.Pythia8EvtGen_A14NNPDF23LO_ttH125_gamgam.merge.DAOD_TRUTH3.e5268_p2613_FinalV3.root";
    multiple_file = true;
  }
  
  if ( option_ == nathan_bkg_ZH ) fname = nathan_bkg_ZH_f_v3 + "mc15_14TeV.341068.Pythia8EvtGen_A14NNPDF23LO_ZH125_gamgam.merge.DAOD_TRUTH3.e5268_p2613_FinalV3.root";
  
  if ( option_ == nathan_bkg_tt ) {
    fname = nathan_bkg_tt_f_v3 + "*mc15_14TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.DAOD_TRUTH3.e5168_p2768_FinalV3.root";
    multiple_file = true;
  } 
  
  if ( option_ == nathan_bkg_bbjj ) fname = nathan_bkg_bbjj_f_v3 + "mc15_14TeV.344820.MadGraphPythia8EvtGen_A14NNPDF23LO_bbjj_plus0jet.merge.DAOD_TRUTH3.e5424_p2768_FinalV3.root";
  
  if ( option_ == nathan_bkg_ggh )fname = nathan_bkg_ggh_f_v3 + "mc15_14TeV.341000.PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_ggH125_gamgam.merge.DAOD_TRUTH3.e5529_p2768_FinalV3.root";
  
  if ( option_ == nathan_bkg_tty ) {
    fname = nathan_bkg_tty_f_v3 + "*mc15_14TeV.206604.MadGraphPythia8_AU2CTEQ6L1_ttgamma.merge.DAOD_TRUTH3.e3621_p2768_FinalV3.root";
    multiple_file = true;
  } 

  if (!multiple_file) {
    if (!gSystem->AccessPathName( fname )  ){
       input = TFile::Open( fname ); // check if file in local directory exists
    }
    if (!input) {
      std::cout << "ERROR: could not open data file"<< fname << std::endl;
      exit(1);
    }
    tree_in = (TTree*)input->Get("finalSelection");
  }
  else{
    tree_in_chain = new TChain("finalSelection");
    tree_in_chain->Add(fname);
    tree_in_chain->SetMakeClass(1);
  }
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  
  if (thread == thread_out)
  {
    if (!multiple_file) {std::cout << "--- Using input file: " << input->GetName() << std::endl;}
    else{std::cout << "--- Using input file: " << option_ << std::endl;}

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
    if ( option_ == nathan_bkg_ggh ) std::cout << "--- Select nathan ggh background sample" << std::endl;
    if ( option_ == nathan_bkg_tt ) std::cout << "--- Select nathan tt background sample" << std::endl;
    if ( option_ == nathan_bkg_bbjj ) std::cout << "--- Select nathan bbjj background sample" << std::endl;
    if ( option_ == nathan_bkg_tty ) std::cout << "--- Select nathan tty background sample" << std::endl;
  }
  if (!multiple_file)
  {
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
    tree_in->SetBranchAddress("bbyy_m",&bbyy_m);
    tree_in->SetBranchAddress("bbyy_pt",&bbyy_pt);
    tree_in->SetBranchAddress("scaledWeight3000fb",&scaledWeight3000fb);
    tree_in->SetBranchAddress("passAllCuts",&passallcut);
  }
  else
  {
    tree_in_chain->SetBranchAddress("b1_m",&b1M);
    tree_in_chain->SetBranchAddress("b1_pt",&b1Pt);
    tree_in_chain->SetBranchAddress("b1_eta",&b1Eta);
    tree_in_chain->SetBranchAddress("b1_phi",&b1Phi);
    tree_in_chain->SetBranchAddress("b1_source",&b1Source);
    tree_in_chain->SetBranchAddress("b2_m",&b2M);
    tree_in_chain->SetBranchAddress("b2_pt",&b2Pt);
    tree_in_chain->SetBranchAddress("b2_eta",&b2Eta);
    tree_in_chain->SetBranchAddress("b2_phi",&b2Phi);
    tree_in_chain->SetBranchAddress("b2_source",&b2Source);
    tree_in_chain->SetBranchAddress("y1_pt",&y1Pt);
    tree_in_chain->SetBranchAddress("y1_eta",&y1Eta);
    tree_in_chain->SetBranchAddress("y1_phi",&y1Phi);
    tree_in_chain->SetBranchAddress("y1_source",&y1Source);
    tree_in_chain->SetBranchAddress("y2_pt",&y2Pt);
    tree_in_chain->SetBranchAddress("y2_eta",&y2Eta);
    tree_in_chain->SetBranchAddress("y2_phi",&y2Phi);
    tree_in_chain->SetBranchAddress("y2_source",&y2Source);
    tree_in_chain->SetBranchAddress("bb_m",&bbM);
    tree_in_chain->SetBranchAddress("bb_pt",&bbPt);
    tree_in_chain->SetBranchAddress("bb_eta",&bbEta);
    tree_in_chain->SetBranchAddress("bb_phi",&bbPhi);
    tree_in_chain->SetBranchAddress("bb_dr",&bbDr);
    tree_in_chain->SetBranchAddress("yy_m",&yyM);
    tree_in_chain->SetBranchAddress("yy_pt",&yyPt);
    tree_in_chain->SetBranchAddress("yy_eta",&yyEta);
    tree_in_chain->SetBranchAddress("yy_phi",&yyPhi);
    tree_in_chain->SetBranchAddress("yy_dr",&yyDr);
    tree_in_chain->SetBranchAddress("finalStateWeight",&finalStateWeight);
    tree_in_chain->SetBranchAddress("bbyy_m",&bbyy_m);
    tree_in_chain->SetBranchAddress("bbyy_pt",&bbyy_pt);
    tree_in_chain->SetBranchAddress("scaledWeight3000fb",&scaledWeight3000fb);
    tree_in_chain->SetBranchAddress("passAllCuts",&passallcut);
  }
}

void diHiggsbbyyTreeInput::finalize()
{
  // counter
  if (thread == thread_out){
    std::cout << "--- Yields" <<std::endl;
    std::cout << std::endl;
  }
  const int ncounters = 19;
  for (int icount=0; icount<ncounters; icount++) 
  {
    TString Name = "Events after ";
    if (icount==0)  Name +=  "no cuts                ";
    if (icount==1)  Name +=  "junk drop              ";
    if (icount==2)  Name +=  "min n.trigger.photons  ";
    if (icount==3)  Name +=  "min n.photons          ";
    if (icount==4)  Name +=  "max n.photons          ";
    if (icount==5)  Name +=  "min n.jets             ";
    if (icount==6)  Name +=  "min n.bjets            ";
    if (icount==7)  Name +=  "min n.leading.bjets    ";
    if (icount==8)  Name +=  "max n.bjets            ";
    if (icount==9)  Name +=  "max n.jets             ";
    if (icount==10) Name +=  "max n.electrons        ";
    if (icount==11) Name +=  "max n.muons            ";
    if (icount==12) Name +=  "angular selection      ";
    if (icount==13) Name +=  "min Myy                ";
    if (icount==14) Name +=  "max Myy                ";
    if (icount==15) Name +=  "min Mbb                ";
    if (icount==16) Name +=  "max Mbb                ";
    if (icount==17) Name +=  "min yy pT              ";
    if (icount==18) Name +=  "min bb pT              ";
    if (thread == thread_out){std::cout<< Name + ": "<< count[icount] <<std::endl;}
    // CutFlow
    cutFlow << icount << " , " << count[icount] <<std::endl;
  }
  cutFlow.close();
  if (thread == thread_out){std::cout << std::endl;}
  accepted_events = count[7];
  
  if (thread == thread_out)
  {
    // Final number of events
    std::cout<<" Total number of accepted events: "<< accepted_events <<std::endl;
    if (nathan_analysis)
    {
      std::cout<<" Total number of events at 3000 fb^-1: "<< scaledWeight3000fb*(double)accepted_events/(double)n_events << " +- "<< scaledWeight3000fb*sqrt( (double)accepted_events/(double)n_events ) <<std::endl;
      std::cout<<" Total number of events at 3000 fb^-1: "<< scaledWeight3000fb*(double)accepted_events/(double)n_events <<std::endl; // don't know why sqrt its not working properly
    }
    else
    {
      std::cout<<" Total number of events at 3000 fb^-1: "<<  weight_perEvent*(double)accepted_events/(double)n_events << " +- "<< totalWeight*sqrt( (double)accepted_events/(double)n_events ) <<std::endl;
      std::cout<<" Total number of events at 3000 fb^-1: "<< weight_perEvent*(double)accepted_events/(double)n_events <<std::endl; // don't know why sqrt its not working properly
    }
  }
  // Write and close output file
  output->Write();
  output->Close();
  if (thread == thread_out)
  {
    // finalize
    std::cout << "--- Finalize. " <<std::endl;
  }
}

void diHiggsbbyyTreeInput::execute(int cut)
{
  if (!multiple_file){n_events = tree_in->GetEntries(); }
  else{ n_events = tree_in_chain->GetEntries(); }
  if (thread == thread_out)
  {
    std::cout << "--- Processing: " << n_events << " events" << std::endl;
    show_progress = new boost::progress_display( n_events/n_thread );
  }
  for (Long64_t ievt=thread*n_events/n_thread; ievt < (thread+1)*n_events/n_thread ;ievt++) 
  {
    if (thread == thread_out){++(*show_progress);}
    if(!multiple_file){tree_in->GetEntry(ievt);}
    else{tree_in_chain->GetEntry(ievt);}
    temp = scaledWeight3000fb;

    bb_cosTSBranch = fabs(
      ((sqrt(b1M*b1M+b1Pt*b1Pt*cosh(b1Eta)*cosh(b1Eta))+b1Pt*TMath::SinH(b1Eta))
      *
      (sqrt(b2M*b2M+b2Pt*b2Pt*cosh(b2Eta)*cosh(b2Eta))-b2Pt*TMath::SinH(b2Eta))
      -
      (sqrt(b1M*b1M+b1Pt*b1Pt*cosh(b1Eta)*cosh(b1Eta))-b1Pt*TMath::SinH(b1Eta))
      *
      (sqrt(b2M*b2M+b2Pt*b2Pt*cosh(b2Eta)*cosh(b2Eta))+b2Pt*TMath::SinH(b2Eta)))
      / (bbM*sqrt(bbM*bbM+bbPt*bbPt))  );
    yy_cosTSBranch = fabs(
      ((sqrt(0*0+y1Pt*y1Pt*cosh(y1Eta)*cosh(y1Eta))+y1Pt*TMath::SinH(y1Eta))
      *
      (sqrt(0*0+y2Pt*y2Pt*cosh(y2Eta)*cosh(y2Eta))-y2Pt*TMath::SinH(y2Eta))
      -
      (sqrt(0*0+y1Pt*y1Pt*cosh(y1Eta)*cosh(y1Eta))-y1Pt*TMath::SinH(y1Eta))
      *
      (sqrt(0*0+y2Pt*y2Pt*cosh(y2Eta)*cosh(y2Eta))+y2Pt*TMath::SinH(y2Eta)))
      / (yyM*sqrt(yyM*yyM+yyPt*yyPt)) );
    bbyy_cosTSBranch = fabs(
      ((sqrt(yyM*yyM+yyPt*yyPt*cosh(TMath::ASinH((y1Pt*TMath::SinH(y1Eta)
      +
      y2Pt*TMath::SinH(y2Eta))/yyPt))*cosh(TMath::ASinH((y1Pt*TMath::SinH(y1Eta)
      +
      y2Pt*TMath::SinH(y2Eta))/yyPt)))+yyPt*sinh(TMath::ASinH((y1Pt*TMath::SinH(y1Eta)
      +
      y2Pt*TMath::SinH(y2Eta))/yyPt)))*(sqrt(bbM*bbM+bbPt*bbPt*cosh(TMath::ASinH((b1Pt*TMath::SinH(b1Eta)
      +
      b2Pt*TMath::SinH(b2Eta))/bbPt))*cosh(TMath::ASinH((b1Pt*TMath::SinH(b1Eta)
      +
      b2Pt*TMath::SinH(b2Eta))/bbPt)))-bbPt*sinh(TMath::ASinH((b1Pt*TMath::SinH(b1Eta)
      + b2Pt*TMath::SinH(b2Eta))/bbPt))) -
      (sqrt(yyM*yyM+yyPt*yyPt*cosh(TMath::ASinH((y1Pt*TMath::SinH(y1Eta)
      +
      y2Pt*TMath::SinH(y2Eta))/yyPt))*cosh(TMath::ASinH((y1Pt*TMath::SinH(y1Eta)
      +
      y2Pt*TMath::SinH(y2Eta))/yyPt)))-yyPt*sinh(TMath::ASinH((y1Pt*TMath::SinH(y1Eta)
      +
      y2Pt*TMath::SinH(y2Eta))/yyPt)))*(sqrt(bbM*bbM+bbPt*bbPt*cosh(TMath::ASinH((b1Pt*TMath::SinH(b1Eta)
      +
      b2Pt*TMath::SinH(b2Eta))/bbPt))*cosh(TMath::ASinH((b1Pt*TMath::SinH(b1Eta)
      +
      b2Pt*TMath::SinH(b2Eta))/bbPt)))+bbPt*sinh(TMath::ASinH((b1Pt*TMath::SinH(b1Eta)
      + b2Pt*TMath::SinH(b2Eta))/bbPt))))  /
      (bbyy_m*sqrt(bbyy_m*bbyy_m+bbyy_pt*bbyy_pt)) );

    // No cuts
    count[0]+=temp;
    if (cut == 0){tree_out->Fill();} 
    //if (passallcut==1)continue;
    count[10]+=temp;
    if (b1M ==0 && yyM==0)continue;
    count[11]+=temp;
    if (cut == 1){tree_out->Fill();}


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
    count[12]+=temp;
    if (cut == 2){tree_out->Fill();}
     


    // Min Myy
    if( yyM < m_mHyy_min ) continue;
    if( yyM < m_mHyy_large_min ) continue;
    count[13]+=temp;
    if (cut == 3){tree_out->Fill();}

    // Max Myy
    if( yyM > m_mHyy_max ) continue;
    if( yyM > m_mHyy_large_max ) continue;
    count[14]+=temp;
    if (cut == 4){tree_out->Fill();}

    // Min Mbb
    if( bbM < m_mHbb_min ) continue;
    count[15]+=temp;
    if (cut == 5){tree_out->Fill();}
    // Max Mbb
    if( bbM > m_mHbb_max ) continue;
    count[16]+=temp;
    if (cut == 6){tree_out->Fill();}
    // Min yy pT
    if( yyPt < m_H_pt_cut ) continue;
    count[17]+=temp;
    if (cut == 7){tree_out->Fill();}
    // Min bb pT
    if( bbPt < m_H_pt_cut ) continue;
    count[18]+=temp;
    if (cut == 8){tree_out->Fill();}
  }
  
  if (thread == thread_out){
  std::cout << "--- End of event loop " <<std::endl; 
  }  
}
