#include "editor.h"

Editor::Editor(QWidget *parent, Qt::WFlags flags)
    : QWidget(parent, flags)
{
    m_editroform_ui.setupUi(this);
    m_editroform_ui.comboBoxBand->setCurrentIndex(0);
    m_editroform_ui.spinBoxVersion->setValue(1);
    QDateTime now = QDateTime::currentDateTime();
    m_editroform_ui.dateTimeEditBegin->setDateTime(now);
    m_editroform_ui.dateTimeEditEnd->setDateTime(now);

    connect(m_editroform_ui.pushButtonAcept, SIGNAL(clicked()), parent, SLOT(pushButtonAccept_clicked()));
    connect(m_editroform_ui.pushButtonCancel, SIGNAL(clicked()), parent, SLOT(pushButtonCancel_clicked()));
};

bool Editor::setHeader(const BRTK::Task::Header &header, ka::KAInfo *ka)
{
    int index = m_editroform_ui.comboBoxBand->findText(QString::number(header.id.band_code));
    m_editroform_ui.comboBoxBand->setCurrentIndex(index);
    m_editroform_ui.spinBoxVersion->setValue(header.id.variant);
    m_editroform_ui.dateTimeEditBegin->setDateTime(ka->msk_time.addSecs(header.begin - ka->brtk_time));
    m_editroform_ui.dateTimeEditEnd->setDateTime(ka->msk_time.addSecs(header.end - ka->brtk_time));
    return true;
};

bool Editor::getHeader(BRTK::Task::Header &header, ka::KAInfo *ka)
{
    header.id.band_code = m_editroform_ui.comboBoxBand->currentText().toInt();
    header.id.variant = m_editroform_ui.spinBoxVersion->value();
    header.id.subsystem = 0;
    header.begin = (ka->msk_time.secsTo(m_editroform_ui.dateTimeEditBegin->dateTime())) + ka->brtk_time;
    header.end = (ka->msk_time.secsTo(m_editroform_ui.dateTimeEditEnd->dateTime())) + ka->brtk_time;
    return true;
};
