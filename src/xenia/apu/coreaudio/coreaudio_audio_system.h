
#ifndef XENIA_APU_COREAUDIO_COREAUDIO_AUDIO_SYSTEM_H_
#define XENIA_APU_COREAUDIO_COREAUDIO_AUDIO_SYSTEM_H_

namespace xe {
namespace apu {
namespace coreaudio {

class CoreAudioDriver;

class CoreAudioSystem {
public:
    CoreAudioSystem();
    ~CoreAudioSystem();

    bool Initialize();
    void Shutdown();

private:
    CoreAudioDriver* driver_;
};

}  // namespace coreaudio
}  // namespace apu
}  // namespace xe

#endif  // XENIA_APU_COREAUDIO_COREAUDIO_AUDIO_SYSTEM_H_
