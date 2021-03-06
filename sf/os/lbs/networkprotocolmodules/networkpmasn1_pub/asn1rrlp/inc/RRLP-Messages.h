// Copyright (c) 2001-2009 Objective Systems, Inc. (http://www.obj-sys.com) 
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available 
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//

/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).
 */
#ifndef RRLP_MESSAGES_H
#define RRLP_MESSAGES_H

#include <stdio.h>
#include <stdlib.h>
#include "rtkey.h"
#include "rtpersrc/asn1PerCppTypes.h"
#include "RRLP-Components.h"

/**
 * Header file for ASN.1 module RRLP-Messages
 */
/**************************************************************/
/*                                                            */
/*  RRLP_Component                                            */
/*                                                            */
/**************************************************************/

/* Choice tag constants */

#define T_RRLP_Component_msrPositionReq 1
#define T_RRLP_Component_msrPositionRsp 2
#define T_RRLP_Component_assistanceData 3
#define T_RRLP_Component_assistanceDataAck 4
#define T_RRLP_Component_protocolError  5
#define T_RRLP_Component_extElem1       6

struct ASN1T_RRLP_Component {
   int t;
   union {
      /* t = 1 */
      ASN1T_MsrPosition_Req *msrPositionReq;
      /* t = 2 */
      ASN1T_MsrPosition_Rsp *msrPositionRsp;
      /* t = 3 */
      ASN1T_AssistanceData *assistanceData;
      /* t = 4 */
      /* t = 5 */
      ASN1T_ProtocolError *protocolError;
      /* t = 6 */
   } u;
} ;

IMPORT_C int asn1PE_RRLP_Component (OSCTXT* pctxt, ASN1T_RRLP_Component* pvalue);

IMPORT_C int asn1PD_RRLP_Component (OSCTXT* pctxt, ASN1T_RRLP_Component* pvalue);

IMPORT_C void asn1Print_RRLP_Component
   (const char* name, ASN1T_RRLP_Component* pvalue);

IMPORT_C void asn1Free_RRLP_Component (OSCTXT *pctxt, ASN1T_RRLP_Component* pvalue);

/**************************************************************/
/*                                                            */
/*  PDU                                                       */
/*                                                            */
/**************************************************************/

#define TV_PDU	(TM_UNIV|TM_CONS|16)

struct ASN1T_PDU : public ASN1TPDU {
   OSUINT8 referenceNumber;
   ASN1T_RRLP_Component component;
   IMPORT_C ASN1T_PDU ();
   IMPORT_C ~ASN1T_PDU ();
} ;

class ASN1C_PDU :
public ASN1CType
{
protected:
   ASN1T_PDU& msgData;
public:
   IMPORT_C ASN1C_PDU (ASN1T_PDU& data);
   IMPORT_C ASN1C_PDU (OSRTMessageBufferIF& msgBuf, ASN1T_PDU& data);
   IMPORT_C ASN1C_PDU (OSRTContext &context, ASN1T_PDU& data);

   inline ASN1T_PDU& getData () { return msgData; }
   inline const ASN1T_PDU& getData () const { return msgData; }

   // standard encode/decode methods (defined in ASN1CType base class):
   // int Encode ();
   // int Decode ();

   // stream encode/decode methods:
   IMPORT_C int EncodeTo (OSRTMessageBufferIF& msgBuf);
   IMPORT_C int DecodeFrom (OSRTMessageBufferIF& msgBuf);

   IMPORT_C void Print ();
} ;

IMPORT_C int asn1PE_PDU (OSCTXT* pctxt, ASN1T_PDU* pvalue);

IMPORT_C int asn1PD_PDU (OSCTXT* pctxt, ASN1T_PDU* pvalue);

IMPORT_C void asn1Print_PDU
   (const char* name, ASN1T_PDU* pvalue);

IMPORT_C void asn1Free_PDU (OSCTXT *pctxt, ASN1T_PDU* pvalue);

#endif
