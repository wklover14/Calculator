#include "maincalculator.h"
#include "ui_maincalculator.h"

MainCalculator::MainCalculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainCalculator)
{
    ui->setupUi(this);

    ui->display->setText( QString::number( calcVal ) ) ;
    QPushButton *numButtons[10] ;
    for(int i = 0; i<10; i++){
        QString buttName = "Button_" + QString::number(i) ;
        numButtons[i] = MainCalculator::findChild<QPushButton *>(buttName) ;
        connect( numButtons[i], SIGNAL( released()), this , SLOT(NumPressed())) ;
    }

    //connect pour les bouttons de calculs mathematiques
    connect( ui->plus , SIGNAL( released() ), this , SLOT(MathButtonPressed() ) );
    connect( ui->moins , SIGNAL( released() ), this , SLOT(MathButtonPressed() ) );
    connect( ui->fois , SIGNAL( released() ), this , SLOT(MathButtonPressed() ) );
    connect( ui->diviser , SIGNAL( released() ), this , SLOT(MathButtonPressed() ) );

    //connect pour le boutton egale
    connect( ui->egale, SIGNAL( released()), this, SLOT( EqualButton() ) ) ;

    //connect pour le boutton signe
    connect( ui->signe, SIGNAL( released()), this, SLOT( ChangeNumberSign()) ) ;

    //connect pour le boutton ac
    connect( ui->AC, SIGNAL( released()), this, SLOT( clear() ) ) ;

    //connect pour les bouttons mem
    connect( ui->Mem_moins , SIGNAL( released() ), this, SLOT( subMemPressed() ) ) ;
    connect( ui->Mem_plus , SIGNAL( released() ), this, SLOT( addMemPressed() ) ) ;
    connect( ui->M , SIGNAL( released() ), this, SLOT( memPressed() ) ) ;
}

MainCalculator::~MainCalculator()
{
    delete ui;
}

void MainCalculator::updateCalcVal(){
    QString displayVal = ui->display->text() ;

    //on effectue l'operation précedente
    if(  divTrigger ){
        if( displayVal.toDouble() == 0 || displayVal.toDouble() == 0.0 ){
            ui->display->setText("E") ;
            divTrigger = false ;
            return ;
        } else {
            calcVal /= displayVal.toDouble() ;
        }
        divTrigger = false ;
    } else if ( multTrigger ) {
        calcVal *= displayVal.toDouble() ;
        multTrigger = false ;
    }else if ( plusTrigger ) {
        calcVal += displayVal.toDouble() ;
        plusTrigger = false ;
    }else if ( moinsTrigger ) {
        calcVal -= displayVal.toDouble() ;
        moinsTrigger = false ;
    } else {
        //cas où on vient d'appuyer sur egale et ensuite on appuie sur une touche de fonctions, par exemple
        calcVal = displayVal.toDouble() ;
        clearLine = false ;
    }
    ui->display->setText( QString::number(calcVal, 'g', 16) ) ;
}

//SLOTS

void MainCalculator::NumPressed(){
    if(clearLine){
        ui->display->setText("") ;
        clearLine = false ;
    }

    QPushButton *button =( QPushButton *)sender() ;
    QString butVal = button->text() ;
    QString displayVal = ui->display->text() ;
    if( (displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0) ){
        ui->display->setText( butVal ) ;
    } else {
        QString newVal = displayVal + butVal ;
        double dbNewVal = newVal.toDouble() ;
        ui->display->setText( QString::number(dbNewVal, 'g', 16) ) ;
    }
}
void MainCalculator::MathButtonPressed(){
    QPushButton *button = (QPushButton *)sender() ;

    updateCalcVal() ;
    op = button->text() ;
    if(clearLine){
        return ;
    }
    QString displayVal = ui->display->text() ;
    if(displayVal == "E")
           return ;

    if( op == "+" ){
        plusTrigger = true ;
    } else if( op == "-" ) {
        moinsTrigger = true ;
    } else if( op == "/" ){
        divTrigger = true ;
    } else if ( op == "*" ){
        multTrigger = true ;
    } else {
        //rien
    }
    clearLine = true ;
}
void MainCalculator::EqualButton(){
    updateCalcVal() ;
    double tmp = calcVal ;
    clearLine = true ;
    clear() ;
    calcVal = tmp ;
    ui->display->setText( QString::number(calcVal, 'g', 16) ) ;
}
void MainCalculator::ChangeNumberSign(){
    double val = (ui->display->text()).toDouble() ;
    val *= -1 ;
    ui->display->setText(  QString::number(val, 'g', 16)  ) ;
}
void MainCalculator::clear(){
   calcVal = 0.0 ;
   ui->display->setText("");
   divTrigger = false ;
   multTrigger = false ;
   plusTrigger = false ;
   moinsTrigger = false ;
   op = "" ;
}
void MainCalculator::subMemPressed(){
   updateCalcVal() ;
   ui->display->setText( QString::number(calcVal, 'g', 16)  ) ;
   mem -= calcVal ;
   clearLine = true ;
}
void MainCalculator::addMemPressed(){
   updateCalcVal() ;
   ui->display->setText( QString::number(calcVal, 'g', 16)  ) ;
   mem += (ui->display->text()).toDouble();
   clearLine = true ;
}
void MainCalculator::memPressed(){
    //ici on fait un rappel memoire lorsque l'affichage est vide
    if( ui->display->text() == "" ){
        ui->display->setText( QString::number(mem, 'g', 16) ) ;
        clearLine = true ;
    }
}

