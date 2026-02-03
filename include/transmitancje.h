#pragma once
#include <vector>
class Transmitancja
{
    private:
        double* licznik;
        double* mianownik;
    public:
        double* getLicznik();
        double* getMianownik();
        void setLicznik(double* licznik);
        void setMianownik(double* mianownik);
        double* Pochodna(double* wielomian, int rozmiar/*, int* nowyrozmiar*/);
        double* Pochodna(std::vector<double*> wielomiany);
        double* Horner(double* wielomian, int rozmiar, double dzielnik);
        double MetodaNewtona(int interacje, double* wielomian, int rozmiar);
        std::vector<double*> WyznaczanieBiegunowZer(double* wielomian, int iteracje, int rozmiar);
        //Transmitancja(int rozLicz, int rozMian);
};