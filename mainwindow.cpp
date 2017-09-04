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

    setWindowTitle("Tag Anything");

    m_editPage = new EditPage(m_dal, this);
    m_searchPage = new SearchPage(m_dal, this);

    ui->page1Layout->addWidget(m_editPage);
    ui->page2Layout->addWidget(m_searchPage);

    //m_editPage->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 2, stop: 0 #C09F80, stop: 1 #FFFFFF); ");
}

MainWindow::~MainWindow()
{
    delete ui;
}
