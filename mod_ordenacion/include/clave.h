#ifndef _CLAVE_
#define _CLAVE_
#include "commons.h"

class Key {
  public:
    Key(int value = 0): value_(value) {
      
    }
    ~Key(){}
    int getValue() {
      return value_;
    }
    Key& operator= (const Key& clave) {
      this->value_ = clave.value_;
      count_++;
      return *this;
    }
    // operator <
    bool operator< (Key& clave) {
      return this->value_ < clave.getValue();
    }
    // operator >
    bool operator> (Key& clave) {
      return this->value_ > clave.getValue();
    }
    // operator >=
    bool operator>= (Key& clave) {
      return this->value_ >= clave.getValue();
    }
    // operator <=
    bool operator<= (Key& clave) {
      return this->value_ <= clave.getValue();
    }
    

  private:
    static int count_;
    int value_;
};

std::ostream& operator<<(std::ostream& os, Key& clave){
      return os << clave.getValue();
}

#endif