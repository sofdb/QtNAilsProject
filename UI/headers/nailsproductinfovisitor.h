#ifndef NAILSPRODUCTINFOVISITOR_H
#define NAILSPRODUCTINFOVISITOR_H

#include <QWidget>

#include "UI/headers/nailsproductvisitor.h"

class NailsProductInfoVisitor : public NailsProductVisitor
{
private:
    QWidget* widget;
public:
    QWidget* getWidget();

    void visitSmaltoSemip(const SmaltoSemip& prod) override;
    void visitTopBase(const TopBase& prod) override;
    void visitGelCostruttore(const GelCostruttore& prod) override;
};

#endif // NAILSPRODUCTINFOVISITOR_H

