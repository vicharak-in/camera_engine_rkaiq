/*
 * rk_aiq_algo_debayer_itf.c
 *
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "rk_aiq_algo_types_int.h"
#include "adebayer/rk_aiq_algo_adebayer_itf.h"
#include "adebayer/rk_aiq_types_algo_adebayer_prvt.h"

RKAIQ_BEGIN_DECLARE

static RkAiqAlgoContext ctx;

static XCamReturn
create_context
(
    RkAiqAlgoContext **context,
    const AlgoCtxInstanceCfg* cfg
)
{	 
	XCamReturn result = XCAM_RETURN_NO_ERROR;

	LOGI_ADEBAYER("%s: (enter)\n", __FUNCTION__ );
    AdebayerInit(&ctx.adebayerCtx);
	*context = &ctx;
	LOGI_ADEBAYER("%s: (exit)\n", __FUNCTION__ );
	return result;
}

static XCamReturn
destroy_context
(
    RkAiqAlgoContext *context
)
{	
	XCamReturn result = XCAM_RETURN_NO_ERROR;
	
	LOGI_ADEBAYER("%s: (enter)\n", __FUNCTION__ );
	AdebayerContext_t* pAdebayerCtx = (AdebayerContext_t*)&context->adebayerCtx;
    AdebayerRelease(pAdebayerCtx);
	LOGI_ADEBAYER("%s: (exit)\n", __FUNCTION__ );
    return result;
}

static XCamReturn
prepare
(
    RkAiqAlgoCom* params
)
{
	XCamReturn result = XCAM_RETURN_NO_ERROR;

	LOGI_ADEBAYER("%s: (enter)\n", __FUNCTION__ );
    AdebayerContext_t* pAdebayerCtx = (AdebayerContext_t *)&params->ctx->adebayerCtx;
    RkAiqAlgoConfigAdebayerInt* pCfgParam = (RkAiqAlgoConfigAdebayerInt*)params;
    pAdebayerCtx->pCalibDb = pCfgParam->rk_com.u.prepare.calib;
	AdebayerStart(pAdebayerCtx);
	LOGI_ADEBAYER("%s: (exit)\n", __FUNCTION__ );
    return result;
}

static XCamReturn
pre_process
(
    const RkAiqAlgoCom* inparams,
    RkAiqAlgoResCom* outparams
)
{
	LOGI_ADEBAYER("%s: (enter)\n", __FUNCTION__ );

	LOGI_ADEBAYER("%s: (exit)\n", __FUNCTION__ );
    return XCAM_RETURN_NO_ERROR;
}

static XCamReturn
processing
(
    const RkAiqAlgoCom* inparams,
    RkAiqAlgoResCom* outparams
)
{
	XCamReturn result = XCAM_RETURN_NO_ERROR;
	int iso;
    RkAiqAlgoProcAdebayerInt* pAdebayerProcParams = (RkAiqAlgoProcAdebayerInt*)inparams; 
    RkAiqAlgoProcResAdebayerInt* pAdebayerProcResParams = (RkAiqAlgoProcResAdebayerInt*)outparams;
    AdebayerContext_t* pAdebayerCtx = (AdebayerContext_t *)&inparams->ctx->adebayerCtx;

	LOGI_ADEBAYER("%s: (enter)\n", __FUNCTION__ );

	if(inparams->u.proc.init)
		iso = 50;
	else
		iso = pAdebayerProcParams->rk_com.u.proc.iso;

    AdebayerProcess(pAdebayerCtx, iso);
    AdebayerGetProcResult(pAdebayerCtx, &pAdebayerProcResParams->debayerRes);

	LOGI_ADEBAYER("%s: (exit)\n", __FUNCTION__ );
    return XCAM_RETURN_NO_ERROR;
}

static XCamReturn
post_process
(
    const RkAiqAlgoCom* inparams,
    RkAiqAlgoResCom* outparams
)
{
	LOGI_ADEBAYER("%s: (enter)\n", __FUNCTION__ );

	LOGI_ADEBAYER("%s: (exit)\n", __FUNCTION__ );
    return XCAM_RETURN_NO_ERROR;	
}

RkAiqAlgoDescription g_RkIspAlgoDescAdebayer = {
    .common = {
        .version = RKISP_ALGO_ADEBAYER_VERSION,
        .vendor  = RKISP_ALGO_ADEBAYER_VENDOR,
        .description = RKISP_ALGO_ADEBAYER_DESCRIPTION,
        .type    = RK_AIQ_ALGO_TYPE_ADEBAYER,
        .id      = 0,
        .create_context  = create_context,
        .destroy_context = destroy_context,
    },
    .prepare = prepare,
    .pre_process = pre_process,
    .processing = processing,
    .post_process = post_process,
};

RKAIQ_END_DECLARE