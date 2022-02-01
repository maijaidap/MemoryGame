/* Class: PlayerNamesDialoq
 * ----------
 * Dialog for asking player names.
 *
 * */

#ifndef PLAYERNAMESDIALOG_HH
#define PLAYERNAMESDIALOG_HH

#include <QDialog>

namespace Ui {
class PlayerNamesDialog;
}

class PlayerNamesDialog : public QDialog
{
    Q_OBJECT

public:
    PlayerNamesDialog(const PlayerNamesDialog& init_value) = delete;
    PlayerNamesDialog& operator=(const PlayerNamesDialog& add_value) = delete;

    // Constructor: Creates a new dialog window for asking player names.
    explicit PlayerNamesDialog(QWidget *parent = nullptr, int number_of_players = 0);
    ~PlayerNamesDialog();

    std::vector<QString> get_player_names() const;

private slots:
    // Administrating the situation when startPushButton is being pushed.
    // When pushed the game continues to the main window,
	// and the gameboard is created according to the defined settings.
    void on_startPushButton_clicked();


private:
    Ui::PlayerNamesDialog *ui = nullptr;
    int number_of_players_    = 0;
};

#endif // PLAYERNAMESDIALOG_HH
