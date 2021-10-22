#include "tasks-editor.h"
#include "db.h"
#include "settings.h"
//trnames
#include "trnames/lookuplist.h"
//qt
#include <QtCore/QTranslator>
#include <QtGui/QApplication>
#include <QtGui/QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator t;
    t.load(QString("tasks-editor_%1")
        .arg(QLocale::system().name())
        , a.applicationDirPath());
    a.installTranslator(&t);

    trnames::LookupList::init(QLocale::system().name());

    SettingsForm set;

    DB db;
    if (db.connect(set.db_user(), set.db_pass(), set.db_name())) {
        set.show();
        return false;
    };

    TasksEditor w(&db, &set);
    w.show();
    return a.exec();
};
