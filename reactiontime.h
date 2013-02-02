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

#ifndef REACTIONTIME_H
#define REACTIONTIME_H

#include <QMainWindow>
#include <QPalette>
#include <QTime>
#include <QTimer>

namespace Ui {
class ReactionTime;
}

class ReactionTime : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ReactionTime(QWidget *parent = 0);
    ~ReactionTime();

public slots:
    /** Handles key press events for the main window.
     * This function catches space bar presses to stop the timer.
     * If it's the end of a set of trials, it resets the system state.
     */
    void keyPressEvent(QKeyEvent *event);
    /** Handles a start button press
     * Clears application state, and kicks off the first trial.
     */
    void startButtonHandler();
    /** Updates UI and checks for state changes
     * Updates the UI with the current elapsed time.  Also starts
     * the next trial when an inter-trial pause timeout expires.
     */
    void updateUI();

private:
    /** Get a random number between 2 and 8
     * @return random number between 2 and 8
     */
    double getDelayTime();

    Ui::ReactionTime *ui;

    QPalette m_normalPalette;
    QPalette m_donePalette;

    QTimer m_updateTimer;
    QTime m_time;
    QTime m_restartTime;

    int m_totalTrials;

    int m_trialCount; //<! Number of trials that have taken place
    int m_totalTime;     //<! Total millisecond counts

    bool m_running; //<! True from when the start button is pressed, until all trials are done.
    bool m_paused;  //<! True if we're in a delay period between individual trials, false if the counter is running
};

#endif // REACTIONTIME_H
