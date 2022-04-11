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
    srand(time(NULL));
    double phi,px,py;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-M_PI, M_PI);
    phi = dis(gen);
    int const c = 1;
    double p1,p2;
    p1= m_p0/2;
    p2=p1;
    double E_g1, E_g2;
    E_g1 = m_p0/2;
    E_g2 = E_g1;
    cout << "Импульс гамма кванта 1 = импульсу гамма кванта два и равен = " << p1 << " GeV/c" <<endl << "Энергия гамма кванта 1 = энергии гамма кванта два и равна = " << E_g1 << "GeV" << endl;
    px=p1*cos(phi);
    py=p1*sin(phi);
}
