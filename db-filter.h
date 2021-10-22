#pragma once

//libdb
#include "libdb/libdb-core/condition.h"
#include "libdb/libdb-core/fieldutil.h"
#include "libdb/libdb-core/exprutil.h"
#include "libdb/libdb-core/parameter.h"
#include "libdb/libdb-comm/srvarr.h"
//brtk
#include "brtk/array.h"

class TasksEditorFilter : public dbcore::CompCond
{
public:
    TasksEditorFilter(short nka = -1, const dbcore::Date &dtfrom = dbcore::Date(), const dbcore::Date &dtto = dbcore::Date())
        : CompCond(dbcomm::SrvArrRecord::getClassMetaRecord())
        , m_tp(BRTK::ArrayPK::Task)
        , m_nka(nka)
        , m_dtfrom(dtfrom)
        , m_dtto(dtto)
        , m_equal_tp(DB_FIELD(dbcomm::SrvArrRecord, tp), m_tp)
        , m_equal_nka(DB_FIELD(dbcomm::SrvArrRecord, ka), m_nka)
        , m_gr_equal_dtfrom(DB_FIELD(dbcomm::SrvArrRecord, dt_change), m_dtfrom)
        , m_less_equal_to(DB_FIELD(dbcomm::SrvArrRecord, dt_change), m_dtto)
        , m_list_expr()
    {
        m_list_expr.clear();
        m_list_expr &= m_equal_tp;
        if (nka)
            m_list_expr &= m_equal_nka;
        if (!dtfrom.isNull())
            m_list_expr &= m_gr_equal_dtfrom;
        if (!dtto.isNull())
            m_list_expr &= m_less_equal_to;
        setExpression(m_list_expr);
    };

private:
    dbcore::ParamShort m_tp;
    dbcore::EFieldEqual m_equal_tp;
    dbcore::ParamShort m_nka;
    dbcore::EFieldEqual m_equal_nka;
    dbcore::ParamDate m_dtfrom;
    dbcore::EFieldGreaterEqual m_gr_equal_dtfrom;
    dbcore::ParamDate m_dtto;
    dbcore::EFieldLessEqual m_less_equal_to;
    dbcore::ListAndExpr m_list_expr;
};
