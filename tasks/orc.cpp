#include "orc.h"
#include "../lst-model.h"
//brtk
#include "brtk/task.h"

ORC::ORC(QWidget *parent, Qt::WFlags flags)
    : Editor(parent, flags)
{
    frame = new QWidget(this);
    m_orc_form_ui.setupUi(frame);
    m_editroform_ui.gridLayout->addWidget(frame, 1, 0, 1, 9);

    m_rk_model = new lst::LstModel("rk.lst");
    m_orc_form_ui.comboBoxORC->setModel(m_rk_model);

    m_orc_form_ui.comboBoxORC->setCurrentIndex(-1);

    setMinimumHeight(76);
    setMaximumHeight(76);
};

bool ORC::setData(QIODevice *blob, ka::KAInfo *ka)
{
    BRTK::Task::Header header;
    blob->read(reinterpret_cast<char*>(&header), sizeof(header));

    setHeader(header, ka);

    uchar rk = 0;
    blob->read(reinterpret_cast<char*>(&rk), sizeof(rk));

    int i = m_orc_form_ui.comboBoxORC->findData(rk, Qt::EditRole);
    m_orc_form_ui.comboBoxORC->setCurrentIndex(i);

    return true;
};

bool ORC::getData(QIODevice *blob, ka::KAInfo *ka)
{
    BRTK::Task::Header header;
    header.size = sizeof(header) + ORCSize;
    header.id.type = BRTK::Task::ORC;

    getHeader(header, ka);

    blob->write(reinterpret_cast<char*>(&header), sizeof(header));

    int i = m_orc_form_ui.comboBoxORC->currentIndex();
    uchar rk = 0;
    if (i >= 0) rk = m_rk_model->key(i).id;

    blob->write(reinterpret_cast<char*>(&rk), sizeof(rk));
    return true;
};
