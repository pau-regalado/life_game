#include <iostream>

class Saludo {
    public:
    virtual void Saludar(void) = 0;
};

class Espanol: public Saludo{
    public:
    virtual void Saludar(void){
        std::cout << "Hoola poopee" << std::endl;
    }
};

class Ingles: public Saludo{
    public:
    virtual void Saludar(void){
        std::cout << "Hellou lutyy" << std::endl;
    }
};

class Persona{
   
    public:
     Saludo* x_;
        Persona(Saludo* x){
            x_ = x;
        }
        ~Persona(void){
            delete x_;
        }
        void setSaludo(Saludo* x){
            x_ = x;
        }
};

int main(void) {
Saludo* s = new Espanol;
Persona p(s);

p.x_->Saludar();

p.setSaludo(new Ingles);

p.x_->Saludar();

return 0;
}
