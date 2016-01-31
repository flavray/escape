#include "image.h"

Image::Image(std::string path) {
    QImage image;
    image.load(path.c_str());
    _image = QGLWidget::convertToGLFormat(image);
    glGenTextures(1, _texture);
}

void Image::prepaint() {
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glShadeModel(GL_FLAT);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _texture[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
            _image.width(), _image.height(),
            0, GL_RGBA, GL_UNSIGNED_BYTE, _image.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
