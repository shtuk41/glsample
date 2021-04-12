/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   bcurve.h
 * Author: aleksander
 *
 * Created on December 12, 2019, 9:21 PM
 */

#ifndef DE_CASTELJAU_BCURVE_H
#define DE_CASTELJAU_BCURVE_H


class de_Casteljau_BCurve 
{
private:
    std::vector<Point> controlPoints;
    int numberOfPoints;
    int numberOfEdges;
    
    Point FindPoint(int level, int elem, int order)
    {
        double delta = 1.0 / (numberOfPoints - 1);
        double t = delta * elem;
        
        if (level > 0)
        {
            Point p1 = FindPoint(level - 1, elem, order + 0); 
            Point p2 = FindPoint(level - 1, elem, order + 1); 
            
            Point p = p1 * (1.0 - t) + p2 * t;
            return p;
        }
        else
        {
            Point p = controlPoints[0 + order] * (1.0 - t) + controlPoints[1 + order] * t;
            return p;
        }
    }
    
public:
    de_Casteljau_BCurve(std::vector<Point> control_points, int number_points) : controlPoints(control_points), numberOfPoints(number_points)
    {
        numberOfEdges = control_points.size() - 1;
    }
        
    Point operator [](int element)
    {
        if (element < 0 || element >= numberOfPoints)
        {
            throw BCurveElementOutOfBoundException();
        }
            
        Point p = FindPoint(numberOfEdges - 1, element, 0);
        
        return p;
    }
};



#endif /* DE_CASTELJAU_BCURVE_H */

