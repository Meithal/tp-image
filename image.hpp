#include <vector>
#include <iostream>


class ImageException : public std::exception {
    private:
        std::string message;  // Store the error message
    public:
        explicit ImageException(const std::string& msg);
            const char* what() const noexcept override;
    };

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
    Gray
};

private:
    int _width;
    int _height;
    int _nb_channels;
    enum Model _model;
    unsigned char* _tab;

public:
    Image();
    Image(int width, int height, int channels, enum Model, int = 0);
    Image(int width, int height, int channels, enum Model, unsigned char*);
    Image(const Image&);
    ~Image();
    Image& operator=(const Image&);
    Image& operator~();

    int getWidth() const;
    void setWidth(int);
    int getHeight() const;
    void setHeight(int);
    int getNbChannels() const;
    void setNbChannels(int);
    enum Model getModel() const;
    void setModel(enum Model);
    std::ostream& print(std::ostream&);

    const unsigned char& at(int channel, int y, int x) const;
    unsigned char& at(int channel, int y, int x);
    const unsigned char& operator()(int channel, int y, int x) const;
    unsigned char& operator()(int channel, int y, int x);
    friend Image operator+(Image&, Image&);
    Image& operator+=(Image&);
    Image& operator+(int);
    Image& operator+(int*);
    Image& operator-(Image&);
    Image& operator-(int);
    Image& operator-(int*);
    Image& operator^(Image&);
    Image& operator^(int);
    Image& operator^(int*);
    Image& operator*=(double);
    Image& operator/=(double);
    Image operator<(double) const;
    Image operator>(double) const;
    Image operator==(double) const;
    Image operator!=(double) const;
    Image operator>=(double) const;
    Image operator<=(double) const;

    friend std::ostream& operator<<(std::ostream&, Image&);

    // Charger et sauvegarder des images (utilisation simple des fichiers binaires)
    bool save(const std::string& filename) const;
    bool load(const std::string& filename);
};

