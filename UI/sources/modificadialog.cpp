#include "UI/headers/modificadialog.h"
#include "logic/headers/smaltosemip.h"
#include "logic/headers/topbase.h"
#include "logic/headers/gelcostruttore.h"
#include "logic/headers/scala3converters.h"

#include <QFileDialog>
#include <QMessageBox>

ModificaDialog::ModificaDialog(NailsProduct* prodotto, bool isNew, QWidget* parent)
    : QDialog(parent), prodotto(prodotto), isNew(isNew)
{
    setWindowTitle(isNew ? "Nuovo Prodotto" : "Modifica Prodotto");

    mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    if (isNew && !prodotto) {
        productTypeBox = new QComboBox();
        productTypeBox->addItem("Smalto Semipermanente");
        productTypeBox->addItem("Top/Base");
        productTypeBox->addItem("Gel Costruttore");

        QPushButton* creaBtn = new QPushButton("Crea");
        connect(creaBtn, &QPushButton::clicked, this, &ModificaDialog::creaProdotto);

        QFormLayout* tipoLayout = new QFormLayout();
        tipoLayout->addRow("Tipo Prodotto:", productTypeBox);
        mainLayout->addLayout(tipoLayout);
        mainLayout->addWidget(creaBtn);
    } else {
        if (!prodotto) {
            QMessageBox::critical(this, "Errore", "Prodotto da modificare non valido.");
            reject(); // chiude il dialogo
            return;
        }
        setupForm();
        setupButtons(mainLayout);
    }
}

void ModificaDialog::creaProdotto() {
    switch (productTypeBox->currentIndex()) { //nei costruttori inserisce valori neutri di default
        case 0: prodotto = new SmaltoSemip("Smalto", "", 15.0, 60, SemiColor::RossoCiliegia); break;
        case 1: prodotto = new TopBase("TopBase", "", 15.0, 60, Finish::Lucido, Scala3::Media, Scala3::Media, TopBaseType::Bonder); break;
        case 2: prodotto = new GelCostruttore("Gel", "", 15.0, 60, Scala3::Media, Scala3::Media, 60, 4); break;
    }

    QLayoutItem* item;
    while ((item = layout()->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    setupForm();
    setupButtons(qobject_cast<QVBoxLayout*>(layout()));
}

void ModificaDialog::setupButtons(QVBoxLayout* layout) {
    QPushButton* salvaBtn = new QPushButton("Salva");
    QPushButton* annullaBtn = new QPushButton("Annulla");

    connect(salvaBtn, &QPushButton::clicked, this, &ModificaDialog::salva);
    connect(annullaBtn, &QPushButton::clicked, this, &ModificaDialog::reject);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->setAlignment(Qt::AlignCenter);
    buttonLayout->addWidget(salvaBtn);
    buttonLayout->addSpacing(20);
    buttonLayout->addWidget(annullaBtn);

    layout->addLayout(buttonLayout);
}

void ModificaDialog::setupForm() {
    formLayout = new QFormLayout();

    nameEdit = new QLineEdit(QString::fromStdString(prodotto->getName()));
    formLayout->addRow("Nome:", nameEdit);

    sizeEdit = new QLineEdit(QString::number(prodotto->getSize()));
    sizeEdit->setValidator(new QDoubleValidator(0.0, 1000.0, 2, sizeEdit));
    formLayout->addRow("Quantità (ml):", sizeEdit);

    polEdit = new QLineEdit(QString::number(prodotto->getPolTime()));
    polEdit->setValidator(new QIntValidator(0, 600, polEdit));
    formLayout->addRow("Tempo Polimerizzazione:", polEdit);

    imageEdit = new QLineEdit(QString::fromStdString(prodotto->getImage()));
    formLayout->addRow("Immagine:", imageEdit);

    QPushButton* imageBrowseBtn = new QPushButton("Sfoglia...");
    connect(imageBrowseBtn, &QPushButton::clicked, this, &ModificaDialog::scegliImmagine);
    formLayout->addRow("", imageBrowseBtn);

    if (auto* smalto = dynamic_cast<SmaltoSemip*>(prodotto)) {
        colorBox = new QComboBox();
        for (int i = 0; i <= static_cast<int>(SemiColor::GlitterArgento); ++i)
            colorBox->addItem(QString::fromStdString(SmaltoSemip::SemicolorToString(static_cast<SemiColor>(i))));
        colorBox->setCurrentIndex(static_cast<int>(smalto->getColor()));
        formLayout->addRow("Colore:", colorBox);
    }

    if (auto* top = dynamic_cast<TopBase*>(prodotto)) {
        finishBox = new QComboBox();
        for (int i = 0; i <= static_cast<int>(Finish::Glitter); ++i)
            finishBox->addItem(QString::fromStdString(TopBase::FinishToString(static_cast<Finish>(i))));
        finishBox->setCurrentIndex(static_cast<int>(top->getFinish()));
        formLayout->addRow("Finish:", finishBox);

        elasticityBox = new QComboBox();
        gripBox = new QComboBox();
        for (int i = 0; i <= static_cast<int>(Scala3::Alta); ++i) {
            QString label = QString::fromStdString(Scala3Converters::Scala3toString(static_cast<Scala3>(i)));
            elasticityBox->addItem(label);
            gripBox->addItem(label);
        }
        elasticityBox->setCurrentIndex(static_cast<int>(top->getElasticity()));
        gripBox->setCurrentIndex(static_cast<int>(top->getGrip()));
        formLayout->addRow("Elasticità:", elasticityBox);
        formLayout->addRow("Grip:", gripBox);

        tbTypeBox = new QComboBox();
        for (int i = 0; i <= static_cast<int>(TopBaseType::Hard); ++i)
            tbTypeBox->addItem(QString::fromStdString(TopBase::TBtypeToString(static_cast<TopBaseType>(i))));
        tbTypeBox->setCurrentIndex(static_cast<int>(top->getTBtype()));
        formLayout->addRow("Tipo Base:", tbTypeBox);
    }

    if (auto* gel = dynamic_cast<GelCostruttore*>(prodotto)) {
        coverageBox = new QComboBox();
        viscosityBox = new QComboBox();
        for (int i = 0; i <= static_cast<int>(Scala3::Alta); ++i) {
            QString label = QString::fromStdString(Scala3Converters::Scala3toString(static_cast<Scala3>(i)));
            coverageBox->addItem(label);
            viscosityBox->addItem(label);
        }
        coverageBox->setCurrentIndex(static_cast<int>(gel->getCoverage()));
        viscosityBox->setCurrentIndex(static_cast<int>(gel->getViscosity()));
        formLayout->addRow("Coprenza:", coverageBox);
        formLayout->addRow("Viscosità:", viscosityBox);

        staplingEdit = new QLineEdit(QString::number(gel->getStap_time()));
        staplingEdit->setValidator(new QIntValidator(0, 600, staplingEdit));
        formLayout->addRow("Tempo Pinzatura:", staplingEdit);

        durabilityEdit = new QLineEdit(QString::number(gel->getDurability()));
        durabilityEdit->setValidator(new QIntValidator(1, 52, durabilityEdit));
        formLayout->addRow("Durata:", durabilityEdit);
    }

    mainLayout->addSpacing(30);
    mainLayout->addLayout(formLayout);
}

NailsProduct* ModificaDialog::getProdotto() const { return prodotto; }


void ModificaDialog::scegliImmagine() {
    QString fileName = QFileDialog::getOpenFileName(this, "Seleziona immagine", "", "Immagini (*.png *.jpg *.jpeg)");
    if (!fileName.isEmpty()) {
        imageEdit->setText(fileName);
    }
}

void ModificaDialog::salva() {
    if (!prodotto) return;

    prodotto->setName(nameEdit->text().toStdString());
    prodotto->setSize(sizeEdit->text().toDouble());
    prodotto->setPolTime(polEdit->text().toUInt());
    prodotto->setImage(imageEdit->text().toStdString());

    if (auto* smalto = dynamic_cast<SmaltoSemip*>(prodotto)) {
        smalto->setColor(static_cast<SemiColor>(colorBox->currentIndex()));
    }

    if (auto* top = dynamic_cast<TopBase*>(prodotto)) {
        top->setFinish(static_cast<Finish>(finishBox->currentIndex()));
        top->setElasticity(static_cast<Scala3>(elasticityBox->currentIndex()));;
        top->setGrip(static_cast<Scala3>(gripBox->currentIndex()));
        top->setTBtype(static_cast<TopBaseType>(tbTypeBox->currentIndex()));
    }

    if (auto* gel = dynamic_cast<GelCostruttore*>(prodotto)) {
        gel->setCoverage(static_cast<Scala3>(coverageBox->currentIndex()));
        gel->setViscosity(static_cast<Scala3>(viscosityBox->currentIndex()));;
        gel->setStap_time(staplingEdit->text().toUInt());
        gel->setDurability(durabilityEdit->text().toUInt());
    }
    emit prodottoCreato(prodotto);
    accept();
}
