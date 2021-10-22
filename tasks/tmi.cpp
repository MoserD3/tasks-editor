#include "tmi.h"
#include "../lst-model.h"
//brtk
#include "brtk/task.h"

TMI::TMI(QWidget *parent, Qt::WFlags flags)
    : Editor(parent, flags)
{
    frame = new QWidget(this);
    m_tmi_form_ui.setupUi(frame);
    m_editroform_ui.gridLayout->addWidget(frame, 1, 0, 1, 9);

    m_tmi_model = new lst::LstModel("sensors.lst");
    m_tmi_form_ui.comboBoxS1->setModel(m_tmi_model);
    m_tmi_form_ui.comboBoxS2->setModel(m_tmi_model);
    m_tmi_form_ui.comboBoxS3->setModel(m_tmi_model);
    m_tmi_form_ui.comboBoxS4->setModel(m_tmi_model);
    m_tmi_form_ui.comboBoxS1->setCurrentIndex(0);
    m_tmi_form_ui.comboBoxS2->setCurrentIndex(0);
    m_tmi_form_ui.comboBoxS3->setCurrentIndex(0);
    m_tmi_form_ui.comboBoxS4->setCurrentIndex(0);

    m_tmi_form_ui.comboBoxIntCount->setCurrentIndex(-1);

    m_tmi_form_ui.spinBoxIntPeriod->setValue(1);
    m_tmi_form_ui.spinBoxCyCount->setValue(1);

    setMinimumHeight(135);
    setMaximumHeight(135);
};

bool TMI::setData(QIODevice *blob, ka::KAInfo *ka)
{
    BRTK::Task::Header header;
    blob->read(reinterpret_cast<char*>(&header), sizeof(header));

    setHeader(header, ka);

    int i = 0;
    uchar s1 = 0;
    uchar s2 = 0;
    uchar s3 = 0;
    uchar s4 = 0;
    blob->read(reinterpret_cast<char*>(&s1), sizeof(s1));
    blob->read(reinterpret_cast<char*>(&s2), sizeof(s2));
    blob->read(reinterpret_cast<char*>(&s3), sizeof(s3));
    blob->read(reinterpret_cast<char*>(&s4), sizeof(s4));

    i = m_tmi_form_ui.comboBoxS1->findData(s1, Qt::EditRole);
    m_tmi_form_ui.comboBoxS1->setCurrentIndex(i);
    i = m_tmi_form_ui.comboBoxS2->findData(s2, Qt::EditRole);
    m_tmi_form_ui.comboBoxS2->setCurrentIndex(i);
    i = m_tmi_form_ui.comboBoxS3->findData(s3, Qt::EditRole);
    m_tmi_form_ui.comboBoxS3->setCurrentIndex(i);
    i = m_tmi_form_ui.comboBoxS4->findData(s4, Qt::EditRole);
    m_tmi_form_ui.comboBoxS4->setCurrentIndex(i);

    uchar ic = 0;
    blob->read(reinterpret_cast<char*>(&ic), sizeof(ic));

    if (ic == 1)
        m_tmi_form_ui.comboBoxIntCount->setCurrentIndex(0);
    else
        if (ic == 3)
            m_tmi_form_ui.comboBoxIntCount->setCurrentIndex(1);
        else
            m_tmi_form_ui.comboBoxIntCount->setCurrentIndex(-1);

    ushort ip = 1;
    ushort cc = 1;
    blob->read(reinterpret_cast<char*>(&ip), sizeof(ip));
    blob->read(reinterpret_cast<char*>(&cc), sizeof(cc));

    m_tmi_form_ui.spinBoxIntPeriod->setValue(ip);
    m_tmi_form_ui.spinBoxCyCount->setValue(cc);
    return true;
};

bool TMI::getData(QIODevice *blob, ka::KAInfo *ka)
{
    BRTK::Task::Header header;
    header.size = sizeof(header) + TMISize;
    header.id.type = BRTK::Task::TMI;

    getHeader(header, ka);

    blob->write(reinterpret_cast<char*>(&header), sizeof(header));

    int i = 0;
    uchar s1 = 0;
    uchar s2 = 0;
    uchar s3 = 0;
    uchar s4 = 0;

    i = m_tmi_form_ui.comboBoxS1->currentIndex();
    s1 = 0;
    if (i >= 0) s1 = m_tmi_model->key(i).id;
    i = m_tmi_form_ui.comboBoxS2->currentIndex();
    s2 = 0;
    if (i >= 0) s2 = m_tmi_model->key(i).id;
    i = m_tmi_form_ui.comboBoxS3->currentIndex();
    s3 = 0;
    if (i >= 0) s3 = m_tmi_model->key(i).id;
    i = m_tmi_form_ui.comboBoxS4->currentIndex();
    s4 = 0;
    if (i >= 0) s4 = m_tmi_model->key(i).id;

    blob->write(reinterpret_cast<char*>(&s1), sizeof(s1));
    blob->write(reinterpret_cast<char*>(&s2), sizeof(s2));
    blob->write(reinterpret_cast<char*>(&s3), sizeof(s3));
    blob->write(reinterpret_cast<char*>(&s4), sizeof(s4));

    i = m_tmi_form_ui.comboBoxIntCount->currentIndex();
    uchar ic = 0;
    if (i == 0)
        ic = 1;
    else
        if (i == 1)
            ic = 3;
        else
            ic = 0;

    blob->write(reinterpret_cast<char*>(&ic), sizeof(ic));
    ushort ip = m_tmi_form_ui.spinBoxIntPeriod->value();
    ushort cc = m_tmi_form_ui.spinBoxCyCount->value();
    blob->write(reinterpret_cast<char*>(&ip), sizeof(ip));
    blob->write(reinterpret_cast<char*>(&cc), sizeof(cc));
    return true;
};
