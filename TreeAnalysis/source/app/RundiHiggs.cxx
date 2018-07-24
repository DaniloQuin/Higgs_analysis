// System include(s):
#include <iostream>
#include <vector>

// Local include(s):
#include "diHiggsbbyyTreeAnalysis.h"

// ROOT include(s):
#include "TTree.h"
#include "math.h"
#include "TApplication.h"
#include "TH1.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TStyle.h"
#include <omp.h>

const float x_min = 0.5;
const float x_max = 0.6;
const bool nathan_analisys = true;
const int num_threads = 6;
const float min_signal = 5;
std::string outputFolder = "/data1/Higgs/diHiggs/samples/MichaSamples/samples/";

void RundiHiggsbbyyTreeAnalysis(Option Sample,float dt,std::vector<float> *vect,std::string name){

  boost::progress_timer t;  // start timing0.125

  diHiggsbbyyTreeAnalysis *diHiggs = new diHiggsbbyyTreeAnalysis(Sample);
  
  diHiggs->initialize(nathan_analisys,dt,vect);
  diHiggs->addBranches(name);
  diHiggs->execute();
  diHiggs->finalize();
  delete diHiggs;


}

int main( int argc, char* argv[] ) {
  if ((argc == 3 && atoi(argv[2]) != 1) || argc == 4)
  {
    std::string name = std::string(argv[1]);
    name = outputFolder + name + "/" ;
    int bining = atoi(argv[2]);
    float mva_sens = 0;
    if (argc == 4){mva_sens = atof(argv[3]);}
    
    //signal sample  
    TApplication* rootapp = new TApplication("histogramas",&argc, argv);

    std::vector<float> *count_sig = new std::vector<float>(); 


    //background samples 
    std::vector<float> *count_bkg1 = new std::vector<float>();  
    std::vector<float> *count_bkg2 = new std::vector<float>(); 
    std::vector<float> *count_bkg3 = new std::vector<float>();
    std::vector<float> *count_bkg4 = new std::vector<float>();
    std::vector<float> *count_bkg5 = new std::vector<float>();
    std::vector<float> *count_bkg6 = new std::vector<float>();
    std::vector<float> *count_bkg7 = new std::vector<float>();
    std::vector<float> *count_bkg8 = new std::vector<float>();
    std::vector<float> *count_bkg9 = new std::vector<float>();
    std::vector<float> *count_bkg10 = new std::vector<float>();
    std::vector<float> *count_bkg11 = new std::vector<float>();
    std::vector<float> *count_bkg12 = new std::vector<float>();
    std::vector<float> *count_bkg13 = new std::vector<float>();

   
    TH1F *sen = new TH1F("sen","Senal",bining,x_min,x_max);
    TH1F *boc = new TH1F("boc","Background",bining,x_min,x_max);
    TH1F *back = new TH1F("bac","S/sqrt(B)",bining,x_min,x_max);
    TH1F *back1 = new TH1F("bac1","Asimov",bining,x_min,x_max);

    sen->SetMarkerStyle(3);
    sen->SetMarkerSize(1.2);
    sen->SetMarkerColor(kBlue);
    
    back->SetMarkerStyle(3);
    back->SetMarkerSize(1.2);
    back->SetMarkerColor(kRed);
    
    back1->SetMarkerStyle(3);
    back1->SetMarkerSize(1.2);
    back1->SetMarkerColor(kYellow);
    
    boc->SetMarkerStyle(3);
    boc->SetMarkerSize(1.2);
    boc->SetMarkerColor(kViolet);
    
    std::cout<<"-----------------------------------------------------\n";

    if (bining!=1){
      omp_lock_t writelock;
      omp_init_lock(&writelock);
      float temp_sa = 0;
      float temp1_sa = 0;
      float sense_sa = 0;
      int cut_sa = 0;

      #pragma omp parallel num_threads(num_threads)
      #pragma omp for

      for (int i = 1; i < bining+1; ++i){
        ROOT::EnableThreadSafety();
        std::vector<float> *count_sig_t = new std::vector<float>(); 
        float temp = 0;
        float temp1 = 0;

        //background samples 
        std::vector<float> *count_bkg1_t = new std::vector<float>();
        std::vector<float> *count_bkg2_t = new std::vector<float>();
        std::vector<float> *count_bkg3_t = new std::vector<float>();
        std::vector<float> *count_bkg4_t = new std::vector<float>();
        std::vector<float> *count_bkg5_t = new std::vector<float>();
        std::vector<float> *count_bkg6_t = new std::vector<float>();
        std::vector<float> *count_bkg7_t = new std::vector<float>();
        std::vector<float> *count_bkg8_t = new std::vector<float>();
        std::vector<float> *count_bkg9_t = new std::vector<float>();
        std::vector<float> *count_bkg10_t = new std::vector<float>();
        std::vector<float> *count_bkg11_t = new std::vector<float>();
        std::vector<float> *count_bkg12_t = new std::vector<float>();
        std::vector<float> *count_bkg13_t = new std::vector<float>();

        RundiHiggsbbyyTreeAnalysis(nathan_sgn_yybb,sen->GetBinCenter(i),count_sig_t,name);
        RundiHiggsbbyyTreeAnalysis(nathan_bkg_ybbj,sen->GetBinCenter(i),count_bkg1_t,name);
        RundiHiggsbbyyTreeAnalysis(nathan_bkg_yccj,sen->GetBinCenter(i),count_bkg2_t,name);
        RundiHiggsbbyyTreeAnalysis(nathan_bkg_yybb,sen->GetBinCenter(i),count_bkg3_t,name);
        RundiHiggsbbyyTreeAnalysis(nathan_bkg_yycc,sen->GetBinCenter(i),count_bkg4_t,name);
        RundiHiggsbbyyTreeAnalysis(nathan_bkg_yyjj,sen->GetBinCenter(i),count_bkg5_t,name);
        RundiHiggsbbyyTreeAnalysis(nathan_bkg_yyZbb,sen->GetBinCenter(i),count_bkg6_t,name);
        RundiHiggsbbyyTreeAnalysis(nathan_bkg_bbH,sen->GetBinCenter(i),count_bkg7_t,name);
        RundiHiggsbbyyTreeAnalysis(nathan_bkg_ttH,sen->GetBinCenter(i),count_bkg8_t,name);
        RundiHiggsbbyyTreeAnalysis(nathan_bkg_ZH,sen->GetBinCenter(i),count_bkg9_t,name);  
        //RundiHiggsbbyyTreeAnalysis(nathan_bkg_tt,sen->GetBinCenter(i),count_bkg10_t,name);
        RundiHiggsbbyyTreeAnalysis(nathan_bkg_bbjj,sen->GetBinCenter(i),count_bkg11_t,name);
        RundiHiggsbbyyTreeAnalysis(nathan_bkg_ggh,sen->GetBinCenter(i),count_bkg12_t,name);
        //RundiHiggsbbyyTreeAnalysis(nathan_bkg_tty,sen->GetBinCenter(i),count_bkg13_t,name);
        
        temp = (*count_sig_t)[8];
        temp1 = (*count_bkg1_t)[8];
        temp1 += (*count_bkg2_t)[8];
        temp1 += (*count_bkg3_t)[8];
        temp1 += (*count_bkg4_t)[8];
        temp1 += (*count_bkg5_t)[8];
        temp1 += (*count_bkg6_t)[8];
        temp1 += (*count_bkg7_t)[8];
        temp1 += (*count_bkg8_t)[8];
        temp1 += (*count_bkg9_t)[8];
        //temp1 += (*count_bkg10_t)[8];
        temp1 += (*count_bkg11_t)[8];
        temp1 += (*count_bkg12_t)[8];
        //temp1 += (*count_bkg13_t)[8];
        std::cout << "(*count_sig_t)[8]" <<"\n"; 
        sen->SetBinContent(i,temp);
        boc->SetBinContent(i,temp1);
        
        if (temp1!=0 && temp != 0){  
         back->SetBinContent(i, temp/sqrt(temp1));
         back1->SetBinContent(i,sqrt(2*((temp+temp1)*log(1+temp/temp1)-temp)));
         std::cout <<  temp/sqrt(temp1) << "\n";
        }

        for (int j = 0; j < 9; ++j){
          temp = (*count_sig_t)[j];
          temp1 = (*count_bkg1_t)[j];
          temp1 += (*count_bkg2_t)[j];
          temp1 += (*count_bkg3_t)[j];
          temp1 += (*count_bkg4_t)[j];
          temp1 += (*count_bkg5_t)[j];
          temp1 += (*count_bkg6_t)[j];
          temp1 += (*count_bkg7_t)[j];
          temp1 += (*count_bkg8_t)[j];
          temp1 += (*count_bkg9_t)[j];
          //temp1 += (*count_bkg10_t)[j];
          temp1 += (*count_bkg11_t)[j];
          temp1 += (*count_bkg12_t)[j];
          //temp1 += (*count_bkg13_t)[j];
          omp_set_lock(&writelock);

          if (sense_sa == 0 || ( sqrt(2*((temp_sa+temp1_sa)*log(1+temp_sa/temp1_sa)-temp_sa)) < sqrt(2*((temp+temp1)*log(1+temp/temp1)-temp)) && temp > 5)){
            temp_sa = temp;
            temp1_sa = temp1;
            sense_sa = sen->GetBinCenter(i);
            cut_sa = j;
          }
          omp_unset_lock(&writelock);
        }
        
        }

        omp_destroy_lock(&writelock);

        std::cout << "BDT sense " << sense_sa << " corte " << cut_sa <<"  S " << temp_sa << " ,B " << temp1_sa <<" , S/sqrt(B+S) : " << temp_sa/sqrt(temp1_sa+temp_sa) << "   |    S/sqrt(B) : " <<  temp_sa/sqrt(temp1_sa)  << "   |    asimov : " << sqrt(2*((temp_sa+temp1_sa)*log(1+temp_sa/temp1_sa)-temp_sa)) << "\n";

        TCanvas *c1 = new TCanvas("c1", "transparent pad",200,32,700,500);
        TPad *pad1 = new TPad("pad1","",0,0,1,1);
        TPad *pad2 = new TPad("pad2","",0,0,1,1);
        
        pad2->SetFillColor(0);
        pad2->SetFillStyle(4000);
        pad2->SetFrameFillStyle(0);

        pad1->Draw();
        pad1->cd();
        
        boc->GetYaxis()->SetTitle("Number of events");
        boc->Draw("P0");
        
        sen->Draw("P0 same");

        gStyle->SetOptTitle(0);
        gStyle->SetOptStat(0);
        
        pad1->Draw();
        pad2->Draw();
        pad2->cd();
        
        back->GetYaxis()->SetTitle("Significance");
        back->GetYaxis()->SetTitleOffset(0.9);
        back->GetXaxis()->SetTitle("BDT Response");
        back->GetYaxis()->SetRangeUser(0., 5.);
        back1->GetYaxis()->SetRangeUser(0., 5.);
        back->Draw("P0 Y+");
        back1->Draw("P0 Y+ same");
        c1->SaveAs((name + "hist1.pdf").c_str());
        //rootapp->Run();
      }
      else{
        
        float temp = 0;
        float temp1 = 0;
        
        RundiHiggsbbyyTreeAnalysis(nathan_sgn_yybb,mva_sens,count_sig,name);
        RundiHiggsbbyyTreeAnalysis(nathan_bkg_ybbj,mva_sens,count_bkg1,name);
        RundiHiggsbbyyTreeAnalysis(nathan_bkg_yccj,mva_sens,count_bkg2,name);
        RundiHiggsbbyyTreeAnalysis(nathan_bkg_yybb,mva_sens,count_bkg3,name);
        RundiHiggsbbyyTreeAnalysis(nathan_bkg_yycc,mva_sens,count_bkg4,name);
        RundiHiggsbbyyTreeAnalysis(nathan_bkg_yyjj,mva_sens,count_bkg5,name);
        RundiHiggsbbyyTreeAnalysis(nathan_bkg_yyZbb,mva_sens,count_bkg6,name);
        RundiHiggsbbyyTreeAnalysis(nathan_bkg_bbH,mva_sens,count_bkg7,name);
        RundiHiggsbbyyTreeAnalysis(nathan_bkg_ttH,mva_sens,count_bkg8,name);
        RundiHiggsbbyyTreeAnalysis(nathan_bkg_ZH,mva_sens,count_bkg9,name); 
        RundiHiggsbbyyTreeAnalysis(nathan_bkg_tt,mva_sens,count_bkg10,name);
        RundiHiggsbbyyTreeAnalysis(nathan_bkg_bbjj,mva_sens,count_bkg11,name);
        RundiHiggsbbyyTreeAnalysis(nathan_bkg_ggh,mva_sens,count_bkg12,name);
        RundiHiggsbbyyTreeAnalysis(nathan_bkg_tty,mva_sens,count_bkg13,name);
        
        for (int i = 0; i < 9; ++i){
          temp =   (*count_sig)[i];
          temp1 =  (*count_bkg1)[i];
          temp1 += (*count_bkg2)[i];
          temp1 += (*count_bkg3)[i];
          temp1 += (*count_bkg4)[i];
          temp1 += (*count_bkg5)[i];
          temp1 += (*count_bkg6)[i];
          temp1 += (*count_bkg7)[i];
          temp1 += (*count_bkg8)[i];
          temp1 += (*count_bkg9)[i];
          temp1 += (*count_bkg10)[i];
          temp1 += (*count_bkg11)[i];
          temp1 += (*count_bkg12)[i];
          temp1 += (*count_bkg13)[i];
        
          std::cout << i <<") S " << temp << " ,B " << temp1 <<" , S/sqrt(B+S) : " << temp/sqrt(temp1+temp) << "   |    S/sqrt(B) : " <<  temp/sqrt(temp1)  << "   |    asimov : " << sqrt(2*((temp+temp1)*log(1+temp/temp1)-temp)) << "\n";
          std::cout<<"-----------------------------------------------------\n";
        }
      }
  }
  else{printf("Usage: ./RundiHiggs [name] [binnin != 1] or ./RundiHiggs [name] [binnin = 1] [bdt_sense] \n");}
  // Return gracefully:
  return 0;
}

