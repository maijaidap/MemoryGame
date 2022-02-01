#include "card.hh"
#include <iostream>
#include <QPixmap>
#include <QIcon>

Card::Card():
    card_number_(), visibility_(EMPTY)
{
}

Card::~Card()
{
    if (push_button_)
    {
        delete push_button_;
        push_button_ = nullptr;
    }

}

Card::Card(const int card_number):
    card_number_(card_number), visibility_(HIDDEN)
{

}

void Card::set_card_number(const int i)
{
    card_number_ = i;
}

void Card::set_visibility(const Visibility_type visibility)
{
    visibility_ = visibility;
}

void Card::set_push_button(QPushButton* push_button)
{
    push_button_ = push_button;

    // Adding picture while card is hidden.
    QPixmap pixmap(QString::fromStdString("card.png"));
    QIcon ButtonIcon(pixmap);
    push_button_->setIcon(ButtonIcon);
    push_button_->setIconSize(ButtonIcon.availableSizes().first());
}

int Card::get_card_number() const
{
    return card_number_;
}

Visibility_type Card::get_visibility() const
{
    return visibility_;
}

QPushButton* Card::get_push_button() const
{
    return push_button_;
}

void Card::turn()
{
    if(visibility_ == HIDDEN)
    {
        visibility_ = OPEN;
        // Setting a picture on the turned card.
        std::string temp_picture = "cat_" + std::to_string(card_number_) + ".png";
        QPixmap pixmap(QString::fromStdString(temp_picture));
        QIcon ButtonIcon(pixmap);
        push_button_->setIcon(ButtonIcon);
    }
    else if(visibility_ == OPEN)
    {
        visibility_ = HIDDEN;

        // Changing the picture while the card is hidden.
        QPixmap pixmap(QString::fromStdString("card.png"));
        QIcon ButtonIcon(pixmap);
        push_button_->setIcon(ButtonIcon);
    }
}

void Card::remove_from_game_board()
{
    visibility_ = EMPTY;
}

void Card::hide_card()
{
    if (visibility_ == OPEN && push_button_->isEnabled())
    {
        turn();
    }
}
