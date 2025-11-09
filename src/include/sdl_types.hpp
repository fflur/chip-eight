#pragma once
#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>
#include <chip_types.hpp>

// Type aliases for SDL types to simplify usage in the project.
using Window = SDL_Window;
using Renderer = SDL_Renderer;
using Texture = SDL_Texture;
using Surface = SDL_Surface;
using Rectangle = SDL_Rect;
using Color = SDL_Color;
using Event = SDL_Event;
using KeySymbol = SDL_Keysym;
using Scancode = SDL_Scancode;
using KeyboardEvent = SDL_KeyboardEvent;
using KeyMap = std::unordered_map<SDL_Scancode, u16>;