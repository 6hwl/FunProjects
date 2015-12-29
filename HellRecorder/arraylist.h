#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdexcept>


template <class T>
class ArrayList
{
 public:
  /**
   * Default constructor - default to a list of capacity = 5
   */
  ArrayList();

  /**
   * Another constructor - default to a list to the indicated capacity
   */
  ArrayList(int cap);

  /**
   * Copy constructor 
   */
  ArrayList(const ArrayList& other);

  /**
   * Assignment operator
   */
  ArrayList& operator=(const ArrayList& other);

  /**
   * Destructor
   */
  ~ArrayList();
  
  /**
   * Standard List interface
   */

  /**
   * Returns the current number of items in the list 
   */
  int size() const;
  
  /**
   * Returns true if the list is empty, false otherwise
   */
  bool empty() const;

  /**
   * Inserts val so it appears at index, pos. Does nothing if invalid index
   */
  void insert (int pos, const T& val);

  /**
   * Removes the value at index, pos
   */
  void remove (int pos);

  /**
   * Overwrites the old value at index, pos, with val
   */
  void set (int position, const T& val);

  /**
   * Returns the value at index, pos
   */
  T& get (int position) ;

  /**
   * Returns the value at index, pos
   */
  T const & get (int position) const;

  /**
   * Produce a new list by concatenating this list and the input list
   *   If this list = [1, 2, 3] and other = [4, 5, 6] then return 
   *   a new list with contents [1, 2, 3, 4, 5, 6].  The capacity
   *   of the new list should be equal to its size (i.e. the new list
   *   would be full upon being returned)
   */
  ArrayList operator+(const ArrayList& other) const;
  
  /**
   * Operator[] to access the element at the given position
   */
  T const & operator[](int position) const;

  /**
   * Non-const version
   */
  T& operator[](int position);


 private:
  /**
   * Should double the size of the list maintaining its contents
   */
  void resize(); 
   
  /* Add necessary data members here */
  T* _data;
  unsigned int _size;
  unsigned int _cap;
  
};


template <class T>
ArrayList<T>::ArrayList() {
  _data = new T[5];
  _size = 0;
  _cap = 5;

}

template <class T>
ArrayList<T>::ArrayList(int cap) {
  if (cap < 0) _cap = 5;
  else _cap = cap;
  _data = new T[cap];
  _size = 0;

}

template <class T>
ArrayList<T>::ArrayList(const ArrayList& other) {
  int length = other.size();
  _data = new T[length];
  _cap = other._cap;
  _size = other._size;
  for (int i = 0; i < length; i++) {
    _data[i] = other[i];
  }
}

template <class T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList& other) {
  if (this == &other) return *this;
  _size = other.size();
  _cap = other._cap;
  delete[] _data;
  _data = new T[_size];
  for (unsigned int i = 0; i < _size; i++) {
    _data[i] = other.get(i);
  }
  return *this;
}

template <class T>
ArrayList<T>::~ArrayList() {
  delete[] _data;
}

template <class T>
int ArrayList<T>::size() const {
  return _size;
}

template <class T>
bool ArrayList<T>::empty() const {
  if (_size == 0) return true;
  else return false;
}

template <class T>
void ArrayList<T>::insert (int pos, const T& val) {
  unsigned int newpos = pos;
  if (!(newpos < 0 || newpos > _size)) {
    if (_size == _cap) resize();
    for (unsigned int i = _size; i > newpos; i--) {
      _data[i] = _data[i - 1];
    }
    _data[newpos] = val;
    _size = _size + 1;
  }
}

template <class T>
void ArrayList<T>::remove (int pos) {
  unsigned int newpos = pos;
  if (!(newpos < 0 || newpos >= _size)) {
    for (unsigned int i = pos; i < _size - 1; i++) {
      _data[i] = _data[i + 1];
    }
    _size = _size - 1;
  }
}

template <class T>
void ArrayList<T>::set (int position, const T& val) {
  unsigned int newpos  = position;
  if (!(newpos < 0 || newpos >= _size)) {
    _data[position] = val;
  }
}

template <class T>
T& ArrayList<T>::get (int position) {
  unsigned int newpos = position;
  if ((newpos < 0 || newpos >= _size)) {
    throw std::range_error("Position is out of bounds");
  } else {
    return _data[position];
  }
}

template <class T>
T const & ArrayList<T>::get (int position) const {
  unsigned int newpos = position;
  if ((newpos < 0 || newpos >= _size)) {
    throw std::range_error("Position is out of bounds");
  } else {
    return _data[position];
  }
}

template <class T>
ArrayList<T> ArrayList<T>::operator+(const ArrayList& other) const {
  // size (no underscore) represents the new (and probably larger) size
  int size = _size + other.size();
  ArrayList newlist;
  for (unsigned int i = 0; i < _size; i++) {
    newlist.insert(i, this->get(i));
  }
  for (int i = _size; i < size; i++) {
    newlist.insert(i, other.get(i - _size));
  }
  return newlist;

}

template <class T>
T const & ArrayList<T>::operator[](int position) const {
  return this->get(position);
}

template <class T>
T& ArrayList<T>::operator[](int position) {
  return this->get(position);
}

template <class T>
void ArrayList<T>::resize() {
  int size = _size * 2;
  T* data_copy = new T[size];
  for (unsigned int i = 0; i < _size; i++) {
    data_copy[i] = _data[i];
  }
  delete[] _data;
  _data = data_copy;
  _cap = size;
}




#endif
