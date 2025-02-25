#ifndef INGREDIENTWIDGET_H
#define INGREDIENTWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QFile>
#include <QUiLoader>
#include <QPixmap>
#include <QDoubleValidator>
#include "ingrediente.hpp"

class IngredientWidget : public QWidget{
    Q_OBJECT
public:
    explicit IngredientWidget(QWidget *parent = nullptr);
    explicit IngredientWidget(const Ingrediente&, QWidget *parent = nullptr);

    void setIngredient(const Ingrediente&);

    QString getNombre() const;
    double getCantidad() const;
    Ingrediente::UnidadMedida getUnidadMedida();

signals:
    void deleteClicked();

private:
    QLabel *itemIconLabel;
    QLineEdit *lineEditNameIngredient;
    QLineEdit *quantityLineEdit;
    QComboBox *comboBoxUnit;
    QPushButton *deleteButton;

    void setupUi();
};

#endif // INGREDIENTWIDGET_H
