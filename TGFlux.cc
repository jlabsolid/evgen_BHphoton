#include "TGFlux.hh"
#include "kin_funcs.h"

//typedef double(TGFlux::*TGFlux_MemFn)(double *xx,  double *par);

TGFlux::TGFlux(double a_M, double a_Eb)
{
  Mtarg = a_M;
  Eb = a_Eb;
  //TGFlux_MemFn p = &TGFlux::G_Flux;
  f_Gflux = new TF1("f_Gflux", G_Flux, 0, 100, 3);
}

double TGFlux::GetFlux(double a_W, double a_Q2) const
{
  f_Gflux->SetParameters(a_W, Eb, Mtarg);
  return f_Gflux->Eval(a_Q2);
}

double TGFlux::GetIntegrFlux(double a_W, double q2_1, double q2_2) const // Flux Integrated over Q2 from Q2_1 to Q2_2
{
  f_Gflux->SetParameters(a_W, Eb, Mtarg);
  return f_Gflux->Integral(q2_1, q2_2);
}

double TGFlux::GetIntegrFlux(double a_W, double q2_2) const // Flux Integrated over Q2 from Q2min to Q2_2
{
  double q2_min = Q2_min( a_W*a_W, Eb, Mtarg );
  f_Gflux->SetParameters(a_W, Eb, Mtarg);
  //std::cout<<" q2_min = "<<q2_min<<"  w = "<<a_W<<"   Eb = "<<Eb<<"  Mtarg = "<<Mtarg<<std::endl;
  return f_Gflux->Integral(q2_min, q2_2);
}

double TGFlux::G_Flux(double *xx, double *par)
{
  double Q2 = xx[0];
  
  double W = par[0];
  double E_beam = par[1];
  double M = par[2];
  
  const double k_0 = E_beam;

  double E_g = (W*W - M*M + Q2)/(2*M);
  double k_pr = E_beam - E_g;
  
  double epsilon = 1/( 1 + 2*(Q2 + E_g*E_g)/( 4*k_0*k_pr - Q2 ) );
  
  double G_w = (Alpha/(4*PI))*((W*W - M*M)/(M*M*k_0*k_0))*(W/Q2)*(1/(1 - epsilon));
  
  return G_w; 
}

