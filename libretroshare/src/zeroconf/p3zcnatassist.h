/*
 * libretroshare/src/zeroconf: p3zcnatassist.h
 *
 * ZeroConf interface for RetroShare.
 *
 * Copyright 2011-2012 by Robert Fernie.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License Version 2 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA.
 *
 * Please report all bugs and problems to "retroshare@lunamutt.com".
 *
 */


#ifndef MRK_P3_ZC_NAT_ASSIST_H
#define MRK_P3_ZC_NAT_ASSIST_H

#include "util/rswin.h"

#include "pqi/pqiassist.h"
#include "retroshare/rsdht.h"

#include <string>
#include <map>
#include "pqi/pqinetwork.h"
#include "pqi/pqimonitor.h"
#include "pqi/p3peermgr.h"
#include "util/rsthreads.h"

#include <dns_sd.h>


class p3NetMgr;

class p3zcNatAssist: public pqiNetAssistFirewall
{
	public:
	p3zcNatAssist();
virtual	~p3zcNatAssist();

	/* pqiNetAssist - external interface functions */
virtual int     tick();
virtual void    enable(bool on);  
virtual void    shutdown(); /* blocking call */
virtual void	restart();

virtual bool    getEnabled();
virtual bool    getActive();

virtual void    setInternalPort(unsigned short iport_in);
virtual void    setExternalPort(unsigned short eport_in);
virtual bool    getInternalAddress(struct sockaddr_storage &addr);
virtual bool    getExternalAddress(struct sockaddr_storage &addr);

                /* TO IMPLEMENT: New Port Forward interface to support as many ports as necessary */
virtual bool    requestPortForward(const PortForwardParams &params) { return false; }
virtual bool    statusPortForward(const uint32_t fwdId, PortForwardParams &params) { return false; }

	/* pqiNetAssistConnect - external interface functions */

	
	public:

	// Callbacks must be public -> so they can be accessed.
	void callbackMapping(DNSServiceRef sdRef, DNSServiceFlags flags,
                 uint32_t interfaceIndex, DNSServiceErrorType errorCode,
                 uint32_t externalAddress, DNSServiceProtocol protocol,
                 uint16_t internalPort, uint16_t externalPort, uint32_t ttl);

	private:

	/* monitoring fns */
	void checkServiceFDs();
	void locked_checkFD(DNSServiceRef ref);

	int locked_startMapping();
	void locked_stopMapping();

	/**************** DATA ****************/

	RsMutex mZcMtx;

	bool mEnabled;
	bool mMapped;
	
	uint16_t mLocalPort;
	bool 	 mLocalPortSet;

	uint16_t mExternalPort;
	bool 	 mExternalPortSet;

	struct sockaddr_storage mExternalAddress;
	int mTTL;

	DNSServiceRef mMappingRef;
	uint32_t mMappingStatus; 
	time_t mMappingStatusTS; 
};

#endif /* MRK_P3_ZC_NAT_ASSIST_H */

