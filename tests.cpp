#include <sstream>
#include <string>

#include "utest.hpp"

#include "image.hpp"

UTEST_MAIN()


struct MyTestFixture {
  Image image;
};


UTEST(ImageLib, test_default_constructor) {
  Image image;
  ASSERT_EQ(image.getHeight(), 0);
  ASSERT_EQ(image.getWidth(), 0);
  ASSERT_EQ(image.getNbChannels(), 0);
  ASSERT_EQ(image.getModel(), Image::None);
}

UTEST(ImageLib, test_param_constructor) {
  Image image(3, 4, 2, Image::Gray);
  ASSERT_EQ(image.getHeight(), 4);
  ASSERT_EQ(image.getWidth(), 3);
  ASSERT_EQ(image.getNbChannels(), 2);
  ASSERT_EQ(image.getModel(), Image::Gray);
}

UTEST(ImageLib, test_param_constructor_value) {
  Image image(3, 4, 2, Image::Gray, 55);
  ASSERT_EQ(image.getHeight(), 4);
  ASSERT_EQ(image.getWidth(), 3);
  ASSERT_EQ(image.getNbChannels(), 2);
  ASSERT_EQ(image.getModel(), Image::Gray);
  ASSERT_EQ(image.at(1, 2, 2), 55);
}

UTEST(ImageLib, test_copy_constructor) {
  Image image(3, 4, 2, Image::Gray);
  Image image2(image);
  ASSERT_EQ(image.getHeight(), 4);
  ASSERT_EQ(image.getWidth(), 3);
  ASSERT_EQ(image.getNbChannels(), 2);
  ASSERT_EQ(image.getModel(), Image::Gray);
  image.at(1, 2, 2) = 100;
  image(1, 1, 1) = 101;
  ASSERT_EQ(image.at(1, 2, 2), 100);
  ASSERT_EQ(image.at(1, 0, 0), 0);
  ASSERT_EQ(image(1, 1, 1), 101);
  ASSERT_EQ(image2.at(1, 2, 2), 0);
  ASSERT_EQ(image2.at(1, 0, 0), 0);
  ASSERT_EQ(image2(1, 1, 1), 0);
}

UTEST(ImageLib, string_output) {
    Image image(3, 4, 2, Image::Gray);

    {
        std::ostringstream oss;
        oss << image;
        std::string s = oss.str();

        ASSERT_STREQ(s.c_str(), "3x4x2(GRAY)");
    }

    image.setWidth(10);
    image.setHeight(20);
    image.setNbChannels(5);
    image.setModel(Image::RGB);
    {
        std::ostringstream oss;
        oss << image;
        std::string s = oss.str();

        ASSERT_STREQ(s.c_str(), "10x20x5(RGB)");
    }

    {
        Image image2;
        std::ostringstream oss;
        oss << image2;
        std::string s = oss.str();

        ASSERT_STREQ(s.c_str(), "0x0x0(None)");
    }
}

UTEST(ImageLib, test_assignment) {
  Image image(3, 4, 2, Image::Gray);
  Image image2;
  ASSERT_EQ(image2.getHeight(), 0);
  image2 = image;
  ASSERT_EQ(image.getHeight(), 4);
  ASSERT_EQ(image2.getHeight(), 4);
  image.at(1, 2, 2) = 100;
  image(1, 1, 1) = 101;
  ASSERT_EQ(image.at(1, 2, 2), 100);
  ASSERT_EQ(image.at(1, 0, 0), 0);
  ASSERT_EQ(image(1, 1, 1), 101);
  ASSERT_EQ(image2.at(1, 2, 2), 0);
  ASSERT_EQ(image2.at(1, 0, 0), 0);
  ASSERT_EQ(image2(1, 1, 1), 0);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wself-assign-overloaded"

  image2 = image2;

#pragma GCC diagnostic pop

  image2(1, 1, 1) = 101;
  ASSERT_EQ(image2(1, 1, 1), 101);
}

UTEST(ImageLib, test_addition) {
  Image i1(2, 2, 3, Image::RGB, 2);
  Image i2(2, 2, 3, Image::RGB, 3);

  ASSERT_EQ(i1.at(0, 0, 0), 2);
  ASSERT_EQ(i2.at(0, 0, 0), 3);
  Image ia = i1 + i2;
  ASSERT_EQ(ia.at(0, 0, 0), 5);
  ASSERT_EQ(i1.at(0, 0, 0), 2);
  ASSERT_EQ(i2.at(0, 0, 0), 3);

  Image i3(2, 2, 3, Image::RGB, 4);
  i3 += i1;

  ASSERT_EQ(i3.at(0, 0, 0), 6);
  ASSERT_EQ(i1.at(0, 0, 0), 2);

  i3 *= 2;
  ASSERT_EQ(i3.at(0, 0, 0), 12);
  i3 /= 3;
  ASSERT_EQ(i3.at(0, 0, 0), 4);
}

UTEST(ImageLib, test_seuil) {
  Image i1(2, 2, 3, Image::RGB, 2);
  Image i2(2, 2, 3, Image::RGB, 3);

  Image i3 = i1 < 2;
  ASSERT_EQ(i3.at(0, 0, 0), 0);
  
  ASSERT_EQ(i3.getModel(), Image::Gray);

  Image i4 = i1 > 1;
  ASSERT_EQ(i4.at(0, 0, 0), 255);
}

UTEST(ImageLib, test_saveload) {
  Image i1(2, 2, 3, Image::RGB, 2);
  i1.save("toto");

  Image i2;
  i2.load("toto");


  ASSERT_EQ(i1.at(0, 0, 0), 2);
  ASSERT_EQ(i1.getWidth(), 2);

  ASSERT_EQ(i2.getWidth(), 2);
  ASSERT_EQ(i2.at(0, 0, 0), 2);

}
