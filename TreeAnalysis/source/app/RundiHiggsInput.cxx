// System include(s):
#include <iostream>


// Local include(s):
#include "diHiggsbbyyTreeInput.h"

// ROOT include(s):
#include "TTree.h"
#include "TChain.h"
#include "string.h"
#include "TROOT.h"
#include <sys/wait.h>

const long num_threads = 7;
const bool nathan_analisys = true;
std::string outputFolder = "/data1/Higgs/diHiggs/samples/MichaSamples/samples/";

std::vector<std::string> archivos_na = { "diHiggs_nathan_sgn_yybb_Tree.root",
                                         "diHiggs_nathan_bkg_ybbj_Tree.root" , 
                                         "diHiggs_nathan_bkg_yccj_Tree.root" , 
                                         "diHiggs_nathan_bkg_yybb_Tree.root" , 
                                         "diHiggs_nathan_bkg_yycc_Tree.root" , 
                                         "diHiggs_nathan_bkg_yyjj_Tree.root" , 
                                         "diHiggs_nathan_bkg_yyZbb_Tree.root" , 
                                         "diHiggs_nathan_bkg_bbH_Tree.root" , 
                                         "diHiggs_nathan_bkg_ttH_Tree.root" , 
                                         "diHiggs_nathan_bkg_ZH_Tree.root",
                                         "diHiggs_nathan_bkg_tt_Tree.root",
                                         "diHiggs_nathan_bkg_bbjj_Tree.root",
                                         "diHiggs_nathan_bkg_ggh_Tree.root",
                                         "diHiggs_nathan_bkg_tty_Tree.root"
                                        };

void RundiHiggsbbyyTreeInput(std::string signal,std::string name,int cut,Option Sample,long num_threads,long thread)
{
  diHiggsbbyyTreeInput *diHiggs = new diHiggsbbyyTreeInput(Sample,num_threads,thread);
  
  diHiggs->initialize(nathan_analisys);
  diHiggs->addBranches(signal,name);

  diHiggs->execute(cut);
  diHiggs->finalize();
  delete diHiggs;
  return;
}

int main( int argc, char* argv[] ) {
  if (argc == 4)
  {
    std::string name = std::string(argv[1]);
    std::string signal = std::string(argv[2]);
    name = outputFolder + name + "/" ;
    int cut = atoi(argv[3]);
    int status;
    pid_t pide;
    
    boost::progress_timer t;
    
    system((std::string("mkdir ")+ std::string(name)).c_str());
    system((std::string("chmod 777 ")+ std::string(name)).c_str());
    
    //std::thread t[num_threads];
    pid_t pid[num_threads];
    
    for (long thread = 0; thread < num_threads; ++thread){
      pid[thread] = fork();
      if (pid[thread] == 0){
        RundiHiggsbbyyTreeInput(signal,name,cut, nathan_sgn_yybb,num_threads,thread);
        RundiHiggsbbyyTreeInput(signal,name,cut,nathan_bkg_ybbj,num_threads,thread);
        RundiHiggsbbyyTreeInput(signal,name,cut,nathan_bkg_yccj,num_threads,thread);
        RundiHiggsbbyyTreeInput(signal,name,cut,nathan_bkg_yybb,num_threads,thread); 
        RundiHiggsbbyyTreeInput(signal,name,cut,nathan_bkg_yycc,num_threads,thread);  
        RundiHiggsbbyyTreeInput(signal,name,cut,nathan_bkg_yyjj,num_threads,thread);
        RundiHiggsbbyyTreeInput(signal,name,cut,nathan_bkg_yyZbb,num_threads,thread);
        RundiHiggsbbyyTreeInput(signal,name,cut,nathan_bkg_bbH,num_threads,thread);
        RundiHiggsbbyyTreeInput(signal,name,cut,nathan_bkg_ttH,num_threads,thread);  
        RundiHiggsbbyyTreeInput(signal,name,cut,nathan_bkg_ZH,num_threads,thread);
        RundiHiggsbbyyTreeInput(signal,name,cut,nathan_bkg_tt,num_threads,thread);
        RundiHiggsbbyyTreeInput(signal,name,cut,nathan_bkg_bbjj,num_threads,thread);
        RundiHiggsbbyyTreeInput(signal,name,cut,nathan_bkg_ggh,num_threads,thread);
        RundiHiggsbbyyTreeInput(signal,name,cut,nathan_bkg_tty,num_threads,thread);
        std::cout << "LLego el thread :" << thread <<" al final.\n";
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
      system((std::string("$ROOTSYS/bin/hadd -f ") + name + archivos_na[i] +  " " + name + archivos_na[i] + std::string("*")).c_str());
      std::cout << "Removing "<< archivos_na[i] <<"\n";
      for (int j = 0; j < num_threads; ++j)
      {
        std::remove(((name  + archivos_na[i]) + std::to_string(j)).c_str());
      }
    }
    // Return gracefully:
    return 0;
  }
  else
  {
    printf("Usage : ./RundiHiggsInput [name] [signal] [cut]\n name: name of the new folder \n signal: file of signal to use (absolute)\n cut: cut to use (3 default)\n");
    return 0;
  }
}

