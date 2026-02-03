#include <iostream>
#include <vector>
#include <QApplication>
#include <QMainWindow>
#include "transmitancje.h"
#include "mainwindow.h"
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    double Licznik[5] = {1, 3, 5, 7, 4};
    double Mianownik[4] = {1, 4, 6, 2};
    int ptr;
    Transmitancja tran;
    double LicznikBieguny[6] = {1, 15 , 85, 225, 274, 120};
    std::vector<double*> myVec;
    myVec = tran.WyznaczanieBiegunowZer(LicznikBieguny,20,6);
    double* Rzeczywiste = myVec.at(0); 
    double* Urojone = myVec.at(1);
    Rzeczywiste = myVec.at(0);
    Urojone = myVec.at(1);
    for(int i = 0; i < sizeof(LicznikBieguny)/sizeof(double)-1; i++)
        std::cout << "Czesc Rzeczywista: " << Rzeczywiste[i] << " Czesc Urojona: " << Urojone[i] << std::endl;
    MainWindow window;
    QLineSeries *series = new QLineSeries();
    double LicznikChart = 1;
    double MianownikChart = 0;
    double czas;
    int j;
    for(int i = 1; i<10000; i++){
        if(i%10 == 0){
            czas = i/(double)1000;
            for(j = 0 ; j< 5; j++){
                if (j == 0)
                    MianownikChart += 1-exp(Rzeczywiste[j]*czas);
                else
                    MianownikChart += exp(Rzeczywiste[j]*czas);
            }
            series->append(czas,MianownikChart);
            std::cout << MianownikChart << i << std::endl;
        }
        MianownikChart = 0;
    }
    
    QChart* chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    QChartView* view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    window.setCentralWidget(view);
    window.show();
    return app.exec();
}