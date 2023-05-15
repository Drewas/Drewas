#include <iostream>
#include <cmath>
#include <TMath.h>

void nica(string filename = "")
{
    //ROOT::EnableImplicitMT();
    ROOT::RDataFrame d("mctree", "/mnt/pool/nica/8/parfenovpeter/Models/UrQMD/urqmd109/auau_2.4gev_hardSkyrme/part1/urqmd_auau_2.4gev_hardSkyrme_3943343_582*.root");
    TCanvas *c1=new TCanvas("c1","test",1920,720);
    c1 -> Divide (3,1);

    auto GetQv = [](const ROOT::VecOps::RVec<Float_t> &Uvector) 
    {
    float Qv=0;
    for (int i=0; i<Uvector.size();i++)
    {Qv += Uvector.at(i);}
    std::cout << Qv << std::endl;
    return Qv;
    };

    auto picycle = [](float psivector)
    {
    float psi = psivector;
    psi = atan2(sin(psi),cos(psi));
    return psi;
    };

    auto h_bimp = d.Histo1D("bimp");
    auto h_nh = d.Histo1D("nh");
    auto h_momx = d.Histo1D("momx");
    auto h_momy = d.Histo1D("momy");
    auto h_momz = d.Histo1D("momz");

auto dd=d
    .Define("pt","sqrt(momx*momx+momy*momy)")
    .Define("p","sqrt(momx*momx+momy*momy+momz*momz)")
    .Define("eta","0.5*log((p+momz)/(p-momz))")
    .Define("eta_protons","eta[pdg==2112]")
    .Define("eta_pions","eta[pdg==211]")
    .Define("eta_kaons","eta[pdg==321]")
    .Define("phi","atan2(momy,momx)")
    .Define("Uxl","cos(1*phi[eta>-5 && eta<-2])")
    .Define("Uxr","cos(1*phi[eta>2 && eta<5])")
    .Define("Uyl","sin(1*phi[eta>-5 && eta<-2])")
    .Define("Uyr","sin(1*phi[eta>2 && eta<5])")
    .Define("Qxl",GetQv, {"Uxl"})
    .Define("Qxr",GetQv, {"Uxr"})
    .Define("Qyl",GetQv, {"Uyl"})
    .Define("Qyr",GetQv, {"Uyr"})
    .Define("psiepRraw","atan2(Qyr,Qxr)")
    .Define("psiepLraw","atan2(Qyl,Qxl)+(float)TMath::Pi()")
    .Define("psiepR",picycle,{"psiepRraw"})
    .Define("psiepL",picycle,{"psiepLraw"})
    .Define("res2","cos(psiepR-psiepL)");
    v1r=(Ux*Qx+Uy*Qy)/res(bin по bimp) //Uслева Qсправа
    v1l=                              //Uсправа Qслева
    v1=(v1l+v1r)/2

    auto h_pt = dd.Histo1D("pt");
    auto h_eta = dd.Histo1D("eta");
    auto h_phi = dd.Histo1D("phi");
    auto h_protons = dd.Histo1D("eta_protons");
    auto h_pions = dd.Histo1D("eta_pions");
    auto h_kaons = dd.Histo1D("eta_kaons");
    auto h_phiepR = dd.Histo1D({"PsiepR", "Psi event plane right", 120, -1*TMath::Pi(), TMath::Pi()},"psiepR");
    auto h_phiepL = dd.Histo1D({"PsiepL", "Psi event plane left", 120, -1*TMath::Pi(), TMath::Pi()},"psiepL");
    auto p_res2 = dd.Profile1D({"Res2", "Resolution 2 profile", 20, 0, 20}, "bimp", "res2");
    auto h_res2 = dd.Histo1D({"res2","resolution2",40,-1.5,1.5},"res2");
    
    auto p_res = new TH1D("Res","Resolution",p_res2->GetNbinsX(),0,20);
    
    for (int i=0;i<p_res2->GetNbinsX();i++)
    {
        float x=p_res2->GetBinCenter(i+1);
        float y=p_res2->GetBinContent(i+1);
        float res = sqrt(y);
        float ey = p_res2->GetBinError(i+1);
        float eres = (y==0) ? 0 : (0.5/sqrt(y))*ey;
        p_res->SetBinContent(i+1,res);
        p_res->SetBinError(i+1,eres);
        cout<<"bin " << i+1 << ": x="<< x << ", y="<< res << endl; 
    }

    TFile *f0 = new TFile("/mnt/pool/nica/8/drewas/test.root","recreate"); //read
    f0->cd();
    p_res->Write();
    p_res2->Write();
    f0->Close();

    c1->cd(1);
    h_phiepR->Draw();
    c1->cd(2);
    h_phiepL->Draw();
    c1->cd(3);
    p_res->Draw();
    c1->SaveAs("/mnt/pool/nica/8/drewas/test.png");
}