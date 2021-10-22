#pragma once

#include "ui_settings.h"
//qt
#include <QtGui/QWidget>

namespace Configuration { class Config; };

class SettingsForm : public QDialog
{
    Q_OBJECT

public:
    SettingsForm(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~SettingsForm();

    virtual void show();
    QString db_user();
    QString db_pass();
    QString db_name();

private:
    Ui::SettingsForm ui;
    Configuration::Config *m_config;
};
