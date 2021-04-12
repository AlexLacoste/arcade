/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** Sdl2
*/

#ifndef SDL2_HPP_
#define SDL2_HPP_

#include <SDL2/SDL.h>
#include <chrono>
#include <functional>
#include <string>
#include "../../shared/IDisplayModule.hpp"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_ttf.h>

typedef std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)>> Texture;
#define create_texture(__value) (Texture{__value, SDL_DestroyTexture})

namespace sdl2
{
    class TextSdl2 : public arcade::displayer::IText {
      public:
        TextSdl2();
        TextSdl2(const std::string &text);
        ~TextSdl2();
        void setText(const std::string &text) override;
        std::string getText() const override;
        void setPosition(arcade::data::Vector2f pos) override;
        arcade::data::Vector2f getPosition() const override;
        void setFont(const std::string &font) override;
        void setColor(arcade::data::Color color) override;
        arcade::data::Color getColor() const override;
        void setCharacterSize(unsigned int size) override;
        arcade::data::FloatRect getLocalBounds() const override;
        arcade::data::FloatRect getGlobalBounds() const override;
        void setOrigin(arcade::data::Vector2f origin) override;
        arcade::data::Vector2f getOrigin() const override;
        void drawText();

      private:
        typedef std::unique_ptr<TTF_Font, std::function<void(TTF_Font *)>> Font;
#define create_font(__value) (Font{__value, TTF_CloseFont})
        Font font;
        Texture texture;
        SDL_Color color = {.r = 255, .g = 255, .b = 255, .a = 255};
        std::string text;
        arcade::data::Vector2f origin;
        SDL_Rect destRect;
        std::string fontPath;
        int size = 1;
    };

    class SpriteSdl2 : public arcade::displayer::ISprite {
      public:
        SpriteSdl2();
        SpriteSdl2(const std::string &spritePath, const std::vector<std::string> &asciiSprite,
            arcade::data::Vector2f scale);
        ~SpriteSdl2();
        void setSprite(
            const std::string &spritePath, const std::vector<std::string> &asciiSprite) override;
        void setPosition(arcade::data::Vector2f pos) override;
        arcade::data::Vector2f getPosition() const override;
        void move(arcade::data::Vector2f pos) override;
        void move(float x, float y) override;
        void setOrigin(arcade::data::Vector2f origin) override;
        arcade::data::Vector2f getOrigin() const override;
        arcade::data::FloatRect getLocalBounds() const override;
        arcade::data::FloatRect getGlobalBounds() const override;
        void setScale(arcade::data::Vector2f scale) override;
        arcade::data::Vector2f getScale() const override;
        void rotate(float angle) override;
        void setRotation(float angle) override;
        float getRotation() const override;
        void setTextureRect(const arcade::data::IntRect &rect) override;
        arcade::data::IntRect getTextureRect() const override;
        void setColor(arcade::data::Color color,
            const std::vector<std::vector<arcade::data::Color>> &asciiColors) override;
        void drawSprite();

      private:
        Texture texture;
        SDL_Rect srcRect;
        SDL_Rect destRect;
        SDL_Point origin;
        arcade::data::Vector2f scale;
        arcade::data::Vector2f size;
        float rotation;
    };

    class GraphicSdl2 : public arcade::displayer::IDisplay {
      public:
        GraphicSdl2();
        ~GraphicSdl2();
        int availableOptions() const override;
        void init(const std::string &title = "Arcade", const unsigned int limit = 60) override;
        void stop() override;
        bool isOpen() const override;
        void clearWindow() override;
        void display() override;
        void restartClock() override;
        double getDeltaTime() const override;
        double getFrameDuration() const;
        arcade::data::Vector2u getWindowSize() const override;
        std::vector<arcade::data::Event> getEvents() override;
        void draw(std::unique_ptr<arcade::displayer::IText> &text) override;
        void draw(std::unique_ptr<arcade::displayer::ISprite> &sprite) override;
        std::unique_ptr<arcade::displayer::IText> createText() const override;
        std::unique_ptr<arcade::displayer::IText> createText(const std::string &text) const override;
        std::unique_ptr<arcade::displayer::ISprite> createSprite() const override;
        std::unique_ptr<arcade::displayer::ISprite> createSprite(const std::string &spritePath,
            const std::vector<std::string> &asciiSprite,
            arcade::data::Vector2f scale = arcade::data::Vector2f{1, 1}) const override;

        double scaleMoveX(double time) const override;
        double scaleMoveY(double time) const override;

        typedef std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer *)>> Renderer;
        #define create_renderer(__value) (Renderer{__value, SDL_DestroyRenderer})
        static Renderer renderer;

      private:
        std::vector<arcade::data::Event> events;
        bool windowIsOpen;

        typedef std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>> Window;
        #define create_window(__value) (Window{__value, SDL_DestroyWindow})
        Window window;

        std::chrono::time_point<std::chrono::high_resolution_clock> timePoint;
        double lastFrameTime;
        unsigned int frameLimit;
    };
} // namespace sdl2

#endif /* !SDL2_HPP_ */
