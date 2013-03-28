#ifndef TCLASCHARGEDPARTICLE_IFNDEF
#define TCLASCHARGEDPARTICLE_IFNDEF

#include <TF1.h>
#include <TF2.h>
#include <TLorentzVector.h>

//class TLorentzVector;

class TCLASChargedParticle
{
  
public:
  TCLASChargedParticle();
  void SetChargeAnd3Mom(double q, double P, double cx, double cy, double cz); // Charge, Momentum (GeV), cx, cy, cz
  void SetEtotEiEo(double ece, double ec_ei, double ec_eo);
  void SetCC_Nphe_t_r(double nphe, double cc_t, double cc_r);
  void SetSC_edep_t_r(double edep, double sc_t, double sc_r);
  void Set_tr_time(double tr_time);
  void SetTrackNumber(int ); // track number from 0 to gpart;

  int GetTrackNumber()const; // track number from 0 to gpart;
  int GetID()const; // id of the particle like -11 <---> e-, 2212 <---> proton
  int GetSector()const;
  int GetFidMomBin()const; // momentum range used in the fiducial cuts
  bool GetFid()const; // false, if the particle is not in the Fiducial volume, true if the particle is in the fid volume
  bool Get_Th_P_Flag()const; // false if particle didn't pass "th vs P" cuts, true if it passed "th vs P" cut.
  double GetPhi()const; // deg
  double GetTheta()const; // deg
  double GetP()const; // Momentum in GeV
  TLorentzVector Get_LV()const;  // The lorentz Vector of the particle
  void Analyse(); // Analysis the track, using the provided information
  void Reset(); // Resets all tracking parameters (like ec_in, nphe etc...) to 0.

private:
  
  void UnknownParticle();

  static const double radian = 57.2957795130823229;
  static const double Me = 0.00051; // GeV
  static const double Mp = 0.9383;  // GeV
  static const double vlight = 29.9792458; // cm/ns

  static const int Nsect = 6;
  static const int NPMcor_range = 5;
  static const int N_prot_fid = 6;
  static const int N_em_fid = 6;
  static const int N_ep_fid = 6;

  bool is_analysed;
  bool is_tr_time;
  int track_number; // track number from 0 to gpart;
  int id;
  int sector;
  int fid_mom_bin;
  double tr_time;
  double P, px, py, pz;
  double phi;      //in deg (0, 360);
  double theta;    //in deg 
  double charge;
  double mass; //GeV
  double ein, eout, ece; // ein, e_out, Max(etot, ec_ei + ec_eo)
  double nphe, cc_t, cc_r; // nphe, cc_t, cc_r
  double edep, sc_t, sc_r; // edep, sc_t, sc_r

  bool fid_flag;        // false if outside of Fiducial region and true if is in Fiducial region
  bool th_P_flag;       // false if particle didn't pass "th vs P" cuts, true if it passed "th vs P" cut.
 
  TF1 *f_SF_em;       // Mean Sampling Fraction for e-
  TF1 *f_Sigma_em;    // Sigma of Sampling Fraction for e-
  TF1 *f_SF_ep;       // Mean Sampling Fraction for e+
  TF1 *f_Sigma_ep;    // Sigma of Sampling Fraction for e+

  TF1 *f_Elos_corr;  // Eloss fuction for proton

  TF1 *f_em_Fiducial_up_[Nsect][N_em_fid];       // Fiducial cut functions for e-
  TF1 *f_em_Fiducial_down_[Nsect][N_em_fid];     // Fiducial cut functions for e-
  TF1 *f_ep_Fiducial_up_[Nsect][N_ep_fid];       // Fiducial cut functions for e+
  TF1 *f_ep_Fiducial_down_[Nsect][N_ep_fid];     // Fiducial cut functions for e+
  TF1 *f_prot_Fid_main_[Nsect][N_prot_fid];      // Fiducial cut functions for prot
  TF1 *f_prot_Fid_alt_up_[Nsect][N_prot_fid];    // Fiducial cut functions for prot
  TF1 *f_prot_Fid_alt_down_[Nsect][N_prot_fid];  // Fiducial cut functions for prot

  TF2 *f_em_Flag_[Nsect];     // Flag functions for negatives. They applay on "th vs P" distributions
  TF2 *f_prot_Flag_[Nsect];   // Flag functions for positives. Note they applay on positrons as well

  TLorentzVector L_part;
};

#endif
