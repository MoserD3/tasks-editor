#include "settings.h"
//config
#include "config/config.h"
#include "config/key.h"
//qt
#include <QtGui/QMessageBox>

#ifdef WIN32
#define CONFIG_FLAGS CONFIG_FORMAT_REG|CONFIG_LOCATION_SYSTEM
#else
#define CONFIG_FLAGS CONFIG_FORMAT_XML|CONFIG_LOCATION_SYSTEM
#endif

SettingsForm::SettingsForm(QWidget *parent, Qt::WFlags flags)
    : QDialog(parent, flags)
    , m_config(NULL)
{
    ui.setupUi(this);

    setWindowTitle(tr("Tasks Editor") + " - " + windowTitle());

    m_config = Configuration::Config::create("tasks-editor");
    m_config->load("OLEGD", "tasks-editor", CONFIG_FLAGS);

    setFixedSize(QSize(301, 170));
};

SettingsForm::~SettingsForm()
{
    Configuration::Config::destroy(m_config);
};

void SettingsForm::show()
{
    m_config->load("OLEGD", "tasks-editor", CONFIG_FLAGS);
    ui.lineEditUser->setText(m_config->key("Database")->key("User")->value());
    ui.lineEditPassword->setText(m_config->key("Database")->key("Password")->value());
    ui.lineEditDBName->setText(m_config->key("Database")->key("Server")->value());
    QDialog::show();
    if (exec()) {
        m_config->key("Database")->key("User")->setValue(ui.lineEditUser->text());
        m_config->key("Database")->key("Password")->setValue(ui.lineEditPassword->text());
        m_config->key("Database")->key("Server")->setValue(ui.lineEditDBName->text());
        if (!m_config->save("OLEGD", "tasks-editor", CONFIG_FLAGS)) {
            QMessageBox::warning(this, tr("Tasks Editor"), tr("Can`t save settings!!")
                , tr("Cancel"), 0, QString::null, 0, 1);
        };
    }
};

QString SettingsForm::db_user()
{
    return m_config->key("Database")->key("User")->value();
};

QString SettingsForm::db_pass()
{
    return m_config->key("Database")->key("Password")->value();
};

QString SettingsForm::db_name()
{
    return m_config->key("Database")->key("Server")->value();
};
