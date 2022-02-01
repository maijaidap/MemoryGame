#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "newgamedialog.hh"
#include "card.hh"

#include <QString>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <vector>
#include <iostream>
#include <random>
#include <algorithm>

const int TIMER_INTERVAL = 1000;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gameboard = new GameBoard();

    // Creating new timer-object..
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_time()));
}

MainWindow::~MainWindow()
{
    if (ui)
    {
        delete ui;
        ui = nullptr;
    }
    if (gameboard)
    {
        delete gameboard;
        gameboard = nullptr;
    }
    if (timer)
    {
        delete timer;
        timer = nullptr;
    }
}

void MainWindow::start_game()
{
    show_player_names();
    create_gameboard_buttons();
    gameboard->shuffle_cards();
    timer->start(TIMER_INTERVAL);
}


void MainWindow::on_actionNewGame_triggered()
{    
    // Saves MainWindow's GameBoard-class into an attribute.
    gameboard->set_main_window(this);

    // Shows NewGameDialog -window.
    NewGameDialog *dlg = new NewGameDialog();
    dlg->exec();
    // Setting information about the amount of players and cards needed for the game.
    gameboard->set_number_of_players(dlg->get_players_amount());
    gameboard->set_number_of_cards(dlg->get_difficulty_level());
    delete dlg;

    // Shows PlayerNamesDialog -window.
    // Transmitting the information about the amount of players.
    PlayerNamesDialog *dlg2 = new PlayerNamesDialog(nullptr, gameboard->get_number_of_players());
    dlg2->exec();
    // Settings players' names into a datastructure.
    gameboard->set_players(dlg2->get_player_names());
    delete dlg2;

    // Clearing resultTextBrowser -field.
    print_text("");

    start_game();
}

void MainWindow::show_player_names()
{
    std::vector<QString> player_names = gameboard->get_player_names();

    // Picking out the players' names into right controls.
    ui->playerOneRadioButton->setText(player_names.at(0));
    ui->playerTwoRadioButton->setText(player_names.at(1));
    ui->playerThreeRadioButton->setText(player_names.at(2));
    ui->playerFourRadioButton->setText(player_names.at(3));

    // Hiding textfileds according to the amount of players.
    if (gameboard->get_number_of_players() == 2)
    {
        ui->playerTwoFrame->show();
        ui->playerThreeFrame->hide();
        ui->playerFourFrame->hide();
    }
    else if (gameboard->get_number_of_players() == 3)
    {
        ui->playerTwoFrame->show();
        ui->playerThreeFrame->show();
        ui->playerFourFrame->hide();
    }
    else if (gameboard->get_number_of_players() == 4)
    {
        ui->playerTwoFrame->show();
        ui->playerThreeFrame->show();
        ui->playerFourFrame->show();
    }
}

void MainWindow::card_clicked(int card_index)
{
    gameboard->show_card(card_index);
}

void MainWindow::create_gameboard_buttons()
{
    clear_timer();

    gameboard->clear_cards();

    // Setting the first check box active.
    ui->playerOneRadioButton->setChecked(true);

    // Obtain the amount of cards.
    int number_of_cards = gameboard->get_number_of_cards();
    // Initializing a card.
    Card* new_card = nullptr;

    // Clear gameboard from cards.
    while (QLayoutItem* item = ui->gameBoardGridLayout->layout()->takeAt(0))
    {
        item->widget()->setVisible(false);
        ui->gameBoardGridLayout->layout()->removeItem(item);
    }

    // Creating buttons to the gameboard.
    for(int i = 0; i < number_of_cards; ++i)
    {
        new_card = new Card(i);
        gameboard->add_card(new_card);

        QPushButton* push_button = new QPushButton(this);
        new_card->set_push_button(push_button);

        push_button->setFixedWidth(60);
        push_button->setFixedHeight(70);
        connect(push_button, &QPushButton::clicked, [this, i] { card_clicked(i); });
        int row = i / 4;
        int column = i % 4;
        ui->gameBoardGridLayout->addWidget(push_button, row,  column);
    }
}

void MainWindow::print_text(std::string text)
{
    ui->resultTextBrowser->setText(QString::fromStdString(text));
}

void MainWindow::update_points(int points)
{
    if (gameboard->get_current_player_index() == 0)
    {
        ui->playerOneRadioButton->setChecked(true);
        ui->playerOnePointsLineEdit->setText(QString::number(points));
    }
    else if (gameboard->get_current_player_index() == 1)
    {
        ui->playerTwoRadioButton->setChecked(true);
        ui->playerTwoPointsLineEdit->setText(QString::number(points));
    }
    else if (gameboard->get_current_player_index() == 2)
    {
        ui->playerThreeRadioButton->setChecked(true);
        ui->playerThreePointsLineEdit->setText(QString::number(points));
    }
    else if (gameboard->get_current_player_index() == 3)
    {
        ui->playerFourRadioButton->setChecked(true);
        ui->playerFourPointsLineEdit->setText(QString::number(points));
    }
}

void MainWindow::update_check_box_status()
{
    if (gameboard->get_current_player_index() == 0)
    {
        ui->playerOneRadioButton->setChecked(true);
    }
    else if (gameboard->get_current_player_index() == 1)
    {
        ui->playerTwoRadioButton->setChecked(true);
    }
    else if (gameboard->get_current_player_index() == 2)
    {
        ui->playerThreeRadioButton->setChecked(true);
    }
    else if (gameboard->get_current_player_index() == 3)
    {
        ui->playerFourRadioButton->setChecked(true);
    }
}

void MainWindow::clear_points()
{
    ui->playerOnePointsLineEdit->setText(0);
    ui->playerTwoPointsLineEdit->setText(0);
    ui->playerThreePointsLineEdit->setText(0);
    ui->playerFourPointsLineEdit->setText(0);
}

void MainWindow::update_time()
{
    timer_seconds_ += 1;
    QString seconds = QStringLiteral("%1").arg(timer_seconds_ % 60, 2, 10, QLatin1Char('0'));
    QString minutes = QStringLiteral("%1").arg(timer_seconds_ / 60, 2, 10, QLatin1Char('0'));
    ui->secondsLcdNumber->display(seconds);
    ui->minutesLcdNumber->display(minutes);
}

void MainWindow::clear_timer()
{
    timer_seconds_ = 0;
    ui->secondsLcdNumber->display(0);
    ui->minutesLcdNumber->display(0);
}

void MainWindow::stop_timer()
{
    timer->stop();
}
