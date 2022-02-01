#include "player.hh"
#include "card.hh"
#include <iostream>


Player::Player(const QString& name):
    name_(name)
{
}

Player::~Player()
{
}

QString Player::get_name() const
{
    return name_;
}

int Player::get_points() const
{
    int points = cards_collected_ / 2;
    return points;
}

unsigned int Player::number_of_pairs() const
{
    int pairs = cards_collected_ / 2;
    return pairs;
}

void Player::add_points()
{
    cards_collected_ += 2;
}
