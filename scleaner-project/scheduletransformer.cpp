#include "scheduletransformer.h"

#include <QTextStream>
#include <QDebug>
#include <QTime>


enum ActivityType {
    W,  // Wykład = lecture
    P,  // Projekt = project
    L,  // Laby = labs
    S   // Seminarium = seminar
};

enum Frequency {
    Weekly,
    BiWeekly,
    SpecificDates
};

// activity structure (each class in a schedule is an activity)
struct Activity {
    unsigned int day; // 1 for Monday, 5 for Friday

    QTime start_time;
    QTime end_time;

    QDate start_date;
    QDate end_date;

    ActivityType act_type;
    QString group;
    QString subgroup;

    Frequency frequency = Frequency::Weekly;
    QList<QDate> specific_dates; // only if frequency == SpecificDates

    bool occurs_on(const QDate& target_date){
        if (target_date.dayOfWeek() != day) return false;

        if (frequency == Frequency::SpecificDates){
            return specific_dates.contains(target_date);
        }

        if ((start_date != NULL && target_date < start_date) || (end_date != NULL && target_date > end_date)){
            return false;
        }

        if (frequency == Frequency::BiWeekly){
            return (target_date.weekNumber() - start_date.weekNumber()) % 2 == 0;
        }

        return true;
    }
};




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

    // read everything into one large buffer
    QString fullText = in.readAll();
    file.close();

    scheduleData.clear();

    bool inQuotes = false;
    QString currentField = "";
    QStringList currentRow;

    for (int i = 0; i < fullText.length(); i++){
        QChar c = fullText[i];

        if (c == '"'){
            // if we encounter double quotes (""), it means single quote character
            if (inQuotes && i + 1 < fullText.length() && fullText[i+1] == '"'){
                currentField += c;
                i++; // skip the second quote
            } else {
                // toggle state
                inQuotes = !inQuotes;
            }
        } else if (c == ';' && !inQuotes){
            // the field is finished
            currentRow.append(currentField);
            currentField.clear();
        } else if ((c == '\n' || c == '\r') && !inQuotes){
            // the row is finished

            // Windows specific fix for \r\n line endings
            if (c == '\r' && i + 1 < fullText.length() && fullText[i + 1] == '\n'){
                i++;
            }

            currentRow.append(currentField);
            scheduleData.append(currentRow);

            currentRow.clear();
            currentField.clear();
        } else {
            // it's just a normal character
            currentField += c;
        }
    }

    // if the file didn't end properly
    if (!currentField.isEmpty() || !currentRow.isEmpty()) {
        currentRow.append(currentField);
        scheduleData.append(currentRow);
    }

    return true;
}


void ScheduleTransformer::print_schedule_data(){
    for (int i = 0; i < scheduleData.length(); i++){
        // row
        for (int j = 0; j < scheduleData[i].length(); j++){
            // cell
            qDebug() << scheduleData[i][j] << " | ";
        }
        qDebug() << "\n";
    }
}
