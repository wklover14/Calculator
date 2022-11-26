#include "numbers.h"
#include "ui_numbers.h"

Numbers::Numbers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Numbers)
{
    ui->setupUi(this);
}

Numbers::~Numbers()
{
    delete ui;
}
