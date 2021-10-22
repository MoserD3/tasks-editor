#include "rko.h"
//brtk
#include "brtk/task.h"

RKO::RKO(QWidget *parent, Qt::WFlags flags)
    : Editor(parent, flags)
{
    frame = new QWidget(this);
    m_rko_form_ui.setupUi(frame);
    m_editroform_ui.gridLayout->addWidget(frame, 1, 0, 1, 9);

    m_rko_form_ui.spinBoxFreqOK->setValue(1);
    m_rko_form_ui.comboBoxPower->setCurrentIndex(0);

    setMinimumHeight(76);
    setMaximumHeight(76);
};

bool RKO::setData(QIODevice *blob, ka::KAInfo *ka)
{
    BRTK::Task::Header header;
    blob->read(reinterpret_cast<char*>(&header), sizeof(header));

    setHeader(header, ka);

    ushort ok_freq;
    uchar power;
    blob->read(reinterpret_cast<char*>(&ok_freq), sizeof(ok_freq));
    blob->read(reinterpret_cast<char*>(&power), sizeof(power));

    m_rko_form_ui.spinBoxFreqOK->setValue(ok_freq);
    m_rko_form_ui.comboBoxPower->setCurrentIndex(power - 1);

    return true;
};

bool RKO::getData(QIODevice *blob, ka::KAInfo *ka)
{
    BRTK::Task::Header header;
    header.size = sizeof(header) + RKOSize;
    header.id.type = BRTK::Task::RKO;

    getHeader(header, ka);

    blob->write(reinterpret_cast<char*>(&header), sizeof(header));

    ushort ok_freq = m_rko_form_ui.spinBoxFreqOK->value();
    uchar power = m_rko_form_ui.comboBoxPower->currentIndex() + 1;
    blob->write(reinterpret_cast<char*>(&ok_freq), sizeof(ok_freq));
    blob->write(reinterpret_cast<char*>(&power), sizeof(power));

    return true;
};
