#include "lst-model.h"
//std
#include <cassert>
//qt
#include <QtCore/QFile>
#include <QtCore/QTextStream>

using namespace lst;

LstModel::LstModel(const QString &fname, QObject *parent)
    : QAbstractListModel(parent)
{
    if (!fname.isNull())
        resetModel(fname);
};

int LstModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_list.count();
};

const LstInfo& LstModel::key(int row) const
{
    return m_list[row];
};

QVariant LstModel::data(const QModelIndex &index, int role) const
{
    const LstInfo &rk = m_list[index.row()];
    switch (role)
    {
    case Qt::EditRole: return rk.id;
    case Qt::DisplayRole: return rk.name;
    };
    return QVariant();
};

QVariant LstModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return QVariant();
    if (orientation != Qt::Horizontal) return QString::number(section);
    static const char* columns[ColumnCount] = { QT_TR_NOOP("ID"), QT_TR_NOOP("Name") };
    assert(section >= 0 && section < ColumnCount);
    return tr(columns[section]);
};

void LstModel::resetModel(const QString &fname)
{
    beginResetModel();
    QFile file(fname);
    if (!file.exists()) {
        //File not exists
        return;
    };
    if (!file.open(QIODevice::ReadOnly)) {
        //File not open
        return;
    };

    QTextStream ts(&file);
    bool ok;
    int i;
    LstInfo li;
    QString str;
    while (!ts.atEnd()) {
        str = ts.readLine();
        if (str.isEmpty()) {
            //Empty string
            break;
        };
        i = str.indexOf(' ');
        li.id = str.left(i).toInt(&ok);
        if (!ok) {
            //error read id
            break;
        };
        li.name = str.mid(i + 1);
        m_list.append(li);
    };

    file.close();
    endResetModel();
};
