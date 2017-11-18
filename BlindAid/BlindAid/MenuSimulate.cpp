#include <iostream>
#include <conio.h>

#include "MenuSimulate.h"

using namespace std;
using namespace cv;

#define PATH "C:\\Projects\\BlindAid\\TestData\\"

SimulateMenu::SimulateMenu(Core::Core *core, Core::Parameters *params, Core::Data *data)
{
  _core = core;
  _params = params;
  _results = data;
}

void SimulateMenu::operator()()
{
  ShowMenu();
}

void SimulateMenu::ShowMenu()
{
  char in;
  system("cls");

  do {
    system("cls");

    cout << "\
+========= Simulation ========+\n\
| 1: Load Photo               |\n\
| 2: Load Video               |\n\
| d: Depth Obstacle Detector  |\n\
| t: Traffic Light Detector   |\n\
| s: Stop Sign Detector       |\n\
| v: Video Simulation         |\n\
+=============================+\n";

    in = _getch();

    switch (in)
    {
    case '1':
      LoadFile(Capture::Simulate::Parameters::MediaType::Photo, "depthMap.png");
      break;
    case '2':
      LoadFile(Capture::Simulate::Parameters::MediaType::Video, "depthMap.png");
      break;
    case 'd':
      TestPhoto("TrafficLight\\tlight", "depthMap.png", 1);
      break;
    case 't':
      TestPhoto("TrafficLight\\tlight", "depthMap.png", 15);
      break;
    case 's':
      TestPhoto("StopSign\\stop", "depthMap.png", 8);
      break;
    case 'v':
      TestVideo("TrafficLight\\tlight", "depthMap.png", 4);
      break;
    }
  } while (in != 'q' && in != 'Q');

}

void SimulateMenu::Process()
{
  if (_core == NULL)
    _core = new Core::Core(_params, NULL, _results);

  (*_core)();
  waitKey();
}

void SimulateMenu::LoadFile(Capture::Simulate::Parameters::MediaType mode, string depthPath)
{
  string name;
  cout << "Enter file name (default directory): ";
  cin >> name;

  _params->GetCaptureParams()->SetMode(SwitchableParameters::Mode::Simulate);
  _params->GetControlParams()->SetMode(SwitchableParameters::Mode::Simulate);
  _params->GetDisplayParams()->SetToggle(SwitchableParameters::Toggle::Enabled);
  _params->GetCaptureParams()->GetSimulateParams()->SetMediaType(mode);
  _params->GetCaptureParams()->GetSimulateParams()->SetDepthSimDataPath(PATH + depthPath);
  _params->GetCaptureParams()->GetSimulateParams()->SetColorSimDataPath(PATH + name);
  _params->GetVisionParams()->GetTrafficLightParams()->SetConsecutiveCount(0);

  Process();
}

void SimulateMenu::TestVideo(string colorVideoPath, string depthPath, int count)
{
  _params->GetCaptureParams()->SetMode(SwitchableParameters::Mode::Simulate);
  _params->GetControlParams()->SetMode(SwitchableParameters::Mode::Simulate);
  _params->GetDisplayParams()->SetToggle(SwitchableParameters::Toggle::Enabled);
  _params->GetCaptureParams()->GetSimulateParams()->SetMediaType(Capture::Simulate::Parameters::MediaType::Video);
  _params->GetCaptureParams()->GetSimulateParams()->SetDepthSimDataPath(PATH + depthPath);

  for (int i = 1; i <= count; ++i)
  {
    _params->GetCaptureParams()->GetSimulateParams()->SetColorSimDataPath(PATH + colorVideoPath + std::to_string(i) + string(".avi"));
    Process();
  }
}

void SimulateMenu::TestPhoto(string colorPath, string depthPath, int count)
{
  _params->GetCaptureParams()->SetMode(SwitchableParameters::Mode::Simulate);
  _params->GetControlParams()->SetMode(SwitchableParameters::Mode::Simulate);
  _params->GetDisplayParams()->SetToggle(SwitchableParameters::Toggle::Enabled);
  _params->GetCaptureParams()->GetSimulateParams()->SetMediaType(Capture::Simulate::Parameters::MediaType::Photo);
  _params->GetCaptureParams()->GetSimulateParams()->SetDepthSimDataPath(PATH + depthPath);
  _params->GetVisionParams()->GetTrafficLightParams()->SetConsecutiveCount(0);

  for (int i = 1; i <= count; ++i)
  {
    _params->GetCaptureParams()->GetSimulateParams()->SetColorSimDataPath(PATH + colorPath + (count != 0 ? std::to_string(i) : "") + string(".jpg"));
    Process();
  }

  destroyAllWindows();
}