#ifndef INGREDIENTE_HPP
#define INGREDIENTE_HPP

#include <QString>
#include <QTextStream>
#include <iostream>

class Ingrediente{
public:
    enum class UnidadMedida {
        GRAMOS,
        KILOGRAMOS,
        MILILITROS,
        LITROS,
        CUCHARADA,
        CUCHARADITA,
        TAZA,
        PIZCA,
        ONZA,
        LIBRA,
        LATA
    };

private:
    QString nombre;
    float cantidad;
    UnidadMedida unidad;

public:
    Ingrediente();
    Ingrediente(const Ingrediente&);
    Ingrediente(const QString&,const float&,const UnidadMedida&);

    void copiarTodo(const Ingrediente&);

    void setNombre(const QString&);
    void setCantidad(const float&);
    void setUnidad(const UnidadMedida&);

    QString getNombre() const;
    float getCantidad() const;
    UnidadMedida getUnidad() const;

    Ingrediente& operator=(const Ingrediente&);

    bool operator==(const Ingrediente& other) const;
    bool operator!=(const Ingrediente& other) const;
    bool operator<(const Ingrediente& other) const;
    bool operator>(const Ingrediente& other) const;
    bool operator<=(const Ingrediente& other) const;
    bool operator>=(const Ingrediente& other) const;

    friend QTextStream& operator<<(QTextStream& , const Ingrediente& );
    friend QTextStream& operator>>(QTextStream& , Ingrediente& e);

    QString unidadMedidaToQstring() const;
    QString toQstring();
    int unidadMedidaToint() const;
};

#endif // INGREDIENTE_HPP
