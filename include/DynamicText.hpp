#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include<bits/stdc++.h>

using namespace std;

class DynamicText{
    public:

		// Constructor
        // example: "./assets/fonts/8bitOperatorPlus8-Regular.ttf"
        DynamicText(std::string fontfilepath, size_t fontSize);
        // Destructor
        ~DynamicText();
        // Function for drawing text
		void DrawText(SDL_Renderer* renderer, std::string text,int x, int y, int w, int h);

	private:
        // Rect,texture, and surface that we draw our font to.
		SDL_Rect m_rectangle;
		SDL_Texture* m_texture;
		SDL_Surface* m_surface;
        // The actual font
		TTF_Font* m_ourFont;
        // Purpose is to ensure that TTF library is only
        // initialized one time
		static bool s_ttfInitialized;

};