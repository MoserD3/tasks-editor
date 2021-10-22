#pragma once

#include "../editor.h"
#include "ui_tmi.h"

namespace lst { class LstModel; };

class TMI : public Editor
{
public:
    TMI(QWidget *parent = 0, Qt::WFlags flags = 0);

    virtual bool setData(QIODevice *blob, ka::KAInfo *ka);
    virtual bool getData(QIODevice *blob, ka::KAInfo *ka);

private:
    enum { TMISize = 9 };
    Ui::TMIForm m_tmi_form_ui;
    QWidget *frame;
    lst::LstModel *m_tmi_model;
};
