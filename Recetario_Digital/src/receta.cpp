#include "receta.hpp"

Receta::Receta():listaIngredientes() {}

Receta::Receta(const Receta& otra){
    copiarTodo(otra);
}

Receta::~Receta() {
}

void Receta::copiarTodo(const Receta& otra){
    this->nombre=otra.nombre;
    this->preparacion=otra.preparacion;
    this->categoria=otra.categoria;
    this->autor=otra.autor;
    this->tiempoPreparacion=otra.tiempoPreparacion;
    this->rutaImagen=otra.rutaImagen;
    this->id=otra.id;

    listaIngredientes = otra.listaIngredientes;
}

void Receta::setNombre(const QString & nuevoNombre){
    nombre=nuevoNombre;
}

void Receta::setPreparacion(const QString & nuevaPreparacion){
    preparacion=nuevaPreparacion;
}

void Receta::setRutaImagen(const QString &newRutaImagen){
    rutaImagen = newRutaImagen;
    cargarImagen();
}

void Receta::setImagen(const QPixmap & nuevaImgen){
    imagen=nuevaImgen;
}

void Receta::cargarImagen(){
    if(!rutaImagen.isEmpty()){
        imagen=QPixmap(rutaImagen);
    }
}

void Receta::setCategoria(const Categoria & nuevaCategoria){
    categoria=nuevaCategoria;
}

void Receta::setAutor(const Nombre & nuevoAutor){
    autor=nuevoAutor;
}

void Receta::setTiempoPreparacion(const int & nuevoTiempo){
    tiempoPreparacion=nuevoTiempo;
}

void Receta::setId(const int & nuevoId){
    id=nuevoId;
}

void Receta::agregarIngrediente(Ingrediente *ingrediente){
    listaIngredientes.insertarIngrediente(ingrediente);
}

void Receta::eliminarTodosLosIngredientes(){
    listaIngredientes.anular();
}

QString Receta::getNombre() const{
    return nombre;
}

QString Receta::getPreparacion() const{
    return preparacion;
}


QString Receta::getRutaImagen() const{
    return rutaImagen;
}

const QPixmap &Receta::getImagen() const{
    return imagen;
}

Receta::Categoria Receta::getCategoria() const{
    return categoria;
}

Nombre Receta::getAutor() const{
    return autor;
}

int Receta::getTiempoPreparacion() const{
    return tiempoPreparacion;
}

int Receta::getId() const{
    return id;
}

ListaIngredientes& Receta::getListaIngredientes() {
    return listaIngredientes;
}

Receta& Receta::operator=(const Receta& otra){
    if (this != &otra) {
        copiarTodo(otra);
    }
    return *this;
}

bool Receta::operator==(const Receta& other) const {
    return nombre == other.nombre;
}

bool Receta::operator!=(const Receta& other) const {
    return !(*this == other);
}

bool Receta::operator<(const Receta& other) const {
    return id < other.id;
}

bool Receta::operator>(const Receta& other) const {
    return other < *this;
}

bool Receta::operator<=(const Receta& other) const {
    return !(*this > other);
}

bool Receta::operator>=(const Receta& other) const {
    return !(*this < other);
}

QTextStream& operator<<(QTextStream& os, const Receta& receta) {
    os << receta.getNombre() << "|"
       << receta.getCategoriaToInt() << "|"
       << receta.getRutaImagen() << "|" //
       << receta.getTiempoPreparacion() << "|"
       << receta.getAutor().getNombre() << "|"
       << receta.getAutor().getApellido() << "|"
       << receta.getPreparacion() << "*";
    return os;
}

QTextStream& operator>>(QTextStream& is, Receta& receta) {
    QString nombre, rutaImagen, autorNombre, autorApellido, preparacion;
    int tiempoPreparacion, categoria;

    nombre = is.readLine('|');
    is >> categoria;
    is.skipWhiteSpace();
    rutaImagen = is.readLine('|');
    is >> tiempoPreparacion;
    is.skipWhiteSpace();
    autorNombre = is.readLine('|');
    autorApellido = is.readLine('|');
    preparacion = is.readLine();

    receta.setNombre(nombre);
    receta.setCategoria(static_cast<Receta::Categoria>(categoria));
    receta.setRutaImagen(rutaImagen);
    receta.setTiempoPreparacion(tiempoPreparacion);


    Nombre autor;
    autor.setNombre(autorNombre);
    autor.setApellido(autorApellido);
    receta.setAutor(autor);

    receta.setPreparacion(preparacion);

    return is;
}

QString Receta::getCategoriaToQstring() const{
    switch (categoria) {
        case Categoria::DESAYUNO:   return "Desayuno";
        case Categoria::COMIDA:     return "Comida";
        case Categoria::CENA:       return "Cena";
        case Categoria::NAVIDEÑO:   return "Navideño";
        default:                    return "Desconocida";
    }
}

int Receta::getCategoriaToInt() const{
    if (categoria >= Categoria::DESAYUNO && categoria <= Categoria::NAVIDEÑO) {
        return static_cast<int>(categoria);
    }

    return -1;
}

int Receta::compararPorNombre(const Receta & a, const Receta & b){
    return QString::compare(a.getNombre(), b.getNombre(), Qt::CaseInsensitive);
}

int Receta::compararPorTiempoPreparacion(const Receta & a, const Receta & b){
    return a.getTiempoPreparacion()-b.getTiempoPreparacion();
}

QJsonObject Receta::toJson() const{
    QJsonObject recetaObject;
    recetaObject["nombre"] = getNombre();
    recetaObject["categoria"] = getCategoriaToInt();
    recetaObject["rutaImagen"] = getRutaImagen();
    recetaObject["tiempoPreparacion"] = getTiempoPreparacion();

    // Procesar autor
    QJsonObject autorObject;
    Nombre autor = getAutor();
    autorObject["nombre"] = autor.getNombre();
    autorObject["apellido"] = autor.getApellido();
    recetaObject["autor"] = autorObject;

    recetaObject["preparacion"] = getPreparacion();

    // Procesar ingredientes
    QJsonArray ingredientesArray;
    ListaIngredientes::posicion* aux = listaIngredientes.getPrimeraPosicion();
    while (aux != nullptr) {
        Ingrediente* ingrediente = aux->getIngredientePtr();
        if (ingrediente) {
            QJsonObject ingredienteObject;
            ingredienteObject["nombre"] = ingrediente->getNombre();
            ingredienteObject["cantidad"] = ingrediente->getCantidad();
            ingredienteObject["unidad"] = ingrediente->unidadMedidaToint();
            ingredientesArray.append(ingredienteObject);
        }
        aux = aux->getSiguiente();
    }
    recetaObject["ingredientes"] = ingredientesArray;

    return recetaObject;
}

void Receta::fromJson(const QJsonObject & json){
    nombre = json["nombre"].toString();
    categoria = static_cast<Categoria>(json["categoria"].toInt());
    rutaImagen = json["rutaImagen"].toString();
    cargarImagen();
    tiempoPreparacion = json["tiempoPreparacion"].toInt();
    preparacion = json["preparacion"].toString();

    // Cargar autor
    QJsonObject autorObject = json["autor"].toObject();
    autor.setNombre(autorObject["nombre"].toString());
    autor.setApellido(autorObject["apellido"].toString());

    // Cargar ingredientes
    QJsonArray ingredientesArray = json["ingredientes"].toArray();
    for (const QJsonValue &ingValue : ingredientesArray) {
        QJsonObject ingredienteObject = ingValue.toObject();
        Ingrediente* ingrediente = new Ingrediente;
        ingrediente->setNombre(ingredienteObject["nombre"].toString());
        ingrediente->setCantidad(ingredienteObject["cantidad"].toDouble());
        int unidadInt = ingredienteObject["unidad"].toInt();
        ingrediente->setUnidad(static_cast<Ingrediente::UnidadMedida>(unidadInt));
        listaIngredientes.insertarIngrediente(ingrediente);
    }
}
