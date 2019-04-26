#include "TH1.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TStyle.h"
#include <iostream>
#include "TLegend.h"
#include "THStack.h"
#include "CMSTDRStyle.h"
#include "CMS_lumi.C"
#include "TArrow.h"
#include "TLatex.h"
using namespace std;

void cmsLumi(bool channel) 
{
        TLatex latex;
        latex.SetNDC();
        latex.SetTextSize(0.04);
        latex.SetLineWidth(2);
        int beamcomenergytev=13;
        latex.SetTextAlign(31); 
        latex.SetTextAlign(11);
        latex.DrawLatex(0.18,0.82,"Preliminary");
        latex.DrawLatex(0.18,0.86,"CMS");
        latex.SetTextSize(0.03);
        latex.DrawLatex(0.76,0.92,Form("35.9 fb^{-1} (%d TeV)", (beamcomenergytev)));
}

TH1D* unroll(TH2D* th2_in,Double_t* xbin, Double_t* ybin,  Int_t xbins_in, Int_t ybins_in)
{
	TH2D* th2 = th2_in;
	Int_t nbinsx =xbins_in;
	Int_t nbinsy =ybins_in;
	Int_t nbins = nbinsx*nbinsy;

	TH1D* h1 = new TH1D("hist", "hist", nbins, 0, nbins);
	TH1D* h1_out = new TH1D("unrolled hist", "unrolled hist", nbins, 0, nbins);

	for(Int_t iy=1; iy<=nbinsy; iy++){
		for(Int_t ix=1; ix<=nbinsx; ix++){
			Double_t x_temp = 0.5*(xbin[ix-1]+xbin[ix]);
			Double_t y_temp = 0.5*(ybin[iy-1]+ybin[iy]);
			h1->SetBinContent(ix+(iy-1)*nbinsx,th2->GetBinContent(th2->FindBin(x_temp, y_temp)));
			h1->SetBinError(ix+(iy-1)*nbinsx,th2->GetBinError(th2->FindBin(x_temp, y_temp)));
		}
	}
/*
	for(Int_t ii=1; ii<=nbins-2;ii++){
		if(ii<9){
			h1_out->SetBinContent(ii, h1->GetBinContent(ii));
			h1_out->SetBinError(ii,h1->GetBinError(ii));
		}
		if(ii==9){
			h1_out->SetBinContent(ii, h1->GetBinContent(ii)+h1->GetBinContent(ii+1)+h1->GetBinContent(ii+2));
			h1_out->SetBinError(ii,sqrt(h1->GetBinError(ii)*h1->GetBinError(ii)+h1->GetBinError(ii+1)*h1->GetBinError(ii+1)+h1->GetBinError(ii+2)*h1->GetBinError(ii+2)));
		}
		if(ii==10){
			h1_out->SetBinContent(ii, h1->GetBinContent(ii+2));
                        h1_out->SetBinError(ii,h1->GetBinError(ii+2));
		}
	}
*/
        for(Int_t ii=1; ii<=nbins;ii++){
                        h1_out->SetBinContent(ii, h1->GetBinContent(ii));
                        h1_out->SetBinError(ii,h1->GetBinError(ii));
/*                if(ii==9){
                        h1_out->SetBinContent(ii, h1->GetBinContent(ii)+h1->GetBinContent(ii+1)+h1->GetBinContent(ii+2));
                        h1_out->SetBinError(ii,sqrt(h1->GetBinError(ii)*h1->GetBinError(ii)+h1->GetBinError(ii+1)*h1->GetBinError(ii+1)+h1->GetBinError(ii+2)*h1->GetBinError(ii+2)));
                }
                if(ii==10){
                        h1_out->SetBinContent(ii, h1->GetBinContent(ii+2));
                        h1_out->SetBinError(ii,h1->GetBinError(ii+2));
                }
*/
        }


	return h1_out;
}

void unrollmain(){
	setTDRStyle();
	TFile* fout = new TFile("aa.root","RECREATE");
	Double_t WA_scale= 1.0;
	std::ostringstream strs;
	std::string lumivalue = strs.str();
	Double_t lumi=35.857;
	Double_t mjj_bins[5]={500, 800, 1200, 1700, 2000};
//        Double_t mlla_bins[5]={90, 130, 170, 210, 240};
        Double_t detajj_bins[4]={30,80,130,200};

	TFile* f_WA=TFile::Open("./2d_WA.root");
	TH2D* th2_WA=(TH2D*)f_WA->Get("th2");
//	TH1D* t_WA=unroll(th2_WA, mjj_bins, mlla_bins, 4,4);
	TH1D* t_WA=unroll(th2_WA, mjj_bins, detajj_bins, 4,3);
	t_WA->SetFillColor(kBlue-6);
	t_WA->SetMarkerColor(kBlue-6);
	t_WA->SetLineColor(kBlue-6);
	t_WA->Scale(lumi*WA_scale);
//	const char *name[9]={"500~800","800~1200","1200~2000","500~800","800~1200","1200~2000","500~800","800~1200","1200~2000"};
	const char *name[12]={"500~800","800~1200","1200~1700","1700~inf","500~800","800~1200","1200~1700","1700~inf","500~800","800~1200","1200~1700","1700~inf"};

	TFile* f_WAJJ=TFile::Open("./2d_WAJJ.root");
        TH2D* th2_WAJJ=(TH2D*)f_WAJJ->Get("th2");
//        TH1D* t_WAJJ=unroll(th2_WAJJ, mjj_bins, mlla_bins, 4,4);
        TH1D* t_WAJJ=unroll(th2_WAJJ, mjj_bins, detajj_bins, 4,3);
	t_WAJJ->SetFillColor(kRed-9);
	t_WAJJ->SetMarkerColor(kRed-9);
        t_WAJJ->SetLineColor(kRed-9);
	t_WAJJ->SetMarkerStyle(21);
	t_WAJJ->Scale(lumi);

	TFile* f_data=TFile::Open("./2d_singledata.root");
        TH2D* th2_data=(TH2D*)f_data->Get("th2");
        TH1D* t_data=unroll(th2_data, mjj_bins, detajj_bins, 4,3);

	TFile* f_DY=TFile::Open("./2d_DY.root");
        TH2D* th2_DY=(TH2D*)f_DY->Get("th2");
//        TH1D* t_DY=unroll(th2_DY, mjj_bins, mlla_bins, 4,4);
        TH1D* t_DY=unroll(th2_DY, mjj_bins, detajj_bins, 4,3);
	t_DY->SetFillColor(kPink+8);
	t_DY->SetMarkerColor(kPink+8);
        t_DY->SetLineColor(kPink+8);
	t_DY->Scale(lumi);

	TFile* f_VV=TFile::Open("./2d_VV.root");
        TH2D* th2_VV=(TH2D*)f_VV->Get("th2");
//        TH1D* t_VV=unroll(th2_VV, mjj_bins, mlla_bins, 4,4);
        TH1D* t_VV=unroll(th2_VV, mjj_bins, detajj_bins, 4,3);
	t_VV->SetFillColor(40);
	t_VV->SetMarkerColor(40);
        t_VV->SetLineColor(40);
	t_VV->Scale(lumi);

	TFile* f_TTJets=TFile::Open("./2d_TTJets.root");
        TH2D* th2_TTJets=(TH2D*)f_TTJets->Get("th2");
//        TH1D* t_TTJets=unroll(th2_TTJets, mjj_bins, mlla_bins, 4,4);
        TH1D* t_TTJets=unroll(th2_TTJets, mjj_bins, detajj_bins, 4,3);
	t_TTJets->SetFillColor(kCyan);
	t_TTJets->SetMarkerColor(kCyan);
        t_TTJets->SetLineColor(kCyan);
	t_TTJets->Scale(lumi);

	TFile* f_STop=TFile::Open("./2d_STop.root");
        TH2D* th2_STop=(TH2D*)f_STop->Get("th2");
//        TH1D* t_STop=unroll(th2_STop, mjj_bins, mlla_bins, 4,4);
        TH1D* t_STop=unroll(th2_STop, mjj_bins, detajj_bins, 4,3);
	t_STop->SetFillColor(kGreen+2);
	t_STop->SetMarkerColor(kGreen+2);
        t_STop->SetLineColor(kGreen+2);
	t_STop->Scale(lumi);
	for(Int_t i=1;i<=12;i++){ t_STop->GetXaxis()->SetBinLabel(i,name[i-1]);}

	TFile* f_fakephoton=TFile::Open("./2d_fakephoton.root");
        TH2D* th2_fakephoton=(TH2D*)f_fakephoton->Get("th2");
        TH1D* t_fakephoton=unroll(th2_fakephoton, mjj_bins, detajj_bins, 4,3);
//	std::cout<<t_fakephoton->GetBinContent(1)<<" error"<<t_fakephoton->GetBinError(1)<<std::endl;
	t_fakephoton->SetFillColor(kYellow-7);
	t_fakephoton->SetMarkerColor(kYellow-7);
        t_fakephoton->SetLineColor(kYellow-7);
        t_fakephoton->Scale(lumi);

        TFile* f_fakelep=TFile::Open("./2d_fakelep.root");
        TH2D* th2_fakelep=(TH2D*)f_fakelep->Get("th2");
        TH1D* t_fakelep=unroll(th2_fakelep, mjj_bins, detajj_bins, 4,3);
        t_fakelep->SetFillColor(kGreen-5);
        t_fakelep->SetMarkerColor(kGreen-5);
        t_fakelep->SetLineColor(kGreen-5);
        t_fakelep->Scale(lumi);

        TFile* f_electronfaketophoton=TFile::Open("./2d_electronfaketophoton.root");
        TH2D* th2_electronfaketophoton=(TH2D*)f_electronfaketophoton->Get("th2");
        TH1D* t_electronfaketophoton=unroll(th2_electronfaketophoton, mjj_bins, detajj_bins, 4,3);
        t_electronfaketophoton->SetFillColor(kBlue-7);
        t_electronfaketophoton->SetMarkerColor(kBlue-7);
        t_electronfaketophoton->SetLineColor(kBlue-7);
        t_electronfaketophoton->Scale(lumi);


	THStack* hs = new THStack("hs", "");
	std::cout<<t_WA->GetBinContent(1)<<std::endl;
	hs->SetMaximum(t_WA->GetBinContent(1)*2.5);
	hs->Add(t_STop);
	hs->Add(t_TTJets);
	hs->Add(t_VV);
	hs->Add(t_DY);
        hs->Add(t_electronfaketophoton);
        hs->Add(t_fakelep);
	hs->Add(t_fakephoton);
	hs->Add(t_WA);
	hs->Add(t_WAJJ);


/*
t_WA->Add(t_STop);
t_WA->Add(t_TTJets);
t_WA->Add(t_VV);
t_WA->Add(t_DY);
t_WA->Add(t_electronfaketophoton);
t_WA->Add(t_fakelep);
t_WA->Add(t_fakephoton);
cout<<"bkg  "<<t_WA->Integral();
*/
	gStyle->SetPadBorderMode(0);
        gStyle->SetOptStat(0);
	gStyle->SetPadTickX(1);
        gStyle->SetPadTickY(1);
        gStyle->SetPadTickX(1);
        gStyle->SetPadTickY(1);
        gStyle->SetAxisColor(1, "XYZ");
        gStyle->SetStripDecimals(kTRUE);
        gStyle->SetTickLength(0.03, "XYZ");
        gStyle->SetNdivisions(510, "XYZ");

	TCanvas* c1=new TCanvas("","",800,800);
	c1->cd();
	TPad* fPad1 = new TPad("pad1", "", 0.00, 0.00, 0.99, 0.99);
	fPad1->Draw();
	CMS_lumi(fPad1, 4, 0, lumivalue);
	hs->Draw("HIST");
	hs->GetYaxis()->SetTitleOffset(0.95);
	hs->GetYaxis()->SetTitle("Events /bin");
//        hs->GetYaxis()->SetTitleSize(0.05);
	hs->GetXaxis()->SetTitle("m_{jj} (GeV)");
	hs->GetXaxis()->SetTitleOffset(1.3);
	hs->GetXaxis()->SetTitleSize(0.04);
//	hs->GetXaxis()->SetLabelSize(0.06);
	
//	t_data->Draw("Same pe");

	TH1D* htemp = (TH1D*)(hs->GetStack()->Last());
        htemp->SetBinErrorOption(TH1::kPoisson);
        static const int binsize = htemp->GetSize()-2;
        Double_t x[binsize];
        Double_t y[binsize];
        Double_t xerror[binsize];
        Double_t yerror[binsize];
        for(int i=0;i<binsize;i++)
        {
                x[i]=htemp->GetBinCenter(i+1);
                y[i]=htemp->GetBinContent(i+1);
                xerror[i]=0.5*htemp->GetBinWidth(i+1);
                yerror[i]=htemp->GetBinError(i+1);
                if(htemp->GetBinContent(i+1)==0)
                {yerror[i]=0.;}
        }
        TGraphErrors* gr = new TGraphErrors(binsize, x, y, xerror, yerror);
        gr->SetFillColor(1);
        gr->SetFillStyle(3005);
        gr->Draw("SAME 2");	

	TLegend* leg1 = new TLegend(0.74, 0.72, 0.94, 0.88);
        TLegend* leg2 = new TLegend(0.54, 0.72, 0.74, 0.88);
        leg1->SetMargin(0.4);
        leg2->SetMargin(0.4);
	leg1->AddEntry(gr,"Stat. Unc.", "f");
	leg1->AddEntry(t_STop, "STop", "f");
	leg1->AddEntry(t_TTJets, "TTJets", "f");
	leg1->AddEntry(t_VV, "VV", "f");
	leg2->AddEntry(t_WA, "QCD W#gamma", "f");
	leg2->AddEntry(t_fakephoton, "Fake Photon", "f");
	leg2->AddEntry(t_DY, "DY", "f");
        leg2->AddEntry(t_fakelep, "fake lepton", "f");
        leg1->AddEntry(t_electronfaketophoton, "e#rightarrow#gamma", "f");
	leg2->AddEntry(t_WAJJ, "EWK W#gamma");
	leg1->SetFillColor(kWhite);
	leg1->Draw();
	leg2->SetFillColor(kWhite);
	leg2->Draw();

	TLatex latex1;
        latex1.SetTextAlign(12);
        latex1.SetTextSize(0.04);
        TArrow* line1 = new TArrow(t_WA->GetBinLowEdge(5),0,t_WA->GetBinLowEdge(5),2.5*t_WA->GetMaximum(),0.07,"") ;
        TArrow* line2 = new TArrow(t_WA->GetBinLowEdge(9),0,t_WA->GetBinLowEdge(9),2.*t_WA->GetMaximum(),0.07,"") ;
        line1->SetLineColor(1);
        line1->SetLineWidth(3);
        line1->SetLineStyle(7);
        line2->SetLineColor(1);
        line2->SetLineWidth(3);
        line2->SetLineStyle(7);
	
	cmsLumi(0);

	fout->cd();
	hs->Write();
	fout->Close();

	latex1.DrawLatexNDC(0.15,0.5,"#font[12]{M_{l#gamma} #in (30, 80)}");
        latex1.DrawLatexNDC(0.45,0.5,"#font[12]{M_{l#gamma} #in (80, 130)}");
        latex1.DrawLatexNDC(0.75,0.5,"#font[12]{M_{l#gamma} > 130}");

        line1->Draw();
        line2->Draw();

	c1->SaveAs("aa.png");
	c1->SaveAs("aa.C");


}
