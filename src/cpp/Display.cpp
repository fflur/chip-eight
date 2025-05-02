#include <Display.hpp>

//---MonochromeDisplay---//

MonochromeDisplay::MonochromeDisplay(std::string win_title) {
    int exit_code;

    this->window = SDL_CreateWindow(
        win_title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        400,
        SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_ALLOW_HIGHDPI
    );

    if (!this->window) throw InitializationException(SDL_GetError());

    this->renderer = SDL_CreateRenderer(
        this->window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if (!this->renderer) throw InitializationException(SDL_GetError());

    exit_code = SDL_GetRendererOutputSize(
        this->renderer,
        &this->win_w,
        &this->win_h
    );

    if (exit_code < 0) throw InitializationException(SDL_GetError());

    this->each_px_w = this->win_w / this->chip_eight_w;
    this->each_px_h = this->win_h / this->chip_eight_h;

    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    for (u8 i = 0; i < this->chip_eight_h; i++)
        for (u8 j = 0; j < this->chip_eight_w; j++) {
            SDL_Rect pixel;
            pixel.w = this->each_px_w;
            pixel.h = this->each_px_h;
            pixel.x = this->each_px_w * j;
            pixel.y = this->each_px_h * i;
            SDL_RenderFillRect(this->renderer, &pixel);
            this->frame[i][j] = pixel;
        }
}

MonochromeDisplay::~MonochromeDisplay() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    window, renderer = nullptr;
}

void MonochromeDisplay::renderSprite(
    u8* ptr_sprite,
    u8 array_len,
    u8 x_coord,
    u8 y_coord
) {
    this->has_px_erased = false;
    u8 times = 7;
    u8 sprite_bits[array_len][8];

    for (u8 i = 0; i < array_len; i++) {
        for (u8 j = 0; j < 8; j++) {
            u8 extracted_bit = *(ptr_sprite + i) & (0b1 << times);
            sprite_bits[i][j] = extracted_bit >> times;
            times -= 1;
        }

        times = 7;
    }

    //Xor'ing to current screen. Wrapping around the screen.
    for (u8 i = 0; i < array_len; i++)
        for (u8 j = 0; j < 8; j++) {
            u8 x =
                i + y_coord >= this->chip_eight_h ?
                    (i + y_coord) - this->chip_eight_h : i + y_coord
            ;

            u8 y =
                j + x_coord >= this->chip_eight_w ?
                (j + x_coord) - this->chip_eight_w : j + x_coord
            ;

            u8 bin_fr_curr_state = this->binary_frame[x][y];
            this->binary_frame[x][y] ^= sprite_bits[i][j];

            if (this->binary_frame[x][y] < bin_fr_curr_state)
                this->has_px_erased = true;
        }

    ptr_sprite = nullptr;
    this->renderToScreen();
}

// Maps 0 to black and 1 to white and presents on screen.
void MonochromeDisplay::renderToScreen() {
    for (u8 i = 0; i < this->chip_eight_h; i++)
        for (u8 j = 0; j < this->chip_eight_w; j++) {
            if (this->binary_frame[i][j] == 0)
                SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
            else
                SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);

            SDL_RenderFillRect(this->renderer, &this->frame[i][j]);
        }

    SDL_RenderPresent(this->renderer);
}

bool MonochromeDisplay::hasPixelErased() {
    return this->has_px_erased;
}

void MonochromeDisplay::clearScreen() {
    for (u8 i = 0; i < this->chip_eight_h; i++)
        for (u8 j = 0; j < this->chip_eight_w; j++)
            this->binary_frame[i][j] = 0b0;

    this->renderToScreen();
}

//---EoF---//
