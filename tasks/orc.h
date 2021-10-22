#pragma once

#include "../editor.h"
#include "ui_orc.h"

namespace lst { class LstModel; };

class ORC : public Editor
{
public:
    ORC(QWidget *parent = 0, Qt::WFlags flags = 0);

    virtual bool setData(QIODevice *blob, ka::KAInfo *ka);
    virtual bool getData(QIODevice *blob, ka::KAInfo *ka);

private:
    enum { ORCSize = 1 };
    Ui::ORCForm m_orc_form_ui;
    QWidget *frame;
    lst::LstModel *m_rk_model;
};
