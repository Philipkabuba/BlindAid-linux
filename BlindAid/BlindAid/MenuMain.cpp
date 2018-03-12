#include "MenuMain.h"

using namespace std;
using namespace cv;

MainMenu::MainMenu(Core::Core *core, Core::Parameters *params, Core::Data *data, Logger *logger, Configuration *config) : Menu(core, params, data, logger, config),
  _realtime(core, params, data, logger, config),
  _simulate(core, params, data, logger, config)
{

}

void MainMenu::ShowMenu()
{
  char in;
  cout << "Welcome to BlindAid!\n\n";

  do {
    cout << "\
+===== Main Menu =====+\n\
| 1: Realtime         |\n\
| 2: Simulate         |\n\
| 3: Reload Settings  |\n\
+=====================+\n";

    in = _getch();

    switch (in)
    {
    case '1':
      _realtime.ShowMenu();
      break;
    case '2':
      _simulate.ShowMenu();
      break;
    case '3':
      _config->Configure();
      break;
    }
    system("cls");
  } while (in != 'q' && in != 'Q');
}