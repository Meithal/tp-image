#include <vector>
#include <iostream>


template<typename T>
T clamp(T v, T min, T max) {
    if (v < min)
        return min;
    if (v > max)
        return max;
    return v;
}

class Image {

public:
enum Model{
    None,
    RGB,
    Gray,
};

private:
    int _width;
    int _height;
    int _nb_channels;
    enum Model _model;
    char* _tab;

public:
    Image();
    Image(int width, int height, int channels, enum Model, int = 0);
    Image(int width, int height, int channels, enum Model, char*);
    Image(const Image&);
    ~Image();
    Image& operator=(const Image&);

    int getWidth() const;
    void setWidth(int);
    int getHeight() const;
    void setHeight(int);
    int getNbChannels() const;
    void setNbChannels(int);
    enum Model getModel() const;
    void setModel(enum Model);
    std::ostream& print(std::ostream&);

    const char& at(int channel, int y, int x) const;
    char& at(int channel, int y, int x);
    const char& operator()(int channel, int y, int x) const;
    char& operator()(int channel, int y, int x);
    Image& operator+(Image&);
    Image& operator+(int);
    Image& operator+(int*);
    Image& operator-(Image&);
    Image& operator-(int);
    Image& operator-(int*);
    Image& operator^(Image&);
    Image& operator^(int);
    Image& operator^(int*);
    Image& operator*(double);
    Image& operator/(double);
    Image operator<(double);
    Image operator==(double);
    Image& operator~();

    friend std::ostream& operator<<(std::ostream&, Image&);
};

