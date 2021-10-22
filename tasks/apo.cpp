#include "apo.h"
//brtk
#include "brtk/task.h"

APO::APO(QWidget *parent, Qt::WFlags flags)
    : Editor(parent, flags)
{
    frame = new QWidget(this);
    m_apoform_ui.setupUi(frame);
    m_editroform_ui.gridLayout->addWidget(frame, 1, 0, 1, 9);

    m_apoform_ui.spinBoxFpk1->setValue(1);
    m_apoform_ui.spinBoxFpk2->setValue(1);

    setMinimumHeight(76);
    setMaximumHeight(76);
};

bool APO::setData(QIODevice *blob, ka::KAInfo *ka)
{
    BRTK::Task::Header header;
    blob->read(reinterpret_cast<char*>(&header), sizeof(header));

    setHeader(header, ka);

    ushort fpk1 = 1;
    ushort fpk2 = 1;
    blob->read(reinterpret_cast<char*>(&fpk1), sizeof(fpk1));
    blob->read(reinterpret_cast<char*>(&fpk2), sizeof(fpk2));

    m_apoform_ui.spinBoxFpk1->setValue(fpk1);
    m_apoform_ui.spinBoxFpk2->setValue(fpk2);

    return true;
};

bool APO::getData(QIODevice *blob, ka::KAInfo *ka)
{
    BRTK::Task::Header header;
    header.size = sizeof(header) + APOSize;
    header.id.type = BRTK::Task::APO;

    getHeader(header, ka);

    blob->write(reinterpret_cast<char*>(&header), sizeof(header));

    ushort fpk1 = m_apoform_ui.spinBoxFpk1->value();
    ushort fpk2 = m_apoform_ui.spinBoxFpk2->value();

    blob->write(reinterpret_cast<char*>(&fpk1), sizeof(fpk1));
    blob->write(reinterpret_cast<char*>(&fpk2), sizeof(fpk2));

    return true;
};
