#include <iostream>

using namespace std;

void Taskno3()
{
    TCanvas *canvas = new TCanvas("hist","gaus",700,500);
    TH1F *gausexp = new TH1F("h","hist", 2000, -20.,20.);
    TF1 *gaup = new TF1 ("exponentg", "exp(x)+100*gaus(x,2)", -20.,20.);
    gausexp->FillRandom("exponentg",10000);
    canvas->SaveAs("/media/sf_Linux-To-Windows/task_no3.png");
}
