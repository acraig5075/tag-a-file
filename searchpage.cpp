#include "searchpage.h"
#include "dataaccess.h"
#include "ui_searchpage.h"
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QClipboard>
#include <QAction>


SearchPage::SearchPage(DataAccess &dal, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchPage),
    m_dal(dal)
{
    ui->setupUi(this);

    m_tagsModel = new QSqlQueryModel(this);
    m_dal.RefreshTagsModel(*m_tagsModel);

    ui->tagEdit->setBuddyList(ui->tagList);
    ui->tagEdit->setTagCompleter(*m_tagsModel);
    ui->resultView->horizontalHeader()->setStretchLastSection(true);
    ui->resultView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->resultView->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->tagEdit->setPlaceholderText("Enter to accept");

    m_resultsModel = new QSqlQueryModel(this);
    updateResultView();

    QAction *clipboardAction = new QAction("Copy to clipboard", this);
    QAction *searchAction = new QAction("Edit / update", this);
    ui->resultView->addAction(clipboardAction);
    ui->resultView->addAction(searchAction);

    QObject::connect(ui->tagList, SIGNAL(tagListDeletion()), this, SLOT(updateResultView()));
    QObject::connect(ui->tagList, SIGNAL(tagListAddition()), this, SLOT(updateResultView()));
    QObject::connect(clipboardAction, SIGNAL(triggered(bool)), this, SLOT(onClipboardMenu()));
    QObject::connect(searchAction, SIGNAL(triggered(bool)), this, SLOT(onSearchMenu()));
}

SearchPage::~SearchPage()
{
    delete ui;
}

void SearchPage::setActive()
{
    m_dal.RefreshTagsModel(*m_tagsModel);
    m_resultsModel->clear();
    ui->tagEdit->clear();
    ui->tagList->clear();
    ui->tagEdit->setTagCompleter(*m_tagsModel);
    ui->resultView->setModel(m_resultsModel);
    ui->resultsLabel->setText("Results:");
}

QString resultsDescription(const QStringList &tags)
{
    QString description;

    if (tags.isEmpty())
    {
        description = "Results:";
    }
    else
    {
        description = "Results matching ";

        for (int i = 0; i < tags.size(); ++i)
        {
            if (i == 0)
                description += tags[0];
            else
                description += QString(" AND %1").arg(tags[i]);
        }

        description += ":";
    }

    return description;
}

void SearchPage::updateResultView()
{
    QStringList tags = ui->tagList->toStringList();

    ui->resultsLabel->setText(resultsDescription(tags));

    m_dal.RefreshSearchModel(*m_resultsModel, tags);

    ui->resultView->setModel(m_resultsModel);
}

QString SearchPage::getSelectedFilename()
{
    QItemSelectionModel *selection = ui->resultView->selectionModel();
    if (selection && selection->hasSelection())
    {
        QModelIndexList indices = selection->selectedRows();
        if (indices.size() > 0)
        {
            QSqlRecord record = m_resultsModel->record(indices[0].row());
            QVariant data = record.value(0);
            return data.toString();
        }
    }

    return "";
}

void SearchPage::onClipboardMenu()
{
    QString filename = getSelectedFilename();

    QApplication::clipboard()->setText(filename);
}

void SearchPage::onSearchMenu()
{
    QString filename = getSelectedFilename();

    int itemID = m_dal.GetItemID(filename);

    emit searchFile(itemID);
}

void SearchPage::searchTag(const QString &tag)
{
    ui->tagList->addTagItem(tag);

    updateResultView();
}
