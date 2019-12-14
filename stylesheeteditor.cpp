#include "stylesheeteditor.h"
#include "ui_stylesheeteditor.h"
#include <QStandardItemModel>

StyleSheetEditor::StyleSheetEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StyleSheetEditor),
    previewWidget(new PreviewWidget(parent))
{
    ui->setupUi(this);
    ui->verticalLayout->addWidget(previewWidget);

    setComboBoxState();
    setConnections();
}

StyleSheetEditor::~StyleSheetEditor()
{
    delete ui;
}

void StyleSheetEditor::setComboBoxState()
{
    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui->comboBox->model());

    for(int i = 0; i < ui->comboBox->count(); ++i)
    {
        if(model->item(i)->text() == StylesSheets::getCurrentStyleName())
        {
            model->item(i)->setFlags(model->item(i)->flags() & ~Qt::ItemIsEnabled);
        }
    }

    ui->comboBox->setCurrentText(StylesSheets::getCurrentStyleName());
}

void StyleSheetEditor::setConnections()
{
    QObject::connect(ui->comboBox, &QComboBox::currentTextChanged, this, &StyleSheetEditor::changeLabelBackgroundColor);
    QObject::connect(ui->pushButton, &QPushButton::clicked, this, &StyleSheetEditor::setNewStyleSheets);
}

void StyleSheetEditor::changeLabelBackgroundColor()
{
    newStyleSheets = StylesSheets::getSelectedStyle(ui->comboBox->currentText());
    previewWidget->updateStyleSheet(newStyleSheets);
}

void StyleSheetEditor::setNewStyleSheets()
{
    StylesSheets::setCurrentStyle(ui->comboBox->currentText());
    emit accept();
}

QString StyleSheetEditor::getStyleSheets() const
{
    return newStyleSheets;
}
