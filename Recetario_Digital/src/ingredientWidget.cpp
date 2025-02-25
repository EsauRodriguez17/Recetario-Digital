#include "ingredientWidget.hpp"

IngredientWidget::IngredientWidget(QWidget *parent)   : QWidget{parent}{
    setupUi();
}

IngredientWidget::IngredientWidget(const Ingrediente& ingredient, QWidget *parent): QWidget{parent}{
    setupUi();
    setIngredient(ingredient);
}

void IngredientWidget::setupUi(){
    setMinimumSize(595,66);

    QFile file(":/ingredientWidget.ui");
    file.open(QFile::ReadOnly);
    QUiLoader loader;
    QWidget *widget = loader.load(&file, this);
    file.close();

    // Configurar el layout de IngredientCard
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(widget);

    // Acceder a los widgets
    itemIconLabel = widget->findChild<QLabel *>("itemIcon");
    lineEditNameIngredient = widget->findChild<QLineEdit *>("lineEditNameIngredient");
    quantityLineEdit = widget->findChild<QLineEdit *>("quantitylineEdit");
    comboBoxUnit = widget->findChild<QComboBox *>("comboBoxUnit");
    deleteButton = widget->findChild<QPushButton *>("deleteIngredientButton");

    deleteButton->setCursor(Qt::PointingHandCursor);

    QDoubleValidator *validator = new QDoubleValidator(0.01, 9999.99, 2, this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    quantityLineEdit->setValidator(validator);

    connect(deleteButton, &QPushButton::clicked, this, &IngredientWidget::deleteClicked);

}

void IngredientWidget::setIngredient(const Ingrediente & ingredient){
    lineEditNameIngredient->setText(ingredient.getNombre());
    quantityLineEdit->setText(QString::number(ingredient.getCantidad(), 'f', 2));
    int unitIndex = ingredient.unidadMedidaToint();
    if (unitIndex != -1) {
        comboBoxUnit->setCurrentIndex(unitIndex);
    }
}

QString IngredientWidget::getNombre() const {
    return lineEditNameIngredient->text();
}

double IngredientWidget::getCantidad() const {
    return quantityLineEdit->text().toDouble();
}

Ingrediente::UnidadMedida IngredientWidget::getUnidadMedida(){
    return static_cast<Ingrediente::UnidadMedida>(comboBoxUnit->currentIndex());
}
