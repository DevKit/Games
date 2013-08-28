#ifndef GROUTINES_H_INCLUDED
#define GROUTINES_H_INCLUDED


// G(raphics) routines


#include "SDL/SDL.h"
#include "SDL/SDL_image.h"


//===========================================================================//
// Name: LoadSurface
// Parameters: An object of the standard string class.
// Purpose: Load an image into an SDL_Surface.
// Pre-condition(s): A valid string, containing the path to an image file
// (no null string or invalid path).
// Post-condition(s): On SUCCESS, return a pointer to the newly allocated
// surface and on FAILURE
// - Invalid_String exception (invalid parameter passed to the function)
// - Null_Pointer exception (SDL_DisplayFormat failed)
// - Specific image loading error (IMG_Load failed to load the image)
//===========================================================================//
SDL_Surface* LoadSurface(std::string name)
{
    if (name == "")
        throw Invalid_String();

    SDL_Surface *tmpSurface = nullptr;
    SDL_Surface *optSurface = nullptr;

    // IMG_Load can handle various image formats
    tmpSurface = IMG_Load(name.c_str());

    if (tmpSurface)
    {
        // Convert a surface to the display format
        // so that it is not done at run-time, which
        // can be detrimental to performance
        optSurface = SDL_DisplayFormat(tmpSurface);

        // Get rid of the old surface
        SDL_FreeSurface(tmpSurface);

        // Chroma (color) keying (Don't apply for PNG and TGA images!)
        /*
        if (optSurface)
        {
            SDL_SetColorKey(optSurface, SDL_SRCCOLORKEY, SDL_MapRGB(optSurface -> format, 0, 0xFF, 0xFF));
        }
        */
    }

    else
        fprintf(stderr, "%s", IMG_GetError());

    return optSurface;
}


void FillWholeRect(SDL_Surface *i, SDL_Color c)
{
    SDL_FillRect(i, &i -> clip_rect, SDL_MapRGB(i -> format, c.r, c.g, c.b));
}


void PlaceSurface(Sint16 x, Sint16 y, SDL_Surface *src, SDL_Surface *dest, SDL_Rect *clip = nullptr)
{
    if (!src || !dest)
        return;

    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    // 2nd optional parameter -> clip
    SDL_BlitSurface(src, nullptr, dest, &offset);
}


#endif // GROUTINES_H_INCLUDED
