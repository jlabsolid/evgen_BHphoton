#include "TCLASChargedParticle.hh"
#include <TLorentzVector.h>

#include <iostream>
#include <TFile.h>
#include <TMath.h>

using namespace std;

TCLASChargedParticle::TCLASChargedParticle()
{
  int file_stat;
  TFile *file_SF_em = new TFile("Supl_files/file_SF_em.root", "Read");
  if( !file_SF_em->IsOpen() ) { cout<<"Error with opening file 'file_SF_em.root' Program is exiting"<<endl; exit(1); }

  TFile *file_SF_ep = new TFile("Supl_files/file_SF_ep.root", "Read");
  if( !file_SF_ep->IsOpen() ) { cout<<"Error with opening file 'file_SF_ep.root' Program is exiting"<<endl; exit(1); }

  TFile *file_Elos_corr = new TFile("Supl_files/Eloss_func.root");
  if( !file_Elos_corr->IsOpen() ) { cout<<"Error with opening file 'Eloss_func.root' Program is exiting"<<endl; exit(1); }

  TFile *file_em_Fid = new TFile("Supl_files/em_Fid_funcs.root", "Read");
  if( !file_em_Fid->IsOpen() ) { cout<<"Error with opening file 'em_Fid_funcs.root' Program is exiting"<<endl; exit(1); }

  TFile *file_ep_Fid = new TFile("Supl_files/ep_Fid_funcs.root", "Read");
  if( !file_ep_Fid->IsOpen() ) { cout<<"Error with opening file 'ep_Fid_funcs.root' Program is exiting"<<endl; exit(1); }

  TFile *file_prot_Fid = new TFile("Supl_files/Fid_functions_prot.root", "Read");
  if( !file_prot_Fid->IsOpen() ) { cout<<"Error with opening file 'Fid_functions_prot.root' Program is exiting"<<endl; exit(1); }

  TFile *file_neg_Flag = new TFile("Supl_files/neg_Flag_funcs.root", "Read");
  if( !file_neg_Flag->IsOpen() ) { cout<<"Error with opening file 'neg_Flag_funcs.root' Program is exiting"<<endl; exit(1); }

  TFile *file_pos_Flag = new TFile("Supl_files/prot_Flag_funcs.root", "Read");
  if( !file_pos_Flag->IsOpen() ) { cout<<"Error with opening file 'prot_Flag_funcs.root' Program is exiting"<<endl; exit(1); }
  
  if( !(f_SF_em = (TF1*)file_SF_em->Get("f_SF_em")) ) {cout<<"Eror getting 'f_SF_em' Program is exiting"<<endl; exit(1); }
  if( !(f_Sigma_em = (TF1*)file_SF_em->Get("f_Sigma_em")) ) {cout<<"Eror getting 'f_Sigma_em' Program is exiting"<<endl; exit(1);}
  if(!(f_SF_ep = (TF1*)file_SF_ep->Get("f_SF_ep")))  {cout<<"Eror getting 'f_SF_ep' Program is exiting"<<endl; exit(1); }
  if(!(f_Sigma_ep = (TF1*)file_SF_ep->Get("f_Sigma_ep"))) {cout<<"Eror getting 'f_SF_ep' Program is exiting"<<endl; exit(1); }
  
  if( !(f_Elos_corr = (TF1*)file_Elos_corr->Get("f_Elos_corr")) ) {cout<<"Eror getting 'f_Elos_corr' Program is exiting"<<endl; exit(1);}

  for( int i = 0; i < Nsect; i++ )
    {
      if( !(f_em_Flag_[i] = (TF2*)file_neg_Flag->Get(Form("f_em_Flag_%d", i + 1))) )
	{ cout<<Form("Error getting 'f_em_Flag_%d ' Programm is exiting", i + 1)<<endl; exit(1); }
      if( !(f_prot_Flag_[i] = (TF2*)file_pos_Flag->Get(Form("f_prot_Flag_%d", i + 1))) )
	{ cout<<Form("Error getting 'f_prot_Flag_%d ' Programm is exiting", i + 1)<<endl; exit(1); }
      
      for( int j = 0; j < N_prot_fid; j++ )
	{
	  if( !(f_em_Fiducial_up_[i][j] = (TF1*)file_em_Fid->Get(Form("f_em_Fiducial_up_%d_%d", i, j))) )
	    { cout<<Form("Error getting 'f_em_Fiducial_up_%d_%d ' Program is exiting", i, j); exit(1); }
	  if( !(f_em_Fiducial_down_[i][j] = (TF1*)file_em_Fid->Get(Form("f_em_Fiducial_down_%d_%d", i, j))) )
	    { cout<<Form("Error getting 'f_em_Fiducial_down_%d_%d ' Program is exiting", i, j); exit(1); }

	  if( !(f_ep_Fiducial_up_[i][j] = (TF1*)file_ep_Fid->Get(Form("f_ep_Fiducial_up_%d_%d", i, j))) )
	    { cout<<Form("Error getting 'f_ep_Fiducial_up_%d_%d ' Program is exiting", i, j); exit(1); }
	  if( !(f_ep_Fiducial_down_[i][j] = (TF1*)file_ep_Fid->Get(Form("f_ep_Fiducial_down_%d_%d", i, j))) )
	    { cout<<Form("Error getting 'f_ep_Fiducial_down_%d_%d ' Program is exiting", i, j); exit(1); }
	 
	  if( !(f_prot_Fid_main_[i][j] = (TF1*)file_prot_Fid->Get(Form("f_prot_Fid_main_%d_%d", i, j))) )
	    { cout<<Form("Error getting 'f_prot_Fid_main_%d_%d' Program is exiting", i, j)<<endl; exit(1);  }
	  if( !(f_prot_Fid_alt_up_[i][j] = (TF1*)file_prot_Fid->Get(Form("f_prot_Fid_alt_up_%d_%d", i, j)) ) )
	    { cout<<Form("Error getting 'f_prot_Fid_alt_up_%d_%d' Program is exiting", i, j)<<endl; exit(1); }
	  if( !(f_prot_Fid_alt_down_[i][j] = (TF1*)file_prot_Fid->Get(Form("f_prot_Fid_alt_down_%d_%d", i, j)) ) )
	    { cout<<Form("Error getting 'f_prot_Fid_alt_down_%d_%d' Program is exiting", i, j)<<endl; exit(1); }
	}
      
    }

  track_number = -1;
}

void TCLASChargedParticle::Reset()
{
  id = 0;
  px = 0; py = 0; pz = 0;
  P = 0;
  charge = 0;
  mass = 0;
  ein = eout = ece = 0;
  nphe = cc_t = cc_r = 0;
  edep = sc_t = sc_r = 0;
  is_analysed = false;
  is_tr_time = false;
  th_P_flag = false;
  fid_flag = false;
}


void TCLASChargedParticle::SetChargeAnd3Mom(double aq, double aP, double acx, double acy, double acz)
{
  charge = aq;
  P = aP;
  px = P*acx;
  py = P*acy;
  pz = P*acz;
  
  phi = atan2(py, px)*radian;
  phi = phi + 30;
  if( phi < 0 ) { phi = phi + 360.; }
  
  sector = int(phi/60);

  theta = acos(pz/P)*radian;
}

void TCLASChargedParticle::SetEtotEiEo(double aetot, double aein, double aeout)
{
  ece = TMath::Max(aetot, ein + eout);
  ein = aein;
  eout = aeout;
}

void TCLASChargedParticle::SetCC_Nphe_t_r(double anphe, double acc_t, double acc_r)
{
  nphe = anphe;
  cc_t = acc_t;
  cc_r = acc_r;
}

void TCLASChargedParticle::SetSC_edep_t_r(double aedep, double asc_t, double asc_r)
{
  edep = aedep;
  sc_t = asc_t;
  sc_r = asc_r;
}

void TCLASChargedParticle::Set_tr_time(double atr_time)
{
  tr_time = atr_time;
  is_tr_time = true;
}

void TCLASChargedParticle::SetTrackNumber( int a_track_number)
{
  track_number = a_track_number;
}

int TCLASChargedParticle::GetTrackNumber() const
{
  if(is_analysed && track_number >= 0)
    {
      return track_number;
    }
  else
    {
      cout<<"I am sorry, but eighter track is not analyzed nor ttrack number was not set"<<endl;
      cout<<"is_analysed = "<<is_analysed<<endl;
      cout<<"track_number = "<<track_number<<endl;
    }
}


int TCLASChargedParticle::GetID() const
{
  return id;
}

int TCLASChargedParticle::GetSector() const
{
  return sector;
}
int TCLASChargedParticle::GetFidMomBin()const
{
  return fid_mom_bin;
}

bool TCLASChargedParticle::GetFid()const
{
  //cout<<"GetFid = "<<fid_flag<<endl;
  return fid_flag;
}

bool TCLASChargedParticle::Get_Th_P_Flag()const
{
  //cout<<"th_P_flag = "<<th_P_flag<<endl;
  return th_P_flag;
}
double TCLASChargedParticle::GetPhi()const
{
  return phi;
}

double TCLASChargedParticle::GetTheta()const
{
  return theta;
}

double TCLASChargedParticle::GetP()const
{
  return P;
}

TLorentzVector TCLASChargedParticle::Get_LV()const
{
  return L_part;
}

void TCLASChargedParticle::Analyse()
{
  if( P && px && py && pz && sc_t && edep && is_tr_time )
    {
      if( charge > 0 ) // Positives
	{
	  double beta_prot = P/sqrt( P*P + Mp*Mp );
	  double tv_prot = sc_t - sc_r/(vlight*beta_prot) - tr_time;
	  
	  if( P < 1.5 && tv_prot > 2. + 12.*(0.9 - sqrt(P*P + Mp*Mp)/P) ) // The 1.5 GeV is mainly for TCS relevant kinematics 
	    {
	      id = 2212; // Proton
	      mass = Mp;
	      
	      double prot_Mcorr = f_Elos_corr->Eval(P);
	      P = P*(1 - prot_Mcorr);  // Proton momentum correction
	      
	      L_part.SetPxPyPzE(px, py, pz, sqrt(px*px + py*py + pz*pz + mass*mass));

	      int fid_pos_range = int(P/0.5);
	      fid_mom_bin = fid_pos_range;
              
	      if( f_prot_Flag_[sector]->Eval(P, theta) > 0.5 )
		{
		  th_P_flag = true;
		}
	      else 
		{
		  th_P_flag = false;
		}	      
              
	      if( fid_pos_range >= 0 && fid_pos_range < N_prot_fid )
		{
		  double pos_fid_lim = f_prot_Fid_main_[sector][fid_pos_range]->Eval(phi);
		  double pos_fid_alt_up = f_prot_Fid_alt_up_[sector][fid_pos_range]->Eval(phi);
		  double pos_fid_alt_down = f_prot_Fid_alt_down_[sector][fid_pos_range]->Eval(phi);
                  
		  if(theta > pos_fid_lim && !(theta > pos_fid_alt_down && theta < pos_fid_alt_down))
		    {
		      //cout<<"sect_p="<<sect_prot<<"\t prot_fid_range="<<fid_pos_range<<"\t p_p="<<p[i]<<endl;
		      fid_flag = true;
		    }
		  else
		    {
		      fid_flag = false;
		    }
		}
	      else
		{
		  fid_flag = false;
		}
	      
	      is_analysed = true;
	    }
	  else if( nphe > 0 && ein > 0.06 )
	    {
	      double SF_mean = f_SF_ep->Eval(P);
	      double SF_sigm = f_Sigma_ep->Eval(P);

	      if( nphe > 25 && ein > 0.06 && ece/P > SF_mean*(1 - 2*SF_sigm) && ein/P > 0.06 )
		{
		  id = -11;
		  mass = Me;
		  L_part.SetPxPyPzE(px, py, pz, sqrt(px*px + py*py + pz*pz + mass*mass));
		  
		  int fid_ep_range = int(P/0.5) - 2;
		  fid_mom_bin = fid_ep_range;
	      
		  if(f_prot_Flag_[sector]->Eval(P, theta) > 0.5) // This is the same function as for protons
		    {
		      th_P_flag = true;
		    }
		  else
		    {
		      th_P_flag = false;
		    }
		  
		  if( fid_ep_range >= 0 && fid_ep_range < N_em_fid  )
		    {
		      //cout<<"Kuku1"<<endl;
		      double ep_fid_up = f_ep_Fiducial_up_[sector][fid_ep_range]->Eval(theta);
		      double ep_fid_down = f_ep_Fiducial_down_[sector][fid_ep_range]->Eval(theta);
		      //cout<<"Kuku2"<<endl;    
		      
		      if(phi > ep_fid_down && phi < ep_fid_up)
			{
			  //cout<<"sect_ep="<<sect_ep<<"\t ep_fid_range="<<fid_pos_range<<"\t p_ep="<<p[i]<<endl;
			  fid_flag = true;
			}
		      else
			{
			  fid_flag = false;
			}			
		    }
		  else
		    {
		      fid_flag = false;
		    }
		  
		  is_analysed = true;	      
		}
	      else
		{
		  UnknownParticle();
		}
	    }
	  else
	    {
	      UnknownParticle();
	    }

	}
      else if( charge < 0 )
	{
	  if( nphe > 0 && ein > 0.06 )
	    {	      
	      double SF_mean = f_SF_em->Eval(P);
	      double SF_sigm = f_Sigma_em->Eval(P);

	      if( nphe > 25 && ein > 0.06 && ece/P > SF_mean*(1 - 2*SF_sigm) && ein/P > 0.06 )
		{
		  //cout<<"Kuku"<<endl;
		  id = 11;
		  mass = Me;
		  L_part.SetPxPyPzE(px, py, pz, sqrt(px*px + py*py + pz*pz + mass*mass));
		  
		  int fid_em_range = int(P/0.5);
		  fid_mom_bin = fid_em_range;

		  if(f_em_Flag_[sector]->Eval(P, theta) > 0.5)
		    {
		      th_P_flag = true;
		    }
		  else
		    {
		      th_P_flag = false;
		    }

		  if( fid_em_range >= 0 && fid_em_range < N_em_fid  )
		    {
		      double em_fid_up = f_em_Fiducial_up_[sector][fid_em_range]->Eval(theta);
		      double em_fid_down = f_em_Fiducial_down_[sector][fid_em_range]->Eval(theta);
		      
		      if(phi > em_fid_down && phi < em_fid_up)
			{
			  //cout<<"sect_ep="<<sect_ep<<"\t ep_fid_range="<<fid_pos_range<<"\t p_ep="<<p[i]<<endl;
			  fid_flag = true;
			}
		      else
			{
			  fid_flag = false;
			}
		    }
		  else
		    {
		      fid_flag = false;
		    }
		  
		  is_analysed = true;
		}
	      else
		{
		  UnknownParticle();
		}
	    }
	  else
	    {
	      UnknownParticle();
	    }
	}
      else
	{
	  UnknownParticle();
	}
    }
  else
    {
      cout<<"!Error analyzing the track: P or cx or cy or cz charge, or tr_time was not set:"<<endl;
      cout<<"P = "<<P<<"   px = "<<px<<"   py = "<<py<<"   pz = "<<px<<"   sc_r = "<<sc_r<<
	"   sc_t = "<<sc_t<<"  edep = "<<edep<<"   is_tr_time = "<<is_tr_time<<endl;
      cout<<" The program is exiting"<<endl;;
      exit(1);
    }
}

void TCLASChargedParticle::UnknownParticle()
{
  id = mass = 0;
  is_analysed = true;
}
