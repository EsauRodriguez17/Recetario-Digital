#ifndef NOMBRE_HPP
#define NOMBRE_HPP
#include <QString>

class Nombre{
private:
    QString nombre;
    QString apellido;
public:
    Nombre();
    Nombre(const Nombre&);
    Nombre(const QString&, const QString&);

    void copiarTodo(const Nombre&);

    void setNombre(const QString&);
    void setApellido(const QString&);

    QString getNombre() const;
    QString getApellido() const;

    Nombre& operator=(const Nombre&);

    bool operator==(const Nombre&) const;
    bool operator!=(const Nombre&) const;
    bool operator<(const Nombre&) const;
    bool operator<=(const Nombre&) const;
    bool operator>(const Nombre&) const;
    bool operator>=(const Nombre&) const;

    QString toQstring() const;
};

#endif // NOMBRE_HPP
