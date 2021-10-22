#include "tasks-model.h"
#include "trnames/tasktype.h"
#include "db.h"
//std
#include <cassert>

TasksModel::TasksModel(DBIface *db, QObject *parent)
    : QAbstractTableModel(parent)
    , m_db(db)
{ };

int TasksModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return m_records.count();
};

const dbcomm::SrvArrKey& TasksModel::key(int row) const
{
    return m_records[row];
};

int TasksModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return ColumnCount;
};

QVariant TasksModel::data(const QModelIndex &index, int role) const
{
    const dbcomm::SrvArrRecord &record = m_records[index.row()];
    switch (role)
    {
    case Qt::EditRole:
        switch (index.column())
        {
        case KAColumn:          return static_cast<int>(record.ka);
        case TypeColumn:        return static_cast<int>(record.subtp);
        case NameColumn:        return static_cast<QString>(record.name);
        case DTChangeColumn:    return static_cast<QDateTime>(record.dt_change);
        case DTCreateColumn:    return static_cast<QDateTime>(record.dt);
        };
        break;
    case Qt::DisplayRole:
        switch (index.column())
        {
        case KAColumn:          return QString::number(record.ka);
        case TypeColumn:        return trnames::TaskType::instance()->getStringByID(record.subtp);
        case NameColumn:        return record.name;
        case DTChangeColumn:    return record.dt_change;
        case DTCreateColumn:    return record.dt;
        };
        break;
    };
    return QVariant();
};

QVariant TasksModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return QVariant();
    if (orientation != Qt::Horizontal) return QString::number(section);
    static const char* columns[ColumnCount] = { QT_TR_NOOP("#KA"), QT_TR_NOOP("Type"), QT_TR_NOOP("Name"), QT_TR_NOOP("Date change"), QT_TR_NOOP("Date create") };
    assert(section >= 0 && section < ColumnCount);
    return tr(columns[section]);
};

namespace {
    class TasksListBuilder : public DBIface::List
    {
    public:
        typedef QList< dbcomm::SrvArrRecord > List;

    public:
        TasksListBuilder(List &list)
            : m_list(list)
        {
            m_list.clear();
        };

        virtual void record(const dbcomm::SrvArrRecord &rec)
        {
            m_list.append(rec);
        };
    private:
        List& m_list;
    };
}; //namespace

void TasksModel::resetModel()
{
    beginResetModel();
    TasksListBuilder builder(m_records);
    m_db->get_list(&builder);
    endResetModel();
};

bool TasksModel::removeRows(int row, int count, const QModelIndex &ind)
{
    beginRemoveRows(ind, row, row + count - 1);
    while (count--) {
        m_db->del(key(row));
        m_records.removeAt(row);
    };
    endRemoveRows();
    return true;
};
