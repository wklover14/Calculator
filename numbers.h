#ifndef NUMBERS_H
#define NUMBERS_H

#include <QWidget>

namespace Ui {
class Numbers;
}

class Numbers : public QWidget
{
    Q_OBJECT

public:
    explicit Numbers(QWidget *parent = nullptr);
    ~Numbers();

private:
    Ui::Numbers *ui;
};

#endif // NUMBERS_H
