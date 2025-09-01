#include "UI/headers/catalogviewer.h"
#include "UI/headers/modificadialog.h"
#include "Json/headers/jsonhandler.h"
#include "logic/headers/scala3converters.h"
#include "UI/headers/productfilters.h"

#include <QApplication>
#include <QFile>
#include <QMessageBox>

CatalogViewer::CatalogViewer(QWidget* parent) :
    QWidget(parent)
{
    QFile file(":/UI/stile.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    qApp->setStyleSheet(styleSheet);


    searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Cerca prodotto...");
    connect(searchBar, &QLineEdit::textChanged, this, &CatalogViewer::filtraProdotti);

    inserisciBtn = new QPushButton("Inserisci", this);
    connect(inserisciBtn, &QPushButton::clicked, this, &CatalogViewer::gestisciInserimento);

    listaProdotti = new QListWidget(this);
    listaProdotti->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    listaProdotti->setMaximumHeight(200);
    connect(listaProdotti, &QListWidget::itemSelectionChanged, this, &CatalogViewer::aggiornaSelezione);

    tipoProdottoBox = new QComboBox();
    tipoProdottoBox->addItems({"Tutti", "Smalto Semipermanente", "Top/Base", "Gel Costruttore"});

    colorBox = new QComboBox();
    colorBox->addItem("Tutti");
    for (int i = 0; i <= static_cast<int>(SemiColor::GlitterArgento); ++i)
        colorBox->addItem(QString::fromStdString(SmaltoSemip::SemicolorToString(static_cast<SemiColor>(i))));

    finishBox = new QComboBox();
    finishBox->addItem("Tutti");
    for (int i = 0; i <= static_cast<int>(Finish::Glitter); ++i)
        finishBox->addItem(QString::fromStdString(TopBase::FinishToString(static_cast<Finish>(i))));

    elasticityBox = new QComboBox();
    gripBox = new QComboBox();
    elasticityBox->addItem("Tutti");
    gripBox->addItem("Tutti");
    for (int i = 0; i <= static_cast<int>(Scala3::Alta); ++i) {
        QString label = QString::fromStdString(Scala3Converters::Scala3toString(static_cast<Scala3>(i)));
        elasticityBox->addItem(label);
        gripBox->addItem(label);
    }

    tbTypeBox = new QComboBox();
    tbTypeBox->addItem("Tutti");
    for (int i = 0; i <= static_cast<int>(TopBaseType::Hard); ++i)
        tbTypeBox->addItem(QString::fromStdString(TopBase::TBtypeToString(static_cast<TopBaseType>(i))));

    coverageBox = new QComboBox();
    viscosityBox = new QComboBox();
    coverageBox->addItem("Tutti");
    viscosityBox->addItem("Tutti");
    for (int i = 0; i <= static_cast<int>(Scala3::Alta); ++i) {
        QString label = QString::fromStdString(Scala3Converters::Scala3toString(static_cast<Scala3>(i)));
        coverageBox->addItem(label);
        viscosityBox->addItem(label);
    }

    QFormLayout* filtriLayout = new QFormLayout();
    filtriLayout->addRow("Tipo Prodotto:", tipoProdottoBox);
    filtriLayout->addRow("Colore:", colorBox);
    filtriLayout->addRow("Finish:", finishBox);
    filtriLayout->addRow("Elasticità:", elasticityBox);
    filtriLayout->addRow("Grip:", gripBox);
    filtriLayout->addRow("Tipo Base:", tbTypeBox);
    filtriLayout->addRow("Coprenza:", coverageBox);
    filtriLayout->addRow("Viscosità:", viscosityBox);

    QVBoxLayout* leftLayout = new QVBoxLayout;
    leftLayout->addWidget(searchBar);
    leftLayout->addWidget(inserisciBtn);
    leftLayout->addLayout(filtriLayout);
    leftLayout->addWidget(listaProdotti);

    placeholder = new QLabel("Seleziona un prodotto per visualizzarne i dettagli");
    placeholder->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    placeholder->setObjectName("placeholder");

    modificaBtn = new QPushButton("Modifica", this);
    rimuoviBtn = new QPushButton("Rimuovi", this);

    QVBoxLayout* rightLayout = new QVBoxLayout;
    productContainer = new QWidget(this);
    productContainer->setLayout(new QVBoxLayout); //vuoto
    productContainer->setObjectName("productContainer");

    rightLayout->addWidget(placeholder);
    rightLayout->addWidget(productContainer); // spazio riservato per il widget prodotto

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->setAlignment(Qt::AlignCenter);
    buttonLayout->addWidget(modificaBtn);
    buttonLayout->addSpacing(100);
    buttonLayout->addWidget(rimuoviBtn);

    rightLayout->addLayout(buttonLayout);

    connect(modificaBtn, &QPushButton::clicked, this, &CatalogViewer::gestisciModifica);
    connect(rimuoviBtn, &QPushButton::clicked, this, &CatalogViewer::gestisciRimozione);

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->addLayout(leftLayout, 1);
    mainLayout->addLayout(rightLayout, 3);

    setLayout(mainLayout);

    connect(tipoProdottoBox, &QComboBox::currentTextChanged, this, &CatalogViewer::applyFilters);
    connect(colorBox, &QComboBox::currentTextChanged, this, &CatalogViewer::applyFilters);
    connect(finishBox, &QComboBox::currentTextChanged, this, &CatalogViewer::applyFilters);
    connect(elasticityBox, &QComboBox::currentTextChanged, this, &CatalogViewer::applyFilters);
    connect(gripBox, &QComboBox::currentTextChanged, this, &CatalogViewer::applyFilters);
    connect(tbTypeBox, &QComboBox::currentTextChanged, this, &CatalogViewer::applyFilters);
    connect(coverageBox, &QComboBox::currentTextChanged, this, &CatalogViewer::applyFilters);
    connect(viscosityBox, &QComboBox::currentTextChanged, this, &CatalogViewer::applyFilters);

    caricaCatalogo();
    refreshCatalog();
}

void CatalogViewer::caricaCatalogo() {
    QFile file("catalogo.json");
    if (!file.exists()) {
        QMessageBox::warning(this, "Attenzione", "File catalogo.json non trovato. Verrà creato un catalogo vuoto.");
        return;
    }

    JsonHandler::loadCatalogFromFile(catalogo, "catalogo.json");
}


void CatalogViewer::refreshCatalog() {
    applyFilters();

    if (catalogo.size() == 0) {
        QMessageBox::information(this, "Catalogo vuoto", "Il catalogo è vuoto. Inserisci un nuovo prodotto.");
        if (!placeholder) {
            QLayout* rightLayout = layout()->itemAt(1)->layout();
            placeholder = new QLabel("Il catalogo è vuoto. Inserisci un nuovo prodotto.");
            placeholder->setAlignment(Qt::AlignCenter);
            placeholder->setObjectName("placeholder");
            rightLayout->addWidget(placeholder);
        }
        if (productWidget) {
            QLayout* rightLayout = layout()->itemAt(1)->layout();
            rightLayout->removeWidget(productWidget);
            delete productWidget;
            productWidget = nullptr;
        }
    }
    if (productWidget && productWidget->getProdotto()) {
        productWidget->refresh();
    }
}

void CatalogViewer::aggiornaSelezione() {
    int index = listaProdotti->currentRow();
    if (index < 0 || index >= catalogo.size()) return;

    NailsProduct* prodotto = catalogo.getProduct(index);
    if (!prodotto) return;

    if (placeholder) {
        QLayout* rightLayout = layout()->itemAt(1)->layout();
        rightLayout->removeWidget(placeholder);
        delete placeholder;
        placeholder = nullptr;
    }

    QLayout* layout = productContainer->layout();
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    productWidget = new ProductWidget(prodotto, this);
    layout->addWidget(productWidget);
}


void CatalogViewer::gestisciModifica() {
    int index = listaProdotti->currentRow();
    if (index < 0 || index >= catalogo.size()) return;

    NailsProduct* prodotto = catalogo.getProduct(index);
    ModificaDialog dialog(prodotto, false, this); //bool false indica alla modificaDialog che è una modifica
    if (dialog.exec() == QDialog::Accepted) {
        JsonHandler::saveCatalogToFile(catalogo, "catalogo.json");
        refreshCatalog();
        aggiornaSelezione();
    }
}

void CatalogViewer::gestisciInserimento() {
    ModificaDialog dialog(nullptr, true, this); // true = inserimento
    if (dialog.exec() == QDialog::Accepted) {
        NailsProduct* nuovo = dialog.getProdotto();
        if (nuovo) {
            try {
                catalogo.addProduct(nuovo);
                JsonHandler::saveCatalogToFile(catalogo, "catalogo.json");
                refreshCatalog();
            } catch (const std::exception& e) {
                QMessageBox::critical(this, "Errore", QString::fromStdString(e.what()));
                delete nuovo; // evita memory leak se non viene aggiunto
            }
        }
    }
}

void CatalogViewer::gestisciRimozione() {
    int index = listaProdotti->currentRow();
    if (index < 0 || index >= catalogo.size()) return;

    auto conferma = QMessageBox::question(this, "Conferma", "Rimuovere il prodotto selezionato?");
    if (conferma == QMessageBox::Yes) {
        catalogo.removeProduct(index);
        JsonHandler::saveCatalogToFile(catalogo, "catalogo.json");
        refreshCatalog();

        QLayout* rightLayout = layout()->itemAt(1)->layout();

        if (productWidget) {
            rightLayout->removeWidget(productWidget);
            delete productWidget;
            productWidget = nullptr;
        }

        if (catalogo.size() == 0 && !placeholder) {
            placeholder = new QLabel("Seleziona un prodotto per visualizzarne i dettagli");
            placeholder->setAlignment(Qt::AlignCenter);
            rightLayout->addWidget(placeholder);
        }
    }
}

void CatalogViewer::applyFilters() {
    listaProdotti->clear();

    QList<NailsProduct*> filtrati = ProductFilters::filtra(
        catalogo,
        searchBar->text(),
        tipoProdottoBox->currentText(),
        colorBox->currentText(),
        finishBox->currentText(),
        elasticityBox->currentText(),
        gripBox->currentText(),
        tbTypeBox->currentText(),
        coverageBox->currentText(),
        viscosityBox->currentText()
    );

    for (auto it = filtrati.constBegin(); it != filtrati.constEnd(); ++it) {
        listaProdotti->addItem(QString::fromStdString((*it)->getName()));
    }
}

void CatalogViewer::filtraProdotti(const QString&) {
    applyFilters();
}

void CatalogViewer::aggiornaDettagli(NailsProduct* prodotto) {
    if (!prodotto) return;

    QLayout* layout = productContainer->layout();
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    productWidget = new ProductWidget(prodotto, this);
    layout->addWidget(productWidget);
}
