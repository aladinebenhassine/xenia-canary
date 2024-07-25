
#include "coreaudio_audio_driver.h"
#include <iostream>
#include <CoreAudio/CoreAudio.h>

namespace xe {
namespace apu {
namespace coreaudio {

CoreAudioDriver::CoreAudioDriver() : audio_unit_(nullptr) {
    std::cout << "CoreAudioDriver created" << std::endl;
}

CoreAudioDriver::~CoreAudioDriver() {
    Shutdown();
    std::cout << "CoreAudioDriver destroyed" << std::endl;
}

bool CoreAudioDriver::Initialize() {
    std::cout << "CoreAudioDriver initialized" << std::endl;

    // Describe the output audio unit
    AudioComponentDescription desc = {0};
    desc.componentType = kAudioUnitType_Output;
    desc.componentSubType = kAudioUnitSubType_DefaultOutput;
    desc.componentManufacturer = kAudioUnitManufacturer_Apple;

    // Get the default output audio unit
    AudioComponent comp = AudioComponentFindNext(NULL, &desc);
    if (comp == NULL) {
        std::cerr << "Failed to find default output audio unit" << std::endl;
        return false;
    }

    // Create the audio unit
    OSStatus status = AudioComponentInstanceNew(comp, &audio_unit_);
    if (status != noErr) {
        std::cerr << "Failed to create audio unit" << std::endl;
        return false;
    }

    // Initialize the audio unit
    status = AudioUnitInitialize(audio_unit_);
    if (status != noErr) {
        std::cerr << "Failed to initialize audio unit" << std::endl;
        return false;
    }

    return true;
}

void CoreAudioDriver::Shutdown() {
    if (audio_unit_) {
        AudioUnitUninitialize(audio_unit_);
        AudioComponentInstanceDispose(audio_unit_);
        audio_unit_ = nullptr;
    }
    std::cout << "CoreAudioDriver shut down" << std::endl;
}

}  // namespace coreaudio
}  // namespace apu
}  // namespace xe
