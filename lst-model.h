#pragma once

#include <QtCore/QAbstractListModel>

namespace lst {

struct LstInfo
{
    LstInfo(int i = 0, const QString &n = QString::null)
        : id(i)
        , name(n)
    { };

    int id;
    QString name;
};

class LstModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum {
        IDColumn,
        NameColumn,
        ColumnCount
    };

public:
    LstModel(const QString &fname = QString::null, QObject *parent = NULL);

    void resetModel(const QString &fname);
    const LstInfo& key(int row) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

private:
    QList<LstInfo> m_list;
};
};//lst
