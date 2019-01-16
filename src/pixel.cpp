#include<cmath>
#include "pixel.hpp"
#include <iostream>

Pixel::Pixel(float x, float y, float intensity):m_x(x),m_y(y),m_intensity(intensity)
{
}


float Pixel::get_x() {
  return m_x;
}

float Pixel::get_y() {
  return m_y;
}

float Pixel::get_intensity() {
  return m_intensity ;
}

float Pixel::distance(Pixel p) {
    return std::pow(std::pow(m_x - p.get_x(),2) + std::pow(m_y - p.get_y(),2),0.5);
}

Pixel Pixel::rotation(Pixel origin, float angle){ // FIX To move in rotation.cpp
  float x = (m_x-origin.m_x)*cos(angle)-(m_y-origin.m_y)*sin(angle)+ origin.m_x;
  float y = (m_x-origin.m_x)*sin(angle)+(m_y-origin.m_y)*cos(angle)+ origin.m_y;
  return Pixel(x,y,m_intensity);
}

Pixel Pixel::warp(Pixel location, float strength) { // FIX to move in warpping.cpp
  float d = this->distance(location);
  float x = (m_x - location.m_x) * cos(strength / d) - (m_y - location.m_y) * sin(strength / d) + location.m_x;
  float y = (m_x - location.m_x) * sin(strength / d) + (m_y - location.m_y) * cos(strength / d) + location.m_y;
  return Pixel(x,y,m_intensity);
}