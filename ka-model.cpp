#include "ka-model.h"
#include "db.h"
//libdb
#include "libdb/libdb-comm/nka.h"
//std
#include <cassert>

using namespace ka;

KAModel::KAModel(DBIface *db, QObject *parent)
    : QAbstractListModel(parent)
    , m_db(db)
{
    resetModel();
};

int KAModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_records.count();
};

const ka::KAInfo& KAModel::key(int row) const
{
    return m_records[row];
};

QVariant KAModel::data(const QModelIndex &index, int role) const
{
    const KAInfo &ka = m_records[index.row()];
    switch (role)
    {
    case Qt::EditRole:
    case Qt::DisplayRole:
        switch (index.column())
        {
        case MSColumn: return ka.ms;
        case BRTKTimeColumn: return ka.brtk_time;
        case MskTimeColumn: return ka.msk_time;
        };
    };
    return QVariant();
};

QVariant KAModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return QVariant();
    if (orientation != Qt::Horizontal) return QString::number(section);
    static const char* columns[ColumnCount] = { QT_TR_NOOP("MS"), QT_TR_NOOP("BRTK time"), QT_TR_NOOP("Msk time") };
    assert(section >= 0 && section < ColumnCount);
    return tr(columns[section]);
};

namespace {
    class KAListBuilder : public DBIface::KAList
    {
    public:
        typedef QList< KAInfo > List;

    public:
        KAListBuilder(List &list)
            : m_list(list)
        {
            m_list.clear();
        };

        virtual void record(const dbcomm::NKAUpdate &rec)
        {
            KAInfo info;
            info.ms = rec.ka_ms;
            info.brtk_time = rec.brtk_time;
            info.msk_time = rec.msk_time;
            m_list.append(info);
        };

    private:
        List& m_list;
    };
};//namespace

void KAModel::resetModel()
{
    beginResetModel();
    m_db->get_ka_list(&KAListBuilder(m_records));
    endResetModel();
};
