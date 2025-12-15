#include "MainWindow.h"
#include <QFile>
#include <QTextStream>
#include <QMenu>
#include <QProcess>
#include <QShortcut>
#include <QKeySequence>
#include <QJsonDocument>
#include <QJsonObject>
#include <QGraphicsItem>
#include "CanvasNode.h"

// ----------------------------------------------------

MainWindow::MainWindow(const QString &projectName,
                       const QString &projectPath,
                       QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    currentProjectPath = projectPath;
    setWindowTitle("TangleML - " + projectName);

    // -------- Python highlighter
    highlighter = new PythonHighlighter(ui.plainTextEdit->document());

    // -------- Canvas setup (replace UI placeholder)
    canvas = new GraphicsViewCanvas(ui.tab_1);
    canvas->setGeometry(ui.graphicsViewCanvas->geometry());
    canvas->show();
    ui.graphicsViewCanvas->hide();

    // -------- Engine menu
    QMenu *engineMenu = new QMenu(this);
    engineMenu->addAction("PyTorch");
    engineMenu->addAction("TangleML");
    ui.btnEngine->setMenu(engineMenu);

    connect(engineMenu, &QMenu::triggered, this, [this](QAction *action){
        ui.btnEngine->setText(action->text());
    });

    // -------- Run button
    connect(ui.btnRun, &QPushButton::clicked, this, [this]() {
        savePyViewToModel();

        QString pythonPath = "python";
        QString modelFile = currentProjectPath + "/.tangle/model.py";

        ui.txtConsole->clear();
        appendConsole("Running model.py...\n");

        QProcess *process = new QProcess(this);

        connect(process, &QProcess::readyReadStandardOutput, this, [=]() {
            appendConsole(process->readAllStandardOutput());
        });

        connect(process, &QProcess::readyReadStandardError, this, [=]() {
            appendConsole(process->readAllStandardError());
        });

        process->start(pythonPath, QStringList() << modelFile);
    });

    // -------- Load model.py
    loadModelFile(currentProjectPath + "/.tangle/model.py");

    // -------- Shortcuts
    new QShortcut(QKeySequence("Ctrl+Return"), this, SLOT(savePyViewToModel()));

    QShortcut *zoomInShortcut1 = new QShortcut(QKeySequence("Ctrl+="), this);
    QShortcut *zoomInShortcut2 = new QShortcut(QKeySequence("Ctrl++"), this);
    QShortcut *zoomOutShortcut = new QShortcut(QKeySequence("Ctrl+-"), this);
    QShortcut* deleteShortcut = new QShortcut(QKeySequence(Qt::Key_Delete), this);
    connect(deleteShortcut, &QShortcut::activated, this, [this]() {
        if (!canvas) return;

        QList<QGraphicsItem*> selectedItems = canvas->scene()->selectedItems();
        for (QGraphicsItem* item : selectedItems) {
            canvas->scene()->removeItem(item);

            // Safe delete: cast to CanvasNode*
            CanvasNode* node = dynamic_cast<CanvasNode*>(item);
            if (node) {
                delete node;
            }
        }
    });


    connect(zoomInShortcut1, &QShortcut::activated, this, &MainWindow::zoomIn);
    connect(zoomInShortcut2, &QShortcut::activated, this, &MainWindow::zoomIn);
    connect(zoomOutShortcut, &QShortcut::activated, this, &MainWindow::zoomOut);


    // -------- Tree drag fix
    for (int i = 0; i < ui.treeWidget->topLevelItemCount(); ++i)
        disableParentDragging(ui.treeWidget->topLevelItem(i));

    // -------- Load per-project view state
    loadViewSettings();
}

// ----------------------------------------------------

void MainWindow::zoomIn()
{
    int tab = ui.tabWidget->currentIndex();

    // Canvas tab
    if (tab == 0 && canvas) {
        canvasZoom *= 1.1;

        // Zoom around the center of the viewport
        QPointF center(canvas->viewport()->width() / 2.0,
                       canvas->viewport()->height() / 2.0);
        canvas->zoom(1.1, center);
    }
    // Py tab
    else if (tab == 2) {
        pyZoom++;
        QFont f = ui.plainTextEdit->font();
        f.setPointSize(f.pointSize() + 1);
        ui.plainTextEdit->setFont(f);
    }

    saveViewSettings();
}

void MainWindow::zoomOut()
{
    int tab = ui.tabWidget->currentIndex();

    // Canvas tab
    if (tab == 0 && canvas) {
        canvasZoom /= 1.1;

        QPointF center(canvas->viewport()->width() / 2.0,
                       canvas->viewport()->height() / 2.0);
        canvas->zoom(1.0 / 1.1, center);
    }
    // Py tab
    else if (tab == 2) {
        pyZoom--;
        QFont f = ui.plainTextEdit->font();
        f.setPointSize(f.pointSize() - 1);
        ui.plainTextEdit->setFont(f);
    }

    saveViewSettings();
}

// ----------------------------------------------------

void MainWindow::loadViewSettings()
{
    QFile file(currentProjectPath + "/.tangle/view.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject obj = doc.object();
    file.close();

    canvasZoom = obj.value("canvasZoom").toDouble(1.0);
    pyZoom = obj.value("pyZoom").toInt(0);

    if (canvas) {
        // Apply saved zoom around center
        QPointF center(canvas->viewport()->width() / 2.0,
                       canvas->viewport()->height() / 2.0);
        canvas->zoom(canvasZoom, center);
    }

    QFont f = ui.plainTextEdit->font();
    f.setPointSize(f.pointSize() + pyZoom);
    ui.plainTextEdit->setFont(f);
}


void MainWindow::saveViewSettings()
{
    QFile file(currentProjectPath + "/.tangle/view.json");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QJsonObject obj;
    obj["canvasZoom"] = canvasZoom;
    obj["pyZoom"] = pyZoom;

    QJsonDocument doc(obj);
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
}

// ----------------------------------------------------

void MainWindow::loadModelFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream in(&file);
    ui.plainTextEdit->setPlainText(in.readAll());
    file.close();
}

void MainWindow::appendConsole(const QString &text)
{
    ui.txtConsole->append(text);
}

void MainWindow::reloadModelFile()
{
    loadModelFile(currentProjectPath + "/.tangle/model.py");
}

void MainWindow::savePyViewToModel()
{
    QFile file(currentProjectPath + "/.tangle/model.py");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    QTextStream out(&file);
    out << ui.plainTextEdit->toPlainText();
    file.close();
}

// ----------------------------------------------------

void MainWindow::disableParentDragging(QTreeWidgetItem *item)
{
    if (!item) return;

    if (item->childCount() > 0)
        item->setFlags(item->flags() & ~Qt::ItemIsDragEnabled);

    for (int i = 0; i < item->childCount(); ++i)
        disableParentDragging(item->child(i));
}
