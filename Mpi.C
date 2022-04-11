#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

void Mpi()
{
    double m_p0 = 0.135; //GeV/c^2//
    //|p1|=|p2|=p, E=pc => mc^2=2pc => p = mc^2/2= m/2//
    //m_po^2 = 4E_g1*E_g2 => E_g1 = m_po/2//
    double phi1,phi2,px1,py1,pz1,theta1,eta1,cosinustheta1,px2,py2,pz2,theta2,eta2,cosinustheta2;
    int const c = 1;
    double p1,p2;
    p1= m_p0/2;
    p2=p1;
    double E_g1, E_g2;
    E_g1 = m_p0/2;
    E_g2 = E_g1;
    cout << "Pgamma 1 = Pgamma 2 = " << p1 << " GeV/c" <<endl << "E gamma 1 = E gamma 2 = " << E_g1 << "GeV" << endl;
    TCanvas *Pion = new TCanvas ("Pion","rand", 2560,1440);
    Pion -> Divide (6,3);
    Pion -> cd(1) ;
    TRandom *rnd = new TRandom();
    TH1D *hist_phi1 = new TH1D ("phi1", "hist phi1",360,-TMath::Pi(),TMath::Pi());
    TH1D *hist_eta1 = new TH1D ("eta1", "hist eta1",600,-3.,3.);
    TH1D *hist_costhetha1 = new TH1D ("costheta1", "hist costheta1",100,-1.,1.);
    TH1D *hist_theta1 = new TH1D ("theta1", "hist theta1",180,0,TMath::Pi());
    TH1D *hist_px1 = new TH1D ("px1", "hist px1",100,-0.08,0.08);
    TH1D *hist_py1 = new TH1D ("py1", "hist py1",100,-0.08,0.08);
    TH1D *hist_E1 = new TH1D ("E1", "hist E1",100,0.066,0.068);
    TH1D *hist_P1 = new TH1D ("P1", "hist P1",100,0.066,0.068);
    TH2D *hist2d1 = new TH2D("hist2d1","px1 and py1", 100,-0.08,0.08,100,-0.08,0.08);
    TH1D *hist_pz1 = new TH1D ("pz1", "hist pz1",100,-0.08,0.08);

    TH1D *hist_phi2 = new TH1D ("phi2", "hist phi2",360,-TMath::Pi(),TMath::Pi());
    TH1D *hist_eta2 = new TH1D ("eta2", "hist eta2",600,-3.,3.);
    TH1D *hist_costhetha2 = new TH1D ("costheta2", "hist costheta2",100,-1.,1.);
    TH1D *hist_theta2 = new TH1D ("theta2", "hist theta2",180,0,TMath::Pi());
    TH1D *hist_px2 = new TH1D ("px2", "hist px2",100,-0.08,0.08);
    TH1D *hist_py2 = new TH1D ("py2", "hist py2",100,-0.08,0.08);
    TH1D *hist_E2= new TH1D ("E2", "hist E2",100,0.066,0.068);
    TH1D *hist_P2 = new TH1D ("P2", "hist P2",100,0.066,0.068);
    TH2D *hist2d2 = new TH2D("hist2d2","px2 and py2", 100,-0.08,0.08,100,-0.08,0.08);
    TH1D *hist_pz2 = new TH1D ("pz2", "hist pz2",100,-0.08,0.08);
    for (int i=0;i<1000000;i++)
    {
        phi1 = rnd->Uniform(-1.*TMath::Pi(),TMath::Pi());
        cosinustheta1 = rnd->Uniform(-1.,1.);
        theta1 = acos(cosinustheta1);
        eta1 = -TMath::Log(tan(0.5*theta1));
        px1=p1*cos(phi1)*sin(theta1);
        py1=p1*sin(phi1)*sin(theta1);
        pz1=p1*cos(theta1);

        phi2 = phi1 - TMath::Pi();
        theta2 = TMath::Pi() - theta1;
        eta2 = -1.*eta1;
        px2=p2*cos(phi2)*sin(theta2);
        py2=p2*sin(phi2)*sin(theta2);
        pz2=p2*cos(theta2);

        hist_phi1->Fill(phi1);
        hist_theta1->Fill(theta1);
        hist_px1->Fill(px1);
        hist_py1->Fill(py1);
        hist_pz1->Fill(pz1);
        hist_E1 -> Fill(E_g1);
        hist_P1 -> Fill(p1);
        hist2d1->Fill(px1,py1);
        hist_eta1->Fill(eta1);

        hist_phi2->Fill(phi2);
        hist_theta2->Fill(theta2);
        hist_px2->Fill(px2);
        hist_py2->Fill(py2);
        hist_pz2->Fill(pz2);
        hist_E2-> Fill(E_g2);
        hist_P2-> Fill(p2);
        hist2d2->Fill(px2,py2);
        hist_eta2->Fill(eta2);
    }
    hist_phi1->Draw();
    Pion -> cd(2);
    hist_E1-> Draw();
    Pion -> cd(3);
    hist_P1 -> Draw();
    Pion->cd(4);
    hist_px1 ->Draw();
    Pion->cd(5);
    hist_py1 ->Draw();
    Pion->cd(6);
    hist_pz1 ->Draw();
    Pion->cd(7)->SetLogz();
    hist2d1->Draw("colz");
    Pion->cd(8);
    hist_theta1->Draw();
    Pion->cd(9);
    hist_eta1->Draw();
    Pion->SaveAs("/media/sf_Linux-To-Windows/eta.png");
    hist_phi2->Draw();
    Pion -> cd(10);
    hist_E2-> Draw();
    Pion -> cd(11);
    hist_P2 -> Draw();
    Pion->cd(12);
    hist_px2 ->Draw();
    Pion->cd(13);
    hist_py2 ->Draw();
    Pion->cd(14);
    hist_pz2 ->Draw();
    Pion->cd(15)->SetLogz();
    hist2d2->Draw("colz");
    Pion->cd(16);
    hist_theta2->Draw();
    Pion->cd(17);
    hist_eta2->Draw();
    Pion->SaveAs("/media/sf_Linux-To-Windows/all.png");
}
