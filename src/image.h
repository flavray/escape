#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <QtOpenGL>
#include <QImage>

#include <string>

/*
    OpenGL Image helper class
*/
class Image {
public:
    Image(std::string path);

    void prepaint();

    int width() { return _image.width(); }
    int height() { return _image.height(); }

private:
    QImage _image;
    GLuint _texture[1];
};

#endif
