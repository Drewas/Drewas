#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

void Mpi()
{
    double m_p0 = 0.135; //GeV/c^2//
    //|p1|=|p2|=p, E=pc => mc^2=2pc => p = mc^2/2= m/2//
    //m_po^2 = 4E_g1*E_g2 => E_g1 = m_po/2//
    double phi,px,py,pz,theta,cosinustheta;
    int const c = 1;
    double p1,p2;
    p1= m_p0/2;
    p2=p1;
    double E_g1, E_g2;
    E_g1 = m_p0/2;
    E_g2 = E_g1;
    cout << "Pgamma 1 = Pgamma 2 = " << p1 << " GeV/c" <<endl << "E gamma 1 = E gamma 2 = " << E_g1 << "GeV" << endl;
    TCanvas *Pion = new TCanvas ("Pion","rand", 1920,1080);
    Pion -> Divide (3,3);
    Pion -> cd(1) ;
    TRandom *rnd = new TRandom();
    TH1D *hist_phi = new TH1D ("phi", "hist phi",360,-TMath::Pi(),TMath::Pi());
    TH1D *hist_costhetha = new TH1D ("costheta", "hist costheta",100,-1.,1.);
    TH1D *hist_theta = new TH1D ("theta", "hist theta",180,0,TMath::Pi());
    TH1D *hist_px = new TH1D ("px", "hist px",100,-0.08,0.08);
    TH1D *hist_py = new TH1D ("py", "hist py",100,-0.08,0.08);
    TH1D *hist_E = new TH1D ("E", "hist E",100,0.066,0.068);
    TH1D *hist_P = new TH1D ("P", "hist  P",100,0.066,0.068);
    TH2D *hist2d = new TH2D("hist2d","px and py", 100,-0.08,0.08,100,-0.08,0.08);
    TH1D *hist_pz = new TH1D ("pz", "hist pz",100,-10.,10.);
    for (int i=0;i<1000000;i++)
    {
        phi = rnd->Uniform(-1.*TMath::Pi(),TMath::Pi());
        cosinustheta = rnd->Uniform(-1.,1.);
        theta = acos(cosinustheta);
        px=p1*cos(phi)*sin(theta);
        py=p1*sin(phi)*sin(theta);
        pz=p1*cos(theta);
        hist_phi->Fill(phi);
        hist_px->Fill(px);
        hist_py->Fill(py);
        hist_E -> Fill(E_g1);
        hist_P -> Fill(p1);
        hist2d->Fill(px,py);
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
    Pion->cd(6)->SetLogz();
    hist2d->Draw("colz");
    Pion->SaveAs("/media/sf_Linux-To-Windows/2dhist.png");
    Pion->cd(7);
    hist_pz ->Draw();
    Pion->SaveAs("/media/sf_Linux-To-Windows/Pz.png");
}
