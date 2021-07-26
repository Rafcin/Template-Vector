#pragma once
#include "Iterator/iterator.h"
#include "Iterator/reverse.h"
#include <cstddef>
#include <iterator>
#include <stdexcept>

/*
 * [Vector Class] By Raf.
 * This is as close as I can get to the STL Vector.
 * @todo Add exceptions & safeguards to prevent stupidity
 * For reference this was a good paper on fast dynamic arrays.
 * https://drops.dagstuhl.de/opus/volltexte/2017/7830/pdf/LIPIcs-ESA-2017-16.pdf
 * Extra:
 * https://medium.com/@vgasparyan1995/how-to-write-an-stl-compatible-container-fc5b994462c6
 * https://www.reddit.com/r/cpp/comments/9nz3xl/example_of_stl_compatible_custom_containers/
 * This is funny, EA (Electronic Arts) of all people made a good library called
 * EASTL. It's readable but like why EA. Of all the companies in the world, the
 * one who literally hates it's community wrote something nice.
 */

template <typename T> class Vector {
private:
  // Had to rename, because of size functions
  std::size_t _size;
  std::size_t _capacity;
  T *_values;
  // I need a break I keep seeing blue spots. Fix commit when finished.
public:
  /**
   * [Constructors]
   */
  // Default
  Vector();
  // By size
  explicit Vector(int size);
  // Copy
  Vector(const Vector &v);
  // Copy Assignment
  Vector<T> &operator=(const Vector<T> &v);
  // Destruction
  ~Vector();

  /**
   * [Mutations]
   */
  // https://www.cplusplus.com/reference/vector/vector/
  // void push_back (const value_type& val);
  void push_back(const T &val);
  void pop_back();
  void clear();

  /**
   * [Accessors]
   */
  // https://www.cplusplus.com/reference/vector/vector/at/
  T &at(int i);
  const T &at(int i) const;
  // Holy shit I love GPT-3
  T &operator[](int i);
  const T &operator[](int i) const;
  // https://www.cplusplus.com/reference/vector/vector/front/
  T &front();
  const T &front() const;

  // https://www.cplusplus.com/reference/vector/vector/back/
  T &back();
  const T &back() const;

  // https://www.cplusplus.com/reference/vector/vector/data/
  // o_o cplusplus.com: Returns a direct pointer to the memory array used
  // internally by the vector to store its owned elements. - Fuck yeah
  /*
   *[std::vector::data]
   *value_type* data() noexcept;
   *const value_type* data() const noexcept;
   */
  const T *data();
  const T *data() const;

  /**
   * [Size]
   */
  // https://www.cplusplus.com/reference/vector/vector/capacity/
  // Why cant't I fucking use the word capacity here.
  std::size_t capacity() const;

  // https://www.cplusplus.com/reference/vector/vector/reserve/
  void reserve(size_t n);

  // https://www.cplusplus.com/reference/vector/vector/resize/
  // void resize (size_type n, value_type val = value_type()); c++98
  // void resize (size_type n); c++11
  // void resize (size_type n, const value_type& val); c++11
  void resize(int size, T val = T()); // c++98

  // https://www.cplusplus.com/reference/vector/vector/max_size/
  // size_type max_size() const noexcept; c++11;
  std::size_t max_size();

  // https://www.cplusplus.com/reference/vector/vector/size/
  // size_type size() const noexcept; c++11
  size_t size() const;

  // https://www.cplusplus.com/reference/vector/vector/shrink_to_fit/
  // void shrink_to_fit(); All Versions
  void shrink_to_fit();

  // https://www.cplusplus.com/reference/vector/vector/empty/
  // bool empty() const noexcept;
  bool empty() const;

  /**
   * [Iterator]
   */
  // I love this iterator so much im shaking in my boots.
  typedef iterator<T> it;
  typedef iterator<const T> cit;
  typedef reverse<T> rit;
  typedef reverse<const T> crit;
  // hahah it cit rit crit

  /**
   * @brief Iterator begin() gets start of vector.
   * @return
   */
  it begin() { return it(&_values[0]); }
  /**
   * @brief Iterator end() gets end of vector.
   * @return
   */
  it end() { return it(&_values[_size]); }

  /**
   * @brief Iterator const cbegin() gets start of vector.
   * @return
   */
  cit cbegin() { return cit(&_values[0]); }

  /**
   * @brief Iterator const cend() gets end of vector.
   * @return
   */
  cit cend() { return cit(&_values[_size]); }

  /**
   * @brief Reverse Iterator rbegin() gets start of vector.
   * @return
   */
  rit rbegin() { return rit(&_values[_size - 1]); }

  /**
   * @brief Reverse Iterator rend() gets ends of vector.
   * @return
   */
  rit rend() { return rit(&_values[-1]); }

  /**
   * @brief Reverse Iterator const crbegin() gets start of vector.
   * @return
   */
  crit crbegin() { return crit(&_values[_size - 1]); }

  /**
   * @brief Reverse Iterator const crend() gets end of vector.
   * @return
   */
  crit crend() { return crit(&_values[-1]); }
};

/**
 * @brief Basic Vector<T> constructor.
 * @tparam T
 */
template <typename T>
Vector<T>::Vector() : _size(0), _capacity(0), _values(0) {}

// Yeah I inline my functions. Performance go brrrr.
/**
 * @brief Vector constructor with size
 * @tparam T
 * @param size
 */
template <typename T>
Vector<T>::Vector(int size)
    : _size(size), _capacity(size), _values(new T[size]) {
  for (std::size_t i = 0; i < _size; i++) {
    _values[i] = T();
  }
}

/**
 * @brief Copy constructor Vector<T>
 * @tparam T
 * @param v
 */
template <typename T>
Vector<T>::Vector(const Vector &v)
    : _size(v._size), _capacity(v._capacity), _values(new T[v._size]) {
  for (std::size_t i = 0; i < v._size; i++) {
    _values[i] = v._values[i];
  }
}

// I hate this one
/**
 * @brief Copy assignment Vector<T>
 * @tparam T
 * @param v
 * @return
 */
template <typename T> Vector<T> &Vector<T>::operator=(const Vector<T> &v) {
  if (this == &v)
    return *this;
  if (v._size <= _capacity) {
    for (std::size_t i = 0; i < v._size; i++) {
      _values[i] = v._values[i];
      _size = v._size;
      return *this;
    }
  }
  T *p = new T[v._size];
  //... ++ the fucking plus plus killed me for days...
  for (std::size_t i = 0; i < v._size; ++i) {
    p[i] = v._values[i];
  }
  // Delete
  delete[] _values;
  _size = v._size;
  _capacity = v._capacity;
  _values = p;
  return *this;
}

/**
 * @brief Destructor for Vector<T>
 * @tparam T
 */
template <typename T> Vector<T>::~Vector() { delete[] _values; }

/**
 * @brief Reserves space vector to contain at least n elements.
 * @tparam T
 * @param n
 */
template <typename T> void Vector<T>::reserve(size_t n) {
  if (n < _capacity)
    return;
  T *p = new T[n];
  for (std::size_t i = 0; i < _size; ++i) {
    p[i] = _values[i];
  }
  delete[] _values;
  _values = p;
  _capacity = n;
}

/**
 * @brief Resize vector<T>
 * @tparam T
 * @param size
 * @param val
 */
template <typename T> void Vector<T>::resize(int size, T val) {
  reserve(size);
  for (std::size_t i = _size; i < size; ++i) {
    _values[i] = T();
    _size = size;
  }
}

/**
 * @brief Is empty vector
 * @tparam T
 * @return
 */
template <typename T> bool Vector<T>::empty() const { return (_size == 0); }

/**
 * @brief Returns vector capacity
 * @tparam T
 * @return
 */
template <typename T> std::size_t Vector<T>::capacity() const {
  return _capacity;
}

/**
 * @brief Pushes type to vector
 * @tparam T
 * @param val
 */
template <typename T> void Vector<T>::push_back(const T &val) {
  if (_capacity == 0) {
    reserve(8);
  }
  if (_size == _capacity) {
    reserve(2 * _capacity);
  }
  _values[_size] = val;
  ++_size;
}

/**
 * @breif Pops last item in the vector
 * @tparam T
 */
template <typename T> void Vector<T>::pop_back() {
  if (_size == 0)
    throw std::invalid_argument("Vector is empty. Nothing to pop.");
  delete _values[_size - 1];
  --_size;
}

/**
 * @brief Get Vector<T> value at index
 * @tparam T
 * @param i
 * @return
 */
template <typename T> T &Vector<T>::at(int i) {
  if (i < 0 || _size <= i) {
    throw std::out_of_range("Range Error");
  }
  return _values[i];
}

/**
 * @brief Get Vector<T> value at index
 * @tparam T
 * @param i
 * @return
 */
template <typename T> const T &Vector<T>::at(int i) const {
  if (i < 0 || _size <= i) {
    throw std::out_of_range("Range Error");
  }
  return _values[i];
}

/**
 * @brief Vector operator access
 * @tparam T
 * @param i
 * @return
 */
template <typename T> T &Vector<T>::operator[](int i) { return _values[i]; }

/**
 * @brief Vector operator access
 * @tparam T
 * @param i
 * @return
 */
template <typename T> const T &Vector<T>::operator[](int i) const {
  return _values[i];
}

/**
 * @brief C++ | Returns a direct pointer to the memory array used internally by
 * the vector to store its owned elements.
 * https://www.cplusplus.com/reference/vector/vector/data/
 * @tparam T
 * @return
 */
template <typename T> const T *Vector<T>::data() { return _values; }