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
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setContextMenuPolicy(Qt::ActionsContextMenu);

    m_filesModel = new QSqlQueryModel(this);
    m_tagsModel = new QSqlQueryModel(this);

    m_dal.SetupFilesModel(*m_filesModel);
    m_dal.SetupTagsModel(*m_tagsModel);

    on_filesButton_clicked();

    QAction *actionSearch = new QAction("Search", this);
    QAction *actionEdit = new QAction("Edit", this);
    QAction *actionDelete = new QAction("Delete", this);

    ui->tableView->addAction(actionSearch);
    ui->tableView->addAction(actionEdit);
    ui->tableView->addAction(actionDelete);

    QObject::connect(actionSearch, SIGNAL(triggered(bool)), this, SLOT(onSearchMenu()));
    QObject::connect(actionEdit, SIGNAL(triggered(bool)), this, SLOT(onEditMenu()));
    QObject::connect(actionDelete, SIGNAL(triggered(bool)), this, SLOT(onDeleteMenu()));
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
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setColumnHidden(0, true);
}

void BrowsePage::on_tagsButton_clicked()
{
    ui->tagsButton->setChecked(true);
    ui->label->setText("All tags:");
    ui->tableView->setModel(m_tagsModel);
    ui->tableView->horizontalHeader()->setStretchLastSection(false);
    ui->tableView->setColumnHidden(0, true);
}

void BrowsePage::onSearchMenu()
{}

void BrowsePage::onEditMenu()
{}

void BrowsePage::onDeleteMenu()
{}
