/*
 * atari_tia_res.c
 *
 *  Created on: 21.12.2018
 *      Author: enradion
 */
#include <os_type.h>
#include <ets_sys.h>

#include "atari_tia/atari_tia.h"
#include "atari_tia/atari_tia_coap.h"
#include "lobaro-coap/coap.h"
#include "atari_tia_res.h"
#include "controller/atari_tia_controller.h"

CoAP_Res_t* pAtariTiaRes = NULL;



static CoAP_HandlerResult_t ICACHE_FLASH_ATTR AtariTia_Res_ReqHandler(CoAP_Message_t* pReq, CoAP_Message_t* pResp) {

	uint8_t valLen = 0;
	uint8_t* pVal = NULL;
	CoAP_option_t* pOpt;

	atari_tia_cfg cfg;

	bool audFound = false;
	bool regFound = false;
	bool valFound = false;

	if(pReq->Code == REQ_PUT)
	{
		for(pOpt=pReq->pOptionsList; pOpt != NULL; pOpt = pOpt->next)
		{
			if(!audFound){
				pVal = CoAP_GetUriQueryVal(pOpt, COAP_ATARI_TIA_AUD_PREFIX, &valLen);
				if(pVal) {
					cfg.aud = (int) atoi(pVal);
					audFound = true;
					continue;
				}
			}

			if(!regFound){
				pVal = CoAP_GetUriQueryVal(pOpt, COAP_ATARI_TIA_REG_PREFIX, &valLen);
				if(pVal) {
					cfg.reg = (int) atoi(pVal);
					regFound = true;
					continue;
				}
			}

			if(!valFound){
				pVal = CoAP_GetUriQueryVal(pOpt, COAP_ATARI_TIA_VAL_PREFIX, &valLen);
				if(pVal) {
					cfg.val = (int) atoi(pVal);
					valFound = true;
					continue;
				}
			}
		}

		if(audFound && regFound && valFound) {
			// trigger audio

		}else {
			const char infoStr[] = "FAIL to set Atari TIA, maybe a parameter is missing ?";
			CoAP_SetPayload(pReq, pResp, (uint8_t*)infoStr, coap_strlen(infoStr), true);
			pResp->Code=RESP_ERROR_BAD_REQUEST_4_00;
		}
	} // end put
	return HANDLER_OK;
}

static CoAP_HandlerResult_t ICACHE_FLASH_ATTR AtariTia_Res_NotifyHandler(CoAP_Observer_t* pObserver, CoAP_Message_t* pResp) {
	// SetLedstatePayload(NULL, pResp);
	return HANDLER_OK;
}

CoAP_Res_t* ICACHE_FLASH_ATTR Create_Atari_TIA_Resource() {
	CoAP_ResOpts_t Options = {.Cf = COAP_CF_TEXT_PLAIN, .Flags = RES_OPT_PUT};

	return (pAtariTiaRes=CoAP_CreateResource(COAP_ATARI_TIA_RESOURCE, COAP_ATARI_TIA_RESOURCE_DESC, Options, AtariTia_Res_ReqHandler, AtariTia_Res_NotifyHandler));
}








