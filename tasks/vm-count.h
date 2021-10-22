#pragma once

#include "../editor.h"
#include "ui_vm-count.h"

class VM_COUNT : public Editor
{
public:
    VM_COUNT(QWidget *parent = 0, Qt::WFlags flags = 0);

    virtual bool setData(QIODevice *blob, ka::KAInfo *ka);
    virtual bool getData(QIODevice *blob, ka::KAInfo *ka);

private:
    enum { VMCountSize = 2 };
    Ui::VMCountForm m_vm_count_form_ui;
    QWidget *frame;
};
