#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QPolygon>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QMessageBox>
#include <set>
#include <cfloat>
#include <iostream>
#include "polygon.h"

#define ROW 200
#define COL 200

namespace Ui {
class MainWindow;
}

using namespace std;

// Creating a shortcut for int, int pair type
typedef pair<int, int> Pair;

// Creating a shortcut for pair<int, pair<int, int>> type
typedef pair<double, pair<int, int> > pPair;

// A structure to hold the neccesary parameters
struct cell{
        // Row and Column index of its parent
        // Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
        int parent_i, parent_j;
        // f = g + h
        double f, g, h;
};

enum dir { NORTH = 0, EAST, SOUTH, WEST };

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);

    bool isValid(int row, int col);
    bool isUnBlocked(int grid[][COL], int row, int col);
    bool isDestination(int row, int col, Pair dest);
    double calculateHValue(int row, int col, Pair dest);
    void findPath(int grid[][200], Pair src, Pair dest, cell new_map[][200], set<pPair> &openList);

private:
    Ui::MainWindow *ui;
    Pair src;
    Pair dest;
    int click;
    vector<Polygon<int> > poly;
    int graph[ROW][COL];
    /*Create an open list having information as-<f, <i, j>> where f = g + h,
    and i, j are the row and column index of that cell*/
    set<pPair> openList;
    // Declare a 2D array of structure to hold the details of that cell
    cell new_map[ROW][COL];
};

#endif // MAINWINDOW_H
