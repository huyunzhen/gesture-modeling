/*
 * GestureLearner.h
 *
 * Sample class implementing comm functionality with MultitouchListener.
 *
 *  Created on: Mar 27, 2009
 *      Author: sashikanth
 */

#ifndef GESTURECOLLECTOR_H_
#define GESTURECOLLECTOR_H_

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <map>
#include <vector>
#include "touch/Touch.h"

using namespace std;
class GestureCollector
{
	bool appendFrames;
public:
	typedef map<string, vector<double> > paramValMapT;

	GestureCollector()
	{
	}
	~GestureCollector()
	{
	}
	GestureSample currGestureSegment;
	string gestureName;
	std::vector<GestureSample> samples;

	void updateFrame(ContactSetFrame frame)
	{
//		//If we are saving a segment, ensure subsequent frame has same number of fingers.
//		if(currGestureSegment.size() > 1 && currGestureSegment.lastFrameSize() != frame.size())
//			return; //Ignore frames with different number of fingers.
		if(appendFrames)
		{
			currGestureSegment.push_back(frame);
			//cout << "frame added: " << currGestureSegment.size() << endl;
		}
	}

	void endSample()
	{
		appendFrames = false;

		if(currGestureSegment.size() > 0)
		{
			samples.push_back(currGestureSegment);
			cout << "Collected: " << samples.size() << " samples. Last sample size:" << currGestureSegment.size();
			cout << " Number of fingers: " << currGestureSegment.numFingers() << endl;
			//currGestureSegment.printSample();

		}
	}

	void clearSample()
	{
		currGestureSegment.clear();
		appendFrames = false;
	}

	void startSample(const char* gestName)
	{
		//clear sample and start appending frames
		gestureName = gestName;
		//cout << "Start Sample, Had frames: " << currGestureSegment.size() << endl;
//		for(size_t i = 0; i < currSample.size(); i++)
//			cout << "\t" << i << ": " << currSample.sample[i].size() << endl;
		currGestureSegment.clear();
		appendFrames = true;
	}

	/**
	 * The sample currently in the buffer has stopped moving.
	 * Check last frame with previous n frames with a tolerance.
	 */
	bool sampleIsNowStatic()
	{
		return currGestureSegment.checkIfStaticAndTrimFrames(10);
	}

	/**
	 * If the sample consists only of static frames.
	 */
	bool sampleIsOnlyStatic()
	{
		return currGestureSegment.checkIfOnlyStaticAndTrim();
	}
	size_t sampleSize()
	{
		return currGestureSegment.size();
	}
	/*
	 * Default implementation of gesture actions
	 */
	virtual vector<string> gestureAction(const char* actionString, vector<string> actionParams)
	{
		return vector<string>();
	}

	virtual paramValMapT parameterize()
	{
		return paramValMapT();
	}
	virtual bool isCurrentlyParameterized(){ return false; }
	virtual void unParameterize(){}
	virtual bool isParameterizationPaused(){ return false;}
	virtual void unpauseParameterization(){}
	virtual void pauseParameterization(){}
};
#endif /* GESTURELEARNER_H_ */
