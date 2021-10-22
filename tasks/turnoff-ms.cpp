#include "turnoff-ms.h"
//brtk
#include "brtk/task.h"

TURNOFF_MS::TURNOFF_MS(QWidget *parent, Qt::WFlags flags)
    : Editor(parent, flags)
{
    frame = new QWidget(this);
    m_turnoff_ms_form_ui.setupUi(frame);
    m_editroform_ui.gridLayout->addWidget(frame, 1, 0, 1, 9);

    setMinimumHeight(76);
    setMaximumHeight(76);
};

bool TURNOFF_MS::setData(QIODevice *blob, ka::KAInfo *ka)
{
    BRTK::Task::Header header;
    blob->read(reinterpret_cast<char*>(&header), sizeof(header));
    setHeader(header, ka);
    return true;
};

bool TURNOFF_MS::getData(QIODevice *blob, ka::KAInfo *ka)
{
    BRTK::Task::Header header;
    header.size = sizeof(header) + TurnoffMSSize;
    header.id.type = BRTK::Task::OffMS;
    getHeader(header, ka);
    blob->write(reinterpret_cast<char*>(&header), sizeof(header));
    return true;
};
