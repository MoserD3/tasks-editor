#include "ku-params.h"
//brtk
#include "brtk/task.h"

KU_PARAMS::KU_PARAMS(QWidget *parent, Qt::WFlags flags)
    : Editor(parent, flags)
{
    frame = new QWidget(this);
    m_ku_params_form_ui.setupUi(frame);
    m_editroform_ui.gridLayout->addWidget(frame, 1, 0, 1, 9);

    m_ku_params_form_ui.spinBoxCCC->setValue(1);
    m_ku_params_form_ui.spinBoxCCSize->setValue(1);

    setMinimumHeight(76);
    setMaximumHeight(76);
};

bool KU_PARAMS::setData(QIODevice *blob, ka::KAInfo *ka)
{
    BRTK::Task::Header header;
    blob->read(reinterpret_cast<char*>(&header), sizeof(header));

    setHeader(header, ka);

    uchar ccc = 1;
    uchar ccsize = 1;
    blob->read(reinterpret_cast<char*>(&ccc), sizeof(ccc));
    blob->read(reinterpret_cast<char*>(&ccsize), sizeof(ccsize));

    m_ku_params_form_ui.spinBoxCCC->setValue(ccc);
    m_ku_params_form_ui.spinBoxCCSize->setValue(ccsize);

    return true;
};

bool KU_PARAMS::getData(QIODevice *blob, ka::KAInfo *ka)
{
    BRTK::Task::Header header;
    header.size = sizeof(header) + KUParamsSize;
    header.id.type = BRTK::Task::KUParams;

    getHeader(header, ka);

    blob->write(reinterpret_cast<char*>(&header), sizeof(header));

    uchar ccc = m_ku_params_form_ui.spinBoxCCC->value();
    uchar ccsize = m_ku_params_form_ui.spinBoxCCSize->value();
    blob->write(reinterpret_cast<char*>(&ccc), sizeof(ccc));
    blob->write(reinterpret_cast<char*>(&ccsize), sizeof(ccsize));

    return true;
};
