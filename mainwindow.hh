/* Class: MainWindow
 * ----------
 * Through main window all the interface components are being administered.
 *
 * */

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "newgamedialog.hh"
#include "playernamesdialog.hh"
#include "gameboard.hh"
#include "card.hh"

#include <QString>
#include <QMainWindow>

class GameBoard;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Forbidding the use of default constructor.
    MainWindow(const MainWindow& init_value) = delete;
    MainWindow& operator=(const MainWindow& add_value) = delete;

    // Constructor: Creates a new main window.
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Starting the game and updating the gameboard.
    void start_game();

    // Creates the right amount of cards to the gameboard. 
    void create_gameboard_buttons();

    // Prints text to the resultTextBrowser -window.
    void print_text(std::string text);

    // Updates the score shown after the player's name.
    void update_points(int points);

    // Updates the radio button indicating player's turn.
    void update_check_box_status();

    // Points are being shown as zeros.
    void clear_points();

    void clear_timer();

    void stop_timer();

private slots:
    // Called when "Uusi peli" has been pushed.
    void on_actionNewGame_triggered();

    // Administrating the situation when a card is pushed.
    void card_clicked(int card_index);

    // Päivittää peliin kuluvaa aikaa.
    void update_time();

private:
    Ui::MainWindow *ui   = nullptr;
    GameBoard *gameboard = nullptr;
    QTimer* timer        = nullptr;
    int timer_seconds_   = 0;

    // Adding player names into a gameboards radiobuttons.
    void show_player_names();

};
#endif // MAINWINDOW_HH
