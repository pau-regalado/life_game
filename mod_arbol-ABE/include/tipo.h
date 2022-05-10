#ifndef __MATRICULA__
#define __MATRICULA__

#include <iostream>

class Matricula{
  public:
    Matricula(void);
    Matricula(int data, std::string matricula);
    ~Matricula(void){}

    int calculateData(std::string mat);

    // getter / setters 

    int getData(void);
    int getData(void) const;
    std::string getMatricula(void);
    std::string getMatricula(void) const;

    void setData(int data);
    void setMatricula(std::string mat);

    Matricula& operator=(const Matricula &p);
    bool operator==(const Matricula &p);
    bool operator!=(const Matricula &p);
    bool operator< (const Matricula &p);
    bool operator> (const Matricula &p);
    bool operator<=(const Matricula &p);
    bool operator>=(const Matricula &p);

  private:
    int data_;
    std::string matricula_;
};

int Matricula::calculateData(std::string mat) {
  int out = 0;
  // para tener en cuenta el orden, data es igual al valor numerico
  // de cada uno de sus caracteres multiplicados por su posicion
  for (int i = mat.size() - 1; i >= 0; i--) {
    out += int(mat[i] * (i + 1));
  }
  return out;
}

// Por defecto
Matricula::Matricula(void){
  data_ = 0;
  matricula_ = "";
}

Matricula::Matricula(int data, std::string matricula){
  // En el caso que haya que transformar un dato a otro:
  // por ej. de la string de la matricula a un valor numerico
  data_ = calculateData(matricula);
  matricula_ = matricula;

  // En el caso que solo sea un valor se asigna directamente
  // data_ = data;
}

int Matricula::getData(void){
  return data_;
}

std::string Matricula::getMatricula() {
  return matricula_;
}

int Matricula::getData(void) const{
  return data_;
}

std::string Matricula::getMatricula() const{
  return matricula_;
}

void Matricula::setData(int data){
  data_ = data;
}

void Matricula::setMatricula(std::string mat){
  matricula_ = mat;
}

Matricula& Matricula::operator=(const Matricula &p){
  this->setData(p.getData());
  this->setMatricula(p.getMatricula());
  return *this;
}
bool Matricula::operator==(const Matricula &p){
  return this->data_ == p.getData();
}
bool Matricula::operator!=(const Matricula &p){
  return this->data_ != p.getData();
}
bool Matricula::operator< (const Matricula &p){
  return this->data_ < p.getData();
}
bool Matricula::operator> (const Matricula &p){
  return this->data_ > p.getData();
}
bool Matricula::operator<=(const Matricula &p){
  return this->data_ <= p.getData();
}
bool Matricula::operator>=(const Matricula &p){
  return this->data_ >= p.getData();
}

std::ostream& operator<< (std::ostream& os, Matricula m) {
  os << m.getMatricula();
  return os;
}

std::istream& operator>> (std::istream& is, Matricula &m) {
  std::string mat;
  is >> mat;
  m.setData(m.calculateData(mat));
  m.setMatricula(mat);
  return is;
}

#endif
