#include "TH2.h"
#include "TFile.h"
#include "TTree.h"
#include <string>
#include <iostream>

using namespace std;

TH2D* hist_2d(std::string filename){

	std::string file = "/afs/cern.ch/user/q/qihuang/eos/ceshi/outv1/for-AQGC/mu/"+filename+".root";
	TFile* f1 = TFile::Open(file.c_str());

	TTree* Outtree1 = (TTree*)f1->Get("demo");
int nentries1 = (int)Outtree1->GetEntries();
                Double_t        WGmass;
                Double_t        Mjj;
                Double_t        photonet;
                Double_t        scalef;
                Double_t        deltaeta;
                Double_t        L1prefiring;
                Double_t        Dphiwajj;
                Double_t        zepp;
                Double_t        photonsceta;
                Double_t        mtVlepJECnew;
   Double_t        ptlep1;
   Double_t        etalep1;
   Double_t        jet1pt;
   Double_t        jet1eta;
   Double_t        jet2pt;
   Double_t        jet2eta;
   Double_t        drj1a;
   Double_t        drj2a;
   Double_t        drj1l;
   Double_t        drj2l;
   Double_t        j1metPhi;
   Double_t        j2metPhi;
   Double_t        Mla;

      Outtree1->SetBranchAddress("ptlep1", &ptlep1);
      Outtree1->SetBranchAddress("etalep1", &etalep1);
      Outtree1->SetBranchAddress("jet1pt", &jet1pt);
      Outtree1->SetBranchAddress("jet1eta", &jet1eta);
      Outtree1->SetBranchAddress("jet2pt", &jet2pt);
      Outtree1->SetBranchAddress("jet2eta", &jet2eta);
      Outtree1->SetBranchAddress("drj1a", &drj1a);
      Outtree1->SetBranchAddress("drj2a", &drj2a);
      Outtree1->SetBranchAddress("drj1l", &drj1l);
      Outtree1->SetBranchAddress("drj2l", &drj2l);
      Outtree1->SetBranchAddress("j1metPhi", &j1metPhi);
      Outtree1->SetBranchAddress("j2metPhi", &j2metPhi);
      Outtree1->SetBranchAddress("Mla", &Mla);
                Outtree1->SetBranchAddress("photonsceta", &photonsceta);
//                Outtree1->SetBranchAddress("mtVlepJECnew", &mtVlepJECnew);
                Outtree1->SetBranchAddress("L1prefiring",&L1prefiring);
                Outtree1->SetBranchAddress("Dphiwajj",&Dphiwajj);
                Outtree1->SetBranchAddress("zepp",&zepp);
                Outtree1->SetBranchAddress("WGmass",&WGmass);
                Outtree1->SetBranchAddress("Mjj",&Mjj);
                Outtree1->SetBranchAddress("photonet",&photonet);
                Outtree1->SetBranchAddress("deltaeta",&deltaeta);
                Outtree1->SetBranchAddress("scalef", &scalef);

double count=0;

	Double_t mjj_bins[5]={500, 800, 1200, 1800, 2000};
//	Double_t mlla_bins[5]={90, 130, 170, 210, 240};
	Double_t mla_bins[4]={30, 80,  130, 200};
//	TH2D* th2 = new TH2D("th2","th2",4, mjj_bins, 4, mlla_bins);
	TH2D* th2 = new TH2D("th2","th2",4, mjj_bins, 3, mla_bins);
	th2->Sumw2();
	for(Int_t i=0; i<nentries1;i++)
	{
		Outtree1->GetEntry(i);if(Mjj>1900)Mjj=1900; if(Mla>190)Mla=190;
		//if(zepp>2.4 || delta_phi <1.9)continue;
		if(fabs(photonsceta)<1.4442 && ptlep1>35 && fabs(etalep1)<2.4 && photonet>30 && jet1pt>50 && jet2pt>40 && fabs(jet1eta)<4.7 && fabs(jet2eta)<4.7 && drj1a>2 && drj2a>2 && drj1l>2 && drj2l>2 && j1metPhi>0.5 && j2metPhi>0.5 && WGmass>100 && Mla>30 && zepp<1.5 && Dphiwajj>2 && deltaeta>2.5){
		th2->Fill(Mjj, Mla, scalef*L1prefiring);	if(deltaeta>4 && Mjj>800)count+=scalef*L1prefiring*35.865;
					}
	}
cout<<filename<<"  "<<count<<endl;

	return th2;  
}
/*
TH2D* hist_2d_data(std::string filename){

	std::string file = "../../signal_region/ele_barrel_lowphotonpt_0401/optimal_"+filename+".root";
	TFile* f1 = TFile::Open(file.c_str());

	TTree* t = (TTree*)f1->Get("outtree");

	Double_t Mjj;
	Double_t delta_phi;
	Double_t zepp;
	Double_t ZGmass;
	Double_t detajj;
	Double_t actualWeight;

	t->SetBranchAddress("Mjj", &Mjj);
	t->SetBranchAddress("delta_phi", &delta_phi);
	t->SetBranchAddress("zepp", &zepp);
	t->SetBranchAddress("ZGmass", &ZGmass);
	t->SetBranchAddress("detajj", &detajj);
	t->SetBranchAddress("actualWeight", &actualWeight);

	Double_t mjj_bins[4]={500, 800, 1200, 2000};
//	Double_t mlla_bins[5]={90, 130, 170, 210, 250};
	Double_t detajj_bins[4]={2.5, 4.5, 6, 6.5};
//	TH2D* th2 = new TH2D("th2","th2",4, mjj_bins, 4, mlla_bins);
	TH2D* th2 = new TH2D("th2","th2",3, mjj_bins, 3, detajj_bins);
	th2->Sumw2();
	for(Int_t i=0; i<t->GetEntries();i++)
	{
		t->GetEntry(i);
		if(zepp>2.4 || delta_phi <1.9)continue;
		if(Mjj<2000 && detajj<6.5) th2->Fill(Mjj, detajj);
		if(Mjj>=2000 && detajj<6.5) th2->Fill(1999, detajj);
		if(Mjj<2000 && detajj>=6.5) th2->Fill(Mjj, 6.1);
		if(Mjj>=2000 && detajj>=6.5) th2->Fill(1999, 6.1);
	}

	return th2;
}
*/
void dhist(){
	TFile* f1=new TFile("2d_STop.root","RECREATE");
	TFile* f2=new TFile("2d_VV.root","RECREATE");
	TFile* f3=new TFile("2d_TTJets.root","RECREATE");
	TFile* f4=new TFile("2d_WA.root","RECREATE");
	TFile* f5=new TFile("2d_DY.root","RECREATE");
	TFile* f6=new TFile("2d_WAJJ.root","RECREATE");
	TFile* f7=new TFile("2d_fakephoton.root","RECREATE");
        TFile* f8=new TFile("2d_fakelep.root","RECREATE");
        TFile* f9=new TFile("2d_electronfaketophoton.root","RECREATE");
	TFile* f10=new TFile("2d_singledata.root","RECREATE");

	TH2D* h1= hist_2d("STop");
	TH2D* h2= hist_2d("VV");
	TH2D* h3= hist_2d("TTJets");
	TH2D* h4= hist_2d("WA");
	TH2D* h5= hist_2d("DY");
	TH2D* h6= hist_2d("WAJJ");
	TH2D* h7= hist_2d("fakephoton");
        TH2D* h8= hist_2d("fakelep");
        TH2D* h9= hist_2d("electronfaketophoton");
	TH2D* h10= hist_2d("sdata");
	
	f1->cd();
	h1->Write();
	f1->Close();
	f2->cd();
	h2->Write();
	f2->Close();
	f3->cd();
	h3->Write();
	f3->Close();
	f4->cd();
	h4->Write();
	f4->Close();
	f5->cd();
	h5->Write();
	f5->Close();
	f6->cd();
	h6->Write();
	f6->Close();
	f7->cd();
	h7->Write();
	f7->Close();
	f8->cd();
	h8->Write();
	f8->Close();
        f9->cd();
        h9->Write();
        f9->Close();
        f10->cd();
        h10->Write();
        f10->Close();
}
