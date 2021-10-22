#include "freq-pk.h"
//brtk
#include "brtk/task.h"

class FreqPKItem : public QTreeWidgetItem
{
public:
#pragma pack(push, 1)
    struct Info
    {
        ushort fpk1;
        uchar fpk1max;
        ushort fpk2;
        uchar fpk2max;
        ushort fpk3;
        uchar fpk3max;
    };
#pragma pack(pop)

    FreqPKItem(QTreeWidget *tw)
        : QTreeWidgetItem(tw)
    { };

    const Info &get_info() { return m_info; };
    void set_info(const Info &info) { m_info = info; };

private:
    Info m_info;
};

FREQ_PK::FREQ_PK(QWidget *parent, Qt::WFlags flags)
    : Editor(parent, flags)
    , m_item(NULL)
{
    frame = new QWidget(this);
    m_freq_pk_form_ui.setupUi(frame);
    m_editroform_ui.gridLayout->addWidget(frame, 1, 0, 1, 9);

    initTreeWidget();

    connect(m_freq_pk_form_ui.pushButtonEdit, SIGNAL(clicked()), this, SLOT(pushButtonEdit_clicked()));
    connect(m_freq_pk_form_ui.treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(treeWidget_clicked(QTreeWidgetItem*)));

    setMinimumHeight(219);
    setMaximumHeight(219);
};

bool FREQ_PK::setData(QIODevice *blob, ka::KAInfo *ka)
{
    BRTK::Task::Header header;
    blob->read(reinterpret_cast<char*>(&header), sizeof(header));

    setHeader(header, ka);

    FreqPKItem::Info info[13];
    blob->read(reinterpret_cast<char*>(info), sizeof(info));
    int i = 0;
    while (i < 13) {
        FreqPKItem *item = reinterpret_cast<FreqPKItem*>(m_freq_pk_form_ui.treeWidget->topLevelItem(i));
        item->set_info(info[i]);
        item->setText(1, QString::number(info[i].fpk1));
        item->setText(2, m_freq_pk_form_ui.comboBoxFtpkmax1->itemText(indx(info[i].fpk1max)));
        item->setText(3, QString::number(info[i].fpk2));
        item->setText(4, m_freq_pk_form_ui.comboBoxFtpkmax2->itemText(indx(info[i].fpk2max)));
        item->setText(5, QString::number(info[i].fpk3));
        item->setText(6, m_freq_pk_form_ui.comboBoxFtpkmax3->itemText(indx(info[i].fpk3max)));
        m_freq_pk_form_ui.treeWidget->resizeColumnToContents(i);
        i++;
    };
    return true;
};

bool FREQ_PK::getData(QIODevice *blob, ka::KAInfo *ka)
{
    BRTK::Task::Header header;
    header.size = sizeof(header) + FreqPKSize;
    header.id.type = BRTK::Task::FreqPK;

    getHeader(header, ka);

    blob->write(reinterpret_cast<char*>(&header), sizeof(header));

    FreqPKItem::Info info;
    int i = 0;
    while (i < 13) {
        FreqPKItem *item = reinterpret_cast<FreqPKItem*>(m_freq_pk_form_ui.treeWidget->topLevelItem(i));
        info = item->get_info();
        blob->write(reinterpret_cast<char*>(&info), sizeof(info));
        i++;
    };
    return true;
};

void FREQ_PK::initTreeWidget()
{
    m_freq_pk_form_ui.spinBoxFpk1->setValue(1);
    m_freq_pk_form_ui.comboBoxFtpkmax1->setCurrentIndex(0);
    m_freq_pk_form_ui.spinBoxFpk2->setValue(1);
    m_freq_pk_form_ui.comboBoxFtpkmax2->setCurrentIndex(0);
    m_freq_pk_form_ui.spinBoxFpk3->setValue(1);
    m_freq_pk_form_ui.comboBoxFtpkmax3->setCurrentIndex(0);

    m_freq_pk_form_ui.treeWidget->clear();
    m_freq_pk_form_ui.treeWidget->setHeaderLabels(
        QStringList() << tr("N") << tr("Fpk1") << tr("ftpk1 max") << tr("Fpk2") << tr("ftpk2 max") << tr("Fpk3") << tr("ftpk3 max"));
    int i = 1;
    FreqPKItem *item = NULL;
    while (i <= 13) {
        FreqPKItem::Info info;
        info.fpk1 = m_freq_pk_form_ui.spinBoxFpk1->value();
        info.fpk1max = num(m_freq_pk_form_ui.comboBoxFtpkmax1->currentIndex());
        info.fpk2 = m_freq_pk_form_ui.spinBoxFpk2->value();
        info.fpk2max = num(m_freq_pk_form_ui.comboBoxFtpkmax2->currentIndex());
        info.fpk3 = m_freq_pk_form_ui.spinBoxFpk3->value();
        info.fpk3max = num(m_freq_pk_form_ui.comboBoxFtpkmax3->currentIndex());

        item = new FreqPKItem(m_freq_pk_form_ui.treeWidget);
        item->set_info(info);

        item->setText(0, QString::number(i++));
        item->setText(1, QString::number(info.fpk1));
        item->setText(2, m_freq_pk_form_ui.comboBoxFtpkmax1->currentText());
        item->setText(3, QString::number(info.fpk2));
        item->setText(4, m_freq_pk_form_ui.comboBoxFtpkmax2->currentText());
        item->setText(5, QString::number(info.fpk3));
        item->setText(6, m_freq_pk_form_ui.comboBoxFtpkmax3->currentText());
        m_freq_pk_form_ui.treeWidget->addTopLevelItem(item);
        m_freq_pk_form_ui.treeWidget->resizeColumnToContents(i);
    };
};

ushort FREQ_PK::num(int i)
{
    if (i == 0) return 1;
    else
        if (i == 1) return 2;
        else
            if (i == 2) return 3;
            else
                if (i == 3) return 5;
                else
                    return 0;
};

int FREQ_PK::indx(ushort n)
{
    if (n == 1) return 0;
    else
        if (n == 2) return 1;
        else
            if (n == 3) return 2;
            else
                if (n == 5) return 3;
                else
                    return -1;
};

void FREQ_PK::pushButtonEdit_clicked()
{
    if (!m_item) {
        //item no select
        return;
    };
    FreqPKItem::Info info;
    info.fpk1 = m_freq_pk_form_ui.spinBoxFpk1->value();
    info.fpk1max = num(m_freq_pk_form_ui.comboBoxFtpkmax1->currentIndex());
    info.fpk2 = m_freq_pk_form_ui.spinBoxFpk2->value();
    info.fpk2max = num(m_freq_pk_form_ui.comboBoxFtpkmax2->currentIndex());
    info.fpk3 = m_freq_pk_form_ui.spinBoxFpk3->value();
    info.fpk3max = num(m_freq_pk_form_ui.comboBoxFtpkmax3->currentIndex());

    m_item->set_info(info);

    m_item->setText(1, QString::number(info.fpk1));
    m_item->setText(2, m_freq_pk_form_ui.comboBoxFtpkmax1->currentText());
    m_item->setText(3, QString::number(info.fpk2));
    m_item->setText(4, m_freq_pk_form_ui.comboBoxFtpkmax2->currentText());
    m_item->setText(5, QString::number(info.fpk3));
    m_item->setText(6, m_freq_pk_form_ui.comboBoxFtpkmax3->currentText());
};

void FREQ_PK::treeWidget_clicked(QTreeWidgetItem *item)
{
    m_item = reinterpret_cast<FreqPKItem*>(item);
    FreqPKItem::Info info = m_item->get_info();
    m_freq_pk_form_ui.spinBoxFpk1->setValue(info.fpk1);
    m_freq_pk_form_ui.comboBoxFtpkmax1->setCurrentIndex(indx(info.fpk1max));
    m_freq_pk_form_ui.spinBoxFpk2->setValue(info.fpk2);
    m_freq_pk_form_ui.comboBoxFtpkmax2->setCurrentIndex(indx(info.fpk2max));
    m_freq_pk_form_ui.spinBoxFpk3->setValue(info.fpk3);
    m_freq_pk_form_ui.comboBoxFtpkmax3->setCurrentIndex(indx(info.fpk3max));
};
