#ifndef JSONVISITOR_H
#define JSONVISITOR_H

#include "UI/headers/nailsproductvisitor.h"

#include <QJsonObject>

class JsonVisitor : public NailsProductVisitor
{
private:
    QJsonObject jsonProduct;

public:
    QJsonObject getJsonProduct() const;
    void visitSmaltoSemip(const SmaltoSemip& prod) override;
    void visitTopBase(const TopBase& prod) override;
    void visitGelCostruttore(const GelCostruttore& prod) override;
};

#endif // JSONVISITOR_H

