// System include(s):
#include <iostream>

// Local include(s):
#include "diHiggsTMVATree.h"

// ROOT include(s):
#include "TTree.h"
#include "TChain.h"
#include "TROOT.h"
#include <sys/wait.h>



const long num_threads = 6 ;
const bool nathan_analisys = true;
std::string outputFolder = "/data1/Higgs/diHiggs/samples/MichaSamples/samples/";

std::vector<std::string> archivos_na = {"diHiggs_nathan_sgn_yybb_BDT.root", 
                                        "diHiggs_nathan_bkg_ybbj_BDT.root",
                                        "diHiggs_nathan_bkg_yccj_BDT.root",
                                        "diHiggs_nathan_bkg_yybb_BDT.root",
                                        "diHiggs_nathan_bkg_yycc_BDT.root",
                                        "diHiggs_nathan_bkg_yyjj_BDT.root",
                                        "diHiggs_nathan_bkg_yyZbb_BDT.root",
                                        "diHiggs_nathan_bkg_bbH_BDT.root",
                                        "diHiggs_nathan_bkg_ttH_BDT.root",
                                        "diHiggs_nathan_bkg_ZH_BDT.root",
                                        //"diHiggs_nathan_bkg_tt_BDT.root",
                                        "diHiggs_nathan_bkg_bbjj_BDT.root",
                                        "diHiggs_nathan_bkg_ggh_BDT.root"
                                        //,"diHiggs_nathan_bkg_tty_BDT.root"
                                      };
                                        


void RundiHiggsTMVATree(Option Sample,long num_threads,long thread,std::string name,int var_cut){
  
  diHiggsTMVATree *diHiggsTMVA = new diHiggsTMVATree(Sample,num_threads,thread);
 
  diHiggsTMVA->initialize(nathan_analisys);
  diHiggsTMVA->addBranches(name,var_cut);
  diHiggsTMVA->execute();
  delete diHiggsTMVA;

  return;
}

int main( int argc, char* argv[] ) {
  if (argc == 3)
  {
    std::string name = std::string(argv[1]);
    name = outputFolder + name + "/" ;
    int var_cut = atoi(argv[2]);
    boost::progress_timer t;
    pid_t pid[num_threads];
    int status;
    pid_t pide;

    for (long thread = 0; thread < num_threads; ++thread)
    {
          pid[thread] = fork();
          if (pid[thread] == 0){
          RundiHiggsTMVATree(nathan_sgn_yybb,num_threads,thread,name,var_cut);
          RundiHiggsTMVATree(nathan_bkg_ybbj,num_threads,thread,name,var_cut);
          RundiHiggsTMVATree(nathan_bkg_yccj,num_threads,thread,name,var_cut);
          RundiHiggsTMVATree(nathan_bkg_yybb,num_threads,thread,name,var_cut);
          RundiHiggsTMVATree(nathan_bkg_yycc,num_threads,thread,name,var_cut);
          RundiHiggsTMVATree(nathan_bkg_yyjj,num_threads,thread,name,var_cut);
          RundiHiggsTMVATree(nathan_bkg_yyZbb,num_threads,thread,name,var_cut);
          RundiHiggsTMVATree(nathan_bkg_bbH,num_threads,thread,name,var_cut);
          RundiHiggsTMVATree(nathan_bkg_ttH,num_threads,thread,name,var_cut);
          RundiHiggsTMVATree(nathan_bkg_ZH,num_threads,thread,name,var_cut);
          //RundiHiggsTMVATree(nathan_bkg_tt,num_threads,thread,name,var_cut);
          RundiHiggsTMVATree(nathan_bkg_bbjj,num_threads,thread,name,var_cut);
          RundiHiggsTMVATree(nathan_bkg_ggh,num_threads,thread,name,var_cut);
          //RundiHiggsTMVATree(nathan_bkg_tty,num_threads,thread,name,var_cut);
          exit(0);
        }

    }

    while ((pide = wait(&status)) != -1){/* NO OP */}
    std::cout << "------------------------------------------------------------------------\n";
    std::cout << "         mergin Files\n";
    std::cout << "------------------------------------------------------------------------\n";
    for (unsigned int i = 0; i < archivos_na.size(); ++i)
    { 
        std::cout << "Mergin "<< archivos_na[i] <<"\n";
        system((std::string("$ROOTSYS/bin/hadd -f ") + name + archivos_na[i] + " " + name + archivos_na[i] + std::string("*")).c_str());
        std::cout << "Removing "<< archivos_na[i] <<"\n";
        for (int j = 0; j < num_threads; ++j)
        {
          std::remove((name + archivos_na[i] + std::to_string(j)).c_str());
        }
    }
    // Return gracefully:
  }
  else{printf("Usage: ./RunTMVATree [name] [var_cut]\n");}
  return 0;
}



























