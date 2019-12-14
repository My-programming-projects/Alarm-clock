#ifndef PREVIEWWIDGET_H
#define PREVIEWWIDGET_H

#include <QDialog>

#include "stylessheets.h"

namespace Ui {
class PreviewWidget;
}

class PreviewWidget : public QDialog
{
    Q_OBJECT

public:
    explicit PreviewWidget(QWidget *parent = nullptr);
    ~PreviewWidget();

    void updateStyleSheet(const QString& styleSheet);

private:
    Ui::PreviewWidget *ui;
};

#endif // PREVIEWWIDGET_H
