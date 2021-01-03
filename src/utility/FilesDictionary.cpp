#include "FilesDictionary.hpp"

#ifdef _WIN32
std::filesystem::path pomodoro::files::sounds::start_break =
    "C:/ProgramData/pomodoro/PowerDown1.ogg";
std::filesystem::path pomodoro::files::sounds::start_work =
    "C:/ProgramData/pomodoro/PowerUp1.ogg";
std::filesystem::path pomodoro::files::configuration =
    "C:/ProgramData/pomodoro/save.cfg";
#elif __APPLE__
std::filesystem::path pomodoro::files::sounds::start_break =
    "~/Library/Application Support/Pomodoro/PowerDown1.ogg";
std::filesystem::path pomodoro::files::sounds::start_work =
    "~/Library/Application Support/Pomodoro/PowerUp1.ogg";
std::filesystem::path pomodoro::files::configuration =
    "~/Library/Application Support/Pomodoro/save.cfg";
#else
std::filesystem::path pomodoro::files::sounds::start_break =
    "~/.pomodoro/PowerDown1.ogg";
std::filesystem::path pomodoro::files::sounds::start_work =
    "~/.pomodoro/PowerUp1.ogg";
std::filesystem::path pomodoro::files::configuration = "~/.pomodoro/save.cfg";
#endif
