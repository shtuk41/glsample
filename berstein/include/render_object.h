/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rengerObject.h
 * Author: aleksander
 *
 * Created on December 12, 2019, 9:19 PM
 */

#ifndef RENGEROBJECT_H
#define RENGEROBJECT_H

class RenderObject
{
public:
	virtual void Draw() = 0;
	virtual ~RenderObject()
	{

	}
};



#endif /* RENGEROBJECT_H */

