/*
Authors: Robin Schmidt, Jonas Schreiner
Purpose: Calculator GUI Application, main function / starting point of the application
last changed: 23.07.2020
*/
#include "Calculator.h"
#include <QtWidgets/QApplication>
#include "Storage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    Storage history;
    Calculator w;
    w.show();
    return a.exec();
}
