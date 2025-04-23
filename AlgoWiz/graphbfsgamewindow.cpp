#include "graphbfsgamewindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QSet>
#include <QMap>
#include <QQueue>
#include <QtCore/qtimer.h>

GraphBFSGameWindow::GraphBFSGameWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("BFS Game");
    resize(800, 600);

    renderer = new GraphAlgoRenderer;
    renderer->createUnweightedGraph();      // reuse your graph
    connect(renderer, &GraphAlgoRenderer::nodeClicked,
            this,     &GraphBFSGameWindow::handleClick);

    info = new QLabel(
        "Click nodes in BFS order starting from A.\n"
        "Ties are broken alphabetically.", this);
    info->setStyleSheet("font-weight:bold;");

    auto *lay = new QVBoxLayout(this);
    lay->addWidget(info);
    lay->addWidget(renderer, 1);

    resetGame();
}

void GraphBFSGameWindow::resetGame()
{
    correctOrder = bfsOrder("A");   // compute once
    nextIndex = 0;

    // reset node colours
    for (const QString &id : renderer->nodes.keys())
        renderer->setNodeColor(id, Qt::black);

    renderer->update();
}

QVector<QString> GraphBFSGameWindow::bfsOrder(const QString &start)
{
    // classic BFS with alphabetical tie-break
    QMap<QString, QSet<QString>> adj;
    for (const auto &e : renderer->edges) {
        adj[e.from].insert(e.to);
        adj[e.to].insert(e.from);
    }
    for (auto &set : adj)
        set = QSet<QString>(set.begin(), set.end());       // ensure unique

    QQueue<QString> q;
    QSet<QString>   vis;
    QVector<QString> out;

    q.enqueue(start);
    vis.insert(start);

    while (!q.isEmpty()) {
        QString u = q.dequeue();
        out.append(u);

        QStringList nbrs = adj[u].values();
        std::sort(nbrs.begin(), nbrs.end(), [](const QString&a,const QString&b){
            return a < b;           // alphabetical tie break
        });
        for (const QString &v : nbrs) {
            if (!vis.contains(v)) {
                vis.insert(v);
                q.enqueue(v);
            }
        }
    }
    return out;
}

void GraphBFSGameWindow::handleClick(const QString &id)
{
    if (nextIndex >= correctOrder.size()) return; // already done

    if (id == correctOrder[nextIndex]) {
        // correct – colour node yellow/green
        renderer->setNodeColor(id,
                               nextIndex + 1 == correctOrder.size() ? Qt::green : Qt::yellow);
        ++nextIndex;

        if (nextIndex == correctOrder.size()) {
            info->setText("Nice! You completed BFS correctly 🎉");
            emit playerFinished();
        }
    } else {
        // wrong – flash red and reset the game
        renderer->setNodeColor(id, Qt::red);
        info->setText("Oops! That was incorrect. Starting over...");

        // Add a slight delay before resetting to show the red feedback
        QTimer::singleShot(1000, this, [this]() {
            resetGame();
            info->setText("Click nodes in BFS order starting from A.\n"
                          "Ties are broken alphabetically.");
        });
    }
}
