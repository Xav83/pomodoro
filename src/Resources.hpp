#pragma once

#include <filesystem>

namespace pomodoro
{
#ifdef _WIN32
std::filesystem::path start_break_sound_file("C:/ProgramData/pomodoro/PowerDown1.ogg");
std::filesystem::path start_work_sound_file("C:/ProgramData/pomodoro/PowerUp1.ogg");
#else
std::filesystem::path start_break_sound_file("~/Library/Application Support/Pomodoro/PowerDown1.ogg");
std::filesystem::path start_work_sound_file("~/Library/Application Support/Pomodoro/PowerUp1.ogg");
#endif
}
