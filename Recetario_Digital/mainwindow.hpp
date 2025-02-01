#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QMessageBox>
#include <QIntValidator>
#include <QFileDialog>
#include <QTimer>
#include <QScrollBar>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QBuffer>

#include "recipeCard.hpp"
#include "ingredientWidget.hpp"
#include "ingrediente.hpp"
#include "listaRecetas.hpp"
#include "receta.hpp"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int lastId;
    ListaRecetas listaRecetas;
    QVBoxLayout *ingredientsLayout;
    QHBoxLayout *lastRecipesLayout;
    QGridLayout *recipesCardsLayout;
    int row = 0;
    int col = 0;
    const int maxColumns = 3;

    const int homePage=0;
    const int recipesPage=1;
    const int addRecipePage=2;
    const int viewRecipePage=3;

    QTimer *scrollTimer;
    int scrollPosition = 0;

    //Inicializacion
    void initializeImagesDirectory();
    void setupRecipesCardsSection();
    void setupIngredientsSection();
    void setupValidators();
    void setupConnections();
    void setupLastRecipesSection();
    void setupAutoScroll();

    //Manejo de las recetas
    void agregarReceta();
    void modificarReceta();
    void agregarIngredientesReceta(Receta *);

    //Manejo de widgets para mostrar recetas e ingredientes en la interfaz
    void clearRecipeCards();
    void createRecipesCards();
    void clearLastRecipesCardsSection();
    void createLastRecipesCards();
    void addRecipeCardWidget(Receta *);
    void addIngredientWidget();
    void clearIngredientWidgets();
    void actualizarRecipeCardWidgets();
    void filtrarPorCategoria(QString);

    //Utilidades
    void desactivarBotonesNavBar();
    void activarBotonesNavBar();
    void setCursorPointerForAllButtons();
    void autoScrollLastRecipesArea();
    void pauseAutoScroll();
    void resumeAutoScroll();
    void stopAutoScroll();

    bool validarCamposAddRecipePage();
    void limpiarCamposAddRecipePage();
    void llenarCamposAddRecipePage(Receta&);

    void llenarCamposViewRecipePage(Receta *);
    void limpiarCamposViewRecipePage();

    //Cargar y guardar las recetas al disco
    void guardarRecetas();
    void cargarRecetas();
protected:
    void closeEvent(QCloseEvent *event) override;

//Manejo de eventos de la interfaz
public slots:
    void onModifyRecipeClicked(RecipeCard *);
    void onDeleteRecipeClicked(RecipeCard *);
    void onViewRecipe(RecipeCard *);
    void onSortChanged(int);
    void onFilterChanged(int);
    void onSearchButtonClicked();
    void onTextChanged(const QString&);
    void onClearButtonClicked();
    void onReturnButtonClicked();
    void onPageChanged(int);

private slots:
    void onHomeButtonClicked();
    void onRecipesButtonClicked();
    void onAddRecipeButtonClicked();
    void onDeleteAllRecipesButtonClicked();
    void onCancelButtonClicked();
    void onConfirmButtonClicked();
    void onUploadPhotoButtonClicked();
    void onDeleteAllIngredientsButtonClicked();
};
#endif // MAINWINDOW_HPP
