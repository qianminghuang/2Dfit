#define xx_cxx
#include "xx.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>

void xx::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L xx.C
//      Root > xx t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch

   if (fChain == 0) return;
   Long64_t nentries = fChain->GetEntriesFast();

  Long64_t npp = fChain->GetEntries("theWeight>0.");
  Long64_t nmm = fChain->GetEntries("theWeight<0.");
  std::cout<< "numberofnp:" << npp << "  numberofnm:" <<nmm << std::endl;


//	TFile * input1 = new TFile ("puweight.root");
//        TH1* h = NULL;
//        input1->GetObject("h2",h);

        TFile *fakelep=new TFile("fakemuon_weight.root");
        TH2F* fakelep1 =(TH2F*)fakelep->Get("muon_frs");

        double fake_photon25;
        double fake_photon30;
        double fake_photon40;
        double fake_photon50;
        double fake_photon70;
        double fake_photon100;
        double fake_photon135;


   Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries; jentry++) {
      //  for (Long64_t jentry=0; jentry<10000;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
       nb = fChain->GetEntry(jentry);   nbytes += nb;
            // std::cout<<nb<<std::endl;
      // if (Cut(ientry) < 0) continue;

 
     if(jentry%100000==0) cout<<" "<<HLT_Ele1<<" "<<HLT_Mu1<<" "<<fabs(theWeight)/theWeight<<" "<<m_dataset<<" "<<jentry<<" "<<nentries<<endl;


        if(!photonhaspixelseed && lep==13 && nlooseeles<1 && nloosemus<2 && HLT_Mu2 ==1 && mtVlepJECnew>30 && ptlep1>25 && fabs(etalep1)<2.4 && drla>0.5 && MET_et>30 && photonet>25 && (fabs(photonsceta)<1.4442 || (fabs(photonsceta)>1.566 && fabs(photonsceta)<2.5)) && jet1pt>40 && jet2pt>30 && fabs(jet1eta)<4.7 && fabs(jet2eta)<4.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5 && drj2l>0.5 && j1metPhi>0.4 && j2metPhi>0.4 && jet1icsv<0.8484 && jet2icsv<0.8484 && WGmass>10 && Mjj>200 && deltaeta>0.5);   
                  else continue;

if(fabs(photonsceta)<1.4442){
         fake_photon25 = 18027.4/67225.5;
         fake_photon30 = 10331/62995.7;
         fake_photon40 = 3548.67/26733.2;
         fake_photon50 = 2213.71/20342.1;
         fake_photon70 = 840.38/9607.4;
         fake_photon100 = 210.729/3371.83;
         fake_photon135 = 99.332/2380.18;
}
else if((fabs(photonsceta)>1.566 && fabs(photonsceta)<2.5)){
         fake_photon25 = 6150.52/23326.2;
         fake_photon30 = 4843.41/21909.3;
         fake_photon40 = 1214.52/9322.99;
         fake_photon50 = 731.674/7323.52;
         fake_photon70 = 195.477/3259.8;
         fake_photon100 = 33.2983/1122.41;
         fake_photon135 = 0.376522/633.378;
}


scalef=lumiWeight*pileupWeight*scalef;
scale_sys_up=scale_sys_up*lumiWeight*pileupWeight;
scale_sys_low=scale_sys_low*lumiWeight*pileupWeight;


double ptlepnew=0;
if(ptlep1>49)ptlepnew=49;
else ptlepnew=ptlep1;

int etabin = fakelep1->GetXaxis()->FindFixBin(fabs(etalep1));
int ptbin = fakelep1->GetYaxis()->FindFixBin(ptlepnew);
double fakelep_weight = fakelep1->GetBinContent(etabin,ptbin);

        if(m_dataset.Contains("fakephoton")){
                                        if(photonet>=25 && photonet<30){scalef=scalef*fake_photon25/35.857;scale_sys_up=scale_sys_up*fake_photon25/35.857;scale_sys_low=scale_sys_low*fake_photon25/35.857;}
                                        if(photonet>=30 && photonet<40){scalef=scalef*fake_photon30/35.857;scale_sys_up=scale_sys_up*fake_photon30/35.857;scale_sys_low=scale_sys_low*fake_photon30/35.857;}
                                        if(photonet>=40 && photonet<50){scalef=scalef*fake_photon40/35.857;scale_sys_up=scale_sys_up*fake_photon40/35.857;scale_sys_low=scale_sys_low*fake_photon40/35.857;}
                                        if(photonet>=50 && photonet<70){scalef=scalef*fake_photon50/35.857;scale_sys_up=scale_sys_up*fake_photon50/35.857;scale_sys_low=scale_sys_low*fake_photon50/35.857;}
                                        if(photonet>=70 && photonet<100){scalef=scalef*fake_photon70/35.857;scale_sys_up=scale_sys_up*fake_photon70/35.857;scale_sys_low=scale_sys_low*fake_photon70/35.857;}
                                        if(photonet>=100 && photonet<135){scalef=scalef*fake_photon100/35.857;scale_sys_up=scale_sys_up*fake_photon100/35.857;scale_sys_low=scale_sys_low*fake_photon100/35.857;}
                                        if(photonet>=135){scalef=scalef*fake_photon135/35.857;scale_sys_up=scale_sys_up*fake_photon135/35.857;scale_sys_low=scale_sys_low*fake_photon135/35.857;}
                                                }

        if(m_dataset.Contains("fakemuon")){scalef=scalef*fakelep_weight/35.857/(1-fakelep_weight);scale_sys_up=scale_sys_up*fakelep_weight/35.857/(1-fakelep_weight);scale_sys_low=scale_sys_low*fakelep_weight/35.857/(1-fakelep_weight);}

        if(m_dataset.Contains("doublefake")){
                                        if(photonet>=25 && photonet<30){scalef=scalef*fake_photon25/35.857*fakelep_weight/(1-fakelep_weight);scale_sys_up=scale_sys_up*fake_photon25/35.857*fakelep_weight/(1-fakelep_weight);scale_sys_low=scale_sys_low*fake_photon25/35.857*fakelep_weight/(1-fakelep_weight);}
                                        if(photonet>=30 && photonet<40){scalef=scalef*fake_photon30/35.857*fakelep_weight/(1-fakelep_weight);scale_sys_up=scale_sys_up*fake_photon30/35.857*fakelep_weight/(1-fakelep_weight);scale_sys_low=scale_sys_low*fake_photon30/35.857*fakelep_weight/(1-fakelep_weight);}
                                        if(photonet>=40 && photonet<50){scalef=scalef*fake_photon40/35.857*fakelep_weight/(1-fakelep_weight);scale_sys_up=scale_sys_up*fake_photon40/35.857*fakelep_weight/(1-fakelep_weight);scale_sys_low=scale_sys_low*fake_photon40/35.857*fakelep_weight/(1-fakelep_weight);}
                                        if(photonet>=50 && photonet<70){scalef=scalef*fake_photon50/35.857*fakelep_weight/(1-fakelep_weight);scale_sys_up=scale_sys_up*fake_photon50/35.857*fakelep_weight/(1-fakelep_weight);scale_sys_low=scale_sys_low*fake_photon50/35.857*fakelep_weight/(1-fakelep_weight);}
                                        if(photonet>=70 && photonet<100){scalef=scalef*fake_photon70/35.857*fakelep_weight/(1-fakelep_weight);scale_sys_up=scale_sys_up*fake_photon70/35.857*fakelep_weight/(1-fakelep_weight);scale_sys_low=scale_sys_low*fake_photon70/35.857*fakelep_weight/(1-fakelep_weight);}
                                        if(photonet>=100 && photonet<135){scalef=scalef*fake_photon100/35.857*fakelep_weight/(1-fakelep_weight);scale_sys_up=scale_sys_up*fake_photon100/35.857*fakelep_weight/(1-fakelep_weight);scale_sys_low=scale_sys_low*fake_photon100/35.857*fakelep_weight/(1-fakelep_weight);}
                                        if(photonet>=135){scalef=scalef*fake_photon135/35.857*fakelep_weight/(1-fakelep_weight);scale_sys_up=scale_sys_up*fake_photon135/35.857*fakelep_weight/(1-fakelep_weight);scale_sys_low=scale_sys_low*fake_photon135/35.857*fakelep_weight/(1-fakelep_weight);}
                                                }


                        int isdata=0;
                        int ismc=0;
                        int ismu=0;
                        if ((m_dataset.Contains("fake") || m_dataset.Contains("SMu")) && !(m_dataset.Contains("electronfaketophoton")) && isprompt==2 && ispromptLep==1){isdata=1;}
                        if (!(m_dataset.Contains("muon")) && !(m_dataset.Contains("fake")) && !(m_dataset.Contains("SMu")) && isprompt==2 && ispromptLep==1){ismc=1;}
                        if((m_dataset.Contains("electronfaketophoton")) && isprompt==3 && ispromptLep==1){ismu=1;}

                        if(m_dataset.Contains("doublefake")){
                scalef=-scalef;
                scale_sys_up=-scale_sys_up;
                scale_sys_low=-scale_sys_low;
				}


if(isdata>0 || ismc>0 || ismu>0)		
ExTree->Fill();
else continue;


   }

}
