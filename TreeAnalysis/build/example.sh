
./RundiHiggsInput test_run /data1/Higgs/diHiggs/samples/NathanSamples/PixelTDR/MadGraphPythia8EvtGen_A14NNPDF23LO_sm_hh_yybb.merge.DAOD_TRUTH1V3/mc15_14TeV.341559.MadGraphPythia8EvtGen_A14NNPDF23LO_sm_hh_yybb.merge.DAOD_TRUTH1.e5268_p2613_FinalV3.root 3

./RundiHiggsSubsampler test_run

./RunTMVAClassification test_run 1 100 6 2.5%

./RunTMVATree test_run

./RundiHiggs test_run 54
