#include "LineShape_pdf_qg_PU30.h"

void GetResonanceShape_qg()
{

    double resmass;

    TH1D * h_shape[95];
    TH1D * h_pdf[95];
    TH1D * h_cdf[95];

    TFile *output = new TFile("Resonance_Shapes_qg_PU30_13TeV.root","RECREATE");
    
    double m0[96]= {500., 600.,  700., 800., 900., 1000., 1100., 1200., 1300., 1400., 1500., 1600., 1700., 1800., 1900., 2000.,2100.,2200.,2300.,2400.,2500.,2600.,2700.,2800.,2900.,3000.,3100.,3200.,3300.,3400.,3500.,3600.,3700.,3800.,3900.,4000.,4100.,4200.,4300.,4400.,4500., 4600., 4700., 4800., 4900., 5000., 5100., 5200., 5300., 5400., 5500., 5600., 5700., 5800., 5900., 6000., 6100, 6200., 6300., 6400., 6500., 6600., 6700., 6800.. 6900., 7000., 7100., 7200., 7300., 7400., 7500., 7600., 7700., 7800., 7900., 8000., 8100., 8200., 8300., 8400., 8500., 8600., 8700., 8800., 8900., 9000., 9100., 9200., 9300., 9400., 9500., 9600., 9700., 9800., 9900., 10000.};
  
    for(int j=0; j<95; j++){
       resmass = m0[j];
       cout<<resmass<<", ";
       char *histname = new char[100];
       sprintf(histname,"h_qg_%d",resmass);

       h_shape[j] = new TH1D(histname,"qg Resonance Shape",nMassBins,massBoundaries);

       LineShape_pdf(resmass);

       for(int i=0; i<h_shape[j]->GetNbinsX(); i++){
               double mss    =  h_shape[j]->GetBinCenter(i+1);
               double prob   =  FastQstarBinnedProb(mss) ;
		       double w = h_shape[j]->GetBinWidth(i+1);
               h_shape[j]-> SetBinContent(i+1,prob );
       }

       h_shape[j]-> SetXTitle("Dijet Mass (GeV)");
       h_shape[j]-> SetYTitle("Probability");

       output->cd();
       h_shape[j]-> Write();

       // make the histograms
       h_pdf[j]=new TH1D(TString(histname)+"_pdf", "qg Resonance Shape", 14000, 0, 14000);
       h_cdf[j]=new TH1D(TString(histname)+"_cdf", "qg Resonance Shape CDF", 14000, 0, 14000);

       for(int i=1; i<=h_shape[j]->GetNbinsX(); i++){

         int bin_min = h_pdf[j]->GetXaxis()->FindBin(h_shape[j]->GetXaxis()->GetBinLowEdge(i)+0.5);
         int bin_max = h_pdf[j]->GetXaxis()->FindBin(h_shape[j]->GetXaxis()->GetBinUpEdge(i)-0.5);
         double bin_content = h_shape[j]->GetBinContent(i)/double(bin_max-bin_min+1);
         for(int b=bin_min; b<=bin_max; b++){
            h_pdf[j]->SetBinContent(b, bin_content);
         }
       }

       for(int i=1; i<=h_cdf[j]->GetNbinsX(); i++){

         int bin_min = h_pdf[j]->GetXaxis()->FindBin(h_cdf[j]->GetXaxis()->GetBinLowEdge(i)+0.5);
         int bin_max = h_pdf[j]->GetXaxis()->FindBin(h_cdf[j]->GetXaxis()->GetBinUpEdge(i)-0.5);

         double curr = 0;
         for(int b=bin_min; b<=bin_max; b++){
            curr+=h_pdf[j]->GetBinContent(b);
         }

         double prev=h_cdf[j]->GetBinContent(i-1);

         h_cdf[j]->SetBinContent(i, prev+curr);
       }

       output->cd();
       h_cdf[j]->Write();
    }

    output->Close();
 }


