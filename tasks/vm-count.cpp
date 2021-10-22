#include "vm-count.h"
//brtk
#include "brtk/task.h"

VM_COUNT::VM_COUNT(QWidget *parent, Qt::WFlags flags)
    : Editor(parent, flags)
{
    frame = new QWidget(this);
    m_vm_count_form_ui.setupUi(frame);
    m_editroform_ui.gridLayout->addWidget(frame, 1, 0, 1, 9);

    m_vm_count_form_ui.spinBoxSignalingVM->setValue(1);
    m_vm_count_form_ui.spinBoxDataVM->setValue(1);

    setMinimumHeight(76);
    setMaximumHeight(76);
};

bool VM_COUNT::setData(QIODevice *blob, ka::KAInfo *ka)
{
    BRTK::Task::Header header;
    blob->read(reinterpret_cast<char*>(&header), sizeof(header));

    setHeader(header, ka);

    uchar sig = 1;
    ushort dat = 1;
    blob->read(reinterpret_cast<char*>(&sig), sizeof(sig));
    blob->read(reinterpret_cast<char*>(&dat), sizeof(dat));

    m_vm_count_form_ui.spinBoxSignalingVM->setValue(sig);
    m_vm_count_form_ui.spinBoxDataVM->setValue(dat);
    return true;
};

bool VM_COUNT::getData(QIODevice *blob, ka::KAInfo *ka)
{
    BRTK::Task::Header header;
    header.size = sizeof(header) + VMCountSize;
    header.id.type = BRTK::Task::VMCount;

    getHeader(header, ka);

    blob->write(reinterpret_cast<char*>(&header), sizeof(header));

    uchar sig = m_vm_count_form_ui.spinBoxSignalingVM->value();
    uchar dat = m_vm_count_form_ui.spinBoxDataVM->value();

    blob->write(reinterpret_cast<char*>(&sig), sizeof(sig));
    blob->write(reinterpret_cast<char*>(&dat), sizeof(dat));
    return true;
};
