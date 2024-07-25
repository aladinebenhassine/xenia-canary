
#ifndef XENIA_APU_COREAUDIO_COREAUDIO_AUDIO_DRIVER_H_
#define XENIA_APU_COREAUDIO_COREAUDIO_AUDIO_DRIVER_H_

#include <AudioUnit/AudioUnit.h>

namespace xe {
namespace apu {
namespace coreaudio {

class CoreAudioDriver {
public:
    CoreAudioDriver();
    ~CoreAudioDriver();

    bool Initialize();
    void Shutdown();

private:
    AudioUnit audio_unit_;
};

}  // namespace coreaudio
}  // namespace apu
}  // namespace xe

#endif  // XENIA_APU_COREAUDIO_COREAUDIO_AUDIO_DRIVER_H_
