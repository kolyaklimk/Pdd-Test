#ifndef TICKETS_H
#define TICKETS_H
#include <QVector>
#include <QString>
struct tickets
{
    int answer[20]; //выбранный ответ
    int correctAnswer[20]; //правильный ответ
    int numberOfOptions[20]; //количество вариантов
    QString pictures[20]; //путь к картинкам
};

#endif // TICKETS_H
