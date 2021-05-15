#ifndef MATCH_H
#define MATCH_H

#include <QDialog>

namespace Ui {
class Match;
}

class Match : public QDialog
{
    Q_OBJECT

public:
    explicit Match(QWidget *parent = nullptr);
    ~Match();

private slots:
    void on_buttonBox_accepted();

    void on_goal1_clicked();

    void on_goal2_clicked();

    void on_retract1_clicked();

    void on_retract2_clicked();

    void on_buttonBox_rejected();

private:
    Ui::Match *ui;
};

#endif // MATCH_H
