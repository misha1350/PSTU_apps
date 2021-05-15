#include <main_menu.h>
#include "set_team.h"
#include "ui_set_team.h"
#include "QTableWidget"
#include "match.h"
#include "remove.h"
#include "add.h"

Set_team::Set_team(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Set_team)
{
    ui->setupUi(this);

    this->setWindowTitle("Edit Teams");

//    this->setCentralWidget(ui->tableView);

    db2=QSqlDatabase::addDatabase("QSQLITE");
    db2.setDatabaseName("./data.db");
    db2.open();

    QSqlQuery qry;
    qry.exec("CREATE TABLE IF NOT EXISTS teams (No int primary key, team text, wins int, losses int, draws int, balls_shot int, balls_lost int, points int)");

    model = new QSqlTableModel(ui->tableView);
    model->setTable("teams");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    model->setSort(7,Qt::DescendingOrder);

    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
}

Set_team::~Set_team()
{
    delete ui;
}

void Set_team::on_addTeam_clicked()
{
    Add window;
    window.setModal(true); //Открывается модальное окно
    window.exec();
}

void Set_team::on_pushButton_3_clicked()
{
    Match window;
    window.setModal(true);
    window.exec();
}

void Set_team::on_pushButton_4_clicked()
{
    Remove window;
    window.setModal(true);
    window.exec();
}

void Set_team::on_submit_clicked()
{
    model->submitAll();
}

void Set_team::on_undo_clicked()
{
    model->revertAll();
}
