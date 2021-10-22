#pragma once

//libdb
#include "libdb/libdb-comm/srvarr.h"
//qt
#include <QtCore/QAbstractTableModel>

class DBIface;

class TasksModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum {
        KAColumn,
        TypeColumn,
        NameColumn,
        DTChangeColumn,
        DTCreateColumn,
        ColumnCount
    };

public:
    TasksModel(DBIface *db, QObject *parent = 0);

    void resetModel();
    const dbcomm::SrvArrKey& key(int row) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    virtual bool removeRows(int row, int count, const QModelIndex &ind);

private:
    QList<dbcomm::SrvArrRecord> m_records;
    DBIface *const m_db;
};
