#ifndef STOPWATCH_H
#define STOPWATCH_H
#include <QTimer>
#include <QObject>

class StopWatch : public QObject
{
    Q_OBJECT
public:
    explicit StopWatch(QObject *parent = nullptr);

signals:

    void timeUpdated(QString timeString);
    void timecircle (QString timeCircle);
public slots:
    void start( );
    void stop();
     void updateTime();
    void clear();
     void circle();
    bool runing();
private:
    QTimer *time;
    double timeValue;
    double lastLapTime;
    int lapCount;
    bool running;

};

#endif // STOPWATCH_H
