//#include "kin_funcs.h"
#include <math.h>


// This is from Byukling Kayanti Formula (6.3)
double Lambda( double x, double y, double z )
{
  return (x - y - z)*(x - y - z) - 4*y*z;
}

//From Byukling Kayanti Formula (5.14)
double T_min( double ma, double mb, double m1, double m2, double s)
{
  return ma*ma + m1*m1 - (1/(2*s))*( (s + ma*ma - mb*mb)*(s + m1*m1 - m2*m2) - sqrt( Lambda(s, ma*ma, mb*mb)*Lambda(s, m1*m1, m2*m2) ) );
}

//From Byukling Kayanti Formula (5.14)
double T_max( double ma, double mb, double m1, double m2, double s)
{
  return ma*ma + m1*m1 - (1/(2*s))*( (s + ma*ma - mb*mb)*(s + m1*m1 - m2*m2) + sqrt( Lambda(s, ma*ma, mb*mb)*Lambda(s, m1*m1, m2*m2) ) );
}

double Q2_min( double s, double Eb, double M )
{
  // M is the target mass;
  double me = 0.00051;
  double Eg = (s - M*M)/(2*M);
  double E_pr = Eb - Eg;
  double P0 = sqrt(Eb*Eb - me*me);
  double P_pr = sqrt(E_pr*E_pr - me*me);
  double Q2min = 2*(Eb*E_pr - P0*P_pr - me*me);

  return Q2min;
}
