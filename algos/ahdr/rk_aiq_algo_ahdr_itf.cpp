/*
 * rk_aiq_algo_ae_itf.c
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
#include "ahdr/rk_aiq_algo_ahdr_itf.h"

#include "ahdr/rk_aiq_ahdr_algo.h"
#include "ahdr/rk_aiq_types_ahdr_algo_prvt.h"



RKAIQ_BEGIN_DECLARE


static RkAiqAlgoContext ctx;

static XCamReturn AhdrCreateCtx(RkAiqAlgoContext **context, const AlgoCtxInstanceCfg* cfg)
{

    LOGI_AHDR("%s:Enter!\n", __FUNCTION__);
    RESULT ret = AHDR_RET_SUCCESS;

    memset(&ctx.AhdrInstConfig, 0x00, sizeof(AhdrInstanceConfig_t));
    ret = AhdrInit(&ctx.AhdrInstConfig);

    if (ret != AHDR_RET_SUCCESS) {
        LOGE_AHDR("%s AHDRInit failed: %d", __FUNCTION__, ret);
        return(XCAM_RETURN_ERROR_FAILED);
    }

    *context = &ctx;

    LOGI_AHDR("%s:Exit!\n", __FUNCTION__);
    return(XCAM_RETURN_NO_ERROR);
}

static XCamReturn AhdrDestroyCtx(RkAiqAlgoContext *context)
{
    LOGI_AHDR("%s:Enter!\n", __FUNCTION__);
    RESULT ret = AHDR_RET_SUCCESS;


    if(context != NULL) {

        AhdrHandle_t pAhdrCtx = (AhdrHandle_t)context->AhdrInstConfig.hAhdr;
        ret = AhdrRelease(pAhdrCtx);
        if (ret != AHDR_RET_SUCCESS) {
            LOGE_AHDR("%s AecRelease failed: %d", __FUNCTION__, ret);
            return(XCAM_RETURN_ERROR_FAILED);
        }
        context = NULL;
    }


    LOGI_AHDR("%s:Exit!\n", __FUNCTION__);
    return(XCAM_RETURN_NO_ERROR);
}

static XCamReturn AhdrPrepare(RkAiqAlgoCom* params)
{
    LOGI_AHDR("%s:Enter!\n", __FUNCTION__);
    RESULT ret = AHDR_RET_SUCCESS;

#ifndef RK_SIMULATOR_HW
    AhdrHandle_t pAhdrCtx = params->ctx->AhdrInstConfig.hAhdr;
    RkAiqAlgoConfigAhdrInt* AhdrCfgParam = (RkAiqAlgoConfigAhdrInt*)params;
    static CamCalibDbContext_t CalibDb;
    CamCalibDbContext_t* pCalibDb = &CalibDb;
    memset(pCalibDb, 0, sizeof(CamCalibDbContext_t));
#include "ahdrhtmldata.h"
    pAhdrCtx->width = AhdrCfgParam->rawWidth;
    pAhdrCtx->height = AhdrCfgParam->rawHeight;
#else
    AhdrHandle_t pAhdrCtx = params->ctx->AhdrInstConfig.hAhdr;
    RkAiqAlgoConfigAhdrInt* AhdrCfgParam = (RkAiqAlgoConfigAhdrInt*)params; //come from params in html
    const CamCalibDbContext_t* pCalibDb = AhdrCfgParam->rk_com.u.prepare.calib;
    pAhdrCtx->width = AhdrCfgParam->rawWidth;
    pAhdrCtx->height = AhdrCfgParam->rawHeight;
#endif


#if 0
    AhdrHandle_t pAhdrCtx = params->ctx->AhdrInstConfig.hAhdr;
    RkAiqAlgoConfigAhdrInt* AhdrCfgParam = (RkAiqAlgoConfigAhdrInt*)params; //come from params in html
    const CamCalibDbContext_t* pCalibDb = AhdrCfgParam->rk_com.u.prepare.calib;
    pAhdrCtx->width = AhdrCfgParam->rawWidth;
    pAhdrCtx->height = AhdrCfgParam->rawHeight;
#endif

    AhdrConfig(pAhdrCtx); //set default paras
    AhdrGetXmlParas(pAhdrCtx, pCalibDb); //convert AeCfg params into AeHandle

    if (ret != AHDR_RET_SUCCESS) {
        LOGE_AHDR("%s AHDRUpdateConfig failed: %d", __FUNCTION__, ret);
        return(XCAM_RETURN_ERROR_FAILED);
    }

    if(/* !params->u.prepare.reconfig*/true) {
        ret = AhdrStart(pAhdrCtx);
        if (ret != AHDR_RET_SUCCESS) {
            LOGE_AHDR("%s AHDRStart failed: %d", __FUNCTION__, ret);
            return(XCAM_RETURN_ERROR_FAILED);
        }
    }

    LOGI_AHDR("%s:Exit!\n", __FUNCTION__);
    return(XCAM_RETURN_NO_ERROR);
}

static XCamReturn AhdrPreProcess(const RkAiqAlgoCom* inparams, RkAiqAlgoResCom* outparams)
{
    LOGI_AHDR("%s:Enter!\n", __FUNCTION__);
    RESULT ret = AHDR_RET_SUCCESS;

    LOGI_AHDR("%s:Exit!\n", __FUNCTION__);
    return(XCAM_RETURN_NO_ERROR);
}

static XCamReturn AhdrProcess(const RkAiqAlgoCom* inparams, RkAiqAlgoResCom* outparams)
{
    LOGI_AHDR("%s:Enter!\n", __FUNCTION__);
    RESULT ret = AHDR_RET_SUCCESS;

    AhdrHandle_t pAhdrCtx = (AhdrHandle_t)inparams->ctx->AhdrInstConfig.hAhdr;
    RkAiqAlgoProcAhdrInt* AhdrParams = (RkAiqAlgoProcAhdrInt*)inparams;
    RkAiqAlgoProcResAhdrInt* AhdrProcResParams = (RkAiqAlgoProcResAhdrInt*)outparams;
    pAhdrCtx->frameCnt = inparams->frame_id;
    AhdrGetROData(pAhdrCtx, &AhdrParams->ispAhdrStats);

    if(!inparams->u.proc.init)
    {
        af_preprocess_result_t af_pre_result;
        RkAiqAlgoPreResAeInt* ae_pre_res_int =
            (RkAiqAlgoPreResAeInt*)(AhdrParams->rk_com.u.proc.pre_res_comb->ae_pre_res);
        RkAiqAlgoPreResAfInt* af_pre_res_int =
            (RkAiqAlgoPreResAfInt*)(AhdrParams->rk_com.u.proc.pre_res_comb->af_pre_res);
        if (ae_pre_res_int && af_pre_res_int)
            AhdrUpdateConfig(pAhdrCtx,
                             ae_pre_res_int->ae_pre_res_rk,
                             af_pre_res_int->af_pre_result);
        else
            AhdrUpdateConfig(pAhdrCtx,
                             ae_pre_res_int->ae_pre_res_rk,
                             af_pre_result);
        AhdrProcessing(pAhdrCtx);
    } else {
        SetFirstPara(pAhdrCtx);
    }

    memcpy(&AhdrProcResParams->AhdrIOData.MergeData, &pAhdrCtx->AhdrIOData.MergeData, sizeof(MergeIOData_s));
    memcpy(&AhdrProcResParams->AhdrIOData.TmoData, &pAhdrCtx->AhdrIOData.TmoData, sizeof(TmoIOData_s));

    LOGI_AHDR("%s:Exit!\n", __FUNCTION__);
    return(XCAM_RETURN_NO_ERROR);
}

static XCamReturn AhdrPostProcess(const RkAiqAlgoCom* inparams, RkAiqAlgoResCom* outparams)
{
    LOGI_AHDR("%s:Enter!\n", __FUNCTION__);
    RESULT ret = AHDR_RET_SUCCESS;

    //TODO

    LOGI_AHDR("%s:Exit!\n", __FUNCTION__);
    return(XCAM_RETURN_NO_ERROR);
}

RkAiqAlgoDescription g_RkIspAlgoDescAhdr = {
    .common = {
        .version = RKISP_ALGO_AHDR_VERSION,
        .vendor  = RKISP_ALGO_AHDR_VENDOR,
        .description = RKISP_ALGO_AHDR_DESCRIPTION,
        .type    = RK_AIQ_ALGO_TYPE_AHDR,
        .id      = 0,
        .create_context  = AhdrCreateCtx,
        .destroy_context = AhdrDestroyCtx,
    },
    .prepare = AhdrPrepare,
    .pre_process = AhdrPreProcess,
    .processing = AhdrProcess,
    .post_process = AhdrPostProcess,
};

RKAIQ_END_DECLARE