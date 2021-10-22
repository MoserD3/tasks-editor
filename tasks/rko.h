#pragma once

#include "../editor.h"
#include "ui_rko.h"

class RKO : public Editor
{
public:
    RKO(QWidget *parent = 0, Qt::WFlags flags = 0);

    virtual bool setData(QIODevice *blob, ka::KAInfo *ka);
    virtual bool getData(QIODevice *blob, ka::KAInfo *ka);

private:
    enum { RKOSize = 3 };
    Ui::RKOForm m_rko_form_ui;
    QWidget *frame;
};
