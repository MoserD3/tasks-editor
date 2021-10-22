#include "kpr2.h"
#include "../val3.h"
//brtk
#include "brtk/task.h"

KPR2::KPR2(QWidget *parent, Qt::WFlags flags)
    : Editor(parent, flags)
{
    frame = new QWidget(this);
    m_kpr2_form_ui.setupUi(frame);
    m_editroform_ui.gridLayout->addWidget(frame, 1, 0, 1, 9);

    m_kpr2_form_ui.spinBoxNSNum->setValue(1);
    m_kpr2_form_ui.spinBoxNSGroupNum->setValue(1);
    m_kpr2_form_ui.comboBoxReceiveSpeed->setCurrentIndex(-1);
    m_kpr2_form_ui.spinBoxInterval->setValue(1);
    m_kpr2_form_ui.spinBoxPeriod->setValue(1);
    m_kpr2_form_ui.spinBoxKICount->setValue(1);
    m_kpr2_form_ui.comboBoxTransmitSpeed->setCurrentIndex(-1);
    m_kpr2_form_ui.spinBoxCarrierFreq->setValue(1);
    m_kpr2_form_ui.spinBoxDuration->setValue(1);

    setMinimumHeight(197);
    setMaximumHeight(197);
};


bool KPR2::setData(QIODevice *blob, ka::KAInfo *ka)
{
    BRTK::Task::Header header;
    blob->read(reinterpret_cast<char*>(&header), sizeof(header));

    setHeader(header, ka);

    VAL3 ns(1);
    VAL3 gns(1);
    uchar num_r = -1;
    uchar inter = 1;
    uchar per = 1;
    uchar kic = 1;
    uchar num_t = -1;
    ushort freq = 1;
    uchar dur = 1;

    blob->read(reinterpret_cast<char*>(&ns), sizeof(ns));
    blob->read(reinterpret_cast<char*>(&gns), sizeof(gns));
    blob->read(reinterpret_cast<char*>(&num_r), sizeof(num_r));
    blob->read(reinterpret_cast<char*>(&inter), sizeof(inter));
    blob->read(reinterpret_cast<char*>(&per), sizeof(per));
    blob->read(reinterpret_cast<char*>(&kic), sizeof(kic));
    blob->read(reinterpret_cast<char*>(&num_t), sizeof(num_t));
    blob->read(reinterpret_cast<char*>(&freq), sizeof(freq));
    blob->read(reinterpret_cast<char*>(&dur), sizeof(dur));

    m_kpr2_form_ui.spinBoxNSNum->setValue(ns.get_val());
    m_kpr2_form_ui.spinBoxNSGroupNum->setValue(gns.get_val());
    m_kpr2_form_ui.comboBoxReceiveSpeed->setCurrentIndex(indx(num_r));
    m_kpr2_form_ui.spinBoxInterval->setValue(inter);
    m_kpr2_form_ui.spinBoxPeriod->setValue(per);
    m_kpr2_form_ui.spinBoxKICount->setValue(kic);
    m_kpr2_form_ui.comboBoxTransmitSpeed->setCurrentIndex(indx(num_t));
    m_kpr2_form_ui.spinBoxCarrierFreq->setValue(freq);
    m_kpr2_form_ui.spinBoxDuration->setValue(dur);

    return true;
};

bool KPR2::getData(QIODevice *blob, ka::KAInfo *ka)
{
    BRTK::Task::Header header;
    header.size = sizeof(header) + KPR2Size;
    header.id.type = BRTK::Task::KPR2;

    getHeader(header, ka);

    blob->write(reinterpret_cast<char*>(&header), sizeof(header));
    VAL3 ns(m_kpr2_form_ui.spinBoxNSNum->value());
    VAL3 gns(m_kpr2_form_ui.spinBoxNSGroupNum->value());
    uchar num_r = num(m_kpr2_form_ui.comboBoxReceiveSpeed->currentIndex());
    uchar inter = m_kpr2_form_ui.spinBoxInterval->value();
    uchar per = m_kpr2_form_ui.spinBoxPeriod->value();
    uchar kic = m_kpr2_form_ui.spinBoxKICount->value();
    uchar num_t = num(m_kpr2_form_ui.comboBoxTransmitSpeed->currentIndex());
    ushort freq = m_kpr2_form_ui.spinBoxCarrierFreq->value();
    uchar dur = m_kpr2_form_ui.spinBoxDuration->value();

    blob->write(reinterpret_cast<char*>(&ns), sizeof(ns));
    blob->write(reinterpret_cast<char*>(&gns), sizeof(gns));
    blob->write(reinterpret_cast<char*>(&num_r), sizeof(num_r));
    blob->write(reinterpret_cast<char*>(&inter), sizeof(inter));
    blob->write(reinterpret_cast<char*>(&per), sizeof(per));
    blob->write(reinterpret_cast<char*>(&kic), sizeof(kic));
    blob->write(reinterpret_cast<char*>(&num_t), sizeof(num_t));
    blob->write(reinterpret_cast<char*>(&freq), sizeof(freq));
    blob->write(reinterpret_cast<char*>(&dur), sizeof(dur));
    return true;
};

uchar KPR2::num(int index)
{
    if (index == 0)  return 1;
    else
        if (index == 1)  return 2;
        else
            if (index == 2)  return 3;
            else
                if (index == 3)  return 5;
                else
                    return 0;
};

int KPR2::indx(uchar num)
{
    if (num == 1)  return 0;
    else
        if (num == 2)  return 1;
        else
            if (num == 3)  return 2;
            else
                if (num == 5)  return 3;
                else
                    return -1;
};
