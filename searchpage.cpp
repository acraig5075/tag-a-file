#include "searchpage.h"
#include "dataaccess.h"
#include "ui_searchpage.h"
#include <QDebug>
#include <QStringListModel>
#include <QClipboard>


SearchPage::SearchPage(DataAccess &dal, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchPage),
    m_dal(dal)
{
    ui->setupUi(this);

    ui->tagEdit->setBuddyList(ui->tagList);

    m_model = new QStringListModel(this);

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

void SearchPage::updateResultView()
{
    QStringList tags = ui->tagList->toStringList();
    QStringList results = m_dal.QueryTags(tags);

    m_model->setStringList(results);
    ui->resultView->setModel(m_model);
}

void SearchPage::copyToClipboard()
{
    QString filename;

    QItemSelectionModel *selection = ui->resultView->selectionModel();
    if (selection && selection->hasSelection())
    {
        QModelIndexList indices = selection->selectedIndexes();
        if (indices.size() > 0)
        {
            QVariant data = m_model->data(indices[0], Qt::DisplayRole);
            filename = data.toString();
        }
    }

    if (!filename.isEmpty())
        QApplication::clipboard()->setText(filename);
}
