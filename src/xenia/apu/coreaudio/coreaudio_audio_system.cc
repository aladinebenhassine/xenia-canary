
#include "coreaudio_audio_system.h"
#include "coreaudio_audio_driver.h"
#include <iostream>

namespace xe {
namespace apu {
namespace coreaudio {

CoreAudioSystem::CoreAudioSystem() {
    driver_ = new CoreAudioDriver();
}

CoreAudioSystem::~CoreAudioSystem() {
    delete driver_;
}

bool CoreAudioSystem::Initialize() {
    std::cout << "CoreAudioSystem initialized" << std::endl;
    return driver_->Initialize();
}

void CoreAudioSystem::Shutdown() {
    std::cout << "CoreAudioSystem shut down" << std::endl;
    driver_->Shutdown();
}

}  // namespace coreaudio
}  // namespace apu
}  // namespace xe
