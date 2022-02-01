#include "newgamedialog.hh"
#include "ui_newgamedialog.h"

NewGameDialog::NewGameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewGameDialog)
{
    ui->setupUi(this);
}

NewGameDialog::~NewGameDialog()
{
    if (ui)
    {
        delete ui;
        ui = nullptr;
    }
}

void NewGameDialog::on_nextPushButton_clicked()
{
    this->close();
}

int NewGameDialog::get_players_amount() const
{
    if (ui->twoPlayersRadioButton->isChecked())
    {
        return 2;
    }
    else if (ui->threePlayersRadioButton->isChecked())
    {
        return 3;
    }
    else if (ui->fourPlayersRadioButton->isChecked())
    {
        return 4;
    }
    return 0;
}

int NewGameDialog::get_difficulty_level() const
{
    if (ui->easyModeRadioButton->isChecked())
    {
        return 12;
    }
    else if (ui->mediumModeRadioButton->isChecked())
    {
        return 16;
    }
    else if (ui->hardModeRadioButton->isChecked())
    {
        return 24;
    }
    return 0;
}

