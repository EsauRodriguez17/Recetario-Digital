#include "nombre.hpp"

Nombre::Nombre() {}

Nombre::Nombre(const Nombre& otro) {
  copiarTodo(otro);
}

Nombre::Nombre(const QString& nombre, const QString& apellido) {
  this->nombre = nombre;
  this->apellido = apellido;
}

void Nombre::copiarTodo(const Nombre& otro) {
  this->nombre = otro.nombre;
  this->apellido = otro.apellido;
}

void Nombre::setNombre(const QString& nuevoNombre) {
  nombre = nuevoNombre;
}

void Nombre::setApellido(const QString& nuevoApellido) {
  apellido = nuevoApellido;
}

QString Nombre::getNombre() const {
  return nombre;
}

QString Nombre::getApellido() const {
  return apellido;
}

Nombre& Nombre::operator=(const Nombre& otro) {
  copiarTodo(otro);

  return *this;
}

bool Nombre::operator==(const Nombre& otro) const {
  return (nombre == otro.nombre && apellido == otro.apellido);
}

bool Nombre::operator!=(const Nombre& otro) const {
  return !(*this == otro);
}
bool Nombre::operator<(const Nombre& otro) const {
  if (apellido == otro.apellido) {
    return nombre < otro.nombre;
  }
  return apellido < otro.apellido;
}

bool Nombre::operator<=(const Nombre& otro) const {
  return (*this < otro || *this == otro);
}

bool Nombre::operator>(const Nombre& otro) const {
  return !(*this <= otro);
}

bool Nombre::operator>=(const Nombre& otro) const {
  return !(*this < otro);
}

QString Nombre::toQstring() const {
  return nombre + " " + apellido;
}
