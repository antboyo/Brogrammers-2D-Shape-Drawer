#include "polygon.h"
#include <cmath>
#include <QMap>
#include <QStringList>
#include <QPainter>
#include <QPoint>
#include <QVector>
Polygon::Polygon(const QMap<QString,QString> & props, QPaintDevice* device):Shape(props, device)
{
}

void Polygon::draw()
{
    getQPainter().begin(getQDevice());
    setStyles();
    QStringList words = props["ShapeDimensions"].split(", ");
    QVector<QPoint> points;
    QPoint point ;
    drawIdentifier(words[0].toInt(),words[1].toInt());
    int npoints =0;
    for(int i =0; i<words.size();npoints++){
        points.push_back({words[i].toInt(),words[i+1].toInt()});
        i+=2;
    }
    getQPainter().drawPolygon(points.data(),npoints);
    getQPainter().end();
}




void Polygon::move(const int translate_x, const int translate_y)
{
    QStringList words = props["ShapeDimensions"].split(", ");

    QString newDimensions;

    //read the positions in
    for(int i = 0; i < words.size(); i++)
    {
        if(i % 2 == 0)
        {
            //if even number
            words[i] = QString::number(words[i].toInt() + (translate_x - prevTranslate_x));
        }
        else
        {
            //if odd number
            words[i] = QString::number(words[i].toInt() + (translate_y - prevTranslate_y));
        }

        //this if statement makes sure that no extra comma is added to the end
        if(i < words.size() - 1)
        {
           newDimensions += words[i] + ", ";
        }
        else
        {
            newDimensions += words[i];
        }

        QTextStream(stdout) << newDimensions  << endl;
    }

    prevTranslate_x = translate_x;
    prevTranslate_y = translate_y;

    props["ShapeDimensions"] = newDimensions;
    QTextStream(stdout) << props["ShapeDimensions"]  << endl;
}

double Polygon::perimeter()
{
    QStringList words = props["ShapeDimensions"].split(", ");
    return  std::sqrt((words[0].toInt()-words[2].toInt())*(words[0].toInt()-words[2].toInt())+(words[3].toInt()-words[1].toInt())*(words[3].toInt()-words[1].toInt())+0.0);
}

int Polygon::area()
{
    return -1;
}
