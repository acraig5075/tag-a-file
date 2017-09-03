#include "searchpage.h"
#include "dataaccess.h"
#include "ui_searchpage.h"
#include <QDebug>
#include <QStringListModel>

SearchPage::SearchPage(DataAccess &dal, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchPage),
    m_dal(dal)
{
    ui->setupUi(this);

    ui->tagEdit->setBuddyList(ui->tagList);

    m_model = new QStringListModel(this);

    QObject::connect(ui->tagList, SIGNAL(tagListDeletion()), this, SLOT(updateResultView()));
    QObject::connect(ui->tagList, SIGNAL(tagListAddition()), this, SLOT(updateResultView()));
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
