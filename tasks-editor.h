#pragma once

#include "ui_tasks-editor.h"
//qt
#include <QtGui/QWidget>

class TasksModel;
class DBIface;
class Editor;
class SettingsForm;

namespace ka { class KAModel; };

class TasksEditor : public QWidget
{
    Q_OBJECT

public:
    TasksEditor(DBIface *db, SettingsForm *settings, QWidget *parent = 0, Qt::WFlags flags = 0);
    ~TasksEditor();

protected slots:
    void groupBoxFilter_clicked();

    void pushButtonNew_clicked();
    void pushButtonDelete_clicked();
    void pushButtonRefresh_clicked();
    void pushButtonSettings_clicked();

    void pushButtonAccept_clicked();
    void pushButtonCancel_clicked();

    void comboBoxType_itemChanged(int i);
    void treeView_clicked(QModelIndex ind);

private:
    Ui::TasksEditorClass ui;

private:
    void clearAll();
    void lockKey();
    void unlockKey();

private:
    DBIface *const m_db;
    TasksModel *m_task_model;
    ka::KAModel *m_ka_model;
    Editor *m_editor;
    SettingsForm *const m_settings;
    bool m_selected;
};
