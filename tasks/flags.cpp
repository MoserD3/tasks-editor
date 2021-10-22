#include "flags.h"
#include "brtk/task.h"

FLAGS::FLAGS(QWidget *parent, Qt::WFlags flags) : Editor(parent, flags)
{
    frame = new QWidget(this);
    m_flagform_ui.setupUi(frame);
    m_editroform_ui.gridLayout->addWidget(frame, 1, 0, 1, 9);

    m_flagform_ui.spinBoxFlag->setValue(1);

    setMinimumHeight(76);
    setMaximumHeight(76);
};

bool FLAGS::setData(QIODevice *blob, ka::KAInfo *ka)
{
    BRTK::Task::Header header;
    blob->read(reinterpret_cast<char*>(&header), sizeof(header));

    setHeader(header, ka);

    uchar flag = 1;
    blob->read(reinterpret_cast<char*>(&flag), sizeof(flag));

    m_flagform_ui.spinBoxFlag->setValue(flag);

    return true;
};

bool FLAGS::getData(QIODevice *blob, ka::KAInfo *ka)
{
    BRTK::Task::Header header;
    header.size = sizeof(header) + FlagsSize;
    header.id.type = BRTK::Task::Flags;

    getHeader(header, ka);

    blob->write(reinterpret_cast<char*>(&header), sizeof(header));

    uchar flag = m_flagform_ui.spinBoxFlag->value();

    blob->write(reinterpret_cast<char*>(&flag), sizeof(flag));

    return true;
};
