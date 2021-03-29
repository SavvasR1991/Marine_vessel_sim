/****************************************************************************
 * Copyright (c) 2015 VT MAK
 * All rights reserved.
 ****************************************************************************/

 //Project include
#include "OCEAN2020FOMf18Init.h"

//VRLINK include
#include <matrix/geodeticCoord.h>
#include <matrix/vlVector.h>
#include <stdio.h>
#include <vlpi/disEnums.h>

// Constructor -- Initialize the base class (will initialize protocol-specific
// parameters), command line arguments and mtl parameters
DtF18Initializer::DtF18Initializer(int argc, char* argv[], DtString appName, double lat , double lon)
	: DtVrlApplicationInitializer(argc, argv, appName)
	, myInitialPosition(mySettings, "initialPosition", DtVector(0.0, 0.0, -1230.0),
		"Initial Location", DtBaseConfigVariable::DtScopeBoth, false, "L")
	, myLispFileName(mySettings, "&lispFile", "f18.xml", "LISP File Name")
	, myDeadReckonAlgorithm(mySettings, "deadReckonAlgorithm", DtDrDrmRvw, "Dead Reckon Algorithm",
		DtBaseConfigVariable::DtScopeBoth, false, "D")
	, myInitialTurnRadius(mySettings, "initialTRadius", -250.0, "Initial Turn Radius",
		DtBaseConfigVariable::DtScopeBoth, false, "r")
	, myInitialSpeed(mySettings, "initialSpeed", 40.0, "Initial Speed")
	, myEntityTypeString(mySettings, "entity&TypeStr", "1:2:225:1:9:0:0", "Entity Type String")
	, myMarkings(mySettings, "f18&Markings", "MAK-VRLink-F18", "F18 Markings")
	, myName(mySettings, "f18Name", "MaK-F18", "F18 Object Name")
	, myDestroyedToFinalDelay(mySettings, "&destroyedToFinalDelay", 20.0,
		"Destroyed To Final Delay")
	, myInitialHeading(mySettings, "initial&Heading", 180.0, "Initial Heading")
	, myTopoOrigin(mySettings, "topo&Origin", "35.699760,-121.326577",
		"Topographic Coordinate System Origin")
	, myWorldPosition(mySettings, "worldPos", DtVector(0.0, 0.0, 0.0),
		"Initial Position in Geocentric Coordinates", DtBaseConfigVariable::DtScopeBoth, false, "W")
	, myLethalDetonationRange(mySettings, "lethalDetonationRange", 20.0, "Lethal Detonation Range",
		DtBaseConfigVariable::DtScopeConfigFile)
	, myMunitionFlightTime(mySettings, "munitionFlightTime", 3.0, "Munition Flight Time",
		DtBaseConfigVariable::DtScopeConfigFile)
	, myInitialPitch(mySettings, "initialPitch", 0.0, "Initial Pitch",
		DtBaseConfigVariable::DtScopeConfigFile)
	, myInitialRoll(mySettings, "initialRoll", 0.0, "Initial Roll",
		DtBaseConfigVariable::DtScopeConfigFile)
	, myAutoRoll(mySettings, "autoRoll", true, "Auto Roll",
		DtBaseConfigVariable::DtScopeConfigFile)
	, myEntityNumber(mySettings, "entNum", 1, "Entity Number",
		DtBaseConfigVariable::DtScopeConfigFile)
	, myHaveArtParts(mySettings, "haveArtParts", false, "Have Articulated Parts",
		DtBaseConfigVariable::DtScopeConfigFile)
	, myRefLatitude(mySettings, "refLatitude", 35.699760, "Reference Latitude",
		DtBaseConfigVariable::DtScopeConfigFile)
	, myRefLongitude(mySettings, "refLongitude", -121.326577, "Reference Longitude",
		DtBaseConfigVariable::DtScopeConfigFile)
	, myDeltaTime(mySettings, "deltaTime", 0.05, "Delta Time",
		DtBaseConfigVariable::DtScopeConfigFile)
#ifdef DtHLA_1516_EVOLVED
	, mySuppressDefaultModules(mySettings, "suppressDefaultModules", false, "Suppress Default Modules (HLA1516-2010 only)",
		DtBaseConfigVariable::DtScopeBoth)
#endif
	, myMtlAutoRoll(1)
#if DtHLA
	, myConfigVarApplicationNumber(mySettings, "&appNumber", 2, "Application Number")
	, mySiteId(mySettings, "&siteId", 1, "Site ID")
#endif
	, myMtlHaveArtParts(0)
	, myMtlInitialPosition(0.0, 0.0, -1230.0)
{
	mySettings.setChangeOnce(true);
}

DtF18Initializer::~DtF18Initializer()
{
}

void DtF18Initializer::initializeMtlParams()
{
	DtVrlApplicationInitializer::initializeMtlParams();
	myMtlEnv->registerConfigVar(myDeadReckonAlgorithm);
	myMtlEnv->registerConfigVar(myInitialTurnRadius);
	myMtlEnv->registerConfigVar(myInitialSpeed);
	myMtlEnv->registerConfigVar(myInitialHeading);
	myMtlEnv->registerConfigVar(myEntityTypeString);
	myMtlEnv->registerConfigVar(myMarkings);
	myMtlEnv->registerConfigVar(myName);
	myMtlEnv->registerConfigVar(myDestroyedToFinalDelay);
	myMtlEnv->registerConfigVar(myLethalDetonationRange);
	myMtlEnv->registerConfigVar(myMunitionFlightTime);
	myMtlEnv->registerConfigVar(myInitialPitch);
	myMtlEnv->registerConfigVar(myInitialRoll);
	myMtlEnv->registerConfigVar(myEntityNumber);
	myMtlEnv->registerConfigVar(myRefLatitude);
	myMtlEnv->registerConfigVar(myRefLongitude);
	myMtlEnv->registerConfigVar(myDeltaTime);
	//myMtlEnv->registerConfigVar( mySuppressDefaultModules );
	myMtlEnv->registerVar("autoRoll", &myMtlAutoRoll);
	myMtlEnv->registerVar("haveArtParts", &myMtlHaveArtParts);
	myMtlEnv->registerVar("initialPos[0]", &myMtlInitialPosition[0]);
	myMtlEnv->registerVar("initialPos[1]", &myMtlInitialPosition[1]);
	myMtlEnv->registerVar("initialPos[2]", &myMtlInitialPosition[2]);
#if DtHLA
	myMtlEnv->registerConfigVar(myConfigVarApplicationNumber);
	myMtlEnv->registerConfigVar(mySiteId);
#endif
}

// Parses the command line
void DtF18Initializer::parseCmdLine()
{
	// Note that we're manually parsing the command line here in order to
	// see whether a file has been specified.  This is due to the support of
	// MTL files.  If the command line is parsed, and then an MTL file is loaded,
	// the command line values will be overridden.  This is not the case with XML.
	// As long as "changeOnce" is set to true on the application settings object,
	// values can only be changed once.  In other words, if the command line is parsed,
	// and values are set, and a file is then loaded, the values set by the command
	// line will not be overridden.  This is not the case with MTL yet.
	for (int index = 1; index < myArgc; ++index)
	{
		if (!strcmp(myArgv[index], "-l") || !strcmp(myArgv[index], "--lispFile"))
		{
			if (index + 1 < myArgc)
			{
				myLispFileName.setValue(myArgv[index + 1]);
				break;
			}
		}
	}

	loadFile(myLispFileName.value());

	DtVrlApplicationInitializer::parseCmdLine();

	if (myInitialPosition.isSet())
	{
		// NOTE: only -L specifies X, Y, and -Z (north, east, and up)
		// All local positions are north, east, down [not up]
		DtVector posVec = myInitialPosition.value();
		posVec[2] = -posVec[2];
		myInitialPosition.setValue(posVec);
	}

	if (myTopoOrigin.isSet())
	{
		double refLat = myRefLatitude.defaultValue();
		double refLon = myRefLongitude.defaultValue();
		int numReads = sscanf(myTopoOrigin.value().c_str(), "%lf,%lf", &refLat, &refLon);
		if (numReads > 0)
		{
			myRefLatitude.setValue(refLat);
			if (numReads > 1)
			{
				myRefLongitude.setValue(refLon);
			}
		}
	}

	if (myWorldPosition.isSet())
	{
		DtGeodeticCoord initPos;
		initPos.setGeocentric(myWorldPosition.value());
		myRefLatitude.setValue(DtRad2Deg(initPos.lat()));
		myRefLongitude.setValue(DtRad2Deg(initPos.lon()));
	}
}

//--------------------------------------------------------------
//    ACCESSORS/MODIFIERS
//    Provide a way to inspect/modify the data
//--------------------------------------------------------------

void DtF18Initializer::setInitialPosition(const DtVector& loc)
{
	myInitialPosition.setValue(loc);
}

DtVector DtF18Initializer::initialPosition() const
{
	return myInitialPosition.value();
}

void DtF18Initializer::setLispFileName(const DtString& name)
{
	myLispFileName.setValue(name);
}

DtString DtF18Initializer::lispFileName() const
{
	return myLispFileName.value();
}

void DtF18Initializer::setDeadReckonAlgorithm(unsigned long alg)
{
	myDeadReckonAlgorithm.setValue(alg);
}

unsigned long DtF18Initializer::deadReckonAlgorithm() const
{
	return myDeadReckonAlgorithm.value();
}

void DtF18Initializer::setInitialTurnRadius(double radius)
{
	myInitialTurnRadius.setValue(radius);
}

double DtF18Initializer::initialTurnRadius() const
{
	return myInitialTurnRadius.value();
}

void DtF18Initializer::setInitialSpeed(double speed)
{
	myInitialSpeed.setValue(speed);
}

double DtF18Initializer::initialSpeed() const
{
	return myInitialSpeed.value();
}

void DtF18Initializer::setEntityTypeStr(const DtString& type)
{
	myEntityTypeString.setValue(type);
}

DtString DtF18Initializer::entityTypeStr() const
{
	return myEntityTypeString.value();
}

void DtF18Initializer::setF18Markings(const DtString& markings)
{
	myMarkings.setValue(markings);
}

DtString DtF18Initializer::f18Markings() const
{
	return myMarkings.value();
}

void DtF18Initializer::setF18Name(const DtString& name)
{
	myName.setValue(name);
}

DtString DtF18Initializer::f18Name() const
{
	return myName.value();
}

void DtF18Initializer::setDestroyedToFinalDelay(double delay)
{
	myDestroyedToFinalDelay.setValue(delay);
}

double DtF18Initializer::destroyedToFinalDelay() const
{
	return myDestroyedToFinalDelay.value();
}

void DtF18Initializer::setInitialHeading(double heading)
{
	myInitialHeading.setValue(heading);
}

double DtF18Initializer::initialHeading() const
{
	return myInitialHeading.value();
}

void DtF18Initializer::setLethalDetonationRange(double range)
{
	myLethalDetonationRange.setValue(range);
}

double DtF18Initializer::lethalDetonationRange() const
{
	return myLethalDetonationRange.value();
}

void DtF18Initializer::setMunitionFlightTime(double time)
{
	myMunitionFlightTime.setValue(time);
}

double DtF18Initializer::munitionFlightTime() const
{
	return myMunitionFlightTime.value();
}

void DtF18Initializer::setInitialPitch(double pitch)
{
	myInitialPitch.setValue(pitch);
}

double DtF18Initializer::initialPitch() const
{
	return myInitialPitch.value();
}

void DtF18Initializer::setInitialRoll(double roll)
{
	myInitialRoll.setValue(roll);
}

double DtF18Initializer::initialRoll() const
{
	return myInitialRoll.value();
}

void DtF18Initializer::setAutoRoll(bool onOff)
{
	myAutoRoll.setValue(onOff);
}

bool DtF18Initializer::autoRoll() const
{
	return myAutoRoll.value();
}

void DtF18Initializer::setEntityNumber(int number)
{
	myEntityNumber.setValue(number);
}

int DtF18Initializer::entityNumber() const
{
	return myEntityNumber.value();
}

void DtF18Initializer::setRefLatitude(double lat)
{
	myRefLatitude.setValue(lat);
}

double DtF18Initializer::refLatitude() const
{
	return myRefLatitude.value();
}

void DtF18Initializer::setRefLongitude(double lon)
{
	myRefLongitude.setValue(lon);
}

double DtF18Initializer::refLongitude() const
{
	return myRefLongitude.value();
}

void DtF18Initializer::setHaveArtParts(bool onOff)
{
	myHaveArtParts.setValue(onOff);
}

bool DtF18Initializer::haveArtParts() const
{
	return myHaveArtParts.value();
}

void DtF18Initializer::setDeltaTime(DtTime time)
{
	myDeltaTime.setValue(time);
}

DtTime DtF18Initializer::deltaTime() const
{
	return myDeltaTime.value();
}

#ifdef DtHLA_1516_EVOLVED
void DtF18Initializer::setSuppressDefaultModules(bool onOff)
{
	mySuppressDefaultModules.setValue(onOff);
}
bool DtF18Initializer::suppressDefaultModules()
{
	return mySuppressDefaultModules.value();
}
#endif

void DtF18Initializer::loadMtlFile(const DtString& fileName)
{
	DtVrlApplicationInitializer::loadMtlFile(fileName);
	setAutoRoll(myMtlAutoRoll);
	setHaveArtParts(myMtlHaveArtParts);
	setInitialPosition(myMtlInitialPosition);
}

#if DtHLA
void DtF18Initializer::setApplicationNumber(int num)
{
	myConfigVarApplicationNumber.setValue(num);
}

int DtF18Initializer::applicationNumber() const
{
	return myConfigVarApplicationNumber.value();
}

void DtF18Initializer::setSiteId(int id)
{
	mySiteId.setValue(id);
}

int DtF18Initializer::siteId() const
{
	return mySiteId.value();
}

#endif
