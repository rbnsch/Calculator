/*
Authors: Robin Schmidt, Jonas Schreiner
Purpose: Calculator GUI Application, GUI button functionality
last changed: 23.07.2020
*/

#include "Calculator.h"
#include <QDebug>
#include "Storage.h"
#include <QListWidgetItem>
#include <string>
#include "invalidMathOperation.h"

//#include <QObject>



Calculator::Calculator(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    bracketc = 0; //number of closed brackets
    bracketo = 0; //number of open brackets

    //button connectivity

    //number buttons
    connect(ui.pushButton1, SIGNAL(released()), this, SLOT(pushbutton()));
    connect(ui.pushButton2, SIGNAL(released()), this, SLOT(pushbutton()));
    connect(ui.pushButton3, SIGNAL(released()), this, SLOT(pushbutton()));
    connect(ui.pushButton4, SIGNAL(released()), this, SLOT(pushbutton()));
    connect(ui.pushButton5, SIGNAL(released()), this, SLOT(pushbutton()));
    connect(ui.pushButton6, SIGNAL(released()), this, SLOT(pushbutton()));
    connect(ui.pushButton7, SIGNAL(released()), this, SLOT(pushbutton()));
    connect(ui.pushButton8, SIGNAL(released()), this, SLOT(pushbutton()));
    connect(ui.pushButton9, SIGNAL(released()), this, SLOT(pushbutton()));
    connect(ui.pushButton0, SIGNAL(released()), this, SLOT(pushbutton()));

    //functionality buttons
    connect(ui.pushButtonEquals, SIGNAL(released()), this, SLOT(equals()));
    connect(ui.pushButtonClear, SIGNAL(released()), this, SLOT(clear()));
    connect(ui.pushButtonDelete, SIGNAL(released()), this, SLOT(deletelast()));
    connect(ui.pushButtonHist, SIGNAL(released()), this, SLOT(history()));
    connect(ui.pushButtonNegative, SIGNAL(released()), this, SLOT(changeprefix()));
    connect(ui.pushButtonAns, SIGNAL(released()), this, SLOT(ans()));
    connect(ui.pushButtonBracketO, SIGNAL(released()), this, SLOT(pushBracket()));
    connect(ui.pushButtonBracketC, SIGNAL(released()), this, SLOT(pushBracket()));
    

    //operator add buttons
    connect(ui.pushButtonAdd, SIGNAL(released()), this, SLOT(pushOperator()));
    connect(ui.pushButtonSub, SIGNAL(released()), this, SLOT(pushOperator()));
    connect(ui.pushButtonMultiply, SIGNAL(released()), this, SLOT(pushOperator()));
    connect(ui.pushButtonDivide, SIGNAL(released()), this, SLOT(pushOperator()));
    connect(ui.pushButtonRoot, SIGNAL(released()), this, SLOT(pushOperator()));
    connect(ui.pushButtonExponent, SIGNAL(released()), this, SLOT(pushOperator()));
    connect(ui.pushButtonDecimal, SIGNAL(released()), this, SLOT(pushOperator()));

    //get history from listdwidget button
    connect(ui.listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(itemSelected(QListWidgetItem*)));
}

//function for pushed numbers
void Calculator::pushbutton() {
    QPushButton* button = (QPushButton*)sender();
    ui.textInput->setText(ui.textInput->toPlainText() + button->text());

}

//recall last result 
void Calculator::ans() {
    QString s = QString::fromStdString(history.getlastresult());
    ui.textInput->setText(ui.textInput->toPlainText() + s);
}

//bracket button pushed and checked for correct input
void Calculator::pushBracket() {
    QPushButton* button = (QPushButton*)sender();
    QString n = button->text();
    QString s = ui.textInput->toPlainText();
    if (n == '(') {
        if (s == "" || s.back() == '+' || s.back() == '-' || s.back() == '/' || s.back() == '*' || s.back() == '^' || s.back() == 'r' || s.back() == '(') {
        ui.textInput->setText(s + n);
        }
    }
    else {
        if (!(s == "") & !(s.back() == '+' || s.back() == '-' || s.back() == '/' || s.back() == '*' || s.back() == '^' || s.back() == 'r' || s.back() == '(')) {
            ui.textInput->setText(s + n);
        }
    }
}

//change prefix button pushed also checking input at correct spot
void Calculator::changeprefix() {
    QString s = ui.textInput->toPlainText();
    int n = s.size();
    if (s != "" && s.back() == '-') {
        if ((n == 1 || s.data()[n - 2] == '+' || s.data()[n - 2] == '-' || s.data()[n - 2] == '*' || s.data()[n - 2] == '/' || s.data()[n - 2] == '^' || s.data()[n - 2] == 'r')){
            s.chop(1);
            ui.textInput->setText(s);
        }
        else {
            ui.textInput->setText(s + "-");
        }
        
    }
    else if (s == "" || (s.back() == '+' || s.back() == '/' || s.back() == '*' || s.back() == '^' || s.back() == 'r' || s.back() == ',')) {
        ui.textInput->setText(s + "-");
    }
    

}

//Function for all the Operator buttons, also checks for correct syntax in term
void Calculator::pushOperator() {
    QPushButton* button = (QPushButton*)sender();
    QString n = button->text();
    QString s = ui.textInput->toPlainText();
    if (n == "sqrt") {
        if ((s == "" || (!(s.back() <= 57 && s.back() >= 48)) && s.back() != 'r' && s.back() != 46)) {
            n = "r";
            ui.textInput->setText(ui.textInput->toPlainText() + n);
        }
    } 
    else if (s != "") {
            if (!(s.back() == '+' || s.back() == '-' || s.back() == '/' || s.back() == '*' || s.back() == '^' || s.back() == 'r' || s.back() == ',' || s.back() == '(')) {
                ui.textInput->setText(ui.textInput->toPlainText() + n);
            }
    }
}

//equals button pushed, computes the term in the inputbox, stores it in history and puts out result in outputbox
void Calculator::equals() {
    ui.textOutput->setText("");
    QString s = ui.textInput->toPlainText();
    if (s != "") {
        QByteArray input = s.toLocal8Bit();
        char* inputString = input.data();
        Evaluate eval(inputString);
        try {
            double x = eval.analyse();
            history.save(inputString, x);
            QString qstr = QString::fromStdString(history.getlastcalculation());
            ui.listWidget->addItem(qstr);
            ui.textOutput->setText(qstr);
        }
        catch (invalidMathOperation e) {
            ui.textOutput->setText(QString::fromStdString(e.problem));
        }
        this->clear();
    }
    
    
    


}

//clears inputfield
void Calculator::clear() {
    ui.textInput->setText("");
}

//deletes last char in inputfield
void Calculator::deletelast() {
    QString s = ui.textInput->toPlainText();
    s.chop(1);
    ui.textInput->setText(s);
}

//takes item from history list and puts it in the inputbox
void Calculator::itemSelected(QListWidgetItem* item) {
    ui.textOutput->setText("");
    int x = ui.listWidget->currentRow();
    QString qstr = QString::fromStdString(history.getCalc(x));
    ui.textInput->setText(qstr);

}
