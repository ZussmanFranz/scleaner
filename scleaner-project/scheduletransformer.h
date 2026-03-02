#ifndef SCHEDULETRANSFORMER_H
#define SCHEDULETRANSFORMER_H

#include <QString>
#include <QFile>

class ScheduleTransformer
{
public:
    ScheduleTransformer();
    ScheduleTransformer(QString read_file_path);
private:
    QString read_file_path;
    bool read_csv_file();
};

#endif // SCHEDULETRANSFORMER_H
