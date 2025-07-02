/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
/*
	converts file with 3D points into x3d format
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <istream>
#include <ostream>
#include <stdexcept>

#include <geo/box.cxx>
#include <geo/point.cxx>

#include <mat/func.cxx>
#include <mat/vector.cxx>


typedef double T ;


void process ( std::istream *input, std::ostream *output )
{
	using namespace geo ;
	using namespace mat ;
	
	// load all the data
	typedef AVector4<T> point_type ;
	typedef std::vector<point_type> pts_list_type ;
	
	pts_list_type pts ;
	
	point_type p ;
	
	p.a[3] = 1 ;

	while ( !input->eof() && input->good() ) {
	
		(*input) >> p.a[0] ;
		(*input) >> p.a[1] ;
		(*input) >> p.a[2] ;
		
		pts.push_back(p) ;
	}
	
	
	
	// do some calculations
	ABox<T> bounding_box = { { 0,0,0 }, { 0, 0, 0 } } ;
	APoint3D<T> centroid ;
	
	{
		T n = T(pts.size()) ;
		
		for ( pts_list_type::iterator p = pts.begin() ; p != pts.end() ; ++p ) {
			
			if ( p == pts.begin() ) {
				for ( int i = 0 ; i < 3 ; ++i )
					bounding_box.mn.a[i] = bounding_box.mx.a[i] = p->a[i] ;
			}
			
			for ( int i = 0 ; i < 3 ; ++i ) {
				if ( p->a[i] < bounding_box.mn.a[i] )
					bounding_box.mn.a[i] = p->a[i] ;
				if ( p->a[i] > bounding_box.mx.a[i] )
					bounding_box.mx.a[i] = p->a[i] ;
			}
			
			centroid.x += p->a[0]/n, centroid.y += p->a[1]/n, centroid.z += p->a[2]/n ;
		}		
	}
	
	
	// generate x3d
	{
		std::ostream &x3d = *output ;
		const char t = '\t', n = '\n' ;
		
		x3d << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << n ;
		x3d << "<!DOCTYPE X3D PUBLIC \"ISO//Web3D//DTD X3D 3.0//EN\" \"http://www.web3d.org/specifications/x3d-3.0.dtd\">" << n ;
		x3d << "<X3D profile='Interchange' version='3.0' xmlns:xsd='http://www.w3.org/2001/XMLSchema-instance' xsd:noNamespaceSchemaLocation=' http://www.web3d.org/specifications/x3d-3.0.xsd '>" << n ;
		
		x3d << "<head>" << n ;
		x3d << "</head>" << n ;
		
		x3d << "<Scene>" << n ;
		//x3d << t << "<NavigationInfo type='&quot;EXAMINE&quot; &quot;ANY&quot;' />" << n ;
		
		// calculate the front view, so we can see the whole object at pi/4 degree
		T pi = const_pi<T>()() ;
		T fov = pi/4 ;
		T view_x = mat::max(bounding_box.mx.a[0],bounding_box.mn.a[0])*2 ;
		T view_y = mat::max(bounding_box.mx.a[1],bounding_box.mn.a[1])*2 ;
		T dist = mat::max(view_x/2/tan(fov/2),view_y/2/tan(fov/2)) ;
		
		// add closes z coordinate
		//dist += 
		
		// scale everything to meters
		T scale = 1 ; //T(1000)/mat::max(view_x,view_y) ;
				
		x3d << t << "<Transform translation='0 0 0' scale='" << scale << " " << scale << " " << scale << "' >" << n ;
		
		//x3d << t << "<Viewpoint DEF='default_view' description='Default View' />" << n ;
		x3d << t << "<Viewpoint DEF='front_view' description='Front View' position='0 0 " << dist << "'" ;
		x3d << " centerOfRotation='" << centroid.x << ' ' << centroid.y << ' ' << centroid.z - dist << "'" ;
				
 		x3d << "/>" << n ;
		
		
		x3d << t << "<Shape>" << n ;
		x3d << t << t << "<PointSet>" << n ;
		//x3d << t << t << t << "<Color" << "/>" << n ;
		x3d << t << t << t << "<Coordinate" << " DEF='contour_pts'" ;
		x3d << " point='" ;
		bool was = false ;
		for ( pts_list_type::iterator p = pts.begin() ; p != pts.end() ; ++p ) {
			if ( was )
				x3d << ", " ;
			x3d << p->a[0] << ' ' << -p->a[1] << ' ' << -p->a[2] ;
			was = true ;
		}
		x3d << "' " ;
		x3d << "/>" << n ;
		x3d << t << t << "</PointSet>" << n ;
		x3d << t << "</Shape>" << n ;
		
		//x3d << t << "<Transform" << " scale='1000'" << "/>" << n ;
		//x3d << t << "<Transform" << " translation='2 0 0'" << "/>" << n ;
		
	
		x3d << t << "</Transform>\n" << n ;
		x3d << "</Scene>" << n ;
		
		x3d << "</X3D>" << n ;
	}
}



int main(int argc, char *argv[])
{
	using namespace std ;
	
	int ret_code = 1 ;
	
	string input_file ;
	
	try {
		if ( argc > 1 )
			input_file = argv[1] ;
		
		
		if ( !input_file.empty() ) {
			ifstream input(input_file.c_str(),ifstream::in) ;
			
			if ( input.fail() )
				throw runtime_error("cannot open input file") ;
			
			process(&input,&cout) ;
		} else {
			process(&cin,&cout) ;
		} 
		
		
		ret_code = 0 ;
	}
	catch(exception &e) {
		cerr << e.what() << endl ;
	}
	catch(...) {
		cerr << "exception!" << endl ;
	}
	
	return ret_code ;	
}
