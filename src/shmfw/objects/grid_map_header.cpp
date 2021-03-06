/***************************************************************************
 *   Software License Agreement (BSD License)                              *
 *   Copyright (C) 2012 by Markus Bader <markus.bader@tuwien.ac.at>        *
 *                                                                         *
 *   Redistribution and use in source and binary forms, with or without    *
 *   modification, are permitted provided that the following conditions    *
 *   are met:                                                              *
 *                                                                         *
 *   1. Redistributions of source code must retain the above copyright     *
 *      notice, this list of conditions and the following disclaimer.      *
 *   2. Redistributions in binary form must reproduce the above copyright  *
 *      notice, this list of conditions and the following disclaimer in    *
 *      the documentation and/or other materials provided with the         *
 *      distribution.                                                      *
 *   3. Neither the name of the copyright holder nor the names of its      *
 *      contributors may be used to endorse or promote products derived    *
 *      from this software without specific prior written permission.      *
 *                                                                         *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS   *
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT     *
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS     *
 *   FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE        *
 *   COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,  *
 *   INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,  *
 *   BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;      *
 *   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER      *
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT    *
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY *
 *   WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE           *
 *   POSSIBILITY OF SUCH DAMAGE.                                           *
 ***************************************************************************/


#include "grid_map_header.h"

using namespace ShmFw;

const size_t& GridMapHeader::getSizeX() const {
    return m_size_x;
}
const size_t& GridMapHeader::getColumns() const {
    return getSizeX();
}
const size_t& GridMapHeader::getSizeY() const {
    return m_size_y;
}
const size_t& GridMapHeader::getRows() const {
    return getSizeY();
}
const size_t& GridMapHeader::getDepth() const {
    return m_depth;
}
const size_t& GridMapHeader::getLayers() const {
    return m_layers;
}
const size_t& GridMapHeader::getTypeHashCode() const {
    return m_type_hash_code;
}
const double& GridMapHeader::getXMin() const  {
    return m_x_min;
}
const double& GridMapHeader::getXMax() const  {
    return m_x_max;
}
const double& GridMapHeader::getYMin() const  {
    return m_y_min;
}
const double& GridMapHeader::getYMax() const  {
    return m_y_max;
}
const double& GridMapHeader::getRotation() const  {
    return m_rotation;
}
void GridMapHeader::setRotation(double phi){
    m_rotation = phi;
}
const double& GridMapHeader::getResolution() const  {
    if ( m_x_resolution == m_y_resolution ) return m_x_resolution;
    else throw 0;
}
const double& GridMapHeader::getResolutionX() const  {
    return m_x_resolution;
}
const double& GridMapHeader::getResolutionY() const  {
    return m_y_resolution;
}
const size_t& GridMapHeader::size() const {
    return m_size;
}
const size_t& GridMapHeader::size_total() const {
    return m_size_total;
}
const size_t& GridMapHeader::bytes() const {
    return m_bytes;
}
const size_t& GridMapHeader::bytes_total() const {
    return m_bytes_total;
}
void GridMapHeader::world2Cell (const double wx, const double wy, int &cx, int &cy ) const {
  cx = m_M[0][0] * wx + m_M[0][1] * wy + m_M[0][2];
  cy = m_M[1][0] * wx + m_M[1][1] * wy + m_M[1][2];
}
void GridMapHeader::cell2World (const int cx, const int cy, double &wx, double &wy ) const {
  wx = m_Minv[0][0] * cx + m_Minv[0][1] * cy + m_Minv[0][2];
  wy = m_Minv[1][0] * cx + m_Minv[1][1] * cy + m_Minv[1][2];
}
cv::Point GridMapHeader::cvCellPoint ( double x, double y ) const {
    return cv::Point ( x2idx ( x ), y2idx ( y ) );
}
cv::Point GridMapHeader::cvCellPoint ( const cv::Point &p ) const {
    return cv::Point ( x2idx ( p.x ), y2idx ( p.y ) );
}
std::vector<cv::Point> GridMapHeader::cvCellPoint ( const std::vector<cv::Point> &src, std::vector<cv::Point> &des ) const {
    des.resize ( src.size() );
    for ( size_t i = 0; i < src.size(); i++ ) des[i] = cvCellPoint ( src[i] );
    return des;
}
cv::Point GridMapHeader::cvCellPoint ( const cv::Point2f &p ) const {
    return cv::Point ( x2idx ( p.x ), y2idx ( p.y ) );
}
std::vector<cv::Point> GridMapHeader::cvCellPoint ( const std::vector<cv::Point2f> &src, std::vector<cv::Point> &des ) const {
    des.resize ( src.size() );
    for ( size_t i = 0; i < src.size(); i++ ) des[i] = cvCellPoint ( src[i] );
    return des;
}
cv::Point GridMapHeader::cvCellPoint ( const cv::Point2d &p ) const {
    return cv::Point ( x2idx ( p.x ), y2idx ( p.y ) );
}
std::vector<cv::Point> GridMapHeader::cvCellPoint ( const std::vector<cv::Point2d> &src, std::vector<cv::Point> &des ) const {
    des.resize ( src.size() );
    for ( size_t i = 0; i < src.size(); i++ ) des[i] = cvCellPoint ( src[i] );
    return des;
}
cv::Point2d GridMapHeader::cvCoordinatePoint ( int &x, int &y ) const {
    return cv::Point2d ( idx2x ( x ), idx2y ( y ) );
}
cv::Point2d GridMapHeader::cvCoordinatePoint ( const cv::Point &p ) const {
    return cv::Point2d ( idx2x ( p.x ), idx2y ( p.y ) );
}
int GridMapHeader::cvtype() const {
    int type = -1;
    if ( m_depth == 1 ) type = CV_8U;
    else if ( m_depth == 2 ) type = CV_16U;
    else if ( m_depth == 3 ) type = CV_8UC3;
    return type;
}
cv::Scalar GridMapHeader::cvGreen() {
    return cv::Scalar ( 0,255,0 );
}
cv::Scalar GridMapHeader::cvBlue() {
    return cv::Scalar ( 0,0,255 );
}
cv::Scalar GridMapHeader::cvRed() {
    return cv::Scalar ( 0,0,255 );
}
cv::Mat_<double> GridMapHeader::getTransformation ( ) const {
    cv::Mat_<double> m ( 3,3 );
    double sx = 1./m_x_resolution;
    double sy = 1./m_x_resolution;
    m ( 0,0 ) = sx, m ( 0,1 ) =  0, m ( 0,2 ) = -m_x_min*sx;
    m ( 1,0 ) =  0, m ( 1,1 ) = sx, m ( 1,2 ) = -m_y_min*sy;
    m ( 2,0 ) =  0, m ( 2,1 ) =  0, m ( 2,2 ) = 1;
    /// ToDo add Rotation
    // double ca = cos(m_rotation);
    // double sa = sin(m_rotation);
    return m;
}
void GridMapHeader::setTypeHasCode ( const size_t type_hash_code ) {
    m_type_hash_code = type_hash_code;
}
void GridMapHeader::initHeader ( const double x_min, const double x_max, const double y_min, const double y_max, const double x_resolution, const double y_resolution, const size_t depth, const size_t layers, const size_t type_hash_code ) {
    initHeader ( x_min, x_max, y_min, y_max, x_resolution, y_resolution, depth, layers );
    setTypeHasCode ( type_hash_code );
}
void GridMapHeader::initHeader ( const double x_min, const double x_max, const double y_min, const double y_max, const double x_resolution, const double y_resolution, const size_t depth, const size_t layers ) {
    m_x_min = x_resolution*round ( x_min/x_resolution );
    m_y_min = y_resolution*round ( y_min/y_resolution );
    m_x_max = x_resolution*round ( x_max/x_resolution );
    m_y_max = y_resolution*round ( y_max/y_resolution );
    // Res:
    m_x_resolution = x_resolution;
    m_y_resolution = y_resolution;
    // Now the number of cells should be integers:
    size_t size_x = round ( ( m_x_max-m_x_min ) /m_x_resolution );
    size_t size_y = round ( ( m_y_max-m_y_min ) /m_y_resolution );
    initSize ( size_x, size_y, depth, layers );
}
void GridMapHeader::updateResolution (const double x_resolution, const double y_resolution) {
    m_x_min = x_resolution*round ( m_x_min/m_x_resolution );
    m_y_min = y_resolution*round ( m_y_min/m_y_resolution );
    m_x_max = x_resolution*round ( m_x_max/m_x_resolution );
    m_y_max = y_resolution*round ( m_y_max/m_y_resolution );
    // Res:
    m_x_resolution = x_resolution;
    m_y_resolution = y_resolution;
}
void GridMapHeader::initHeader ( const double x_min, const double x_max, const double y_min, const double y_max, const size_t size_x, const size_t size_y, const size_t depth, const size_t layers, const size_t type_hash_code ) {
    initHeader ( x_min, x_max, y_min, y_max, size_x, size_y, depth, layers );
    setTypeHasCode ( type_hash_code );
}
void GridMapHeader::initHeader ( const double x_min, const double x_max, const double y_min, const double y_max, const size_t size_x, const size_t size_y, const size_t depth, const size_t layers ) {
    m_x_min = x_min;
    m_y_min = y_min;
    m_x_max = x_max;
    m_y_max = y_max;
    m_x_resolution = ( m_x_max-m_x_min ) / ( double ) size_x;
    m_y_resolution = ( m_y_max-m_y_min ) / ( double ) size_y;
    initSize ( size_x, size_y, depth, layers );
}
void GridMapHeader::initSize ( const size_t size_x, const size_t size_y, const size_t depth, const size_t layers ) {
    m_depth = depth;
    m_layers = layers;
    m_size_x = size_x;
    m_size_y = size_y;
    m_size = size_x * size_y;
    m_size_total = size_x * size_y * layers;
    m_bytes = size_x * size_y * depth;
    m_bytes_total = size_x * size_y * depth * layers;
}
int   GridMapHeader::x2idx ( double x ) const {
    return static_cast<int> ( ( x-this->m_x_min ) /this->m_x_resolution );
}
int   GridMapHeader::y2idx ( double y ) const {
    return static_cast<int> ( ( y-this->m_y_min ) /this->m_y_resolution );
}
int GridMapHeader::cxcy2idx ( int x,int y ) const {
    return x + y * this->m_size_x;
}
void  GridMapHeader::idx2cxcy ( const int &idx,  int &cx, int &cy ) const {
    cx = idx % this->m_size_x;
    cy = idx / this->m_size_x;
}
double   GridMapHeader::idx2x ( int cx ) const {
    return this->m_x_min+ ( cx+0.5f ) *this->m_x_resolution;
}
double   GridMapHeader::idx2y ( int cy ) const {
    return this->m_y_min+ ( cy+0.5f ) *this->m_y_resolution;
}
bool GridMapHeader::idxInRangeMap ( int cx, int cy ) const {
    return ( cx >= 0 ) && ( cy >= 0 ) && ( cx < ( int ) m_size_x ) && ( cy < ( int ) m_size_y );
}
bool GridMapHeader::xyInRangeMap ( double x, double y ) const {
    return ( x >= m_x_min ) && ( y >= m_y_min ) && ( x <= m_x_max ) && ( y <= m_y_max );
}
bool GridMapHeader::compareResolution ( const GridMapHeader& o ) const {
    return getResolutionX() == o.getResolutionX() && getResolutionY() == o.getResolutionY();
}
bool GridMapHeader::compareGridSize ( const GridMapHeader& o ) const {
    return getSizeX() == o.getSizeX() && getSizeY() == o.getSizeY();
}
bool GridMapHeader::compareMetricRepresentation ( const GridMapHeader& o ) const {
    return getXMin() == o.getXMin() && getXMax() == o.getXMax() && getYMin() == o.getYMin() && getYMax() == o.getYMax() && getRotation() == o.getRotation();
}