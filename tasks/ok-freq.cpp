#include "ok-freq.h"
//brtk
#include "brtk/task.h"

OK_FREQ::OK_FREQ(QWidget *parent, Qt::WFlags flags)
    : Editor(parent, flags)
{
    frame = new QWidget(this);
    m_ok_freq_form_ui.setupUi(frame);
    m_editroform_ui.gridLayout->addWidget(frame, 1, 0, 1, 9);

    m_ok_freq_form_ui.spinBoxFok1->setValue(1);
    m_ok_freq_form_ui.spinBoxFok2->setValue(1);
    m_ok_freq_form_ui.spinBoxFok3->setValue(1);
    m_ok_freq_form_ui.spinBoxFok4->setValue(1);

    connect(m_ok_freq_form_ui.comboBoxNum
        , SIGNAL(currentIndexChanged(int))
        , SLOT(comboBoxNum_indexChanged(int)));

    m_ok_freq_form_ui.comboBoxNum->setCurrentIndex(-1);

    setMinimumHeight(130);
    setMaximumHeight(130);
};

bool OK_FREQ::setData(QIODevice *blob, ka::KAInfo *ka)
{
    BRTK::Task::Header header;
    blob->read(reinterpret_cast<char*>(&header), sizeof(header));

    setHeader(header, ka);

    uchar count = 0;
    blob->read(reinterpret_cast<char*>(&count), sizeof(count));
    m_ok_freq_form_ui.comboBoxNum->setCurrentIndex(count - 1);

    ushort fok1 = 1;
    ushort fok2 = 1;
    ushort fok3 = 1;
    ushort fok4 = 1;
    blob->read(reinterpret_cast<char*>(&fok1), sizeof(fok1));
    blob->read(reinterpret_cast<char*>(&fok2), sizeof(fok2));
    blob->read(reinterpret_cast<char*>(&fok3), sizeof(fok3));
    blob->read(reinterpret_cast<char*>(&fok4), sizeof(fok4));
    m_ok_freq_form_ui.spinBoxFok1->setValue(fok1);
    m_ok_freq_form_ui.spinBoxFok2->setValue(fok2);
    m_ok_freq_form_ui.spinBoxFok3->setValue(fok3);
    m_ok_freq_form_ui.spinBoxFok4->setValue(fok4);
    return true;
};

bool OK_FREQ::getData(QIODevice *blob, ka::KAInfo *ka)
{
    BRTK::Task::Header header;
    header.size = sizeof(header);
    header.id.type = BRTK::Task::OKFreq;

    getHeader(header, ka);

    uchar count = m_ok_freq_form_ui.comboBoxNum->currentIndex() + 1;
    header.size += sizeof(count); //length byte
    header.size += (count * 2);

    blob->write(reinterpret_cast<char*>(&header), sizeof(header));

    ushort fok1 = m_ok_freq_form_ui.spinBoxFok1->value();
    ushort fok2 = m_ok_freq_form_ui.spinBoxFok2->value();
    ushort fok3 = m_ok_freq_form_ui.spinBoxFok3->value();
    ushort fok4 = m_ok_freq_form_ui.spinBoxFok4->value();

    blob->write(reinterpret_cast<char*>(&count), sizeof(count));

    if (count >= 1) blob->write(reinterpret_cast<char*>(&fok1), sizeof(fok1));
    if (count >= 2) blob->write(reinterpret_cast<char*>(&fok2), sizeof(fok2));
    if (count >= 3) blob->write(reinterpret_cast<char*>(&fok3), sizeof(fok3));
    if (count >= 4) blob->write(reinterpret_cast<char*>(&fok4), sizeof(fok4));

    return true;
};

void OK_FREQ::comboBoxNum_indexChanged(int i)
{
    m_ok_freq_form_ui.spinBoxFok4->setEnabled(false);
    m_ok_freq_form_ui.spinBoxFok3->setEnabled(false);
    m_ok_freq_form_ui.spinBoxFok2->setEnabled(false);
    m_ok_freq_form_ui.spinBoxFok1->setEnabled(false);
    switch (i)
    {
    case 3:	m_ok_freq_form_ui.spinBoxFok4->setEnabled(true);
    case 2:	m_ok_freq_form_ui.spinBoxFok3->setEnabled(true);
    case 1:	m_ok_freq_form_ui.spinBoxFok2->setEnabled(true);
    case 0:	m_ok_freq_form_ui.spinBoxFok1->setEnabled(true);
    };
};
