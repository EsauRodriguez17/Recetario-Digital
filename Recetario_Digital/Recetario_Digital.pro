QT       += core gui
 QT += uitools

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ingredientWidget.cpp \
    ingrediente.cpp \
    listaIngredientes.cpp \
    listaRecetas.cpp \
    main.cpp \
    mainwindow.cpp \
    nombre.cpp \
    receta.cpp \
    recipeCard.cpp

HEADERS += \
    exception.hpp \
    ingredientWidget.hpp \
    ingrediente.hpp \
    listaIngredientes.hpp \
    listaRecetas.hpp \
    mainwindow.hpp \
    nombre.hpp \
    receta.hpp \
    recipeCard.hpp

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Recursos.qrc

DISTFILES +=
