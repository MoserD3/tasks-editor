#pragma once

#include "../editor.h"
#include "ui_ok-freq.h"

class OK_FREQ : public Editor
{
    Q_OBJECT

public:
    OK_FREQ(QWidget *parent = 0, Qt::WFlags flags = 0);

    virtual bool setData(QIODevice *blob, ka::KAInfo *ka);
    virtual bool getData(QIODevice *blob, ka::KAInfo *ka);

    public slots:
    void comboBoxNum_indexChanged(int i);

private:
    Ui::OKFreqForm m_ok_freq_form_ui;
    QWidget *frame;
};
