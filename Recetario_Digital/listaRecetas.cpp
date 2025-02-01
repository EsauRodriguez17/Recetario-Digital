#include "listaRecetas.hpp"


ListaRecetas::ListaRecetas():ancla(nullptr),size(0){
}

ListaRecetas::ListaRecetas(const ListaRecetas& otra):ancla(nullptr),size(otra.size){
    copiarTodo(otra);
}

ListaRecetas::~ListaRecetas(){
    anular();
}

void ListaRecetas::copiarTodo(const ListaRecetas & otra){
    Nodo* aux(otra.ancla);
    Nodo* ultimo(nullptr);
    Nodo* nuevoNodo;

    while (aux != nullptr) {
        if ((nuevoNodo = new Nodo(aux->getReceta())) == nullptr) {
            throw Exception("Memoria no disponible al copiar");
        }

        if (ultimo == nullptr) {
            ancla = nuevoNodo;
        } else {
            nuevoNodo->setAnterior(ultimo);
            ultimo->setSiguiente(nuevoNodo);
        }

        ultimo = nuevoNodo;

        aux = aux->getSiguiente();
    }
}

ListaRecetas& ListaRecetas::operator=(const ListaRecetas& otra){
    anular();

    copiarTodo(otra);

    return *this;
}


bool ListaRecetas::vacia() const {
   return ancla == nullptr;
}


int ListaRecetas::getSize() const {
    return size;
}

void ListaRecetas::agregarReceta(Receta* receta,Nodo* p) {
    if (p != nullptr && !posicionValida(p)) {
        throw Exception("Posición invalida para insertar el dato.");
    }

    Nodo* aux(new Nodo(receta));

    if (aux == nullptr) {
        throw Exception("Memoria insuficiente para agregar una nueva cancion");
    }

    if (p == nullptr) {  // Insertar al principio
        aux->setSiguiente(ancla);

        if (ancla != nullptr) {
            ancla->setAnterior(aux);
        }
        ancla = aux;
    } else {  // Insertar en cualquier posicion
        aux->setAnterior(p);
        aux->setSiguiente(p->getSiguiente());

        if (p->getSiguiente() != nullptr) {
            p->getSiguiente()->setAnterior(aux);
        }
        p->setSiguiente(aux);
    }
    size++;
}

void ListaRecetas::eliminarReceta(Nodo* p) {
    if (!posicionValida(p)) {
        throw Exception("Posicion invalida para eliminar el dato.");
    }

    if (p->getAnterior() != nullptr) {
        p->getAnterior()->setSiguiente(p->getSiguiente());
    }

    if (p->getSiguiente() != nullptr) {
        p->getSiguiente()->setAnterior(p->getAnterior());
    }

    if (p == ancla) {
        ancla = ancla->getSiguiente();
    }

    delete p;
    size--;
}

bool ListaRecetas::posicionValida(Nodo* pos) const {
    Nodo* aux(ancla);

    while (aux != nullptr) {
        if (aux == pos) {
            return true;
        }

        aux = aux->getSiguiente();
    }

    return false;
}

ListaRecetas::Nodo* ListaRecetas::getPrimeraPosicion() const {
    return ancla;
}

ListaRecetas::Nodo* ListaRecetas::getUltimaPosicion() const {
    if (vacia()) {
        return nullptr;
    }

    Nodo* aux(ancla);

    while (aux->getSiguiente() != nullptr) {
        aux = aux->getSiguiente();
    }

    return aux;
}

ListaRecetas::Nodo* ListaRecetas::getPosicionPrevia(Nodo*  p) const {
    if (p == ancla) {
        return nullptr;
    }

    return p->getAnterior();
}

ListaRecetas::Nodo* ListaRecetas::getSiguientePosicion( Nodo*  p) const {
    if (!posicionValida(p)) {
        return nullptr;
    }

    return p->getSiguiente();
}


ListaRecetas::Nodo* ListaRecetas::localiza(Receta * receta){
    Nodo* aux(ancla);

    while (aux != nullptr && aux->getRecetaPtr() != receta) {
        aux = aux->getSiguiente();
    }

    return aux;
}

Receta* ListaRecetas::recuperarReceta(Nodo* p) const {
    if (!posicionValida(p)) {
        throw Exception("Posicion invalida para recuperar el elemento.");
    }

    return p->getRecetaPtr();
}

ListaRecetas::Nodo* ListaRecetas::busquedaLineal(const Receta* objetivo, int (*cmp)(const Receta&, const Receta&)) const {
    Nodo* aux(ancla);

    while (aux != nullptr) {
        if (cmp(aux->getReceta(), *objetivo) == 0) {
            return aux;
        }

        aux = aux->getSiguiente();
    }

    return aux;
}


void ListaRecetas::quickSort(int (*cmp)(const Receta &, const Receta &)){
    if(ancla==nullptr){
        return;
    }

    quickSort(ancla, getUltimaPosicion(), cmp);
}

void ListaRecetas::quickSort(Nodo* left, Nodo* right, int (*cmp)(const Receta &, const Receta &)){
    if (left == nullptr || right == nullptr || left == right || left->getAnterior() == right) {
        return;
    }

    Nodo* pivotNode = partition(left, right, cmp);

    quickSort(left, pivotNode->getAnterior(), cmp);
    quickSort(pivotNode->getSiguiente(), right, cmp);
}

ListaRecetas::Nodo* ListaRecetas::partition(Nodo* left, Nodo* right, int (*cmp)(const Receta&, const Receta&)) {
    Receta* pivot = right->getRecetaPtr();
    Nodo* i = left->getAnterior();

    for (Nodo* j = left; j != right; j = j->getSiguiente()) {
        if (cmp(*j->getRecetaPtr(), *pivot) <= 0) {
            i = (i == nullptr) ? left : i->getSiguiente();
            swap(i, j);
        }
    }

    i = (i == nullptr) ? left : i->getSiguiente();
    swap(i, right);

    return i;
}

void ListaRecetas::swap(Nodo* a, Nodo* b){
    Receta* temp = a->getRecetaPtr();
    a->setRecetaPtr(b->getRecetaPtr());
    b->setRecetaPtr(temp);
}

void ListaRecetas::guardarRecetas(const QString &filePath){
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        throw Exception("Error, No se pudo abrir el archivo para guardar las recetas.");
        return;
    }

    QJsonArray recetasArray;
    posicion* posActual = getPrimeraPosicion();

    while (posActual != nullptr) {
        Receta* receta = posActual->getRecetaPtr();
        if (receta) {
            recetasArray.append(receta->toJson()); // Usamos el método toJson de Receta
        }
        posActual = posActual->getSiguiente();
    }

    QJsonDocument jsonDoc(recetasArray);
    file.write(jsonDoc.toJson());
    file.close();
}

void ListaRecetas::cargarRecetas(const QString &filePath){
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw Exception("Error, No se pudo abrir el archivo para cargar las recetas");
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDoc(QJsonDocument::fromJson(fileData));
    QJsonArray recetasArray = jsonDoc.array();

    for (const QJsonValue &value : recetasArray) {
        QJsonObject recetaObject = value.toObject();

        Receta* receta = new Receta;
        receta->fromJson(recetaObject); // Llamar al método fromJson de la receta
        agregarReceta(receta, getUltimaPosicion());
    }
}

void ListaRecetas::anular() {
    Nodo* aux;

    while (ancla != nullptr) {
        aux = ancla;

        ancla = ancla->getSiguiente();

        delete aux;
    }
}

ListaRecetas::Nodo::Nodo():receta(nullptr),anterior(nullptr),siguiente(nullptr){}

ListaRecetas::Nodo::Nodo(Receta *r):receta(r),anterior(nullptr),siguiente(nullptr){}

ListaRecetas::Nodo::Nodo(const Receta &r):receta(new Receta(r)),anterior(nullptr),siguiente(nullptr){
    if (receta == nullptr) {
        throw Exception("Memoria insuficiente al crear Nodo");
    }
}

ListaRecetas::Nodo::~Nodo(){
    delete receta;
}

Receta *ListaRecetas::Nodo::getRecetaPtr() const{
    return receta;
}

Receta ListaRecetas::Nodo::getReceta() const{
    if (receta == nullptr) {
        throw Exception("Receta inexistente");
    }
    return *receta;
}

ListaRecetas::Nodo *ListaRecetas::Nodo::getAnterior() const{
  return anterior;
}

ListaRecetas::Nodo *ListaRecetas::Nodo::getSiguiente() const{
  return siguiente;
}

void ListaRecetas::Nodo::setRecetaPtr(Receta * r){
    receta=r;
}

void ListaRecetas::Nodo::setReceta(const Receta & r){
    if (receta == nullptr) {
        if ((receta = new Receta(r)) == nullptr) {
            throw Exception("Memoria no disponible");
        }
    } else {
        *receta = r;
    }
}

void ListaRecetas::Nodo::setAnterior(Nodo * p){
  anterior = p;
}

void ListaRecetas::Nodo::setSiguiente(Nodo * p){
  siguiente = p;
}
