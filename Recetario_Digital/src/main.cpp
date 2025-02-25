#include "mainwindow.hpp"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("Fusion");
    QFile file(":/style.qss");
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = file.readAll();
        a.setStyleSheet(styleSheet);
        file.close();
    } else {
        qWarning("No se pudo abrir el archivo de estilo.");
    }
    MainWindow w;
    w.show();
    return a.exec();
}
