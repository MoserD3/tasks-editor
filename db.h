#pragma once

//libdb
#include "libdb/libdb-core/context.h"
#include "libdb/libdb-core/connection.h"
#include "libdb/libdb-core/logger.h"
//qt
#include <QtCore/QDateTime>

namespace dbcomm { class SrvArrRecord; class SrvArrKey; };
namespace dbcomm { class NKAUpdate; };
class QIODevice;

class DBIface
{
public:
    struct Filter
    {
        short nka;
        QDateTime dt_from;
        QDateTime dt_to;
    };

    class List
    {
    public:
        virtual void record(const dbcomm::SrvArrRecord &rec) = 0;
    };

    class Sink
    {
    public:
        virtual void body(QIODevice *blob) = 0;
    };

    class Source
    {
    public:
        virtual void record(dbcomm::SrvArrRecord &rec) = 0;
        virtual void body(QIODevice *body) = 0;
    };

    class KAList
    {
    public:
        virtual void record(const dbcomm::NKAUpdate &rec) = 0;
    };

    virtual void get_list(List *iface) = 0;
    virtual bool get_sink(const dbcomm::SrvArrKey &key, Sink *iface) = 0;
    virtual void del(const dbcomm::SrvArrKey &key) = 0;
    virtual void get_ka_list(KAList *iface) = 0;
    virtual void put(const dbcomm::SrvArrKey &key, Source *iface) = 0;
    virtual void set_filter(bool filter_on, const Filter &filter = Filter()) = 0;
};

class DB : public DBIface, public QObject
{
public:
    DB()
        : m_context()
        , m_connection(m_context)
        , m_filter_on(false)
    { };

    int connect(const QString &db_user, const QString &db_password, const QString &db_name);

    //DBIface
    virtual void get_list(List *iface);
    virtual bool get_sink(const dbcomm::SrvArrKey &key, Sink *iface);
    virtual void get_ka_list(KAList *iface);
    virtual void del(const dbcomm::SrvArrKey &key);
    virtual void put(const dbcomm::SrvArrKey &key, Source *iface);
    virtual void set_filter(bool filter_on, const Filter &filter = Filter());

private:
    dbcore::Context m_context;
    dbcore::Connection m_connection;
    Filter m_filter;
    bool m_filter_on;
};
