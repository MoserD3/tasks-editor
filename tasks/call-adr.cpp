#include "call-adr.h"
#include "../val3.h"
//brtk
#include "brtk/task.h"

class CallAdrItem : public QListWidgetItem
{
public:
    CallAdrItem(QListWidget* lw, VAL3 adr)
        : QListWidgetItem(QString("%1").arg(adr.get_val()), lw)
        , m_adr(adr)
    { };

    const VAL3& get_adr() const { return m_adr; };

private:
    VAL3 m_adr;
};

CALL_ADR::CALL_ADR(QWidget *parent, Qt::WFlags flags)
    : Editor(parent, flags)
{
    frame = new QWidget(this);
    m_call_adr_form_ui.setupUi(frame);
    m_editroform_ui.gridLayout->addWidget(frame, 1, 0, 1, 9);

    m_call_adr_form_ui.listWidget->clear();
    m_call_adr_form_ui.spinBoxAdr->setValue(1);
    connect(m_call_adr_form_ui.pushButtonAdd, SIGNAL(clicked()), this, SLOT(pushButtonAdd_clicked()));
    connect(m_call_adr_form_ui.pushButtonDelete, SIGNAL(clicked()), this, SLOT(pushButtonDelete_clicked()));
    setMinimumHeight(168);
    setMaximumHeight(168);
};

bool CALL_ADR::setData(QIODevice *blob, ka::KAInfo *ka)
{
    BRTK::Task::Header header;
    blob->read(reinterpret_cast<char*>(&header), sizeof(header));

    setHeader(header, ka);

    uchar count = 0;
    blob->read(reinterpret_cast<char*>(&count), sizeof(count));

    VAL3 adr = 0;
    while (count--) {
        blob->read(reinterpret_cast<char*>(&adr), sizeof(adr));
        m_call_adr_form_ui.listWidget->addItem(new CallAdrItem(m_call_adr_form_ui.listWidget, adr));
    };
    return true;
};

bool CALL_ADR::getData(QIODevice *blob, ka::KAInfo *ka)
{
    uchar count = m_call_adr_form_ui.listWidget->count();
    BRTK::Task::Header header;
    header.size = sizeof(header) + 1 + (count * 3);
    header.id.type = BRTK::Task::CallAddr;

    getHeader(header, ka);

    blob->write(reinterpret_cast<char*>(&header), sizeof(header));
    blob->write(reinterpret_cast<char*>(&count), sizeof(count));

    VAL3 adr = 0;
    CallAdrItem *item = NULL;
    int i = 0;
    while (i < count)	{
        item = reinterpret_cast<CallAdrItem*>(m_call_adr_form_ui.listWidget->item(i++));
        adr = item->get_adr();
        blob->write(reinterpret_cast<char*>(&adr), sizeof(adr));
    };
    return true;
};

void CALL_ADR::pushButtonAdd_clicked()
{
    VAL3 adr = m_call_adr_form_ui.spinBoxAdr->value();
    m_call_adr_form_ui.listWidget->addItem(new CallAdrItem(m_call_adr_form_ui.listWidget, adr));
};

void CALL_ADR::pushButtonDelete_clicked()
{
    QListWidgetItem *item = NULL;
    item = m_call_adr_form_ui.listWidget->currentItem();
    if (item) delete item;
};
