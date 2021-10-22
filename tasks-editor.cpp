#include "tasks-editor.h"
#include "settings.h"
#include "factory.h"
#include "tasks-model.h"
#include "ka-model.h"
#include "db.h"
//brtk
#include "brtk/array.h"
//trnames
#include "trnames/tasktype.h"
//qt
#include <QtCore/QFile>

TasksEditor::TasksEditor(DBIface *db, SettingsForm *settings, QWidget *parent, Qt::WFlags flags)
    : QWidget(parent, flags)
    , m_db(db)
    , m_task_model(NULL)
    , m_ka_model(NULL)
    , m_editor(NULL)
    , m_settings(settings)
    , m_selected(false)
{
    ui.setupUi(this);

    m_task_model = new TasksModel(m_db);
    m_ka_model = new ka::KAModel(m_db);

    //m_ka_model->resetModel();

    ui.comboBoxType->setModel(trnames::TaskType::instance());
    ui.comboBoxFilterNKA->setModel(m_ka_model);
    ui.comboBoxNKA->setModel(m_ka_model);
    ui.treeView->setModel(m_task_model);

    ui.treeView->setColumnWidth(0, 70);
    ui.treeView->setColumnWidth(1, 250);
    ui.treeView->setColumnWidth(2, 100);
    ui.treeView->setColumnWidth(3, 130);
    ui.treeView->setColumnWidth(4, 130);

    pushButtonRefresh_clicked();
};

TasksEditor::~TasksEditor()
{ };

void TasksEditor::groupBoxFilter_clicked()
{
    if (ui.groupBoxFilter->isChecked()) {
        ui.comboBoxFilterNKA->setCurrentIndex(-1);
        QDateTime now = QDateTime::currentDateTime();
        ui.dateTimeEditFilterFrom->setDateTime(now.addDays(-7));
        ui.dateTimeEditFilterTo->setDateTime(now);
    };
};

void TasksEditor::pushButtonNew_clicked()
{
    ui.treeView->clearSelection();
    clearAll();
    unlockKey();
    m_selected = false;
};

void TasksEditor::pushButtonDelete_clicked()
{
    if (!m_selected) return;
    QModelIndex ind = ui.treeView->currentIndex();
    m_task_model->removeRows(ind.row(), 1, ind);

    pushButtonRefresh_clicked();
};

void TasksEditor::pushButtonRefresh_clicked()
{
    m_selected = false;
    if (ui.groupBoxFilter->isChecked()) {
        DBIface::Filter f;
        int i = ui.comboBoxFilterNKA->currentIndex();
        f.nka = 0;
        if (i >= 0)
            f.nka = m_ka_model->key(i).ms;
        f.dt_from = ui.dateTimeEditFilterFrom->dateTime();
        f.dt_to = ui.dateTimeEditFilterTo->dateTime();
        m_db->set_filter(true, f);
    }
    else
        m_db->set_filter(false);

    m_task_model->resetModel();
    clearAll();
    lockKey();
};

void TasksEditor::pushButtonSettings_clicked()
{
    m_settings->show();
};

namespace {
    class TaskSaver : public DBIface::Source
    {
    public:
        explicit TaskSaver(Editor *editor, ka::KAInfo *ka, const QString &name)
            : m_editor(editor)
            , m_ka(ka)
            , m_name(name)
        { };

        virtual void record(dbcomm::SrvArrRecord &rec)
        {
            rec.pz_cancel;
            rec.dt_change = QDateTime::currentDateTime();
            rec.name = m_name;
        };
        virtual void body(QIODevice *blob)
        {
            m_editor->getData(blob, m_ka);
        };

    private:
        Editor *const m_editor;
        ka::KAInfo *m_ka;
        QString m_name;
    };
};//namespace

void TasksEditor::pushButtonAccept_clicked()
{
    if (!m_editor) return;

    dbcomm::SrvArrKey key;
    key.tp = BRTK::ArrayPK::Task;

    ka::KAInfo ka_info = m_ka_model->key(ui.comboBoxNKA->currentIndex());

    if (m_selected) {
        QModelIndex ind = ui.treeView->currentIndex();
        key.ka = ind.sibling(ind.row(), TasksModel::KAColumn).data(Qt::EditRole).toInt();
        key.subtp = ind.sibling(ind.row(), TasksModel::TypeColumn).data(Qt::EditRole).toInt();
        key.dt = ind.sibling(ind.row(), TasksModel::DTCreateColumn).data(Qt::EditRole).toDateTime();
    }
    else {
        key.ka = ka_info.ms;
        key.subtp = trnames::TaskType::instance()->getIDByIndex(ui.comboBoxType->currentIndex());
        key.dt = QDateTime::currentDateTime();
    };

    m_db->put(key, &TaskSaver(m_editor, &ka_info, ui.lineEditName->text()));

    pushButtonRefresh_clicked();
};

void TasksEditor::pushButtonCancel_clicked()
{
    ui.treeView->clearSelection();
    pushButtonRefresh_clicked();
};

void TasksEditor::comboBoxType_itemChanged(int i)
{
    int pz_tp = ui.comboBoxType->itemData(i).toInt();
    if (m_editor) {
        delete m_editor;
        m_editor = NULL;
    };
    m_editor = FactoryContainer::instance().create(pz_tp, this);
    ui.gridLayoutMain->addWidget(m_editor, 4, 0, 1, 1);
};

namespace {
    class DataLoader : public DB::Sink
    {
    public:
        explicit DataLoader(Editor *editor, ka::KAInfo *ka)
            : m_editor(editor)
            , m_ka(ka)
        { };

        virtual void body(QIODevice *blob)
        {
            blob->open(QIODevice::ReadOnly);
            m_editor->setData(blob, m_ka);
        };

    private:
        Editor *m_editor;
        ka::KAInfo *m_ka;
    };
};//namespace

void TasksEditor::treeView_clicked(QModelIndex ind)
{
    m_selected = true;

    lockKey();
    if (!ind.isValid()) return;

    QString name = ind.sibling(ind.row(), TasksModel::NameColumn).data(Qt::EditRole).toString();
    ui.lineEditName->setText(name);

    int i = -1;
    int pz_tp = ind.sibling(ind.row(), TasksModel::TypeColumn).data(Qt::EditRole).toInt();
    i = ui.comboBoxType->findData(pz_tp, Qt::EditRole);
    ui.comboBoxType->setCurrentIndex(i);

    if (m_editor) {
        delete m_editor;
        m_editor = NULL;
    };
    m_editor = FactoryContainer::instance().create(pz_tp, this);
    ui.gridLayoutMain->addWidget(m_editor, 4, 0, 1, 1);

    int ka = ind.sibling(ind.row(), TasksModel::KAColumn).data(Qt::EditRole).toInt();
    i = ui.comboBoxNKA->findData(ka, Qt::EditRole);
    ui.comboBoxNKA->setCurrentIndex(i);

    ka::KAInfo ka_info = m_ka_model->key(i);

    m_db->get_sink(m_task_model->key(ind.row()), &DataLoader(m_editor, &ka_info));
};

void TasksEditor::clearAll()
{
    if (m_editor) {
        delete m_editor;
        m_editor = NULL;
    };
    ui.comboBoxType->setCurrentIndex(-1);
    ui.comboBoxNKA->setCurrentIndex(0);
    ui.lineEditName->clear();
};

void TasksEditor::lockKey()
{
    ui.comboBoxType->setEnabled(false);
    ui.comboBoxNKA->setEnabled(false);
    ui.lineEditName->setEnabled(false);
};

void TasksEditor::unlockKey()
{
    ui.comboBoxType->setEnabled(true);
    ui.comboBoxNKA->setEnabled(true);
    ui.lineEditName->setEnabled(true);
};
