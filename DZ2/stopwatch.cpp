#include "stopwatch.h"

StopWatch::StopWatch(QObject *parent)
    : QObject(parent),
    time(new QTimer(this)),
    timeValue(0),
    lastLapTime(0),
    lapCount(0),
    running(false)

{
connect(time, &QTimer::timeout, this, &StopWatch::updateTime);

    time->setInterval(100);
}

void StopWatch::start()
{
    if (!running)
    {
        time->start();
        running=true;
    }
}

void StopWatch::stop()
{
    if (running) {
        time->stop();
        running = false;
    }
}

void StopWatch::updateTime()
{
    timeValue += 0.1;
    emit timeUpdated(QString::number(timeValue, 'f', 1));
}

void StopWatch::clear()
{
timeValue = 0;
    lapCount=0;
lastLapTime=0;
}

QString StopWatch::circle()
{
    lapCount++;
    double circle = timeValue-lastLapTime;
    lastLapTime=timeValue;

    QString text=QString("Круг %1, время: %2 сек")
                       .arg(lapCount)
                       .arg(circle, 0, 'f', 1);

    return text;
}

bool StopWatch::runing()
{
    return running;
}

