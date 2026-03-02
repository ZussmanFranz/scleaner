#ifndef SCHEDULETRANSFORMER_H
#define SCHEDULETRANSFORMER_H

#include <QFile>
#include <QString>
#include <QList>
#include <QStringList>

class ScheduleTransformer
{
public:
    ScheduleTransformer();
    ScheduleTransformer(QString read_file_path);
    void print_schedule_data();
private:
    QString read_file_path;
    QList<QStringList> scheduleData;

    bool read_csv_file();
};

#endif // SCHEDULETRANSFORMER_H
