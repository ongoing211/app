#ifndef WINDOW_H
#define WINDOW_H

#include "image.h"

#include <QMainWindow>
#include <QGraphicsScene>


QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
QT_END_NAMESPACE

class Window : public QMainWindow
{
    Q_OBJECT

    Ui::Window *ui;
    Image img;
    QGraphicsScene scene;

    void display();

    bool isAnyfileLoaded = false;
    bool isImageReady();

public:
    Window(QWidget *parent = nullptr);
    ~Window();

private slots:
    void on_action_file_open_triggered();
    void on_action_file_close_triggered();
    void on_action_file_save_triggered();
    void on_action_file_saveAs_triggered();
    void on_action_props_props_triggered();
    void on_action_img_std_blur_gaussianBlur_triggered();
    void on_action_img_std_blur_medianBlur_triggered();
    void on_action_img_std_sharp_sharp_triggered();
    void on_action_img_changeSize_triggered();
    void on_action_triggered();
};
#endif // WINDOW_H
