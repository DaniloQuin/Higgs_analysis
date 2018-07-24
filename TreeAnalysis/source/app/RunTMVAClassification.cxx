// System include(s):
#include <iostream>

// Local include(s):
#include "diHiggsTMVAClassification.h"

// ROOT include(s):
#include "TTree.h"

const bool nathan_analisys = true;
std::string outputFolder = "/data1/Higgs/diHiggs/samples/MichaSamples/samples/";

int main( int argc, char* argv[] ) {

	if (argc == 7)
	{
		std::string name = std::string(argv[1]);
		name = outputFolder + name + "/" ;
		int Fast = atoi(argv[2]);

		std::string tree = argv[3];
		std::string depth = argv[4];
		std::string minodesize = argv[5];
		
		int var_cut = atoi(argv[6]);
		
	  	boost::progress_timer t;  // start timing

		diHiggsTMVAClassification *diHiggsTMVA = new diHiggsTMVAClassification(nathan_analisys);
		diHiggsTMVA->addMethod(Fast,name,tree,depth,minodesize,var_cut);
		diHiggsTMVA->execute();
	}
	else{printf("Usage: ./RundiHiggsbbyySubsampler [name] [fast(1=yes 0=no)] [number of trees] [depth of tree] [min node size with %% at the end] [number_variable_cut max 29]\n");}

	  // Return gracefully:
	  return 0;
}


