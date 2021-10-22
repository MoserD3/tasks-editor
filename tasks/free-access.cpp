#include "free-access.h"
//brtk
#include "brtk/task.h"

FREE_ACCESS::FREE_ACCESS(QWidget *parent, Qt::WFlags flags)
    : Editor(parent, flags)
{
    frame = new QWidget(this);
    m_free_access_form_ui.setupUi(frame);
    m_editroform_ui.gridLayout->addWidget(frame, 1, 0, 1, 9);

    m_free_access_form_ui.spinBoxCount->setValue(1);

    setMinimumHeight(76);
    setMaximumHeight(76);
};

bool FREE_ACCESS::setData(QIODevice *blob, ka::KAInfo *ka)
{
    BRTK::Task::Header header;
    blob->read(reinterpret_cast<char*>(&header), sizeof(header));

    setHeader(header, ka);

    uchar count = 1;
    blob->read(reinterpret_cast<char*>(&count), sizeof(count));

    m_free_access_form_ui.spinBoxCount->setValue(count);

    return true;
};

bool FREE_ACCESS::getData(QIODevice *blob, ka::KAInfo *ka)
{
    BRTK::Task::Header header;
    header.size = sizeof(header) + FreeAccessSize;
    header.id.type = BRTK::Task::FreeAccess;

    getHeader(header, ka);

    blob->write(reinterpret_cast<char*>(&header), sizeof(header));

    uchar count = m_free_access_form_ui.spinBoxCount->value();
    blob->write(reinterpret_cast<char*>(&count), sizeof(count));
    return true;
};
