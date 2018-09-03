#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    QFile infile("./polygon.txt");
    if(!infile.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", infile.errorString());
    }

    QTextStream in(&infile);
    QString line = in.readLine();
    int op = line.toInt();
   while (!in.atEnd()){
       for(int i = 0; i<op; i++){
        line = in.readLine();
        int num;num = line.toInt();
        vector<Point<int> >tmp;
        line = in.readLine();
        QStringList list = line.split(' ');
        for (QStringList::Iterator S =  list.begin(); S != list.end(); S++){
            int x, y;
            QString a, b;
            a = *S;
            x = a.toInt();
            ++S;
            b = *S;
            y = b.toInt();
            Point<int> p(x,y);
            tmp.push_back(p);
        }
        Polygon<int> pp(num, tmp);
        this->poly.push_back(pp);
       }
   }

   infile.close();

   for(int i = 0; i<ROW; i++){
        for(int j = 0; j<ROW; j++){
          this->graph[i][j] = 1;
        }
      }

  for(int i = 10; i<ROW-10; i++){
    for(int j = 10; j<COL-10; j++){
      Point<int> a(i, j-10);
      Point<int> b(i+7, j-7); Point<int> c(i+10, j); Point<int> d(i+7, j+7); Point<int> e(i, j+10); Point<int> f(i-7, j+7); Point<int> g(i-10, j); Point<int> h(i-7, j-7);
      vector<Point<int> > temp;
      temp.push_back(a);temp.push_back(b);temp.push_back(c);temp.push_back(d);temp.push_back(e);temp.push_back(f);temp.push_back(g);temp.push_back(h);
      Polygon<int> comp(8, temp);

      for(int k = 0; k<2; k++){
        Polygon<int> _pl = poly[k] - comp;
        Polygon<int> _ch = _pl.convexHull();
        if (_ch.IsCollide()) {
          this->graph[i][j] = 0;
        }
      }
    }
  }



   /*for(int i = 0; i<poly.size(); i++){
     qDebug() << poly.size();
     qDebug() << poly[i].vertices.size();
     for(int j= 0; j<poly[i].vertices.size(); j++){
       qDebug() << "'" <<poly[i].vertices[j].x <<"'" << "," << poly[i].vertices[j].y;
     }
   }*/


}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    QString x = QString::number(event->x());
    QString y = QString::number(event->y());

    if(click%2 == 0){
        this->src.first = x.toInt();
        this->src.second = y.toInt();
        ui->scr_x->setNum(this->src.first);
        ui->src_y->setNum(this->src.second);
    }
    else{
        this->dest.first = x.toInt();
        this->dest.second = y.toInt();
        ui->dest_x->setNum(this->dest.first);
        ui->dest_y->setNum(this->dest.second);
    }

    this->click++;
    MainWindow::repaint();

}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if( (event->key() == Qt::Key_Enter) ||(event->key() == Qt::Key_Return)){
        qDebug() << "Enter!";
        //findPath(graph, src, dest, new_map, openList);
    }

    else
        qDebug() << "Wrong Button!";
}

void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    int x=src.first;
    int y = src.second;
    int _x = dest.first;
    int _y = dest.second;

    QPolygon(poly_src);
    poly_src << QPoint(x, y-10) << QPoint(x+7, y-7) << QPoint(x+10, y) << QPoint(x+7, y+7)
         << QPoint(x, y+10) << QPoint(x-7, y+7) << QPoint(x-10, y) << QPoint(x-7, y-7);

    QPolygon(poly_dest);
    poly_dest << QPoint(_x, _y-10) << QPoint(_x+7, _y-7) << QPoint(_x+10, _y) << QPoint(_x+7, _y+7)
         << QPoint(_x, _y+10) << QPoint(_x-7, _y+7) << QPoint(_x-10, _y) << QPoint(_x-7, _y-7);

    QPen blackpen;
    blackpen.setWidth(2);
    blackpen.setColor(Qt::black);
    painter.setPen(blackpen);
    painter.drawPolygon(poly_src);

    QPen redpen;
    redpen.setWidth(2);
    redpen.setColor(Qt::red);
    painter.setPen(redpen);
    painter.drawPolygon(poly_dest);
}



// A Utility Function to check whether given cell (row, col)
// is a valid cell or not.
bool MainWindow::isValid(int row, int col)
{
        // Returns true if row number and column number
        // is in range
        return (row >= 10) && (row < ROW-10) &&
                (col >= 10) && (col < COL-10);
}

// A Utility Function to check whether the given cell is
// blocked or not
bool MainWindow::isUnBlocked(int grid[][COL], int row, int col)
{
        // Returns true if the cell is not blocked else false
        if (grid[row][col] == 1)
                return (true);
        else
                return (false);
}

// A Utility Function to check whether destination cell has
// been reached or not
bool MainWindow::isDestination(int row, int col, Pair dest)
{
        if (row == dest.first && col == dest.second)
                return (true);
        else
                return (false);
}

// A Utility Function to calculate the 'h' heuristics.
double MainWindow::calculateHValue(int row, int col, Pair dest)
{
        // Return using the distance formula
        return ((double)sqrt ((row-dest.first)*(row-dest.first)
                                                + (col-dest.second)*(col-dest.second)));
}

void MainWindow::findPath(int grid[][200], Pair src, Pair dest, cell new_map[][200], set<pPair> &openList){
  // If the source is out of range
  if (isValid (src.first, src.second) == false)
  {
    printf ("Source is invalid\n");
    return;
  }

  // If the destination is out of range
  if (isValid (dest.first, dest.second) == false)
  {
    printf ("Destination is invalid\n");
    return;
  }

  // Either the source or the destination is blocked
  if (isUnBlocked(grid, src.first, src.second) == false ||
      isUnBlocked(grid, dest.first, dest.second) == false)
  {
    printf ("Source or the destination is blocked\n");
    return;
  }

  // If the destination cell is the same as source cell
  if (isDestination(src.first, src.second, dest) == true)
  {
    printf ("We are already at the destination\n");
    return;
  }

  // Create a closed list and initialise it to false which means
  // that no cell has been included yet
  // This closed list is implemented as a boolean 2D array
  bool closedList[ROW][COL];
  memset(closedList, false, sizeof (closedList));

  // Declare a 2D array of structure to hold the details of that cell
        int i, j;

        for (i=0; i<ROW; i++)
        {
                for (j=0; j<COL; j++)
                {
                        new_map[i][j].f = FLT_MAX;
                        new_map[i][j].g = FLT_MAX;
                        new_map[i][j].h = FLT_MAX;
                        new_map[i][j].parent_i = -1;
                        new_map[i][j].parent_j = -1;
                }
        }

        // Initialising the parameters of the starting node
        i = src.first, j = src.second;
        new_map[i][j].f = 0.0;
        new_map[i][j].g = 0.0;
        new_map[i][j].h = 0.0;
        new_map[i][j].parent_i = i;
        new_map[i][j].parent_j = j;

  // Put the starting cell on the open list and set its
        // 'f' as 0
        openList.insert(make_pair (0.0, make_pair (i, j)));

  // We set this boolean value as false as initially
        // the destination is not reached.
        bool foundDest = false;

        while (!openList.empty())
        {
                pPair p = *openList.begin();

                // Remove this vertex from the open list
                openList.erase(openList.begin());

                // Add this vertex to the closed list
                i = p.second.first;
                j = p.second.second;
                closedList[i][j] = true;

    // To store the 'g', 'h' and 'f' of 4 directions
                double gNew, hNew, fNew;

    for(int target = NORTH; target<=WEST; target++){
      switch (target) {
        case NORTH:{
          if (isValid(i-1, j) == true)
          {
            // If the destination cell is the same as the current successor
            if (isDestination(i-1, j, dest) == true)
            {
              // Set the Parent of the destination cell
              new_map[i-1][j].parent_i = i;
              new_map[i-1][j].parent_j = j;
              printf ("The destination cell is found\n");
              foundDest = true;
              return;
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i-1][j] == false &&
              isUnBlocked(grid, i-1, j) == true){
              gNew = new_map[i][j].g + 1.0;
              openList.insert( make_pair(FLT_MAX, make_pair(i-1, j)));

              // The distance from start to a neighbor
              if(gNew>=new_map[i-1][j].g)
                break;// This is not a better path.

              // This path is the best until now. Record it!
              // Update the details of this cell
              hNew = calculateHValue (i-1, j, dest);
              fNew = gNew + hNew;

              new_map[i-1][j].f = fNew;
              new_map[i-1][j].g = gNew;
              new_map[i-1][j].h = hNew;
              new_map[i-1][j].parent_i = i;
              new_map[i-1][j].parent_j = j;
      /*
      If it isn’t on the open list, add it to
      // the open list. Make the current square
      // the parent of this square. Record the
      // f, g, and h costs of the square cell
      //			 OR
      // If it is on the open list already, check
      // to see if this path to that square is better,
      // using 'f' cost as the measure.
      if (new_map[i-1][j].f == FLT_MAX ||
          new_map[i-1][j].f > fNew)
      {
        openList.insert( make_pair(fNew,
                    make_pair(i-1, j)));

        // Update the details of this cell
        new_map[i-1][j].f = fNew;
        new_map[i-1][j].g = gNew;
        new_map[i-1][j].h = hNew;
        new_map[i-1][j].parent_i = i;
        new_map[i-1][j].parent_j = j;
      }
      */
            }
          }
          break;
        }//end NORTH

        case EAST:{
          if (isValid(i, j+1) == true)
          {
            // If the destination cell is the same as the current successor
            if (isDestination(i, j+1, dest) == true)
            {
              // Set the Parent of the destination cell
              new_map[i][j+1].parent_i = i;
              new_map[i][j+1].parent_j = j;
              printf ("The destination cell is found\n");
              foundDest = true;
              return;
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i][j+1] == false &&
              isUnBlocked(grid, i, j+1) == true){
              gNew = new_map[i][j].g + 1.0;
              openList.insert( make_pair(FLT_MAX, make_pair(i, j+1)));

              // The distance from start to a neighbor
              if(gNew>=new_map[i][j+1].g)
                break;// This is not a better path.

              // This path is the best until now. Record it!
              // Update the details of this cell
              hNew = calculateHValue (i, j+1, dest);
              fNew = gNew + hNew;

              new_map[i][j+1].f = fNew;
              new_map[i][j+1].g = gNew;
              new_map[i][j+1].h = hNew;
              new_map[i][j+1].parent_i = i;
              new_map[i][j+1].parent_j = j;
            }
          }
          break;
        }//end EAST

        case SOUTH:{
          if (isValid(i+1, j) == true)
          {
            // If the destination cell is the same as the current successor
            if (isDestination(i+1, j, dest) == true)
            {
              // Set the Parent of the destination cell
              new_map[i+1][j].parent_i = i;
              new_map[i+1][j].parent_j = j;
              printf ("The destination cell is found\n");
              foundDest = true;
              return;
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i+1][j] == false &&
              isUnBlocked(grid, i+1, j) == true){
              gNew = new_map[i][j].g + 1.0;
              openList.insert( make_pair(FLT_MAX, make_pair(i+1, j)));

              // The distance from start to a neighbor
              if(gNew>=new_map[i+1][j].g)
                break;// This is not a better path.

              // This path is the best until now. Record it!
              // Update the details of this cell
              hNew = calculateHValue (i+1, j, dest);
              fNew = gNew + hNew;

              new_map[i+1][j].f = fNew;
              new_map[i+1][j].g = gNew;
              new_map[i+1][j].h = hNew;
              new_map[i+1][j].parent_i = i;
              new_map[i+1][j].parent_j = j;
            }
          }
          break;
        }//end SOUTH

        case WEST:{
          if (isValid(i, j-1) == true)
          {
            // If the destination cell is the same as the current successor
            if (isDestination(i, j-1, dest) == true)
            {
              // Set the Parent of the destination cell
              new_map[i][j-1].parent_i = i;
              new_map[i][j-1].parent_j = j;
              printf ("The destination cell is found\n");
              foundDest = true;
              return;
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i][j-1] == false &&
              isUnBlocked(grid, i, j-1) == true){
              gNew = new_map[i][j].g + 1.0;
              openList.insert( make_pair(FLT_MAX, make_pair(i, j-1)));

              // The distance from start to a neighbor
              if(gNew>=new_map[i][j-1].g)
                break;// This is not a better path.

              // This path is the best until now. Record it!
              // Update the details of this cell
              hNew = calculateHValue (i, j-1, dest);
              fNew = gNew + hNew;

              new_map[i][j-1].f = fNew;
              new_map[i][j-1].g = gNew;
              new_map[i][j-1].h = hNew;
              new_map[i][j-1].parent_i = i;
              new_map[i][j-1].parent_j = j;
            }
          }
          break;
        }//end WEST

      }//end switch
    }//end for loop
  }//end while loop
}
