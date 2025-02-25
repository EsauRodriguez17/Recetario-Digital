#include "recipeCard.hpp"

RecipeCard::RecipeCard(Receta* receta,QWidget *parent)    : QWidget{parent}{
    setMinimumSize(321, 265);
    setupUi();
    this->receta=receta;
    setReceta(*receta);

    connect(modifyButton, &QPushButton::clicked, this, &RecipeCard::modifyClicked);
    connect(deleteButton, &QPushButton::clicked, this, &RecipeCard::deleteClicked);

    modifyButton->setCursor(Qt::PointingHandCursor);
    deleteButton->setCursor(Qt::PointingHandCursor);
    imageLabel->setCursor(Qt::PointingHandCursor);

}

void RecipeCard::setupUi() {
    QFile file(":/recipeCard.ui");
    file.open(QFile::ReadOnly);
    QUiLoader loader;
    QWidget *widget = loader.load(&file, this);
    file.close();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(widget);

    titleLabel = widget->findChild<QLabel *>("tittle");
    categoryLabel = widget->findChild<QLabel *>("category");
    timeLabel = widget->findChild<QLabel *>("time");
    imageLabel = widget->findChild<QLabel *>("image");
    deleteButton = widget->findChild<QPushButton *>("deleteRecipeButton");
    modifyButton = widget->findChild<QPushButton *>("modifyRecipeButton");
}

void RecipeCard::setReceta(const Receta &receta) {
    QString nombreReceta = receta.getNombre();
    if (nombreReceta.length() > 19) {
        titleLabel->setText(nombreReceta.left(16) + "...");
    } else {
        titleLabel->setText(nombreReceta);
    }

    categoryLabel->setText(receta.getCategoriaToQstring());
    timeLabel->setText(QString::number(receta.getTiempoPreparacion()) + " min");

    if (!receta.getImagen().isNull()) {
        imageLabel->setScaledContents(true);
        imageLabel->setPixmap(receta.getImagen());
    } else {
        imageLabel->setText("Sin imagen");
    }

}

void RecipeCard::actualizarVista(){
    setReceta(*receta);
}

void RecipeCard::setRecetaAsociada(Receta*receta){
    this->receta=receta;
}

void RecipeCard::desactivarBotones(){
    modifyButton->setVisible(false);
    deleteButton->setVisible(false);
}

Receta *RecipeCard::getRecetaAsociada(){
    return receta;
}

void RecipeCard::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && imageLabel->geometry().contains(event->pos())) {
        emit imageClicked();
    }
    QWidget::mousePressEvent(event);
}
