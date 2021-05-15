#ifndef SET_TEAM_H
#define SET_TEAM_H

#include <QDialog>
#include <QtSql>
#include <QSqlError>
#include <QDebug>
#include <QFileInfo>

namespace Ui {
class Set_team;
}

class Set_team : public QDialog
{
    Q_OBJECT

public:
    explicit Set_team(QWidget *parent = nullptr);
    ~Set_team();

private slots:

    void on_addTeam_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_submit_clicked();

    void on_undo_clicked();

private:
    Ui::Set_team *ui;
    QSqlDatabase db2;
    QSqlTableModel *model;
};

#endif // SET_TEAM_H
