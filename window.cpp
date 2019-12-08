#include "window.h"
#include "ui_window.h"
#include "consts.h"

#include <QFileDialog>
#include <QDialog>
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>
#include <QFormLayout>
#include <QLabel>

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);
    setFixedSize(windowProps::W_onLoad, windowProps::H_onLoad);
}

Window::~Window()
{
    delete ui;
}

// Loading an image
void Window::on_action_file_open_triggered()
{
    isAnyfileLoaded = true;
    const std::string path = QFileDialog::getOpenFileName(this,                        // Parent window
                                                          tr("Открыть изображение"),   // Windows title
                                                          tr(""),                      // Default path
                                                          tr("Images (*.jpeg *.jpg)")) // Saving path
            .toStdString();

    img.load(path);
    display();
}

// Display it on scene
void Window::display()
{

    setFixedSize(img.getW(), img.getH());
    ui->graphicsView->resize(img.getW(), img.getH());

    this->scene.addPixmap(img.toQPixmap());

    ui->graphicsView->setScene(&scene);
}

bool Window::isImageReady()
{
    if (!isAnyfileLoaded) {
        QMessageBox::critical(this, tr("Ошибка"), tr("Сначала загрузите файл"));
        return false;
    }
    return true;
}

void Window::on_action_file_close_triggered()
{
    this->close();
}

void Window::on_action_file_save_triggered()
{
    if (not isImageReady()) return;

    img.save();
}

void Window::on_action_file_saveAs_triggered()
{
    if(not isImageReady()) return;

    std::string path = QFileDialog::getSaveFileName(this,
                                                          "Сохранить изображение",
                                                          "",
                                                          "Images (*.jpeg *.jpg)")
            .toStdString();
    img.save(path);
}

void Window::on_action_props_props_triggered()
{
    std::string props = img.getProps();

    QMessageBox msg(this);
    msg.setText(tr("Свойства изображения"));
    msg.setDetailedText(QString::fromStdString(props));
    msg.exec();
}

void Window::on_action_img_std_blur_gaussianBlur_triggered()
{
    if (not isImageReady()) return;
    int size = QInputDialog::getInt(this, "Размер ядра Гаусса", "Введите размер ядра Гаусса", 3, 0, 50, 2);
    if (size % 2 != 1) {
        QMessageBox::critical(this, tr("Ошибка"), tr("Размер ядра Гаусса должен быть нечётным числом"));
        return;
    }
    img.applyGaussianBlur(size, size);
    display();
}

void Window::on_action_img_std_blur_medianBlur_triggered()
{
    if (not isImageReady()) return;
    int size = QInputDialog::getInt(this, "Размер ядра медианного фильтра", "Введите размер медианного фильтра", 3, 0, 50, 2);
    if (size % 2 != 1) {
        QMessageBox::critical(this, tr("Ошибка"), tr("Размер медианного фильтра должен быть нечётным числом"));
        return;
    }
    img.applyMedianBlurring(size);
    display();
}

void Window::on_action_img_std_sharp_sharp_triggered()
{
    if (not isImageReady()) return;
    img.applySharp();
    display();
}

void Window::on_action_img_changeSize_triggered()
{
    if (not isImageReady()) return;
    double coef = QInputDialog::getDouble(this, "Изменить размер", "Коэфицент изменения", 1, 0, 50, 5);
    img.changeSize(coef);
    display();
}
