#include <iostream>
// #include <sys/time.h>
// #include <sys/resource.h>
#include <vector>
#include <TMath.h> 
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TF1.h>
#include <TLorentzVector.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TMinuit.h>
#include <TRandom.h>
#include <TApplication.h>

using namespace std;

int anaTCS(string input_filename,string detector){
// int main(int argc,char *argv[]){
//  string  input_filename=argv[1];
//   string  detector=argv[2];

//     const rlim_t kStackSize = 500L * 1024L * 1024L;   // min stack size = 64 Mb
//     struct rlimit rl;
//     int result;
// 
//     result = getrlimit(RLIMIT_STACK, &rl);
//     if (result == 0)
//     {
// 	cout << "rlim_cur " <<  rl.rlim_cur << endl;
//         if (rl.rlim_cur < kStackSize)
//         {
//             rl.rlim_cur = kStackSize;
//             result = setrlimit(RLIMIT_STACK, &rl);
//             if (result != 0)
//             {
//                 fprintf(stderr, "setrlimit returned result = %d\n", result);
//             }
//         }
// 	cout << "rlim_cur " <<  rl.rlim_cur << endl;        
//     }


// gROOT->Reset();
gStyle->SetPalette(1);
gStyle->SetOptStat(1111111);
// gStyle->SetOptStat(0);


const double DEG=180/3.1416;

//   Double_t cov= 1e-12 * 1e-24; //pb to cm2 coversion
//   Double_t lumi = 1e37;  // 1e37/cm2/s is from 3nA on 15cm long LH2 target
//   Double_t br = 1.;
//   Double_t range_angle = 4*3.1415926;
//   Double_t range_P= (3.62-0)*(1.6-0);  // Q' and t range
//   Double_t time = 50*3600*24;  //50 days in seconds
//   Double_t eff = 0.85;
//   Double_t overall_NOneve = cov *lumi * br * range_angle * range_P * eff * time;  

TLorentzVector target;
double Pmax,etamin,etamax,tmin,tmax,thetamax;
int index;

TH2F *hacceptance_negative_largeangle,*hacceptance_negative_forwardangle,*hacceptance_positive_largeangle,*hacceptance_positive_forwardangle,*hacceptance_negative,*hacceptance_positive;
TH3F *hacceptance_PThetaPhi_negative,*hacceptance_PThetaPhi_positive;
if (detector=="SoLID"){  
// TFile *acceptancefile_negative=new TFile("acceptance_solid_CLEO_JPsi_negative_output.root");
// TH2F *hacceptance_6_negative=(TH2F*) acceptancefile_negative->Get("acceptance_6");
// TH2F *hacceptance_7_negative=(TH2F*) acceptancefile_negative->Get("acceptance_7");
// TFile *acceptancefile_positive=new TFile("acceptance_solid_CLEO_JPsi_positive_output.root");
// TH2F *hacceptance_6_positive=(TH2F*) acceptancefile_positive->Get("acceptance_6");
// TH2F *hacceptance_7_positive=(TH2F*) acceptancefile_positive->Get("acceptance_7");

TFile *acceptancefile_negative=new TFile("acceptance_solid_CLEO_JPsi_negative_target300_output.root");
hacceptance_negative_largeangle=(TH2F*) acceptancefile_negative->Get("acceptance_largeangle");
hacceptance_negative_forwardangle=(TH2F*) acceptancefile_negative->Get("acceptance_forwardangle");
hacceptance_positive_largeangle=(TH2F*) acceptancefile_negative->Get("acceptance_largeangle");
hacceptance_positive_forwardangle=(TH2F*) acceptancefile_negative->Get("acceptance_forwardangle");

// TH2F *hacceptance_negative;
// hacceptance_negative->Add(hacceptance_negative_largeangle,hacceptance_negative_forwardangle);
// TH2F *hacceptance_positive;
// hacceptance_positive->Add(hacceptance_positive_largeangle,hacceptance_positive_forwardangle);

hacceptance_negative=(TH2F*) hacceptance_negative_largeangle->Clone();
hacceptance_negative->Add(hacceptance_negative_forwardangle);
hacceptance_positive=(TH2F*) hacceptance_positive_largeangle->Clone();
hacceptance_positive->Add(hacceptance_positive_forwardangle);

//   TCanvas *c_acceptance = new TCanvas("acceptance","acceptance",1200,900);
//   c_acceptance->Divide(2,3);
//   c_acceptance->cd(1);
//   hacceptance_negative_largeangle->Draw("colz");
//   c_acceptance->cd(3);
//   hacceptance_negative_forwardangle->Draw("colz");  
//   c_acceptance->cd(5);
//   hacceptance_negative->Draw("colz");   
//   c_acceptance->cd(2);
//   hacceptance_positive_largeangle->Draw("colz");
//   c_acceptance->cd(4);
//   hacceptance_positive_forwardangle->Draw("colz");
//   c_acceptance->cd(6);
//   hacceptance_positive->Draw("colz");

//   TCanvas *c_acceptance_ratio = new TCanvas("acceptance_ratio","acceptance_ratio",1000,900);  
//   TH2F *hacceptance_ratio=(TH2F*) hacceptance_negative->Clone();
//   hacceptance_ratio->Divide(hacceptance_negative,hacceptance_positive);
//   hacceptance_ratio->Draw("colz"); 
  
  target.SetPxPyPzE(0.,0.,0.,0.938);
  Pmax=11;
  etamin=0.;
  etamax=0.5;
  tmin=0;  
  tmax=3.8;
  index=4;
  thetamax=60;
}
else if (detector=="CLAS12"){
//   TFile *acceptancefile=new TFile("clas12_acceptance_pipele.root");
  TFile *acceptancefile=new TFile("clas12_acceptance_pipele_largebin.root");

  hacceptance_PThetaPhi_positive=(TH3F*) acceptancefile->Get("acceptance_PThetaPhi_positive");  
  hacceptance_PThetaPhi_negative=(TH3F*) acceptancefile->Get("acceptance_PThetaPhi_negative");
  
//   TCanvas *c_acceptance = new TCanvas("acceptance","acceptance",1200,900);
//   c_acceptance->Divide(2,1);
//   c_acceptance->cd(1);
//   hacceptance_PThetaPhi_positive->Draw();
//   c_acceptance->cd(2);
//   hacceptance_PThetaPhi_negative->Draw();  
  
  target.SetPxPyPzE(0.,0.,0.,0.938);  
  Pmax=11; 
  etamin=0.;  
  etamax=0.5;
  tmin=0;    
  tmax=3.8;
  index=4; 
  thetamax=60;  
}
else if (detector=="EIC"){
  target.SetPxPyPzE(0., -60*sin(6./DEG), -60*cos(6./DEG), sqrt(60*60+0.938*0.938));
  Pmax=70;
  etamin=0.;
  etamax=1;
  tmin=0;  
  tmax=300;
  index=1;  
  thetamax=180;  
}
else {
  cout << " I don't know your detector " << endl;
  return 0;
}

char output_filename[200];
// sprintf(output_filename, "%s_%s_output.root",input_filename.substr(input_filename.find("/"),input_filename.rfind(".")).c_str(),detector.c_str());
sprintf(output_filename, "output2.root");
TFile *outputfile=new TFile(output_filename, "recreate");

TH1F *hcrs_BH_log=new TH1F("crs_BH_log","crs_BH_log",24,-12,12);

TH2F *hMissP_MM2=new TH2F("MissP_MM2","MissP_MM2",100,-0.1,0.1,500,0,5);
TH2F *hMissPxPy=new TH2F("MissPxPy","MissPxPy",100,-1,1,100,-1,1);
TH1F *hMissMM2=new TH1F("MissMM2","MissMM2",100,-0.1,0.1);
TH1F *hMissPx=new TH1F("MissPx","MissPx",100,-1,1);
TH1F *hMissPy=new TH1F("MissPy","MissPy",100,-1,1);

TH1F *hEg=new TH1F("Eg","Eg",120,0,12);
TH1F *hflux_factor=new TH1F("flux_factor","flux_factor",200,-0.001,0.003);
TH1F *hEgflux_factor=new TH1F("Egflux_factor","Egflux_factor",120,0,12);
TH2F *hEg_flux_factor=new TH2F("Eg_flux_factor","Eg_flux_factor",120,0,12,200,-0.001,0.003);

const int n=5;

TH1F *hphoton_mom[n];
TH2F *hproton_theta_mom[n],*helectron_theta_mom[n],*hpositron_theta_mom[n];
TH2F *helectron_positron_theta_mom_ratio[n];
TH2F *hep_mom[n],*hep_theta[n];
TH1F *ht[n],*hs[n],*hep_InvM[n];
TH2F *ht_Q2[n];
TH1F *htau[n];
TH1F *heta[n];
TH2F *htheta_phi_CM[n];
TH1F *hphi_CM[n];
TH2F *htheta_phi_CM_bin[4][n];
TH1F *hphi_CM_bin[4][n];
for(int k=0;k<n;k++){
  char hstname[100];
  sprintf(hstname,"photon_mom_%i",k);
  hphoton_mom[k]=new TH1F(hstname,hstname,120,0,12);
  hphoton_mom[k]->SetTitle("Photon (equivalent);Mom (GeV);#sigma (fb/0.1GeV)");
  sprintf(hstname,"proton_theta_mom_%i",k);
  hproton_theta_mom[k]=new TH2F(hstname,hstname,180,0,180,110,0,Pmax);
  hproton_theta_mom[k]->SetTitle("Proton;#theta (degree);Mom (GeV)");  
  sprintf(hstname,"electron_theta_mom_%i",k);
  helectron_theta_mom[k]=new TH2F(hstname,hstname,180,0,180,110,0,Pmax);  
  helectron_theta_mom[k]->SetTitle("electron;#theta (degree);Mom (GeV)");  
  sprintf(hstname,"positron_theta_mom_%i",k);
  hpositron_theta_mom[k]=new TH2F(hstname,hstname,180,0,180,110,0,Pmax);
  hpositron_theta_mom[k]->SetTitle("positron;#theta (degree);Mom (GeV)");  
  
  sprintf(hstname,"electron_positron_theta_mom_ratio_%i",k);  
  helectron_positron_theta_mom_ratio[k]=new TH2F(hstname,hstname,180,0,180,110,0,Pmax);
    
  sprintf(hstname,"ep_mom_%i",k);
  hep_mom[k]=new TH2F(hstname,hstname,110,0,Pmax,110,0,Pmax);
  sprintf(hstname,"ep_theta_%i",k);
  hep_theta[k]=new TH2F(hstname,hstname,180,0,180,180,0,180);
  sprintf(hstname,"t_%i",k);
  ht[k]=new TH1F(hstname,hstname,100,0,tmax);
  sprintf(hstname,"s_%i",k);
  hs[k]=new TH1F(hstname,hstname,100,0,etamax);
  sprintf(hstname,"ep_InvM_%i",k);
  hep_InvM[k]=new TH1F(hstname,hstname,100,0,4);
  sprintf(hstname,"t_Q2_%i",k);  
  ht_Q2[k]=new TH2F(hstname,hstname,100,0,tmax,100,0,10);  
  
  sprintf(hstname,"tau_%i",k);
  htau[k]=new TH1F(hstname,hstname,1000,0,1);
  sprintf(hstname,"eta_%i",k);
  heta[k]=new TH1F(hstname,hstname,1000,0,1);
  
  sprintf(hstname,"theta_phi_CM_%i",k);
  htheta_phi_CM[k]=new TH2F(hstname,hstname,360,-3.15,3.15,180,0,3.15);
  sprintf(hstname,"phi_CM_%i",k);
  hphi_CM[k]=new TH1F(hstname,hstname,360,-3.15,3.15);
  hphi_CM[k]->SetTitle(";#phi_CM;d#sigma/(dQ dt d#theta d#phi) (pb/GeV^3)");  
  
  for(int l=0;l<4;l++){  
    sprintf(hstname,"theta_phi_CM_bin_%i_%i",l,k);
    htheta_phi_CM_bin[l][k]=new TH2F(hstname,hstname,360,-3.15,3.15,180,0,3.15);
    sprintf(hstname,"phi_CM_bin_%i_%i",l,k);    
    hphi_CM_bin[l][k]=new TH1F(hstname,hstname,360,-3.15,3.15);    
    hphi_CM_bin[l][k]->SetTitle(";#phi_CM;d#sigma/(dQ dt d#theta d#phi) (pb/GeV^3)");
  }
  
}
  
// const int Netabin=1;
// const int Ntbin=1;
// const int NQ2bin=1;
// double etabin_edge[Netabin+1]={12,22};
// double Q2bin_edge[NQ2bin+1]={4,9};
// double tbin_edge[Ntbin+1]={0.,3.5};

const int Netabin=6;
const int NQ2bin=4;
const int Ntbin=5;
// double etabin_edge[Netabin+1]={12,13,14,15,16,17,18,19,20,21,22};
double etabin_edge[Netabin+1]={0.10,0.15,0.17,0.19,0.21,0.25,0.45};
double Q2bin_edge[NQ2bin+1]={4,4.25,4.75,6.0,9};
// double Q2bin_edge[NQ2bin+1]={4,4.25,4.75,5.25,6.0,9};
// double tbin_edge[Ntbin+1]={0.0,0.2,0.4,0.8,1.6,3.2};
double tbin_edge[Ntbin+1]={0.0,0.2,0.3,0.5,1.6,3.8};
// double tbin_edge[Ntbin+1]={0.0,0.3,0.34,0.38,0.42,0.8,1.6,3.2};

float countbin[Netabin][Ntbin][NQ2bin];
TH2F *ht_Q2_etabin[Netabin];
// TH2F *hThetaPhiCM_etabin_Q2bin_tbin[Netabin][NQ2bin][Ntbin];
for(int etabin=0;etabin<Netabin;etabin++){
    char hstname[100];
  sprintf(hstname,"t_Q2_etabin_%i",etabin);  
  ht_Q2_etabin[etabin]=new TH2F(hstname,hstname,50,0,tmax,50,0,10);     
for(int Q2bin=0;Q2bin<NQ2bin;Q2bin++){
for(int tbin=0;tbin<Ntbin;tbin++){  
//   char hstname[100];
//   sprintf(hstname,"ThetaPhiCM_etabin_Q2bin_tbin_%i_%i_%i",etabin,Q2bin,tbin);  
//   hThetaPhiCM_etabin_Q2bin_tbin[etabin][Q2bin][tbin]=new TH2F(hstname,hstname,45,-3.15,3.15,45,0,3.15);  
  countbin[etabin][Q2bin][tbin]=0;
}}}

// vector<TH2F> *hThetaPhiCM_etabin_Q2bin_tbin;
// for(int etabin=0;etabin<Netabin;etabin++){
// for(int tbin=0;tbin<Ntbin;tbin++){
// for(int Q2bin=0;Q2bin<NQ2bin;Q2bin++){
//   char hstname[100];
//   sprintf(hstname,"ThetaPhiCM_etabin_Q2bin_tbin_%i_%i_%i",etabin,tbin,Q2bin);  
//   TH2F *hThetaPhiCM_etabin_Q2bin_tbin_temp=new TH2F(hstname,hstname,90,-3.15,3.15,45,0,3.15);  
//   hThetaPhiCM_etabin_Q2bin_tbin->push_back(*hThetaPhiCM_etabin_Q2bin_tbin_temp);
// }}}

TH1F *ht_final=new TH1F("t_final","t_final",50,tmin,tmax);
TH1F *heta_final=new TH1F("eta_final","eta_final",50,etamin,etamax);
TH1F *hQ2_final=new TH1F("Q2_final","Q2_final",70,3,10);
TH2F *heta_t_final=new TH2F("eta_t_final","eta_t_final",50,etamin,etamax,50,tmin,tmax);
TH2F *heta_Q2_final=new TH2F("eta_Q2_final","eta_Q2_final",50,etamin,etamax,70,3,10);
TH2F *ht_Q2_final=new TH2F("t_Q2_final","t_Q2_final",50,tmin,tmax,70,3,10);
// TH3F *heta_t_Q2_final=new TH3F("eta_t_Q2_final","eta_t_Q2_final",50,etamin,etamax,50,tmin,tmax,70,3,10);

TH1F *ht_final_bin=new TH1F("t_final_bin","t_final_bin",Ntbin,tbin_edge);
TH1F *heta_final_bin=new TH1F("eta_final_bin","eta_final_bin",Netabin,etabin_edge);
TH1F *hQ2_final_bin=new TH1F("Q2_final_bin","Q2_final_bin",NQ2bin,Q2bin_edge);
TH2F *heta_t_final_bin=new TH2F("eta_t_final_bin","eta_t_final_bin",Netabin,etabin_edge,Ntbin,tbin_edge);
TH2F *heta_Q2_final_bin=new TH2F("eta_Q2_final_bin","eta_Q2_final_bin",Netabin,etabin_edge,NQ2bin,Q2bin_edge);
TH2F *ht_Q2_final_bin=new TH2F("t_Q2_final_bin","t_Q2_final_bin",Ntbin,tbin_edge,NQ2bin,Q2bin_edge);
// TH3F *heta_t_Q2_final_bin=new TH3F("eta_t_Q2_final_bin","eta_t_Q2_final_bin",Netabin,etabin_edge,Ntbin,tbin_edge,Ntbin,tbin_edge);

TH2F *hgen_t_Q2[20];
TH2F *hgen_theta_phi_CM[20];
for(int k=0;k<20;k++){
   char hstname[100];
//    sprintf(hstname,"gen_t_InvM2_ep_%i",k);
//    hgen_t_Q2[k]=new TH2F(hstname,hstname,200,0,20,900,3,12);
      sprintf(hstname,"gen_t_Q2_%i",k);
      hgen_t_Q2[k]=new TH2F(hstname,hstname,200,0,2,250,0,20);
      sprintf(hstname,"hgen_theta_phi_CM_%i",k);
//    hgen_theta_phi_CM[k]=new TH2F(hstname,hstname,360,-3.15,3.15,180,0,3.15);      
      hgen_theta_phi_CM[k]=new TH2F(hstname,hstname,360,-3.15,3.15,100,-1,1);      
}


TFile *file=new TFile(input_filename.c_str());
    if (file->IsZombie()) {
       cout << "Error opening file" << input_filename << endl;
       return 0;
//        exit(-1);
}
else cout << "open file " << input_filename << endl;
TTree *Ttr1 = (TTree*) file->Get("tr1");

Double_t Q2,t_t,psf,psf_flux,crs_BH,flux_factor;
TLorentzVector *L_em,*L_ep,*L_prot;
Ttr1->SetBranchAddress("Q2",&Q2);
Ttr1->SetBranchAddress("t",&t_t);
Ttr1->SetBranchAddress("psf",&psf);
Ttr1->SetBranchAddress("psf_flux",&psf_flux);
Ttr1->SetBranchAddress("crs_BH",&crs_BH);
Ttr1->SetBranchAddress("flux_factor",&flux_factor);
Ttr1->SetBranchAddress("L_em",&L_em);
Ttr1->SetBranchAddress("L_ep",&L_ep);
Ttr1->SetBranchAddress("L_prot",&L_prot);

Int_t nevent = (Int_t)Ttr1->GetEntries();
Int_t nselected = 0;
cout << "nevent " << nevent << endl;

  Double_t cov= 1e-12 * 1e-24; //pb to cm2 coversion
  Double_t lumi = 1e37;  // 1e37/cm2/s is from 3nA on 15cm long LH2 target
  Double_t br = 1.;
  Double_t time = 50*3600*24;  //50 days in seconds
  Double_t eff = 0.85;
  Double_t overall_NOpsf = cov *lumi * br * eff * time /nevent;

  Int_t counter;
  Int_t countd = 1;
  cout << "|___________________|" << endl;
  cout << "|" << flush;

  int yescounter=0,nocounter=0;
  
      double weight[n]={1,1,1,1};
for (Int_t i=0;i<nevent;i++) {
 
    Ttr1->GetEntry(i);  

//     cout << i << "\r"; 
    
    if (i<10)   cout << Q2 << " " << t_t << " " << psf << " " << psf_flux << " " << crs_BH << " " << flux_factor << " " << L_em->M() << " " << L_ep->M() << " " << L_prot->M() << endl;
    
    Double_t id = i;
    Double_t neventd = nevent;
    if(floor(id/neventd*20) == countd){   
      cout << "=" << flush;
      countd++;
      if(countd == 20){
	cout << "|" << endl;
      }
    }    
    
  if (crs_BH > 10000000)     if (i<10)   cout << Q2 << " " << t_t << " " << psf << " " << psf_flux << " " << crs_BH << " " << flux_factor << " " << L_em->M() << " " << L_ep->M() << " " << L_prot->M() << endl;



      hcrs_BH_log->Fill(log10(crs_BH));
  
//       if (isinf(crs_BH) || isnan(crs_BH) ) {cout << nevt << " " << crs_BH << endl; continue;}
//       if (isinf(crs_BH) || TMath::IsNaN(crs_BH) ) {nocounter++; continue;}
//       if (TMath::IsNaN(crs_BH)) {nocounter++; continue;}      
//      cout << i << " " << crs_BH << endl;
      
      yescounter++;      

      TLorentzVector pr=*L_prot,e=*L_em,p=*L_ep;
      
      ///smear by resolution mom 4%, theta 1mr, phi 6mr
      pr.SetRho(gRandom->Gaus(pr.P(),pr.P()*0.04));
      pr.SetTheta(gRandom->Gaus(pr.Theta(),1e-3));
      pr.SetPhi(gRandom->Gaus(pr.Phi(),6e-3));
      pr.SetXYZM(pr.Px(),pr.Py(),pr.Pz(),0.938);
      p.SetRho(gRandom->Gaus(p.P(),p.P()*0.04));
      p.SetTheta(gRandom->Gaus(p.Theta(),1e-3));
      p.SetPhi(gRandom->Gaus(p.Phi(),6e-3));
      p.SetXYZM(p.Px(),p.Py(),p.Pz(),0.000511);            
      e.SetRho(gRandom->Gaus(e.P(),e.P()*0.04));
      e.SetTheta(gRandom->Gaus(e.Theta(),1e-3));
      e.SetPhi(gRandom->Gaus(e.Phi(),6e-3));  
      e.SetXYZM(e.Px(),e.Py(),e.Pz(),0.000511);
  
      double M=0.938;      
//       TLorentzVector target(0.,0.,0.,M);                  
      TLorentzVector ph=pr+e+p-target;
      TLorentzVector ep=e+p;
      TLorentzVector beam(0.,0.,11.,11.);
      TLorentzVector Miss=beam-ph;
      
//       cout << ph.P() << " " << ph.E() << " " << ph.Theta() << " " << ph.Phi()  << endl;
//       ph.SetXYZM(0,0,ph.P(),0);
   
      double ph_mom=ph.P(),pr_mom=pr.P(),e_mom=e.P(),p_mom=p.P();
      double ph_theta=ph.Theta(),pr_theta=pr.Theta(),e_theta=e.Theta(),p_theta=p.Theta();
      double ph_phi=ph.Phi(),pr_phi=pr.Phi(),e_phi=e.Phi(),p_phi=p.Phi();
      
      double InvM_ep=ep.M();
      double t=-(pr-target).M2();
      double s=(ph+target).M2();
      double W=(ph+target).M();
      double tau=InvM_ep*InvM_ep/(s-M*M);
      double eta=tau/(2-tau);
      double tmin=4*eta*eta*M*M/(1-eta*eta);
      
      if(InvM_ep <2 || InvM_ep > 3) continue;      
      
//       cout << " t " << t_t << " " << -t << endl;
//       cout << " M " << Q2 << " " << InvM_ep*InvM_ep << endl;      
//       cout << InvM_ep << " " << t << " " << s << " " << W << endl; 

      TLorentzVector target_CM=target,pr_CM=pr,e_CM=e,p_CM=p; 
      target_CM.Boost(-ep.BoostVector()); 
      pr_CM.Boost(-ep.BoostVector());
      e_CM.Boost(-ep.BoostVector());
      p_CM.Boost(-ep.BoostVector());
      TVector3 e3=-pr_CM.Vect().Unit();
      TVector3 e2=(e3.Cross(target_CM.Vect())).Unit();
      TVector3 e1=e2.Cross(e3);                          
      double z=e_CM.Vect().Dot(e3),y=e_CM.Vect().Dot(e2),x=e_CM.Vect().Dot(e1);
      double theta_CM=acos(z/sqrt(x*x+y*y+z*z));
      double phi_CM=acos(x/sqrt(x*x+y*y));
      if (y<0) phi_CM=-phi_CM;
//       cout << " phi_CM " << phi_cm  << " " << phi_CM << endl;
//       cout << " th_cm " << th_cm << " " << theta_CM << endl;   
      
//       cout << e_CM.Vect().Angle(p_CM.Vect()) << endl; 
//       double theta_CM=e_CM.Vect().Angle(-pr_CM.Vect());
//       TVector3 plane_decay=(e.Vect().Cross(p.Vect())).Unit();
//       TVector3 plane_scatter=(ph.Vect().Cross(pr.Vect())).Unit();
//       double phi_CM=plane_decay.Angle(plane_scatter);
//       cout << theta_CM <<  " " << phi_CM << endl;
        
      hEg->Fill(ph_mom);
      hflux_factor->Fill(flux_factor);
      hEgflux_factor->Fill(ph_mom,flux_factor);
      hEg_flux_factor->Fill(ph_mom,flux_factor);      

    double acc_proton=0,acc_positron=0,acc_electron=0;
      if (detector=="SoLID"){ 
       acc_proton=hacceptance_positive->GetBinContent(hacceptance_positive->FindBin(pr_theta*DEG,pr_mom));  
       acc_positron=hacceptance_positive->GetBinContent(hacceptance_positive->FindBin(p_theta*DEG,p_mom));
       acc_electron=hacceptance_negative->GetBinContent(hacceptance_negative->FindBin(e_theta*DEG,e_mom));    
       
       if (hacceptance_positive_largeangle->GetBinContent(hacceptance_positive_largeangle->FindBin(p_theta*DEG,p_mom)) > 0 && hacceptance_negative_largeangle->GetBinContent(hacceptance_negative_largeangle->FindBin(e_theta*DEG,e_mom)) > 0) {acc_positron=0; acc_electron=0;} //cut away two lepton in largeangle only   
       if (p_mom > 4.9 && e_mom > 4.9) {acc_positron=0; acc_electron=0;} //cut away two lepton exceed CC limit
       if (hacceptance_positive_largeangle->GetBinContent(hacceptance_positive_largeangle->FindBin(pr_theta*DEG,pr_mom)) > 0 && pr_mom > 2.5)  acc_proton=0; //cut away 2.5 at largeangle  for proton
       if (hacceptance_positive_forwardangle->GetBinContent(hacceptance_positive_forwardangle->FindBin(pr_theta*DEG,pr_mom)) > 0 && pr_mom > 4.6)  acc_proton=0; //cut away 4.6 at forwardangel for proton
      }   
      else if (detector=="CLAS12"){
	  acc_proton=hacceptance_PThetaPhi_positive->GetBinContent(hacceptance_PThetaPhi_positive->FindBin(pr_phi*DEG+180,pr_theta*DEG,pr_mom));
	  if (p_theta*DEG<36) acc_positron=hacceptance_PThetaPhi_positive->GetBinContent(hacceptance_PThetaPhi_positive->FindBin(p_phi*DEG+180,p_theta*DEG,p_mom));
	  if (e_theta*DEG<36) acc_electron=hacceptance_PThetaPhi_negative->GetBinContent(hacceptance_PThetaPhi_negative->FindBin(e_phi*DEG+180,e_theta*DEG,e_mom));
	  ///note CLAS12 phi (0,360), TCS sim phi (-180,180) 
	  if (acc_proton < 0.9 || acc_positron < 0.9 || acc_electron < 0.9) {acc_proton=acc_positron=acc_electron=0;}  //cut away unsure low acceptance	  
      }
      else if (detector=="EIC"){}
      else {return 0;}
      double acc=acc_proton*acc_positron*acc_electron;
      
      /// cut to quasi real
      double acc_cut=1;
      if(fabs(Miss.M2())>0.02 || fabs(Miss.Px()/Miss.P())>0.2 || fabs(Miss.Py()/Miss.P())>0.2) acc_cut=0;

// 	cout << acc << " " << acc_proton << " " << acc_positron << " " << acc_electron << endl;
// 	cout << pr_theta*DEG << " " << pr_phi*DEG << " " << p_theta*DEG << " " << p_phi*DEG << " " << e_theta*DEG << " " << e_phi*DEG << endl;
  
      weight[0]=1;
      weight[1]=crs_BH*psf*psf_flux*flux_factor;
      weight[2]=weight[1]*acc;
      weight[3]=weight[2]*overall_NOpsf;
      weight[4]=weight[3]*acc_cut;
// //       doubleD weight[n]={1,crs_BH*psf*psf_flux*flux_factor,crs_BH*psf*psf_flux*flux_factor*acc,crs_BH*psf*psf_flux*flux_factor*acc*overall_NOpsf};
      for(int k=0;k<n;k++){
	hphoton_mom[k]->Fill(ph_mom,weight[k]);
	hproton_theta_mom[k]->Fill(pr_theta*DEG,pr_mom,weight[k]);
	helectron_theta_mom[k]->Fill(e_theta*DEG,e_mom,weight[k]);
	hpositron_theta_mom[k]->Fill(p_theta*DEG,p_mom,weight[k]);
	
	hep_mom[k]->Fill(p_mom,e_mom,weight[k]);
	hep_theta[k]->Fill(p_theta*DEG,e_theta*DEG,weight[k]);
	ht[k]->Fill(t,weight[k]);
	hs[k]->Fill(s,weight[k]);
	hep_InvM[k]->Fill(InvM_ep,weight[k]);
	ht_Q2[k]->Fill(t,Q2,weight[k]);
	hep_theta[k]->Fill(p_theta*DEG,e_theta*DEG,weight[k]);
	htheta_phi_CM[k]->Fill(phi_CM,theta_CM,weight[k]);
	hphi_CM[k]->Fill(phi_CM,weight[k]);
	
	if (17.5 < s && s < 19.5){
	  if (0.1 < t && t < 0.9){
	    htheta_phi_CM_bin[int((t-0.1)/0.2)][k]->Fill(phi_CM,theta_CM,weight[k]);
  
// 	    cout << InvM_ep << " " << s << endl;
// 	    if (3.1415926/4.<theta_CM && theta_CM <3.*3.1415926/4. && fabs(InvM_ep*InvM_ep-5.)<0.1 && fabs(sqrt(s)-sqrt(20))<0.1){	      
// 		hphi_CM_bin[int((t-0.1)/0.2)][k]->Fill(phi_CM,weight[k]);
// 	    }
	    
	    hphi_CM_bin[int((t-0.1)/0.2)][k]->Fill(phi_CM,weight[k]);
	  }
	}
      }              

        hMissP_MM2->Fill(Miss.M2(),Miss.P(),weight[index-1]);
        hMissPxPy->Fill(Miss.Px()/Miss.P(),Miss.Py()/Miss.P(),weight[index-1]);
	hMissMM2->Fill(Miss.M2(),weight[index-1]);
        hMissPx->Fill(Miss.Px()/Miss.P(),weight[index-1]);
        hMissPy->Fill(Miss.Py()/Miss.P(),weight[index-1]);
		
	
	ht_final->Fill(t,weight[index]);
	heta_final->Fill(eta,weight[index]);
	hQ2_final->Fill(Q2,weight[index]);
	heta_t_final->Fill(eta,t,weight[index]);
	heta_Q2_final->Fill(eta,Q2,weight[index]);
	ht_Q2_final->Fill(t,Q2,weight[index]);
// 	heta_t_Q2_final->Fill(eta,t,Q2,weight[index]);

	ht_final_bin->Fill(t,weight[index]);
	heta_final_bin->Fill(eta,weight[index]);
	hQ2_final_bin->Fill(Q2,weight[index]);
	heta_t_final_bin->Fill(eta,t,weight[index]);
	heta_Q2_final_bin->Fill(eta,Q2,weight[index]);
	ht_Q2_final_bin->Fill(t,Q2,weight[index]);
// 	heta_t_Q2_final_bin->Fill(eta,t,Q2,weight[index]);
        
//       if (6 < ph_mom && ph_mom < 11) {
// 	hgen_t_Q2[int((ph_mom-6)/0.25)]->Fill(t,Q2,psf);
// //       hgen_t_Q2[int((ph_mom-6)/0.25)]->Fill(t,InvM_ep);      
//       
// 	if (0.5<t && t <1.6 && 1 < Q2 && Q2< 4) hgen_theta_phi_CM[int((ph_mom-6)/0.25)]->Fill(phi_CM,cos(theta_CM));
//       }

//       int etabin=int((s-12.)/((22.-12.)/Netabin));
//       int tbin=int((t-0.)/((3.2-0.)/Ntbin));
//       int Q2bin=int((Q2-4.)/((9.-4.)/NQ2bin));
	
	int etabin=-1,Q2bin=-1,tbin=-1;
	for (int k=0;k<Netabin;k++)  {
	  if (*(etabin_edge+k) <= eta && eta < *(etabin_edge+k+1)) {
	    etabin=k; 
// 	    cout << "s " << s << " " << etabin << " " << *(etabin_edge+k) << " " << *(etabin_edge+k+1) <<endl;
	  }  
	}
	for (int k=0;k<NQ2bin;k++) {
	  if (*(Q2bin_edge+k) <= Q2 && Q2 < *(Q2bin_edge+k+1)) {
	    Q2bin=k;
// 	    cout << "Q2 " << Q2 << " " << Q2bin << " " << *(Q2bin_edge+k) << " " << *(Q2bin_edge+k+1) <<endl;
	  }
	}
	for (int k=0;k<Ntbin;k++)  {
	  if (*(tbin_edge+k) <= t && t < *(tbin_edge+k+1)) {
	    tbin=k;
// 	    cout << "t " << t << " " << tbin << " " << *(tbin_edge+k) << " " << *(tbin_edge+k+1) <<endl;
	  }
	}	
	
      if ( (0 <= etabin && etabin < Netabin) && (0 <= Q2bin && Q2bin < NQ2bin) && (0<= tbin && tbin < Ntbin) ){  
// 	cout << "in range " << etabin << " " << tbin << " " << Q2bin << endl;
// 	hThetaPhiCM_etabin_Q2bin_tbin[etabin][Q2bin][tbin]->Fill(phi_CM,theta_CM,weight[index]);
// 	vector<TH2F>::iterator iter=hThetaPhiCM_etabin_Q2bin_tbin->begin()+(etabin*Netabin+tbin*Ntbin+Q2bin*NQ2bin);
// 	iter->Fill(phi_CM,theta_CM,weight[n-1]);

	countbin[etabin][Q2bin][tbin] = countbin[etabin][Q2bin][tbin] + weight[index];
	ht_Q2_etabin[etabin]->Fill(t,Q2,weight[index]);
      }
      else {
	cout << etabin << " " << Q2bin  << " " << tbin << endl;
	cout << "out of range " << eta << " " << Q2 << " " << t << endl;	
      }    

	
// 	  cout << etabin << " " << tbin << " " << Q2bin << " " << countbin[etabin][Q2bin][tbin] <<  endl;


}

      cout << "yescounter " << yescounter << " nocounter " << nocounter << endl;      
  
for(int etabin=0;etabin<Netabin;etabin++){
for(int Q2bin=0;Q2bin<NQ2bin;Q2bin++){
for(int tbin=0;tbin<Ntbin;tbin++){  
//   double a=hThetaPhiCM_etabin_Q2bin_tbin[etabin][Q2bin][tbin]->Integral();
//   cout << etabin << " " << Q2bin  << " " << tbin << " " << a << endl;
  
//   cout << etabin << " " << tbin << " " << Q2bin << endl;
//   Double_t a=countbin[etabin][Q2bin][tbin];
//   if (isinf(a) || TMath::IsNaN(a)) cout << etabin << " " << tbin << " " << Q2bin << " " << " bad" <<  endl;

  cout << etabin << " " << Q2bin << " " <<  tbin << " "  << countbin[etabin][Q2bin][tbin] <<  endl;

//     vector<TH2F>::iterator iter=hThetaPhiCM_etabin_Q2bin_tbin->begin()+(etabin*Netabin+tbin*Ntbin+Q2bin*NQ2bin);
//     cout << etabin << " " << tbin << " " << Q2bin << " " << iter->Integral() <<  endl;    
      
}}}        

TCanvas *c_theta_mom = new TCanvas("theta_mom","theta_mom",1500,900);
c_theta_mom->Divide(5,n);
for(int k=0;k<n;k++){
//   double max,min;
//   max=log10(hproton_theta_mom[k]->GetBinContent(hproton_theta_mom[k]->GetMaximumBin()))+1;
//   min=log10(hproton_theta_mom[k]->GetBinContent(hproton_theta_mom[k]->GetMinimumBin()))-1;
  
  c_theta_mom->cd(5*k+1);
  hphoton_mom[k]->Draw();
  c_theta_mom->cd(5*k+2);
  gPad->SetLogz(1);  
//  hproton_theta_mom[k]->SetMinimum(min);
 // hproton_theta_mom[k]->SetMaximum(max);     
//   hproton_theta_mom[k]->SetAxisRange(0,60,"X");
  hproton_theta_mom[k]->Draw("colz");
  c_theta_mom->cd(5*k+3);
  gPad->SetLogz(1);
//   helectron_theta_mom[k]->SetMinimum(min);
//   helectron_theta_mom[k]->SetMaximum(max);
//   helectron_theta_mom[k]->SetAxisRange(0,40,"X");  
  helectron_theta_mom[k]->Draw("colz");
  c_theta_mom->cd(5*k+4);
  gPad->SetLogz(1);
// hpositron_theta_mom[k]->SetMinimum(min);
 // hpositron_theta_mom[k]->SetMaximum(max);  
//   hpositron_theta_mom[k]->SetAxisRange(0,40,"X");  
  hpositron_theta_mom[k]->Draw("colz");
  c_theta_mom->cd(5*k+5);
  gPad->SetLogz(1);  
  helectron_positron_theta_mom_ratio[k]->Divide(helectron_theta_mom[k],hpositron_theta_mom[k]);  
//   max=log10(hproton_theta_mom[k]->GetBinContent(hproton_theta_mom[k]->GetMaximumBin()))+1;
//   min=log10(hproton_theta_mom[k]->GetBinContent(hproton_theta_mom[k]->GetMinimumBin()))-1;
//   helectron_positron_theta_mom_ratio[k]->SetMinimum(min);
//   helectron_positron_theta_mom_ratio[k]->SetMaximum(max);
//   helectron_positron_theta_mom_ratio[k]->SetAxisRange(0,40,"X");
  helectron_positron_theta_mom_ratio[k]->Draw("colz");  
}

TCanvas *c_theta_mom_final = new TCanvas("theta_mom_final","theta_mom_final",1200,800);
c_theta_mom_final->Divide(2,2);
for(int k=index;k<index+1;k++){
  c_theta_mom_final->cd(1);
  gPad->SetLogz(1);  
//   hphoton_mom[k]->Draw();
  hep_mom[k]->Draw("colz");
  c_theta_mom_final->cd(2);
  gPad->SetLogz(1);
  hproton_theta_mom[k]->SetMinimum(0.01);
  hproton_theta_mom[k]->SetAxisRange(0,thetamax,"X");  
  hproton_theta_mom[k]->Draw("colz");
  c_theta_mom_final->cd(3);
  gPad->SetLogz(1);
  helectron_theta_mom[k]->SetMinimum(0.01);
  helectron_theta_mom[k]->SetAxisRange(0,thetamax,"X");    
  helectron_theta_mom[k]->Draw("colz");
  c_theta_mom_final->cd(4);
  gPad->SetLogz(1);
  hpositron_theta_mom[k]->SetMinimum(0.01);
  hpositron_theta_mom[k]->SetAxisRange(0,thetamax,"X");    
  hpositron_theta_mom[k]->Draw("colz");
}

int nc=10;
TCanvas *c_other = new TCanvas("other","other",1800,900);
c_other->Divide(nc,n);
for(int k=0;k<n;k++){
  c_other->cd(nc*k+1);
  gPad->SetLogz(1);
  hep_mom[k]->SetMinimum(0.01);
  hep_mom[k]->Draw("colz");
  c_other->cd(nc*k+2);
  gPad->SetLogz(1);
  hep_theta[k]->SetMinimum(0.01);
  hep_theta[k]->Draw("colz");
  c_other->cd(nc*k+3);
  gPad->SetLogy(1);  
  ht[k]->Draw();
  c_other->cd(nc*k+4);
  gPad->SetLogy(1);  
  hs[k]->Draw();
  c_other->cd(nc*k+5);
  gPad->SetLogy(1);  
  hep_InvM[k]->Draw();
  c_other->cd(nc*k+6);
  gPad->SetLogz(1);
  ht_Q2[k]->Draw("colz");
  c_other->cd(nc*k+7);
//   gPad->SetLogy(1);  
//   htau[k]->Draw();
  c_other->cd(nc*k+8);
//   gPad->SetLogy(1);  
//   heta[k]->Draw();
  c_other->cd(nc*k+9);
//   gPad->SetLogz(1);
  htheta_phi_CM[k]->SetMinimum(0.01);
  htheta_phi_CM[k]->Draw("colz");
  c_other->cd(nc*k+10);
  hphi_CM[k]->Draw();
}



TCanvas *c_theta_phi_CM_bin = new TCanvas("theta_phi_CM_bin","theta_phi_CM_bin",1600,900);
c_theta_phi_CM_bin->Divide(4,n);
for(int k=0;k<n;k++){
  for(int l=0;l<4;l++){
   c_theta_phi_CM_bin->cd(4*k+l+1);
   gPad->SetLogz(1);
   htheta_phi_CM_bin[l][k]->SetMinimum(0.01);   
   htheta_phi_CM_bin[l][k]->Draw("colz");
  }
}

TCanvas *c_theta_phi_CM_bin_final = new TCanvas("theta_phi_CM_bin_final","theta_phi_CM_bin_final",1000,800);
c_theta_phi_CM_bin_final->Divide(2,2);
for(int l=0;l<4;l++){
   c_theta_phi_CM_bin_final->cd(l+1);
   gPad->SetLogz(1);
   htheta_phi_CM_bin[l][3]->SetMinimum(0.01);   
   htheta_phi_CM_bin[l][3]->Draw("colz");  
   cout << htheta_phi_CM_bin[l][3]->Integral() << endl;  
}

TCanvas *c_phi_CM_bin = new TCanvas("phi_CM_bin","phi_CM_bin",1600,900);
c_phi_CM_bin->Divide(4,n);
for(int k=0;k<n;k++){
  for(int l=0;l<4;l++){
   c_phi_CM_bin->cd(4*k+l+1);
   hphi_CM_bin[l][k]->Draw();
  }
}

TCanvas *c_gen_t_Q2 = new TCanvas("gen_t_Q2","gen_t_Q2",1600,900);
c_gen_t_Q2->Divide(5,4);
for(int k=0;k<20;k++){
   c_gen_t_Q2->cd(k+1);
   hgen_t_Q2[k]->Draw("colz");
}

TCanvas *c_gen_theta_phi_CM = new TCanvas("gen_theta_phi_CM","gen_theta_phi_CM",1600,900);
c_gen_theta_phi_CM->Divide(5,4);
for(int k=0;k<20;k++){
   c_gen_theta_phi_CM->cd(k+1);
   hgen_theta_phi_CM[k]->Draw("colz");
}

TCanvas *c_crs_BH_log = new TCanvas("crs_BH_log","crs_BH_log",600,600);
gPad->SetLogy(1);
hcrs_BH_log->Draw();

TCanvas *c_Miss_2D = new TCanvas("Miss_2D","Miss_2D",1300,600);
c_Miss_2D->Divide(2,1);
c_Miss_2D->cd(1);
gPad->SetLogz(1);
hMissP_MM2->Draw("colz");
c_Miss_2D->cd(2);
gPad->SetLogz(1);
hMissPxPy->Draw("colz");

TCanvas *c_Miss_1D = new TCanvas("Miss_1D","Miss_1D",1800,600);
c_Miss_1D->Divide(3,1);
c_Miss_1D->cd(1);
gPad->SetLogy(1);
hMissMM2->Draw();
c_Miss_1D->cd(2);
gPad->SetLogy(1);
hMissPx->Draw();
c_Miss_1D->cd(3);
gPad->SetLogy(1);
hMissPy->Draw();

TCanvas *c_flux_factor = new TCanvas("flux_factor","flux_factor",600,600);
c_flux_factor->Divide(2,2);
c_flux_factor->cd(1);
hEg->Draw();
c_flux_factor->cd(2);
hflux_factor->Draw();
c_flux_factor->cd(3);
hEgflux_factor->Draw();
c_flux_factor->cd(4);
hEg_flux_factor->Draw("colz");

// cout << "hEgflux_factor " << hEgflux_factor->Integral() << endl;

TCanvas *c_kin = new TCanvas("kin","kin",1800,600);
c_kin->Divide(6,2);
c_kin->cd(1);
heta_final->Draw();
c_kin->cd(2);
ht_final->Draw();
c_kin->cd(3);
hQ2_final->Draw();
c_kin->cd(4);
heta_t_final->Draw("colz");
c_kin->cd(5);
heta_Q2_final->Draw("colz");
c_kin->cd(6);
ht_Q2_final->Draw("colz");
c_kin->cd(7);
heta_final_bin->Draw();
c_kin->cd(8);
ht_final_bin->Draw();
c_kin->cd(9);
hQ2_final_bin->Draw();
c_kin->cd(10);
heta_t_final_bin->Draw("colz");
c_kin->cd(11);
heta_Q2_final_bin->Draw("colz");
c_kin->cd(12);
ht_Q2_final_bin->Draw("colz");

// TCanvas *c_kin_3D = new TCanvas("kin_3D","kin_3D",1600,800);
// c_kin_3D->Divide(2,1);
// c_kin_3D->cd(1);
// heta_t_Q2_final->Draw();
// c_kin_3D->cd(2);
// heta_t_Q2_final_bin->Draw();

TCanvas *c_t_Q2_etabin = new TCanvas("t_Q2_etabin","t_Q2_etabin",1600,800);
c_t_Q2_etabin->Divide(Netabin/2,2);
for(int etabin=0;etabin<Netabin;etabin++){
c_t_Q2_etabin->cd(etabin+1);
ht_Q2_etabin[etabin]->Draw("colz");
}

// cout << "total events " << heta_Q2_final_bin->Integral() << endl;
// for(int etabin=0;etabin<Netabin;etabin++){
// for(int Q2bin=0;Q2bin<NQ2bin;Q2bin++){
// // for(int tbin=0;tbin<Ntbin;tbin++){  
//   cout << heta_Q2_final_bin->GetBinContent(etabin+1,Q2bin+1) << endl;  
// // }
// }}

outputfile->Write();
outputfile->Flush();

// rootapp->Run();


 return 0;


}