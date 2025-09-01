#ifndef MODIFICADIALOG_H
#define MODIFICADIALOG_H

#include "logic/headers/nailsproduct.h"

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QFormLayout>
#include <QPushButton>
#include <QDialog>

class ModificaDialog : public QDialog {
    Q_OBJECT
private:
    NailsProduct* prodotto;
    bool isNew;

    QLineEdit* nameEdit;
    QLineEdit* sizeEdit;
    QLineEdit* polEdit;
    QLineEdit* imageEdit;
    QComboBox* colorBox;
    QComboBox* finishBox;
    QComboBox* elasticityBox;
    QComboBox* gripBox;
    QComboBox* tbTypeBox;
    QComboBox* coverageBox;
    QComboBox* viscosityBox;
    QLineEdit* staplingEdit;
    QLineEdit* durabilityEdit;

    QVBoxLayout* mainLayout;
    QFormLayout* formLayout;
    QComboBox* productTypeBox;

    void setupForm();
    void setupButtons(QVBoxLayout* layout);
    void creaProdotto();

public:
    explicit ModificaDialog(NailsProduct* prodotto, bool isNew, QWidget* parent = nullptr);
    NailsProduct* getProdotto() const;

private slots:
    void scegliImmagine();
    void salva();

signals:
    void prodottoCreato(NailsProduct* prodotto);
};

#endif // MODIFICADIALOG_H
