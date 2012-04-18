/*
 * MyPhyLayer.h
 *
 *  Created on: 23.02.2009
 *      Author: karl
 */

#ifndef MYPHYLAYER_H_
#define MYPHYLAYER_H_

#include <PhyLayer.h>
#include "RandomFading.h"
#include "PathlossModel.h"

class MyPhyLayer: public PhyLayer {
protected:
	virtual AnalogueModel* getAnalogueModelFromName(std::string name, ParameterMap& params) const{

		if(name == "RandomFading")
		{
			simtime_t accuracy = params["accuracy"].doubleValue();
			double min = params["min"].doubleValue();
			double max = params["max"].doubleValue();

			return new RandomFading(accuracy, min, max);
		}
		else if(name =="PathlossModel")
		{
			// init with default value
			double alpha = params["alpha"];

			return new PathlossModel(alpha);
		}

		return PhyLayer::getAnalogueModelFromName(name, params);
	}
};

#endif /* MYPHYLAYER_H_ */
