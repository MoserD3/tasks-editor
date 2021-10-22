#pragma once

#include <QtCore/QDateTime>
#include <QtCore/QAbstractListModel>

class DBIface;

namespace ka {
struct KAInfo
{
    int ms;
    int brtk_time;
    QDateTime msk_time;
};

class KAModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum {
        MSColumn,
        BRTKTimeColumn,
        MskTimeColumn,
        ColumnCount
    };

public:
    KAModel(DBIface *db, QObject *parent = 0);

    void resetModel();
    const KAInfo& key(int row) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

private:
    QList<KAInfo> m_records;
    DBIface *const m_db;
};
}; //ka
