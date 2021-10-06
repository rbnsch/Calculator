#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Calculator.h"
#include <QPushButton>
#include <QApplication>
#include <iostream>
#include "Storage.h"
#include "Evaluate.h"

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = Q_NULLPTR);

private:
    Ui::CalculatorClass ui;
    Storage history;
    int bracketo;
    int bracketc;

public slots: 
    void pushbutton();
    void equals();
    void changeprefix();
    void clear();
    void deletelast();
    void pushOperator();
    void itemSelected(QListWidgetItem* item);
    void ans();
    void pushBracket();

};
