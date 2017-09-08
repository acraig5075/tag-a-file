#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "editpage.h"
#include "searchpage.h"
#include "browsepage.h"
#include "dataaccess.h"
#include <QSettings>

#define VERSION "1.0"

MainWindow::MainWindow(DataAccess &dal, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_dal(dal)
{
    ui->setupUi(this);

    setWindowTitle(QString("Tag a File %1").arg(VERSION));

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
    switch (index)
    {
    case 1: // searchPage
        m_searchPage->setActive();
        break;
    case 2: // browse page
        m_browsePage->setActive();
        break;
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


void MainWindow::writePositionSettings()
{
    QSettings settings( "Alasdair Craig", "Tag a File" );

    settings.beginGroup( "MainWindow" );
    settings.setValue( "Geometry", saveGeometry() );
    settings.setValue( "Maximised", isMaximized() );

    if ( !isMaximized() )
    {
        settings.setValue( "Pos", pos() );
        settings.setValue( "Size", size() );
    }

    settings.endGroup();
}

void MainWindow::readPositionSettings()
{
    QSettings settings( "Alasdair Craig", "Tag a File" );

    settings.beginGroup( "MainWindow" );
    restoreGeometry(settings.value( "Geometry", saveGeometry() ).toByteArray());
    move(settings.value( "Pos", pos() ).toPoint());
    resize(settings.value( "Size", size() ).toSize());

    if ( settings.value( "Maximised", isMaximized() ).toBool() )
        showMaximized();

    settings.endGroup();
}

void MainWindow::closeEvent( QCloseEvent* )
{
    writePositionSettings();
}
