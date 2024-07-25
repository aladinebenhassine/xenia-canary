
#ifndef XENIA_UI_METAL_METAL_GRAPHICS_SYSTEM_H_
#define XENIA_UI_METAL_METAL_GRAPHICS_SYSTEM_H_

#import <Metal/Metal.h>

namespace xe {
namespace ui {
namespace metal {

class MetalGraphicsSystem {
public:
    MetalGraphicsSystem();
    ~MetalGraphicsSystem();

    bool Initialize();
    void Shutdown();

private:
    id<MTLDevice> device_;
    id<MTLCommandQueue> command_queue_;
};

}  // namespace metal
}  // namespace ui
}  // namespace xe

#endif  // XENIA_UI_METAL_METAL_GRAPHICS_SYSTEM_H_
