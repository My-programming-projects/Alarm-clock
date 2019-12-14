#include "previewwidget.h"
#include "ui_previewwidget.h"

PreviewWidget::PreviewWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreviewWidget)
{
    ui->setupUi(this);
    ui->tableWidget->verticalHeader()->setVisible(false);
}

PreviewWidget::~PreviewWidget()
{
    delete ui;
}

void PreviewWidget::updateStyleSheet(const QString &styleSheet)
{
    setStyleSheet(styleSheet);
    ui->pushButton->setStyleSheet(styleSheet);
    ui->comboBox->setStyleSheet(styleSheet);
    ui->tableWidget->setStyleSheet(styleSheet);
    ui->checkBox->setStyleSheet(styleSheet);
    ui->horizontalSlider->setStyleSheet(styleSheet);
    ui->spinBox->setStyleSheet(styleSheet);
    ui->textEdit->setStyleSheet(styleSheet);
}
