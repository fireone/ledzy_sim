#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QAction>

#include <map>

#include "ieffect.h"
#include "leds.h"

namespace Ui {
class MainWindow;
}

class QAbstractButton;

enum PLAY_STATE
{
    PAUSE,
    PLAY,
    STOP
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void stopClicked();
    void playClicked();
    void stepClicked();

    void actionBackgroundClicked();
    void actionFramerateClicked();

    void effectSelected();

    void updateEffect();



private:
    void makeConnections();

    void addMenuItems();
    void addMenuItem( ieffect* pEffect, QString name );

    void initLeds();

    void stateUpdated();

    Ui::MainWindow *ui;

    QAbstractButton *m_pResetButton;
    QAbstractButton *m_pPlayButton;
    QAbstractButton *m_pStepButton;

    led::RGB m_leds[1080];

    PLAY_STATE m_playState;

    QTimer *m_pTimer;
    int m_timerInterval;

    ieffect* m_pEffect;

    std::map<QAction*, ieffect*> m_effects;
};

#endif // MAINWINDOW_H
