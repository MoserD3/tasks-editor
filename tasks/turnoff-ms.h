#pragma once

#include "../editor.h"
#include "ui_turnoff-ms.h"

class TURNOFF_MS : public Editor
{
public:
    TURNOFF_MS(QWidget *parent = 0, Qt::WFlags flags = 0);

    virtual bool setData(QIODevice *blob, ka::KAInfo *ka);
    virtual bool getData(QIODevice *blob, ka::KAInfo *ka);

private:
    enum { TurnoffMSSize = 0 };
    Ui::TurnoffMSForm m_turnoff_ms_form_ui;
    QWidget *frame;
};
