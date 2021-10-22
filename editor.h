#pragma once

#include "ui_editor.h"
#include "brtk/task.h"
#include "ka-model.h"
//qt
#include <QtGui/QWidget>

class Editor : public QWidget
{
    Q_OBJECT

public:
    Editor(QWidget *parent = 0, Qt::WFlags flags = 0);

    virtual bool setData(QIODevice *blob, ka::KAInfo *ka) = 0;
    virtual bool getData(QIODevice *blob, ka::KAInfo *ka) = 0;

protected:
    bool setHeader(const BRTK::Task::Header &header, ka::KAInfo *ka);
    bool getHeader(BRTK::Task::Header &header, ka::KAInfo *ka);

protected:
    Ui::EditorForm m_editroform_ui;
};
