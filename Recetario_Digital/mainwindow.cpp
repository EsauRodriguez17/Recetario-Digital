#include "mainwindow.hpp"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    this->setWindowTitle("Recetario Digital");
    setFixedSize(1080, 760);
    ui->homeButton->setChecked(true);
    this->lastId=0;
    ui->messageWidget->setVisible(false);

    initializeImagesDirectory();
    cargarRecetas();

    setupLastRecipesSection();
    setupIngredientsSection();
    setupRecipesCardsSection();
    setCursorPointerForAllButtons();
    setupValidators();
    setupConnections();
    ui->pages->setCurrentIndex(homePage);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::initializeImagesDirectory() {
    QString imagesDir = QDir::currentPath() + "/imagenes";
    QDir dir(imagesDir);
    if (!dir.exists()) {
        dir.mkpath(".");
        qDebug() << "Carpeta de imágenes creada en:" << imagesDir;
    } else {
        qDebug() << "La carpeta de imágenes ya existe en:" << imagesDir;
    }


    QString recetasFile = QDir::currentPath() + "/recetas.json";
    QFile file(recetasFile);

    // Verificar y crear el archivo recetas.json si no existe
    if (!file.exists()) {
        if (file.open(QIODevice::WriteOnly)) {
            file.close();
            qDebug() << "Archivo recetas.json creado en:" << recetasFile;
        } else {
            qDebug() << "Error al crear el archivo recetas.json en:" << recetasFile;
        }
    } else {
        qDebug() << "El archivo recetas.json ya existe en:" << recetasFile;
    }
}

void MainWindow::setupRecipesCardsSection() {
    QWidget *recipesCardsContainer = new QWidget();
    recipesCardsLayout = new QGridLayout(recipesCardsContainer);
    ui->recipesArea->setWidget(recipesCardsContainer);
    ui->recipesArea->setWidgetResizable(true);

    createRecipesCards();
}

void MainWindow::setupIngredientsSection() {
    QWidget *ingredientsContainer = new QWidget();
    ingredientsLayout = new QVBoxLayout(ingredientsContainer);
    ingredientsContainer->setLayout(ingredientsLayout);
    ui->ingredientsArea->setWidget(ingredientsContainer);
    ui->ingredientsArea->setWidgetResizable(true);

    connect(ui->addIngredientButton, &QPushButton::clicked, this, [this]() {
        addIngredientWidget();
    });
}

void MainWindow::setupValidators() {
    QIntValidator *validator = new QIntValidator(1, std::numeric_limits<int>::max(), this);
    ui->lineEditDuration->setValidator(validator);

}

void MainWindow::setupConnections(){

    connect(ui->homeButton,&QPushButton::clicked, this, &MainWindow::onHomeButtonClicked);
    connect(ui->recipesButton,&QPushButton::clicked, this, &MainWindow::onRecipesButtonClicked);

    connect(ui->addRecipeButton,&QPushButton::clicked, this, &MainWindow::onAddRecipeButtonClicked);
    connect(ui->deleteAllRecipesButton,&QPushButton::clicked, this, &MainWindow::onDeleteAllRecipesButtonClicked);

    connect(ui->cancelButton,&QPushButton::clicked, this, &MainWindow::onCancelButtonClicked);
    connect(ui->confirmButton,&QPushButton::clicked, this, &MainWindow::onConfirmButtonClicked);

    connect(ui->uploadPhotoButton,&QPushButton::clicked, this, &MainWindow::onUploadPhotoButtonClicked);
    connect(ui->deleteAllIngredientsButton,&QPushButton::clicked, this, &MainWindow::onDeleteAllIngredientsButtonClicked);

    ui->comboBoxSort->addItem("--Selecciona--");
    ui->comboBoxSort->setItemData(0, true, Qt::UserRole-1);

    // Agregar las opciones de ordenamiento
    ui->comboBoxSort->addItem("Nombre");
    ui->comboBoxSort->addItem("Tiempo de Preparacion");
    connect(ui->comboBoxSort, &QComboBox::currentIndexChanged, this, &MainWindow::onSortChanged);
    ui->comboBoxSort->setCurrentIndex(0);

    //Agregar las opciones de filtrado
    ui->comboBoxFilter->addItem("Todas");
    ui->comboBoxFilter->addItem("Desayuno");
    ui->comboBoxFilter->addItem("Comida");
    ui->comboBoxFilter->addItem("Cena");
    ui->comboBoxFilter->addItem("Navideño");
    connect(ui->comboBoxFilter,&QComboBox::currentIndexChanged,this,&MainWindow::onFilterChanged);
    ui->comboBoxFilter->setCurrentIndex(0);

    connect(ui->searchRecipeLineEdit, &QLineEdit::returnPressed, this, &MainWindow::onSearchButtonClicked);

    connect(ui->searchRecipeButton, &QPushButton::clicked, this, &MainWindow::onSearchButtonClicked);

    connect(ui->searchRecipeLineEdit, &QLineEdit::textChanged, this, &MainWindow::onTextChanged);
    connect(ui->clearSearchLineEditButton, &QPushButton::clicked, this, &MainWindow::onClearButtonClicked);

    ui->clearSearchLineEditButton->setVisible(false);

    connect(ui->exploreRecipesButton,&QPushButton::clicked, this, &MainWindow::onRecipesButtonClicked);
    connect(ui->returnButton,&QPushButton::clicked, this, &MainWindow::onReturnButtonClicked);

    connect(ui->pages, &QStackedWidget::currentChanged, this, &MainWindow::onPageChanged);

}

void MainWindow::setupLastRecipesSection(){
    QWidget *lastRecipesContainer = new QWidget();
    lastRecipesLayout = new QHBoxLayout(lastRecipesContainer);
    lastRecipesLayout->setSpacing(10);
    lastRecipesLayout->setContentsMargins(10, 0, 10, 0);
    lastRecipesLayout->setAlignment(Qt::AlignVCenter);
    ui->lastRecipesArea->setWidget(lastRecipesContainer);
    ui->lastRecipesArea->setWidgetResizable(true);

    createLastRecipesCards();
    setupAutoScroll();


}

void MainWindow::setupAutoScroll() {
    scrollTimer = new QTimer(this);
    connect(scrollTimer, &QTimer::timeout, this, &MainWindow::autoScrollLastRecipesArea);

    QScrollBar *scrollBar = ui->lastRecipesArea->horizontalScrollBar();
    connect(scrollBar, &QScrollBar::sliderPressed, this, &MainWindow::pauseAutoScroll);
    connect(scrollBar, &QScrollBar::sliderReleased, this, &MainWindow::resumeAutoScroll);

    scrollTimer->start(46);
}

void MainWindow::autoScrollLastRecipesArea() {
    QScrollBar *scrollBar = ui->lastRecipesArea->horizontalScrollBar();

    scrollPosition += 1;

    if (scrollPosition >= scrollBar->maximum()) {
        scrollPosition = scrollBar->minimum();
    }

    scrollBar->setValue(scrollPosition);
}

void MainWindow::pauseAutoScroll() {
    if (scrollTimer->isActive()) {
        scrollTimer->stop();
    }
}

void MainWindow::resumeAutoScroll() {
    QTimer::singleShot(2000, this, [this]() {
        if (!scrollTimer->isActive()) {
            scrollTimer->start(46);
        }
    });
}

void MainWindow::stopAutoScroll() {
    if (scrollTimer) {
        scrollTimer->stop();
    }
}

void MainWindow::agregarReceta(){
    Receta *nuevaReceta=new Receta;

    if(nuevaReceta==nullptr){
        QMessageBox::critical(this,"Error","Error de memoria: no se pudo reservar memoria para la receta.",QMessageBox::Ok);
    }

    nuevaReceta->setNombre(ui->lineEditName->text());
    nuevaReceta->setCategoria(static_cast<Receta::Categoria>(ui->comboBoxCategory->currentIndex()));
    nuevaReceta->setTiempoPreparacion(ui->lineEditDuration->text().toInt());
    Nombre autorReceta(ui->lineEditAutorFirstName->text(),ui->lineEditAutorLastName->text());
    nuevaReceta->setAutor(autorReceta);
    QString sourcePath = ui->uploadPhotoButton->property("imagePath").toString();
    QString imagesDir = QDir::currentPath() + "/imagenes";
    QString destinationPath = imagesDir + "/" + QFileInfo(sourcePath).fileName(); // Nueva ruta

    // Copiar la imagen a la carpeta de imágenes
    if (QFile::copy(sourcePath, destinationPath)) {
        nuevaReceta->setRutaImagen(destinationPath);
        qDebug() << "Imagen copiada a:" << destinationPath;
    } else {
        qDebug() << "Error al copiar la imagen.";
    }
    nuevaReceta->setPreparacion(ui->instructionsText->toPlainText());

    agregarIngredientesReceta(nuevaReceta);

    try {
        listaRecetas.agregarReceta(nuevaReceta,listaRecetas.getUltimaPosicion());
    } catch (const Exception& e) {
        QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
    }

    addRecipeCardWidget(nuevaReceta);

    qDebug()<<listaRecetas.getUltimaPosicion();
    qDebug()<<listaRecetas.getSize();
    qDebug()<< "El tamaño del puntero a receta es: " << sizeof(nuevaReceta) << " bytes.";
    qDebug()<< "El tamaño del objeto receta al que apunta es: " << sizeof(*nuevaReceta) << " bytes.";

}


void MainWindow::modificarReceta(){
    RecipeCard *recipeCard=ui->confirmButton->property("recipePointer").value<RecipeCard*>();
    Receta *receta=recipeCard->getRecetaAsociada();

    if (receta->getNombre() != ui->lineEditName->text()) {
        receta->setNombre(ui->lineEditName->text());
    }

    int nuevaCategoria = ui->comboBoxCategory->currentIndex();
    if (receta->getCategoriaToInt() != nuevaCategoria) {
        receta->setCategoria(static_cast<Receta::Categoria>(nuevaCategoria));
    }

    int nuevoTiempoPreparacion = ui->lineEditDuration->text().toInt();
    if (receta->getTiempoPreparacion() != nuevoTiempoPreparacion) {
        receta->setTiempoPreparacion(nuevoTiempoPreparacion);
    }

    Nombre nuevoAutor(ui->lineEditAutorFirstName->text(), ui->lineEditAutorLastName->text());
    if (receta->getAutor() != nuevoAutor) {
        receta->setAutor(nuevoAutor);
    }

    // Verificar si se ha cambiado la imagen
    QString sourcePath = ui->uploadPhotoButton->property("imagePath").toString();
    QString currentImagePath = receta->getRutaImagen();

    if (sourcePath != currentImagePath) {
        QString imagesDir = QDir::currentPath() + "/imagenes";
        QString destinationPath = imagesDir + "/" + QFileInfo(sourcePath).fileName();

        // Eliminar la imagen antigua si existe
        if (!currentImagePath.isEmpty() && QFile::exists(currentImagePath)) {
            QFile::remove(currentImagePath); // Eliminar archivo
            qDebug() << "Imagen antigua eliminada:" << currentImagePath;
        }

        if (QFile::copy(sourcePath, destinationPath)) {
            receta->setRutaImagen(destinationPath);
            qDebug() << "Imagen copiada a:" << destinationPath;
        } else {
            qDebug() << "Error al copiar la nueva imagen.";
        }
    }

    if (receta->getPreparacion() != ui->instructionsText->toPlainText()) {
        receta->setPreparacion(ui->instructionsText->toPlainText());
    }

    receta->eliminarTodosLosIngredientes();
    agregarIngredientesReceta(receta);

    recipeCard->actualizarVista();

}


void MainWindow::agregarIngredientesReceta(Receta *receta){
    for(int i=0;i< ingredientsLayout->count();i++){
        QWidget *widget= ingredientsLayout->itemAt(i)->widget();

        IngredientWidget *ingredientWidget=qobject_cast<IngredientWidget*>(widget);
        if(ingredientWidget){
            QString nombre=ingredientWidget->getNombre();
            float cantidad=ingredientWidget->getCantidad();
            Ingrediente::UnidadMedida unidad=ingredientWidget->getUnidadMedida();

            Ingrediente *nuevoIngrediente=new Ingrediente(nombre,cantidad,unidad);
            receta->agregarIngrediente(nuevoIngrediente);

            qDebug()<< "El tamaño del puntero a Ingrediente es: " << sizeof(nuevoIngrediente) << " bytes.";
            qDebug()<< "El tamaño del objeto Ingrediente  al que apunta es: " << sizeof(*nuevoIngrediente) << " bytes.";
        }

    }
}

void MainWindow::clearRecipeCards(){
    while (QLayoutItem* item = recipesCardsLayout->takeAt(0)) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }
    row=0;
    col=0;
}

void MainWindow::createRecipesCards(){
    if (listaRecetas.getSize() > 0) {
        ListaRecetas::posicion* posActual = listaRecetas.getPrimeraPosicion();

        while (posActual != nullptr) {
            addRecipeCardWidget(posActual->getRecetaPtr());
            posActual = posActual->getSiguiente();
        }
    }
}

void MainWindow::clearLastRecipesCardsSection() {
    while (QLayoutItem* item = lastRecipesLayout->takeAt(0)) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }
}

void MainWindow::createLastRecipesCards(){
    ListaRecetas::posicion *posActual=listaRecetas.getUltimaPosicion();

    int i=0;
    while(i< 6 && posActual !=nullptr){
        RecipeCard *recetaCard = new RecipeCard(posActual->getRecetaPtr());
        recetaCard->setFixedWidth(400);
        recetaCard->desactivarBotones();
        connect(recetaCard, &RecipeCard::imageClicked, this, [this, recetaCard]() {
            onViewRecipe(recetaCard);
        });

        recetaCard->setFixedWidth(330);
        posActual=posActual->getAnterior();

        lastRecipesLayout->addWidget(recetaCard);

        i++;
    }
}

void MainWindow::addRecipeCardWidget(Receta *receta){
        // Crear una nueva RecipeCard con la receta
        RecipeCard *recetaCard = new RecipeCard(receta);

        recipesCardsLayout->addWidget(recetaCard,row,col);
        col++;
        if (col >= maxColumns) {
            col = 0;
            row++;
        }

        connect(recetaCard, &RecipeCard::modifyClicked, this, [this, recetaCard]() {
            onModifyRecipeClicked(recetaCard);
        });
        connect(recetaCard, &RecipeCard::deleteClicked, this, [this, recetaCard]() {
            onDeleteRecipeClicked(recetaCard);
        });
        connect(recetaCard, &RecipeCard::imageClicked, this, [this, recetaCard]() {
            onViewRecipe(recetaCard);
        });

        qDebug()<< "El tamaño del puntero a recetaCard es: " << sizeof(recetaCard) << " bytes.";
        qDebug()<< "El tamaño del objeto recetaCard al que apunta es: " << sizeof(*recetaCard) << " bytes.";

}


void MainWindow::addIngredientWidget(){
    IngredientWidget *newIngredientWidget=new IngredientWidget;
    connect(newIngredientWidget, &IngredientWidget::deleteClicked, this, [newIngredientWidget, this]() {
        ingredientsLayout->removeWidget(newIngredientWidget);  // Elimina el widget del layout
        newIngredientWidget->deleteLater();  // Destruye el widget
    });
    ingredientsLayout->addWidget(newIngredientWidget);
    qDebug()<< "El tamaño del puntero a IngredientWidget vacio es: " << sizeof(newIngredientWidget) << " bytes.";
    qDebug()<< "El tamaño del objeto IngredientWidget vacio al que apunta es: " << sizeof(*newIngredientWidget) << " bytes.";
}

void MainWindow::clearIngredientWidgets(){
    while (QLayoutItem* item = ingredientsLayout->takeAt(0)) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }
}

void MainWindow::actualizarRecipeCardWidgets(){
    ListaRecetas::posicion* posActual = listaRecetas.getPrimeraPosicion();
    int i = 0;

    while (posActual != nullptr && i < recipesCardsLayout->count()) {
        QWidget* widget = recipesCardsLayout->itemAt(i)->widget();
        RecipeCard* recipeCardWidget = qobject_cast<RecipeCard*>(widget);

        if (recipeCardWidget) {
            recipeCardWidget->setRecetaAsociada(posActual->getRecetaPtr());
            recipeCardWidget->actualizarVista();
        }

        posActual = posActual->getSiguiente();
        i++;
    }
}


void MainWindow::desactivarBotonesNavBar(){
    ui->homeButton->setEnabled(false);
    ui->recipesButton->setEnabled(false);
}


void MainWindow::activarBotonesNavBar(){
    ui->homeButton->setEnabled(true);
    ui->recipesButton->setEnabled(true);
}

void MainWindow::setCursorPointerForAllButtons(){
    QList<QWidget *> widgets = this->findChildren<QWidget *>();
    for (QWidget *widget : widgets) {
        // Verifica si el widget es un QPushButton
        QPushButton *button = qobject_cast<QPushButton *>(widget);
        if (button) {
            button->setCursor(Qt::PointingHandCursor);
        }
    }
}

bool MainWindow::validarCamposAddRecipePage(){
    QList<QLineEdit*> camposTexto{
        ui->lineEditName,
        ui->lineEditDuration,
        ui->lineEditAutorFirstName,
        ui->lineEditAutorLastName
    };

    QStringList camposFaltantes;
    bool camposVacios=false;

    for (auto campo : camposTexto) {
        if (campo->text().isEmpty()) {
            camposVacios=true;
            break;
        }
    }

    if(camposVacios){
        camposFaltantes << "Hay campos de texto vacios en la informacion general";
    }

    if(ui->uploadPhotoImage->pixmap().isNull()){
        camposFaltantes << "Debes agregar una imagen del platillo";
    }

    if (ui->instructionsText->toPlainText().isEmpty()) {
        camposFaltantes << "Debes agregar el procedimiento";
    }

    bool ingredientesValidos=true;
    for(int i=0;i<ingredientsLayout->count();i++){
        QWidget *widget =ingredientsLayout->itemAt(i)->widget();

        if(IngredientWidget *ingredientWidget=qobject_cast<IngredientWidget *>(widget)){
            if(ingredientWidget->getNombre().isEmpty() || ingredientWidget->getCantidad() <0.001 ){
                ingredientesValidos=false;
                break;
            }
        }
    }

    if(!ingredientesValidos){
        camposFaltantes << "Debes llenar todos los campos de los ingredientes";
    }

    if (!camposFaltantes.isEmpty()) {
        QString mensaje =camposFaltantes.join("\n");
        QMessageBox::warning(this, "Campos Vacíos", mensaje);
        return false;
    }

    return true;

}

void MainWindow::limpiarCamposAddRecipePage(){
    ui->lineEditName->clear();
    ui->lineEditDuration->clear();
    ui->comboBoxCategory->setCurrentIndex(0);
    ui->lineEditAutorFirstName->clear();
    ui->lineEditAutorLastName->clear();
    ui->instructionsText->clear();
    ui->uploadPhotoImage->clear();
    clearIngredientWidgets();
    ui->confirmButton->setProperty("recipePointer", QVariant());
    ui->uploadPhotoButton->setProperty("imagePath", QVariant());
}


void MainWindow::llenarCamposAddRecipePage(Receta& recipe){
    ui->lineEditName->setText(recipe.getNombre());
    ui->lineEditDuration->setText(QString::number(recipe.getTiempoPreparacion()));
    ui->comboBoxCategory->setCurrentIndex(recipe.getCategoriaToInt());
    ui->lineEditAutorFirstName->setText(recipe.getAutor().getNombre());
    ui->lineEditAutorLastName->setText(recipe.getAutor().getApellido());

    QString fileName=recipe.getRutaImagen();
    ui->uploadPhotoButton->setProperty("imagePath",fileName);

    if(!fileName.isEmpty()){
        ui->uploadPhotoImage->setPixmap(recipe.getImagen());
        ui->uploadPhotoImage->setScaledContents(true);
    }

    ui->instructionsText->setText(recipe.getPreparacion());

    ListaIngredientes& lista=recipe.getListaIngredientes();

    ListaIngredientes::posicion *posActual=lista.getPrimeraPosicion();

    while(posActual != nullptr){
        Ingrediente *in=lista.recuperarIngrediente(posActual);
        IngredientWidget *newIngredientWidget=new IngredientWidget(*in);
        connect(newIngredientWidget, &IngredientWidget::deleteClicked, this, [newIngredientWidget, this]() {
            ingredientsLayout->removeWidget(newIngredientWidget);  // Elimina el widget del layout
            newIngredientWidget->deleteLater();  // Destruye el widget
        });
        ingredientsLayout->addWidget(newIngredientWidget);
        posActual=posActual->getSiguiente();
    }
}

void MainWindow::llenarCamposViewRecipePage(Receta * receta){
    ui->tittleViewRecipe->setText(receta->getNombre());

    if (!receta->getImagen().isNull()) {
        ui->imageViewRecipe->setPixmap(receta->getImagen());
    } else {
        ui->imageViewRecipe->setText("Sin Imagen");
    }

    ui->Procedimiento->setText(receta->getPreparacion());
    ui->Ingredientes->setText(receta->getListaIngredientes().toQstring());
    ui->tiempoPreparacion->setText(QString::number(receta->getTiempoPreparacion())+" Minutos");
    ui->autor->setText(receta->getAutor().toQstring());
    ui->categoria->setText(receta->getCategoriaToQstring());
}

void MainWindow::limpiarCamposViewRecipePage(){
    ui->tittleViewRecipe->clear();
    ui->imageViewRecipe->setPixmap(QPixmap());
    ui->Procedimiento->clear();
    ui->Ingredientes->clear();
    ui->tiempoPreparacion->clear();
    ui->autor->clear();
    ui->categoria->clear();
}

void MainWindow::onModifyRecipeClicked(RecipeCard *recipeCard) {
    Receta *recipe= recipeCard->getRecetaAsociada();

    ui->recipesButton->setChecked(false);
    ui->pages->setCurrentIndex(addRecipePage);
    ui->confirmButton->setText("Guardar Cambios");
    ui->confirmButton->setProperty("recipePointer", QVariant::fromValue(recipeCard));

    ui->uploadPhotoButton->setText("Cambiar Imagen");
    ui->uploadPhotoButton->setStyleSheet("color: black; border-bottom: 2px solid blue;");

    desactivarBotonesNavBar();
    llenarCamposAddRecipePage(*recipe);
}


void MainWindow::onDeleteRecipeClicked(RecipeCard *recipeCard) {
    Receta* recipe=recipeCard->getRecetaAsociada();
    ListaRecetas::posicion *pos=listaRecetas.localiza(recipe);

    if(pos !=nullptr){
        try {
            listaRecetas.eliminarReceta(pos);

            clearRecipeCards();
            createRecipesCards();

            qDebug()<<"Eliminada Correctamente";
            qDebug()<<listaRecetas.getUltimaPosicion();
            qDebug()<<listaRecetas.getSize();
        } catch (const std::exception& e) {
            QMessageBox::warning(this, "Error", e.what());
        }
    }
    else{
        qDebug()<<"No se pudo localizar la receta";
    }

}

void MainWindow::onViewRecipe(RecipeCard *recipeCard){
    ui->returnButton->setProperty("previousPage",ui->pages->currentIndex());

    Receta* recipe=recipeCard->getRecetaAsociada();
    ui->pages->setCurrentIndex(viewRecipePage);
    llenarCamposViewRecipePage(recipe);
}

void MainWindow::onSortChanged(int index){
    if(listaRecetas.vacia()){return;}

    if(index==1){
        listaRecetas.quickSort(Receta::compararPorNombre);
    }
    else{
        listaRecetas.quickSort(Receta::compararPorTiempoPreparacion);
    }

    actualizarRecipeCardWidgets();
}

void MainWindow::onFilterChanged(int){

    if(recipesCardsLayout->count()>0){
        QString categoriaSeleccionada = ui->comboBoxFilter->currentText();

        clearRecipeCards();
        if(categoriaSeleccionada == "Todas"){
            createRecipesCards();
        }

        filtrarPorCategoria(categoriaSeleccionada);

    }

}

void MainWindow::onSearchButtonClicked(){
    qDebug()<<"Busqueda realizada";

    QString search=ui->searchRecipeLineEdit->text().trimmed();
    if(!search.isEmpty()){
        Receta * objetivo=new Receta;
        objetivo->setNombre(search);

        ListaRecetas::posicion* pos=listaRecetas.busquedaLineal(objetivo,Receta::compararPorNombre);
        if(pos!= nullptr){
            Receta *receta=listaRecetas.recuperarReceta(pos);
            llenarCamposViewRecipePage(receta);
            ui->pages->setCurrentIndex(viewRecipePage);
        }
        else{
            ui->messageWidget->setVisible(true);

            QTimer::singleShot(2000, this, [this]() {
                ui->messageWidget->setVisible(false);
            });
        }
        delete objetivo;
    }

}

void MainWindow::onTextChanged(const QString &text){
    ui->clearSearchLineEditButton->setVisible(!text.isEmpty());
}

void MainWindow::onClearButtonClicked(){
    ui->searchRecipeLineEdit->clear();
    ui->clearSearchLineEditButton->setVisible(false);
}
void MainWindow::filtrarPorCategoria(QString categoriaSeleccionada){
    if (listaRecetas.getSize() > 0) {
        ListaRecetas::posicion* posActual = listaRecetas.getPrimeraPosicion();

        while (posActual != nullptr) {
            if (posActual->getRecetaPtr()->getCategoriaToQstring() == categoriaSeleccionada) {
                addRecipeCardWidget(posActual->getRecetaPtr());
            }

            posActual = posActual->getSiguiente();
        }
    }
}

void MainWindow::onHomeButtonClicked(){
    ui->pages->setCurrentIndex(homePage);
    ui->recipesButton->setChecked(false);
    ui->homeButton->setChecked(true);
}

void MainWindow::onRecipesButtonClicked(){
    ui->pages->setCurrentIndex(recipesPage);
    ui->homeButton->setChecked(false);
    ui->recipesButton->setChecked(true);
}

void MainWindow::onAddRecipeButtonClicked(){
    ui->recipesButton->setChecked(false);
    desactivarBotonesNavBar();
    ui->pages->setCurrentIndex(addRecipePage);
    ui->confirmButton->setText("Agregar Receta");

}

void MainWindow::onDeleteAllRecipesButtonClicked(){
    if(recipesCardsLayout->count() == 0){
        return;
    }

    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(this, "Eliminar todas las recetas",
                                  "¿Estás seguro de que deseas eliminar todas las recetas?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        listaRecetas.anular();
        clearRecipeCards();
    }
}

void MainWindow::onCancelButtonClicked(){
    activarBotonesNavBar();
    limpiarCamposAddRecipePage();
    ui->pages->setCurrentIndex(recipesPage);
    ui->recipesButton->setChecked(true);
    ui->uploadPhotoButton->setStyleSheet("color: rgb(240, 128, 0); border-bottom: 2px solid rgb(240, 128, 0);");
}

void MainWindow::onConfirmButtonClicked(){
    if(!validarCamposAddRecipePage()){
        return;
    }

    if(ui->confirmButton->text()=="Agregar Receta"){
        agregarReceta();
    }
    else{
        modificarReceta();
        ui->uploadPhotoButton->setStyleSheet("color: rgb(240, 128, 0); border-bottom: 2px solid rgb(240, 128, 0);");
    }

    limpiarCamposAddRecipePage();
    activarBotonesNavBar();
    ui->pages->setCurrentIndex(recipesPage);
    ui->recipesButton->setChecked(true);
}


void MainWindow::onUploadPhotoButtonClicked(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Seleccionar Imagen"),
                                                    "", tr("Imágenes (*.png *.jpg *.jpeg *.bmp *.gif);;Todos los archivos (*)"));

    if (!fileName.isEmpty()) {
        QPixmap image(fileName);
        ui->uploadPhotoImage->setPixmap(image);
        ui->uploadPhotoImage->setScaledContents(true);
        if (image.isNull()) {
            QMessageBox::warning(this, tr("Error"), tr("No se pudo cargar la imagen."));
            return;
        }
    }

    ui->uploadPhotoButton->setProperty("imagePath", fileName);

}

void MainWindow::onDeleteAllIngredientsButtonClicked(){
    if(ingredientsLayout->count() == 0){
        return;
    }

    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(this, "Eliminar todos los ingredientes",
                                  "¿Estás seguro de que deseas eliminar todos las ingredientes?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        clearIngredientWidgets();
    }
}

void MainWindow::onReturnButtonClicked(){
    ui->pages->setCurrentIndex(ui->returnButton->property("previousPage").toInt());
    limpiarCamposViewRecipePage();
}

void MainWindow::onPageChanged(int index){
    qDebug()<<"pagina cambiada:";
    if(index == homePage){
        qDebug()<<"Home page";
        createLastRecipesCards();
        setupAutoScroll();
    }
    else{
        qDebug()<<"otra pagina";
        clearLastRecipesCardsSection();
        stopAutoScroll();
    }
}

void MainWindow::guardarRecetas() {
    QString datosRecetas = QDir::currentPath() + "/recetas.json";

    try{
        listaRecetas.guardarRecetas(datosRecetas);
        QMessageBox::information(this, "Guardado", "Las recetas han sido guardadas exitosamente.");
    }catch (const Exception& e) {
        QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
    }
}

void MainWindow::cargarRecetas() {
    QString datosRecetas = QDir::currentPath() + "/recetas.json";

    try{
        listaRecetas.cargarRecetas(datosRecetas);
        QMessageBox::information(this, "Guardado", "Las recetas han sido cargadas exitosamente.");
    }catch (const Exception& e) {
        QMessageBox::warning(this, "Error", QString::fromStdString(e.what())+"\n"
        "asegurate que el archivo recetas.json\n se encuentre en la carpeta: " +QDir::currentPath());
    }
}


void MainWindow::closeEvent(QCloseEvent *event){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmar", "¿Deseas guardar las recetas antes de salir?",
                                  QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    if (reply == QMessageBox::Yes) {
        guardarRecetas();
    } else if (reply == QMessageBox::Cancel) {
        event->ignore();
        return;
    }

    event->accept();
}

