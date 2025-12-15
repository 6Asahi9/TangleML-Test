#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QShortcut>
#include "ui_mainwindow.h"
#include "PythonHighlighter.h"
#include "GraphicsViewCanvas.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(const QString &projectName,
                        const QString &projectPath,
                        QWidget *parent = nullptr);

    void loadModelFile(const QString &filePath);
    void appendConsole(const QString &text);
    void reloadModelFile();
    void savePyViewToModel();

private:
    Ui::MainWindow ui;
    QString currentProjectPath;
    PythonHighlighter *highlighter = nullptr;

    // -------- Canvas
    GraphicsViewCanvas *canvas = nullptr;

    // -------- Zoom state (per project)
    double canvasZoom = 1.0;
    int pyZoom = 0;

    // -------- Helpers
    void disableParentDragging(QTreeWidgetItem* item);

    void loadViewSettings();
    void saveViewSettings();

    void zoomIn();
    void zoomOut();
};

#endif // MAINWINDOW_H
