#ifndef LISTAINGREDIENTES_H
#define LISTAINGREDIENTES_H

#include "ingrediente.hpp"
#include "exception.hpp"

class ListaIngredientes{
private:
    class Nodo {
    private:
        Ingrediente* ingrediente;
        Nodo* siguiente;

    public:
        Nodo();
        Nodo(Ingrediente*);
        Nodo(const Ingrediente&);

        Ingrediente* getIngredientePtr() const;
        Ingrediente getIngrediente() const;
        Nodo* getSiguiente() const;

        void setIngredientePtr(Ingrediente*);
        void setIngrediente(const Ingrediente&);
        void setSiguiente(Nodo*);
    };

    Nodo* ancla;

    int size;

    void copiarTodo(const ListaIngredientes&);

public:
    typedef ListaIngredientes::Nodo posicion;

    ListaIngredientes();
    ListaIngredientes(const ListaIngredientes&);
    ~ListaIngredientes();

    ListaIngredientes& operator=(const ListaIngredientes&);

    bool vacia() const;
    bool posicionValida(Nodo*) const;

    void insertarIngrediente(Ingrediente*);
    void eliminarIngrediente(Nodo*);

    Nodo* getPrimeraPosicion() const ;
    Nodo* getUltimaPosicion() const;
    Nodo*getPosicionPrevia(Nodo*) const;
    Nodo* getSiguientePosicion(Nodo*) const;

    Ingrediente* recuperarIngrediente(Nodo*);

    Nodo *busquedaLineal(const Ingrediente*,int (*cmp)(const Ingrediente&, const Ingrediente&)) const;
    Nodo *buscarPosicionOrdenada(const Ingrediente*) const;

    QString toQstring() ;
    void anular();

    int getSize() const;
};

#endif // LISTAINGREDIENTES_H
