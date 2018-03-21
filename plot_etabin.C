// using namespace std;
{
  gROOT->Reset();
  using namespace std;  
const int m=6;
char *filename[m]={"CLAS12_TCS_etabin.txt","SoLID_TCS_etabin.txt","R_Dual_SoLID_TCS_etabin.dat","R_DD_d0_SoLID_TCS_etabin.dat","R_DD_d0_5_SoLID_TCS_etabin.dat","R_DD_d1_SoLID_TCS_etabin.dat"};
const int n=30;
double Q2[m][n],eta[m][n],t[m][n],R[m][n];
for(int k=0;k<m;k++){
  ifstream input(filename[k]);
  cout << "open file " << filename[k] << endl;
  char textline[100];
  if (k==0 || k==1) input.getline(textline,100);  //skip first line in file from simulation
  for(int i=0;i<n;i++){
//     input >> Q2[k][i] >> eta[k][i] >> t[k][i] >> R[k][i];
//     cout << Q2[k][i] << " " <<  eta[k][i] << " " <<  t[k][i] << " " <<  R[k][i] << endl;
    input >> eta[k][i] >> Q2[k][i] >> t[k][i] >> R[k][i];
    cout <<  eta[k][i] << " " <<  Q2[k][i] << " " <<  t[k][i] << " " <<  R[k][i] << endl;
  }
}

const int Netabin=6;
const int NQ2bin_etabin=5;
TGraphErrors *g[m][Netabin];
for(int k=0;k<m;k++){
for(int i=0;i<Netabin;i++) {
  g[k][i]=new TGraphErrors();  
  for(int j=0;j<NQ2bin_etabin;j++) {
    if (k==0){    
      g[k][i]->SetPoint(j,Q2[k][i*NQ2bin_etabin+j]+0.1,0.05);
      g[k][i]->SetPointError(j,0,R[k][i*NQ2bin_etabin+j]);
    }
    else if (k==1){
      g[k][i]->SetPoint(j,Q2[k][i*NQ2bin_etabin+j],0.05);
      g[k][i]->SetPointError(j,0,R[k][i*NQ2bin_etabin+j]);
    }    
    else{
      g[k][i]->SetPoint(j,Q2[k][i*NQ2bin_etabin+j],R[k][i*NQ2bin_etabin+j]);
      g[k][i]->SetPointError(j,0,0);
    }
  }
}
}

double etabin_edge[Netabin+1]={0.100,0.140,0.175,0.195,0.210,0.230,0.400};
// double etabin_edge[Netabin+1]={0.10,0.15,0.19,0.19,0.22,0.22,0.40};
cout << "etabin" << endl;
TCanvas *c = new TCanvas("R","R",1600,800);
c->Divide(3,2);
// TCanvas *c = new TCanvas("R","R",1200,800);
// c->Divide(2,2);
for(int etabin=0;etabin<Netabin;etabin++){
  c->cd(etabin+1);   
    char title[100];
    sprintf(title,"%.03f < #eta < %.03f;Q'2 (GeV^{2});R'",etabin_edge[etabin],etabin_edge[etabin+1]);
   TH1F *hr = gPad->DrawFrame(4,-0.1,9,0.3);
   hr->SetTitle(title);
//    gPad->GetFrame()->SetFillColor(21);
//    gPad->GetFrame()->SetBorderSize(12);  
  // gPad->SetLogz();
   
//   for(int k=0;k<m;k++){
//     if (k==0) {
//       g[k][etabin]->SetMarkerStyle(20);            
//       g[k][etabin]->Draw("P");  
//     }
//     else {
//       g[k][etabin]->SetLineStyle(k);    
//       g[k][etabin]->Draw("L");
//     }
//   }

      g[0][etabin]->SetMarkerStyle(20);            
      g[0][etabin]->SetMarkerColor(kBlue);                  
      g[0][etabin]->Draw("P");      
      g[1][etabin]->SetMarkerStyle(20);            
      g[1][etabin]->SetMarkerColor(kBlack);                  
      g[1][etabin]->Draw("P");      
      
      g[2][etabin]->SetLineStyle(1);      
      g[2][etabin]->SetLineColor(kBlue);            
      g[2][etabin]->Draw("L");
      g[3][etabin]->SetLineStyle(2);      
      g[3][etabin]->SetLineColor(kRed);
      g[3][etabin]->Draw("L");
      g[5][etabin]->SetLineStyle(4);      
      g[5][etabin]->SetLineColor(kRed);
      g[5][etabin]->Draw("L");   
}

}