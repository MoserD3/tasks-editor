#pragma once

#include "../editor.h"
#include "ui_apo.h"

class APO : public Editor
{
public:
    APO(QWidget *parent = 0, Qt::WFlags flags = 0);

    virtual bool setData(QIODevice *blob, ka::KAInfo *ka);
    virtual bool getData(QIODevice *blob, ka::KAInfo *ka);

private:
    enum { APOSize = 4 };
    Ui::APOForm m_apoform_ui;
    QWidget *frame;
};
