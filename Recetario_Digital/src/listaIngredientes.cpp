#include "listaIngredientes.hpp"

ListaIngredientes::ListaIngredientes():ancla(nullptr),size(0){
}

ListaIngredientes::ListaIngredientes(const ListaIngredientes& otra):ancla(nullptr),size(otra.size){
    copiarTodo(otra);
}

ListaIngredientes::~ListaIngredientes(){
    anular();

}

void ListaIngredientes::copiarTodo(const ListaIngredientes & otra){
    Nodo *aux(otra.ancla);
    Nodo *ultimo(nullptr);
    Nodo *nuevoNodo;

    while(aux !=nullptr){
        nuevoNodo=new Nodo(aux->getIngrediente());

        if(ultimo==nullptr){
            ancla=nuevoNodo;
        }
        else{
            ultimo->setSiguiente(nuevoNodo);
        }

        ultimo=nuevoNodo;

        aux=aux->getSiguiente();
    }
}

ListaIngredientes& ListaIngredientes:: operator=(const ListaIngredientes& otra){
    copiarTodo(otra);

    return *this;
}


bool ListaIngredientes::vacia() const{
  return ancla==nullptr;
}

bool ListaIngredientes::posicionValida(Nodo* p) const{
    Nodo *aux(ancla);

    while(aux !=nullptr){
        if(aux==p){
            return true;
        }

        aux=aux->getSiguiente();
    }

    return false;
}

int ListaIngredientes::getSize() const {
    return size;
}

void ListaIngredientes::insertarIngrediente(Ingrediente *ingrediente) {
    Nodo* pos = buscarPosicionOrdenada(ingrediente);

    Nodo* aux(new Nodo(ingrediente));

    if(aux==nullptr){
        throw Exception("Memoria insuficiente para agregar un nuevoIngrediente");
    }

    if(pos==nullptr){ //Insertar al principio
        aux->setSiguiente(ancla);
        ancla=aux;
    }
    else{ //Insertar en cualquier posicion
        aux->setSiguiente(pos->getSiguiente());
        pos->setSiguiente(aux);
    }

    size++;
}

void ListaIngredientes::eliminarIngrediente(Nodo* p){
    if (vacia()) {
        throw Exception("La lista está vacía, no hay ingredientes para eliminar.");
    }

    if (!posicionValida(p)) {
        throw Exception("Posicion invalida para eliminar el dato.");
    }

    if(p==ancla){ //Eliminar el primero
        ancla=ancla->getSiguiente();
    }
    else{ //Eliminar cualquier otro
        getPosicionPrevia(p)->setSiguiente(p->getSiguiente());
    }

    delete p;
    size--;
}


ListaIngredientes::Nodo *ListaIngredientes::getPrimeraPosicion() const{
  return ancla;
}

ListaIngredientes::Nodo *ListaIngredientes::getUltimaPosicion() const{
    if(vacia()){
        return nullptr;
    }

    Nodo* aux(ancla);

    while(aux->getSiguiente() != nullptr){
        aux=aux->getSiguiente();
    }

    return aux;
}

ListaIngredientes::Nodo *ListaIngredientes::getPosicionPrevia(Nodo * p) const{
    if(p==ancla){
        return nullptr;
    }

    Nodo* aux(ancla);


    while(aux != nullptr && aux->getSiguiente() !=p){
        aux=aux->getSiguiente();
    }

    return aux;
}

ListaIngredientes::Nodo *ListaIngredientes::getSiguientePosicion(Nodo * p) const{
    if(!posicionValida(p)){
        return nullptr;
    }

    return p->getSiguiente();
}

Ingrediente *ListaIngredientes::recuperarIngrediente(Nodo * p){
    if (!posicionValida(p)) {
        throw Exception("Posicion invalida para recuperar el elemento.");
    }

    return p->getIngredientePtr();
}



ListaIngredientes::Nodo *ListaIngredientes::busquedaLineal(const Ingrediente *objetivo, int (*cmp)(const Ingrediente &, const Ingrediente &)) const{
    Nodo* aux(ancla);

    while(aux !=nullptr){
        if(cmp(aux->getIngrediente(),*objetivo)==0){
            return aux;
        }

        aux=aux->getSiguiente();
    }

    return aux;
}

ListaIngredientes::Nodo *ListaIngredientes::buscarPosicionOrdenada(const Ingrediente * ingrediente) const{
    Nodo* aux(ancla);

    while(aux!=nullptr and aux->getIngrediente().getNombre() <= ingrediente->getNombre()){
        aux=aux->getSiguiente();
    }

    return aux;
}



QString ListaIngredientes::toQstring() {
    Nodo* aux(ancla);
    QString resultado;
    int i=0;

    resultado+="---INGREDIENTES---\n\n";
    while(aux !=nullptr){
        resultado+=QString::number(i+1)+". "+ aux->getIngrediente().toQstring()+"\n";
        aux=aux->getSiguiente();

        if(aux != nullptr){
            resultado += "─────────────────────────\n";
        }
        i++;
    }

    return resultado;
}

void ListaIngredientes::anular(){
    Nodo *aux;

    while(ancla!=nullptr){
        aux=ancla;

        ancla=ancla->getSiguiente();

        delete aux;
    }
}

ListaIngredientes::Nodo::Nodo():ingrediente(nullptr),siguiente(nullptr){}

ListaIngredientes::Nodo::Nodo(Ingrediente * i):ingrediente(i),siguiente(nullptr){}

ListaIngredientes::Nodo::Nodo(const Ingrediente & i):ingrediente(new Ingrediente(i)),siguiente(nullptr){
    if(ingrediente==nullptr){
        throw Exception("Memoria insuficiente al crear Nodo");
    }
}

Ingrediente *ListaIngredientes::Nodo::getIngredientePtr() const{
    return ingrediente;
}

Ingrediente ListaIngredientes::Nodo::getIngrediente() const{
    if(ingrediente==nullptr){
        throw Exception("Ingrediente inexistente");
    }
    return *ingrediente;
}

ListaIngredientes::Nodo *ListaIngredientes::Nodo::getSiguiente() const{
    return siguiente;
}

void ListaIngredientes::Nodo::setIngredientePtr(Ingrediente * i){
    ingrediente=i;
}

void ListaIngredientes::Nodo::setIngrediente(const Ingrediente & i){
    if (ingrediente == nullptr) {
        if ((ingrediente = new Ingrediente(i)) == nullptr) {
            throw Exception("Memoria no disponible");
        }
    } else {
        *ingrediente = i;
    }
}

void ListaIngredientes::Nodo::setSiguiente(Nodo * p){
    siguiente=p;
}
