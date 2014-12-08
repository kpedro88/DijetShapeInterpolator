
#ifndef _LINESHAPE_PDF_GG_H
#define _LINESHAPE_PDF_GG_H


#include "Math/Interpolator.h"
#include "shape_gg.h"
   
//Resonance Shape of any mass value using Interpolation technique 
//Author: Sertac Ozturk
// sertac@fnal.gov,  sertac.ozturk@cern.ch


void LineShape_pdf(double mass){
	setArray(mass);
}


void setArray (double mass){ 
	 for(int ind=0;ind<nMassBins; ind++){
             double bin_width;		 
             double mjj = (massBoundaries[ind]+massBoundaries[ind+1])/2;
             if(mjj>1.5*mass) FoundQstarBinnedProb[ind] = 0.;
	// Create a vector and fill it with variable x bins according to entered mass value
	     else{
	         for(int i=0;i<103; i++){
		    massnew[i] = massBoundaries[i]/mass;
		    if(massBoundaries[i]<=mjj && massBoundaries[i+1]>=mjj) bin_width = binwidth[i];
		    if(massnew[i]<=1.52 && massnew[i]>=0.){ // x distribution is from 0. to 1.5
		    v.push_back(massnew[i]);
		}
	}
	
	const unsigned int s = v.size();
	
	// Definition of arrays with variable bins 
	double bins[1000]; // variable bins for x distribution
	double m[1000]; // variable mass bins for dijet mass distribution
	double dndm[1000];
	double prob[1000];
	
	
	// Fill the bin values to array
	for(int j=0; j<v.size(); j++){
		bins[j] = v[j];
		m[j] = v[j] * mass;
	}
	
	// Definition of histograms
	TH1F* h_new2 = new TH1F("h_new2","with variale bins2",s-1 , m); // Histogram for dijet mass distribution with variable mass bins
	
	if(mass == mqstar[0]){ // If mass = 0.5 TeV
		for(int k=0; k<n; k++){
			x[k] = bincenter[k];
			y[k] = y500[k];
		}
	}
	
	if(mass == mqstar[1]){ // If mass = 1 TeV
		for(int k=0; k<n; k++){
			x[k] = bincenter[k];
			y[k] = y1000[k];}
	}
	
	if(mass == mqstar[2]){ // If mass = 2 TeV
		for(int k=0; k<n; k++){
			x[k] = bincenter[k];
			y[k] = y2000[k];}
	}
	
	if(mass == mqstar[3]){ // If mass = 3 TeV
		for(int k=0; k<n; k++){
			x[k] = bincenter[k];
			y[k] = y3000[k];}
	}
	
	if(mass == mqstar[4]){ // If mass = 4 TeV
		for(int k=0; k<n; k++){
			x[k] = bincenter[k];
			y[k] = y4000[k];}
	}

        if(mass == mqstar[5]){ // If mass = 5 TeV
                for(int k=0; k<n; k++){
                        x[k] = bincenter[k];
                        y[k] = y5000[k];}
        }
	
       if(mass == mqstar[6]){ // If mass = 6 TeV
                for(int k=0; k<n; k++){
                        x[k] = bincenter[k];
                        y[k] = y6000[k];}
        }

       if(mass == mqstar[7]){ // If mass = 7 TeV
                for(int k=0; k<n; k++){
                        x[k] = bincenter[k];
                        y[k] = y7000[k];}
        } 

       if(mass == mqstar[8]){ // If mass = 8 TeV
                for(int k=0; k<n; k++){
                        x[k] = bincenter[k];
                        y[k] = y8000[k];}
        }

       if(mass == mqstar[9]){ // If mass = 9 TeV
                for(int k=0; k<n; k++){
                        x[k] = bincenter[k];
                        y[k] = y9000[k];}
        }

	// Calculate and create new x distribution with fixed bins at entered mass value which is between 0.5 TeV and 1 TeV
	if((mass > mqstar[0] && mass < mqstar[1]) || mass < mqstar[0]){ 
		for(int k=0; k<n; k++){
			double bincont1 = y500[k];
			double bincont2 = y1000[k];
			double Mjj1 = mqstar[0];
			double Mjj2 = mqstar[1];
			double Mq = mass;
			double norm = (Mq - Mjj1)/(Mjj2 - Mjj1);
			double eff = bincont2 - bincont1;
			double neff = eff * norm;
			double mqstar1 = bincont1 + neff;
			y[k] = mqstar1;
			x[k] = bincenter[k];}
	}
	
	// Calculate and create new x distribution with fixed bins at entered mass value which is between 1 TeV and 2 TeV. 
	if(mass > mqstar[1] && mass < mqstar[2]){
		for(int k=0; k<n; k++){
			double bincont1 = y1000[k];
			double bincont2 = y2000[k];
			double Mjj1 = mqstar[1];
			double Mjj2 = mqstar[2];
			double Mq = mass;
			double norm = (Mq - Mjj1)/(Mjj2 - Mjj1);
			double eff = bincont2 - bincont1;
			double neff = eff * norm;
			double mqstar1 = bincont1 + neff;
			y[k] = mqstar1;
			x[k] = bincenter[k];}
	}
	
	// Calculate and create new x distribution with fixed bins at entered mass value which is between 2 TeV and 3 TeV. 
	if(mass > mqstar[2] && mass < mqstar[3]){
        for(int k=0; k<n; k++){
			double bincont1 = y2000[k];
			double bincont2 = y3000[k];
			double Mjj1 = mqstar[2];
			double Mjj2 = mqstar[3];
			double Mq = mass;
			double norm = (Mq - Mjj1)/(Mjj2 - Mjj1);
			double eff = bincont2 - bincont1;
			double neff = eff * norm;
			double mqstar1 = bincont1 + neff;
			y[k] = mqstar1;
			x[k] = bincenter[k];}
	}

	// Calculate and create new x distribution with fixed bins at entered mass value which is between 3 TeV and 4 TeV.
	if(mass > mqstar[3] && mass < mqstar[4]){
        for(int k=0; k<n; k++){
                        double bincont1 = y3000[k];
                        double bincont2 = y4000[k];
                        double Mjj1 = mqstar[3];
                        double Mjj2 = mqstar[4];
                        double Mq = mass;
                        double norm = (Mq - Mjj1)/(Mjj2 - Mjj1);
                        double eff = bincont2 - bincont1;
                        double neff = eff * norm;
                        double mqstar1 = bincont1 + neff;
                        y[k] = mqstar1;
                        x[k] = bincenter[k];}
        }

        // Calculate and create new x distribution with fixed bins at entered mass value which is between 4 TeV and 5 TeV.
        if(mass > mqstar[4] && mass < mqstar[5]){
        for(int k=0; k<n; k++){
                        double bincont1 = y4000[k];
                        double bincont2 = y5000[k];
                        double Mjj1 = mqstar[4];
                        double Mjj2 = mqstar[5];
                        double Mq = mass;
                        double norm = (Mq - Mjj1)/(Mjj2 - Mjj1);
                        double eff = bincont2 - bincont1;
                        double neff = eff * norm;
                        double mqstar1 = bincont1 + neff;
                        y[k] = mqstar1;
                        x[k] = bincenter[k];}
        }

       // Calculate and create new x distribution with fixed bins at entered mass value which is between 5 TeV and 6 TeV.
       if(mass > mqstar[5] && mass < mqstar[6]){
        for(int k=0; k<n; k++){
                        double bincont1 = y5000[k];
                        double bincont2 = y6000[k];
                        double Mjj1 = mqstar[5];
                        double Mjj2 = mqstar[6];
                        double Mq = mass;
                        double norm = (Mq - Mjj1)/(Mjj2 - Mjj1);
                        double eff = bincont2 - bincont1;
                        double neff = eff * norm;
                        double mqstar1 = bincont1 + neff;
                        y[k] = mqstar1;
                        x[k] = bincenter[k];}
        }  

        // Calculate and create new x distribution with fixed bins at entered mass value which is between 6 TeV and 7 TeV.
        if(mass > mqstar[6] && mass < mqstar[7]){
        for(int k=0; k<n; k++){
                        double bincont1 = y6000[k];
                        double bincont2 = y7000[k];
                        double Mjj1 = mqstar[6];
                        double Mjj2 = mqstar[7];
                        double Mq = mass;
                        double norm = (Mq - Mjj1)/(Mjj2 - Mjj1);
                        double eff = bincont2 - bincont1;
                        double neff = eff * norm;
                        double mqstar1 = bincont1 + neff;
                        y[k] = mqstar1;
                        x[k] = bincenter[k];}
        }

       // Calculate and create new x distribution with fixed bins at entered mass value which is between 7 TeV and 8 TeV.
       if(mass > mqstar[7] && mass < mqstar[8]){
       for(int k=0; k<n; k++){
                        double bincont1 = y7000[k];
                        double bincont2 = y8000[k];
                        double Mjj1 = mqstar[7];
                        double Mjj2 = mqstar[8];
                        double Mq = mass; 
                        double norm = (Mq - Mjj1)/(Mjj2 - Mjj1);
                        double eff = bincont2 - bincont1;
                        double neff = eff * norm;
                        double mqstar1 = bincont1 + neff;
                        y[k] = mqstar1;
                        x[k] = bincenter[k];}
        }  

	// Calculate and create new x distribution with fixed bins at entered mass value which is between 8 TeV and 9 TeV. 
	if((mass > mqstar[8] && mass < mqstar[9]) || mass > mqstar[9]){
	for(int k=0; k<n; k++){
			double bincont1 = y8000[k];
			double bincont2 = y9000[k];
			double Mjj1 = mqstar[8];
			double Mjj2 = mqstar[9];
			double Mq = mass;
			double norm = (Mq - Mjj1)/(Mjj2 - Mjj1);
			double eff = bincont2 - bincont1;
			double neff = eff * norm;
			double mqstar1 = bincont1 + neff;
			y[k] = mqstar1;
			x[k] = bincenter[k];}
	}	
	
	// Interpolation tecnique is used to convert distribution in x to distribution in dijet mass with variable bins
	ROOT::Math::Interpolator inter(n, ROOT::Math::Interpolation::kCSPLINE); // If CSPLINE is not valid, please use kCSPLINE
	inter.SetData(n, x, y);
	
	// Generate the new distribution in x with variable bins
	for(int t=0; t<n; t++){
		f[t] = inter.Eval(x[t]);} 
	
	//  int bin_number = h_new->GetNbinsX();
	for(int z=0; z<s; z++){
		double bin = inter.Integ(v[z], v[z+1]); 
		dndm[z] = bin;
		h_new2->SetBinContent(z+1,bin); // histogram in dijet mass distribution with variable bins
	}
	
	v.clear();
	
	double integ = h_new2->Integral();
	h_new2->Delete();
	
	for(int p=0; p<s; p++){
		double nor = dndm[p] / integ;
		prob[p] = nor;
		if(m[p]<mjj && m[p+1]>=mjj){
		FoundQstarBinnedProb[ind] = prob[p];	
	    }
	  }
       }
    }	
 };


// This gets the qstar binned probability faster than the original rountine
Double_t FastQstarBinnedProb(Double_t mjj )
{
    int bin=0;
    int binFound=0;
    for(int i=0;i<nMassBins && binFound==0; i++){
		if(massBoundaries[i+1]>mjj){
			binFound=1;
			bin=i;
		}
    }
    if(FoundQstarBinnedProb[bin]<0.) return 0.;
    else return FoundQstarBinnedProb[bin];
}


#endif
