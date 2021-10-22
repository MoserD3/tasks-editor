#pragma once

#include "../editor.h"
#include "ui_free-access.h"

class FREE_ACCESS : public Editor
{
public:
    FREE_ACCESS(QWidget *parent = 0, Qt::WFlags flags = 0);

    virtual bool setData(QIODevice *blob, ka::KAInfo *ka);
    virtual bool getData(QIODevice *blob, ka::KAInfo *ka);

private:
    enum { FreeAccessSize = 1 };
    Ui::FreeAccessForm m_free_access_form_ui;
    QWidget *frame;
};
