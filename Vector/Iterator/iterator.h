#include <iterator>
template <typename T> class iterator {
protected:
  T *m_ptr;
public:
  using iterator_category = std::random_access_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = T *;
  using reference = T &;

  iterator(T* ptr = nullptr){m_ptr = ptr;}
  iterator(const iterator<T>& rawit) = default;
  ~iterator(){}

  iterator<T>& operator=(const iterator<T>& rawit) = default;
  iterator<T>& operator=(T* ptr){m_ptr = ptr;return (*this);}

  operator bool() const { if (m_ptr) return true; else return false; }
  bool operator==(const iterator<T> &rawit) const { return (m_ptr == rawit.gcptr()); }
  bool operator!=(const iterator<T> &rawit) const { return (m_ptr != rawit.gcptr()); }

  iterator<T> &operator+=(const difference_type &movement) {
    m_ptr += movement;
    return (*this);
  }
  iterator<T> &operator-=(const difference_type &movement) {
    m_ptr -= movement;
    return (*this);
  }
  iterator<T> &operator++() {
    ++m_ptr;
    return (*this);
  }
  iterator<T> &operator--() {
    --m_ptr;
    return (*this);
  }
  iterator<T> operator++(int) {
    auto temp(*this);
    ++m_ptr;
    return temp;
  }
  iterator<T> operator--(int) {
    auto temp(*this);
    --m_ptr;
    return temp;
  }
  iterator<T> operator+(const difference_type &movement) {
    auto oldPtr = m_ptr;
    m_ptr += movement;
    auto temp(*this);
    m_ptr = oldPtr;
    return temp;
  }
  iterator<T> operator-(const difference_type &movement) {
    auto oldPtr = m_ptr;
    m_ptr -= movement;
    auto temp(*this);
    m_ptr = oldPtr;
    return temp;
  }

  difference_type operator-(const iterator<T> &rawit) {
    return std::distance(rawit.gptr(), this->gptr());
  }

  T &operator*() { return *m_ptr; }
  const T &operator*() const { return *m_ptr; }
  T *operator->() { return m_ptr; }

  T *gptr() const { return m_ptr; }
  const T *gcptr() const { return m_ptr; }
};