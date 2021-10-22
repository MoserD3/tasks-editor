#include "regions.h"
//brtk
#include "brtk/task.h"

class RegionsItem : public QListWidgetItem
{
public:
    RegionsItem(QListWidget* lw, int spec, int geo)
        : QListWidgetItem(lw)
        , m_spec(spec)
        , m_geo(geo)
    {
        setText(QString("%1=%2, %3=%4")
            .arg(QApplication::translate("RegionsItem", "Special", 0, QApplication::UnicodeUTF8))
            .arg(spec)
            .arg(QApplication::translate("RegionsItem", "Geographical", 0, QApplication::UnicodeUTF8))
            .arg(geo));
    };

    const uchar& get_spec() const { return m_spec; };
    const uchar& get_geo() const { return m_geo; };

private:
    uchar m_spec;
    uchar m_geo;
};

REGIONS::REGIONS(QWidget *parent, Qt::WFlags flags)
    : Editor(parent, flags)
{
    frame = new QWidget(this);
    m_regions_form_ui.setupUi(frame);
    m_editroform_ui.gridLayout->addWidget(frame, 1, 0, 1, 9);

    m_regions_form_ui.listWidget->clear();
    m_regions_form_ui.spinBoxSpec->setValue(1);
    m_regions_form_ui.spinBoxGeo->setValue(1);

    connect(m_regions_form_ui.pushButtonAdd
        , SIGNAL(clicked())
        , SLOT(pushButtonAdd_clicked()));
    connect(m_regions_form_ui.pushButtonDelete
        , SIGNAL(clicked())
        , SLOT(pushButtonDelete_clicked()));

    setMinimumHeight(168);
    setMaximumHeight(168);
};

bool REGIONS::setData(QIODevice *blob, ka::KAInfo *ka)
{
    BRTK::Task::Header header;
    blob->read(reinterpret_cast<char*>(&header), sizeof(header));

    setHeader(header, ka);

    uchar count = 0;
    blob->read(reinterpret_cast<char*>(&count), sizeof(count));

    uchar spec = 0;
    uchar geo = 0;
    while (count--) {
        blob->read(reinterpret_cast<char*>(&spec), sizeof(spec));
        blob->read(reinterpret_cast<char*>(&geo), sizeof(geo));
        m_regions_form_ui.listWidget->addItem(new RegionsItem(m_regions_form_ui.listWidget, spec, geo));
    };
    return true;
};

bool REGIONS::getData(QIODevice *blob, ka::KAInfo *ka)
{
    uchar count = m_regions_form_ui.listWidget->count();
    BRTK::Task::Header header;
    header.size = sizeof(header) + 1 + (count * 2);
    header.id.type = BRTK::Task::Regions;

    getHeader(header, ka);

    blob->write(reinterpret_cast<char*>(&header), sizeof(header));
    blob->write(reinterpret_cast<char*>(&count), sizeof(count));

    uchar spec = 0;
    uchar geo = 0;
    RegionsItem *item = NULL;
    int i = 0;
    while (i < count)	{
        item = reinterpret_cast<RegionsItem*>(m_regions_form_ui.listWidget->item(i++));
        spec = item->get_spec();
        geo = item->get_geo();
        blob->write(reinterpret_cast<char*>(&spec), sizeof(spec));
        blob->write(reinterpret_cast<char*>(&geo), sizeof(geo));
    };
    return true;
};

void REGIONS::pushButtonAdd_clicked()
{
    uchar spec = m_regions_form_ui.spinBoxSpec->value();
    uchar geo = m_regions_form_ui.spinBoxGeo->value();
    m_regions_form_ui.listWidget->addItem(new RegionsItem(m_regions_form_ui.listWidget, spec, geo));
};

void REGIONS::pushButtonDelete_clicked()
{
    QListWidgetItem *item = NULL;
    item = m_regions_form_ui.listWidget->currentItem();
    if (item) delete item;
};
