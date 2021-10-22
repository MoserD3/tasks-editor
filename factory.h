#pragma once

#include "editor.h"
#include "tasks/apo.h"
#include "tasks/self-noise.h"
#include "tasks/ok-freq.h"
#include "tasks/turnoff-ms.h"
#include "tasks/rko.h"
#include "tasks/ms-freq.h"
#include "tasks/ku-params.h"
#include "tasks/vm-count.h"
#include "tasks/flags.h"
#include "tasks/free-access.h"
#include "tasks/kpr2.h"
#include "tasks/orc.h"
#include "tasks/tmi.h"
#include "tasks/regions.h"
#include "tasks/call-adr.h"
#include "tasks/freq-pk.h"
//brtk
#include "brtk/task.h"

class Factory
{
public:
    virtual Editor* create(QWidget *parent) const = 0;
};

template< class Type >
class FactoryTempl : public Factory
{
public:
    virtual Editor* create(QWidget *parent) const { return new Type(parent); };
    static const FactoryTempl instance;
};

template< class Type >
const FactoryTempl< Type > FactoryTempl< Type >::instance;

class FactoryContainer
{
public:
    QHash< int, const Factory* > factories;
    FactoryContainer()
    {
        factories.insert(BRTK::Task::APO, &(FactoryTempl< APO >::instance));
        factories.insert(BRTK::Task::APOSelfNoise, &(FactoryTempl< SELF_NOISE >::instance));
        factories.insert(BRTK::Task::OKFreq, &(FactoryTempl< OK_FREQ >::instance));
        factories.insert(BRTK::Task::OffMS, &(FactoryTempl< TURNOFF_MS >::instance));
        factories.insert(BRTK::Task::RKO, &(FactoryTempl< RKO >::instance));
        factories.insert(BRTK::Task::MSFreq, &(FactoryTempl< MS_FREQ >::instance));
        factories.insert(BRTK::Task::KUParams, &(FactoryTempl< KU_PARAMS >::instance));
        factories.insert(BRTK::Task::VMCount, &(FactoryTempl< VM_COUNT >::instance));
        factories.insert(BRTK::Task::Flags, &(FactoryTempl< FLAGS >::instance));
        factories.insert(BRTK::Task::FreeAccess, &(FactoryTempl< FREE_ACCESS >::instance));
        factories.insert(BRTK::Task::KPR2, &(FactoryTempl< KPR2 >::instance));
        factories.insert(BRTK::Task::ORC, &(FactoryTempl< ORC >::instance));
        factories.insert(BRTK::Task::TMI, &(FactoryTempl< TMI >::instance));
        factories.insert(BRTK::Task::Regions, &(FactoryTempl< REGIONS >::instance));
        factories.insert(BRTK::Task::CallAddr, &(FactoryTempl< CALL_ADR >::instance));
        factories.insert(BRTK::Task::FreqPK, &(FactoryTempl< FREQ_PK >::instance));
    };

    Editor* create(int pz_type, QWidget *parent) const
    {
        return factories[pz_type]->create(parent);
    };

    static const FactoryContainer& instance()
    {
        static const FactoryContainer inst;
        return inst;
    };
};
