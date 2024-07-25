
#include "metal_graphics_system.h"
#include <iostream>
#include <Metal/Metal.h>
#include <QuartzCore/CAMetalLayer.h>

namespace xe {
namespace ui {
namespace metal {

MetalGraphicsSystem::MetalGraphicsSystem() : device_(nullptr), command_queue_(nullptr) {
    std::cout << "MetalGraphicsSystem created" << std::endl;
}

MetalGraphicsSystem::~MetalGraphicsSystem() {
    Shutdown();
    std::cout << "MetalGraphicsSystem destroyed" << std::endl;
}

bool MetalGraphicsSystem::Initialize() {
    std::cout << "MetalGraphicsSystem initialized" << std::endl;

    // Create Metal device
    device_ = MTLCreateSystemDefaultDevice();
    if (!device_) {
        std::cerr << "Failed to create Metal device" << std::endl;
        return false;
    }

    // Create command queue
    command_queue_ = [device_ newCommandQueue];
    if (!command_queue_) {
        std::cerr << "Failed to create command queue" << std::endl;
        return false;
    }

    return true;
}

void MetalGraphicsSystem::Shutdown() {
    command_queue_ = nil;
    device_ = nil;
    std::cout << "MetalGraphicsSystem shut down" << std::endl;
}

}  // namespace metal
}  // namespace ui
}  // namespace xe
