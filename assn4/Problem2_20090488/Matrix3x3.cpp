#include "Matrix3x3.h"

//Default constructor
//set default matrix with all elements with 0
Matrix3x3::Matrix3x3(){
  for(int i = 0; i<3; i++){
    for(int j = 0; j<3; j++){
      element[i][j] = 0;
    }
  }
}

//copy constructor
//deep copy in order to get every elements
Matrix3x3::Matrix3x3(double element[][3]){
  for(int i = 0; i<3; i++){
    for(int j = 0; j<3; j++){
      this->element[i][j] = element[i][j];
    }
  }
}

//+ operator overloading
//plus calculation of each elements
Matrix3x3 Matrix3x3::operator+(const Matrix3x3& mat){
  Matrix3x3 tmp;
  for(int i = 0; i<3; i++){
    for(int j = 0; j<3; j++){
      tmp.element[i][j] = this->element[i][j] + mat.element[i][j];
    }
  }
  return tmp;
}

//- operator overloading
//minus calculation of each elements of arrays
Matrix3x3 Matrix3x3::operator-(const Matrix3x3& mat){
  Matrix3x3 tmp;
  for(int i = 0; i<3; i++){
    for(int j = 0; j<3; j++){
      tmp.element[i][j] = this->element[i][j] - mat.element[i][j];
    }
  }
  return tmp;
}

//* operator overloading
//* calculation of each elements of arrays
Matrix3x3 Matrix3x3::operator*(const Matrix3x3& mat){
  Matrix3x3 tmp;
  for(int i = 0; i<3; i++){
    for(int j = 0; j<3; j++){
      double cal = 0;
      for(int k = 0; k<3; k++){
        cal += this->element[i][k]*mat.element[k][j];
      }
      tmp.element[i][j] = cal;
    }
  }
  return tmp;
}

//* operator overloading passing with vector object
//only extract 2X1 vector information
Vector2 Matrix3x3::operator*(const Vector2& vec){
  double x = element[0][0]*vec.get_x()+element[0][1]*vec.get_y()+element[0][2]*1;
  double y = element[1][0]*vec.get_x()+element[1][1]*vec.get_y()+element[1][2]*1;
  Vector2 tmp(x,y);
  return tmp;
}

//first set defualt matrix object named tmp
//put elements information after calcuating with double number
Matrix3x3 Matrix3x3::operator*(const double num){
  double element[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
  for(int i =0; i<3; i++){
    for(int j=0; j<3; j++){
      element[i][j] = num*this->element[i][j];
    }
  }
  Matrix3x3 tmp(element);

  return tmp;
}

Matrix3x3& Matrix3x3::operator=(const Matrix3x3& mat){
  for(int i =0; i<3; i++){
    for(int j=0; j<3; j++){
      this->element[i][j] = mat.element[i][j];
    }
  }
  return *this;
}

//with using the equation to get determinant
//be able to get inverse matrix
//if there is no inverse, print erre msg.
Matrix3x3 Matrix3x3::inverse(){
  Matrix3x3 tmp;
  double det = 0;
  det = this->element[0][0]*this->element[1][1]*this->element[2][2] - this->element[0][0]*this->element[1][2]*this->element[2][1]+ this->element[0][1]*this->element[1][2]*this->element[2][0] - this->element[0][1]*this->element[1][0]*this->element[2][2]+ this->element[0][2]*this->element[1][0]*this->element[2][1] - this->element[0][2]*this->element[1][1]*this->element[2][0];

  if(det == 0){
    std::cout << "No inverse matrix exists" << std::endl;
    return *this;
  }

  for(int i=0; i<3; i+=1) {
    for(int j=0; j<3; j+=1) {
      tmp.element[i][j]=1.0/det*(this->element[(i+1)%3][(j+1)%3]*this->element[(i+2)%3][(j+2)%3] - this->element[(i+1)%3][(j+2)%3]*this->element[(i+2)%3][(j+1)%3]);
    }
  }
  return tmp;
}

//string elements information
std::string Matrix3x3::toString(){
  std::string middle = "";
  for(int i =0; i<3; i++){
    for(int j=0; j<3; j++){
      if(j==2)
        middle += std::to_string(element[i][j])+"; ";
      else
        middle += std::to_string(element[i][j])+", ";
    }
  }
  std::string tmp = "[" + middle + "]";

  return tmp;
}

//top level funtion of operator overloading
Matrix3x3 operator*(double num, const Matrix3x3& mat){
  Matrix3x3 tmp;
  for(int i = 0; i<3; i++){
    for(int j =0; j<3; j++){
      tmp.element[i][j] = mat.element[i][j]*num;
    }
  }
  return tmp;
}

//return simple identity array
Matrix3x3 Matrix3x3::identity(){
  double element[3][3] = {{1,0,0}, {0,1,0}, {0,0,1}};
  Matrix3x3 tmp(element);
  return tmp;
}

//return the matrix for trnaslate
Matrix3x3 Matrix3x3::translate(double x, double y){
  double element[3][3] = {{1,0,x}, {0,1,y}, {0,0,1}};
  Matrix3x3 tmp(element);
  return tmp;
}

//return the matrix for rotating
Matrix3x3 Matrix3x3::rotate(double theta){
  double element[3][3] = {{cos(theta * PI / 180.0),-sin(theta * PI / 180.0),0}, {sin(theta * PI / 180.0),cos(theta * PI / 180.0),0}, {0,0,1}};
  Matrix3x3 tmp(element);
  return tmp;
}

//return the matrix for scaling
Matrix3x3 Matrix3x3::scale(double sx, double sy){
  double element[3][3] = {{sx,0,0}, {0,sy,0}, {0,0,1}};
  Matrix3x3 tmp(element);
  return tmp;
}
