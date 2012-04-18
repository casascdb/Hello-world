#ifndef PATHLOSSMODEL_H_
#define PATHLOSSMODEL_H_

#include <AnalogueModel.h>
#include <Mapping.h>
#include <BaseWorldUtility.h>
#include "MiXiMDefs.h"

#include <cstdlib>

class PathlossModel;

/**
 * @brief Mapping that represents a Pathloss-function.
 */
class PathlossConstMapping : public SimpleConstMapping
{

protected:
	PathlossModel* model;
	Coord myPos;
	Coord sendersPos;

public:
	/**
	 * @brief initializes the PathlossMapping
	 */
	PathlossConstMapping(PathlossModel* model,
						 const Argument& start,
						 const Coord& myPos,
						 const Coord& sendersPos) :
		SimpleConstMapping(DimensionSet(Dimension::time, Dimension("frequency")), start),
		model(model),
		myPos(myPos),
		sendersPos(sendersPos)
	{}

	/**
	 * @brief simply calculate and return attenuation value
	 */
	virtual double getValue(const Argument& pos) const;

	/**
	 * @brief creates a clone of this mapping. This method has to be implemented
	 * by every subclass. But most time the implementation will look like the
	 * implementation of this method (except of the class name).
	 */
	ConstMapping* constClone() const
	{
		return new PathlossConstMapping(*this);
	}

};


/**
 * @brief Basic implementation of a PathlossModel that uses
 * PathlossConstMapping (that is subclassed from SimpleConstMapping) as attenuation-Mapping.
 *
 */
class PathlossModel : public AnalogueModel
{
protected:
	friend class PathlossConstMapping;
	double carrierFreq;

	/** @brief Path loss coefficient. **/
    double pathLossAlphaHalf;

    /** @brief stores my Move pattern */

    /** const Move& myMove; **/

public:
	/**
	 * @brief Initializes the analogue model. myMove needs to be valid
	 * as long as this instance exists.
	 *
	 * The constructor needs some specific knowledge in order to create
	 * its mapping properly:
	 *
	 * 1. the coefficient alpha (specified e.g. in config.xml and passed
	 *    in constructor call)
	 * 2. the carrier frequency
	 * 3. a pointer to the hosts move pattern
	 */
	PathlossModel(double alpha):
		carrierFreq(2.4e9),
		pathLossAlphaHalf(alpha * 0.5)
	{}

	/**
	 * @brief Filters a specified Signal by adding an attenuation
	 * over time to the Signal.
	 */
	virtual void filterSignal(AirFrame *, const Coord&, const Coord&);
};

#endif /*PATHLOSSMODEL_H_*/
