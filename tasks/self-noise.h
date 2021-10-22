#pragma once

#include "../editor.h"
#include "ui_self-noise.h"

class SELF_NOISE : public Editor
{
public:
    SELF_NOISE(QWidget *parent = 0, Qt::WFlags flags = 0);

    virtual bool setData(QIODevice *blob, ka::KAInfo *ka);
    virtual bool getData(QIODevice *blob, ka::KAInfo *ka);

private:
    enum { SelfNoiseSize = 0 };
    Ui::SelfNoiseForm m_self_noise_form_ui;
    QWidget *frame;
};
