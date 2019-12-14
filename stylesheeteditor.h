#ifndef BACKGROUNDOPTIONSDIALOG_H
#define BACKGROUNDOPTIONSDIALOG_H

#include <QDialog>

#include "previewwidget.h"


namespace Ui {
class StyleSheetEditor;
}

class StyleSheetEditor : public QDialog
{
    Q_OBJECT

public:
    explicit StyleSheetEditor(QWidget *parent = nullptr);
    ~StyleSheetEditor();

    QString getStyleSheets() const;

private slots:

    void changeLabelBackgroundColor();
    void setNewStyleSheets();

private:

    void setComboBoxState();
    void setConnections();

    Ui::StyleSheetEditor *ui;

    PreviewWidget* previewWidget;

    QString newStyleSheets;
};

#endif // BACKGROUNDOPTIONSDIALOG_H
