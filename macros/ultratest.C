#include <ROOT/TThreadExecutor.hxx>
#include <iostream>

void ultratest() {
   ROOT::TThreadExecutor t;


   TFile* infile = new TFile("test.root");
   TTree* T = (TTree*)infile->Get("T");

   int nentries = T->GetEntries();

   //Double_t energy[64][32]={-10};

   Double_t energy[32] = {0};
   Float_t sume = 0;
   



   // T->SetBranchAddress("adc_counts[64][32]",&energy);
   T->SetBranchAddress("electron_adc_counts[32]",energy);
   T->SetBranchAddress("sum_E",&sume);






   // float energy2[32] = {0};
   // auto branch = T2->Branch("scaled_electron_adc_counts",&energy2,"float[32]");

   

   TF1* f_tmp = new TF1("f_tmp","landau(0)",0,20);

   TH2D *h_electrons = new TH2D("h_electrons","",31,0,31,500,0,0.5);

   TH2D* h_shifted = new TH2D("h_shifted","",279,0,31,500,0,0.5);

   TH1D* h_tmp = new TH1D("h_tmp","",31,0,31);

   for (int q = 0; q < nentries;q++)
     {
       T->GetEntry(q);
       int maxbin = 0;
       double maxval = 0;
       for (int k = 0; k < 31;k++)
	 {
	   if (energy[k] > maxval)
	     {
	       maxbin = k;
	       maxval = energy[k];
	     }
	 }

       bool pileup = false;
	     
       for (int k = maxbin+1; k < 31;k++)
	 {
	   if ( energy[k] > 1.05 * energy[k-1])
	     {
	       pileup = true;
	     }
	 }
       
       if (pileup == true ) {continue;}




       int binshift = maxbin - 6;



       for (int k = 0;k < 31;k++)
	 {
	   
	   h_electrons->Fill(k-binshift,energy[k]);
	   if (maxval > 3000)
	     {
	   h_tmp->SetBinContent(k-binshift+1,energy[k]);
	     }
	 }
       
      
       // h_tmp->Fit(f_tmp,"Q0","",4,10);
       
       

       // if (maxval > 0 )
       // 	 {
       // 	   h_tmp->Fit(f_tmp,"Q0","",4,10);

       // 	   double landauhalfmax = f_tmp->GetMaximum()/2;
       // 	   double maxlocation = f_tmp->GetMaximumX();
       // 	   double landau_halfmax = f_tmp->GetX(landauhalfmax,4,maxlocation);
	   
       // 	   if (f_tmp->GetChisquare()/f_tmp->GetNDF() > 1.2 ) {continue;}
       // 	   cout <<f_tmp->GetMaximum() << " ,  " << maxlocation << " , " << landau_halfmax << endl;


       // 	   double halfmax = h_tmp ->GetMaximum()/2.0;
       // 	   double bina = h_tmp->GetBinContent(5);
       // 	   double binb = h_tmp->GetBinContent(6);
	   
       // 	   double fracbin = (halfmax - bina ) / ( binb - bina);
	   
       // 	   cout << halfmax << " , " << bina << " , " << binb << " , " << fracbin <<  " , " << endl;
       // 	   for (int k = 0;k < 31;k++)
       // 	     {
       // 	       h_shifted->Fill(k-binshift-(landau_halfmax - 5),energy[k]);
       // 	     }
       // 	 }
       // cout << energy[29][6] << endl;;
     
       
       
     }


   TProfile* profile = (TProfile*)h_shifted->ProfileX("profile");

   TCanvas*c5 = new TCanvas("c5","",700,500);
   h_electrons->Draw("COLZ");
   // TFile * outfile = new TFile("simplifiedtree.root","RECREATE");
   // T2->Write();
   
   TCanvas*c6 = new TCanvas("c6","",700,500);
   h_shifted->Draw("COLZ");
   profile->Draw();
   cout << "ended " << endl;
   
   TCanvas*c7 = new TCanvas("c7","",700,500);
   h_tmp->Draw();
}
