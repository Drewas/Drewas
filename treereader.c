#include <iostream>
#include <fstream>
#include <cmath>

#include <Rtypes.h>
#include <TString.h>
#include <TChain.h>
#include <TVector3.h>
#include <TMath.h>
#include "TH1F.h"
#include "TFile.h"

void treereader()
{
	TChain *inchain = new TChain("T");
	inchain->Add("/media/sf_Linux-To-Windows/4agev/run*.root");

  const Int_t NtrackMax = 1000;
  Int_t           ievnt;
  Int_t           ntrks_g;
  Int_t           mfilt_g;
  Int_t           nv0_g;
  Float_t         qphi_g;
  Float_t         dqphi_g;
  Float_t         phi12_g;
  Float_t         qxcorr_g;
  Float_t         qycorr_g;
  Int_t           n;
  Int_t           itrk[NtrackMax];
  Int_t           a1[NtrackMax];
  Int_t           a2[NtrackMax];
  Int_t           a3[NtrackMax];
  Int_t           z1[NtrackMax];
  Int_t           z2[NtrackMax];
  Int_t           z3[NtrackMax];
  Float_t         p1[NtrackMax];
  Float_t         p2[NtrackMax];
  Float_t         p3[NtrackMax];
  Float_t         dedx[NtrackMax];
  Float_t         diffphi[NtrackMax];
  Float_t         pzcm[NtrackMax];
  Float_t         qphi[NtrackMax];
  Float_t         theta[NtrackMax];
  Float_t         weight[NtrackMax];
  Float_t         ylab[NtrackMax];
  Float_t         ycm[NtrackMax];
  Float_t         mass[NtrackMax];
  Float_t         nnet[NtrackMax];

  inchain->SetBranchAddress("ievnt", &ievnt);
  inchain->SetBranchAddress("ntrks_g", &ntrks_g);
  inchain->SetBranchAddress("mfilt_g", &mfilt_g);
  inchain->SetBranchAddress("nv0_g", &nv0_g);
  inchain->SetBranchAddress("qphi_g", &qphi_g);
  inchain->SetBranchAddress("dqphi_g", &dqphi_g);
  inchain->SetBranchAddress("phi12_g", &phi12_g);
  inchain->SetBranchAddress("qxcorr_g", &qxcorr_g);
  inchain->SetBranchAddress("qycorr_g", &qycorr_g);
  inchain->SetBranchAddress("n", &n);
  inchain->SetBranchAddress("itrk", itrk);
  inchain->SetBranchAddress("a1", a1);
  inchain->SetBranchAddress("a2", a2);
  inchain->SetBranchAddress("a3", a3);
  inchain->SetBranchAddress("z1", z1);
  inchain->SetBranchAddress("z2", z2);
  inchain->SetBranchAddress("z3", z3);
  inchain->SetBranchAddress("p1", p1);
  inchain->SetBranchAddress("p2", p2);
  inchain->SetBranchAddress("p3", p3);
  inchain->SetBranchAddress("dedx", dedx);
  inchain->SetBranchAddress("diffphi", diffphi);
  inchain->SetBranchAddress("pzcm", pzcm);
  inchain->SetBranchAddress("qphi", qphi);
  inchain->SetBranchAddress("theta", theta);
  inchain->SetBranchAddress("weight", weight);
  inchain->SetBranchAddress("ylab", ylab);
  inchain->SetBranchAddress("ycm", ycm);
  inchain->SetBranchAddress("mass", mass);
  inchain->SetBranchAddress("nnet", nnet);

  Long64_t Nentries = inchain->GetEntries();


  //Histograms
  TProfile* bphi12 = new TProfile ("bphi12","cos(phi12) vs b", 10, 0, 10);
  TProfile* hphi12 = new TProfile ("hphi12","cos(phi12)", 400, 0, 230);
  TH1F* hptprot = new TH1F ("hptprot", "transverse impulse of protons", 400, -0.01, 3);
  TH1F* hptpi = new TH1F ("hptpi", "transverse impulse of pions", 400, -0.01, 1.05);
  TH1F* hycm = new TH1F ("hycm", "Rapidity in center mass", 400, -1.1, 2.7);
  TH1F* hylab = new TH1F ("hylab", "Rapidity in lab", 400, -0.3, 3.2);
  TH2F* hRigid = new TH2F("hRigid", "Rigidity to dE/dx", 400, -2, 2, 700, -5.0,-2.4);
  TH2F* hRigidprot = new TH2F("hRigidprot", "Rigidity of protons to dE/dx", 400, -2, 2, 700, -5.0,-2.4);
  TH1F* hMult = new TH1F("hMult", "Multiplicity", 100, 0, 400);
  for (Long64_t iev = 0; iev < Nentries; iev++)
  {
	  inchain->GetEntry(iev);
	  float phi12rad = phi12_g*TMath::DegToRad();
	  float cophi12rad = cos(phi12rad);
	  std::vector<float> bmult = {0,60,90,120,155,180,210,235,260};
      for (int i=0; i<8;i++)
      {
          if (ntrks_g>bmult[i] && ntrks_g<bmult[i+1])
          {
              bphi12->Fill((9-i), cophi12rad);
          }
      }
      if (ntrks_g>bmult[8])
          {
              bphi12->Fill(1, cophi12rad);
          }
	  if (iev%1000==0)
          std::cout << "event " << iev << " out of "<< Nentries << std::endl;
	  hMult->Fill(n);
	  hphi12->Fill(ntrks_g,cophi12rad);
	  for (int itr=0;itr < n; itr++)
      {
          float rigidity = sqrt(p1[itr]*p1[itr] + p2[itr]*p2[itr]+ p3[itr]*p3[itr])/(z1[itr]);
          float log10_dedx = log10(dedx[itr]);
          float pt = sqrt(p1[itr]*p1[itr]+p2[itr]*p2[itr]);
          hycm->Fill(ycm[itr]);
          hylab->Fill(ylab[itr]);
          hRigid->Fill(rigidity,log10_dedx);
          if (z1[itr]==1 && a1[itr]==1)
          {
              hRigidprot->Fill(rigidity,log10_dedx);
              hptprot->Fill(pt);
          }
          if (z1[itr]==1 && a1[itr]==0)
          {
              hptpi->Fill(pt);
          }
      }
  }
  TFile *f4 = new TFile("Histo4gev.root", "recreate");
  hRigid->Write(); // жесткость по dEdx
  hRigidprot->Write(); //Жесткость протонов
  hMult->Write(); // множественность
  hphi12->Write(); // косинус phi12
  bphi12->Write(); // центральность ядер, разделенная по классам множественности
  hylab->Write();// быстрота в лаб системе
  hycm->Write(); // быстрота в системе центра масс
  hptpi->Write(); // поперечный имппульс пионов
  hptprot->Write(); // поперечный импульс протонов
}
