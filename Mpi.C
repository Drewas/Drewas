#include <iostream>
#include <cmath>

using namespace std;

void Mpi()
{
    setlocale( LC_ALL, "Russian" );
    double m_p0 = 0.135; //GeV//
    int const c = 3*pow(10,8);
    //|p1|=|p2|=p, E=pc => mc^2=2pc => p = mc^2/2//
    //m_po^2 = 4E_g1*E_g2 => E_g1 = m_po/2//
    double p1,p2;
    p1= m_p0*pow(c,2)/2;
    p2=p1;
    double E_g1, E_g2;
    E_g1 = m_p0/2;
    E_g2 = E_g1;
    cout << "»мпульс гамма кванта 1 = импульсу гамма кванта два и равен = " << p1 << endl << "Ёнерги€ гамма кванта 1 = энергии гамма кванта два и равна = " << E_g1 << endl;
}
