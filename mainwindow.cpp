#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "editpage.h"
#include "searchpage.h"
#include "browsepage.h"
#include "dataaccess.h"


MainWindow::MainWindow(DataAccess &dal, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_dal(dal)
{
    ui->setupUi(this);

    setWindowTitle("Tag a File");

    m_editPage = new EditPage(m_dal, this);
    m_searchPage = new SearchPage(m_dal, this);
    m_browsePage = new BrowsePage(m_dal, this);

    ui->page1Layout->addWidget(m_editPage);
    ui->page2Layout->addWidget(m_searchPage);
    ui->page3Layout->addWidget(m_browsePage);

    ui->tabWidget->setCurrentIndex(0);

    QObject::connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));
    QObject::connect(m_browsePage, SIGNAL(searchFile(int)), this, SLOT(onSearchFile(int)));
    QObject::connect(m_browsePage, SIGNAL(searchTag(int)), this, SLOT(onSearchTag(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::tabChanged(int index)
{
    if (index == 1) // searchPage
    {
        m_searchPage->setActive();
    }
}

void MainWindow::onSearchFile(int id)
{
    QString filename = m_dal.GetItemContent(id);

    ui->tabWidget->setCurrentIndex(0);

    m_editPage->editContent(filename);
}

void MainWindow::onSearchTag(int id)
{
    QString tag = m_dal.GetTagTitle(id);

    ui->tabWidget->setCurrentIndex(1);

    m_searchPage->searchTag(tag);
}
