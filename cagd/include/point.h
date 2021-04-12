/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   point.h
 * Author: aleksander
 *
 * Created on December 12, 2019, 9:16 PM
 */

#ifndef POINT_H
#define POINT_H

struct Point
{
	Point(float x, float y, float z):x(x),y(y),z(z)
	{
	}

	Point () : x(0), y(0), z(0) {}

	Point operator* (float d)
	{
		Point p = Point(x * d, y * d, z * d);
		return p;
	}

	Point operator+ (const Point &pt)
	{
		return Point(x + pt.x, y + pt.y, z + pt.z);
	}

	friend std::ostream& operator<<(std::ostream& os, const Point &pt)
	{
		os << ":" << pt.x << "," << pt.y << "," << pt.z << ":";
		return os;
	}

	float x;
	float y;
	float z;
};


#endif /* POINT_H */

