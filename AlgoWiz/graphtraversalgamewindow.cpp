#include "graphtraversalgamewindow.h"
#include "graphalgorenderer.h"
#include <QTabWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QRandomGenerator>
#include <QQueue>
#include <QSet>
#include <QMap>
#include <algorithm>

GraphTraversalGameWindow::GraphTraversalGameWindow(QWidget *parent)
    : QWidget(parent),
    bfsRenderer(new GraphAlgoRenderer(this)),
    dfsRenderer(new GraphAlgoRenderer(this)),
    bfsLabel (new QLabel(this)),
    dfsLabel (new QLabel(this)),
    bfsIndex(0),
    dfsIndex(0)
{
    setWindowTitle("Graph Traversal Quiz");
    setupTabs();

    // first call to prime the BFS tab, second to prime the DFS tab
    resetGame(true);
    resetGame(false);
}

void GraphTraversalGameWindow::setupTabs()
{
    auto *tabs = new QTabWidget(this);

    // --- BFS Tab ---
    bfsRenderer->createUnweightedGraph();
    bfsLabel->setWordWrap(true);
    bfsLabel->setFont(QFont("Arial", 25));
    connect(bfsRenderer, &GraphAlgoRenderer::nodeClicked, this, [=](const QString &id){
        if (bfsIndex < bfsList.size() && id == bfsList[bfsIndex]) {
            bfsRenderer->setNodeColor(id, bfsIndex+1==bfsList.size()?Qt::green:Qt::yellow);
            if (++bfsIndex == bfsList.size()) {
                bfsLabel->setText("BFS Complete!");
                emit playerFinished();
            }
        } else {
            bfsRenderer->setNodeColor(id, Qt::red);
            bfsLabel->setText("Incorrect! The BFS traversal will restart.");
            QTimer::singleShot(1500, this, [=]{ resetGame(true); });
        }
    });

    // --- DFS Tab ---
    dfsRenderer->createUnweightedGraph();
    dfsLabel->setWordWrap(true);
    dfsLabel->setFont(QFont("Arial", 25));
    connect(dfsRenderer, &GraphAlgoRenderer::nodeClicked, this, [=](const QString &id){
        if (dfsIndex < dfsList.size() && id == dfsList[dfsIndex]) {
            dfsRenderer->setNodeColor(id, dfsIndex+1==dfsList.size()?Qt::green:Qt::yellow);
            if (++dfsIndex == dfsList.size()) {
                dfsLabel->setText("DFS Complete!");
                emit playerFinished();
            }
        } else {
            dfsRenderer->setNodeColor(id, Qt::red);
            dfsLabel->setText("Incorrect! The DFS traversal will restart.");
            QTimer::singleShot(1500, this, [=]{ resetGame(false); });
        }
    });

    // Layout both tabs
    auto *bfsLay = new QVBoxLayout;
    bfsLay->addWidget(bfsLabel);
    bfsLay->addWidget(bfsRenderer, 1);
    auto *dfsLay = new QVBoxLayout;
    dfsLay->addWidget(dfsLabel);
    dfsLay->addWidget(dfsRenderer, 1);

    auto *bfsW = new QWidget; bfsW->setLayout(bfsLay);
    auto *dfsW = new QWidget; dfsW->setLayout(dfsLay);

    tabs->addTab(bfsW, "BFS Challenge");
    tabs->addTab(dfsW, "DFS Challenge");

    auto *root = new QVBoxLayout(this);
    root->addWidget(tabs);
}

void GraphTraversalGameWindow::resetGame(bool bfsMode)
{
    // pick a random start node
    auto keys  = bfsRenderer->nodes.keys();
    QString start = keys.at(QRandomGenerator::global()->bounded(keys.size()));

    if (bfsMode) {
        bfsIndex = 0;
        bfsList  = bfsOrder(start);
        bfsLabel->setText(
            QString("Hint: BFS visits level by level.\n"
                    "Ties are broken alphabetically.\n\n"
                    "Start at “%1”")
                .arg(start)
            );
        // reset all node colors
        for (auto it = bfsRenderer->nodes.constBegin(),
             end = bfsRenderer->nodes.constEnd();
             it != end; ++it)
        {
            bfsRenderer->setNodeColor(it.key(), Qt::black);
        }
    } else {
        dfsIndex = 0;
        dfsList  = dfsOrder(start);
        dfsLabel->setText(
            QString("Hint: DFS goes deep before backtracking.\n"
                    "Ties are broken alphabetically.\n\n"
                    "Start at “%1”")
                .arg(start)
            );
        for (auto it = dfsRenderer->nodes.constBegin(),
             end = dfsRenderer->nodes.constEnd();
             it != end; ++it)
        {
            dfsRenderer->setNodeColor(it.key(), Qt::black);
        }
    }
}

QVector<QString> GraphTraversalGameWindow::bfsOrder(const QString &start)
{
    QMap<QString,QSet<QString>> adj;
    for (auto &e : bfsRenderer->edges) {
        adj[e.from].insert(e.to);
        adj[e.to].insert(e.from);
    }

    QVector<QString> out;
    QQueue<QString> queue;
    QSet<QString> seen;
    queue.enqueue(start);
    seen.insert(start);

    while (!queue.isEmpty()) {
        auto u = queue.dequeue();
        out.append(u);
        auto nbrs = adj[u].values();
        std::sort(nbrs.begin(), nbrs.end());
        for (auto &v : nbrs)
            if (!seen.contains(v)) {
                seen.insert(v);
                queue.enqueue(v);
            }
    }
    return out;
}

QVector<QString> GraphTraversalGameWindow::dfsOrder(const QString &start)
{
    QMap<QString,QSet<QString>> adj;
    for (auto &e : dfsRenderer->edges) {
        adj[e.from].insert(e.to);
        adj[e.to].insert(e.from);
    }

    QVector<QString> out;
    QSet<QString> seen;
    std::function<void(const QString&)> dfs = [&](const QString &u){
        seen.insert(u);
        out.append(u);
        auto nbrs = adj[u].values();
        std::sort(nbrs.begin(), nbrs.end());
        for (auto &v : nbrs)
            if (!seen.contains(v))
                dfs(v);
    };
    dfs(start);
    return out;
}
