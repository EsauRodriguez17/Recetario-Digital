#include "ingrediente.hpp"

Ingrediente::Ingrediente() {}

Ingrediente::Ingrediente(const Ingrediente& otro){
    copiarTodo(otro);
}

Ingrediente::Ingrediente(const QString& nombre,const float& cantidad,const UnidadMedida& unidad){
    this->nombre=nombre;
    this->cantidad=cantidad;
    this->unidad=unidad;
}

void Ingrediente::copiarTodo(const Ingrediente& otro){
    this->nombre=otro.nombre;
    this->cantidad=otro.cantidad;
    this->unidad=otro.unidad;
}

void Ingrediente::setNombre(const QString & nuevoNombre){
    nombre=nuevoNombre;
}

void Ingrediente::setCantidad(const float & nuevaCantidad){
    cantidad=nuevaCantidad;
}

void Ingrediente::setUnidad(const UnidadMedida & nuevaUnidad){
    unidad=nuevaUnidad;
}

QString Ingrediente::getNombre() const{
    return nombre;
}

float Ingrediente::getCantidad() const{
    return cantidad;
}

Ingrediente::UnidadMedida Ingrediente::getUnidad() const{
    return unidad;

}

Ingrediente& Ingrediente::operator=(const Ingrediente& otro){
    copiarTodo(otro);

    return *this;
}

bool Ingrediente::operator==(const Ingrediente& other) const {
    return (nombre == other.nombre) &&
           (cantidad == other.cantidad) &&
           (unidad == other.unidad);
}

bool Ingrediente::operator!=(const Ingrediente& other) const {
    return !(*this == other);
}

bool Ingrediente::operator<(const Ingrediente& other) const {
    return nombre < other.nombre;
}

bool Ingrediente::operator>(const Ingrediente& other) const {
    return other < *this;
}

bool Ingrediente::operator<=(const Ingrediente& other) const {
    return !(*this > other);
}

bool Ingrediente::operator>=(const Ingrediente& other) const {
    return !(*this < other);
}

QTextStream& operator<<(QTextStream& os, const Ingrediente& ingrediente) {
    os << ingrediente.getNombre() << "|"
       << ingrediente.getCantidad() << "|"
       << static_cast<int>(ingrediente.getUnidad()) << "#";
    return os;
}

QTextStream& operator>>(QTextStream& is, Ingrediente& ingrediente) {
    QString nombre;
    float cantidad;
    int unidad;


    nombre = is.readLine('|');
    is >> cantidad;
    is.skipWhiteSpace();
    is >> unidad;


    ingrediente.setNombre(nombre);
    ingrediente.setCantidad(cantidad);
    ingrediente.setUnidad(static_cast<Ingrediente::UnidadMedida>(unidad));

    return is;
}

QString Ingrediente::unidadMedidaToQstring() const{
    switch (unidad) {
        case UnidadMedida::GRAMOS:       return "Gramos";
        case UnidadMedida::KILOGRAMOS:   return "Kilogramos";
        case UnidadMedida::MILILITROS:   return "Mililitros";
        case UnidadMedida::LITROS:       return "Litros";
        case UnidadMedida::CUCHARADA:    return "Cucharada";
        case UnidadMedida::CUCHARADITA:  return "Cucharadita";
        case UnidadMedida::TAZA:         return "Taza";
        case UnidadMedida::PIZCA:        return "Pizca";
        case UnidadMedida::ONZA:         return "Onza";
        case UnidadMedida::LIBRA:        return "Libra";
        case UnidadMedida::LATA:         return "Lata";
        default:                         return "Desconocido";
    }
}

QString Ingrediente::toQstring(){
    return QString::number(cantidad, 'f', 2) +" " + unidadMedidaToQstring()+" de " +nombre;
}

int Ingrediente::unidadMedidaToint() const{
    if (unidad >= UnidadMedida::GRAMOS && unidad <= UnidadMedida::LATA) {
        return static_cast<int>(unidad);
    }

    return -1;
}
