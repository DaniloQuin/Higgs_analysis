// System include(s):
#include <iostream>


// Local include(s):
#include "diHiggsTreeInput_subsample.h"

// ROOT include(s):
#include "TTree.h"
#include "TChain.h"
#include "TROOT.h"
#include "string.h"

const bool nathan_analisys = true;
std::string outputFolder = "/data1/Higgs/diHiggs/samples/MichaSamples/samples/";


void RundiHiggsbbyyTreeInput(Option Sample,std::string name){

  boost::progress_timer t;  // start timing
  diHiggsTreeInput_subsample *diHiggs = new diHiggsTreeInput_subsample(Sample);
  
  diHiggs->initialize(nathan_analisys);
  diHiggs->addBranches(name);

  diHiggs->execute();
  diHiggs->finalize();
  delete diHiggs;
  return;
}

int main( int argc, char* argv[] ) {
	if (argc == 2){
		std::string name = std::string(argv[1]);
		name = outputFolder + name + "/" ;
  		boost::progress_timer t;
	    
	    RundiHiggsbbyyTreeInput(nathan_bkg_ybbj,name);
	    RundiHiggsbbyyTreeInput(nathan_bkg_yccj,name);
	    RundiHiggsbbyyTreeInput(nathan_bkg_yybb,name);
	    RundiHiggsbbyyTreeInput(nathan_bkg_yycc,name);
	    RundiHiggsbbyyTreeInput(nathan_bkg_yyjj,name);
	    RundiHiggsbbyyTreeInput(nathan_bkg_yyZbb,name);
	    RundiHiggsbbyyTreeInput(nathan_bkg_bbH,name);
	    RundiHiggsbbyyTreeInput(nathan_bkg_ttH,name);
	    RundiHiggsbbyyTreeInput(nathan_bkg_ZH,name);
	    //RundiHiggsbbyyTreeInput(nathan_bkg_tt,name);
	    RundiHiggsbbyyTreeInput(nathan_bkg_bbjj,name);
	    RundiHiggsbbyyTreeInput(nathan_bkg_ggh,name);
	    RundiHiggsbbyyTreeInput(nathan_sgn_yybb,name);
	}

	else{printf("Usage: ./RundiHiggsbbyySubsampler [name]\n");}
	return 0;
}

