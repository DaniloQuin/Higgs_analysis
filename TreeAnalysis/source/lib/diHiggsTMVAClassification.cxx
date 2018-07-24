// System include(s):
#include <iostream>
#include <iomanip>
#include <unistd.h>

// Local include(s):
#include "diHiggsTMVAClassification.h"

static const bool v2 = true;

diHiggsTMVAClassification::diHiggsTMVAClassification(bool nathan)
{
  nathan_analysis = nathan;
  std::cout << std::endl;
  std::cout << "[diHiggsTMVAClassification :: diHiggsTMVAClassification] ";
  
}

diHiggsTMVAClassification::~diHiggsTMVAClassification()
{
  
  delete input_sgn;
  delete input_bkg_bbyy;
  delete input_bkg_bbyj;
  delete input_bkg_ccyy;
  delete input_bkg_jjyy;
  delete outputFile;
  delete signalTree;
  delete bkgTree_bbyy;
  delete bkgTree_bbyj;
  delete bkgTree_ccyy;
  delete bkgTree_jjyy;
  
}
 

void diHiggsTMVAClassification::addMethod(bool fast,std::string name,std::string tree,std::string depth,std::string minnodesize, int var_cut)
{

  // Read training and test data
  inputFolder = name;
  if (fast)
  {
    fname_sgn_yybb = inputFolder + "diHiggs_nathan_sgn_yybb_Tree_sub.root";
    fname_bkg_ybbj = inputFolder + "diHiggs_nathan_bkg_ybbj_Tree_sub.root";
    fname_bkg_yccj = inputFolder + "diHiggs_nathan_bkg_yccj_Tree_sub.root";
    fname_bkg_yybb = inputFolder + "diHiggs_nathan_bkg_yybb_Tree_sub.root";
    fname_bkg_yycc = inputFolder + "diHiggs_nathan_bkg_yycc_Tree_sub.root";
    fname_bkg_yyjj = inputFolder + "diHiggs_nathan_bkg_yyjj_Tree_sub.root";
    fname_bkg_yyZbb = inputFolder + "diHiggs_nathan_bkg_yyZbb_Tree_sub.root";
    fname_bkg_bbH = inputFolder + "diHiggs_nathan_bkg_bbH_Tree_sub.root";
    fname_bkg_ttH = inputFolder + "diHiggs_nathan_bkg_ttH_Tree_sub.root";
    fname_bkg_ZH = inputFolder + "diHiggs_nathan_bkg_ZH_Tree_sub.root";
    fname_bkg_tt = inputFolder + "diHiggs_nathan_bkg_tt_Tree_sub.root";
    fname_bkg_bbjj = inputFolder + "diHiggs_nathan_bkg_bbjj_Tree_sub.root";
    fname_bkg_ggh = inputFolder + "diHiggs_nathan_bkg_ggh_Tree_sub.root";
  }
  else
  {
    fname_sgn_yybb = inputFolder + "diHiggs_nathan_sgn_yybb_Tree.root";
    fname_bkg_ybbj = inputFolder + "diHiggs_nathan_bkg_ybbj_Tree.root";
    fname_bkg_yccj = inputFolder + "diHiggs_nathan_bkg_yccj_Tree.root";
    fname_bkg_yybb = inputFolder + "diHiggs_nathan_bkg_yybb_Tree.root";
    fname_bkg_yycc = inputFolder + "diHiggs_nathan_bkg_yycc_Tree.root";
    fname_bkg_yyjj = inputFolder + "diHiggs_nathan_bkg_yyjj_Tree.root";
    fname_bkg_yyZbb = inputFolder + "diHiggs_nathan_bkg_yyZbb_Tree.root";
    fname_bkg_bbH = inputFolder + "diHiggs_nathan_bkg_bbH_Tree.root";
    fname_bkg_ttH = inputFolder + "diHiggs_nathan_bkg_ttH_Tree.root";
    fname_bkg_ZH = inputFolder + "diHiggs_nathan_bkg_ZH_Tree.root";
    fname_bkg_tt = inputFolder + "diHiggs_nathan_bkg_tt_Tree.root";
    fname_bkg_bbjj = inputFolder + "diHiggs_nathan_bkg_bbjj_Tree.root";
    fname_bkg_ggh = inputFolder + "diHiggs_nathan_bkg_ggh_Tree.root";
  }
  input_nathan_sgn_yybb = TFile::Open(fname_sgn_yybb);
  input_nathan_bkg_ybbj = TFile::Open(fname_bkg_ybbj);
  input_nathan_bkg_yccj = TFile::Open(fname_bkg_yccj);
  input_nathan_bkg_yybb = TFile::Open(fname_bkg_yybb);
  input_nathan_bkg_yycc = TFile::Open(fname_bkg_yycc);
  input_nathan_bkg_yyjj = TFile::Open(fname_bkg_yyjj);
  input_nathan_bkg_yyZbb = TFile::Open(fname_bkg_yyZbb);
  input_nathan_bkg_bbH = TFile::Open(fname_bkg_bbH);
  input_nathan_bkg_ttH = TFile::Open(fname_bkg_ttH);
  input_nathan_bkg_ZH = TFile::Open(fname_bkg_ZH);
  //input_nathan_bkg_tt = TFile::Open(fname_bkg_tt);
  input_nathan_bkg_bbjj = TFile::Open(fname_bkg_bbjj);
  input_nathan_bkg_ggh = TFile::Open(fname_bkg_ggh);

  std::cout << "--- TMVAClassification       : Using nathan input signal file yybb " << input_nathan_sgn_yybb->GetName() << std::endl;
  std::cout << "--- TMVAClassification       : Using nathan input background file ybbj " << input_nathan_bkg_ybbj->GetName() << std::endl;
  std::cout << "--- TMVAClassification       : Using nathan input background file yccj " << input_nathan_bkg_yccj->GetName() << std::endl;
  std::cout << "--- TMVAClassification       : Using nathan input background file yybb " << input_nathan_bkg_yybb->GetName() << std::endl;
  std::cout << "--- TMVAClassification       : Using nathan input background file yycc " << input_nathan_bkg_yycc->GetName() << std::endl;
  std::cout << "--- TMVAClassification       : Using nathan input background file yyjj " << input_nathan_bkg_yyjj->GetName() << std::endl;
  std::cout << "--- TMVAClassification       : Using nathan input background file yyZbb " << input_nathan_bkg_yyZbb->GetName() << std::endl;
  std::cout << "--- TMVAClassification       : Using nathan input background file bbH " << input_nathan_bkg_bbH->GetName() << std::endl;
  std::cout << "--- TMVAClassification       : Using nathan input background file ttH " << input_nathan_bkg_ttH->GetName() << std::endl;
  std::cout << "--- TMVAClassification       : Using nathan input background file ZH " << input_nathan_bkg_ZH->GetName() << std::endl;
  //std::cout << "--- TMVAClassification       : Using nathan input background file tt " << input_nathan_bkg_tt->GetName() << std::endl;
  std::cout << "--- TMVAClassification       : Using nathan input background file bbjj " << input_nathan_bkg_bbjj->GetName() << std::endl;
  std::cout << "--- TMVAClassification       : Using nathan input background file ggh " << input_nathan_bkg_ggh->GetName() << std::endl;


  nathan_signalTree_yybb = (TTree*)input_nathan_sgn_yybb->Get("diHiggs");
  nathan_bkgTree_ybbj    = (TTree*)input_nathan_bkg_ybbj->Get("diHiggs");
  nathan_bkgTree_yccj    = (TTree*)input_nathan_bkg_yccj->Get("diHiggs");
  nathan_bkgTree_yybb    = (TTree*)input_nathan_bkg_yybb->Get("diHiggs");
  nathan_bkgTree_yycc    = (TTree*)input_nathan_bkg_yycc->Get("diHiggs");
  nathan_bkgTree_yyjj    = (TTree*)input_nathan_bkg_yyjj->Get("diHiggs");
  nathan_bkgTree_yyZbb   = (TTree*)input_nathan_bkg_yyZbb->Get("diHiggs");
  nathan_bkgTree_bbH     = (TTree*)input_nathan_bkg_bbH->Get("diHiggs");
  nathan_bkgTree_ttH     = (TTree*)input_nathan_bkg_ttH->Get("diHiggs");
  nathan_bkgTree_ZH      = (TTree*)input_nathan_bkg_ZH->Get("diHiggs");
  //nathan_bkgTree_tt      = (TTree*)input_nathan_bkg_tt->Get("diHiggs");
  nathan_bkgTree_bbjj      = (TTree*)input_nathan_bkg_bbjj->Get("diHiggs");
  nathan_bkgTree_ggh      = (TTree*)input_nathan_bkg_ggh->Get("diHiggs");


  // Create a ROOT output file where TMVA will store ntuples, histograms, etc. 
  TString outfileName;

  outfileName = name + TString( "TMVA_na.root" );
  
  outputFile = TFile::Open( outfileName, "RECREATE" );

  // Create the factory object. Later you can choose the methods                            
  // whose performance you'd like to investigate. The factory is                            
  // the only TMVA object you have to interact with                                         
  //                                                                                        
  // The first argument is the base of the name of all the                                  
  // weightfiles in the directory weight/                                                   
  //                                                                                        
  // The second argument is the output file for the training results                        
  // All TMVA output can be suppressed by removing the "!" (not) in                         
  // front of the "Silent" argument in the option string 
  TMVA::Factory * factory = new TMVA::Factory( "TMVAClassification", outputFile,"!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
  TMVA::DataLoader *dataloader;
  chdir(name.c_str());
  dataloader=new TMVA::DataLoader("dataset_na");
  
  if (var_cut >= 1){dataloader->AddVariable("b1_m","b1_m", "", 'D' );}
  else {dataloader->AddSpectator("b1_m","b1_m", "", 'D' );}

  if (var_cut >= 2){dataloader->AddVariable("b1_pt","b1_pt", "", 'D' );}
  else {dataloader->AddSpectator("b1_pt","b1_pt", "", 'D' );}

  if (var_cut >= 3){dataloader->AddVariable("b1_eta","b1_eta", "", 'D' );}
  else {dataloader->AddSpectator("b1_eta","b1_eta", "", 'D' );}

  if (var_cut >= 4){dataloader->AddVariable("b1_phi","b1_phi", "", 'D' );}
  else {dataloader->AddSpectator("b1_phi","b1_phi", "", 'D' );}

  if (var_cut >= 5){dataloader->AddVariable("b2_m","b2_m", "", 'D' );}
  else {dataloader->AddSpectator("b2_m","b2_m", "", 'D' );}

  if (var_cut >= 6){dataloader->AddVariable("b2_pt","b2_pt", "", 'D' );}
  else {dataloader->AddSpectator("b2_pt","b2_pt", "", 'D' );}

  if (var_cut >= 7){dataloader->AddVariable("b2_eta","b2_eta", "", 'D' );}
  else {dataloader->AddSpectator("b2_eta","b2_eta", "", 'D' );}

  if (var_cut >= 8){dataloader->AddVariable("b2_phi","b2_phi", "", 'D' );}
  else {dataloader->AddSpectator("b2_phi","b2_phi", "", 'D' );}

  if (var_cut >= 9){dataloader->AddVariable("y1_pt","y1_pt", "", 'D' );}
  else {dataloader->AddSpectator("y1_pt","y1_pt", "", 'D' );}

  if (var_cut >= 10){dataloader->AddVariable("y1_eta","y1_eta", "", 'D' );}
  else {dataloader->AddSpectator("y1_eta","y1_eta", "", 'D' );}

  if (var_cut >= 11){dataloader->AddVariable("y1_phi","y1_phi", "", 'D' );}
  else {dataloader->AddSpectator("y1_phi","y1_phi", "", 'D' );}

  if (var_cut >= 12){dataloader->AddVariable("y2_pt","y2_pt", "", 'D' );}
  else {dataloader->AddSpectator("y2_pt","y2_pt", "", 'D' );}

  if (var_cut >= 13){dataloader->AddVariable("y2_eta","y2_eta", "", 'D' );}
  else {dataloader->AddSpectator("y2_eta","y2_eta", "", 'D' );}

  if (var_cut >= 14){dataloader->AddVariable("y2_phi","y2_phi", "", 'D' );}
  else {dataloader->AddSpectator("y2_phi","y2_phi", "", 'D' );}

  if (var_cut >= 15){dataloader->AddVariable("bb_m","bb_m", "", 'D' );}
  else {dataloader->AddSpectator("bb_m","bb_m", "", 'D' );}

  if (var_cut >= 16){dataloader->AddVariable("bb_pt","bb_pt", "", 'D' );}
  else {dataloader->AddSpectator("bb_pt","bb_pt", "", 'D' );}

  if (var_cut >= 17){dataloader->AddVariable("bb_eta","bb_eta", "", 'D' );}
  else {dataloader->AddSpectator("bb_eta","bb_eta", "", 'D' );}

  if (var_cut >= 18){dataloader->AddVariable("bb_phi","bb_phi", "", 'D' );}
  else {dataloader->AddSpectator("bb_phi","bb_phi", "", 'D' );}

  if (var_cut >= 19){dataloader->AddVariable("bb_dr","bb_dr", "", 'D' );}
  else {dataloader->AddSpectator("bb_dr","bb_dr", "", 'D' );}

  if (var_cut >= 20){dataloader->AddSpectator("yy_m","yy_m", "", 'D' );}
  else {dataloader->AddSpectator("yy_m","yy_m", "", 'D' );}

  if (var_cut >= 21){dataloader->AddVariable("yy_pt","yy_pt", "", 'D' );}
  else {dataloader->AddSpectator("yy_pt","yy_pt", "", 'D' );}

  if (var_cut >= 22){dataloader->AddVariable("yy_eta","yy_eta", "", 'D' );}
  else {dataloader->AddSpectator("yy_eta","yy_eta", "", 'D' );}

  if (var_cut >= 23){dataloader->AddVariable("yy_phi","yy_phi", "", 'D' );}
  else {dataloader->AddSpectator("yy_phi","yy_phi", "", 'D' );}

  if (var_cut >= 24){dataloader->AddVariable("yy_dr","yy_dr", "", 'D' );}
  else {dataloader->AddSpectator("yy_dr","yy_dr", "", 'D' );}

  if (var_cut >= 25){dataloader->AddVariable("bb_cosTSBranch","bb_cosTSBranch", "", 'D' );}
  else {dataloader->AddSpectator("bb_cosTSBranch","bb_cosTSBranch", "", 'D' );}

  if (var_cut >= 26){dataloader->AddVariable("yy_cosTSBranch","yy_cosTSBranch", "", 'D' );}
  else {dataloader->AddSpectator("yy_cosTSBranch","yy_cosTSBranch", "", 'D' );}

  if (var_cut >= 27){dataloader->AddVariable("bbyy_cosTSBranch","bbyy_cosTSBranch", "", 'D' );}
  else {dataloader->AddSpectator("bbyy_cosTSBranch","bbyy_cosTSBranch", "", 'D' );}

  if (var_cut >= 28){dataloader->AddVariable("bbyy_m","bbyy_m", "", 'D' );}
  else {dataloader->AddSpectator("bbyy_m","bbyy_m", "", 'D' );}

  if (var_cut >= 29){dataloader->AddVariable("bbyy_pt","bbyy_pt", "", 'D' );}
  else {dataloader->AddSpectator("bbyy_pt","bbyy_pt", "", 'D' );}

  dataloader->AddSpectator("scaledWeight3000fb","scaledWeight3000fb","", 'D');

  // global event weights per tree (see below for setting event-wise weights) - probably global variables instead of local * dan
  Double_t nathan_signalWeight   = 1.0;
  Double_t nathan_bkgWeight_ybbj = 1.0;
  Double_t nathan_bkgWeight_yccj = 1.0;
  Double_t nathan_bkgWeight_yybb = 1.0;
  Double_t nathan_bkgWeight_yycc = 1.0;
  Double_t nathan_bkgWeight_yyjj = 1.0;
  Double_t nathan_bkgWeight_yyZbb = 1.0;
  Double_t nathan_bkgWeight_bbH = 1.0;
  Double_t nathan_bkgWeight_ttH = 1.0;
  Double_t nathan_bkgWeight_ZH = 1.0;
  Double_t nathan_bkgWeight_tt = 1.0;
  Double_t nathan_bkgWeight_bbjj = 1.0;
  Double_t nathan_bkgWeight_ggh = 1.0;


  // You can add an arbitrary number of signal or background trees
  dataloader->AddSignalTree    (nathan_signalTree_yybb , nathan_signalWeight);

  dataloader->AddBackgroundTree(nathan_bkgTree_ybbj  , nathan_bkgWeight_ybbj);
  dataloader->AddBackgroundTree(nathan_bkgTree_yccj  , nathan_bkgWeight_yccj);
  dataloader->AddBackgroundTree(nathan_bkgTree_yybb  , nathan_bkgWeight_yybb);
  dataloader->AddBackgroundTree(nathan_bkgTree_yycc  , nathan_bkgWeight_yycc);
  dataloader->AddBackgroundTree(nathan_bkgTree_yyjj  , nathan_bkgWeight_yyjj);
  dataloader->AddBackgroundTree(nathan_bkgTree_yyZbb , nathan_bkgWeight_yyZbb);
  dataloader->AddBackgroundTree(nathan_bkgTree_bbH   , nathan_bkgWeight_bbH );
  dataloader->AddBackgroundTree(nathan_bkgTree_ttH   , nathan_bkgWeight_ttH );
  dataloader->AddBackgroundTree(nathan_bkgTree_ZH    , nathan_bkgWeight_ZH );
  //dataloader->AddBackgroundTree(nathan_bkgTree_tt    , nathan_bkgWeight_tt );
  dataloader->AddBackgroundTree(nathan_bkgTree_bbjj    , nathan_bkgWeight_bbjj );
  dataloader->AddBackgroundTree(nathan_bkgTree_ggh    , nathan_bkgWeight_ggh );

  // Set individual event weights (the variables must exist in the original TTree) we have to fix this *dan
   
  dataloader->SetSignalWeightExpression( "scaledWeight3000fb" );
  dataloader->SetBackgroundWeightExpression( "scaledWeight3000fb " );

  // Tell the dataloader how to use the training and testing events
  // If no numbers of events are given, half of the events in the tree are used
  // for training, and the other half for testing:
  //
  // For all events in the samples tree file
  TCut mycut = "";
  //-----------------------------------------------------------------------
  //           DEFINITIVE

    dataloader->PrepareTrainingAndTestTree( mycut, "SplitMode=random:V:VerboseLevel=Verbose" );
      
  //            FAST TESTING
  //
  //------------------------------------------------------------------------

  // For N = 10000 events for training and test:   None, NumEvents,EqualNumEvents
  // TCut mycuts = ""; // leave it empty or for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";    
  // TCut mycutb = ""; // leave it empty or for example: TCut mycutb = "abs(var1)<0.5";                       
  // dataloader->PrepareTrainingAndTestTree( mycuts, mycutb,
  // 					  "nTrain_Signal=10000:nTrain_Background=10000:SplitMode=Random:NormMode=NumEvents:!V" );
  // Specifying testing and training events (recommended)
  // dataloader->PrepareTrainingAndTestTree( mycuts, mycutb,
  // 					  "nTrain_Signal=100000:nTrain_Background=100000:nTest_Signal=100000:nTest_Background=100000:SplitMode=Random:NormMode=NumEvents:!V" );

  // Book MVA methods

  // Cut-based method
  //  factory->BookMethod( dataloader, TMVA::Types::kCuts, "Cuts",
  //		       "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart" );
  // // Decorrelated likelihood
  // factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "LikelihoodD",
  // 		       "!H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=Decorrelate" );
  // // K-Nearest Neighbour classifier (KNN)
  // factory->BookMethod( dataloader, TMVA::Types::kKNN, "KNN",
  // 		       "H:nkNN=20:ScaleFrac=0.8:SigmaFact=1.0:Kernel=Gaus:UseKernel=F:UseWeight=T:!Trim" );

  // BDT method
  // Adaptive Boost                                                        
  //factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT",
	//	       "!H:!V:NTrees=10000:MinNodeSize=0.2%:MaxDepth=12:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
  // Adaptive Boost                                                        
 // factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT_AdaBoost",
 //          (std::string("!H:!V:NTrees=") + tree + ":MinNodeSize=" + minnodesize + ":MaxDepth=" + depth + ":BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=50:DoBoostMonitor=true").c_str());

  factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT",
           (std::string("!H:!V:NTrees=") + tree + ":MinNodeSize=" + minnodesize + ":MaxDepth=" + depth + ":BoostType=RealAdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=50:DoBoostMonitor=true").c_str());

  

  // for final run ncut = -1
  // // Gradient Boost
  //factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG",
  // 		       "!H:!V:NTrees=850:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=2" );

  // Now you can tell the factory to train, test, and evaluate the MVAs                     
  //                                                                                        
  // Train MVAs using the set of training events
  factory->TrainAllMethods();
  
  // Evaluate all MVAs using the set of test events
  factory->TestAllMethods();
  
  // Evaluate and compare performance of all configured MVAs
  factory->EvaluateAllMethods();

  // Save the output
  outputFile->Close();
  
  std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
  std::cout << "==> TMVAClassification is done!" << std::endl;
  
  delete factory;
  delete dataloader;
  
}

void diHiggsTMVAClassification::execute()
{

  // This loads the library
  TMVA::Tools::Instance();
  std::cout << "[diHiggsTMVAClassification :: Finalize]" <<std::endl;
    
}




