/* Copyright (c) 2013 Rich Mattes
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "reactiontime.h"
#include "ui_reactiontime.h"
#include <QDebug>
#include <QKeyEvent>

ReactionTime::ReactionTime(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ReactionTime)
{
    ui->setupUi(this);

    // Seed the random number generator
    QTime midnight(0, 0, 0);
    srand(midnight.secsTo(QTime::currentTime()));

    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(startButtonHandler()));
    connect(&m_updateTimer, SIGNAL(timeout()), this, SLOT(updateUI()));

    m_normalPalette = ui->millisecondTime->palette();
    m_donePalette = ui->millisecondTime->palette();
    m_donePalette.setColor(QPalette::Text, QColor(0, 255, 0));
    m_donePalette.setColor(QPalette::WindowText, QColor(0, 255, 0));
    m_running = false;
    m_paused = false;
    m_totalTrials = 10;

    m_updateTimer.start(30);
}

ReactionTime::~ReactionTime()
{
    delete ui;
}

void ReactionTime::startButtonHandler()
{
    ui->startButton->setEnabled(false);
    ui->millisecondTime->setPalette(m_normalPalette);
    ui->millisecondTime->display(0);

    m_trialCount = 0;
    m_totalTime = 0;

    m_running = true;
    m_paused = true;
    m_time.start();

    m_restartTime = QTime::currentTime().addMSecs(getDelayTime() * 1000.0);

}

void ReactionTime::keyPressEvent(QKeyEvent *event)
{
    int finalTime;
    if (m_running && !m_paused) {
        if (event->key() == Qt::Key_Space) {
            finalTime = m_time.elapsed();
            ui->millisecondTime->display(finalTime);

            ++m_trialCount;
            m_totalTime += finalTime;

            if (m_trialCount >= m_totalTrials) {
                m_running = false;
                ui->startButton->setEnabled(true);
                qDebug() << QString("Average time: %1").arg(m_totalTime / m_trialCount);
                ui->millisecondTime->display(m_totalTime / m_trialCount);
                ui->millisecondTime->setPalette(m_donePalette);
            } else {
                m_paused = true;
                m_restartTime = QTime::currentTime().addMSecs(getDelayTime()*1000.0);
            }
        }
    }
}

void ReactionTime::updateUI()
{
    if (m_running) {
        if (m_paused) {
            if (QTime::currentTime().msecsTo(m_restartTime) <= 0) {
                m_paused = false;
                m_time.restart();
            }
        } else {
            ui->millisecondTime->display(m_time.elapsed());
        }
    }
}

double ReactionTime::getDelayTime()
{
     double randomNumber = ((double)rand() / static_cast<double>( RAND_MAX ) * 6.0) + 2.0;
     qDebug() << QString("Random Number: %1").arg(randomNumber);
     return randomNumber;
}
