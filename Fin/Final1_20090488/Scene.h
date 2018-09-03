#ifndef _SCENE_H_
#define _SCENE_H_

#include "Polygon.h"

template <typename T>
class Scene {
public:
	vector<T> ary;
	Scene() { vector<T> ary; }
	inline Scene(T poly){this->ary.push_back(poly);}
	~Scene(){};
};

#endif
