{
  gROOT->Reset();
  using namespace std;
    
const int m=5;
const int n=36;
// double Q2[m][n],eta[m][n],t[m][n],R[m][n];
double eta[m][n]={
0.1125  ,0.13    ,0.14    ,0.15    ,0.165   ,0.1775  ,0.185   ,0.1925  ,0.1985  ,0.2045  ,0.2135  ,0.25, 
0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,
0.1125  ,0.13    ,0.14    ,0.15    ,0.165   ,0.1775  ,0.185   ,0.1925  ,0.1985  ,0.2045  ,0.2135  ,0.25,
0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,
0.1125  ,0.13    ,0.14    ,0.15    ,0.165   ,0.1775  ,0.185   ,0.1925  ,0.1985  ,0.2045  ,0.2135  ,0.25,
0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,
0.1125  ,0.13    ,0.14    ,0.15    ,0.165   ,0.1775  ,0.185   ,0.1925  ,0.1985  ,0.2045  ,0.2135  ,0.25,
0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,
0.1125  ,0.13    ,0.14    ,0.15    ,0.165   ,0.1775  ,0.185   ,0.1925  ,0.1985  ,0.2045  ,0.2135  ,0.25  
0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,
};
double R[m][n]={
//data
0.0279353,0.0243093,0.0238357,0.0282804,0.0219733,0.0335238,0.0218918,0.0304778,0.0265566,0.0327793,0.0245719,0.0295209,
0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,

// GK - LO:

-0.010531, -0.0121874, -0.0137036, -0.0150071, -0.0167775, -0.0183132, -0.0190091, -0.0198618, -0.0203198, -0.0207188, -0.021882, -0.0257672,
0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,

// GK - NLO:

0.0265917, 0.0247947, 0.0216782, 0.0190935, 0.0158372, 0.01219, 0.0119234, 0.0103253, 0.0100094, 0.00961676, 0.00740375, -0.00148355,
0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,

// MSTW - LO:

-0.014972, -0.0176175, -0.018384, -0.0192794, -0.0208255, -0.0213469, -0.0229581, -0.0236044, -0.0248041, -0.0259236, -0.0264306, -0.026399,
0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,

// MSTW -NLO:

0.0169379, 0.013815, 0.0114872, 0.00930311, 0.00619707, 0.00361426, 0.00221902, 0.000768982, -0.000400544, -0.00160126, -0.00320989, -0.00833223,
0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0
};

// char *filename[m]={"SoLID_TCS_Q2bin.txt","R_Dual_SoLID_TCS_Q2bin.dat","R_DD_d0_SoLID_TCS_Q2bin.dat","R_DD_d0_5_SoLID_TCS_Q2bin.dat","R_DD_d1_SoLID_TCS_Q2bin.dat"};
// for(int k=0;k<m;k++){
//   ifstream input(filename[k]);
//   cout << "open file " << filename[k] << endl;
//   char textline[100];
//   if (k==0) input.getline(textline,100);  //skip first line in file from simulation
//   for(int i=0;i<n;i++){
//     input >> Q2[k][i] >> eta[k][i] >> t[k][i] >> R[k][i];
//     cout << Q2[k][i] << " " <<  eta[k][i] << " " <<  t[k][i] << " " <<  R[k][i] << endl;
//   }
// }

const int NQ2bin=3;
const int Netabin_Q2bin=12;
TGraphErrors *g[m][NQ2bin];
for(int k=0;k<m;k++){
for(int i=0;i<NQ2bin;i++) {
  g[k][i]=new TGraphErrors();  
  for(int j=0;j<Netabin_Q2bin;j++) {
    if (k==0){
      if (j==0 || j==3 || j==7 || j==11){      
	g[k][i]->SetPoint(j,eta[k][i*Netabin_Q2bin+j],0.);
	g[k][i]->SetPointError(j,0,R[k][i*Netabin_Q2bin+j]); // 1/sqrt(6*1.33*1.1)
      }
    }
    else{
      g[k][i]->SetPoint(j,eta[k][i*Netabin_Q2bin+j],R[k][i*Netabin_Q2bin+j]);
      g[k][i]->SetPointError(j,0,0);
    }
  }
}
}

// double Q2bin_edge[NQ2bin+1]={4.0,4.4,4.9,9.0};
double Q2bin_edge[NQ2bin+1]={4,6,6,9};
cout << "Q2bin" << endl;
TCanvas *c = new TCanvas("R","R",1200,800);
c->Divide(1,1);
for(int Q2bin=0;Q2bin<1;Q2bin++){
  
//   c->cd(Q2bin+1);
    char title[100];
    sprintf(title,"%.0f < Q'2 < %.0f (GeV^{2});#eta;R",Q2bin_edge[Q2bin],Q2bin_edge[Q2bin+1]);
   TH1F *hr = gPad->DrawFrame(0.1,-0.04,0.28,0.04);
   hr->SetTitle(title);
//    hr->SetXTitle("X title");
//    hr->SetYTitle("Y title");
//    gPad->GetFrame()->SetFillColor(21);
//    gPad->GetFrame()->SetBorderSize(12);  
  // gPad->SetLogz();
//   for(int k=0;k<m;k++){
//     if (k==0) {
//       g[k][Q2bin]->SetMarkerStyle(20);            
//       g[k][Q2bin]->Draw("P");  
//     }
//     else {
//       g[k][Q2bin]->SetLineStyle(k);    
//       g[k][Q2bin]->Draw("L");
//     }
//   }
  
      g[0][Q2bin]->SetMarkerStyle(20);            
      g[0][Q2bin]->Draw("P");
      g[1][Q2bin]->SetLineStyle(1);      
      g[1][Q2bin]->SetLineColor(kBlue);            
      g[1][Q2bin]->Draw("L");
      g[2][Q2bin]->SetLineStyle(2);      
      g[2][Q2bin]->SetLineColor(kBlue);
      g[2][Q2bin]->Draw("L");
      g[3][Q2bin]->SetLineStyle(1);      
      g[3][Q2bin]->SetLineColor(kRed);            
      g[3][Q2bin]->Draw("L");
      g[4][Q2bin]->SetLineStyle(2);      
      g[4][Q2bin]->SetLineColor(kRed);
      g[4][Q2bin]->Draw("L");
      
   
}

}
