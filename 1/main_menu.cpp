#include "main_menu.h"
#include "ui_main_menu.h"
#include <QFileInfo>

main_menu::main_menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::main_menu)
{
    ui->setupUi(this);

    this->setWindowTitle("Tournament Table Calculator");

    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./data.db");

    if(db.open())
        ui->label->setText("Database success");
    else
        ui->label->setText("Database failure");
}

main_menu::~main_menu()
{
    delete ui;
}


void main_menu::on_pushButton_clicked()
{
    window = new Set_team(this);
    window->setAttribute(Qt::WA_DeleteOnClose); //Освобождение памяти после закрытия окна set_team
    window->show();
}
