/* Class: NewGameDialog
 * ----------
 * Dialog for asking game settings.
 *
 * */

#ifndef NEWGAMEDIALOG_HH
#define NEWGAMEDIALOG_HH

#include <QDialog>

namespace Ui {
class NewGameDialog;
}

class NewGameDialog : public QDialog
{
    Q_OBJECT

public:
    NewGameDialog(const NewGameDialog& init_value) = delete;
    NewGameDialog& operator=(const NewGameDialog& add_value) = delete;

    // Constructor: Creates a new dialog window for asking game settings.
    explicit NewGameDialog(QWidget *parent = nullptr);
    ~NewGameDialog();

    int get_players_amount() const;
    int get_difficulty_level() const;

private slots:
    void on_nextPushButton_clicked();

private:
    Ui::NewGameDialog *ui = nullptr;
};

#endif // NEWGAMEDIALOG_HH
