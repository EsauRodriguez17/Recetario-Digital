QT       += core gui
 QT += uitools

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

INCLUDEPATH += include

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/ingredientWidget.cpp \
    src/ingrediente.cpp \
    src/listaIngredientes.cpp \
    src/listaRecetas.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/nombre.cpp \
    src/receta.cpp \
    src/recipeCard.cpp

HEADERS += \
    include/exception.hpp \
    include/ingredientWidget.hpp \
    include/ingrediente.hpp \
    include/listaIngredientes.hpp \
    include/listaRecetas.hpp \
    include/mainwindow.hpp \
    include/nombre.hpp \
    include/receta.hpp \
    include/recipeCard.hpp

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Recursos.qrc

DISTFILES +=
