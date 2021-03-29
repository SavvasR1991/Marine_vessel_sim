/*******************************************************************************
** Copyright (c) 1992-2010 VT MAK
** All rights reserved.
*******************************************************************************/
//! \file f18Init.h
//! \ingroup Examples

#pragma once

//VRLINK include
#include <matrix/vlVector.h>
#include <mtl/configVariable.h>
#include <mtl/mtlEnvironment.h>
#include <vl/exerciseConnInitializer.h>
#include <vlutil/vlString.h>

class DtMtlEnvironment;

//! DtF18Initializer derives from DtVrlApplicationInitializer and
//! describes how command line/MTL parameters could be added to
//! a VR-Link application.  DtVrlApplicationInitializer contains
//! default behavior for protocol specific parameters, while 
//! DtF18Initializer contains behavior particular to the F18 app
//! parseCmdLine() parses the command line arguments specified in
//! this class and DtVrlApplicationInitializer.  loadMtlFile() can be
//! called (defined in DtVrlApplicationInitializer) with an MTL file name.
//! This will parse the MTL file specified and set those variables registered
//! \ingroup Examples
class DtF18Initializer : public DtVrlApplicationInitializer
{
public:

	//! Default CTOR
	DtF18Initializer(int argc, char* argv[], DtString AppName,double, double);

	//! Default DTOR
	virtual ~DtF18Initializer();

private:

	//! Copy CTOR not implemented -- Do Not copy.
	DtF18Initializer(const DtF18Initializer& other);

	//! Assignment Operator  not implemented -- Do Not copy.
	DtF18Initializer &operator=(const DtF18Initializer &other);

public:

	virtual void parseCmdLine();
	virtual void initializeMtlParams();

	//! Accessors/Modifiers for our cmd line values
	virtual void setInitialPosition(const DtVector& loc);
	virtual DtVector initialPosition() const;

	virtual void setLispFileName(const DtString& name);
	virtual DtString lispFileName() const;

	virtual void setDeadReckonAlgorithm(unsigned long alg);
	virtual unsigned long deadReckonAlgorithm() const;

	virtual void setInitialTurnRadius(double radius);
	virtual double initialTurnRadius() const;

	virtual void setInitialSpeed(double speed);
	virtual double initialSpeed() const;

	virtual void setEntityTypeStr(const DtString& type);
	virtual DtString entityTypeStr() const;

	virtual void setF18Markings(const DtString& markings);
	virtual DtString f18Markings() const;

	virtual void setF18Name(const DtString& name);
	virtual DtString f18Name() const;

	virtual void setDestroyedToFinalDelay(double delay);
	virtual double destroyedToFinalDelay() const;

	virtual void setInitialHeading(double heading);
	virtual double initialHeading() const;

	//! Accessors/Modifiers for MTL only parameters
	virtual void setLethalDetonationRange(double range);
	virtual double lethalDetonationRange() const;

	virtual void setMunitionFlightTime(double time);
	virtual double munitionFlightTime() const;

	virtual void setInitialPitch(double pitch);
	virtual double initialPitch() const;

	virtual void setInitialRoll(double roll);
	virtual double initialRoll() const;

	virtual void setAutoRoll(bool onOff);
	virtual bool autoRoll() const;

	virtual void setEntityNumber(int number);
	virtual int entityNumber() const;

	virtual void setHaveArtParts(bool onOff);
	virtual bool haveArtParts() const;

	virtual void setDeltaTime(DtTime time);
	virtual DtTime deltaTime() const;

#ifdef DtHLA_1516_EVOLVED
	virtual void setSuppressDefaultModules(bool onOff);
	virtual bool suppressDefaultModules();
#endif

	//! Ref latitude and longitude can be set individually by MTL or by a 
	//! string in the command line
	virtual void setRefLatitude(double lat);
	virtual double refLatitude() const;

	virtual void setRefLongitude(double lon);
	virtual double refLongitude() const;

	//! These are parameters used by the F18 that are defined in the DIS
	//! DtVrlApplicationInitializer, but not the HLA version, so define them
	//! for HLA here
#if DtHLA
	virtual void setApplicationNumber(int num);
	virtual int applicationNumber() const;

	virtual void setSiteId(int id);
	virtual int siteId() const;
#endif

protected:
	virtual void loadMtlFile(const DtString& fileName);


protected:
	DtConfigVariable<DtVector> myInitialPosition;
	DtConfigVariable<DtString> myLispFileName;
	DtConfigVariable<int>      myDeadReckonAlgorithm;
	DtConfigVariable<double>   myInitialTurnRadius;
	DtConfigVariable<double>   myInitialSpeed;
	DtConfigVariable<DtString> myEntityTypeString;
	DtConfigVariable<DtString> myMarkings;
	DtConfigVariable<DtString> myName;
	DtConfigVariable<double>   myDestroyedToFinalDelay;
	DtConfigVariable<double>   myInitialHeading;
	DtConfigVariable<DtString> myTopoOrigin;
	DtConfigVariable<DtVector> myWorldPosition;
	DtConfigVariable<double>   myLethalDetonationRange;
	DtConfigVariable<double>   myMunitionFlightTime;
	DtConfigVariable<double>   myInitialPitch;
	DtConfigVariable<double>   myInitialRoll;
	DtConfigVariable<bool>     myAutoRoll;
	DtConfigVariable<int>      myEntityNumber;
	DtConfigVariable<bool>     myHaveArtParts;
	DtConfigVariable<double>   myRefLatitude;
	DtConfigVariable<double>   myRefLongitude;
	DtConfigVariable<double>   myDeltaTime;
#ifdef DtHLA_1516_EVOLVED
	DtConfigVariable<bool>     mySuppressDefaultModules;
#endif
#if DtHLA
	//! This is already in the DIS base-class... For the F18,
	//! make one for HLA
	DtConfigVariable<int> myConfigVarApplicationNumber;
	DtConfigVariable<int> mySiteId;
#endif

	int myMtlAutoRoll;
	int myMtlHaveArtParts;
	DtVector myMtlInitialPosition;
};



