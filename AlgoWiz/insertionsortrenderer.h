#ifndef INSERTIONSORTRENDERER_H
#define INSERTIONSORTRENDERER_H

#include "sortingalgorenderer.h"
#include <QTimer>

class Insertionsortrenderer : public sortingAlgoRenderer
{
public:
    Insertionsortrenderer();

private:
    void sort();
    QTimer timer;
};

#endif // INSERTIONSORTRENDERER_H
