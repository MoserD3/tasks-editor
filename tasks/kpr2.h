#pragma once

#include "../editor.h"
#include "ui_kpr2.h"

class KPR2 : public Editor
{
public:
    KPR2(QWidget *parent = 0, Qt::WFlags flags = 0);

    virtual bool setData(QIODevice *blob, ka::KAInfo *ka);
    virtual bool getData(QIODevice *blob, ka::KAInfo *ka);

private:
    enum { KPR2Size = 14 };
    Ui::KPR2Form m_kpr2_form_ui;
    QWidget *frame;

private:
    uchar num(int index);
    int indx(uchar num);
};
