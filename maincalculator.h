#ifndef MAINCALCULATOR_H
#define MAINCALCULATOR_H

#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainCalculator; }
QT_END_NAMESPACE

class MainCalculator : public QMainWindow
{
    Q_OBJECT

public:
    MainCalculator(QWidget *parent = nullptr);
    ~MainCalculator();

private:
    Ui::MainCalculator *ui;
    double calcVal = 0.0 ;
    double mem = 0.0 ;
    bool divTrigger = false ;
    bool multTrigger = false ;
    bool plusTrigger = false ;
    bool moinsTrigger = false ;
    bool clearLine = false ;
    QString op = "" ;
    void updateCalcVal() ;

private slots:
      void NumPressed() ;
      void MathButtonPressed() ;
      void EqualButton() ;
      void ChangeNumberSign() ;
      void clear();
      void subMemPressed();
      void addMemPressed();
      void memPressed();
};
#endif // MAINCALCULATOR_H
