#include <utility>

#include "image.hpp"

std::ostream& Image::print(std::ostream & o)
{
    o << getWidth()
        << "x" << getHeight()
        << "x" << getNbChannels()
        << "(";

    switch (_model) {
        case Image::RGB:
            o << "RGB";
            break;
        case Image::Gray:
            o << "GRAY";
            break;
        case Image::None:
            o << "None";
            break;
    }

    o << ")";

    return o;
}

Image::Image()
    : Image(0, 0, 0, Image::None)
{
}

Image::Image(int width, int height, 
    int nb_channels, Model model, 
    int remplissage)
    : _width(width), 
    _height(height),
    _nb_channels(nb_channels), 
    _model(model),
    _tab(new char[(unsigned)(nb_channels*width*height)])
{
    std::memset(_tab, remplissage, (unsigned)(nb_channels*width*height));
}

Image::Image(int width, int height, int nb_channels, 
    Image::Model model, char* v)
: _width(width), _height(height),
    _nb_channels(nb_channels), _model(model),
    _tab(new char[(unsigned)(nb_channels*width*height)])
{
    std::memcpy(_tab, v, (unsigned)(nb_channels*width*height));
}

Image::Image(const Image &o) : Image(
    o.getWidth(), o.getHeight(), o.getNbChannels()
    ,o.getModel(), o._tab)
{
}

Image::~Image()
{
    delete[] _tab;
}

Image &Image::operator=(const Image &o)
{
    if(&o == this)
        return *this;
    Image temp(o);
    std::swap(_width, temp._width);
    std::swap(_height, temp._height);
    std::swap(_nb_channels, temp._nb_channels);
    std::swap(_model, temp._model);

    std::swap(_tab, temp._tab);

    return *this;
}


int Image::getWidth() const
{
    return _width;
}

void Image::setWidth(int w)
{
    _width = w;
}

int Image::getHeight() const
{
    return _height;
}

void Image::setHeight(int h)
{
    _height = h;
}

int Image::getNbChannels() const
{
    return _nb_channels;
}

void Image::setNbChannels(int n)
{
    _nb_channels = n;
}

Image::Model Image::getModel() const
{
    return _model;
}

void Image::setModel(Model m)
{
    _model = m;
}

const char& Image::at(int channel, int y, int x) const
{  
    return const_cast<Image*>(this)->at(channel, y, x);
}

char &Image::at(int channel, int y, int x)
{
    return _tab[y*_nb_channels*_width+x*_nb_channels+channel];
}

const char& Image::operator()(int channel, int y, int x) const
{
    return at(channel, y, x);
}

char& Image::operator()(int channel, int y, int x)
{
    return at(channel, y, x);
}

Image &Image::operator+(Image & o)
{
    for(int i = 0; i < _nb_channels * _height * _width; i++) {
        _tab[i] = (char)clamp((int)_tab[i] + (int)o._tab[i], 0, 255);
    }

    return *this;
}
Image &Image::operator+(int v)
{
    for(int i = 0; i < _nb_channels * _height * _width; i++) {
        _tab[i] = (char)clamp((int)_tab[i] + v, 0, 255);
    }

    return *this;
}
Image &Image::operator+(int * pixel)
{
    for(int i = 0; i < _nb_channels * _height * _width; i+=_nb_channels) {
        for(int j=0; j < _nb_channels; j++) {
            _tab[i+j] = (char)clamp((int)_tab[i + j] + *(pixel + j), 0, 255);
        }
    }

    return *this;
}
Image &Image::operator-(Image &o)
{
    for(int i = 0; i < _nb_channels * _height * _width; i++) {
        _tab[i] = (char)clamp((int)_tab[i] - (int)o._tab[i], 0, 255);
    }

    return *this;
}
Image &Image::operator-(int v)
{
    for(int i = 0; i < _nb_channels * _height * _width; i++) {
        _tab[i] = (char)clamp((int)_tab[i] - v, 0, 255);
    }

    return *this;
}
Image &Image::operator-(int * pixel)
{
    for(int i = 0; i < _nb_channels * _height * _width; i+=_nb_channels) {
        for(int j=0; j < _nb_channels; j++) {
            _tab[i+j] = (char)clamp((int)_tab[i + j] - *(pixel + j), 0, 255);
        }
    }

    return *this;
}
Image &Image::operator^(Image &o)
{
    for(int i = 0; i < _nb_channels * _height * _width; i++) {
        _tab[i] = (char)clamp(std::abs((int)_tab[i] - (int)o._tab[i]), 0, 255);
    }

    return *this;
}
Image &Image::operator^(int v)
{
    for(int i = 0; i < _nb_channels * _height * _width; i++) {
        _tab[i] = (char)clamp(std::abs((int)_tab[i] - v), 0, 255);
    }

    return *this;
}
Image &Image::operator^(int * pixel)
{
    for(int i = 0; i < _nb_channels * _height * _width; i+=_nb_channels) {
        for(int j=0; j < _nb_channels; j++) {
            _tab[i+j] = (char)clamp(std::abs((int)_tab[i + j] - *(pixel + j)), 0, 255);
        }
    }

    return *this;
}

Image &Image::operator*(double v)
{
    for(int i = 0; i < _nb_channels * _height * _width; i++) {
        _tab[i] = (char)clamp((int)(_tab[i] * v), 0, 255);
    }

    return *this;
}

Image &Image::operator/(double v)
{
    if(v == 0)
        return *this;
    for(int i = 0; i < _nb_channels * _height * _width; i++) {
        _tab[i] = (char)clamp((int)(_tab[i] / v), 0, 255);
    }

    return *this;
}

Image Image::operator<(double v)
{
    Image n(*this);
    for(int y = 0; y < _height; y++)
        for (int x = 0; x < _width; x++)
            for(int c = 0; c < _nb_channels; c++)
                if(at(c, y, x) < v)
                    n.at(c, y, x) = (char)255;
    return n;
}

Image Image::operator==(double v)
{
    Image n(*this);
    for(int y = 0; y < _height; y++)
        for (int x = 0; x < _width; x++)
            for(int c = 0; c < _nb_channels; c++)
                if(at(c, y, x) == v)
                    n.at(c, y, x) = (char)255;
    return n;
}

Image &Image::operator~()
{
    for(int i = 0; i < _nb_channels * _height * _width; i++) {
        _tab[i] = (char)255 - _tab[i];
    }

    return *this;
}

std::ostream &operator<<(std::ostream&o, Image&i)
{
    return i.print(o);
}
