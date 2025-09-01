#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include "UI/headers/catalogviewer.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    qDebug() << "Avvio applicazione...";

    try {
        qDebug() << "Creazione CatalogViewer...";
        CatalogViewer viewer;

        qDebug() << "Impostazioni finestra...";
        viewer.setWindowTitle("Catalogo Nails");
        viewer.resize(1000, 600);

        qDebug() << "Visualizzazione finestra...";
        viewer.show();

        qDebug() << "Avvio loop Qt...";
        return app.exec();
    } catch (const std::exception& e) {
        qDebug() << "Eccezione catturata:" << e.what();
        QMessageBox::critical(nullptr, "Errore critico", QString("Crash: %1").arg(e.what()));
        return -1;
    } catch (...) {
        qDebug() << "Eccezione sconosciuta catturata.";
        QMessageBox::critical(nullptr, "Errore critico", "Crash sconosciuto.");
        return -1;
    }
}
