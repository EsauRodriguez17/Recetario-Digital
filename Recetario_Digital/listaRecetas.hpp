#ifndef LISTARECETAS_H
#define LISTARECETAS_H

#include "receta.hpp"
#include <QJsonDocument>
#include <QFile>
#include "exception.hpp"

class ListaRecetas{
private:
    class Nodo{
    private:
        Receta* receta;
        Nodo* anterior;
        Nodo* siguiente;

    public:
        Nodo();
        Nodo(Receta*);
        Nodo(const Receta&);

        ~Nodo();

        Receta* getRecetaPtr() const;
        Receta getReceta() const;
        Nodo* getAnterior() const;
        Nodo* getSiguiente() const;

        void setRecetaPtr(Receta*);
        void setReceta(const Receta&);
        void setAnterior(Nodo*);
        void setSiguiente(Nodo*);
    };

    Nodo* ancla;
    int size;

    void copiarTodo(const ListaRecetas& );

public:
    typedef ListaRecetas::Nodo posicion;

    ListaRecetas();
    ListaRecetas(const ListaRecetas& );
    ~ListaRecetas();

    ListaRecetas& operator=(const ListaRecetas& );

    void agregarReceta(Receta*,Nodo*);
    void eliminarReceta(Nodo*);

    Receta* recuperarReceta(Nodo*) const;


    bool vacia() const;
    bool posicionValida(Nodo*) const;
    int getSize() const;

    Nodo* getPrimeraPosicion() const;
    Nodo* getUltimaPosicion() const;
    Nodo* getPosicionPrevia(Nodo*) const;
    Nodo* getSiguientePosicion(Nodo* ) const;

    Nodo* localiza(Receta*);

    Nodo* busquedaLineal(const Receta* , int (*cmp)(const Receta&, const Receta&)) const;

    void quickSort(int (*cmp)(const Receta&, const Receta&));
    void quickSort(Nodo*, Nodo*,int (*cmp)(const Receta&, const Receta&));
    Nodo* partition(Nodo* left, Nodo* right, int (*cmp)(const Receta&, const Receta&));

    void swap(Nodo*, Nodo*);

    void guardarRecetas(const QString&);
    void cargarRecetas(const QString&);

    void anular();
};

#endif // LISTARECETAS_H
