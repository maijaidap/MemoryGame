/* Class: Card
 * ----------
 * Describes one card in the memory game.
 *
 * */

#ifndef CARD_HH
#define CARD_HH

#include <QPushButton>

enum Visibility_type {OPEN, HIDDEN, EMPTY};

class Card
{
public:
    // Forbidding the use of default constructor.
    Card(const Card& init_value) = delete;
    Card& operator=(const Card& add_value) = delete;

    // Constructor: Creates an empty card.
    Card();
    ~Card();

    // COnstructor: Creates a hidden card.
    Card(const int card_number);

    // Setters and getters.
    void set_card_number(const int card_number);
    void set_visibility(const Visibility_type visibility);
    void set_push_button(QPushButton* push_button);
    int get_card_number() const;
    Visibility_type get_visibility() const;
    QPushButton* get_push_button() const;

    // Turns the card. Changing the visibility of the card. 
    void turn();

    // Removes a card from the gameboard: Changes visibility into empty. 
    void remove_from_game_board();

    // Hides an individual card.
    void hide_card();

private:
    int card_number_            = 0;
    Visibility_type visibility_ = HIDDEN;
    QPushButton* push_button_   = nullptr;
};

#endif // CARD_HH
