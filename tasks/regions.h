#pragma once

#include "../editor.h"
#include "ui_regions.h"

class REGIONS : public Editor
{
    Q_OBJECT

public:
    REGIONS(QWidget *parent = 0, Qt::WFlags flags = 0);

    virtual bool setData(QIODevice *blob, ka::KAInfo *ka);
    virtual bool getData(QIODevice *blob, ka::KAInfo *ka);

    protected slots:
    void pushButtonAdd_clicked();
    void pushButtonDelete_clicked();

private:
    Ui::RegionsForm m_regions_form_ui;
    QWidget *frame;
};
