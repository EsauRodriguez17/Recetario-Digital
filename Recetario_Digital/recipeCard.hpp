#ifndef RECIPECARD_H
#define RECIPECARD_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFile>
#include <QUiLoader>
#include <QMouseEvent>
#include <QPixmap>
#include "receta.hpp"

class RecipeCard : public QWidget{
    Q_OBJECT

public:
    explicit RecipeCard(Receta* ,QWidget *parent = nullptr);
    void setReceta(const Receta &receta);
    void actualizarVista();
    void setRecetaAsociada(Receta*);

    void desactivarBotones();

    Receta* getRecetaAsociada();

signals:
    void modifyClicked();
    void deleteClicked();
    void imageClicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QLabel *titleLabel;
    QLabel *categoryLabel;
    QLabel *timeLabel;
    QLabel *imageLabel;
    QPushButton *deleteButton;
    QPushButton *modifyButton;
    Receta *receta;

    void setupUi();
};

#endif // RECIPECARD_H
