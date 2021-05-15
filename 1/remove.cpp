#include "remove.h"
#include "ui_remove.h"
#include "set_team.h"

Remove::Remove(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Remove)
{
    ui->setupUi(this);

    this->setWindowTitle("Remove a team from the list");
}

Remove::~Remove()
{
    delete ui;
}

void Remove::on_buttonBox_accepted()
{
    QString team_name;
    team_name = ui->lineEdit->text();

    int row_count = 0;
            QSqlQuery * find_row = new QSqlQuery;
            find_row->exec("SELECT No FROM teams WHERE team='"+team_name+"'");
            find_row->next();
            row_count = find_row->value(0).toInt();
            qDebug() << "Row to be deleted:" << row_count;
            find_row->prepare("DELETE FROM teams WHERE team = '"+team_name+"'");
            find_row->exec();
        }
//    }
//}
