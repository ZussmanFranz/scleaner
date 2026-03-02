#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QString>

class Activity
{
public:
    Activity();
private:
    int day;    // day of week
    int from;   // starting hour
    int to;     // ending hour
    //type (enum)
    QString group;
    QString subgroup;
    //start_date (?)
    //end_date (?)
};

#endif // ACTIVITY_H
