#include "searchpage.h"
#include "dataaccess.h"
#include "ui_searchpage.h"
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QClipboard>


SearchPage::SearchPage(DataAccess &dal, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchPage),
    m_dal(dal)
{
    ui->setupUi(this);
    ui->tagEdit->setBuddyList(ui->tagList);
    ui->tagEdit->setTagCompleter(m_dal.BrowseTags());
    ui->resultView->horizontalHeader()->setStretchLastSection(true);
    ui->resultView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->resultView->setContextMenuPolicy(Qt::ActionsContextMenu);

    m_model = new QSqlQueryModel(this);
    updateResultView();

    QAction *clipboardAction = new QAction("Copy to clipboard", this);
    ui->resultView->addAction(clipboardAction);

    QObject::connect(ui->tagList, SIGNAL(tagListDeletion()), this, SLOT(updateResultView()));
    QObject::connect(ui->tagList, SIGNAL(tagListAddition()), this, SLOT(updateResultView()));
    QObject::connect(clipboardAction, SIGNAL(triggered(bool)), this, SLOT(copyToClipboard()));
}

SearchPage::~SearchPage()
{
    delete ui;
}

void SearchPage::setActive()
{
    m_model->clear();
    ui->tagEdit->clear();
    ui->tagList->clear();
    ui->tagEdit->setTagCompleter(m_dal.BrowseTags());
    ui->resultView->setModel(m_model);
}

void SearchPage::updateResultView()
{
    QStringList tags = ui->tagList->toStringList();

    m_dal.SetupSearchModel(*m_model, tags);

    ui->resultView->setModel(m_model);
}

void SearchPage::copyToClipboard()
{
    QString filename;

    QItemSelectionModel *selection = ui->resultView->selectionModel();
    if (selection && selection->hasSelection())
    {
        QModelIndexList indices = selection->selectedRows();
        if (indices.size() > 0)
        {
            QSqlRecord record = m_model->record(indices[0].row());
            QVariant data = record.value(0);
            filename = data.toString();
        }
    }

    QApplication::clipboard()->setText(filename);
}

void SearchPage::searchTag(const QString &tag)
{
    ui->tagList->addTagItem(tag);

    updateResultView();
}
