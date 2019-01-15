#ifndef DEF_IMAGE
#define DEF_IMAGE

/*!
 * \file image.hpp
 * \brief Definition of Image class
 * \author Perrine, Célestine, Aurélien, Lucas
 */
#include <iostream>
#include <opencv2/opencv.hpp>
// #include <opencv2/core/types_c.h>
#include <vector>
#include <string.h>
#include "pixel.hpp"


/*! \class Image
   * \brief class of the image we'll work on
   *
   *  The class is composed of several methods
   */
class Image {
  private:
    std::vector<float> m_intensity_array; /*!< 1D array of pixels reprensenting our image.*/
    unsigned int m_height;
    unsigned int m_width;
    unsigned int m_size;
    cv::Mat *m_original_image; /*!< We keep the Opencv image format in memory in our class to save it at the end. All the mathematical operation will be performed on the attribute m_intensity_array.*/
    std::string m_name;
  public:
    Image(cv::Mat image,std::string name);
    ~Image();
    float get_intensity(unsigned int k);
    void display_attributes();
    void back_to_Mat(); /*!< Update the Mat version of Image*/
    void display_Mat();
    float min_intensity();
    float max_intensity();
    void save_Mat(std::string name = "");
    void draw_rectangle(float intensity, unsigned int origine[2], unsigned int width, unsigned int height);
    unsigned int coord_to_index(unsigned int x, unsigned int y);
    // unsigned int *index_to_coord(unsigned int k);
    void symetry_y();
    void symetry_diag();
    void weight_coeff(unsigned int x_spot, unsigned int y_spot); /*!< Simulates the fingerprint with a weak pressure given the center of pressure (circle approximation)*/
    void weight_coeff_ellipse(float percentage);  /*!< Simulates the fingerprint with a weak pressure given a "percentage" of pressure (ellipse approximation) */
    unsigned int *find_ellipse(); /*!< Finds the ellipse that best represents the finger*/
    std::vector<Pixel> coord_pixels();  /*!< Returns the array of Pixels*/
    std::vector<Pixel> coord_pixels_rotated(std::vector<Pixel> Pixel_array, float angle, Pixel rot_Pixel); /*!< Returns array of rotated pixels (but keep same order than coord_pixels)*/
    void rotate(float angle, Pixel rot_point);
    void rotate_bilinear(float angle, Pixel rot_point);
    int optimization(Image &modele);
    void translation_x(int p_x);
    void translation_y(int p_y);
    std::vector<Pixel> coord_pixels_warpped(std::vector<Pixel> Pixel_array, float strength, Pixel location); /*!< Returns array of warpped pixels (but keep same order than coord_pixels)*/
    void warp(float strength, Pixel location); /*!< Warp a part of picture*/
};

#endif
