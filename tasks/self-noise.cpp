#include "self-noise.h"
//brtk
#include "brtk/task.h"

SELF_NOISE::SELF_NOISE(QWidget *parent, Qt::WFlags flags)
    : Editor(parent, flags)
{
    frame = new QWidget(this);
    m_self_noise_form_ui.setupUi(frame);
    m_editroform_ui.gridLayout->addWidget(frame, 1, 0, 1, 9);

    setMinimumHeight(76);
    setMaximumHeight(76);
};

bool SELF_NOISE::setData(QIODevice *blob, ka::KAInfo *ka)
{
    BRTK::Task::Header header;
    blob->read(reinterpret_cast<char*>(&header), sizeof(header));
    setHeader(header, ka);
    return true;
};

bool SELF_NOISE::getData(QIODevice *blob, ka::KAInfo *ka)
{
    BRTK::Task::Header header;
    header.size = sizeof(header) + SelfNoiseSize;
    header.id.type = BRTK::Task::APOSelfNoise;
    getHeader(header, ka);
    blob->write(reinterpret_cast<char*>(&header), sizeof(header));
    return true;
};
