#include "add.h"
#include "ui_add.h"
#include "set_team.h"

Add::Add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add)
{
    ui->setupUi(this);
}

Add::~Add()
{
    delete ui;
}

void Add::on_buttonBox_accepted()
{
    QString team_name = ui->lineEdit->text();
        int row_count = 0;
        QSqlQuery * find_row = new QSqlQuery;
        find_row->exec("SELECT * FROM teams WHERE No=(SELECT max(No) FROM teams)");
        find_row->next();
        row_count = find_row->value(0).toInt();
        row_count++;
        qDebug() << "Last team No. is" << row_count;
        QSqlQuery * qry = new QSqlQuery;
            qry->prepare("INSERT INTO teams VALUES (:No, :team, 0, 0, 0, 0, 0, 0)");
            qry->bindValue(":No", row_count);
            qry->bindValue(":team", team_name);
            qry->exec();
}
