#ifndef RECETA_HPP
#define RECETA_HPP

#include <QPixmap>
#include <QString>
#include <QTextStream>
#include <QJsonObject>
#include <QJsonArray>
#include <iostream>
#include "nombre.hpp"
#include "listaIngredientes.hpp"

class Receta{
public:
    enum class Categoria {
        DESAYUNO,
        COMIDA,
        CENA,
        NAVIDEÑO
    };

private:
    int id;
    QString nombre;
    QString preparacion;
    QString rutaImagen;
    QPixmap imagen;
    Categoria categoria;
    Nombre autor;
    int tiempoPreparacion;
    ListaIngredientes listaIngredientes;

public:
    Receta();
    Receta(const Receta&);
    ~Receta();

    void copiarTodo(const Receta&);

    void setNombre(const QString&);
    void setPreparacion(const QString&);
    void setCategoria(const Categoria&);
    void setAutor(const Nombre&);
    void setTiempoPreparacion(const int&);
    void setId(const int&);
    void setRutaImagen(const QString &newRutaImagen);
    void setImagen(const QPixmap&);

    void cargarImagen();

    void agregarIngrediente(Ingrediente *ingrediente);
    void eliminarTodosLosIngredientes();

    QString getNombre() const;
    QString getPreparacion() const;
    Categoria getCategoria() const;
    Nombre getAutor() const;
    int getTiempoPreparacion() const;
    int getId() const;
    ListaIngredientes& getListaIngredientes();
    QString getRutaImagen() const;
    const QPixmap& getImagen() const;

    Receta& operator=(const Receta&);

    bool operator==(const Receta& other) const;
    bool operator!=(const Receta& other) const;
    bool operator<(const Receta& other) const;
    bool operator>(const Receta& other) const;
    bool operator<=(const Receta& other) const;
    bool operator>=(const Receta& other) const;

    friend QTextStream& operator<<(QTextStream& , const Receta&);
    friend QTextStream& operator>>(QTextStream& , Receta& );

    QString getCategoriaToQstring() const;
    int getCategoriaToInt() const;

    static int compararPorNombre(const Receta&,const Receta&);
    static int compararPorTiempoPreparacion(const Receta&,const Receta&);

    QJsonObject toJson() const;
    void fromJson(const QJsonObject &);


};

#endif // RECETA_HPP
