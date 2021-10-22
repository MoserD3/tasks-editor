#include "db.h"
#include "db-filter.h"
//libdb
#include "libdb/libdb-core/context.h"
#include "libdb/libdb-core/connection.h"
#include "libdb/libdb-core/transaction.h"
#include "libdb/libdb-core/blobdevice.h"
#include "libdb/libdb-core/exception.h"
#include "libdb/libdb-core/query.h"
#include "libdb/libdb-core/resultset.h"
#include "libdb/libdb-comm/srvarr.h"
#include "libdb/libdb-comm/nka.h"
//brtk
#include "brtk/array.h"
//qt
#include <QtGui/QMessageBox>

int DB::connect(const QString &db_user, const QString &db_password, const QString &db_name)
try	{
    m_connection.SelectDB(db_name);
    m_connection.Connect(db_user, db_password, dbcore::Connection::ReadCommited);
    if (!m_connection.IsConnected()) {
        QMessageBox::warning(0, tr("DB Error!!"), tr("No database connection (\"%1\", \"%2\")!!")
            .arg(db_name)
            .arg(db_user)
            , tr("Cancel")
            , 0, QString::null, 0, 1);
        return 1;
    };
    return 0;
}
catch (const dbcore::Exception &ex)
{
    QMessageBox::warning(0, tr("DB Error!!"), tr("No database connection (\"%1\", \"%2\")!!\n%3")
        .arg(db_name)
        .arg(db_user)
        .arg(ex.toString())
        , tr("Cancel"), 0, QString::null, 0, 1);
    return 1;
};

void DB::get_list(List *iface)
try {
    dbcomm::SrvArrRecord rec;
    dbcore::ResultSet rs;
    if (m_filter_on) {
        TasksEditorFilter cond(m_filter.nka, m_filter.dt_from, m_filter.dt_to);
        rs = dbcore::ResultSet(m_connection, rec, cond);
    }
    else {
        TasksEditorFilter cond;
        rs = dbcore::ResultSet(m_connection, rec, cond);
    }
    while (rs.next())
        iface->record(rec);
}
catch (const dbcore::Exception &ex)
{
    QMessageBox::warning(0, tr("DB Error!!"), tr("Can`t refresh list!!\n%1")
        .arg(ex.toString())
        , tr("Cancel"), 0, QString::null, 0, 1);
};

bool DB::get_sink(const dbcomm::SrvArrKey &key, Sink *iface)
try {
    dbcomm::SrvArrRecord rec;
    dbcore::ResultSet rs(m_connection, rec, key);
    if (!rs.next())
        return false;
    dbcore::BlobDevice blob(rs, rec.packet);
    iface->body(&blob);
    blob.close();
    rec.packet.reset();
    return true;
}
catch (const dbcore::Exception &ex)
{
    QMessageBox::warning(0, tr("DB Error!!"), tr("Can`t open record!!\n%1")
        .arg(ex.toString())
        , tr("Cancel"), 0, QString::null, 0, 1);
    return false;
};

void DB::get_ka_list(KAList *iface)
try	{
    dbcomm::NKAUpdate rec;
    dbcore::ResultSet rs(m_connection, rec);
    while (rs.next())
        iface->record(rec);
}
catch (const dbcore::Exception &ex)
{
    QMessageBox::warning(0, tr("DB Error!!"), tr("Can`t open nka record!!\n%1")
        .arg(ex.toString())
        , tr("Cancel"), 0, QString::null, 0, 1);
};

void DB::del(const dbcomm::SrvArrKey &key)
try {
    dbcore::Query quary(m_connection);
    quary.Delete(key);
}
catch (const dbcore::Exception &ex)
{
    QMessageBox::warning(0, tr("DB Error!!"), tr("Can`t delete record!!\n%1")
        .arg(ex.toString())
        , tr("Cancel"), 0, QString::null, 0, 1);
};

void DB::put(const dbcomm::SrvArrKey &key, Source *iface)
try {
    dbcomm::SrvArrRecord rec;
    dbcore::Transaction tr(m_connection);
    dbcore::ResultSet rs(tr, rec, key, dbcore::NoOrder, true);
    if (rs.next()) {
        iface->record(rec);
        dbcore::BlobDevice blob(rs, rec.packet);
        blob.open(QIODevice::WriteOnly | QIODevice::Truncate);
        iface->body(&blob);
        blob.close();
        dbcore::Query quary(m_connection);
        quary.Update(rec, key, false, false);
    }
    else {
        rec.ka = key.ka;
        rec.tp = key.tp;
        rec.subtp = key.subtp;
        rec.dt = key.dt;

        iface->record(rec);
        dbcore::Query quary(tr);
        quary.Insert(rec);
        dbcore::BlobDevice blob(quary, rec.packet);
        blob.open(QIODevice::WriteOnly | QIODevice::Truncate);
        iface->body(&blob);
        blob.close();
    };
    tr.success();
}
catch (const dbcore::Exception &ex)
{
    QMessageBox::warning(0, tr("DB Error!!"), tr("Can`t save record!!\n%1")
        .arg(ex.toString())
        , tr("Cancel"), 0, QString::null, 0, 1);
};

void DB::set_filter(bool filter_on, const Filter &filter)
{
    m_filter_on = filter_on;
    if (m_filter_on)
        m_filter = filter;
};
