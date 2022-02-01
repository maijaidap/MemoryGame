#include "playernamesdialog.hh"
#include "ui_playernamesdialog.h"

PlayerNamesDialog::PlayerNamesDialog(QWidget *parent, int number_of_players) :
    QDialog(parent),
    ui(new Ui::PlayerNamesDialog)
{
    ui->setupUi(this);
    // Finding the amount of players so that it's clear 
    // input fields is needed for player names. 
    number_of_players_ = number_of_players;

    // Hiding text fields according to the amount of players.
    if (number_of_players == 2)
    {
        ui->playerThreeFrame->hide();
        ui->playerFourFrame->hide();
    }
    else if (number_of_players == 3)
    {
        ui->playerFourFrame->hide();
    }
}

PlayerNamesDialog::~PlayerNamesDialog()
{
    if (ui)
    {
        delete ui;
        ui = nullptr;
    }
}

std::vector<QString> PlayerNamesDialog::get_player_names() const
{
    std::vector<QString> player_names = {};

    player_names.push_back(ui->player1LineEdit->text());
    player_names.push_back(ui->player2LineEdit->text());
    player_names.push_back(ui->player3LineEdit->text());
    player_names.push_back(ui->player4LineEdit->text());

    return player_names;
}

void PlayerNamesDialog::on_startPushButton_clicked()
{
    this->close();
}
