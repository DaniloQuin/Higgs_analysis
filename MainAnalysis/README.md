* Instructions based entirely on Stephane Jezequel/Ben Smart bbyy main package.

1. Download the main (HEAD) bbyy analysis package:
   * svn co svn+ssh://svn.cern.ch/reps/atlasphys-hxp/Physics/Higgs/HiggsProspects/ECFA2016/HHbbgg/AnalysisCode/trunk/ HHbbgg

2. Download the package that  mimic the expected performance of the upgraded ATLAS detectors at the HL-LHC era.
   * mkdir UpgradeSmearingFunctions
   * cd UpgradeSmearingFunctions
   * svn co svn+ssh://svn.cern.ch/reps/atlasoff/PhysicsAnalysis/UpgradePhys/SmearingFunctions/UpgradePerformanceFunctions/tags/UpgradePerformanceFunctions-02-09-05 UpgradePerformanceFunctions
   
3. Include the lines from diHiggsTree_Modifications.txt into /HHyybb/Root/HHyybb_xAODAnalysis.cxx and /HHyybb/HHyybb/HHyybb_xAODAnalysis.h

4. Setup and compile RootCore in the package folder.
   * cd diHiggsbbyyAnalysis
   * source rc_init.sh

5. Run it locally (Legacy method).
   * ./run_script_py.sh
   * Before running you need to change the location of your input files in run_script_py.sh
   * Check the configuration (n.events, etc.) for each sample in file_xsec, and set it up in the executable

* UpgradePerformanceFunctions-02-06-00 for Danilo's thesis (me :D )
