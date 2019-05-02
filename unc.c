#include "TCanvas.h"
#include "TAxis.h"
#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TDirectory.h"
#include "RooPlot.h"
#include "RooAddPdf.h"
#include "RooFitResult.h"
#include "RooDataHist.h"
#include "RooHistPdf.h"
#include "TLegend.h"
#include "TFitResultPtr.h"
#include "TMatrixDSym.h"
#include "RooChi2Var.h"
#include "RooExtendPdf.h"
#include <TLatex.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include "TH2.h"
#include "TStyle.h"
#include "TNtupleD.h"
#include <stdio.h>
#include <stdlib.h>


void unc()
{
//for fake photon
//TFile * input1 = new TFile ("/afs/cern.ch/user/q/qihuang/eos/ceshi/outv1/for-AQGC/mu/fakephoton.root");
//TFile * input2 = new TFile ("/afs/cern.ch/user/q/qihuang/eos/ceshi/outv1/for-AQGC/mu-photon/outoutfakephoton.root");

//for fake lepton
//TFile * input1 = new TFile ("/afs/cern.ch/user/q/qihuang/eos/ceshi/outv1/for-AQGC/mu/fakelep.root");
//TFile * input2 = new TFile ("/afs/cern.ch/user/q/qihuang/eos/ceshi/outv1/for-AQGC/mu-lep/outoutfakemuon.root");

//for L1 prefiring
TFile * input1 = new TFile ("/afs/cern.ch/user/q/qihuang/eos/ceshi/outv1/for-AQGC/mu/WAJJ.root");
TFile * input2 = new TFile ("/afs/cern.ch/user/q/qihuang/eos/ceshi/outv1/for-AQGC/mu/WAJJ.root");

//TFile * input1 = new TFile ("/afs/cern.ch/user/q/qihuang/eos/ceshi/outv1/for-AQGC/mu/WA.root");
//TFile * input2 = new TFile ("/afs/cern.ch/user/q/qihuang/eos/ceshi/outv1/for-AQGC/mu/WA.root");

TTree *Outtree1 = (TTree*)input1->Get("demo");
TTree *Outtree2 = (TTree*)input2->Get("demo");

int nentries1 = (int)Outtree1->GetEntries();
int nentries2 = (int)Outtree2->GetEntries();


                Double_t        WGmass;
                Double_t        Mjj;
                Double_t        photonet;
                Double_t        scalef;
                Double_t        deltaeta;
                Double_t        L1prefiring;
                Double_t        L1prefiringup;
                Double_t        L1prefiringdown;
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
                Outtree1->SetBranchAddress("L1prefiringup",&L1prefiringup);
                Outtree1->SetBranchAddress("L1prefiringdown",&L1prefiringdown);
                Outtree1->SetBranchAddress("Dphiwajj",&Dphiwajj);
                Outtree1->SetBranchAddress("zepp",&zepp);
                Outtree1->SetBranchAddress("WGmass",&WGmass);
                Outtree1->SetBranchAddress("Mjj",&Mjj);
                Outtree1->SetBranchAddress("photonet",&photonet);
                Outtree1->SetBranchAddress("deltaeta",&deltaeta);
                Outtree1->SetBranchAddress("scalef", &scalef);

      Outtree2->SetBranchAddress("ptlep1", &ptlep1);
      Outtree2->SetBranchAddress("etalep1", &etalep1);
      Outtree2->SetBranchAddress("jet1pt", &jet1pt);
      Outtree2->SetBranchAddress("jet1eta", &jet1eta);
      Outtree2->SetBranchAddress("jet2pt", &jet2pt);
      Outtree2->SetBranchAddress("jet2eta", &jet2eta);
      Outtree2->SetBranchAddress("drj1a", &drj1a);
      Outtree2->SetBranchAddress("drj2a", &drj2a);
      Outtree2->SetBranchAddress("drj1l", &drj1l);
      Outtree2->SetBranchAddress("drj2l", &drj2l);
      Outtree2->SetBranchAddress("j1metPhi", &j1metPhi);
      Outtree2->SetBranchAddress("j2metPhi", &j2metPhi);
      Outtree2->SetBranchAddress("Mla", &Mla);
                Outtree2->SetBranchAddress("photonsceta", &photonsceta);
//                Outtree2->SetBranchAddress("mtVlepJECnew", &mtVlepJECnew);
                Outtree2->SetBranchAddress("L1prefiring",&L1prefiring);
                Outtree2->SetBranchAddress("L1prefiringup",&L1prefiringup);
                Outtree2->SetBranchAddress("L1prefiringdown",&L1prefiringdown);
                Outtree2->SetBranchAddress("Dphiwajj",&Dphiwajj);
                Outtree2->SetBranchAddress("zepp",&zepp);
                Outtree2->SetBranchAddress("WGmass",&WGmass);
                Outtree2->SetBranchAddress("Mjj",&Mjj);
                Outtree2->SetBranchAddress("photonet",&photonet);
                Outtree2->SetBranchAddress("deltaeta",&deltaeta);
                Outtree2->SetBranchAddress("scalef", &scalef);


Double_t binx[5]={500,800,1200,1700,2000};
Double_t biny[4]={30,80,130,200};
TH2F *histo1=new TH2F("histo1","histo1",4,binx,3,biny);
TH2F *histo2=new TH2F("histo2","histo2",4,binx,3,biny);


                for(int j=0; j<nentries1; j++)
                {
                        Outtree1->GetEntry(j);

			if(Mjj>1900)Mjj=1900; if(Mla>190)Mla=190; 

                        bool ipass=(fabs(photonsceta)<1.4442 && ptlep1>35 && fabs(etalep1)<2.4 && photonet>30 && jet1pt>50 && jet2pt>40 && fabs(jet1eta)<4.7 && fabs(jet2eta)<4.7 && drj1a>2 && drj2a>2 && drj1l>2 && drj2l>2 && j1metPhi>0.5 && j2metPhi>0.5 && WGmass>100 && Mla>30 && zepp<1.5 && Dphiwajj>2 && deltaeta>2.5);  

                        double lumi=35.857;

                        if(ipass>0) {
                                histo1->Fill(Mjj,Mla,lumi*scalef*L1prefiring);
                        	    }

                }

                for(int j=0; j<nentries2; j++)
                {
                        Outtree2->GetEntry(j);

			if(Mjj>1900)Mjj=1900; if(Mla>190)Mla=190; 

                        bool ipass=(fabs(photonsceta)<1.4442 && ptlep1>35 && fabs(etalep1)<2.4 && photonet>30 && jet1pt>50 && jet2pt>40 && fabs(jet1eta)<4.7 && fabs(jet2eta)<4.7 && drj1a>2 && drj2a>2 && drj1l>2 && drj2l>2 && j1metPhi>0.5 && j2metPhi>0.5 && WGmass>100 && Mla>30 && zepp<1.5 && Dphiwajj>2 && deltaeta>2.5); 

                        double lumi=35.857;

                        if(ipass>0) { 
				L1prefiring=L1prefiring+(L1prefiringup-L1prefiringdown)/2;     //for L1 prefiring
                                histo2->Fill(Mjj,Mla,lumi*scalef*L1prefiring);
                        	    }

                }


cout<<"fakephoton  "<<histo1->Integral()<<"    photonup   "<<histo2->Integral()<<endl;
for (int bin=0;bin<=histo2->GetNcells();++bin){histo2->SetBinContent(bin,fabs(histo2->GetBinContent(bin)-histo1->GetBinContent(bin)));}

histo2->Divide(histo1);

	TCanvas *c1 = new TCanvas("c1","c1",800,600);
	histo2->GetXaxis()->SetTitle("M_{jj}");
        histo2->GetYaxis()->SetTitle("M_{l#gamma}");

	histo2->Draw("colztext");
//        c1->Print("fahephoton_unc_MB.png");
//        c1->Print("fahelep_unc_MB.png");
        c1->Print("L1_unc_MB.png");
//        c1->Print("L1WA_unc_MB.png");



} //main


