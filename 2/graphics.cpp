#include "graphics.h"
#include "ui_graphics.h"
#include "functional"
#include <queue>
#include <vector>

using namespace std;

// number of total nodes
const int N = 6;
const int INF = INT_MAX;

int adjacensyMatrix[N][N] =
{
    { INF, 28, 13, 15, INF, 18 },
    { 28,  INF, INF,  20,  21, INF },
    { 13,   INF,  INF, INF,  30, INF },
    { 15,   20,   INF,   INF, 39, 31},
    { 30,   21,   INF,   39, INF, INF },
    { 18,   INF,    INF,   31,   INF, INF }
};
int final_min;
QString final_path;
bool was_drawn;
class Logic
{
public:
    vector<pair<int, int>> path;
    int matrix_reduced[N][N];
    int cost;
    int vertex;
    int level;
};

void ReduceRow(int matrix_reduced[N][N], int row[N])
{
    fill_n(row, N, INF);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matrix_reduced[i][j] < row[i])
                row[i] = matrix_reduced[i][j];
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matrix_reduced[i][j] != INF && row[i] != INF)
                matrix_reduced[i][j] -= row[i];
        }
    }
}

void ReduceColumn(int matrix_reduced[N][N], int column[N])
{
    fill_n(column, N, INF);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matrix_reduced[i][j] < column[j])
                column[j] = matrix_reduced[i][j];
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matrix_reduced[i][j] != INF && column[j] != INF)
                matrix_reduced[i][j] -= column[j];
        }
    }
}

int CostCalc(int matrix_reduced[N][N])
{
    int cost = 0;

    int row[N];
    ReduceRow(matrix_reduced, row);

    int column[N];
    ReduceColumn(matrix_reduced, column);

    for (int i = 0; i < N; i++)
        cost += (row[i] != INT_MAX) ? row[i] : 0,
            cost += (column[i] != INT_MAX) ? column[i] : 0;
    return cost;
}

Logic* NewNode(int matrix_parent[N][N], vector<pair<int, int>> const &path,int level, int i, int j)
{
    Logic* node = new Logic;
    node->path = path;
    if (level != 0)
        node->path.push_back(make_pair(i, j));
    memcpy(node->matrix_reduced, matrix_parent,
        sizeof node->matrix_reduced);
    for (int k = 0; level != 0 && k < N; k++)
    {
        node->matrix_reduced[i][k] = INF;
        node->matrix_reduced[k][j] = INF;
    }

    node->matrix_reduced[j][0] = INF;
    node->level = level;
    node->vertex = j;
    return node;
}

void PrintPath(vector<pair<int, int>> const &list)
{
    for (int i = 0; i < list.size(); i++) {
//        qInfo() << list[i].first + 1 << "->"
//             << list[i].second + 1;
        if (final_path.isEmpty()) {
//            path.append(QString::number(list[i].first+1));
            final_path.append(QString::number(list[i].first+1));
        }
//        path.append(QString::number(list[i].second+1));
        final_path.append("->");
        final_path.append(QString::number(list[i].second+1));
    }
}

class comp {
public:
    bool operator()(const Logic* lhs, const Logic* rhs) const
    {
        return lhs->cost > rhs->cost;
    }
};

int solve(int adjacensyMatrix[N][N])
{
    priority_queue<Logic*, vector<Logic*>, comp> pq;
    vector<pair<int, int>> Pair;
    Logic* root = NewNode(adjacensyMatrix, Pair, 0, -1, 0);
    root->cost = CostCalc(root->matrix_reduced);
    pq.push(root);
    while (!pq.empty())
    {
        Logic* min = pq.top();
        pq.pop();
        int i = min->vertex;
        if (min->level == N - 1)
        {
            min->path.push_back(make_pair(i, 0));
            PrintPath(min->path);
            final_min = min->cost;
            return min->cost;
        }

        for (int j = 0; j < N; j++)
        {
            if (min->matrix_reduced[i][j] != INF)
            {
                Logic* child = NewNode(min->matrix_reduced, min->path,
                    min->level + 1, i, j);

                child->cost = min->cost + min->matrix_reduced[i][j]
                            + CostCalc(child->matrix_reduced);
                pq.push(child);
            }
        }
        delete min;
    }
}

Graphics::Graphics(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Graphics)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    draw = new MyPoint;
    ui->graphicsView->setScene(scene);

    ui->graphicsView->setScene(scene);
    scene->addItem(draw);
    ui->path->hide();

}

MyPoint::MyPoint(QObject *parent)
    : QObject(parent), QGraphicsItem()
{

}

MyPoint::~MyPoint()
{

}

QRectF MyPoint::boundingRect() const
{
    return QRectF(0,0,100,100);
}



void MyPoint::paint(QPainter *draw, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int x1 = 20, y1 = 160,
        x2 = -40, y2 = -230,
        x3 = 60, y3 = 0,
        x4 = -200, y4 = -50,
        x5 = 170, y5 = -170,
        x6 = -260, y6 = 210,
        d = 75;
    draw->setBrush(Qt::green);
    draw->setPen(Qt::black);
    draw->drawLine(x4+d/2-5, y4+d/2-5, x5+d/2-5, y5+d/2-5);
    draw->drawLine(x1+d/2-5, y1+d/2-5, x4+d/2-5, y4+d/2-5);
    draw->drawLine(x2+d/2-5, y2+d/2-5, x1+d/2-5, y1+d/2-5);
    draw->drawLine(x1+d/2-5, y1+d/2-5, x3+d/2-5, y3+d/2-5);
    draw->drawLine(x3+d/2-5, y3+d/2-5, x5+d/2-5, y5+d/2-5);
    draw->drawLine(x5+d/2-5, y5+d/2-5, x2+d/2-5, y2+d/2-5);
    draw->drawLine(x2+d/2-5, y2+d/2-5, x4+d/2-5, y4+d/2-5);
    draw->drawLine(x4+d/2-5, y4+d/2-5, x6+d/2-5, y6+d/2-5);
    draw->drawLine(x6+d/2-5, y6+d/2-5, x1+d/2-5, y1+d/2-5);
    if (was_drawn==true)  {
        draw->setPen(Qt::red);
        draw->drawLine(x1+d/2-5, y1+d/2-5, x3+d/2-5, y3+d/2-5);
        draw->drawLine(x3+d/2-5, y3+d/2-5, x5+d/2-5, y5+d/2-5);
        draw->drawLine(x5+d/2-5, y5+d/2-5, x2+d/2-5, y2+d/2-5);
        draw->drawLine(x2+d/2-5, y2+d/2-5, x4+d/2-5, y4+d/2-5);
        draw->drawLine(x4+d/2-5, y4+d/2-5, x6+d/2-5, y6+d/2-5);
        draw->drawLine(x6+d/2-5, y6+d/2-5, x1+d/2-5, y1+d/2-5);
    }
    draw->setPen(Qt::black);
    draw->drawEllipse(QRectF(x1, y1, d, d));
    draw->drawEllipse(QRectF(x2, y2, d, d));
    draw->drawEllipse(QRectF(x3, y3, d, d));
    draw->drawEllipse(QRectF(x4, y4, d, d));
    draw->drawEllipse(QRectF(x5, y5, d, d));
    draw->drawEllipse(QRectF(x6, y6, d, d));
    draw->drawText(x1+d/2-2, y1+d/2+5, "1");
    draw->drawText(x2+d/2-2, y2+d/2+5, "2");
    draw->drawText(x3+d/2-2, y3+d/2+5, "3");
    draw->drawText(x4+d/2-2, y4+d/2+5, "4");
    draw->drawText(x5+d/2-2, y5+d/2+5, "5");
    draw->drawText(x6+d/2-2, y6+d/2+5, "6");
           Q_UNUSED(option);
           Q_UNUSED(widget);
}

void Graphics::on_pushButton_clicked()
{
    solve(adjacensyMatrix);
//    qInfo() << final_min;
//    qInfo() << final_path;
    QMessageBox::information(this, "Значения", "Рассчитано с предопределёнными значениями.\n\t"
                                   "Города: " +final_path+ "\n\tМинимальная общая длина: " +QString::number(final_min), "Понял");
    ui->path->setText("Путь: " +final_path+ "\nS=" +QString::number(final_min));
    ui->path->show();
    final_path.clear();
    was_drawn = true;
}

Graphics::~Graphics()
{
    delete ui;
}
