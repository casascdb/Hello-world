/*
 * RandomFading.h
 *
 *  Created on: 23.02.2009
 *      Author: karl
 */

#ifndef RANDOMFADING_H_
#define RANDOMFADING_H_

#include <AnalogueModel.h>

class RandomFading: public AnalogueModel {

protected:
    simtime_t accuracy;
    double min;
    double max;

protected:
    double getRandomAtt() {
        return 1.0 - (dblrand() * (max - min) + min);
    }

public:
    RandomFading(simtime_t accuracy, double min, double max):
        accuracy(accuracy * 0.001),
        min(min),
        max(max)
    {}

    virtual void filterSignal(AirFrame *frame, const Coord& sendersPos, const Coord& receiverPos)
    {
        Signal& signal = frame->getSignal();

        simtime_t start = signal.getReceptionStart();
        simtime_t end = start + signal.getDuration();

        Mapping* att = MappingUtils::createMapping(DimensionSet(Dimension::time), Mapping::LINEAR);

        for(simtime_t t = start; t < end; t += accuracy) {
            att->appendValue(Argument(t), getRandomAtt());
        }
        att->appendValue(Argument(end), getRandomAtt());

        signal.addAttenuation(att);
    }
};

#endif /* RANDOMFADING_H_ */
