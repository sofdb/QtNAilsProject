#ifndef CATALOGVIEWER_H
#define CATALOGVIEWER_H

#include "logic/headers/nailsproduct.h"
#include "UI/headers/productwidget.h"
#include "logic/headers/catalogo.h"

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QFormLayout>

class CatalogViewer : public QWidget {
    Q_OBJECT

public:
    explicit CatalogViewer(QWidget* parent = nullptr);
    void refreshCatalog();

private slots:
    void aggiornaSelezione();
    void gestisciModifica();
    void gestisciRimozione();
    void gestisciInserimento();
    void filtraProdotti(const QString& testo);
    void applyFilters();
private:
    Catalogo catalogo;
    QList<NailsProduct*> catalogoVector;
    QListWidget* listaProdotti;
    QLineEdit* searchBar;
    QPushButton* inserisciBtn;
    QPushButton* modificaBtn;
    QPushButton* rimuoviBtn;
    QWidget* productContainer = nullptr;
    ProductWidget* productWidget = nullptr;
    QLabel* placeholder = nullptr;

    QComboBox* tipoProdottoBox;
    QComboBox* colorBox;
    QComboBox* finishBox;
    QComboBox* elasticityBox;
    QComboBox* gripBox;
    QComboBox* tbTypeBox;
    QComboBox* coverageBox;
    QComboBox* viscosityBox;

    void aggiornaDettagli(NailsProduct* prodotto);
    void caricaCatalogo();
};

#endif // CATALOGVIEWER_H
