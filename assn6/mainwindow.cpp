#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow){
    this->start=0;
    this->end=0;
    this->click=0;
    ui->setupUi(this);

    p[0].setX(300);p[0].setY(400);
    p[1].setX(100);p[1].setY(100);
    p[2].setX(700);p[2].setY(350);
    p[3].setX(280);p[3].setY(600);
    p[4].setX(100);p[4].setY(400);
    p[5].setX(500);p[5].setY(320);
    p[6].setX(250);p[6].setY(450);

    if(start == 0)
        ui->start_value->setText("none");
    if(end == 0)
        ui->end_value->setText("none");
}

MainWindow::~MainWindow(){
    delete ui;
}

//if there is no click (at the first time), just using black pen
//otherwise, use red pen for drawing the route
void MainWindow::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    QPen blackpen(Qt::black);
    blackpen.setWidth(3);
    painter.setPen(blackpen);
    for(int i =0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            if(0 < give[i][j] && give[i][j] < MAX )
                painter.drawLine(p[i], p[j]);
        }
    }

    QPen redpen(Qt::red);
    redpen.setWidth(5);

    if(click!=0){
        painter.setPen(redpen);
        for(int i = 0; i<route.size()-1; i++){
            painter.drawLine(p[route[i]], p[route[i+1]]);
        }
    }
}

//using the previous node
//backtracking to the start from the end
void MainWindow::findRoute(int prev[], QVector<int>& route, int& end){
  route.push_back(prev[end]);
  end = route.back();
}

//searching for the index which have the minimum value
int MainWindow::findShort(int basic[], bool signedSet[]){
  int idx=0;
  int min = MAX;
  for(int i =0; i<SIZE; i++){
    if(basic[i] <= min && !signedSet[i]){
      idx = i;
      min = basic[i];
    }
  }

  return idx;
}

//dijstra algorithm for finding MST
QVector<int> MainWindow::dijkstra(int graph[][SIZE], int start, int end){
  bool signedSet[SIZE]; // check whether assigned or not
  int basic[SIZE];//store the distance from the start
  int prev[SIZE];//store the rigth before node
  QVector<int> route;//will be returned with having route

//Make all the set will be empty
  for(int i = 0; i<SIZE; i++){
    signedSet[i] = false;
    basic[i] = MAX;
    prev[i] = UNFILLED;
  }

//starting node should have distance 0
  basic[start] = 0;

//Find the short distance from the start
//searching adjacent nodes and update the distance and the previous node
//keep doing until all the nodes will be updated
//And to find the route to the END node, pop out with using previous node
//and push them in the vector
  for(int row =0; row<SIZE; row++){
    int idx = findShort(basic, signedSet);
    signedSet[idx] = true;
    for(int col = 0; col<SIZE; col++){
      if (!signedSet[col] && col!=idx && basic[idx] != MAX && basic[col] > basic[idx]+graph[idx][col]){
        basic[col] = basic[idx] + graph[idx][col];
        prev[col] = idx;
      }
    }
  }

  route.push_back(end);
  while(1){
    findRoute(prev, route, end);
    if (end == UNFILLED) {
        route.pop_back();
        break;
    }
  }

  return route;
}

//using dijkstra algorithm, find the route
//and paint the edges again
void MainWindow::on_pushButton_clicked(){
    this->route = dijkstra(this->give, this->start, this->end);
    MainWindow::repaint();

}

//following click events return "START" and "END" nodes
//The first click will be "FIRST" node and the Second click will be "SECOND"
//As first click is always old, and the second is even
//so we will count click number
void MainWindow::on_p0_clicked(){
    if(click%2 == 0){
        this->start = 0;
        ui->start_value->setNum(this->start);
    }
    else{
        this->end = 0;
        ui->end_value->setNum(this->end);
    }

    this->click++;
}

void MainWindow::on_p1_clicked(){
    if(click%2 == 0){
        this->start = 1;
        ui->start_value->setNum(this->start);
    }
    else{
        this->end = 1;
        ui->end_value->setNum(this->end);
    }

    this->click++;
}

void MainWindow::on_p2_clicked(){
    if(click%2 == 0){
        this->start = 2;
        ui->start_value->setNum(this->start);
    }
    else{
        this->end = 2;
        ui->end_value->setNum(this->end);
    }

    this->click++;
}

void MainWindow::on_p3_clicked(){
    if(click%2 == 0){
        this->start = 3;
        ui->start_value->setNum(this->start);
    }
    else{
        this->end = 3;
        ui->end_value->setNum(this->end);
    }

    this->click++;
}

void MainWindow::on_p4_clicked(){
    if(click%2 == 0){
        this->start = 4;
        ui->start_value->setNum(this->start);
    }
    else{
        this->end = 4;
        ui->end_value->setNum(this->end);
    }

    this->click++;
}

void MainWindow::on_p5_clicked(){
    if(click%2 == 0){
        this->start = 5;
        ui->start_value->setNum(this->start);
    }
    else{
        this->end = 5;
        ui->end_value->setNum(this->end);
    }

    this->click++;
}

void MainWindow::on_p6_clicked(){
    if(click%2 == 0){
        this->start = 6;
        ui->start_value->setNum(this->start);
    }
    else{
        this->end = 6;
        ui->end_value->setNum(this->end);
    }

    this->click++;
}
