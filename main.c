//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

char s[] = "hello world\n";

int main( int argc, char* args[] )
{
	printf("%s", s);
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	
	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;
	SDL_Surface *png;
	SDL_Surface *dot;
	SDL_RWops *rpng;
	SDL_Rect rec = {0};
	SDL_Rect rec2 = {0};
 (void)rec2;
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	else
	{
		//Create window
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN);
		if( window == NULL )
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		else
		{
			rpng = SDL_RWFromFile("./42microchip.png","rb+");
			if (rpng == NULL)
				return (3);
			png = IMG_LoadPNG_RW(rpng);
			if (png == NULL)
				return (2);
		    dot = SDL_CreateRGBSurfaceWithFormat(png->flags,5, 5, 32, png->format->format);
				//Get window surface
			screenSurface = SDL_GetWindowSurface( window );

			//Fill the surface white
			//SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
			SDL_FillRect( dot, NULL, SDL_MapRGB( dot->format, 0x0, 0xFF, 0x0 ) );
			rec.x = 0;
			rec.y = 0;
			rec.h = 250;
			rec.w = 250;
			rec2.x = 10;
			rec2.y = 10;
			 SDL_BlitSurface( png, &rec, screenSurface, &rec2 );
			//Update the surface
			SDL_UpdateWindowSurface( window );

			//Hack to get window to stay up
			SDL_Event e; bool quit = false;
			while( quit == false)
			{
				while( SDL_PollEvent( &e ) )
				{
					 if( e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
					 	quit = true;
					if (e.motion.state == true)
					{
					 //SDL_Rect recm = {.h=210, .w=210, .x = 220, .y=210};
					 SDL_Rect recm = {.h=dot->h, .w=dot->w, .x = e.motion.x, .y=e.motion.y};
					 SDL_BlitSurface( dot, NULL, screenSurface, &recm );
					 SDL_UpdateWindowSurface( window );
					}
				}
				
			}
		}
	}
	__always_inline
	SDL_RWclose(rpng);
		//Destroy window
	SDL_FreeSurface(png);
	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}