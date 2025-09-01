#include "UI/headers/productfilters.h"
#include "logic/headers/Scala3Converters.h"

QList<NailsProduct*> ProductFilters::filtra(
    const Catalogo& catalogo,
    const QString& searchText,
    const QString& tipoProdotto,
    const QString& color,
    const QString& finish,
    const QString& elasticity,
    const QString& grip,
    const QString& tbType,
    const QString& coverage,
    const QString& viscosity)
{
    QList<NailsProduct*> risultati;

    for (int i = 0; i < catalogo.size(); ++i) {
        NailsProduct* prodotto = catalogo.getProduct(i);
        QString nome = QString::fromStdString(prodotto->getName());

        if (!nome.contains(searchText, Qt::CaseInsensitive)) continue;

        QString tipoProdottoEffettivo = tipoProdotto;

        if (tipoProdottoEffettivo.isEmpty() || tipoProdottoEffettivo == "Tutti") {
            if (!color.isEmpty() && color != "Tutti") {
                tipoProdottoEffettivo = "Smalto Semipermanente";
            } else if ((!finish.isEmpty() && finish != "Tutti") ||
                    (!elasticity.isEmpty() && elasticity != "Tutti") ||
                    (!grip.isEmpty() && grip != "Tutti") ||
                    (!tbType.isEmpty() && tbType != "Tutti")) {
                tipoProdottoEffettivo = "Top/Base";
            } else if ((!coverage.isEmpty() && coverage != "Tutti") ||
                    (!viscosity.isEmpty() && viscosity != "Tutti")) {
                tipoProdottoEffettivo = "Gel Costruttore";
            }
        }
        
        bool match = true;

        if (!tipoProdottoEffettivo.isEmpty() && tipoProdottoEffettivo != "Tutti") {
            if (tipoProdottoEffettivo == "Smalto Semipermanente" && !dynamic_cast<SmaltoSemip*>(prodotto)) { match = false; }
            else if (tipoProdottoEffettivo == "Top/Base" && !dynamic_cast<TopBase*>(prodotto)) { match = false; }
            else if (tipoProdottoEffettivo == "Gel Costruttore" && !dynamic_cast<GelCostruttore*>(prodotto)) { match = false; }
        }

        if (auto* smalto = dynamic_cast<SmaltoSemip*>(prodotto)) {
            if (!color.isEmpty() && color != "Tutti" &&
                color != QString::fromStdString(SmaltoSemip::SemicolorToString(smalto->getColor()))) {
                match = false;
            }
        }

        if (auto* tb = dynamic_cast<TopBase*>(prodotto)) {
            if (!finish.isEmpty() && finish != "Tutti" &&
                finish != QString::fromStdString(TopBase::FinishToString(tb->getFinish()))) {
                match = false;
            }
            if (!elasticity.isEmpty() && elasticity != "Tutti" &&
                elasticity != QString::fromStdString(Scala3Converters::Scala3toString(tb->getElasticity()))) {
                match = false;
            }
            if (!grip.isEmpty() && grip != "Tutti" &&
                grip != QString::fromStdString(Scala3Converters::Scala3toString(tb->getGrip()))) {
                match = false;
            }
            if (!tbType.isEmpty() && tbType != "Tutti" &&
                tbType != QString::fromStdString(TopBase::TBtypeToString(tb->getTBtype()))) {
                match = false;
            }
        }

        if (auto* gel = dynamic_cast<GelCostruttore*>(prodotto)) {
            if (!coverage.isEmpty() && coverage != "Tutti" &&
                coverage != QString::fromStdString(Scala3Converters::Scala3toString(gel->getCoverage()))) {
                match = false;
            }
            if (!viscosity.isEmpty() && viscosity != "Tutti" &&
                viscosity != QString::fromStdString(Scala3Converters::Scala3toString(gel->getViscosity()))) {
                match = false;
            }
        }

        if (match){
            risultati.append(prodotto);
        }
    }
    return risultati;
}
