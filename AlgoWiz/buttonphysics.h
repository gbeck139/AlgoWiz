/**
 * @file ButtonPhysics.h
 * @author Jared Pratt, Grant Beck
 * @brief Header file for the ButtonPhysics class, which applies simple Box2D physics simulation to QPushButton widgets.
 * @date 2025-04-25
 */

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

/**
 * @class ButtonPhysics
 * @brief Applies 2D physics simulation to QPushButton widgets using Box2D, adding dynamic motion effects.
 */
class ButtonPhysics : public QObject
{
    Q_OBJECT

    QElapsedTimer m_clock; // Timer to track elapsed time for physics calculations.
    QHash<QPushButton*, float> m_phase; // Stores random phase values for each button, used for impulse variation.

public:
    /**
     * @brief Constructor for ButtonPhysics.
     * @param parent - the parent widget.
     * @param buttons - list of QPushButton pointers to apply physics to.
     */
    ButtonPhysics(QWidget* parent, const QList<QPushButton*>& buttons);

    /**
     * @brief Destructor for ButtonPhysics.
     */
    ~ButtonPhysics();

    /**
     * @brief eventFilter - intercepts events for the buttons to apply physics-based nudging on hover.
     * @param watched - the object being watched.
     * @param event - the event that occurred.
     * @return true if the event was handled, false otherwise.
     */
    bool eventFilter(QObject* watched, QEvent* event) override;

private slots:
    /**
     * @brief updatePhysics - called periodically to step the physics simulation and update button positions.
     */
    void updatePhysics();

private:
    /**
     * @brief initPhysics - initializes the Box2D world and physics bodies.
     */
    void initPhysics();

    /**
     * @brief createButtonBody - creates a Box2D body for a given button.
     * @param button - the QPushButton to assign a physics body.
     */
    void createButtonBody(QPushButton* button);

    /**
     * @brief toPixels - converts a Box2D position (in meters) to pixels.
     * @param position - the Box2D vector position.
     * @return QPointF representing the position in pixels.
     */
    QPointF toPixels(const b2Vec2& position);

    /**
     * @brief toMeters - converts a pixel position to Box2D meters.
     * @param position - the QPointF pixel position.
     * @return b2Vec2 representing the position in meters.
     */
    b2Vec2 toMeters(const QPointF& position);

    QWidget* m_parent; // Parent widget for the buttons.
    QList<QPushButton*> m_buttons; // List of buttons being affected by the physics simulation.
    QTimer* m_timer;
    b2World* m_world;
    QMap<QPushButton*, b2Body*> m_buttonBodies; // Mapping from buttons to their corresponding Box2D bodies.
    QMap<QPushButton*, QPoint> m_originalPositions;

    const float PIXELS_PER_METER = 100.0f;
    const float TIME_STEP = 1.0f / 60.0f;
    const int VELOCITY_ITERATIONS = 6;
    const int POSITION_ITERATIONS = 2;
};

#endif // BUTTONPHYSICS_H
