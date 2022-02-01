#include "gameboard.hh"
#include "card.hh"
#include "player.hh"
#include <vector>
#include <QString>
#include <QWidget>
#include <QTimer>
#include <QHBoxLayout>
#include <QPushButton>
#include <iostream>
#include <random>
#include <algorithm>

// Delay as milliseconds.
const int DELAY = 1100;

GameBoard::GameBoard()
{
}

GameBoard::~GameBoard()
{
    for (std::string::size_type i = 0; i < players_.size(); ++i)
    {
        if (players_.at(i))
        {
            delete players_.at(i);
            players_.at(i) = nullptr;
        }
    }

    for (std::string::size_type i = 0; i < cards_.size(); ++i)
    {
        if (cards_.at(i))
        {
            delete cards_.at(i);
            cards_.at(i) = nullptr;
        }
    }
}

void GameBoard::set_number_of_cards(int number_of_cards)
{
    number_of_cards_ = number_of_cards;
}

void GameBoard::set_number_of_players(int number_of_players)
{
    number_of_players_ = number_of_players;
}

void GameBoard::set_players(std::vector<QString> player_names)
{
    // Initializing player's index into a default state. 
    current_player_index_ = 0;

    main_window_->clear_points();

    // Clear all the information about the previous players.
    for (std::string::size_type i = 0; i < players_.size(); ++i)
    {
        if (players_.at(i))
        {
            delete players_.at(i);
            players_.at(i) = nullptr;
        }
    }

    // Empty vector containing players.
    players_.clear();

    // Setting player names. 
    player_names_ = player_names;
    Player* new_player = nullptr;

    // Creating new player objects. 
    for (int i = 0; i < number_of_players_; ++i)
    {
        new_player = new Player(player_names_.at(i));
        players_.push_back(new_player);
    }
}

void GameBoard::set_main_window(MainWindow* main_window)
{
    main_window_ = main_window;
}

int GameBoard::get_number_of_cards() const
{
    return number_of_cards_;
}

int GameBoard::get_number_of_players() const
{
    return number_of_players_;
}

std::vector<QString> GameBoard::get_player_names() const
{
    return player_names_;
}

void GameBoard::add_card(Card* card)
{
    cards_.push_back(card);
}

void GameBoard::show_card(int card_index)
{
    visible_cards_ += 1;

    if (visible_cards_ <= 2)
    {
        // Check whether a card is already turned.
        if (std::count(pushed_buttons_.begin(), pushed_buttons_.end(), card_index))
        {
            visible_cards_ -= 1;
        }
        else
        {
            // Saving turned cards.
            pushed_buttons_.push_back(card_index);
            // Turns the chosen card. 
            cards_.at(card_index)->turn();

            if (visible_cards_ == 2)
            {
                int card1 = pushed_buttons_.at(0);
                int card2 = pushed_buttons_.at(1);
                // Check whether a pair is found. 
                check_cards(card1, card2);
                // Turn cards after a certain timeframe. 
                QTimer::singleShot(DELAY, [=]() {hide_cards();});
            }
        }
    }
}

void GameBoard::check_cards(int card1, int card2)
{
    // Check whether cards are the same. 
    if (cards_.at(card1)->get_card_number() ==
        cards_.at(card2)->get_card_number())
    {
        // Inactivating card, 
        // so they show as inactive on the gameboard.
        cards_.at(card1)->set_visibility(EMPTY);
        cards_.at(card2)->set_visibility(EMPTY);
        cards_.at(card1)->get_push_button()->setEnabled(false);
        cards_.at(card2)->get_push_button()->setEnabled(false);

        add_points_to_player();

        is_game_over();
    }
    else
    {
        // Changes player's turn. 
        change_turn();
        main_window_->update_check_box_status();
    }
}

void GameBoard::hide_cards()
{
    for (std::string::size_type i = 0; i < cards_.size(); ++i)
    {
        cards_.at(i)->hide_card();
    }
    // Initializing pushed buttons empty.
    visible_cards_ = 0;
    pushed_buttons_ = {};
}

void GameBoard::is_game_over()
{
    // Variable for storing information about turnable cards. 
    int cards_enabled = 0;

    for (std::string::size_type i = 0; i < cards_.size(); ++i)
    {
        if (cards_.at(i)->get_push_button()->isEnabled())
        {
              cards_enabled += 1;
        }
    }

    // All the cards have been turned.
    if (cards_enabled == 0)
    {
        if (is_game_tie())
        {
            main_window_->stop_timer();
            main_window_->print_text("Peli päättyi tasapeliin!");
        }
        else
        {
            main_window_->stop_timer();
            std::string winner = get_winner()->get_name().toStdString();
            main_window_->print_text("Peli on päättynyt! " + winner + " voitti pelin!");
        }
    }
}

void GameBoard::change_turn()
{
    current_player_index_ += 1;

    // Examine whether player's turns have been used.
    if (current_player_index_ == number_of_players_)
    {
        current_player_index_ = 0;
    }
}

void GameBoard::add_points_to_player()
{
    get_current_player()->add_points();
    // Updating points to the gameboard..
    main_window_->update_points(get_current_player()->get_points());
}

bool GameBoard::is_game_tie()
{
    int winners_points = get_winner()->get_points();

    int same_points = 0;

    for (std::string::size_type i = 0; i < players_.size(); ++i)
    {
        if (winners_points == players_.at(i)->get_points())
        {
            same_points += 1;
        }
    }

    if (same_points > 1)
    {
        return true;
    }
    return false;
}


Player* GameBoard::get_winner() const
{
    // Initializing temp variables with first player's information. 
    Player* winner = players_.at(0);
    int most_points = players_.at(0)->get_points();

    for (std::string::size_type i = 1; i < players_.size(); ++i)
    {
        if (most_points < players_.at(i)->get_points())
        {
            winner = players_.at(i);
            most_points = players_.at(i)->get_points();
        }
    }

    return winner;
}

int GameBoard::get_current_player_index() const
{
    return current_player_index_;
}

std::vector<Card*> GameBoard::get_cards() const
{
    return cards_;
}

Player *GameBoard::get_current_player() const
{
    return players_.at(current_player_index_);
}

void GameBoard::clear_cards()
{
    for (std::string::size_type i = 0; i < cards_.size(); ++i)
    {
        if (cards_.at(i))
        {
            delete cards_.at(i);
            cards_.at(i) = nullptr;
        }
    }

    cards_.clear();
}

void GameBoard::shuffle_cards()
{
    // Initializes random generator with current time. 
    std::default_random_engine gen(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distr(1, get_number_of_cards()/2);
    distr(gen);

    // Temp vector for storing numbers picked in random order. 
    std::vector<int> picture_numbers = {};

    // Generating a random number for all the cards. 
    for (std::string::size_type i = 0; i < get_cards().size(); ++i)
    {
        int random_num = distr(gen);

        // Check there isn't two of the same number. 
        while (std::count (picture_numbers.begin(), picture_numbers.end(),
                           random_num) >= 2)
        {
            random_num = distr(gen);
        }

        picture_numbers.push_back(random_num);
    }

    // Set a number for every card. 
    for (std::string::size_type i = 0; i < picture_numbers.size(); ++i)
    {
        cards_.at(i)->set_card_number(picture_numbers.at(i));
    }
}
