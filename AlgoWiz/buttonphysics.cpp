/**
 * @file ButtonPhysics.cpp
 * @author Jared Pratt, Grant Beck
 * @brief Implementation of the ButtonPhysics class, applying Box2D physics simulation to QPushButton widgets.
 * @date 2025-04-25
 */

#include "ButtonPhysics.h"
#include <QDebug>
#include <QRandomGenerator>
#include <QTimer>

ButtonPhysics::ButtonPhysics(QWidget* parent, const QList<QPushButton*>& buttons)
    : QObject(parent), m_parent(parent), m_buttons(buttons)
{
    // Initialize the Box2D physics world with minimal gravity
    m_world = new b2World(b2Vec2(0.0f, 0.03f));

    // Setup the timer for physics updates
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &ButtonPhysics::updatePhysics);

    // Store original button positions
    for (QPushButton* button : m_buttons) {
        m_originalPositions[button] = button->pos();
    }

    initPhysics();

    // Start elapsed timer and assign random phase offsets to each button
    m_clock.start();
    for (QPushButton* b : m_buttons)
    {
        double phase = QRandomGenerator::global()->generateDouble() * 2.0 * M_PI; // 0‒2π
        m_phase[b] = static_cast<float>(phase);
    }

    m_timer->start(20);

    // Install event filters on each button for interactive nudges
    for (QPushButton* button : m_buttons) {
        button->installEventFilter(this);
    }
}

ButtonPhysics::~ButtonPhysics()
{
    m_timer->stop();
    delete m_world;
}

void ButtonPhysics::initPhysics()
{
    for (QPushButton* button : m_buttons) {
        createButtonBody(button);
    }
}

void ButtonPhysics::createButtonBody(QPushButton* button)
{
    QPointF pos = button->pos();

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = toMeters(pos + QPointF(button->width()/2, button->height()/2));
    bodyDef.linearDamping = 4.0f;
    bodyDef.angularDamping = 2.0f;
    bodyDef.fixedRotation = false;
    bodyDef.bullet = true;

    b2Body* body = m_world->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(toMeters(QPointF(button->width()/2, button->height()/2)).x,
                        toMeters(QPointF(button->width()/2, button->height()/2)).y);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 0.5f;
    fixtureDef.friction = 2.5f;
    fixtureDef.restitution = 0.05f;

    body->CreateFixture(&fixtureDef);

    m_buttonBodies[button] = body;

    body->SetAwake(true);
    body->SetLinearVelocity(b2Vec2(0, 0));
}

void ButtonPhysics::updatePhysics()
{
    m_world->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

    double t = m_clock.elapsed() / 1000.0;
    const float amp_px = 4.0f;
    const float freq   = 2.0f;
    const float k      = 0.15f;

    for (QPushButton* button : m_buttons) {
        b2Body* body = m_buttonBodies[button];
        if (!body) continue;

        QPoint origPx = m_originalPositions[button];
        b2Vec2 home   = toMeters(origPx + QPointF(button->width()/2, button->height()/2));

        float phase   = m_phase[button];
        float dx_px   = amp_px * std::sin(2 * M_PI * freq * t + phase);
        float dy_px   = amp_px * std::cos(2 * M_PI * freq * t + phase);
        b2Vec2 wobble = toMeters(QPointF(dx_px, dy_px));

        b2Vec2 pos      = body->GetPosition();
        b2Vec2 target   = home + wobble;
        b2Vec2 delta    = target - pos;

        // Move body toward target with a soft spring effect
        body->SetTransform(pos + k * delta, 0.0f);
        body->SetLinearVelocity(b2Vec2(0, 0));

        QPointF pix = toPixels(body->GetPosition());
        button->move(pix.x() - button->width()/2, pix.y() - button->height()/2);
    }
}

QPointF ButtonPhysics::toPixels(const b2Vec2& position)
{
    return QPointF(position.x * PIXELS_PER_METER, position.y * PIXELS_PER_METER);
}

b2Vec2 ButtonPhysics::toMeters(const QPointF& position)
{
    return b2Vec2(position.x() / PIXELS_PER_METER, position.y() / PIXELS_PER_METER);
}

bool ButtonPhysics::eventFilter(QObject* watched, QEvent* event)
{
    QPushButton* button = qobject_cast<QPushButton*>(watched);
    if (button && m_buttons.contains(button)) {
        b2Body* body = m_buttonBodies[button];

        if (event->type() == QEvent::Enter && body) {
            // Apply a gentle nudge when the mouse hovers over the button
            body->SetLinearVelocity(b2Vec2(0, 0));

            float forceX = (QRandomGenerator::global()->bounded(6) - 3) * 0.7f;
            float forceY = -0.7f;
            body->ApplyLinearImpulse(b2Vec2(forceX, forceY), body->GetWorldCenter(), true);

            // Slightly scale the button visually
            QString currentStyle = button->styleSheet();
            if (!currentStyle.contains("transform: scale(")) {
                button->setStyleSheet(currentStyle + " transform: scale(1.02);");
            }

            return true;
        }
        else if (event->type() == QEvent::Leave) {
            // Remove scaling when the mouse leaves
            QString currentStyle = button->styleSheet();
            if (currentStyle.contains("transform: scale(")) {
                int start = currentStyle.indexOf("transform:");
                int end = currentStyle.indexOf(";", start);
                if (end != -1) {
                    currentStyle.remove(start, end - start + 1);
                    button->setStyleSheet(currentStyle);
                }
            }

            return true;
        }
    }
    return QObject::eventFilter(watched, event);
}
