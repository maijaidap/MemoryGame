/* Class: GameBoard
 * ----------
 * Class for administrating the gameboard shown in the main window.
 *
 * */

#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include "player.hh"
#include "card.hh"
#include "mainwindow.hh"

#include <QString>
#include <QTimer>
#include <vector>

class MainWindow;

class GameBoard
{
public:
    // Forbidding the use of default constructor.
    GameBoard(const GameBoard& init_value) = delete;
    GameBoard& operator=(const GameBoard& add_value) = delete;

    // Constructor: Creates a new gameboard.
    GameBoard();
    ~GameBoard();

    // Setters and getters.
    void set_number_of_cards(int number_of_cards);
    void set_number_of_players(int number_of_players);
    void set_players(std::vector<QString> player_names_);
    void set_main_window(MainWindow *main_window);

    int get_number_of_cards() const;
    int get_number_of_players() const;
    std::vector<QString> get_player_names() const;
    std::vector<Card*> get_cards() const;
    Player* get_current_player() const;
    Player* get_winner() const;
    int get_current_player_index() const;

    // Clears information about gameboard's cards.
    void clear_cards();

    // Shuffles cards to the gameboard.
    void shuffle_cards();

    // Adds a new card to the cards_ datastructure.
    void add_card(Card* card);

    // Showhs two cards at a time on the gameboard.
    void show_card(int card_index);

    // Check whether a pair is found. 
    void check_cards(int card1, int card2);

    // Hides turned cards. 
    void hide_cards();

    // Check if all the pairs are found. 
    void is_game_over();

    // Changes player's turn and changes current_player_index_ -value.
    void change_turn();

    // Adds points to a specific player.
    void add_points_to_player();

    // Check if the game ends with a tie. 
    bool is_game_tie();

private:
    // Attributes for storing information about players.
    std::vector<QString> player_names_  = {};
    std::vector<Player*> players_       = {};
    int current_player_index_           = 0;

    // Attributes for storing information about cards. 
    int number_of_cards_        = 0;
    int number_of_players_      = 0;
    std::vector<Card*> cards_   = {};
    int visible_cards_          = 0;

    std::vector<int> pushed_buttons_ = {};
    MainWindow* main_window_         = nullptr;
};

#endif // GAMEBOARD_HH
