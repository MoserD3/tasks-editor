#include "ms-freq.h"
//brtk
#include "brtk/task.h"

MS_FREQ::MS_FREQ(QWidget *parent, Qt::WFlags flags)
    : Editor(parent, flags)
{
    frame = new QWidget(this);
    m_msfreq_form_ui.setupUi(frame);
    m_editroform_ui.gridLayout->addWidget(frame, 1, 0, 1, 9);

    m_msfreq_form_ui.spinBoxFms1->setValue(1);
    m_msfreq_form_ui.spinBoxFms2->setValue(1);

    setMinimumHeight(76);
    setMaximumHeight(76);
};

bool MS_FREQ::setData(QIODevice *blob, ka::KAInfo *ka)
{
    BRTK::Task::Header header;
    blob->read(reinterpret_cast<char*>(&header), sizeof(header));

    setHeader(header, ka);

    ushort fms1 = 1;
    ushort fms2 = 1;
    blob->read(reinterpret_cast<char*>(&fms1), sizeof(fms1));
    blob->read(reinterpret_cast<char*>(&fms2), sizeof(fms2));

    m_msfreq_form_ui.spinBoxFms1->setValue(fms1);
    m_msfreq_form_ui.spinBoxFms2->setValue(fms2);

    return true;
};

bool MS_FREQ::getData(QIODevice *blob, ka::KAInfo *ka)
{
    BRTK::Task::Header header;
    header.size = sizeof(header) + MSFreqSize;
    header.id.type = BRTK::Task::MSFreq;

    getHeader(header, ka);

    blob->write(reinterpret_cast<char*>(&header), sizeof(header));

    ushort fms1 = m_msfreq_form_ui.spinBoxFms1->value();
    ushort fms2 = m_msfreq_form_ui.spinBoxFms2->value();

    blob->write(reinterpret_cast<char*>(&fms1), sizeof(fms1));
    blob->write(reinterpret_cast<char*>(&fms2), sizeof(fms2));

    return true;
};
