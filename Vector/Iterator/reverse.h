template <typename T> class reverse : public iterator<T> {
public:
  reverse(T *ptr = nullptr) : iterator<T>(ptr) {}
  reverse(const iterator<T> &rawit) { this->m_ptr = rawit.gptr(); }
  reverse(const reverse<T> &rrawit) = default;
  ~reverse() {}

  reverse<T> &operator=(const reverse<T> &rrawit) = default;
  reverse<T> &operator=(const iterator<T> &rawit) {
    this->m_ptr = rawit.gptr();
    return (*this);
  }
  reverse<T> &operator=(T *ptr) {
    this->setPtr(ptr);
    return (*this);
  }

  reverse<T> &operator+=(const typename iterator<T>::difference_type &movement) {
    this->m_ptr -= movement;
    return (*this);
  }
  reverse<T> &operator-=(const typename iterator<T>::difference_type &movement) {
    this->m_ptr += movement;
    return (*this);
  }

  reverse<T> &operator++() {
    --this->m_ptr;
    return (*this);
  }
  reverse<T> operator++(int) {
    auto temp(*this);
    --this->m_ptr;
    return temp;
  }

  reverse<T> &operator--() {
    ++this->m_ptr;
    return (*this);
  }
  reverse<T> operator--(int) {
    auto temp(*this);
    ++this->m_ptr;
    return temp;
  }

  reverse<T> operator+(const int &movement) {
    auto old = this->m_ptr;
    this->m_ptr -= movement;
    auto temp(*this);
    this->m_ptr = old;
    return temp;
  }
  reverse<T> operator-(const int &movement) {
    auto old = this->m_ptr;
    this->m_ptr += movement;
    auto temp(*this);
    this->m_ptr = old;
    return temp;
  }

  typename iterator<T>::difference_type operator-(const reverse<T> &rrawit) {return std::distance(this->gptr(), rrawit.gptr());}

  iterator<T> base() {
    iterator<T> forwardIterator(this->m_ptr);
    ++forwardIterator;
    return forwardIterator;
  }
};