#pragma once

#include "../editor.h"
#include "ui_ku-params.h"

class KU_PARAMS : public Editor
{
public:
    KU_PARAMS(QWidget *parent = 0, Qt::WFlags flags = 0);

    virtual bool setData(QIODevice *blob, ka::KAInfo *ka);
    virtual bool getData(QIODevice *blob, ka::KAInfo *ka);

private:
    enum { KUParamsSize = 2 };
    Ui::KUParamsForm m_ku_params_form_ui;
    QWidget *frame;
};
