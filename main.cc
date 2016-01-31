#include <iostream>

#include <QApplication>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "game.h"

int main(int argc, char *argv[]) {

    /* FreeType initialization */
    FT_Library  library;
    if (FT_Init_FreeType(&library)) {
        std::cerr << "Unable to load FreeType library." << std::endl;
        return EXIT_FAILURE;
    }

    /* FreeSans font loading */
    FT_Face font;
    if(FT_New_Face(library, "data/FreeSans.ttf", 0, &font)) {
        std::cerr << "Unable to load font." << std::endl;
        return EXIT_FAILURE;
    }

    /* Height = 32px */
    FT_Set_Pixel_Sizes(font, 0, 32);

    /* Load differents chars used throughout the app */
    char charset[] = {'1', '2', '3', '4', '5',
                      '6', '7', '8', '9',
                      '/', 'm'};
    for (char c : charset)
        if (FT_Load_Char(font, c, FT_LOAD_RENDER)) {
            std::cerr << "Unable to load character " << c << std::endl;
            return EXIT_FAILURE;
        }


    QApplication app(argc, argv);

    Game game;
    /* Mandatory, otherwise the game object isn't properly
       built.
    */
    game.setFont(font);
    game.show();
    return app.exec();
}
