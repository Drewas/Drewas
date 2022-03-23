#include <iostream>

using namespace std;

void Taskno1()
{
    TCanvas *Functions=new TCanvas("Funtions","sin+cos",700,500);
    const int n=21;
    double x[n],y[n],x1[n],y1[n];
    int j=-10;
    for (int i=0;i<n;i++)
    {
        x[i]=j;
        y[i]=x[i]*TMath::Sin(x[i]);
        x1[i]=j;
        y1[i]=x1[i]*TMath::Cos(x1[i]);
        j++;
    }
    TGraph *graphicsin=new TGraph(n,x,y);
    TGraph *graphiccos=new TGraph(n,x1,y1);
    graphicsin -> SetLineColor(1);
    graphiccos -> SetLineColor(2);
    graphicsin -> GetXaxis()-> SetTitle ("X");
    graphicsin -> GetYaxis()-> SetTitle ("Y");
    Functions -> cd();
    graphicsin -> Draw("ACP");
    graphiccos -> Draw("CP");
    Functions -> SaveAs("/media/sf_Linux-To-Windows/task_no1.png");
    Functions -> SetLogy();
    Functions -> SaveAs("/media/sf_Linux-To-Windows/task_no1LOGY.png");
}
