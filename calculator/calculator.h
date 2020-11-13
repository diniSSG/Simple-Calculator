#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include<QPushButton>

namespace Ui {
class calculator;
}

class calculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit calculator(QWidget *parent = nullptr);
    ~calculator();

private:
    Ui::calculator *ui;

private slots:
    void Numpressed();
    void MathButtonPressed();
    void EqualButton();
    void ChangeNumberSign();

    void on_Clear_clicked();
};

#endif // CALCULATOR_H
