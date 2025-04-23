// ButtonPhysics.h
#ifndef BUTTONPHYSICS_H
#define BUTTONPHYSICS_H

#include <QObject>
#include <QTimer>
#include <QPushButton>
#include <QList>
#include <QWidget>
#include <QPointF>
#include <QEvent>
#include <Box2D/Box2D.h>
#include <QElapsedTimer>

class ButtonPhysics : public QObject
{
    Q_OBJECT

    QElapsedTimer m_clock;
    QHash<QPushButton*, float> m_phase;

public:
    ButtonPhysics(QWidget* parent, const QList<QPushButton*>& buttons);
    ~ButtonPhysics();

    bool eventFilter(QObject* watched, QEvent* event) override;

private slots:
    void updatePhysics();

private:
    void initPhysics();
    void createButtonBody(QPushButton* button);
    QPointF toPixels(const b2Vec2& position);
    b2Vec2 toMeters(const QPointF& position);

    QWidget* m_parent;
    QList<QPushButton*> m_buttons;
    QTimer* m_timer;
    b2World* m_world;
    QMap<QPushButton*, b2Body*> m_buttonBodies;

    QMap<QPushButton*, QPoint> m_originalPositions;

    const float PIXELS_PER_METER = 100.0f;
    const float TIME_STEP = 1.0f / 60.0f;
    const int VELOCITY_ITERATIONS = 6;
    const int POSITION_ITERATIONS = 2;
};

#endif // BUTTONPHYSICS_H
