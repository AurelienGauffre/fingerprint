#include "image.hpp"

std::vector<Pixel> Image::convert_to_pixels() {
  std::vector<Pixel> Pixel_array;
  for (int y = 0; y < m_height; y++)
  {
    for (int x = 0; x < m_width; x++)
    {
      Pixel_array.push_back(Pixel(x,y, m_intensity_array[coord_to_index(x,y)]));
    }
  }
  return Pixel_array;
}

/*!
  *  Do not change the position of the Pixels in the returned array.
  */
std::vector<Pixel> Image::rotate_pixels(std::vector<Pixel>& Pixel_array, float angle, Pixel rot_Pixel) {
  for (int i = 0; i < (int)Pixel_array.size(); i++) {
    Pixel_array[i].rotation(rot_Pixel, angle);
  }
  return Pixel_array;
}


void Image::rotate_bilinear(float angle, const Pixel& rot_point, bool fill_black) {
  std::vector<Pixel> pixels(this->convert_to_pixels());
  std::vector<Pixel> former_pixels(this->rotate_pixels(pixels,angle, rot_point));
  this->bilinear_interpolation(former_pixels, fill_black);
}

void Image::bilinear_interpolation(std::vector<Pixel> &former_pixels, bool fill_black){
  std::vector<float> new_pixels_array(m_size);
  int fill = 1;
  if (fill_black) {
    fill = 0;
  }
  for (int i = 0; i < m_size; i++) {
    float x = former_pixels[i].get_x();
    float y = former_pixels[i].get_y();
    int x1 = (int)x ;
    int x2 = x1 + 1 ;
    int y1 = (int)y ;
    int y2 = y1 + 1 ;

    if ((x2 < (int)m_width)&&(x1 >= 0)&&(y2 < (int)m_height)&&(y1>=0)) {
      new_pixels_array[i] =  former_pixels[coord_to_index(x1,y1)].get_intensity()*(x2-x)*(y2-y)+ \
      former_pixels[coord_to_index(x2,y1)].get_intensity()*(x-x1)*(y2-y)+ \
      former_pixels[coord_to_index(x1,y2)].get_intensity()*(x2-x)*(y-y1)+ \
      former_pixels[coord_to_index(x2,y2)].get_intensity()*(x-x1)*(y-y1);
    }
    else{
      new_pixels_array[i] = fill;
    }
  }
  m_intensity_array = new_pixels_array;
}

cv::Mat Image::rotate_opencv(float angle, Pixel& rot_point) {
  cv::Mat result;
  cv::Point2f p_rot(rot_point.get_x(), rot_point.get_y());
  cv::Mat rot_mat = cv::getRotationMatrix2D(p_rot, angle, 1.0);
  cv::warpAffine(*m_original_image, result, rot_mat, cv::Size(m_width, m_height));
  return result;
}
