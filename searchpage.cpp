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

    m_model = new QStringListModel(this);

    QObject::connect(ui->tagList, SIGNAL(tagSelectionChanged()), this, SLOT(updateResultView()));
}

SearchPage::~SearchPage()
{
    delete ui;
}

void SearchPage::on_tagEdit_returnPressed()
{
    QString value = ui->tagEdit->text();

    while (value.endsWith('-'))
        value.chop(1);
    while (value.contains("--"))
        value.replace("--", "-");

    if (!value.isEmpty())
    {
        auto matches = ui->tagList->findItems(value, Qt::MatchExactly);
        if (matches.isEmpty())
        {
            ui->tagList->addItem(value);
            ui->tagEdit->clear();
            ui->tagEdit->setFocus();

            updateResultView();
        }
    }
}

void SearchPage::updateResultView()
{
    QStringList tags = ui->tagList->toStringList();
    QStringList results = m_dal.QueryTags(tags);

    m_model->setStringList(results);
    ui->resultView->setModel(m_model);
}
