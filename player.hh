/* Class: Player
 * ----------
 * Describes one player.
 * */

#ifndef PLAYER_HH
#define PLAYER_HH

#include "card.hh"

#include <string>
#include <QString>

class Player
{

public:
    Player(const Player& init_value) = delete;
    Player& operator=(const Player& add_value) = delete;

    // Contructor: Creates a new player with a given name. 
    Player(const QString& name);
    ~Player();

    QString get_name() const;
    int get_points() const;

    unsigned int number_of_pairs() const;

    void add_points();

private:
    QString name_        = "";
    int cards_collected_ = 0;
};


#endif // PLAYER_HH
