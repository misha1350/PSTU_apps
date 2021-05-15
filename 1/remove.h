#ifndef REMOVE_H
#define REMOVE_H

#include <QDialog>

namespace Ui {
class Remove;
}

class Remove : public QDialog
{
    Q_OBJECT

public:
    explicit Remove(QWidget *parent = nullptr);
    ~Remove();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Remove *ui;
};

#endif // REMOVE_H
