#pragma once
#include <iostream>
#include <sdl_types.hpp>
#include <instruction_set.hpp>

class MonochromeDisplay : public Display {
    private:
        int win_w;
        int win_h;
        float each_px_w; // Pixel width for this display.
        float each_px_h; // Pixel height for this display.
        const float chip_eight_w = 64.0f;
        const float chip_eight_h = 32.0f;
        bool has_px_erased = false;
        u8 binary_frame[32][64];
        Rectangle frame[32][64]; // 1 frame.
        Window* window;
        Renderer* renderer;

        void renderToScreen();

    public:
        MonochromeDisplay(std::string);
        ~MonochromeDisplay();
        bool hasPixelErased() override;
        void renderSprite(std::vector<u8>&, u8, u8) override;
        void clearScreen() override;
};
