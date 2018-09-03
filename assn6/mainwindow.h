#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QString>
#include <QVector>

#define SIZE (7)
#define MAX (999999)
#define UNFILLED (88888)

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QVector<int> dijkstra(int graph[][7], int start, int end);
    int findShort(int ary[], bool a[]);
    void findRoute(int prev[], QVector<int>& route, int& end);

protected:
    virtual void paintEvent(QPaintEvent *e);
//    virtual void mousePressEvent(QMouseEvent *e);

private slots:
    void on_p0_clicked();
    void on_p1_clicked();
    void on_p2_clicked();
    void on_p3_clicked();
    void on_p4_clicked();
    void on_p5_clicked();
    void on_p6_clicked();



    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QPoint p[7];
    int start;
    int end;
    int click;
    QVector<int> route;

    int give[SIZE][SIZE]={
      {0,3,MAX,MAX,MAX,4,3},
      {3,0,7,MAX,10,4,MAX},
      {MAX,7,0,15,MAX,2,MAX},
      {MAX,MAX,15,0,8,MAX,3},
      {MAX,10,MAX,8,0,MAX,3},
      {4,4,2,MAX,MAX,0,MAX},
      {3,MAX,MAX,3,3,MAX,0}
    };

};

#endif // MAINWINDOW_H
