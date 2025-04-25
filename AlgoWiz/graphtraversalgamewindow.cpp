/**
 * @file graphtraversalgamewindow.cpp
 * @brief Implementation of the GraphTraversalGameWindow class, providing an interactive game for BFS and DFS traversal practice.
 * @author Jared Pratt, Grant Beck
 * @date 2025-04-25
 */

#include "graphtraversalgamewindow.h"
#include "graphalgorenderer.h"
#include "styleutils.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QRandomGenerator>
#include <QQueue>
#include <QSet>
#include <QMap>
#include <QStackedWidget>
#include <QFrame>
#include <algorithm>

// Constructor: Initializes game components and UI
GraphTraversalGameWindow::GraphTraversalGameWindow(QWidget *parent)
    : QWidget(parent),
    bfsRenderer(new GraphAlgoRenderer(this)),
    dfsRenderer(new GraphAlgoRenderer(this)),
    bfsLabel(new QLabel(this)),
    dfsLabel(new QLabel(this)),
    stackedWidget(new QStackedWidget(this)),
    bfsButton(new QPushButton("BFS Challenge", this)),
    dfsButton(new QPushButton("DFS Challenge", this)),
    restartButton(new QPushButton("RESTART", this)),
    bfsIndex(0),
    dfsIndex(0),
    currentMode(true)
{
    setWindowTitle("Graph Traversal Quiz");
    setupUI();

    // Prepare both game modes initially
    resetGame(true);
    resetGame(false);
    switchMode(true);
    restartButton->hide();
}

void GraphTraversalGameWindow::setupUI()
{
    // UI setup for BFS and DFS pages with renderer, labels, and frames
    auto *bfsPage = new QWidget(this);
    auto *dfsPage = new QWidget(this);

    auto *bfsBackingFrame = new QFrame(this);
    bfsBackingFrame->setFrameShape(QFrame::StyledPanel);
    bfsBackingFrame->setStyleSheet("QFrame { background-color: rgba(40, 40, 50, 0.6); border-radius: 12px; }");
    bfsBackingFrame->setMinimumHeight(500);

    auto *dfsBackingFrame = new QFrame(this);
    dfsBackingFrame->setFrameShape(QFrame::StyledPanel);
    dfsBackingFrame->setStyleSheet("QFrame { background-color: rgba(40, 40, 50, 0.6); border-radius: 12px; }");
    dfsBackingFrame->setMinimumHeight(500);

    bfsRenderer->createUnweightedGraph();
    bfsLabel->setWordWrap(true);
    bfsLabel->setFont(QFont("Arial", 25));
    bfsLabel->setAlignment(Qt::AlignCenter);
    bfsLabel->setStyleSheet("QLabel { color: white; }");
    connect(bfsRenderer, &GraphAlgoRenderer::nodeClicked, this, &GraphTraversalGameWindow::handleBfsNodeClick);

    auto *bfsFrameLayout = new QVBoxLayout(bfsBackingFrame);
    bfsFrameLayout->addWidget(bfsLabel);
    bfsFrameLayout->addWidget(bfsRenderer, 1);
    bfsFrameLayout->setContentsMargins(20, 20, 20, 20);

    auto *bfsLayout = new QVBoxLayout(bfsPage);
    bfsLayout->addWidget(bfsBackingFrame, 1);
    bfsLayout->setContentsMargins(20, 10, 20, 20);

    dfsRenderer->createUnweightedGraph();
    dfsLabel->setWordWrap(true);
    dfsLabel->setFont(QFont("Arial", 25));
    dfsLabel->setAlignment(Qt::AlignCenter);
    dfsLabel->setStyleSheet("QLabel { color: white; }");
    connect(dfsRenderer, &GraphAlgoRenderer::nodeClicked, this, &GraphTraversalGameWindow::handleDfsNodeClick);

    auto *dfsFrameLayout = new QVBoxLayout(dfsBackingFrame);
    dfsFrameLayout->addWidget(dfsLabel);
    dfsFrameLayout->addWidget(dfsRenderer, 1);
    dfsFrameLayout->setContentsMargins(20, 20, 20, 20);

    auto *dfsLayout = new QVBoxLayout(dfsPage);
    dfsLayout->addWidget(dfsBackingFrame, 1);
    dfsLayout->setContentsMargins(20, 10, 20, 20);

    stackedWidget->addWidget(bfsPage);
    stackedWidget->addWidget(dfsPage);

    bfsButton->setStyleSheet(gameButtonStyle());
    dfsButton->setStyleSheet(gameButtonStyle());

    bfsButton->setMinimumHeight(60);
    dfsButton->setMinimumHeight(60);

    restartButton->setStyleSheet(gameButtonStyle() + "QPushButton { font: 800 22px 'Trebuchet MS'; padding: 12px 30px; }");
    restartButton->setMinimumSize(150, 70);

    connect(bfsButton, &QPushButton::clicked, this, [this]() { switchMode(true); });
    connect(dfsButton, &QPushButton::clicked, this, [this]() { switchMode(false); });
    connect(restartButton, &QPushButton::clicked, this, &GraphTraversalGameWindow::handleRestart);

    auto *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(bfsButton, 1);
    buttonLayout->addWidget(dfsButton, 1);
    buttonLayout->setSpacing(20);
    buttonLayout->setContentsMargins(20, 20, 20, 10);

    auto *bottomLayout = new QHBoxLayout();
    bottomLayout->addStretch();
    bottomLayout->addWidget(restartButton);
    bottomLayout->setContentsMargins(20, 10, 40, 30);

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addSpacing(50);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(stackedWidget, 1);
    mainLayout->addLayout(bottomLayout);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
}

void GraphTraversalGameWindow::switchMode(bool toBfs)
{
    // Switch between BFS and DFS modes and handle UI updates
    currentMode = toBfs;
    stackedWidget->setCurrentIndex(toBfs ? 0 : 1);
    bfsButton->setEnabled(!toBfs);
    dfsButton->setEnabled(toBfs);

    bfsButton->setStyleSheet(gameButtonStyle() +
                             (toBfs ? "QPushButton { background: rgba(255,165,0,0.4); border-width: 3px; }" : ""));
    dfsButton->setStyleSheet(gameButtonStyle() +
                             (!toBfs ? "QPushButton { background: rgba(255,165,0,0.4); border-width: 3px; }" : ""));

    bool bfsComplete = bfsIndex == bfsList.size();
    bool dfsComplete = dfsIndex == dfsList.size();

    if (toBfs) {
        restartButton->setVisible(bfsComplete);
    } else {
        restartButton->setVisible(dfsComplete);
    }
}

void GraphTraversalGameWindow::handleBfsNodeClick(const QString &id)
{
    if (bfsIndex >= bfsList.size()) return;

    if (id == bfsList[bfsIndex]) {
        bfsRenderer->setNodeColor(id, bfsIndex+1==bfsList.size() ? Qt::green : Qt::yellow);
        if (++bfsIndex == bfsList.size()) {
            bfsLabel->setText("BFS Complete!");
            restartButton->show();
            emit playerFinished();
        }
    } else {
        // Incorrect click, reset the BFS game
        bfsRenderer->setNodeColor(id, Qt::red);
        bfsLabel->setText("Incorrect! The BFS traversal will restart.");
        QTimer::singleShot(1500, this, [=]{ resetGame(true); });
    }
}

void GraphTraversalGameWindow::handleDfsNodeClick(const QString &id)
{
    if (dfsIndex >= dfsList.size()) return;

    if (id == dfsList[dfsIndex]) {
        dfsRenderer->setNodeColor(id, dfsIndex+1==dfsList.size() ? Qt::green : Qt::yellow);
        if (++dfsIndex == dfsList.size()) {
            dfsLabel->setText("DFS Complete!");
            restartButton->show();
            emit playerFinished();
        }
    } else {
        // Incorrect click, reset the DFS game
        dfsRenderer->setNodeColor(id, Qt::red);
        dfsLabel->setText("Incorrect! The DFS traversal will restart.");
        QTimer::singleShot(1500, this, [=]{ resetGame(false); });
    }
}

void GraphTraversalGameWindow::handleRestart()
{
    resetGame(currentMode);
    restartButton->hide();
}

void GraphTraversalGameWindow::resetGame(bool bfsMode)
{
    // Resets the game state and regenerates the correct traversal order
    auto renderer = bfsMode ? bfsRenderer : dfsRenderer;
    auto keys = renderer->nodes.keys();
    QString start = keys.at(QRandomGenerator::global()->bounded(keys.size()));

    if (bfsMode) {
        bfsIndex = 0;
        bfsList = bfsOrder(start);
        bfsLabel->setText(
            QString("Hint: BFS visits level by level.\n"
                    "Ties are broken alphabetically.\n\n"
                    "Start at “%1”")
                .arg(start)
            );

        for (auto it = bfsRenderer->nodes.constBegin(),
             end = bfsRenderer->nodes.constEnd();
             it != end; ++it)
        {
            bfsRenderer->setNodeColor(it.key(), Qt::black);
        }
    } else {
        dfsIndex = 0;
        dfsList = dfsOrder(start);
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
    // Standard BFS traversal with alphabetical tie-breaking
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
        std::sort(nbrs.begin(), nbrs.end());  // Alphabetical order
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
    // Standard DFS traversal with alphabetical tie-breaking (recursive)
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
        std::sort(nbrs.begin(), nbrs.end());  // Sort neighbors alphabetically for consistent traversal
        for (auto &v : nbrs)
            if (!seen.contains(v))
                dfs(v);
    };
    dfs(start);
    return out;
}

