#pragma once

#include "../editor.h"
#include "ui_freq-pk.h"

class FreqPKItem;

class FREQ_PK : public Editor
{
    Q_OBJECT

public:
    FREQ_PK(QWidget *parent = 0, Qt::WFlags flags = 0);

    virtual bool setData(QIODevice *blob, ka::KAInfo *ka);
    virtual bool getData(QIODevice *blob, ka::KAInfo *ka);

private:
    enum { FreqPKSize = 117 };
    Ui::FreqPKForm m_freq_pk_form_ui;
    QWidget *frame;

private:
    void initTreeWidget();
    ushort num(int i);
    int indx(ushort n);

protected slots:
    void pushButtonEdit_clicked();
    void treeWidget_clicked(QTreeWidgetItem *item);

private:
    FreqPKItem *m_item;
};
