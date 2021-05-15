#include "set_team.h"
#include "match.h"
#include "ui_match.h"

Match::Match(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Match)
{
    ui->setupUi(this);

    this->setWindowTitle("Match Results");
}

Match::~Match()
{
    delete ui;
}

int score1 = 0; int score2 = 0;

void Match::on_buttonBox_accepted()
{
    int row_count = 0;
    int team_count = 0;
    QString Team1 = ui->lineTeam1->text();
    QString Team2 = ui->lineTeam2->text();
    qDebug() << Team1 << Team2;
    QSqlQuery qry2;
    if((qry2.exec("SELECT * FROM teams WHERE team='"+Team1+"'")) && qry2.exec("SELECT * FROM teams WHERE team='"+Team2+"'")) //Наличие команд?
    {
        while (qry2.next()) {
            team_count++;
        }
        if (team_count==1) {
            QSqlQuery * find_row = new QSqlQuery;
            find_row->exec("SELECT No FROM teams WHERE team='"+Team1+"'");
            find_row->next();
            row_count = find_row->value(0).toInt();
            qDebug() << "Team found at" << row_count;
        }
        if (team_count < 1)
            qDebug() << "Unable to find team";
        if (team_count > 1)
            qDebug() << "Duplicate teams found";
    }

    int wins1, wins2, losses1, losses2, draws1, draws2, shot1, shot2, got_shot1, got_shot2, pts1, pts2;
    QSqlQuery * match_logic1 = new QSqlQuery;
    QSqlQuery * match_logic2 = new QSqlQuery;
    match_logic1->exec("SELECT * FROM teams WHERE team='"+Team1+"'");
    match_logic2->exec("SELECT * FROM teams WHERE team='"+Team2+"'"); //Поиск рядов по командам
    match_logic1->next();
    match_logic2->next();

    //Чтение всех данных из рядов
    wins1 = match_logic1->value(2).toInt();
    wins2 = match_logic2->value(2).toInt();
    losses1 = match_logic1->value(3).toInt();
    losses2 = match_logic2->value(3).toInt();
    draws1 = match_logic1->value(4).toInt();
    draws2 = match_logic2->value(4).toInt();
    shot1 = match_logic1->value(5).toInt();
    shot2 = match_logic2->value(5).toInt();
    got_shot1 = match_logic1->value(6).toInt();
    got_shot2 = match_logic2->value(6).toInt();
    pts1 = match_logic1->value(7).toInt();
    pts2 = match_logic2->value(7).toInt();
    shot1 += score1; got_shot1 += score2; shot2 += score2; got_shot2 += score1;

    if (score1 > score2) {
        wins1++; losses2++;
        pts1 += 3;
    }
    if (score1 < score2) {
        wins2++; losses1++;
        pts2 += 3;
    }
    if (score1 == score2) {
        draws1++; draws2++;
        pts1++; pts2++;
    }
    match_logic1->prepare("UPDATE teams SET wins = :w1, losses = :l1, draws = :d1, balls_shot = :s1, balls_lost = :gs1, points = :p1 WHERE team = '"+Team1+"'");
    match_logic1->bindValue(":w1", wins1);
    match_logic1->bindValue(":l1", losses1);
    match_logic1->bindValue(":d1", draws1);
    match_logic1->bindValue(":s1", shot1);
    match_logic1->bindValue(":gs1", got_shot1);
    match_logic1->bindValue(":p1", pts1);
    match_logic1->exec();

    match_logic2->prepare("UPDATE teams SET wins = :w2, losses = :l2, draws = :d2, balls_shot = :s2, balls_lost = :gs2, points = :p2 WHERE team = '"+Team2+"'");
    match_logic2->bindValue(":w2", wins2);
    match_logic2->bindValue(":l2", losses2);
    match_logic2->bindValue(":d2", draws2);
    match_logic2->bindValue(":s2", shot2);
    match_logic2->bindValue(":gs2", got_shot2);
    match_logic2->bindValue(":p2", pts2);
    match_logic2->exec();

        score1 = 0; score2 = 0;
        qDebug() << "Team1:" << wins1 << losses1 << draws1 << shot1 << got_shot1 << pts1;
        qDebug() << "Team2:" << wins2 << losses2 << draws2 << shot2 << got_shot2 << pts2;
    }

void Match::on_goal1_clicked()
{
    if (score1 <= 999) {
        score1++;
        ui->label_Score1->setText(QString::number(score1));
    }
}

void Match::on_goal2_clicked()
{
    if (score2 <= 999) {
        score2++;
        ui->label_Score2->setText(QString::number(score2));
    }
}

void Match::on_retract1_clicked()
{
    if (score1 > 0) {
        score1--;
        ui->label_Score1->setText(QString::number(score1));
    }
}

void Match::on_retract2_clicked()
{
    if (score2 > 0) {
        score2--;
        ui->label_Score2->setText(QString::number(score2));
    }
}

void Match::on_buttonBox_rejected()
{
    score1 = 0; score2 = 0;
}

