#ifndef TTCS_crs_HH
#define TTCS_crs_HH

#include <TF1.h>
#include <TF2.h>

class TTCS_crs: public TObject
{
public:
  TTCS_crs();
  TTCS_crs(double, double, double); // s(GeV)^2, Q2(GeV)^2, t(GeV)^2
  double Eval_BH(double, double) const;// phi and theta in radians
  double Eval_BH(double, double, double, double, double, double) const; // s, Q2, t
  void Set_SQ2t(double, double, double);
  double Integral_BH_phi_th( double phi_min = 0, double phi_max = 360, double th_min = 0, double th_max = 180);
  void Set_Weight( double weight = -1.); // with +1 it will weight with L/L0, otherwise it will not
  void Draw_BH(const char* option);

private:
  double is, iQ2, it;
  double iweight;


  static const double radian = 57.2957795130823229;
  static const double m_e = 0.00051;
  static const double M_p = 0.938272;
  static const double alpha_em = 1./137.;
  static const double PI = 3.14159265358979312;
  static const double ammp = 2.793;
  static const double ammn = -1.913;

  static double BH_crs_section( double *, double *); // Hmmm why it worked with static ?, and didn't work without static?
  TF2 *f_BH;
};

#endif
