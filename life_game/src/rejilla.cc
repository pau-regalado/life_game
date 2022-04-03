#include "../include/rejilla.h"
#include "../include/celula.h"
#include "../include/state.h"

// ----------------------- Grid ---------------------------------

Grid::Grid(int row, int col){
  nrows_ = row;
  ncols_ = col;
  turno_ = 0;

  // Reserva de memoria dinamica de (nrows_ + 2) vectores de celulas y cada
  // uno de ellos realiza lo mismo con (ncols_ + 2), para inicializar toda la
  // matriz a muerta y ademas tener un borde contra desbordamientos
  rejilla_ = new Celula*[nrows_ + 2];
  for (int i = 0; i < nrows_ + 2; i++) {
    rejilla_[i] = new Celula[ncols_ + 2];
    for (int j = 0; j < ncols_ + 2; j++) {
      rejilla_[i][j].setX(i);
      rejilla_[i][j].setY(j);
      rejilla_[i][j].setState(new StateDead(&rejilla_[i][j]));
    }
  } 
}

// NOTESE: segun esta implementacion de la practica, todas las clases derivadas
// de Grid se muestran igual, por lo que se podria implementar directamente en
// la clase padre y ahorrar codigo, pero se ha mantenido asi para demostrar que
// funciona la herencia y cada rejilla se imprime a su manera

// Muestra por pantalla la rejilla, de esta forma podemos implementar el 
// polimorfismo con el operador de insercion
std::ostream& operator<<(std::ostream& os, Grid &g) {
  g.print();
  return os;
}

// --------- MODIFICACION -----------

void Grid::contEstados(void){
  int v = 0, m = 0;
  for(int i = 1; i < nrows_ + 1; i++){
    for(int j = 1; j < ncols_ + 1; j++){
    	if (rejilla_[i][j].getState()->getState() == A){
	  v++;	
	}else if (rejilla_[i][j].getState()->getState() == D) {
	  m++;
	}
    }
  }
  std::cout << "Vivas: " << v << " Muertas: " << m << std::endl;
}

// NOTESE: segun esta implementacion de la practica, todos los destructores de 
// las clases derivadas de Grid son  iguales, por lo que se podria implementar 
// directamente en la clase padre y ahorrar codigo, pero se ha mantenido el 
// destructor de Grid virtual puto para que se vea que funciona la herencia

// Necesario para la definicion de los destructores derivados
Grid::~Grid(){std::cout << "Destruccion base" << std::endl;}

// Bateria para cargar celulas vivas directamente para probar el codigo
// resaltar que obviamente puede dar error de ejecucion. Se utiliza
// conscientemente
void Grid::defecto(void){

  rejilla_[1][1].setState(new StateAlive(&rejilla_[1][1]));
  rejilla_[1][2].setState(new StateAlive(&rejilla_[1][2]));
  rejilla_[1][3].setState(new StateAlive(&rejilla_[1][3]));
  
  /*
  //rejilla_[4][1].setState(new StateAlive(&rejilla_[4][1]));
  //rejilla_[4][3].setState(new StateAlive(&rejilla_[4][3]));
  //rejilla_[2][4].setState(new StateAlive(&rejilla_[2][4]));
  //rejilla_[1][4].setState(new StateAlive(&rejilla_[1][4]));
  rejilla_[1][1].setState(new StateAlive(&rejilla_[1][1]));
  rejilla_[2][2].setState(new StateAlive(&rejilla_[2][2]));
  rejilla_[3][3].setState(new StateAlive(&rejilla_[3][3]));
  rejilla_[4][4].setState(new StateAlive(&rejilla_[4][4]));
  rejilla_[4][3].setState(new StateAlive(&rejilla_[4][3]));
  rejilla_[2][4].setState(new StateAlive(&rejilla_[2][4]));
  rejilla_[1][4].setState(new StateAlive(&rejilla_[1][4]));*/

}

// Bucle para insertar celulas dentro de la rejilla
void Grid::insert(void){

  int opt;
  bool quit = false;

  while (!quit) {
    std::cout << "Grid actual:" << std::endl;
    print();
    std::cout << "1) Introducir celula viva" << std::endl;
    std::cout << "2) Terminar" << std::endl;
    std::cout << "opt> ";

    std::cin >> opt;

    std::cout << std::endl;

    switch (opt){
    case 1: {
      int x, y;
      char e;
      std::cout << "x: ";
      std::cin >> x;
      std::cout << "y: ";
      std::cin >> y;

      if (x < nrows_ + 1 && y < ncols_ + 1){
        std::cout << "En que estado? (D | A) : ";
        std::cin >> e;
        switch (e){
        case 'D':
            rejilla_[x][y].setState(new StateDead(&rejilla_[x][y]));
          break;
        case 'A':
            rejilla_[x][y].setState(new StateAlive(&rejilla_[x][y]));
          break;        
        default:
          std::cout << "Error. Estado desconocido" << std::endl;
          break;
        }
      } else
        std::cout << "Posicion invalida";
        std::cout << std::endl;
        break;
    }
    case 2: 
      quit = true;
    }
  }
}

// Lleva la rejilla a la siguiente generacion
// Recorre la matriz una primera vez para que cada celula actualice sus
// vecinas y una segunda vez para transitar a los estados correspondientes
// Vemos que solo se actualizan las celulas de dentro, las que no estan en
// el borde
void Grid::nextGeneration(void){

  // Actualizamos vecinas vivas
  for (int i = 1; i < nrows_ + 1; i++) {
    for (int j = 1; j < ncols_ + 1; j++) {
      rejilla_[i][j].neighbors(*this);
    }
  }
  for (int i = 1; i < nrows_ + 1; i++) {
    for (int j = 1; j < ncols_ + 1; j++) {
      rejilla_[i][j].updateState();
    }
  }
  turno_++;
  print();
}

// ------------------- GridWithOpenBorder ---------------------------------
// Llamada al constructor de Grid, todos los objetos Grid se construyen igual
GridWithOpenBorder::GridWithOpenBorder(int row, int col): Grid(row,col){}

// Libera la memoria reservada para la rejilla
GridWithOpenBorder::~GridWithOpenBorder(){
  std::cout << "Destruccion OpenBorder" << std::endl;
  for (int i = 0; i < nrows_ + 2; i++){
    delete[] rejilla_[i]; // Libera la memoria de cada vector
  }
  delete rejilla_;        // Libera la memoria reservada para el vertor principal
}

// Devuelve la celula en la posicion indicada. OpenBorder no calcula nada
Celula& GridWithOpenBorder::getCelula(int x, int y){
    return rejilla_[x][y];
}
// Getter constante, se usa en la mayoria del codigo
// Devuelve la celula en la posicion indicada. OpenBorder no calcula nada
const Celula& GridWithOpenBorder::getCelula(int x, int y) const{
  return rejilla_[x][y];
}

// Imprime la rejilla por pantalla sin mostrar los bordes reservados para
// evitar el desbordamiento
void GridWithOpenBorder::print(void){
  std::cout << std::endl << "TURNO OPEN: " << turno_ << std::endl;

  for (int i = 0; i < ncols_ + 2; i++){
    std::cout << "⬛";
  }
  std::cout << std::endl;

  for (int i = 1; i < nrows_ + 1; i++) {
    std::cout << "⬛";
    for (int j = 1; j < ncols_ + 1; j++) {
      std::cout << rejilla_[i][j];
    }
    std::cout << "⬛" << std::endl;
  }
  
  for (int i = 0; i < ncols_ + 2; i++){
    std::cout << "⬛";
  }
  std::cout << std::endl << std::endl;
  contEstados();
}

// ------------------- GridWithPeriodicBorder ---------------------------------
// Llamada al constructor de Grid, todos los objetos Grid se construyen igual
GridWithPeriodicBorder::GridWithPeriodicBorder(int row, int col): Grid(row,col){}

// Libera la memoria reservada para la rejilla.
GridWithPeriodicBorder::~GridWithPeriodicBorder(){
  std::cout << "Destruccion PeriodicBorder" << std::endl;
  for (int i = 0; i < nrows_ + 2; i++){
    delete[] rejilla_[i]; // Libera la memoria de cada vector
  }
  delete rejilla_;        // Libera la memoria reservada para el vertor principal
}

// Devuelve la celula en la posicion indicada.
// Si una coordenada toca el borde, se le asigna la posicion del lado opuesto,
// dando efecto de rejilla circular.
Celula& GridWithPeriodicBorder::getCelula(int x, int y){
  if (x == 0) {
    x = nrows_;
  }else if (x == nrows_ + 1) {
    x = 0;
  }
  if (y == 0) {
    y = ncols_;
  }else if (y == ncols_ + 1) {
    y = 0;
  }
  return rejilla_[x][y];
}

// Getter constante, se usa en la mayoria del codigo
// Devuelve la celula en la posicion indicada.
// Si una coordenada toca el borde, se le asigna la posicion del lado opuesto,
// dando efecto de rejilla circular.
const Celula& GridWithPeriodicBorder::getCelula(int x, int y) const{
  if (x == 0) {
    x = nrows_;
  }else if (x == nrows_ + 1) {
    x = 1;
  }
  if (y == 0) {
    y = ncols_;
  }else if (y == ncols_ + 1) {
    y = 1;
  }
  return rejilla_[x][y];
}

// Imprime la rejilla por pantalla sin mostrar los bordes reservados para
// evitar el desbordamiento
void GridWithPeriodicBorder::print(void){
  std::cout << std::endl << "TURNO PERIODIC: " << turno_ << std::endl;

  for (int i = 0; i < ncols_ + 2; i++){
    std::cout << "⬛";
  }
  std::cout << std::endl;

  for (int i = 1; i < nrows_ + 1; i++) {
    std::cout << "⬛";
    for (int j = 1; j < ncols_ + 1; j++) {
      std::cout << rejilla_[i][j];
    }
    std::cout << "⬛" << std::endl;
  }
  
  for (int i = 0; i < ncols_ + 2; i++){
    std::cout << "⬛";
  }
  std::cout << std::endl << std::endl;
  contEstados();
}

// ------------------- GridWithReflectiveBorder ---------------------------------

// Llamada al constructor de Grid, todos los objetos Grid se construyen igual
GridWithReflectiveBorder::GridWithReflectiveBorder(int row, int col): Grid(row, col){}

// Libera la memoria reservada para la rejilla.
GridWithReflectiveBorder::~GridWithReflectiveBorder(){
  std::cout << "Destruccion ReflectiveBorder" << std::endl;
  for (int i = 0; i < nrows_ + 2; i++){
    delete[] rejilla_[i]; // Libera la memoria de cada vector
  }
  delete rejilla_;        // Libera la memoria reservada para el vertor principal
}

// Devuelve la celula en la posicion indicada.
// Las coordenadas que se encuentran en los bordes, esto es, si alguna o ambas
// de sus coordenadas lo estan, se calcula la posicion de la celula que la esta
// investigando y se devuelve la posicion de esta ultima.
Celula& GridWithReflectiveBorder::getCelula(int x, int y){
  if (x == 0){
    x = 1;
    if (y == 0) {
      y = 1;
    } else if (y == ncols_ + 1) {
      y = ncols_;
    }
  }
  if (x == nrows_ + 1){
    x = nrows_;
    if (y == 0) {
      y = 1;
    } else if (y == ncols_ + 1) {
      y = ncols_;
    }
  }
  if (y == 0){
    y = 1;
    if (x == 0) {
      x = 1;
    } else if (x == nrows_ + 1) {
      x = nrows_;
    }
  }
  if (y == ncols_ + 1){
    y = ncols_;
    if (x == 0) {
      x = 1;
    } else if (x == nrows_ + 1) {
      x = nrows_;
    }
  }
  return rejilla_[x][y];
}

// Getter constante, se usa en la mayoria del codigo
// Devuelve la celula en la posicion indicada.
// Las coordenadas que se encuentran en los bordes, esto es, si alguna o ambas
// de sus coordenadas lo estan, se calcula la posicion de la celula que la esta
// investigando y se devuelve la posicion de esta ultima.
const Celula& GridWithReflectiveBorder::getCelula(int x, int y) const{
  if (x == 0){
    x = 1;
    if (y == 0) {
      y = 1;
    } else if (y == ncols_ + 1) {
      y = ncols_;
    }
  }
  if (x == nrows_ + 1){
    x = nrows_;
    if (y == 0) {
      y = 1;
    } else if (y == ncols_ + 1) {
      y = ncols_;
    }
  }
  if (y == 0){
    y = 1;
    if (x == 0) {
      x = 1;
    } else if (x == nrows_ + 1) {
      x = nrows_;
    }
  }
  if (y == ncols_ + 1){
    y = ncols_;
    if (x == 0) {
      x = 1;
    } else if (x == nrows_ + 1) {
      x = nrows_;
    }
  }
  return rejilla_[x][y];
}

// Imprime la rejilla por pantalla sin mostrar los bordes reservados para
// evitar el desbordamiento
void GridWithReflectiveBorder::print(void){
  std::cout << std::endl << "TURNO Reflective: " << turno_ << std::endl;
  for (int i = 0; i < ncols_ + 2; i++){
    std::cout << "⬛";
  }
  std::cout << std::endl;

  for (int i = 1; i < nrows_ + 1; i++) {
    std::cout << "⬛";
    for (int j = 1; j < ncols_ + 1; j++) {
      std::cout << rejilla_[i][j];
    }
    std::cout << "⬛" << std::endl;
  }
  
  for (int i = 0; i < ncols_ + 2; i++){
    std::cout << "⬛";
  }
  std::cout << std::endl << std::endl;
  contEstados();
}
