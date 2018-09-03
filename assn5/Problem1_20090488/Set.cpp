#include "Set.h"
#include "Pairs.h"

template<class T>
Set<T>::Set(){
  this->size = 0;
  this->elements = nullptr;
}

template<class T>
Set<T>::Set(int size, T* elements){
  this->size = size;
  this->elements = new T[size];
  for(int i = 0; i<size; i++){
    this->elements[i] = elements[i];
  }
}

template<class T>
Set<T>::~Set(){
  delete[] elements;
}

template<class T>
Set<T> Set<T>::operator+(const Set& set){
  Set A(this->size, this->elements);
  Set B(set.size, set.elements);

  for(int i = 0; i<B.size; i++){
    A = A + B.elements[i];
  }

  return A;
}

template<class T>
Set<T> Set<T>::operator-(const Set& set){
  Set A(this->size, this->elements);
  Set B(set.size, set.elements);

  for (int i = 0; i<B.size; i++) {
    A = A - B.elements[i];
  }

  return A;
}

template<class T>
Set<T> Set<T>::operator*(const Set& set){
  // int new_size = this->size * set.size;
  //
  // for(int i =0; i<this->size; i++){
  //   for(int j=0; j<set.size; j++){
  //     Pair<
  //   }
  // }

}

template<class T>
Set<T>& Set<T>::operator=(const Set& set){
  this->size = set.size;
  this->elements = new T[size];

  for (int i = 0; i < this->size; i++) {
    this->elements[i] = set.elements[i];
  }

  return *this;
}

template<class T>
bool Set<T>::operator==(const Set& set){
  for (int i = 0; i < this->size; i++) {
		if (!(this->contains(set.elements[i])))
			return false;
	}
	return true;
}

template<class T>
Set<Set<T> > Set<T>::powerSet(){
  int new_size = 1;
  for(int i =0; i<this->size; i++)
    new_size *= 2;
  Set<T>* element = new Set<T>[new_size];
  Set<Set<T> > result(new_size, element);

  Set<T> empty;
  Set<T> tmp;
  result.get_elements()[0] = empty;
  int count = 1;

  if(2<=new_size){
    for(int i = 0; i<count; i++){
      for(int j= 0; j<this->size; j++){
        tmp = result.get_elements()[i]+this->elements[j];
        int check=0;
        for(int k=0; k<count; k++){
          if(result.get_elements()[k] == tmp)
            break;
          check++;
        }
        if(!(tmp == result.get_elements()[count-1]) && (check == count-1)){
          result.get_elements()[count] = tmp;
          count++;
        }
      }
    }
  }

  return result;
}

template<class T>
bool Set<T>::isSubsetOf(const Set& set){
  for (int i = 0; i < set.size; i++) {
    if (!(this->contains(set.elements[i])))
      return false;
  }
  return true;
}

template<class T>
Set<T> Set<T>::intersection(const Set& set){
  Set A(this->size, this->elements);
  int count = 0;
  int new_size = 0;
  if(this->size >= set.size)
    new_size = this->size;
  else
    new_size = set.size;

  T* tmp = new T[new_size];

  for (int i = 0; i < set.size; i++) {
    if (A.contains(set.elements[i])) {
      tmp[count] = set.elements[i];
      count++;
    }
  }

  delete[] A.elements;
  A.size = count;
  A.elements = new T[A.size];
  for (int i = 0; i < A.size; i++) {
    A.elements[i] = tmp[i];
  }

  return A;
}

template<class T>
std::ostream& operator<<(std::ostream&, const Set<T>&){

}


//check whether the specific element is excisted
template<class T>
bool Set<T>::contains(const T element){
  for(int i =0; i<this->size; i++){
    if(this->elements[i] == element)
      return true;
  }
  return false;
}

template<class T>
Set<T> Set<T>::operator+(const T element){
	Set A(this->size, this->elements);
	int new_size = A.size;
	T* new_array = nullptr;

	if (!contains(element)) {
		new_size++;
		new_array = new T[new_size];
		for (int i = 0; i < A.size; i++) {
			new_array[i] = A.elements[i];
		}

		delete[] A.elements;
		A.size = new_size;
		A.elements = new_array;
		A.elements[A.size-1] = element;
	}

  return A;
}

template<class T>
Set<T> Set<T>::operator-(const T element){
	Set A(this->size, this->elements);
	int new_size = A.size;
	T* new_array = nullptr;

	if (contains(element)) {
		new_size--;
		new_array = new T[new_size];
		int new_num = 0;
		for (int i = 0; i < A.size; i++) {
			if (!(A.elements[i] == element)) {
				new_array[new_num] = A.elements[i];
				new_num++;
			}
		}

		delete[] A.elements;
		A.size = new_size--;
		A.elements = new_array;
	}

	return A;
}

template<class T>
void Set<T>::print(){
  cout << "{";
  for(int i = 0; i<this->size-1; i++){
    cout << this->elements[i] <<", ";
  }
  cout << this->elements[this->size-1];
  cout << "}" << endl;
}
