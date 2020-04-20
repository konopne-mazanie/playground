#pragma once

#include "Rgb.h"
#include <string>

/* external dependencies */
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Texture;
struct SDL_Rect;
struct _TTF_Font;
using TTF_Font = _TTF_Font;

class Rectangle;
class Vector;

namespace MySDL {

class SDL {
public:
	explicit SDL(uint32_t flags);
	~SDL();
};

class TTF {
public:
	TTF();
	~TTF();
};

class Window {
public:
	Window(std::string const &title, int width, int height);
	~Window();

	Window(Window const &) = delete;
	Window &operator=(Window const &) = delete;

	SDL_Window *get() {
		return window_;
	}

	Vector size() const;

private:
	SDL_Window *window_;
};

class Renderer {
public:
	explicit Renderer(Window &window);
	explicit Renderer(SDL_Window &window);
	~Renderer();

	Renderer(Renderer const &) = delete;
	Renderer &operator=(Renderer const &) = delete;

	SDL_Renderer *get() {
		return renderer_;
	}

	SDL_Renderer const *get() const {
		return renderer_;
	}

	void setColor(Rgb rgb);
	void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void clear();
	void render();
	void drawLine(int x0, int y0, int x1, int y1);

private:
	SDL_Renderer *renderer_;
};

class Surface {
public:
	~Surface();

	explicit Surface(std::string const &filename);
	explicit Surface(SDL_Surface *surface);

	Surface(Surface const &) = delete;
	Surface &operator=(Surface &) = delete;

	Surface(Surface &&old) noexcept;
	Surface &operator=(Surface &&old) noexcept;

	SDL_Surface *get() { return surface_; }
	SDL_Surface const *get() const { return surface_; }

	Vector size() const;

private:
	SDL_Surface *surface_;
	unsigned char *data_;
};

class Texture {
public:
	~Texture();

	Texture(Renderer &renderer, Surface &surface);

	Texture(Texture const &) = delete;
	Texture &operator=(Texture const &) = delete;

	Texture(Texture &&old) noexcept;
	Texture &operator=(Texture &&old) noexcept;

	SDL_Texture *get() { return texture_; }
	SDL_Texture const *get() const { return texture_; }

	Vector size() const;

private:
	SDL_Texture *texture_;
};

Texture loadTexture(Renderer &renderer, std::string const &filename);

class Font {
public:
	Font(std::string const &file, int pointsize);
	Font(Font const &) = delete;
	Font &operator=(Font const &) = delete;
	~Font();

	// It would be nice to have string_view there.
	Surface renderText_solid(std::string const &text, Rgb color);

private:
	TTF_Font *font_;
};

} // namespace MySDL

SDL_Rect toSDL(Rectangle const &rect);
void draw(MySDL::Renderer &renderer, MySDL::Texture &texture, Rectangle const &rectangle, double angle);
