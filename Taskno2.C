#include <iostream>

using namespace std;

void Taskno2()
{
    TCanvas *canvas=new TCanvas("canvas","sin+cos",700,500);
    const int n=20;
    double x[n],y[n];
    for (int i=0;i<n;i++)
    {
        x[i]=i*0.1;
        y[i]=10*TMath::Sin(x[i]+0.2);
    }
    TGraph *graphic=new TGraph(n,x,y);
    graphic-> SetMarkerStyle(30);
    graphic-> GetXaxis()-> SetTitle ("X");
    graphic-> GetYaxis()-> SetTitle ("Y");
    canvas-> cd();
    graphic->Draw("ACP");
    canvas->SaveAs("/media/sf_Linux-To-Windows/task_no2.png");
}
