// Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
// This file defines the common data structures used in the interface
// to the LBS protocol module. 
// 
//

/**
 @file
 @publishedPartner
 @released
*/

#ifndef LBSNETCOMMON_H_
#define LBSNETCOMMON_H_

#include <lbs.h>
#include <lbs/lbsassistancedatabase.h>

/**
The maximum number of supported positioning protocols

@see TLbsNetPosCapabilities::SetPosProtocols
*/
const TInt KLbsMaxNetPosProtocols = 10;

/**
The maximum number of supported positioning methods 
@see TLbsNetPosCapabilities::SetPosMethods
*/
const TInt KLbsMaxNetPosMethods   = 10;

/**
The maximum number of concurrent positioning sessions

@see TLbsNetSessionIdArray

@publishedPartner
@released
*/
const TInt KLbsMaxNetSessions = 10;

/**
GPS positioning means

This is the only means supported

@see TLbsNetPosMethod::TLbsNetPosMethod
@see TLbsNetPosMethod::PosMeans
*/
const TUid KLbsPositioningMeansGps   = { 0x10282295 };

/**
Cell positioning means

Not supported
*/
const TUid KLbsPositioningMeansCell  = { 0x10282296 };

/**
EOTD positioning means

Not supported
*/
const TUid KLbsPositioningMeansEotd  = { 0x10282297 };

/**
OTDOA positioning means

Not supported
*/
const TUid KLbsPositioningMeansOtdoa = { 0x10282298 };

/**
AFLT positioning means

Not supported
*/
const TUid KLbsPositioningMeansAflt  = { 0x10282299 };


const TUid KLbsPositioningMeansNone  = { 0x1028229A };

/**
The generic base for classes that store Lbs network related information

@publishedPartner
@released
 */
class TLbsNetClassTypeBase
	{
public:
	IMPORT_C TUint32 ClassType() const;
	IMPORT_C TUint ClassSize() const;

protected:
	IMPORT_C TLbsNetClassTypeBase();

protected:
	/** The type of the derived class */
	TUint32 iClassType;
	/** The size of the derived class */
	TUint iClassSize;
	};


/**
Session Identifiers are used to uniquely identify requests either generated by,
or received by, a network protocol module.

TLbsNetSessionId contains two fields - an owner and a request number. 
The owner is the UID of the component that created the request. The request
number is used to uniquely identify a request by that component. 

The request number may increment with each new request. However, this is not
guaranteed. In some instances, the request number will be derived from details
obtained by the network.

For requests generated by the network protocol module, the ECom implementation
UID should be used as the session id owner. Where, requests originate from
within the LBS subsystem, the owner will be the UID of the component that
created the request. This will normally be the Network Request Handler.

@see MLbsNetworkProtocolObserver
@see CLbsNetworkProtocolBase
	
@publishedPartner
@released
*/
class TLbsNetSessionId : public TLbsNetClassTypeBase
	{
public:
	typedef TUint32 TSessionNum;

	IMPORT_C TLbsNetSessionId();
	
	IMPORT_C TLbsNetSessionId(TUid aSessionOwner, TSessionNum aSessionNum);

	IMPORT_C TUid SessionOwner() const;
	
	IMPORT_C TSessionNum SessionNum() const;

	IMPORT_C void SetSessionOwner(TUid aSessionOwner);
	
	IMPORT_C void SetSessionNum(TSessionNum aSessionNum);

	IMPORT_C void IncrSession();
	
	IMPORT_C TBool operator==(const TLbsNetSessionId& aSessionId) const;
	IMPORT_C TBool operator!=(const TLbsNetSessionId& aSessionId) const;
	
protected:
	TUid    iSessionOwner;
	TUint32 iSessionNum; 
	TUint8  iReserved[4];
	};


/**
The class encapsulates an array of @see TLbsNetSessionId session ids.

@see TLbsNetSessionId
@see MLbsNetworkProtocolObserver2
@see CLbsNetworkProtocolBase2

@publishedPartner
@released
*/
class TLbsNetSessionIdArray : public TLbsNetClassTypeBase
	{
public:
	IMPORT_C TLbsNetSessionIdArray();
	
	IMPORT_C TInt NumSessions() const;
	IMPORT_C TInt GetSession(TInt aIndex, TLbsNetSessionId &aSessionId) const;
	
	IMPORT_C TInt SetSessions(const TLbsNetSessionId aSessions[], TInt aNumSessions);

private:
	TInt 			 iNumSessions;
	TLbsNetSessionId iSessions[KLbsMaxNetSessions];
	TUint8  		 iReserved[20]; 
	};


/**
Privacy procedure requested by the network.

An instance of the class TLbsNetPosRequestPrivacy is passed to the LBS subsystem in the method
MLbsNetworkProtocolObserver::ProcessPrivacyRequest(). The class is used to indicate what advice
should be given to the user. For example, this may advise that the user is consulted over
the request or simply notified about it.

The class also specifies whether the request should be accepted or rejected. In the situation
where the user is consulted, the action is the default behaviour when the user does not respond.

For example, if the advice is set to ERequestAdviceVerify and the action is ERequestActionAllow,
this indicates that the user should be asked if they wish to accept or reject the request. 
However, if the user does not respond, the terminal should automatically accept the request.

Alternatively, the network may wish to advise the terminal that it has rejected a location
request designated for the device. In this situation the advice is set to ERequestAdviceNotify
with an action of ERequestActionReject.
	
@see MLbsNetworkProtocolObserver::ProcessPrivacyRequest
	
@publishedPartner
@released
*/
class TLbsNetPosRequestPrivacy : public TLbsNetClassTypeBase
	{
public:
	enum TLbsRequestAdvice
		{
				/** Not Used */
		ERequestAdviceNotUsed = 0,
				/** The LBS subsystem should notify the user that their
				location has been requested. */
		ERequestAdviceNotify,
				/** The LBS subsystem should ask the user if they wish
				to accept or reject an external request. */
		ERequestAdviceVerify,
				/** The LBS subsystem should neither notify or query the user if they wish
				to accept or reject an external request. Details of the request
				should be logged. */
		ERequestAdviceSilent,
				/** The terminal should no indication that the device's location
				is being determined by an external party. The user should neither be notified
				nor queried. In addition, no information about the request should be logged.
				This option is defined by some protocols (e.g. SUPL) but is not implemented
				by the LBS subsystem. */
		ERequestAdviceStealth
		};
		
	enum TLbsRequestAction 
		{
 				/** Must not be used with an exception of marking uninitialized values. 
 				The protocol must not send this value to the LBS as a privacy request parameters.*/
		ERequestActionNotUsed = 0,
				/** The default action for LBS subsystem should be to accept the request.
				If this value is passed in combination with ERequestAdviceVerify, it
				indicates that the user should be asked if they wish to accept or reject
				the request. However, if the user does not respond, the request should
				be allowed. */
		ERequestActionAllow,
				/** The default action for LBS subsystem should be to reject the request.
				If this value is passed in combination with ERequestAdviceVerify, it
				indicates that the user should be asked if they wish to accept or reject
				the request. However, if the user does not respond, the request should
				be rejected.
		
				If ERequestActionReject is passed in combination with ERequestAdviceNotify,
				it indicates that the user should be informed that a request has been made
				but the terminal should	automatically reject it.*/
		ERequestActionReject,
		};
	
	IMPORT_C TLbsNetPosRequestPrivacy();

	IMPORT_C TLbsRequestAdvice RequestAdvice() const;
	
	IMPORT_C TLbsRequestAction RequestAction() const;

	IMPORT_C void SetRequestAdvice(TLbsRequestAdvice aAdvice);
	
	IMPORT_C void SetRequestAction(TLbsRequestAction aAction);
	
protected:
	TLbsRequestAction iAction;
	TLbsRequestAdvice iAdvice;
	TUint8  iReserved[16];
	};


/**
The TLbsNetPosRequestQuality is used by the network protocol module
to specify the desired quality of a location request.
An instance of the class is passed by the protocol module when it
calls MLbsNetworkProtocolObserver::ProcessLocationRequest.

The parameters in TLbsNetPosRequestQuality include the desired minumum
horizontal and vertical accuracy for the requested location update.
It also enables a time limit and age of the fix to be specified.

The time limit indicates the maximum time the device should spend
calculating before it responses to network.

The maximum fix age indicates that the network will accept a previous
location calculation that is within the given time period.

It is possible to combine both the desired minimum accuracy and the
maximum time. In this situation the LBS subsystem should respond
either when the desired accuracy has been achieved or when the time
limit has been reached.

@see CLbsLocationSourceBase::RequestLocationUpdate
@see MLbsLocationSourceObserver

@publishedPartner
@released
*/
class TLbsNetPosRequestQuality : public TLbsNetClassTypeBase
	{
public:
	IMPORT_C TLbsNetPosRequestQuality();

	IMPORT_C TTimeIntervalMicroSeconds MaxFixTime() const;
	IMPORT_C TTimeIntervalMicroSeconds MaxFixAge()  const;

	IMPORT_C TReal32 MinHorizontalAccuracy() const;
	IMPORT_C TReal32 MinVerticalAccuracy()   const;

	IMPORT_C void SetMaxFixTime(TTimeIntervalMicroSeconds aTime);
	IMPORT_C void SetMaxFixAge(TTimeIntervalMicroSeconds  aTime);

	IMPORT_C void SetMinHorizontalAccuracy(TReal32 aAccuracy);
	IMPORT_C void SetMinVerticalAccuracy(TReal32 aAccuracy);

protected:
	TReal32 iMinHorizontalAccuracy;
	TReal32 iMinVerticalAccuracy;
	TTimeIntervalMicroSeconds iMaxFixTime;
	TTimeIntervalMicroSeconds iMaxFixAge;
	TUint8  iReserved[16];
	};


/**
This class is the root class for those derived classes that 
encapsulated the parameters for the terminal issuing
a network and a self location eequest.

@see TLbsNetPosRequestOptions
@see TLbsNetPosRequestOptionsAssistance

@publishedPartner
@released
*/
class TLbsNetPosRequestOptionsBase : public TLbsNetClassTypeBase
	{
public:
	IMPORT_C TLbsNetPosRequestOptionsBase();
	
protected:
	TUint8 iReserved[20];
	};

/**
This class encapsulated the common parameters for the terminal issuing
a network and a self location request.

@see TLbsNetPosRequestOptionsAssistance
@see CLbsNetworkProtocolBase::RequestNetworkLocation
@see CLbsNetworkProtocolBase::RequestSelfLocation

@publishedPartner
@released
*/
class TLbsNetPosRequestOptions : public TLbsNetPosRequestOptionsBase
	{
public:
	IMPORT_C TLbsNetPosRequestOptions();

	IMPORT_C void SetNewClientConnected(TBool aNewClient);
	IMPORT_C void SetRequestQuality(const TLbsNetPosRequestQuality& aQuality);

	IMPORT_C TBool NewClientConnected() const;
	IMPORT_C void  GetRequestQuality(TLbsNetPosRequestQuality& aQuality) const;
	
protected:
	TBool iNewClient;
	TLbsNetPosRequestQuality iQuality;
	TUint8 iReserved[20];
	};

/**
This class encapsulated the parameters for the terminal issuing a self
location request.

@see TLbsNetPosRequestOptions
@see CLbsNetworkProtocolBase::RequestSelfLocation

@publishedPartner
@released
*/
class TLbsNetPosRequestOptionsAssistance : public TLbsNetPosRequestOptions
	{
public:

	IMPORT_C TLbsNetPosRequestOptionsAssistance();

	IMPORT_C void SetDataRequestMask(TLbsAsistanceDataGroup aDataRequestMask);
	IMPORT_C void SetPosMode(TPositionModuleInfo::TTechnologyType aPosMode);

	IMPORT_C TLbsAsistanceDataGroup DataRequestMask() const;
	IMPORT_C TPositionModuleInfo::TTechnologyType PosMode() const;
		
protected:
	TLbsAsistanceDataGroup iDataRequestMask;
	TPositionModuleInfo::TTechnologyType iPosMode;
	TUint8 iReserved[20];
	};

/**
This class encapsulated the parameters for the terminal issuing a transmit
location request.

@see TLbsNetPosRequestOptions
@see CLbsNetworkProtocolBase::RequestTransmitLocation

@publishedPartner
@released
*/
class TLbsNetPosRequestOptionsTechnology : public TLbsNetPosRequestOptions
	{
public:

	IMPORT_C TLbsNetPosRequestOptionsTechnology();

	IMPORT_C void SetPosMode(TPositionModuleInfo::TTechnologyType aPosMode);

	IMPORT_C TPositionModuleInfo::TTechnologyType PosMode() const;
		
protected:
	TPositionModuleInfo::TTechnologyType iPosMode;
	TUint8 iReserved[20];
	};

/**
TLbsNetPosMethod describe a positioning means (technology) and its mode of
operation. It is used to by the network to request that a particilar
method is used when calculating the current location. The class is also
used to detail the positioning capabilities of the device.

@see TLbsNetDeviceCapabilities
	
@publishedPartner
@released
*/
class TLbsNetPosMethod : public TLbsNetClassTypeBase
	{
public:
	IMPORT_C TLbsNetPosMethod();
	
	IMPORT_C TUid PosMeans() const;
	IMPORT_C TPositionModuleInfo::TTechnologyType PosMode() const;

	IMPORT_C void SetPosMethod(TUid aPosMeans, TPositionModuleInfo::TTechnologyType aPosMode);
	
protected: 
	TUid iPosMeans;
	TPositionModuleInfo::TTechnologyType iPosMode;
	TUint8  iReserved[12];
	};

/**
TLbsNetPosCapabilities define the positioning capabilities of the
LBS subsystem and device hardware.

The positioning capabilities describe the protocols supported and
the types of network request the device is able to respond
to. For example, this might include terminal based GPS but not
terminal assisted.

Some capabilities will be static or dependent on hardware. However,
other capabilities may vary dynamically - for example, as a result of
the user or the network configuring the device.

@see TLbsNetPosMethod
@see CLbsNetworkProtocolObserver::GetCurrentCapabilities()
	
@publishedPartner
@released
*/
class TLbsNetPosCapabilities : public TLbsNetClassTypeBase
	{
public:
	IMPORT_C TLbsNetPosCapabilities();
	
	IMPORT_C TInt NumPosProtocols() const;
	IMPORT_C TInt GetPosProtocol(TInt aIndex, TUid& aPosProtocol) const;
	
	IMPORT_C TInt NumPosMethods() const;
	IMPORT_C TInt GetPosMethod(TInt aIndex, TLbsNetPosMethod& aPosMethod) const;
	
	IMPORT_C TInt SetPosProtocols(const TUid aPosProtocols[], TInt aNumPosProtocols);
	IMPORT_C TInt SetPosMethods(const TLbsNetPosMethod aPosMethods[], TInt aNumPosMethods);
	
protected: 
	TInt iNumPosProtocols;
	TUid iPosProtocol[KLbsMaxNetPosProtocols];
	
	TInt iNumPosMethods;
	TLbsNetPosMethod iPosMethod[KLbsMaxNetPosMethods];
	
	TUint8  iReserved[20]; 
	};

/**
The class TLbsNetPosRequestMethod is used by the network protocol
module to specify the means and operation mode that should be used
to obtain the device's location.
An instance of the class is passed by the protocol module when it
calls MLbsNetworkProtocolObserver::ProcessLocationRequest.

The class contains a prioritised list of the positioning methods that
should be used to obtain the device's position. The first entry (index
zero) contains the preferred positioning method - for example,
terminal based GPS. The subsequent entries indicate the mechanisms
that should be used if the previous method was not available or was not
successful. Under most protocols, there will be a maximum of two
positioning methods specified.

See TLbsNetPosMethod for information on how different technology
mechanisms (e.g. GPS) and modes (e.g. terminal based) are specified.

@see TLbsNetPosMethod
@see MLbsLocationSourceObserver::ProcessLocationRequest
@see MLbsLocationSourceObserver::GetCurrentCapabilities

@publishedPartner
@released
*/
class TLbsNetPosRequestMethod : public TLbsNetClassTypeBase
	{
public:
	IMPORT_C TLbsNetPosRequestMethod();

	IMPORT_C TInt NumPosMethods() const;
	IMPORT_C TInt GetPosMethod(TInt aIndex, TLbsNetPosMethod& aPosMethod) const;
	IMPORT_C TBool GpsTimingOfCellFramesRequested() const;

	IMPORT_C TInt SetPosMethods(const TLbsNetPosMethod aPosMethods[], TInt aNumPosMethods);
	IMPORT_C void SetGpsTimingOfCellFramesRequested(TBool aRequested);

protected:
	TInt iNumPosMethods;
	TLbsNetPosMethod iPosMethod[KLbsMaxNetPosMethods];
	TBool iGpsTimingOfCellFramesRequested;

private:
	TUint8  iReserved[16];
	};

#endif // LBSNETCOMMON_H_

