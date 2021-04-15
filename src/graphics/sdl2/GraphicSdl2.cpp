/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** Sdl2
*/

#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include <thread>
#include "Sdl2.hpp"
#include <SDL2/SDL_ttf.h>
#include <unordered_map>
#include "../../shared/Errors.hpp"

extern "C" std::unique_ptr<sdl2::GraphicSdl2> entry_point()
{
    return std::make_unique<sdl2::GraphicSdl2>();
}

sdl2::GraphicSdl2::Renderer sdl2::GraphicSdl2::renderer = nullptr;

static const std::unordered_map<int, char> sdl2ToArcadeKey{
    {SDLK_KP_DIVIDE, '/'},
    {SDLK_KP_MULTIPLY, '*'},
    {SDLK_KP_MINUS, '-'},
    {SDLK_KP_PLUS, '+'},
    {SDLK_KP_ENTER, '\n'},
    {SDLK_KP_EQUALS, '='},
    {SDLK_POWER, '*'},
    {SDLK_KP_0, '0'},
    {SDLK_KP_1, '1'},
    {SDLK_KP_2, '2'},
    {SDLK_KP_3, '3'},
    {SDLK_KP_4, '4'},
    {SDLK_KP_5, '5'},
    {SDLK_KP_6, '6'},
    {SDLK_KP_7, '7'},
    {SDLK_KP_8, '8'},
    {SDLK_KP_9, '9'},
};

static const std::unordered_map<int, arcade::data::KeyCode> sdl2ToArcadeKeyCode{
    {SDLK_RETURN, arcade::data::KeyCode::ENTER},
    {SDLK_RETURN2, arcade::data::KeyCode::ENTER},
    {SDLK_BACKSPACE, arcade::data::KeyCode::BACKSPACE},
    {SDLK_ESCAPE, arcade::data::KeyCode::ESCAPE},
    {SDLK_SPACE, arcade::data::KeyCode::SPACE},
    {SDLK_DOWN, arcade::data::KeyCode::DOWN},
    {SDLK_UP, arcade::data::KeyCode::UP},
    {SDLK_LEFT, arcade::data::KeyCode::LEFT},
    {SDLK_RIGHT, arcade::data::KeyCode::RIGHT},

};

static const std::unordered_map<int, arcade::data::MouseBtn> sdl2ToArcadeMouseBtn{
    {SDL_BUTTON_LEFT, arcade::data::MouseBtn::BTN_1},
    {SDL_BUTTON_MIDDLE, arcade::data::MouseBtn::BTN_2},
    {SDL_BUTTON_RIGHT, arcade::data::MouseBtn::BTN_3},
};

sdl2::GraphicSdl2::GraphicSdl2()
{
}

sdl2::GraphicSdl2::~GraphicSdl2()
{
    if (!this->windowIsOpen) {
        this->windowIsOpen = false;
        this->window.reset();
        sdl2::GraphicSdl2::renderer.reset();
        TTF_Quit();
        SDL_Quit();
    }
}

int sdl2::GraphicSdl2::availableOptions() const
{
    return SET_CHARACTER_SIZE | MOUSE_MOVE | SETTING_FONTS;
}

bool sdl2::GraphicSdl2::isOpen() const
{
    return this->windowIsOpen;
}

void sdl2::GraphicSdl2::init(const std::string &title, const unsigned int limit)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0 || TTF_Init() != 0 || SDL_GetError()) {
        throw arcade::errors::Error("SDL init error or TTF init");
    }
    this->window = create_window(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, 1920, 1080,  SDL_WINDOW_RESIZABLE));
    if (!this->window || SDL_GetError()) {
        throw arcade::errors::Error("SDL create window");
    }
    sdl2::GraphicSdl2::renderer = create_renderer(
        SDL_CreateRenderer(this->window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
    if (!sdl2::GraphicSdl2::renderer || SDL_GetError()) {
        throw arcade::errors::Error("SDL create renderer");
    }
    this->windowIsOpen = true;
    this->frameLimit = limit;
    this->restartClock();
}

void sdl2::GraphicSdl2::display()
{
    SDL_RenderPresent(sdl2::GraphicSdl2::renderer.get());
    this->events.clear();
    double waiting = ((1.0f / this->frameLimit) * 1000) - (getFrameDuration() * 1000);
    if (waiting > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(waiting)));
    }
    this->lastFrameTime = getFrameDuration();
    restartClock();
}

void sdl2::GraphicSdl2::stop()
{
    this->windowIsOpen = false;
    this->window.reset();
    sdl2::GraphicSdl2::renderer.reset();
    SDL_Quit();
    TTF_Quit();
}

void sdl2::GraphicSdl2::clearWindow()
{
    if (SDL_RenderClear(sdl2::GraphicSdl2::renderer.get()) != 0) {
        throw arcade::errors::Error("SDL clear renderer");
    }
}

void sdl2::GraphicSdl2::restartClock()
{
    this->timePoint = std::chrono::high_resolution_clock::now();
}

double sdl2::GraphicSdl2::getDeltaTime() const
{
    return this->lastFrameTime;
}

double sdl2::GraphicSdl2::getFrameDuration() const
{
    return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1>>>(
        std::chrono::high_resolution_clock::now() - this->timePoint)
        .count();
}

arcade::data::Vector2u sdl2::GraphicSdl2::getWindowSize() const
{
    int w = 0;
    int h = 0;
    SDL_GetWindowSize(&*this->window, &w, &h);
    return arcade::data::Vector2u{static_cast<unsigned int>(w), static_cast<unsigned int>(h)};
}

std::vector<arcade::data::Event> sdl2::GraphicSdl2::getEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            this->events.emplace_back(arcade::data::EventType::WINDOW_CLOSED,
                static_cast<arcade::data::EventType>(event.key.type));
        }
        if (event.type == SDL_KEYDOWN) {
            if (sdl2ToArcadeKey.find(event.key.keysym.sym) != sdl2ToArcadeKey.end()) {
                this->events.emplace_back(arcade::data::EventType::KEY_PRESSED,
                    sdl2ToArcadeKey.at(event.key.keysym.sym));
            } else if (sdl2ToArcadeKeyCode.find(event.key.keysym.sym)
                != sdl2ToArcadeKeyCode.end()) {
                this->events.emplace_back(arcade::data::EventType::KEY_PRESSED,
                    sdl2ToArcadeKeyCode.at(event.key.keysym.sym));
            } else if (event.key.keysym.sym >= 'a' && event.key.keysym.sym <= 'z') {
                int maj = 0;
                if (event.key.keysym.mod & KMOD_SHIFT) {
                    maj = 32;
                }
                this->events.emplace_back(
                    arcade::data::EventType::KEY_PRESSED, event.key.keysym.sym - maj);
            }
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (sdl2ToArcadeMouseBtn.find(event.button.button)
                != sdl2ToArcadeMouseBtn.end()) {
                this->events.emplace_back(arcade::data::EventType::MOUSE_PRESSED,
                    static_cast<arcade::data::MouseBtn>(
                        sdl2ToArcadeMouseBtn.at(event.button.button)),
                    event.button.x, event.button.y);
            }
        }
    }
    return this->events;
}

void sdl2::GraphicSdl2::draw(std::unique_ptr<arcade::displayer::IText> &text)
{
    reinterpret_cast<std::unique_ptr<TextSdl2> &>(text)->drawText();
}

void sdl2::GraphicSdl2::draw(std::unique_ptr<arcade::displayer::ISprite> &sprite)
{
    reinterpret_cast<std::unique_ptr<SpriteSdl2> &>(sprite)->drawSprite();
}

std::unique_ptr<arcade::displayer::IText> sdl2::GraphicSdl2::createText(const std::string &text) const
{
    return std::make_unique<TextSdl2>(text);
}

std::unique_ptr<arcade::displayer::IText> sdl2::GraphicSdl2::createText() const
{
    return std::make_unique<TextSdl2>();
}

std::unique_ptr<arcade::displayer::ISprite> sdl2::GraphicSdl2::createSprite() const
{
    return std::make_unique<SpriteSdl2>();
}

std::unique_ptr<arcade::displayer::ISprite> sdl2::GraphicSdl2::createSprite(
    const std::string &spritePath, const std::vector<std::string> &asciiSprite,
    arcade::data::Vector2f scale) const
{
    return std::make_unique<SpriteSdl2>(spritePath, asciiSprite, scale);
}

double sdl2::GraphicSdl2::scaleMoveX(double time) const
{
    if (!time) {
        return 0;
    }
    return (getWindowSize().x / time) / (1.0f / getDeltaTime());
}

double sdl2::GraphicSdl2::scaleMoveY(double time) const
{
    if (!time) {
        return 0;
    }
    return (getWindowSize().y / time) / (1.0f / getDeltaTime());
}