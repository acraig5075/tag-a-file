#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "editpage.h"
#include "searchpage.h"


MainWindow::MainWindow(DataAccess &dal, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_dal(dal)
{
    ui->setupUi(this);

    m_editPage = new EditPage(m_dal, this);
    m_searchPage = new SearchPage(m_dal, this);

    ui->page1Layout->addWidget(m_editPage);
    ui->page2Layout->addWidget(m_searchPage);
}

MainWindow::~MainWindow()
{
    delete ui;
}
