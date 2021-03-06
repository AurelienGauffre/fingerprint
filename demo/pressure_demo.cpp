#include "image.hpp"

int main(int argc, char const *argv[]) {
  std::cout << "Demo pressure :" << std::endl ;
  std::string m_name;
  if (argc == 2){
    m_name = (std::string)argv[1];
  }
  else{
    m_name = "../ressources/clean_finger.png" ;
  }
  cv::Mat m_image;
  m_image = cv::imread(m_name, cv::IMREAD_GRAYSCALE);
  Image im1(m_image, m_name);
  im1.weight_coeff_ellipse(0.85);
  im1.display_Mat();
  return 0;
}
