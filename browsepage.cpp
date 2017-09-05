#include "browsepage.h"
#include "ui_browsepage.h"
#include "dataaccess.h"
#include <QSqlQueryModel>


BrowsePage::BrowsePage(DataAccess &dal, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BrowsePage),
    m_dal(dal)
{
    ui->setupUi(this);

    ui->filesButton->setCheckable(true);
    ui->tagsButton->setCheckable(true);

    m_filesModel = new QSqlQueryModel(this);
    m_tagsModel = new QSqlQueryModel(this);

    m_dal.SetupFilesModel(*m_filesModel);
    m_dal.SetupTagsModel(*m_tagsModel);

    on_filesButton_clicked();
}

BrowsePage::~BrowsePage()
{
    delete ui;
}

void BrowsePage::on_filesButton_clicked()
{
    ui->filesButton->setChecked(true);
    ui->label->setText("All files:");
    ui->tableView->setModel(m_filesModel);
    ui->tableView->show();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
}

void BrowsePage::on_tagsButton_clicked()
{
    ui->tagsButton->setChecked(true);
    ui->label->setText("All tags:");
    ui->tableView->setModel(m_tagsModel);
    ui->tableView->show();
    ui->tableView->horizontalHeader()->setStretchLastSection(false);
}
