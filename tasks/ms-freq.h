#pragma once

#include "../editor.h"
#include "ui_ms-freq.h"

class MS_FREQ : public Editor
{
public:
    MS_FREQ(QWidget *parent = 0, Qt::WFlags flags = 0);

    virtual bool setData(QIODevice *blob, ka::KAInfo *ka);
    virtual bool getData(QIODevice *blob, ka::KAInfo *ka);

private:
    enum { MSFreqSize = 4 };
    Ui::MSFreqForm m_msfreq_form_ui;
    QWidget *frame;
};
