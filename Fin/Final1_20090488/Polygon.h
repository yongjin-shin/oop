#ifndef _POLYGON_H_
#define _POLYGON_H_
#include "Point.h"
#include <math.h>


template<class T>
class Polygon{

private:
  int num;
  Point<T> p0;
  vector<Point<T> > vertices;

public:
  Polygon(){num=0;}
  Polygon(int num, vector<Point<T> > p);
  ~Polygon() {}
  Polygon operator+(Polygon poly);
  Polygon operator-(Polygon poly);
  Polygon& operator=(Polygon poly);
  void add(Point<T> poly);
  /*friend ostream& operator<<(ostream& out, Polygon<T>& poly) {
    out << "{";
    for(typename vector<Point<T> >::iterator it = poly.vertices.begin(); it<poly.vertices.end(); it++){
      out << *it;
    }
    out << "}";
    return out;
  }*/
  Polygon convexHull();
  void swap(Point<T> &p1, Point<T> &p2);
  int orientation(Point<T> p, Point<T> q, Point<T> r);
  int compare(const Point<T> p1, const Point<T> p2);
  double distSq(Point<T> p1, Point<T> p2);
  Point<T> underTop(stack<Point<T> > &S);

  bool IsCollide();
  double distance(const Polygon<T> poly);
};

template<class T>
Polygon<T>::Polygon(int num, vector<Point<T> > vertices){
  this->num = num;
  for(typename vector<Point<T> >::iterator it = vertices.begin(); it<vertices.end(); it++)
    this->vertices.push_back(*it);
}

template<class T>
void Polygon<T>::add(Point<T> p){
  num++;
  vertices.push_back(p);
}

template<class T>
Polygon<T> Polygon<T>::operator+(Polygon<T> poly){
  int num=0;
  vector<Point<T> > tmp;
  for(typename vector<Point<T> >::iterator it = this->vertices.begin(); it<this->vertices.end(); it++){
    for(typename vector<Point<T> >::iterator that = poly.vertices.begin(); that<poly.vertices.end(); that++){
      tmp.push_back(*it + *that);
      num++;
    }
  }
  Polygon result(num, tmp);
  return result;
}

template<class T>
Polygon<T> Polygon<T>::operator-(Polygon<T> poly){
  int num=0;
  vector<Point<T> > tmp;
  for(typename vector<Point<T> >::iterator it = this->vertices.begin(); it<this->vertices.end(); it++){
    for(typename vector<Point<T> >::iterator that = poly.vertices.begin(); that<poly.vertices.end(); that++){
      tmp.push_back(*it - *that);
      num++;
    }
  }
  Polygon result(num, tmp);
  return result;
}


template<class T>
Polygon<T>& Polygon<T>::operator=(Polygon<T> poly){
   this->num = poly.num;
   for(typename vector<Point<T> >::iterator it = poly.vertices.begin(); it<poly.vertices.end(); it++)
     this->vertices.push_back(*it);

  return *this;
}

template<class T>
void Polygon<T>::swap(Point<T>& p1, Point<T>& p2){
  Point<T> tmp = p1;
  p1 = p2;
  p2 = tmp;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
template<class T>
int Polygon<T>::orientation(Point<T> p, Point<T> q, Point<T> r){
  int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
  if(val == 0) return 0;//colinear
  return (val>0)?1:2;//clock or counterclockwise
}


// A function to return square of distance
// between p1 and p2
template<class T>
double Polygon<T>::distSq(Point<T> p1, Point<T> p2){
	return (p1.x - p2.x)*(p1.x - p2.x) +
		(p1.y - p2.y)*(p1.y - p2.y);
}

// A function will be used to sort an array of
// points with respect to the first point
template<class T>
int Polygon<T>::compare(const Point<T> p1, const Point<T> p2){
// Find orientation
  int o = orientation(p0, p1, p2);
  if (o == 0)
	 return (distSq(p0, p2) >= distSq(p0, p1))? -1 : 1;

  return (o == 2)? -1: 1;
}

//find the element right under the top
template<class T>
Point<T> Polygon<T>::underTop(stack<Point<T> > &S){
	Point<T> p = S.top();
	S.pop();
	Point<T> res = S.top();
	S.push(p);
	return res;
}

//find the convex Hull with given a set of points
template<class T>
Polygon<T> Polygon<T>::convexHull() {
  // Find the bottommost point
  int ymin = vertices[0].y, min = 0;
  for (int i = 1; i < num; i++){
  	int y = vertices[i].y;

  	// Pick the bottom-most or choose the left
  	// most point in case of tie
  	if ((y < ymin) || (ymin == y && vertices[i].x < vertices[min].x))
  		ymin = vertices[i].y, min = i;
  }

  // Place the bottom-most point at first position
  swap(vertices[0], vertices[min]);

  // Sort n-1 points with respect to the first point.
  // A point p1 comes before p2 in sorted ouput if p2
  // has larger polar angle (in counterclockwise direction) than p1
  this->p0 = vertices[0];
  for(int j =1; j<num;j++){
    for(int i = num-2; j<=i; i--){
      if(0<compare(vertices[i], vertices[i+1])){
        swap(vertices[i], vertices[i+1]);
      }
    }
  }

  // If two or more points make same angle with p0,
  // Remove all but the one that is farthest from p0
  int m = 1; // Initialize size of modified array
  for (int i=1; i<num; i++){
  	// Keep removing i while angle of i and i+1 is same
  	// with respect to p0
  	while (i < num-1 &&
      orientation(p0, vertices[i], vertices[i+1]) == 0)
  		i++;

  	vertices[m] = vertices[i];
  	m++; // Update size of modified array
  }

   // If modified array of points has less than 3 points,
   // convex hull is not possible
   //if (m < 3)
   //  return;

  // Create an empty stack and push first three points
  // to it.
  stack<Point<T> > S;
  S.push(vertices[0]);
  S.push(vertices[1]);
  S.push(vertices[2]);

  // Process remaining n-3 points
  for (int i = 3; i < m; i++){
  	// Keep removing top while the angle formed by
  	// points next-to-top, top, and points[i] makes
  	// a non-left turn
  	while (orientation(underTop(S), S.top(), vertices[i]) != 2)
  		S.pop();
  	S.push(vertices[i]);
  }

  // Now stack has the output points,
  // copy contents of stack into new Polygon
  Polygon<T> final;
  while (!S.empty()){
  	final.vertices.push_back(S.top());
  	S.pop();
    final.num++;
  }
  return final;
}

//if (0,0) is inside the convex Hull
//the number of intersection is odd number
//otherwise it is even number
template<class T>
bool Polygon<T>::IsCollide(){
	int check = 0;

	//if convexhull contains (zero,zero)
	for (int i = 0; i < num; i++) {
		if (0 == vertices[i].x && 0 == vertices[i].y)
			return true;
	}

  for(int i = 0 ; i < num ; i++){
    int j = (i+1)%num;
    //if (0,0) is insdide the line
    //from ith vertices to jth vertices
    if((vertices[i].y > 0) != (vertices[j].y > 0) ){
      //inter is the intersection  between
      //horizontal line through B and the line from i to j
      double inter = (vertices[j].x- vertices[i].x)*(vertices[j].y-vertices[i].y)/(vertices[j].y-vertices[i].y)+vertices[i].x;
      //if there is a intersection, add up the number
      if(0 < inter)
        check++;
    }
  }
  return check % 2 > 0;
}

template<class T>
double Polygon<T>::distance(const Polygon<T> poly) {
	Polygon<T> tmp = *this - poly;
	Point<T> zero;
	double min=distSq(zero, tmp.vertices[0]);
	//compare each point of distance
	//return only the minum value
	for (int i = 1; i<tmp.vertices.size(); i++) {
		if (min >= distSq(zero, tmp.vertices[i]))
			min = distSq(zero, tmp.vertices[i]);
	}
	min = sqrt(min);
	return min;
}

#endif
