#ifndef TGFlux_HH
#define TGFlux_HH

#include <TF1.h>

class TGFlux
{
public:
  TGFlux(double Mtarg = 0.9383, double Eb = 5.76);
  double GetFlux(double W, double Q2) const;
  double GetIntegrFlux(double W, double Q2_1, double Q2_2) const; // Flux Integrated over Q2 from Q2_1 to Q2_2
  double GetIntegrFlux(double W, double Q2_2) const; // Flux Integrated over Q2 from Q2min to Q2_2
  void SetEb(double a_Eb) { Eb = a_Eb; }
  
private:
  double Eb;
  double Mtarg;
  
  static const double Alpha = 1./137.;
  static const double PI = 3.14159265358979312;
  static const double m_e = 0.00051;
  
  TF1 *f_Gflux;
  static double G_Flux(double *, double *);
  
};

#endif
