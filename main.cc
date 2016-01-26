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

    QApplication app(argc, argv);

    Game game;
    /* Mandatory, otherwise the game object isn't properly
       built.
    */
    game.setFont(font);
    game.show();
    return app.exec();
}
