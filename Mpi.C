#include <iostream>
#include <stdlib.h>
#include <random>
#include <math.h>

using namespace std;

void Mpi()
{
    setlocale( LC_ALL, "Russian" );
    double m_p0 = 0.135; //GeV/c^2//
    //|p1|=|p2|=p, E=pc => mc^2=2pc => p = mc^2/2= m/2//
    //m_po^2 = 4E_g1*E_g2 => E_g1 = m_po/2//
    double phi,px,py;
    int const c = 1;
    double p1,p2;
    p1= m_p0/2;
    p2=p1;
    double E_g1, E_g2;
    E_g1 = m_p0/2;
    E_g2 = E_g1;
    cout << "Импульс гамма кванта 1 = импульсу гамма кванта два и равен = " << p1 << " GeV/c" <<endl << "Энергия гамма кванта 1 = энергии гамма кванта два и равна = " << E_g1 << "GeV" << endl;
    TCanvas *Pion = new TCanvas ("Pion","rand", 700,500);
    Pion -> Divide (3,2);
    Pion -> cd(1) ;
    TRandom *rnd = new TRandom();
    TH1F *hist_phi = new TH1F ("phi", "hist uniform phi",360,-TMath::Pi(),TMath::Pi());
    TH1F *hist_px = new TH1F ("px", "hist uniform px",100,-TMath::Pi(),TMath::Pi());
    TH1F *hist_py = new TH1F ("phi", "hist uniform px",100,-TMath::Pi(),TMath::Pi());
    TH1F *hist_E = new TH1F ("E", "hist uniform E",100,-TMath::Pi(),TMath::Pi());
    TH1F *hist_P = new TH1F ("P", "hist uniform P",100,-TMath::Pi(),TMath::Pi());
    for (int i=0;i<=1000;i++)
    {
        phi = rnd->Uniform(-1.*TMath::Pi(),TMath::Pi());
        px=p1*cos(phi);
        py=p1*sin(phi);
        hist_phi->Fill(phi);
        hist_px->Fill(px);
        hist_py->Fill(py);
        hist_E -> Fill(E_g1);
        hist_P -> Fill(p1);
    }
    hist_phi->Draw();
    Pion->SaveAs("/media/sf_Linux-To-Windows/Phi.png");
    Pion -> cd(2);
    hist_E -> Draw();
    Pion->SaveAs("/media/sf_Linux-To-Windows/E.png");
    Pion -> cd(3);
    hist_P -> Draw();
    Pion->SaveAs("/media/sf_Linux-To-Windows/P.png");
    Pion->cd(4);
    hist_px ->Draw();
    Pion->SaveAs("/media/sf_Linux-To-Windows/Px.png");
    Pion->cd(5);
    hist_py ->Draw();
    Pion->SaveAs("/media/sf_Linux-To-Windows/Py.png");

}
