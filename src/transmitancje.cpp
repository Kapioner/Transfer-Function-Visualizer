#include "transmitancje.h"
#include <math.h>
#include <iostream>
#include <vector>
#include <complex>
double* Transmitancja::getLicznik(){
    return licznik;
}
double* Transmitancja::getMianownik(){
    return mianownik;
}
void Transmitancja::setLicznik(double* licznik){
    this->licznik = licznik;
}
void Transmitancja::setMianownik(double* mianownik){
    this->mianownik = mianownik;
}
double* Transmitancja::Pochodna(double* wielomian, int rozmiar/*, int* nowyrozmiar*/)
{
    double* NewWielomian = new double[rozmiar];
    int j = rozmiar-1,i;
    for( i = 0; i < rozmiar; i++ ){
        if (j>=0){
        NewWielomian[i] = wielomian[i]*j;
        j--;
        }
    }
    //std::copy(NewWielomian + 1, NewWielomian + rozmiar, NewWielomian); // std::copy( kopiuj od, kopiuj do, na miejsce )
    //*nowyrozmiar = i-1;
    return NewWielomian;
}
double* Transmitancja::Horner(double* wielomian, int rozmiar, double dzielnik){
    double* NewWielomian = new double[rozmiar];
    std::cout << "Dzielnik " << dzielnik;
    for(int i=0; i< rozmiar; i++)
    {
        if (i == 0)
            NewWielomian[0] = wielomian[0];
        else
        {
            NewWielomian[i] = NewWielomian[i-1]*dzielnik + wielomian[i];
            std::cout << "Wielomian[i]" << wielomian[i] << std::endl;
            std::cout << "Licznik horner " << NewWielomian[i] << std::endl;
        }
    }
    return NewWielomian;
}
double Transmitancja::MetodaNewtona(int iteracje, double* wielomian, int rozmiar){
    double miejsce = 1;
    int k;
    double WynWiel,WynPoch, newmiejsce;
    double* wielomian1;
    wielomian1 = Pochodna(wielomian,rozmiar);
    for(int i = 0; i< iteracje; i++){
        WynWiel = 0;
        WynPoch = 0;
        k = rozmiar - 1;
        for(int j = 0; j < rozmiar; j++){
            WynWiel += wielomian[j]*pow(miejsce, k);
            k--;
            if (k>=0)
            WynPoch += wielomian1[j]*pow(miejsce, k);
        }
        newmiejsce = miejsce - WynWiel/WynPoch;
        miejsce = newmiejsce;
        std::cout << miejsce << std::endl;
    }
    return miejsce;
}
std::vector<double*> Transmitancja::WyznaczanieBiegunowZer(double* wielomian, int iteracje, int rozmiar){
    double* NewWielomian = new double[rozmiar];
    std::vector<double*> myVec;
    int rozmiar1 = rozmiar;
    double* WielPoHornerze;
    double* Real = new double[rozmiar-1];
    double* Imaginary = new double[rozmiar-1];
    int j = 0;
    for(int i = 0; i < rozmiar; i++)
    {
        NewWielomian[i] = *(wielomian+i);
    }
    while (1)
    {
        if(rozmiar1 > 3)
        {
            double miejscezerowe = MetodaNewtona(iteracje,NewWielomian, rozmiar1);
            double miej = miejscezerowe;
            WielPoHornerze = Horner(NewWielomian, rozmiar1, miej);
            Real[j] = miejscezerowe;
            Imaginary[j] = 0;
            j++;
            for(int i = 0; i< rozmiar1; i++){
                NewWielomian[i] = *(WielPoHornerze+i); 
                std::cout << "Wielomian po hornerze " << NewWielomian[i] << std::endl;
            }
            rozmiar1--;
        }
        else
        {
            std::cout << NewWielomian[0] << std::endl << NewWielomian[1] << std::endl << NewWielomian[2] << std::endl;
            double delta = NewWielomian[1]*NewWielomian[1] - 4*NewWielomian[0]*NewWielomian[2]; 
            double x1, x2;
            if (delta > 0)
            {
                x1 = (-NewWielomian[1] + sqrt(delta))/(2*NewWielomian[0]);
                Real[j] = x1;
                Imaginary[j] = 0;
                j++;
                x2 = (-NewWielomian[1] - sqrt(delta))/(2*NewWielomian[0]);
                Real[j] = x2;
                Imaginary[j] = 0;
                break;
            }
            else if(delta == 0)
            {
                x1 = -NewWielomian[1]/(2*NewWielomian[0]);
                Real[j] = x1;
                Imaginary[j] = 0;
                j++;
                x2 = x1;                
                Real[j] = x1;
                Imaginary[j] = 0;
                break;
            }
            else if(delta < 0)
            {
                std::complex<double> x1(-NewWielomian[1]/(2*NewWielomian[0]), (std::sqrt(abs(delta)))/(2*NewWielomian[0]));
                Real[j] = real(x1);
                Imaginary[j] = imag(x1);
                j++;
                std::complex<double> x2(-NewWielomian[1]/(2*NewWielomian[0]), (-(std::sqrt(abs(delta)))/(2*NewWielomian[0])));                
                Real[j] = real(x2);
                Imaginary[j] = imag(x2);
                break;
            }
        }
    }
    myVec.push_back(Real);
    myVec.push_back(Imaginary);
    return myVec;
}
/*Transmitancja::Transmitancja(double* licznik, double* mianownik, int rozLicz, int rozMian){
    this->licznik = licznik+rozLicz;
    this->mianownik = mianownik+rozMian;
}*/