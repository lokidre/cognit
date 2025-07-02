/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include <set>
#include <vector>
#include <map>


//TODO: checking - a lot of points on straight line around intersection

#include "lines.hpp"
#include "corners.hpp"

#include "../dsp/median.hpp"

#include "../geo/line.hpp"
#include "../geo/line/convert.hpp"
#include "../geo/line/dist.hpp"
#include "../geo/line/sect.hpp"
#include "../geo/vector/rotate.hpp"
#include "../geo/vector/trans.hpp"

#include "../opt/lmeds_pca.hpp"


namespace cognit {


template <class T>
class ChessboardDetector {

public :
	typedef T float_type ;

	typedef cognit::ANormalLine<T> normal_line_type ;

	struct Intersection {
		bool valid ;
		ANormalLine<T> vl, hl ; // horizontal and vertical lines
		T x, y ;
		int xx, yy ;
		T value ;  // some value - the strength
	} ;

	typedef std::vector<Intersection> intersection_list_type ;

	struct Line {
		T t, r ;
		intersection_list_type intersections ;
	} ;

	struct Segment {
		cognit::APointLine<T> line ;  // beginning and end of the segment
		intersection_list_type intersections ;
	} ;

	typedef std::vector<Segment> segment_list_type ;

	struct ChessboardInfo {
		int width, height ;
		intersection_list_type intersections ;
	} ;

	typedef std::vector<normal_line_type> normal_line_container_type ;
	///typedef std::vector<Line> normal_line_container_type ;

	typedef std::vector<typename EdgeDetector<T>::edge_type> point_list_type ;

	typedef std::pair<T,Intersection> sorted_corner_pair ;
	typedef std::map<T,Intersection> sorted_corner_list ;


public :  // options
	//T sigma_ ;
	//int aperture_ ;
	//T point_dispersion_ ;

	ChessboardInfo chessboard_ ;

	int chessboard_width_, chessboard_height_ ;

	LineDetector<T> lines_ ;


public :
	void set_sigma(const T &s ) {  lines_.set_sigma(s) ;  }


public :
	ChessboardDetector()
	{
		chessboard_width_ = 5, chessboard_height_ = 7 ;
	}


public :
	template <class image_type>
	void detect(const image_type *image, const int width, const int height )
	{
		using namespace std ;
		using namespace apl ;

		// do line detection
		lines_.detect(image,width,height) ;

		const int total = width * height ;


		//
		// now select line segments
		// criteria:
		// 1. the gradient direction is approximately perpendicular to the line
		/*
		segment_list_type segments ;

		// TODO: find out what's wrong with gradients
		{
			for ( normal_line_container_type::iterator l = lines.begin() ; l != lines.end() ; ++l ) {
				T pi = const_pi<T>()() ;
				T max_delta_theta = pi/6 ;
				T gradient_theta ;

				sorted_corner_list sorted_corners ;
				Corner first_corner ;

				// walk through all the edges, collecting the ones that have the correct gradient direction
				for ( Edges<T>::iterator e = edges.begin(), e_end = edges.end() ; e != e_end ; ++e ) {
					// verify the distance
					if ( pt_dist(*e,*l) > point_dispersion_ )
						continue ;

					// verify the gradient direction
					if ( tiny(e->gx) )
						gradient_theta = pi/2 ;
					else if ( tiny(e->gy) ) 
						gradient_theta = 0 ;
					else {
						//if ( abs(e->gx) > abs(e->gy) )
						//	gradient_theta = acos(abs(e->gx/e->norm)) ;
						//else
							gradient_theta = asin(abs(e->gy/e->norm)) ;

						//if ( gradient_theta < 0 )
						//	gradient_theta += pi ;
						if ( e->gx < 0 && e->gy > 0 )
							gradient_theta = pi - gradient_theta ;
						if ( e->gx > 0 && e->gy < 0 )
							gradient_theta = pi - gradient_theta ;
						if ( e->gx < 0 && e->gy < 0 )
							gradient_theta = pi + gradient_theta ;

						if ( gradient_theta < 0 ) {
							int a =0 ;
						}


					}


					//if ( abs(gradient_theta-l->t) > max_delta_theta )
					//	continue ;

					Corner c ;
					c.x = e->x, c.y = e->y ;
					if ( sorted_corners.empty() ) {
						first_corner = c ;
						sorted_corners.insert(sorted_corner_pair(0,c)) ;
					} else {
						sorted_corners.insert(sorted_corner_pair(-pt_dist_sqr_2d<T>(first_corner,c)*(first_corner.x * c.y - first_corner.y * c.x),c)) ;
					}

					// candidate_points.push_back(*e) ;
				}

				// now that we have sorted points, we can just select first and last one
				if ( sorted_corners.empty() )
					continue ;
					// throw std::runtime_error("something went wrong with segments") ;

				// compute the segment by taking the perpendicular from 

				Segment seg ;
				seg.line.u.x = sorted_corners.begin()->second.x, seg.line.u.y = sorted_corners.begin()->second.y ;
				seg.line.v.x = sorted_corners.rbegin()->second.x, seg.line.v.y = sorted_corners.rbegin()->second.y ;
				segments.push_back(seg) ;
			}  // for all lines
		}
		*/



		//
		// now select only those lines that belong to the chessboard
		//

		// 
		// collect all the intersections
		//
		intersection_list_type intersections ;
		{
			Intersection pt ;
			T pi2 = const_pi<T>()()/2, pi4 = pi2/2 ;

			// find all intersections
			for ( normal_line_container_type::iterator l1 = lines_.lines_.begin() ; l1 != lines_.lines_.end() ; ++l1 ) {
				normal_line_container_type::iterator l2 = l1 ;
				for ( ++l2 ; l2 != lines_.lines_.end() ; ++l2 ) {
					// find intersection
					if ( !ln_sect(*l1,*l2,pt) )
						continue ;
					if ( pt.x < 40 || pt.x >= width-40 || pt.y < 40 || pt.y >= height-40 )
						continue ;

					if ( l1->t > pi4 && l1->t <= pi4+pi2 )
						pt.hl = *l1, pt.vl = *l2 ;
					else
						pt.vl = *l1, pt.hl = *l2 ;

					intersections.push_back(pt) ;
				}
			}
		}


		// now, that we have intersections, verify that they are indeed chessboard corners
		// we filter out everything else
		// the criterias are:
		// 1. intersection should be around 90 degree
		// 2. the color should be black and white (dark/light)
		// 3. the point is outside of the line segment
		intersection_list_type corners ;
		{
			// check max value
			int image_min = image[0], image_max = image[0] ;
			const image_type *p = image ;
			for ( int i = 0 ; i < total ; ++i, ++p ) {
				if ( *p < image_min )
					image_min = *p ;
				if ( *p > image_max )
					image_max = *p ;
			}

			T pi = const_pi<T>()() ;

			for ( intersection_list_type::iterator c = intersections.begin(), c_end = intersections.end() ; c != c_end ; ++c ) {

				// filter out those too close to the border, we aren't looking for those
				if ( c->x < 40 || c->x >= width-40 || c->y < 40 || c->y >= height-40 )
					continue ;

				// 
				// 1. 90 degree stuff
				//
				if ( abs(abs(c->hl.t - c->vl.t) - pi/2)  > pi/20 )
					continue ;

				//
				// . check the segments (the intersection is outside)
				//


				// 
				// 2. color
				//
				{
					// get coordinates of 4 sample points
					// we get them by taking a vector and rotating among given direction
					T t[4] ;  // thetas
					APoint2D<T> s[4] ;
					multiset<int> b[4] ;  // overkill

					const int median_count = 20 ;

					int m[4][median_count] ; // 15 median values for each
					bool bad = false ; // the main flag

					t[0] = abs(c->hl.t + c->vl.t ) / 2 ;
					
					APoint2D<T> s0(20,0) ;

					for ( int i = 1 ; i < 4 ; ++i ) {
						t[i] = t[i-1] + pi/2 ;
						if ( t[i] > pi*2 )
							t[i] -= pi*2 ;
					}

					// translate every point
					for ( int i = 0 ; i < 4 ; ++i ) {
						pt_rot_2d(s0,t[i],s[i]) ;
						pt_trans_2d(s[i],*c) ;
					}

					// now get a box of 5x5=25 samples
					for ( int k = 0 ; k < 4 ; ++k ) {
						for ( int j = -2 ; j <= 2 ; ++j ) {
							for ( int i = -2 ; i <= 2 ; ++i ) {
								b[k].insert( image[(int(s[k].y)+j)*width + int(s[k].x)+i] ) ;
							}
						}
					}

					for ( int k = 0 ; k < 4 ; ++k ) {
						multiset<int>::iterator it = b[k].begin() ;
						for ( int i = 0 ; i < ((int)b[k].size()-median_count)/2 ; ++i )
							++it ;
						for ( int i = 0 ; i < median_count ; ++i )
							m[k][i] = *it++ ;
					}

					// now verify everything
					// . the color has to be uniform - no big difference
					//int color_diff = (image_max-image_min)/30 ;
					int min_color_diff = (image_max-image_min)/30 ;
					int max_color_diff = (image_max-image_min)/4 ;

					for ( int k = 0 ; k < 4 ; ++k ) {
						for ( int i = 1 ; i < median_count ; ++i )
							if ( abs(m[k][i]-m[k][i-1]) > max_color_diff )
								bad = true ;
					}

					// on the opposite sides the colors must be the same
					for ( int k = 0 ; k < 2 ; ++k ) {
						for ( int i = 0 ; i < median_count ; ++i )
							if ( abs(m[k][i]-m[k+2][i]) > max_color_diff )
								bad = true ;
					}

					// on the adjacent sides the color must be different
					// int color_diff = (image_max-image_min)/40 ;
					for ( int k = 1 ; k < 4 ; ++k ) {
						for ( int i = 0 ; i < median_count ; ++i )
							if ( abs(m[k][i]-m[k-1][i]) < min_color_diff )
								bad = true ;
					}

					// final decision
					if ( bad )
						continue ;
				}



				//
				// each intersection should be intersection of two lines
				// test for that
				vector<typename EdgeDetector<T>::edge_type> line_edges[2] ;

				int square_min_width = 60, square_min_height = 60 ;

				for ( EdgeDetector<T>::iterator e = lines_.edges_.begin(), e_end = lines_.edges_.end() ; e != e_end ; ++e ) {
					if ( pt_dist_2d<T>(*e,*c) < 5 )
						continue ;

					if ( pt_dist(*e,c->hl) <= lines_.point_dispersion_*2 && pt_dist_2d<T>(*e,*c) < square_min_width/2 )
						line_edges[0].push_back(*e) ;

					if ( pt_dist(*e,c->vl) <= lines_.point_dispersion_*2 && pt_dist_2d<T>(*e,*c) < square_min_height/2 )
						line_edges[1].push_back(*e) ;
				}

				// we must have certain amount of edge points around each intersection
				if ( (int)line_edges[0].size() < square_min_width - 20 || (int)line_edges[1].size() < square_min_height - 20 )
					continue ;



				corners.push_back(*c) ;
			}
			// corners = intersections ;
		}
		
		if ( corners.empty() )
			throw runtime_error("no corner detected") ;


		//
		// now that we have set of possible chessboard corners
		// select the ones that are best fit for a chessboard
		{
			//
			// try each point for being a corner the left point of chessboard, if chessboard is strictly vertical, then the lowest y can be selected
			// 
			Intersection left_corner ;
			intersection_list_type::iterator c = corners.begin(), c_end = corners.end() ;
			left_corner = *c++ ;
			for ( ; c != c_end ; ++c ) {
				if ( c->x < left_corner.x )
					left_corner = *c ;
			}

			// once we found the left corner, we can search for the lowest corner
			for ( intersection_list_type::iterator c = corners.begin(), c_end = corners.end() ; c != c_end ; ++c ) {
				if ( c->vl.r != left_corner.vl.r || c->vl.t != left_corner.vl.t )
					continue ;
				if ( c->y < left_corner.y )
					left_corner = *c ;
			}

			// 
			// now we follow both directions and collect all the corners among lines
			//
			// collect all the horizontal corners on the line
			// first sort them
			sorted_corner_list border_corners[2] ;  // 0 - horizontal, 1 - vertical

			for ( intersection_list_type::iterator c = corners.begin(), c_end = corners.end() ; c != c_end ; ++c ) {
				if ( c->hl.r == left_corner.hl.r && c->hl.t == left_corner.hl.t )
					border_corners[0].insert(sorted_corner_pair(pt_dist_2d<T>(*c,left_corner),*c)) ;
			}

			//if ( (int)hcorners.size() < chessboard_width - 1 )
			//	throw runtime_error("invalid chessboard") ;

			// the first row is ready
			// now for each element of first row rebuild the column
			for ( intersection_list_type::iterator c = corners.begin(), c_end = corners.end() ; c != c_end ; ++c ) {
				if ( c->vl.r == left_corner.vl.r && c->vl.t == left_corner.vl.t )
					border_corners[1].insert(sorted_corner_pair(pt_dist_2d<T>(*c,left_corner),*c)) ;
			}

			//
			// analyze the distribution of the points
			// the distribution must be linear
			// the angles must be same
			//
			// TODO: needed
			/*
			for ( int k = 0 ; k < 2 ; ++k ) {
				vector<T> ratios ;  // remember all the ratios and select the average
				sorted_corner_list::iterator c = border_corners[k].begin() ;
				Intersection p, q ;
				p = c->second, ++c ;
				q = c->second, ++c ;
				for ( ; c != border_corners[k].end() ; ++c ) {
					ratios.push_back(pt_dist_2d<T>(q,c->second)/pt_dist_2d<T>(p,q)) ;
					p = q, q = c->second ;
				}

				// determine average ratio
				ABuffer<T> rats((int)ratios.size()) ;
				int j = 0 ;
				for ( vector<T>::iterator rr = ratios.begin() ; rr != ratios.end() ; ++rr, ++j )
					rats[j] = *rr ;

				T average_ratio = median_quick_select(rats.get(),rats.size()) ;
				//for ( vector<T>::iterator r = ratios.begin(), r_end = ratios.end() ; r != r_end ; ++r ) 
				//	average_ratio += *r/T(ratios.size()) ;

				// now filter out those who are off
				vector<T>::iterator r = ratios.begin(), r_end = ratios.end(), r_next ;
				c = border_corners[k].begin(), ++c ;
				// T pr = *r++ ;
				for ( ; r != r_end ; ++r ) {
					if ( *r/average_ratio > 1.2 || *r/average_ratio < 0.8 ) {  // if we have to remove some intersection
						// do another test - which one to remove: the current or next
						c = border_corners[k].erase(c) ;
						++c ;  // skip next
						++r ;
						// r_next = r ;
						//++r_next ;
						//if ( r_next != r_end && abs(*r - average_ratio) < abs(*r_next - 
					}
				}

			}
			*/


			chessboard_.width = (int)border_corners[0].size() ;
			chessboard_.height = (int)border_corners[1].size() ;

			// collect all the intersections of horizontal and vertical selected lines
			for ( sorted_corner_list::iterator vc = border_corners[1].begin(), vc_end = border_corners[1].end() ; vc != vc_end ; ++vc ) {
				for ( sorted_corner_list::iterator hc = border_corners[0].begin(), hc_end = border_corners[0].end() ; hc != hc_end ; ++hc ) {
					// find intersection between current horizontal and vertical lines
					Intersection p ;
					ln_sect(vc->second.hl,hc->second.vl,p) ;
					p.xx = (int)p.x, p.yy = (int)p.y ;
					p.hl = vc->second.hl, p.vl = hc->second.vl ;
					chessboard_.intersections.push_back(p) ;
				}
			}

		}

		if ( chessboard_.width <= 1 || chessboard_.height <= 1 )
			throw runtime_error("chessboard not detected") ;



		//
		// Improve the accuracy of detected intersections
		//
		{
			// do LMeDS for each set of points and find intersection
			// find the smallest square size
			T square_min_width = pt_dist_2d<T>(chessboard_.intersections[0],chessboard_.intersections[1]) ;
			T square_min_height = pt_dist_2d<T>(chessboard_.intersections[0],chessboard_.intersections[chessboard_.width]) ;
			T t ;
			
			for ( int i = 2 ; i < chessboard_.width ; ++i ) {
				t = pt_dist_2d<T>(chessboard_.intersections[i-1],chessboard_.intersections[i]) ;
				if ( t < square_min_width )
					square_min_width = t ;
			}
			for ( int j = 2 ; j < chessboard_.height ; ++j ) {
				t = pt_dist_2d<T>(chessboard_.intersections[(j-1)*chessboard_.width],chessboard_.intersections[j*chessboard_.width]) ;
				if ( t < square_min_height )
					square_min_height = t ;
			}

			// now collect all the points that belong to the horizontal and vertical lines for each point
			vector<typename EdgeDetector<T>::edge_type> line_edges[2] ;
			ABuffer<T> x_buffer, y_buffer, lmeds_buffer ;

			for ( intersection_list_type::iterator p = chessboard_.intersections.begin() ; p != chessboard_.intersections.end() ; ++p ) {
				line_edges[0].clear(), line_edges[1].clear() ;

				for ( EdgeDetector<T>::iterator e = lines_.edges_.begin(), e_end = lines_.edges_.end() ; e != e_end ; ++e ) {
					if ( pt_dist_2d<T>(*e,*p) < 5 )
						continue ;

					if ( pt_dist(*e,p->hl) <= lines_.point_dispersion_ && pt_dist_2d<T>(*e,*p) < square_min_width/2 )
						line_edges[0].push_back(*e) ;

					if ( pt_dist(*e,p->vl) <= lines_.point_dispersion_ && pt_dist_2d<T>(*e,*p) < square_min_height/2 )
						line_edges[1].push_back(*e) ;
				}

				// now approximate the straight line
				Vec2<T> l[2][2] ;
				APoint2D<T> lp[2][2] ;
				for ( int i = 0 ; i < 2 ; ++i ) {
					int n = (int)line_edges[i].size() ;
					x_buffer.resize(n), y_buffer.resize(n), lmeds_buffer.resize(n) ;
					T *x = x_buffer.get(), *y = y_buffer.get() ;
					
					for ( vector<typename EdgeDetector<T>::edge_type>::iterator e = line_edges[i].begin(), e_end = line_edges[i].end() ; e != e_end ; ++e, ++x, ++y ) {
						//*x = e->x+0.5, *y = e->y+0.5 ;
						*x = e->x, *y = e->y ;
						int a = 0 ;
					}

					// TODO: figure why lmeds isn't working
					// lmeds_pca(x_buffer.get(),y_buffer.get(),n,l[i][0],l[i][1],lmeds_buffer.get()) ;
					//lp[i][0].x = l[i][0].a[0], lp[i][0].y = l[i][0].a[1] ;
					//lp[i][1].x = l[i][1].a[0], lp[i][1].y = l[i][1].a[1] ;

					lsm_pca(x_buffer.get(),y_buffer.get(),n,l[i][0],l[i][1]) ;

					lp[i][0].x = l[i][0].a[0], lp[i][0].y = l[i][0].a[1] ;
					lp[i][1].x = lp[i][0].x + l[i][1].a[0], lp[i][1].y = lp[i][0].y + l[i][1].a[1] ;
				}

				// find the intersection - this should be accurate
				ptln_sect_2d<T>(lp[0][0],lp[0][1],lp[1][0],lp[1][1],*p) ;
				p->xx = (int)p->x, p->yy = (int)p->y ;
				if ( p->xx < 0 || p->xx >= width || p->yy < 0 || p->yy >= height )
					throw runtime_error("invalid intersection") ;
			}

		}


		/*
		//
		// employ the harris corner detector to detect accurate corner positions
		//
		CornerDetector<T> corner_detector ;
		corner_detector.detect(image,width,height) ;


		//
		// Calculate accurate chessboard intersections
		//
		{
			// walk through all detected chessboard intersections and find 4 corners around it
			// then find intersection betwen these 4 corners - that's our chessboard
			// we search 4 corners by increasing the search window
			// if we reached max range - then something is wrong
			const int max_range = 30 ;
			for ( corner_list_type::iterator c = chessboard_.corners.begin() ; c != chessboard_.corners.end() ; ++c ) {
				int search_range = 3 ;
				const Corners<T>::corner_type *h = corner_detector.corners() ;
				Corners<T>::corner_type corners[4] ;
				int corner_count = 0 ;

				for ( ; search_range < max_range ; search_range++ ) {
					// horizontal
					for ( int i = -search_range ; i <= search_range ; ++i ) {
						if ( h[(int(c->y)-search_range)*width+int(c->x)+i].valid )
							corners[corner_count++] = h[(int(c->y)-search_range)*width + int(c->x)+i] ;
						if ( h[(int(c->y)+search_range)*width+int(c->x)+i].valid )
							corners[corner_count++] = h[(int(c->y)+search_range)*width + int(c->x)+i] ;
					}

					// left/right
					for ( int i = -search_range+1 ; i < search_range ; ++i ) {
						if ( h[(int(c->y)+i)*width+int(c->x)-search_range].valid )
							corners[corner_count++] = h[(int(c->y)+i)*width+int(c->x)-search_range] ;
						if ( h[(int(c->y)+i)*width+int(c->x)+search_range].valid )
							corners[corner_count++] = h[(int(c->y)+i)*width+int(c->x)+search_range] ;
					}

					if ( corner_count == 4 )
						break ;
				}

				if ( search_range == max_range )
					throw runtime_error("couldn't find corner near intersection") ;

				// now we have 4 corners, we have to find the ones that are crossed
				// we can do this by taking the cross product with intersection and figuring out the smallest
				Corners<T>::corner_type u[2], v[2] ;
				u[0] = corners[0], u[1] = corners[1] ;
				int cross_index = 1 ;
				T max_corner = abs((u[0].x-c->x)*(u[1].y-c->y) - (u[0].y-c->y)*(u[1].x-c->x)) ;
				for ( int i = 2 ; i < 4 ; ++i ) {
					T k = abs((u[0].x-c->x)*(corners[i].y-c->y) - (u[0].y-c->y)*(corners[i].x-c->x)) ;
					if ( k < max_corner ) {
						max_corner = k ;
						cross_index = i ;
						u[1] = corners[i] ;
					}
				}

				// now that we have 2 corners, we have to get the other two
				v[0] = cross_index == 2 ? corners[1] : corners[2] ;
				v[1] = cross_index == 3 ? corners[2] : corners[3] ;

				// now find the intersection between two lines - that's the chessboard intersection point.
				ptln_sect_2d<T> ( u[0], u[1], v[0], v[1], *c ) ;
			}
		}
		*/

	}


} ;


}


