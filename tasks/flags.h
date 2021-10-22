#pragma once

#include "../editor.h"
#include "ui_flags.h"

class FLAGS : public Editor
{
public:
    FLAGS(QWidget *parent = 0, Qt::WFlags flags = 0);

    virtual bool setData(QIODevice *blob, ka::KAInfo *ka);
    virtual bool getData(QIODevice *blob, ka::KAInfo *ka);

private:
    enum { FlagsSize = 1 };
    Ui::FlagsForm m_flagform_ui;
    QWidget *frame;
};
