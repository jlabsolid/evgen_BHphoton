// using namespace std;
{
  gROOT->Reset();
  using namespace std;  
const int m=6;
char *filename[m]={"CLAS12_TCS_Q2bin.txt","SoLID_TCS_Q2bin.txt","R_Dual_SoLID_TCS_Q2bin.dat","R_DD_d0_SoLID_TCS_Q2bin.dat","R_DD_d0_5_SoLID_TCS_Q2bin.dat","R_DD_d1_SoLID_TCS_Q2bin.dat"};
const int n=36;
double Q2[m][n],eta[m][n],t[m][n],R[m][n];
for(int k=0;k<m;k++){
  ifstream input(filename[k]);
  cout << "open file " << filename[k] << endl;
  char textline[100];
  if (k==0 || k==1) input.getline(textline,100);  //skip first line in file from simulation
  for(int i=0;i<n;i++){
    input >> Q2[k][i] >> eta[k][i] >> t[k][i] >> R[k][i];
    cout << Q2[k][i] << " " <<  eta[k][i] << " " <<  t[k][i] << " " <<  R[k][i] << endl;
  }
}

const int NQ2bin=3;
const int Netabin_Q2bin=12;
TGraphErrors *g[m][NQ2bin];
for(int k=0;k<m;k++){
for(int i=0;i<NQ2bin;i++) {
  if(i==1) continue;
  g[k][i]=new TGraphErrors();  
  for(int j=0;j<Netabin_Q2bin;j++) {
    if (k==0){
      if (j%2!=0){
	g[k][i]->SetPoint(j,eta[k][i*Netabin_Q2bin+j]+0.005,0.05);
	if (i==0) g[k][i]->SetPointError(j,0,R[k][i*Netabin_Q2bin+j]*0.5); //1/sqrt(4)
	if (i==2) g[k][i]->SetPointError(j,0,R[k][i*Netabin_Q2bin+j]*0.7); //1/sqrt(2)
      }
    }
    else if (k==1){
      if (j%2!=0){
	g[k][i]->SetPoint(j,eta[k][i*Netabin_Q2bin+j],0.05);
	if (i==0) g[k][i]->SetPointError(j,0,R[k][i*Netabin_Q2bin+j]*0.5); //1/sqrt(4)
	if (i==2) g[k][i]->SetPointError(j,0,R[k][i*Netabin_Q2bin+j]*0.7); //1/sqrt(2)
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
double Q2bin_edge[NQ2bin+1]={4.0,5,5,9.0};
cout << "Q2bin" << endl;
// TCanvas *c = new TCanvas("R","R",1600,400);
// c->Divide(3,1);
TCanvas *c = new TCanvas("R","R",1200,400);
c->Divide(2,1);
for(int Q2bin=0;Q2bin<NQ2bin;Q2bin++){
//   c->cd(Q2bin+1);
    if (Q2bin==0) c->cd(1);
    if (Q2bin==1) continue;      
    if (Q2bin==2) c->cd(2);
    
    char title[100];
    sprintf(title,"%.0f < Q'2 < %.0f (GeV^{2});#eta;R'",Q2bin_edge[Q2bin],Q2bin_edge[Q2bin+1]);
//    TH1F *hr = gPad->DrawFrame(0.1,-0.1,0.4,0.3);
   TH1F *hr = gPad->DrawFrame(0.1,-0.1,0.4,0.3);    
   hr->SetTitle(title);
//    gPad->GetFrame()->SetFillColor(21);
//    gPad->GetFrame()->SetBorderSize(12);  
  // gPad->SetLogz();
   
//    for(int k=0;k<m;k++){
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
      g[0][Q2bin]->SetMarkerColor(kBlue);                  
      g[0][Q2bin]->Draw("P");      
      g[1][Q2bin]->SetMarkerStyle(20);            
      g[1][Q2bin]->SetMarkerColor(kBlack);                  
      g[1][Q2bin]->Draw("P");          
      
      g[2][Q2bin]->SetLineStyle(1);      
      g[2][Q2bin]->SetLineColor(kBlue);            
      g[2][Q2bin]->Draw("L");
      g[3][Q2bin]->SetLineStyle(2);      
      g[3][Q2bin]->SetLineColor(kRed);
      g[3][Q2bin]->Draw("L");
      g[5][Q2bin]->SetLineStyle(4);      
      g[5][Q2bin]->SetLineColor(kRed);
      g[5][Q2bin]->Draw("L");
  
}

}