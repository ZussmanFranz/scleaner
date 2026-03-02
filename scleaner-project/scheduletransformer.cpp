#include "scheduletransformer.h"

#include <QTextStream>
#include <QDebug>


ScheduleTransformer::ScheduleTransformer() {
    // OK
}

ScheduleTransformer::ScheduleTransformer(QString read_file_path) {
    this->read_file_path = read_file_path;

    // now read the file
    read_csv_file();
}

bool ScheduleTransformer::read_csv_file(){
    if (read_file_path.isEmpty()){
        qDebug() << "Error: File path is empty!";
        return false;
    }

    QFile file(read_file_path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Failed to open file:" << file.errorString();
        return false;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();

        qDebug() << line;
    }

    return true;
}
