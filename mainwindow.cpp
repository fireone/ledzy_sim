#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QToolButton>
#include <QStyle>
#include <QColorDialog>
#include <QInputDialog>

#include "sky_effect.h"
#include "runner.h"
#include "diagonal_on.h"
#include "diagonal_on_2.h"
#include "race_cars.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow( parent ),
    ui( new Ui::MainWindow ),
    m_playState( PAUSE ),
    m_pTimer( 0 ),
    m_timerInterval( 10 ),
    m_pEffect( 0 ),
    m_effects()
{
    ui->setupUi( this );

    this->setFixedWidth( 950 );
    this->setFixedHeight( 1050 );

    this->setWindowTitle( "Ledzy SIM" );

    makeConnections();

    addMenuItems();

    initLeds();

    m_pEffect = new runner( m_leds );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED( event )

    QPainter painter( this );

    //horisontal odd ones
    for( int j = 0; j < 3; ++j)
    for( int k = 0; k < 90; ++k )
    {
        int i = j * 2 * 90 + k;

        painter.setPen( QPen( QColor( m_leds[ i ].r,
                                      m_leds[ i ].g,
                                      m_leds[ i ].b ) ) );

        painter.setBrush( QBrush( QColor( m_leds[ i ].r,
                                          m_leds[ i ].g,
                                          m_leds[ i ].b ) ) );

        painter.drawEllipse( 25 + k * 10,
                             25 + 15 + j * 360,
                             5,
                             5 );
    }

    //horisontal even ones
    for( int j = 0; j < 3; ++j )
    for( int k = 0; k < 90; ++k )
    {
        int i = 90 + j * 2 * 90 + k;

        painter.setPen( QPen( QColor( m_leds[ i ].r,
                                      m_leds[ i ].g,
                                      m_leds[ i ].b ) ) );

        painter.setBrush( QBrush( QColor( m_leds[ i ].r,
                                          m_leds[ i ].g,
                                          m_leds[ i ].b ) ) );

        painter.drawEllipse( 950 - ( 35 + k * 10 ),
                             25 + 15 + j * 360 + 180,
                             5,
                             5 );
    }

    //vertical odd ones
    for( int j = 0; j < 3; ++j )
    for( int k = 0; k < 90; ++k )
    {
        int i = 540 + j * 2 * 90 + k;

        painter.setPen( QPen( QColor( m_leds[ i ].r,
                                      m_leds[ i ].g,
                                      m_leds[ i ].b ) ) );

        painter.setBrush( QBrush( QColor( m_leds[ i ].r,
                                          m_leds[ i ].g,
                                          m_leds[ i ].b ) ) );

        painter.drawEllipse( 25 - 5 + j * 360,
                             950 - ( 15 + k * 10 ),
                             5,
                             5 );
    }

    //vertical even ones
    for( int j = 0; j < 3; ++j )
    for( int k = 0; k < 90; ++k )
    {
        int i = 540 + 90 + j * 2 * 90 + k;

        painter.setPen( QPen( QColor( m_leds[ i ].r,
                                      m_leds[ i ].g,
                                      m_leds[ i ].b ) ) );

        painter.setBrush( QBrush( QColor( m_leds[ i ].r,
                                          m_leds[ i ].g,
                                          m_leds[ i ].b ) ) );

        painter.drawEllipse( 25 - 5 + j * 360 + 180,
                             45 + k * 10,
                             5,
                             5 );
    }
}

void MainWindow::stopClicked()
{
    m_playState = STOP;

    m_pPlayButton->setIcon( style()->standardIcon( QStyle::SP_MediaPlay ) );

    m_pEffect->reset();

    initLeds();

    update();

    stateUpdated();
}

void MainWindow::playClicked()
{
    if( m_playState != PLAY )
    {
        m_pPlayButton->setIcon(
            style()->standardIcon( QStyle::SP_MediaPause ) );
        m_playState = PLAY;
    }
    else
    {
        m_pPlayButton->setIcon( style()->standardIcon( QStyle::SP_MediaPlay ) );
        m_playState = PAUSE;
    }

    stateUpdated();
}

void MainWindow::stepClicked()
{
    updateEffect();
}

void MainWindow::actionBackgroundClicked()
{
    QColor color = QColorDialog::getColor( Qt::yellow, this );
    if( color.isValid() )
    {
      QPalette pal = palette();

      pal.setColor( QPalette::Window, color );

      this->setPalette( pal );
    }
}

void MainWindow::actionFramerateClicked()
{
    bool ok( false );

    int current_framerate = static_cast<int>( 1000.0 / m_timerInterval );

    int ret = QInputDialog::getInt( this,
                                    "Set framerate",
                                    "Framerate [hz]:",
                                    current_framerate,
                                    1,
                                    100,
                                    1,
                                    &ok );

    if( ok )
    {
        m_timerInterval = 1000 / ret;

        stateUpdated();
    }
}

void MainWindow::effectSelected()
{
    m_pEffect = m_effects[ qobject_cast<QAction*>( sender() ) ];

    m_pEffect->reset();
}

void MainWindow::updateEffect()
{
    m_pEffect->update();

    this->update();
}

void MainWindow::makeConnections()
{
    connect( ui->actionBackground,
             SIGNAL( triggered( bool ) ),
             this,
             SLOT( actionBackgroundClicked() ) );

    connect( ui->actionFramerate,
             SIGNAL( triggered( bool ) ),
             this,
             SLOT( actionFramerateClicked() ) );

    m_pResetButton = new QToolButton(this);
    m_pResetButton->setIcon( style()->standardIcon( QStyle::SP_MediaStop ) );

    m_pResetButton->setIconSize( QSize( 50, 50 ) );
    m_pResetButton->setGeometry( 395, 970, 50, 50 );

    connect( m_pResetButton, SIGNAL( clicked() ), this, SLOT( stopClicked() ) );

    m_pPlayButton = new QToolButton(this);
    m_pPlayButton->setIcon( style()->standardIcon( QStyle::SP_MediaPlay ) );

    m_pPlayButton->setIconSize( QSize( 50, 50 ) );
    m_pPlayButton->setGeometry( 450, 970, 50, 50 );

    connect( m_pPlayButton, SIGNAL( clicked() ), this, SLOT( playClicked() ) );

    m_pStepButton = new QToolButton( this );
    m_pStepButton->setIcon(
        style()->standardIcon( QStyle::SP_MediaSkipForward ) );

    m_pStepButton->setIconSize( QSize( 50, 50 ) );
    m_pStepButton->setGeometry( 505, 970, 50, 50 );

    connect( m_pStepButton, SIGNAL( clicked() ), this, SLOT( stepClicked() ) );

    m_pTimer = new QTimer( this );
    connect( m_pTimer, SIGNAL( timeout() ), this, SLOT( updateEffect() ) );

}

void MainWindow::addMenuItems()
{
    addMenuItem( new runner( m_leds ), "Runner" );
    addMenuItem( new sky_effect( m_leds ), "Sky effect" );
    addMenuItem( new diagonal_on( m_leds ), "Diagonal on" );
    addMenuItem( new diagonal_on_2( m_leds ), "Diagonal on 2" );
    addMenuItem( new race_cars( m_leds ), "Race cars" );
}

void MainWindow::addMenuItem(ieffect* pEffect, QString name)
{
    QAction* act = ui->menuEffect->addAction( name );

    m_effects[ act ] = pEffect;

    connect( act, SIGNAL( triggered() ), this, SLOT( effectSelected() ) );
}

void MainWindow::initLeds()
{
    for( int i = 0; i < 1080; ++i )
    {
        m_leds[ i ].r = 0;
        m_leds[ i ].g = 0;
        m_leds[ i ].b = 0;
    }
}

void MainWindow::stateUpdated()
{
    switch( m_playState )
    {
        case PAUSE:
            m_pTimer->stop();
        break;

        case PLAY:
            m_pTimer->start( m_timerInterval );
        break;

        case STOP:
            m_pTimer->stop();
        break;

        default:
        break;
    }
}

