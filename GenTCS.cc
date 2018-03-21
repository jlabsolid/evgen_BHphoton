#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TTree.h>
#include <TRandom2.h>
#include <TLorentzVector.h>
#include <TGenPhaseSpace.h>
#include "kin_funcs.h"
#include "TTCS_crs.hh"
#include "TTCS_kine.hh"

#include <iostream>

using namespace std;

double N_EPA(double, double, double); // 1st argument is Eg, the secon one is Q2max (0.02)
double Brem_Approx(double, double,double); // argument Eg, Eb, l as target length

int main(int argc, char* argv[])
{ 
  double Eb=11.,Eg_min=4.2,Qp2min=4,Qp2max=9,Q2max=0.05,tlim=3.2,Ep=0.,l=15;
  int Nevent=1e6;
  
  if (argc != 10 || argv[1]=="-h") {
    cout << "input: Eb(GeV) Egmin(GeV) Q'2min(GeV2) Q'2max(GeV2) Q2max(GeV2) tlim(GeV2) Ep(GeV) l(cm) Nevent" << endl; 
    return 0;    
  }
  else {        
    Eb=atof(argv[1]);
    Eg_min=atof(argv[2]);
    Qp2min=atof(argv[3]); 
    Qp2max=atof(argv[4]);     
    Q2max=atof(argv[5]);     
    tlim=atof(argv[6]);
    Ep=atof(argv[7]);
    l=atof(argv[8]);    
    Nevent=int(atof(argv[9]));
  }

      tlim = -tlim;
      
//     const double Ep = 0.;    
//   const double Eb = 11.;
// // 2*0.938*(0.938-sqrt(0.938^2+2.5^2))=3.2
//   const double tlim = -3.2; // limit of t distribution
// //2*0.938*(0.938-sqrt(0.938^2+4.6^2))=7
// //   const double tlim = -7.0; // limit of t distribution  
//  const double Eg_min = 6; //Gev
  
//   const double Ep = 60.;    
// //   const double Eb = 6.;
//   const double Eb = 11.;  
//   const double tlim = -200; // limit of t distribution
//   const double Eg_min = 0.01;

//     const int Nevent = 100000;
    
  const double PI = 3.14159265358979312;
  const double radian = 57.2957795130823229;
  
  const double Mp = 0.9383;
  const double Me = 0.00051;

  TFile *file_out = new TFile(Form("GenTCS_Eb%s_Egmin%s_Qp2min%s_Qp2max%s_Q2max%s_tlim%s_Ep%s_l%s_%s.root",argv[1],argv[2],argv[3],argv[4],argv[5],argv[6],argv[7],argv[8],argv[9]), "Recreate");
  TObjArray *Hlist = new TObjArray();
  
  TLorentzVector L_em, L_ep, L_prot;
  TLorentzVector L_gprime;

  double Q2, t;
  double psf;
  double crs_BH;
  double psf_flux;
  double flux_factor;
  double delt_perp;
  
  double em_px,em_py,em_pz,ep_px,ep_py,ep_pz,prot_px,prot_py,prot_pz;
  
  TTree *tr1 = new TTree("tr1", "TCS kinematics");
//   tr1->Branch("L_em", "TLorentzVector", &L_em, 3200, 99);
//   tr1->Branch("L_ep", "TLorentzVector", &L_ep, 3200, 99);
//   tr1->Branch("L_prot", "TLorentzVector", &L_prot, 3200, 99);
  tr1->Branch("Q2", &Q2, "Q2/D");
  tr1->Branch("t", &t, "t/D");
  tr1->Branch("psf", &psf, "psf/D");
  tr1->Branch("crs_BH", &crs_BH, "crs_BH/D");
  //tr1->Branch("delt_perp", &delt_perp, "delt_perp/D");
  tr1->Branch("psf_flux", &psf_flux, "psf_flux/D");
  tr1->Branch("flux_factor", &flux_factor, "flux_factor/D");
  tr1->Branch("em_px", &em_px, "em_px/D");
  tr1->Branch("em_py", &em_py, "em_py/D");  
  tr1->Branch("em_pz", &em_pz, "em_pz/D");  
  tr1->Branch("ep_px", &ep_px, "ep_px/D");
  tr1->Branch("ep_py", &ep_py, "ep_py/D");  
  tr1->Branch("ep_pz", &ep_pz, "ep_pz/D");  
  tr1->Branch("prot_px", &prot_px, "prot_px/D");
  tr1->Branch("prot_py", &prot_py, "prot_py/D");  
  tr1->Branch("prot_pz", &prot_pz, "prot_pz/D");  
  
  TTCS_crs tcs_crs1;
  TTCS_kine tcs_kine1;

  TRandom2 *rand = new TRandom2();
  rand->SetSeed(0);

//   TLorentzVector target(0., 0., 0., Mp);
  TLorentzVector target(0., -Ep*sin(6./radian), -Ep*cos(6./radian), sqrt(Ep*Ep+Mp*Mp));
  TLorentzVector beam(0.,0.,Eb,sqrt(Eb*Eb+Me*Me));
    
  double masses_p_qpr[2]; // masses of proton and q^{\prime}
  masses_p_qpr[0] = Mp;
  
  double masses_lep_pair[2] = {Me, Me};

  TGenPhaseSpace event;

  for( int i = 0; i < Nevent; i++ )
    {
      if( i%50000 == 0 ){ cout<<"Processed "<<i<<" events"<<endl; }
      
      double Eg = rand->Uniform(Eg_min, Eb);
      
      if (Ep==0) {
	flux_factor = N_EPA(Eg, Q2max, Eb)+Brem_Approx(Eg,Eb,l);
      }
      else {
      	flux_factor = N_EPA(Eg, Q2max, Eb);
      }
      
      psf_flux = Eb - Eg_min;

      TLorentzVector ph(0.,0.,Eg,Eg);      
//       double W2 = Mp*Mp + 2*Mp*Eg;
      double W2 = (ph+target).M2();      
      double Mpr_max = sqrt(W2) - Mp;
      
//       Lcm.SetPxPyPzE(0., 0., Eg, Eg + Mp);
         TLorentzVector Lcm=ph+target;

      double t_min = -1000.;

      while( t_min < tlim )
	{
	  //double psf_Q2 = TMath::Min(Mpr_max*Mpr_max, 4.) - Qp2min;
	  //double psf_Q2 = TMath::Min(Mpr_max*Mpr_max, 9.) - Qp2min;
// 	  double psf_Q2 = Mpr_max*Mpr_max - Qp2min;
	  double psf_Q2 = TMath::Min(Mpr_max*Mpr_max, Qp2max) - Qp2min;
	  if (psf_Q2<=0) {cout << " s or Eg is too small so that max Q2 is below Q'2min" << endl; return 0;}
	  Q2 = rand->Uniform(Qp2min, Qp2min + psf_Q2);
	  
	  //Q2 = 1.25; //Just for test
	  //double Q2 = rand->Uniform(Qp2min, Mpr_max*Mpr_max);
	  //cout<<"Q2 = "<<Q2<<endl;
	  
	  t_min = T_min(0., Mp, sqrt(Q2), Mp, W2);
	  double t_max = T_max(0., Mp, sqrt(Q2), Mp, W2);
	  double psf_tM;
	  
	  if(t_min > tlim)
	    {
	      psf_tM = t_min - TMath::Max(t_max, tlim);
	      t = rand->Uniform(t_min - psf_tM, t_min);
	      
	      //t = -0.25;
	      double u = 2*Mp*Mp + Q2 - W2 - t;
	      double th_qprime = acos((W2*(t - u) - Mp*Mp*(Q2 - Mp*Mp))/sqrt(Lambda(W2, 0, Mp*Mp)*Lambda(W2, Q2, Mp*Mp))); //Byuklin Kayanti (4.9)
	      double th_pprime = PI + th_qprime;
	      
	      double Pprime = 0.5*sqrt(Lambda(W2, Q2, Mp*Mp)/W2);
	      
	      double phi_rot = rand->Uniform(0, 2*PI);
	      
	      L_gprime.SetPxPyPzE(Pprime*sin(th_qprime), 0., Pprime*cos(th_qprime), sqrt(Pprime*Pprime + Q2));
	      L_prot.SetPxPyPzE(Pprime*sin(th_pprime), 0., Pprime*cos(th_pprime), sqrt(Pprime*Pprime + Mp*Mp));
	      
	      // cout<<"Pprime = "<<Pprime<<endl;
	      // cout<<"th_qprime = "<<th_qprime*radian<<endl;
	      
	      L_gprime.RotateZ(phi_rot);
	      L_prot.RotateZ(phi_rot);
	      
	      L_gprime.Boost(Lcm.BoostVector());
	      L_prot.Boost(Lcm.BoostVector());
	      
	      //cout<<"L_gprime.Px = "<<L_gprime.Px()<<endl;	  
	      
	      //cout<<"Q2 = "<<L_gprime.M2()<<endl;
	      //cout<<"Q2 = "<<(L_em + L_ep).M2()<<endl;
	      
	      event.SetDecay(L_gprime, 2, masses_lep_pair);
	      double weight = event.Generate();
	      
	      L_em = *event.GetDecay(0);
	      L_ep = *event.GetDecay(1);
	  
	      //cout<<"s = "<<(L_gprime + L_prot).M2()<<endl;
	      
	      tcs_kine1.SetLemLepLp(L_em, L_ep, L_prot);
	      double phi_cm = tcs_kine1.GetPhi_cm();
	      double th_cm = tcs_kine1.GetTheta_cm();
	      
	      // cout<<"phi_cm = "<<phi_cm<<endl;
	      // cout<<"th_cm = "<<th_cm<<endl;
	      
	      double psf_phi_cm = 2*PI;
	      double psf_th_cm = 2/sin(th_cm/radian);
	      
	      tcs_crs1.Set_SQ2t(W2, Q2, t);
	      tcs_crs1.Set_Weight(-1);
	      crs_BH = tcs_crs1.Eval_BH(phi_cm, th_cm);
	      //delt_perp = tcs_crs1.Get_Delta_Perp();
	      
	      psf = psf_Q2*psf_tM*psf_phi_cm*psf_th_cm;
	      
	      // cout<<"psf_Q2:psf_tM:psf_phi_cm:psf_th_cm:Q2:tM:phi_cm:th_cm:psf"<<
	      //   psf_Q2<<" "<<psf_tM<<" "<<psf_phi_cm<<" "<<psf_th_cm<<" "<<Q2<<" "<<t<<" "<<phi_cm<<" "<<th_cm<<" "<<psf<<endl;
	      
	      em_px=L_em.Px();
	      em_py=L_em.Py();
	      em_pz=L_em.Pz();
	      ep_px=L_ep.Px();
	      ep_py=L_ep.Py();
	      ep_pz=L_ep.Pz();
	      prot_px=L_prot.Px();
	      prot_py=L_prot.Py();
	      prot_pz=L_prot.Pz();

	      tr1->Fill();
	    }
	  // else
	  //   {
	  //     cout<<"i= "<<i<<endl;
	  //     cout<<"t_min t_max Q2="<<t_min<<"  "<<t_max<<"  "<<Q2<<endl;
	  //   }
	}
      
    }
  
  Hlist->Write();
  tr1->Write();
  file_out->Close();
}

double N_EPA(double Eg, double Q2max, double Eb)
{
  const double alpha = 1./137.;
  const double PI = 3.14159265358979312;
  
  //double Eb = 5.76;
//   double Eb = 11.; // Be Carefull!!
  double x = Eg/Eb;
  double me = 0.00051;
  double Mp = 0.9383;
  double Q2_min = me*me*x*x/(1 - x);
  return (1/Eb)*alpha/(PI*x)*( (1 - x + x*x/2)*log(Q2max/Q2_min) - (1 - x));
}

double Brem_Approx(double Eg, double Eb,double l)
{
  double X_0 = 890.;   // LH2 rad. length in cm
  return 0.5*(l/X_0)*(4./3.)*(1/Eg-1/Eb); // 0.5 is for effectiv luminosity (after integration int_0^l (l-x)dx )
}
