#!/usr/bin/env python

from ROOT import gROOT, THStack, TH1D, TList, TFile

print '-----begin to transfer TH2D to txt for Higgs-combine tool----- \n'

f_in = TFile.Open("./aa.root")
tstack = f_in.Get("hs")
t_list = tstack.GetHists()

th1_STop = t_list.At(0)
th1_TTJets = t_list.At(1)
th1_VV = t_list.At(2)
th1_DY = t_list.At(3)
th1_electronfaketophoton = t_list.At(4)
th1_fakelep = t_list.At(5)
th1_fakephoton= t_list.At(6)
th1_WA = t_list.At(7)
th1_WAJJ = t_list.At(8)
print '>>>>begin to read bin content to the txt file>>>>'
jet=[1.160,1.253,1.252,1.169,1.256,1.305,1.195,1.180,1,1]
jer=[1.011,1.005,1.005,1.009,1.024,1.003,1.084,1.010,1,1]
jes=[1.020,1.015,1.021,1.10,1.045,1.032,1.302,1.05,1,1]
pdf_QCD=[1.011,1.013,1.029,1.014,1.014,1.017,1.014,1.011,1,1]
pdf_ewk=[1.037,1.039,1.042,1.036,1.036,1.045,1.048,1.042,1,1]
l1_signal=[1.012,1.020,1.037,1.009,1.011,1.031,1.005,1.015,1,1]
l1_others=[1.010,1.021,1.029,1.006,1.012,1.018,1.006,1.010,1,1]
#scale_QCD=[1.094,1.13,1.3,1.138,1.163,1.137,1.041,1.178,1.159]
scale_QCD=[1.136,1.186,1.242,1.074,1.130,1.117,1.056,1.118,1,1]
scale_QCD_extra_down=[0.982,0.948,0.922,1.026,1.001,1.013,1.007,1.005,1,1]
scale_QCD_extra_up=[1.022,1.062,1.094,0.972,0.999,0.992,0.985,0.990,1,1]
scale_ewk=[1.027,1.054,1.088,1.019,1.049,1.103,1.047,1.116,1,1]
for i in range(1,11):
   f = open('%s_%s_bin_%d.txt'%('muon', 'barrel', i),'w')
   f.write('imax 1   number of channels\n')
   f.write('jmax 8   number of processes-1\n')
   f.write('kmax 22  number of nuisance parameters (sources of systematical uncertainties)\n')
   f.write('------------\n')
   f.write('# we have just one channel, in which we observe 0 events\n')
   f.write('bin mb\n')
   bin_content = th1_STop.GetBinContent(i)+th1_TTJets.GetBinContent(i)+th1_VV.GetBinContent(i)+th1_DY.GetBinContent(i)+th1_electronfaketophoton.GetBinContent(i)+th1_fakelep.GetBinContent(i)+th1_fakephoton.GetBinContent(i)+th1_WA.GetBinContent(i)+th1_WAJJ.GetBinContent(i)
# bincontent of each precess
   STop_bincontent = th1_STop.GetBinContent(i) if th1_STop.GetBinContent(i)>0 else 0
   TTJets_bincontent = th1_TTJets.GetBinContent(i) if th1_TTJets.GetBinContent(i)>0 else 0
   VV_bincontent = th1_VV.GetBinContent(i) if th1_VV.GetBinContent(i)>0 else 0
   DY_bincontent = th1_DY.GetBinContent(i) if th1_DY.GetBinContent(i) else 0
   electronfaketophoton_bincontent = th1_electronfaketophoton.GetBinContent(i) if th1_electronfaketophoton.GetBinContent(i)>0 else 0
   fakelep_bincontent = th1_fakelep.GetBinContent(i) if th1_fakelep.GetBinContent(i) else 0
   fakephoton_bincontent = th1_fakephoton.GetBinContent(i) if th1_fakephoton.GetBinContent(i) else 0
   WA_bincontent = th1_WA.GetBinContent(i) if th1_WA.GetBinContent(i) else 0
   WAJJ_bincontent = th1_WAJJ.GetBinContent(i)  if th1_WAJJ.GetBinContent(i)>0 else 0
# bin error

   STop_binerror = th1_STop.GetBinError(i)/STop_bincontent if STop_bincontent>0 else 0
   STop_binerror = STop_binerror if STop_binerror<1 else 1
   STop_binerror = STop_binerror+1

   TTJets_binerror = th1_TTJets.GetBinError(i)/TTJets_bincontent if TTJets_bincontent>0 else 0
   TTJets_binerror = TTJets_binerror if TTJets_binerror<1 else 1
   TTJets_binerror = TTJets_binerror+1

   VV_binerror = th1_VV.GetBinError(i)/VV_bincontent if VV_bincontent>0 else 0
   VV_binerror = VV_binerror if VV_binerror<1 else 1
   VV_binerror = VV_binerror+1

   DY_binerror = th1_DY.GetBinError(i)/DY_bincontent if DY_bincontent>0 else 0
   DY_binerror = DY_binerror if DY_binerror<1 else 1
   DY_binerror = DY_binerror+1

   electronfaketophoton_binerror = th1_electronfaketophoton.GetBinError(i)/electronfaketophoton_bincontent if electronfaketophoton_bincontent>0 else 0
   electronfaketophoton_binerror = electronfaketophoton_binerror if electronfaketophoton_binerror<1 else 1
   electronfaketophoton_binerror = electronfaketophoton_binerror+1

   fakelep_binerror = th1_fakelep.GetBinError(i)/fakelep_bincontent if fakelep_bincontent>0 else 0
   fakelep_binerror = fakelep_binerror if fakelep_binerror<1 else 1
   fakelep_binerror = fakelep_binerror+1

   fakephoton_binerror = th1_fakephoton.GetBinError(i)/fakephoton_bincontent if fakephoton_bincontent>0 else 0
   fakephoton_binerror = fakephoton_binerror if fakephoton_binerror<1 else 1
   fakephoton_binerror = fakephoton_binerror+1

   WA_binerror = th1_WA.GetBinError(i)/WA_bincontent if WA_bincontent>0 else 0
   WA_binerror = WA_binerror if WA_binerror<1 else 1
   WA_binerror = WA_binerror+1

   WAJJ_binerror = th1_WAJJ.GetBinError(i)/WAJJ_bincontent if WAJJ_bincontent>0 else 0
   WAJJ_binerror = WAJJ_binerror if WAJJ_binerror<1 else 1
   WAJJ_binerror = WAJJ_binerror+1


   f.write('observation %.2f\n'%bin_content)
   f.write('------------\n')
   f.write('# now we list the expected events for signal and all backgrounds in that bin\n')
   f.write('# the second process line must have a positive number for backgrounds, and 0 for signal\n')
   f.write('# then we list the independent sources of uncertainties, and give their effect (syst. error)\n')
   f.write('# on each process and bin\n')
   f.write('bin\tmb\tmb\tmb\tmb\tmb\tmb\tmb\tmb\tmb\n')
   f.write('process\tVBS\tQCD\tfakephoton\tTTJets\tVV\tSTop\tDY\tfakelep\telectronfaketophoton\n')
   f.write('process\t0\t1\t2\t3\t4\t5\t6\t7\t8\n')
   f.write('rate\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\n'%(WAJJ_bincontent, WA_bincontent, fakephoton_bincontent, TTJets_bincontent, VV_bincontent, STop_bincontent, DY_bincontent,fakephoton_bincontent,electronfaketophoton_bincontent))
   f.write('------------\n')
   f.write('lumi\tlnN\t1.025\t1.025\t-\t1.025\t1.025\t1.025\t1.025\t-\t1.025\t#lumi\n')
#   f.write('QCD_%s_%s\tlnN\t-\t1.08\t-\t-\t-\t-\t-\t#0.09 uncertainty on QCD ZA cross section in ele_barrel\n'%('ele','barrel'))
   if fakephoton_bincontent==0:
       f.write('fake_%s_%s\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\t# uncertainty on muon_barrel\n'%('muon','barrel'))
   else: 
       f.write('fake_%s_%s\tlnN\t-\t-\t%0.2f\t-\t-\t-\t-\t-\t-\t# uncertainty on muon_barrel\n'%('muon','barrel',jet[i-1]))
   f.write('VBS_stat_%s_%s_bin_%d\tlnN\t%0.2f\t-\t-\t-\t-\t-\t-\t-\t-\n'%('muon','barrel',i,WAJJ_binerror))
   f.write('QCD_stat_%s_%s_bin_%d\tlnN\t-\t%0.2f\t-\t-\t-\t-\t-\t-\t-\n'%('muon','barrel',i,WA_binerror))
   f.write('fake_photon_stat_%s_%s_bin_%d\tlnN\t-\t-\t%0.2f\t-\t-\t-\t-\t-\t-\n'%('muon','barrel',i,fakephoton_binerror))
   f.write('TTJets_stat_%s_%s_bin_%d\tlnN\t-\t-\t-\t%0.2f\t-\t-\t-\t-\t-\n'%('muon','barrel',i,TTJets_binerror))
   f.write('VV_stat_%s_%s_bin_%d\tlnN\t-\t-\t-\t-\t%0.2f\t-\t-\t-\t-\n'%('muon','barrel',i,VV_binerror))
   f.write('STop_stat_%s_%s_bin_%d\tlnN\t-\t-\t-\t-\t-\t%0.2f\t-\t-\t-\n'%('muon','barrel',i,STop_binerror))
   f.write('DY_stat_%s_%s_bin_%d\tlnN\t-\t-\t-\t-\t-\t-\t%0.2f\t-\t-\n'%('muon','barrel',i,DY_binerror))
   f.write('JES\tlnN\t%0.2f\t%0.2f\t-\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t-\t-\n'%(jes[i-1],jes[i-1],jes[i-1],jes[i-1],jes[i-1],jes[i-1]))
   f.write('JER\tlnN\t%0.2f\t%0.2f\t-\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t-\t-\n'%(jer[i-1],jer[i-1],jer[i-1],jer[i-1],jer[i-1],jer[i-1]))
   f.write('QCDWA_pdf\tlnN\t-\t%0.2f\t-\t-\t-\t-\t-\t-\t-\n'%(pdf_QCD[i-1]))
   f.write('QCDWA_scale\tlnN\t-\t%0.2f\t-\t-\t-\t-\t-\t-\t-\n'%(scale_QCD[i-1]))
   f.write('QCDWA_scale_extra\tlnN\t-\t%0.3f/%0.3f\t-\t-\t-\t-\t-\t-\t-\n'%(scale_QCD_extra_down[i-1],scale_QCD_extra_up[i-1]))
   f.write('signal_pdf\tlnN\t%0.2f\t-\t-\t-\t-\t-\t-\t-\t-\n'%(pdf_ewk[i-1]))
   f.write('signal_scale\tlnN\t%0.2f\t-\t-\t-\t-\t-\t-\t-\t-\n'%(scale_ewk[i-1]))
   f.write('muon_trigger\tlnN\t1.02\t1.02\t-\t1.02\t1.02\t1.02\t1.02\t-\t-\n')
   f.write('muon_efficiency\tlnN\t1.02\t1.02\t-\t1.02\t1.02\t1.02\t1.02\t-\t-\n')
   f.write('pileup\tlnN\t1.01\t1.01\t-\t1.01\t1.01\t1.01\t1.01\t-\t-\n')
   f.write('photon_id\tlnN\t1.03\t1.02\t-\t1.03\t1.03\t1.03\t1.03\t-\t-\n')
   f.write('interference\tlnN\t1.04\t-\t-\t-\t-\t-\t-\t-\t-\n')
#   f.write('ttjets_xs\tlnN\t-\t-\t-\t1.1\t-\t-\t-\t-\t-\n')
#   f.write('VV_xs\tlnN\t-\t-\t-\t-\t1.1\t-\t-\t-\t-\n')
#   f.write('l1prefiring_signal_%s\tlnN\t%0.2f\t-\t-\t-\t-\t-\t-\n'%('ele',l1_signal[i-1]))
   f.write('l1prefiring\tlnN\t%0.2f\t%0.2f\t-\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t-\t-\n'%(l1_signal[i-1],l1_others[i-1],l1_others[i-1],l1_others[i-1],l1_others[i-1],l1_others[i-1]))

   print 'bin ',i,' ',WAJJ_binerror,' ',WA_binerror,' ',fakephoton_binerror,' ',TTJets_binerror,' ',VV_binerror,' ',STop_binerror,' ',DY_binerror,' ',fakelep_binerror,' ',electronfaketophoton_binerror
   


