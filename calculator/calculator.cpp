#include "calculator.h"
#include "ui_calculator.h"

double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

calculator::calculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::calculator)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(calcVal));
    QPushButton*numButtons[10];
    for(int i=0;i<10;++i){
        QString butName ="Button"+QString::number(i);
        numButtons[i]= calculator::findChild<QPushButton*>(butName);
        connect(numButtons[i],SIGNAL(released()), this,
                SLOT(Numpressed()));
    }
    // Connect signals and slots for math buttons
        connect(ui->Add, SIGNAL(released()), this,
                SLOT(MathButtonPressed()));
        connect(ui->Substract, SIGNAL(released()), this,
                SLOT(MathButtonPressed()));
        connect(ui->Multiply, SIGNAL(released()), this,
                SLOT(MathButtonPressed()));
        connect(ui->Divide, SIGNAL(released()), this,
                SLOT(MathButtonPressed()));

        // Connect equals button
        connect(ui->Equal, SIGNAL(released()), this,
                SLOT(EqualButton()));

        // Connect change sign
        connect(ui->ChangeSign, SIGNAL(released()), this,
                SLOT(ChangeNumberSign()));


}
calculator::~calculator()
{
    delete ui;
}

void calculator::Numpressed(){
    QPushButton*button=(QPushButton *)sender();
    QString butval=button->text();
    QString displayval=ui->Display->text();
    if((displayval.toDouble()==0) ||(displayval.toDouble()==0.0)){
        ui->Display->setText(butval);
    }else{
        QString newval = displayval+butval;
        double dblNewval = newval.toDouble();
        ui->Display->setText(QString::number(dblNewval, 'g',16));

    }

}
void calculator::MathButtonPressed(){
    //cancel out previous math button clicks
    divTrigger=false;
     multTrigger=false;
      addTrigger=false;
       subTrigger=false;

       //store current value on display
       QString displayval = ui->Display->text();
       calcVal = displayval.toDouble();

       //sender returns a pointer to the button pressed
      QPushButton*button=(QPushButton *)sender();

      //Get math symbol on the button
      QString butval = button->text();

      if(QString::compare(butval,"/",Qt::CaseInsensitive)==0)
      {

           divTrigger = true;
       }

      else if(QString::compare(butval,"*",Qt::CaseInsensitive)==0)
      {

           multTrigger = true;
       }
      else if(QString::compare(butval,"+",Qt::CaseInsensitive)==0)
      {

           addTrigger = true;
       }
      else
      {
          subTrigger = true;
      }

      //clear display
      ui->Display-> setText("");
}
void calculator::EqualButton(){
    //Holds new calculation
    double Solution =0.0;

    //get value in display
    QString displayval = ui->Display->text();
    double dbldisplayval = displayval.toDouble();

    //make sure a math button was pressed
    if(addTrigger||subTrigger||multTrigger||divTrigger){
        if(addTrigger){
            Solution = calcVal +dbldisplayval;
        }
        else if(subTrigger){
            Solution = calcVal-dbldisplayval;
        }
        else if(multTrigger){
            Solution = calcVal*dbldisplayval;
        }
        else{
            Solution = calcVal/dbldisplayval;
        }
    }
    //put solution in display
    ui->Display->setText(QString::number(Solution));

}
void calculator ::ChangeNumberSign(){
    //get the value on display
    QString displayval = ui->Display->text();

    //regular expression checking the number &plus sign
    QRegExp reg("[-+]?[0-9]*");

    //if it is a number change the sign
    if(reg.exactMatch(displayval)){
        double dbldispalyval = displayval. toDouble();
        double dbldisplayvalsign = -1* dbldispalyval;

        //put solution in display
        ui->Display->setText(QString::number(dbldisplayvalsign));


    }


}

void calculator::on_Clear_clicked()
{
    ui->Display->setText("");
}
