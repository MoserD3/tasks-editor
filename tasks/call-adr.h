#pragma once

#include "../editor.h"
#include "ui_call-adr.h"

class CALL_ADR : public Editor
{
    Q_OBJECT

public:
    CALL_ADR(QWidget *parent = 0, Qt::WFlags flags = 0);

    virtual bool setData(QIODevice *blob, ka::KAInfo *ka);
    virtual bool getData(QIODevice *blob, ka::KAInfo *ka);

protected slots:
    void pushButtonAdd_clicked();
    void pushButtonDelete_clicked();

private:
    Ui::CallAdrForm m_call_adr_form_ui;
    QWidget *frame;
};
