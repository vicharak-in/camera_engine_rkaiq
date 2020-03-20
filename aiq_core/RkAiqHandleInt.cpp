/*
 * RkAiqHandleInt.cpp
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

#include "RkAiqHandleInt.h"
#include "RkAiqCore.h"

namespace RkCam {

XCamReturn RkAiqHandleIntCom::configInparamsCom(RkAiqAlgoCom* com, int type)
{
    ENTER_ANALYZER_FUNCTION();

    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqAlgoComInt* rk_com = NULL;

    switch (mDes->type) {
    case RK_AIQ_ALGO_TYPE_AE:
        rk_com = &(((RkAiqAlgoConfigAeInt*)com)->rk_com);
        break;
    case RK_AIQ_ALGO_TYPE_AWB:
        rk_com = &(((RkAiqAlgoConfigAwbInt*)com)->rk_com);
        break;
    case RK_AIQ_ALGO_TYPE_AF:
        rk_com = &(((RkAiqAlgoConfigAfInt*)com)->rk_com);
        break;
    case RK_AIQ_ALGO_TYPE_ABLC:
        rk_com = &(((RkAiqAlgoConfigAblcInt*)com)->rk_com);
        break;
    case RK_AIQ_ALGO_TYPE_ADPCC:
        rk_com = &(((RkAiqAlgoConfigAdpccInt*)com)->rk_com);
        break;
    case RK_AIQ_ALGO_TYPE_AHDR:
        rk_com = &(((RkAiqAlgoConfigAhdrInt*)com)->rk_com);
        break;
    case RK_AIQ_ALGO_TYPE_ANR:
        rk_com = &(((RkAiqAlgoConfigAnrInt*)com)->rk_com);
        break;
    case RK_AIQ_ALGO_TYPE_ALSC:
        rk_com = &(((RkAiqAlgoConfigAlscInt*)com)->rk_com);
        break;
    case RK_AIQ_ALGO_TYPE_AGIC:
        rk_com = &(((RkAiqAlgoConfigAgicInt*)com)->rk_com);
        break;
    case RK_AIQ_ALGO_TYPE_ADEBAYER:
        rk_com = &(((RkAiqAlgoConfigAdebayerInt*)com)->rk_com);
        break;
    case RK_AIQ_ALGO_TYPE_ACCM:
        rk_com = &(((RkAiqAlgoConfigAccmInt*)com)->rk_com);
        break;
    case RK_AIQ_ALGO_TYPE_AGAMMA:
        rk_com = &(((RkAiqAlgoConfigAgammaInt*)com)->rk_com);
        break;
    case RK_AIQ_ALGO_TYPE_AWDR:
        rk_com = &(((RkAiqAlgoConfigAwdrInt*)com)->rk_com);
        break;
    case RK_AIQ_ALGO_TYPE_ADHAZ:
        rk_com = &(((RkAiqAlgoConfigAdhazInt*)com)->rk_com);
        break;
    case RK_AIQ_ALGO_TYPE_A3DLUT:
        rk_com = &(((RkAiqAlgoConfigA3dlutInt*)com)->rk_com);
        break;
    case RK_AIQ_ALGO_TYPE_ALDCH:
        rk_com = &(((RkAiqAlgoConfigAldchInt*)com)->rk_com);
        break;
    case RK_AIQ_ALGO_TYPE_AR2Y:
        rk_com = &(((RkAiqAlgoConfigAr2yInt*)com)->rk_com);
        break;
    case RK_AIQ_ALGO_TYPE_ACP:
        rk_com = &(((RkAiqAlgoConfigAcpInt*)com)->rk_com);
        break;
    case RK_AIQ_ALGO_TYPE_AIE:
        rk_com = &(((RkAiqAlgoConfigAieInt*)com)->rk_com);
        break;
    case RK_AIQ_ALGO_TYPE_ASHARP:
        rk_com = &(((RkAiqAlgoConfigAsharpInt*)com)->rk_com);
        break;
    case RK_AIQ_ALGO_TYPE_AORB:
        rk_com = &(((RkAiqAlgoConfigAorbInt*)com)->rk_com);
        break;
    case RK_AIQ_ALGO_TYPE_AFEC:
        rk_com = &(((RkAiqAlgoConfigAfecInt*)com)->rk_com);
        break;
    case RK_AIQ_ALGO_TYPE_ACGC:
        rk_com = &(((RkAiqAlgoConfigAcgcInt*)com)->rk_com);
        break;
    case RK_AIQ_ALGO_TYPE_ASD:
        rk_com = &(((RkAiqAlgoConfigAsdInt*)com)->rk_com);
        break;
    default:
        LOGE_ANALYZER("wrong algo type !");
    }

    if (!rk_com)
        goto out;

    xcam_mem_clear(*rk_com);

    if (type == RkAiqHandle::RKAIQ_CONFIG_COM_PREPARE) {
        rk_com->u.prepare.calib = (CamCalibDbContext_t*)(shared->calib);
    } else if (type == RkAiqHandle::RKAIQ_CONFIG_COM_PROC) {
        rk_com->u.proc.pre_res_comb = &shared->preResComb;
        rk_com->u.proc.proc_res_comb = &shared->procResComb;
        rk_com->u.proc.post_res_comb = &shared->postResComb;
        rk_com->u.proc.iso = shared->iso;
    } else {

    }

    EXIT_ANALYZER_FUNCTION();
out:
    return RkAiqHandle::configInparamsCom(com, type);
}

void
RkAiqAeHandleInt::init()
{
    ENTER_ANALYZER_FUNCTION();

    RkAiqAeHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAeInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAeInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAeInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAeInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAeInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAeInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAeInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn
RkAiqAeHandleInt::updateConfig()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    //TODO

    mCfgMutex.lock();
    // if something changed, api will modify aecCfg in mAlgoCtx
    if (updateExpSwAttr) {
        mCurExpSwAttr = mNewExpSwAttr;
        updateExpSwAttr = false;
        updateAtt = true;
        rk_aiq_uapi_ae_setExpSwAttr(mAlgoCtx, &mCurExpSwAttr, false);
    }
    if (updateLinExpAttr) {
        mCurLinExpAttr = mNewLinExpAttr;
        updateLinExpAttr = false;
        updateAtt = true;
        rk_aiq_uapi_ae_setLinExpAttr(mAlgoCtx, &mCurLinExpAttr, false);
    }
    if (updateHdrExpAttr) {
        mCurHdrExpAttr = mNewHdrExpAttr;
        updateHdrExpAttr = false;
        updateAtt = true;
        rk_aiq_uapi_ae_setHdrExpAttr(mAlgoCtx, &mCurHdrExpAttr, false);
    }
    if (updateLinAeRouteAttr) {
        mCurLinAeRouteAttr = mNewLinAeRouteAttr;
        updateLinAeRouteAttr = false;
        updateAtt = true;
        rk_aiq_uapi_ae_setLinAeRouteAttr(mAlgoCtx, &mCurLinAeRouteAttr, false);
    }
    if (updateHdrAeRouteAttr) {
        mCurHdrAeRouteAttr = mNewHdrAeRouteAttr;
        updateHdrAeRouteAttr = false;
        updateAtt = true;
        rk_aiq_uapi_ae_setHdrAeRouteAttr(mAlgoCtx, &mCurHdrAeRouteAttr, false);
    }
    // once any params are changed, run reconfig to convert aecCfg to paectx
    AeInstanceConfig_t* pAeInstConfig = (AeInstanceConfig_t*)mAlgoCtx;
    AeConfig_t pAecCfg = pAeInstConfig->aecCfg;
    pAecCfg->ApiReconfig = updateAtt;
    updateAtt = false;

    mCfgMutex.unlock();
    // TODO

    EXIT_ANALYZER_FUNCTION();
    return ret;
}
XCamReturn
RkAiqAeHandleInt::setExpSwAttr(Uapi_ExpSwAttr_t ExpSwAttr)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    //TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurExpSwAttr, &ExpSwAttr, sizeof(Uapi_ExpSwAttr_t))) {
        mNewExpSwAttr = ExpSwAttr;
        updateExpSwAttr = true;
    }
    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}
XCamReturn
RkAiqAeHandleInt::getExpSwAttr(Uapi_ExpSwAttr_t* pExpSwAttr)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_ae_getExpSwAttr(mAlgoCtx, pExpSwAttr);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAeHandleInt::setLinExpAttr(Uapi_LinExpAttr_t LinExpAttr)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    //TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurLinExpAttr, &LinExpAttr, sizeof(Uapi_LinExpAttr_t))) {
        mNewLinExpAttr = LinExpAttr;
        updateLinExpAttr = true;
    }
    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}
XCamReturn
RkAiqAeHandleInt::getLinExpAttr(Uapi_LinExpAttr_t* pLinExpAttr)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_ae_getLinExpAttr(mAlgoCtx, pLinExpAttr);

    EXIT_ANALYZER_FUNCTION();
    return ret;

}
XCamReturn
RkAiqAeHandleInt::setHdrExpAttr(Uapi_HdrExpAttr_t HdrExpAttr)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    //TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurHdrExpAttr, &HdrExpAttr, sizeof(Uapi_HdrExpAttr_t))) {
        mNewHdrExpAttr = HdrExpAttr;
        updateHdrExpAttr = true;
    }
    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}
XCamReturn
RkAiqAeHandleInt::getHdrExpAttr (Uapi_HdrExpAttr_t* pHdrExpAttr)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_ae_getHdrExpAttr(mAlgoCtx, pHdrExpAttr);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}
XCamReturn
RkAiqAeHandleInt::setLinAeRouteAttr(Uapi_LinAeRouteAttr_t LinAeRouteAttr)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    //TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurLinAeRouteAttr, &LinAeRouteAttr, sizeof(Uapi_LinAeRouteAttr_t))) {
        mNewLinAeRouteAttr = LinAeRouteAttr;
        updateLinAeRouteAttr = true;
    }
    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}
XCamReturn
RkAiqAeHandleInt::getLinAeRouteAttr(Uapi_LinAeRouteAttr_t* pLinAeRouteAttr)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_ae_getLinAeRouteAttr(mAlgoCtx, pLinAeRouteAttr);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}
XCamReturn
RkAiqAeHandleInt::setHdrAeRouteAttr(Uapi_HdrAeRouteAttr_t HdrAeRouteAttr)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    //TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurHdrAeRouteAttr, &HdrAeRouteAttr, sizeof(Uapi_HdrAeRouteAttr_t))) {
        mNewHdrAeRouteAttr = HdrAeRouteAttr;
        updateHdrAeRouteAttr = true;
    }
    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}
XCamReturn
RkAiqAeHandleInt::getHdrAeRouteAttr(Uapi_HdrAeRouteAttr_t* pHdrAeRouteAttr)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_ae_getHdrAeRouteAttr(mAlgoCtx, pHdrAeRouteAttr);

    EXIT_ANALYZER_FUNCTION();
    return ret;

}
XCamReturn
RkAiqAeHandleInt::queryExpInfo(Uapi_ExpQueryInfo_t* pExpQueryInfo)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_ae_queryExpInfo(mAlgoCtx, pExpQueryInfo);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}
XCamReturn
RkAiqAeHandleInt::prepare()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqAeHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "ae handle prepare failed");

    RkAiqAlgoConfigAeInt* ae_config_int = (RkAiqAlgoConfigAeInt*)mConfig;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;

    /*****************AecConfig algo params*****************/
    ae_config_int->rk_com.u.prepare.calib->aec.CommCtrl = shared->calib->aec.CommCtrl;
    ae_config_int->rk_com.u.prepare.calib->aec.HdrAeCtrl = shared->calib->aec.HdrAeCtrl;
    ae_config_int->rk_com.u.prepare.calib->aec.LinearAeCtrl = shared->calib->aec.LinearAeCtrl;
    ae_config_int->rk_com.u.prepare.calib->sensor = shared->calib->sensor;

    /*****************AecConfig pic-info params*****************/
    ae_config_int->RawWidth = shared->snsDes.sensor_output_width;
    ae_config_int->RawHeight = shared->snsDes.sensor_output_height;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "ae algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAeHandleInt::preProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAeInt* ae_pre_int = (RkAiqAlgoPreAeInt*)mPreInParam;
    RkAiqAlgoPreResAeInt* ae_pre_res_int = (RkAiqAlgoPreResAeInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqIspStats* ispStats = &shared->ispStats;
    RkAiqPreResComb* comb = &shared->preResComb;

    ret = RkAiqAeHandle::preProcess();
    if (ret) {
        comb->ae_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "ae handle preProcess failed");
    }

    comb->ae_pre_res = NULL;

    ae_pre_int->ispAeStats = &ispStats->aec_stats;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "ae algo pre_process failed");

    // set result to mAiqCore
    comb->ae_pre_res = (RkAiqAlgoPreResAe*)ae_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAeHandleInt::processing()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAeInt* ae_proc_int = (RkAiqAlgoProcAeInt*)mProcInParam;
    RkAiqAlgoProcResAeInt* ae_proc_res_int = (RkAiqAlgoProcResAeInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqProcResComb* comb = &shared->procResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAeHandle::processing();
    if (ret) {
        comb->ae_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "ae handle processing failed");
    }

    comb->ae_proc_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "ae algo processing failed");

    comb->ae_proc_res = (RkAiqAlgoProcResAe*)ae_proc_res_int;

    LOGE("AeProc HwCofing,rawaebig2.wnd_num=%d,rawaebig3.win.h_size=%d,rawhist2.weight[25]=%d", ae_proc_res_int->ae_proc_res_com.ae_meas.rawaebig2.wnd_num,
         ae_proc_res_int->ae_proc_res_com.ae_meas.rawaebig3.win.h_size, ae_proc_res_int->ae_proc_res_com.hist_meas.rawhstbig2.weight[25]);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAeHandleInt::postProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAeInt* ae_post_int = (RkAiqAlgoPostAeInt*)mPostInParam;
    RkAiqAlgoPostResAeInt* ae_post_res_int = (RkAiqAlgoPostResAeInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqPostResComb* comb = &shared->postResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAeHandle::postProcess();
    if (ret) {
        comb->ae_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "ae handle postProcess failed");
        return ret;
    }

    comb->ae_post_res = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "ae algo post_process failed");
    // set result to mAiqCore
    comb->ae_post_res = (RkAiqAlgoPostResAe*)ae_post_res_int ;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

void
RkAiqAwbHandleInt::init()
{
    ENTER_ANALYZER_FUNCTION();

    RkAiqAwbHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAwbInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAwbInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAwbInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAwbInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAwbInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAwbInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAwbInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn
RkAiqAwbHandleInt::updateConfig()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    //TODO
    mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt = mNewAtt;
        updateAtt = false;
        // TODO
        rk_aiq_uapi_awb_SetAttrib(mAlgoCtx, mCurAtt, false);
    }
    mCfgMutex.unlock();


    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAwbHandleInt::setAttrib(rk_aiq_wb_attrib_t att)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    //TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurAtt, &att, sizeof(rk_aiq_wb_attrib_t))) {
        mNewAtt = att;
        updateAtt = true;
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAwbHandleInt::getAttrib(rk_aiq_wb_attrib_t *att)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_awb_GetAttrib(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAwbHandleInt::getCct(rk_aiq_wb_cct_t *cct)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_awb_GetCCT(mAlgoCtx, cct);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAwbHandleInt::queryWBInfo(rk_aiq_wb_querry_info_t *wb_querry_info )
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_awb_QueryWBInfo(mAlgoCtx, wb_querry_info);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAwbHandleInt::prepare()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqAwbHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "awb handle prepare failed");

    RkAiqAlgoConfigAwbInt* awb_config_int = (RkAiqAlgoConfigAwbInt*)mConfig;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;

    // TODO
    //awb_config_int->rawBit;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "ae algo post_process failed");

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAwbHandleInt::preProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAwbInt* awb_pre_int = (RkAiqAlgoPreAwbInt*)mPreInParam;
    RkAiqAlgoPreResAwbInt* awb_pre_res_int = (RkAiqAlgoPreResAwbInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqPreResComb* comb = &shared->preResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAwbHandle::preProcess();
    if (ret) {
        comb->awb_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "awb handle preProcess failed");
    }
    comb->awb_pre_res = NULL;
#ifdef RK_SIMULATOR_HW
    if(shared->hardware_version == 0) {
        awb_pre_int->awb_hw0_statis = ispStats->awb_stats;
    } else {
        awb_pre_int->awb_hw1_statis = ispStats->awb_stats_v201;
    }
#else
    if(shared->hardware_version == 0) {
        for(int i = 0; i < RK_AIQ_AWB_MAX_WHITEREGIONS_NUM; i++) {
            //mAwbPreParam.awb_hw0_statis.light,
            for(int j = 0; j < RK_AIQ_AWB_XY_TYPE_MAX_V200; j++) {
                awb_pre_int->awb_hw0_statis.light[i].xYType[j].WpNo
                    = ispStats->awb_stats.light[i].xYType[j].WpNo;
                awb_pre_int->awb_hw0_statis.light[i].xYType[j].Rvalue
                    = ispStats->awb_stats.light[i].xYType[j].Rvalue;
                awb_pre_int->awb_hw0_statis.light[i].xYType[j].Gvalue
                    = ispStats->awb_stats.light[i].xYType[j].Gvalue;
                awb_pre_int->awb_hw0_statis.light[i].xYType[j].Bvalue
                    = ispStats->awb_stats.light[i].xYType[j].Bvalue;

                awb_pre_int->awb_hw0_statis.multiwindowLightResult[i].xYType[j].WpNo
                    = ispStats->awb_stats.multiwindowLightResult[i].xYType[j].WpNo;
                awb_pre_int->awb_hw0_statis.multiwindowLightResult[i].xYType[j].Rvalue
                    = ispStats->awb_stats.multiwindowLightResult[i].xYType[j].Rvalue;
                awb_pre_int->awb_hw0_statis.multiwindowLightResult[i].xYType[j].Gvalue
                    = ispStats->awb_stats.multiwindowLightResult[i].xYType[j].Gvalue;
                awb_pre_int->awb_hw0_statis.multiwindowLightResult[i].xYType[j].Bvalue
                    = ispStats->awb_stats.multiwindowLightResult[i].xYType[j].Bvalue;

            }
        }
        for(int i = 0; i < RK_AIQ_AWB_GRID_NUM_TOTAL; i++) {
            awb_pre_int->awb_hw0_statis.blockResult[i].Rvalue
                = ispStats->awb_stats.blockResult[i].Rvalue;
            awb_pre_int->awb_hw0_statis.blockResult[i].Gvalue
                = ispStats->awb_stats.blockResult[i].Gvalue;
            awb_pre_int->awb_hw0_statis.blockResult[i].Bvalue
                = ispStats->awb_stats.blockResult[i].Bvalue;
            memcpy(awb_pre_int->awb_hw0_statis.blockResult[i].isWP,
                   ispStats->awb_stats.blockResult[i].isWP,
                   sizeof(awb_pre_int->awb_hw0_statis.blockResult[i].isWP));
        }

        for(int i = 0; i < RK_AIQ_AWB_STAT_WP_RANGE_NUM_V200; i++) {
            awb_pre_int->awb_hw0_statis.excWpRangeResult[i].Rvalue
                = ispStats->awb_stats.excWpRangeResult[i].Rvalue;
            awb_pre_int->awb_hw0_statis.excWpRangeResult[i].Gvalue
                = ispStats->awb_stats.excWpRangeResult[i].Gvalue;
            awb_pre_int->awb_hw0_statis.excWpRangeResult[i].Bvalue
                = ispStats->awb_stats.excWpRangeResult[i].Bvalue;
            awb_pre_int->awb_hw0_statis.excWpRangeResult[i].WpNo
                = ispStats->awb_stats.excWpRangeResult[i].WpNo;
        }


    } else {
        //V201 TO DO
    }
#endif
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "awb algo pre_process failed");
    // set result to mAiqCore
    comb->awb_pre_res = (RkAiqAlgoPreResAwb*)awb_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAwbHandleInt::processing()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAwbInt* awb_proc_int = (RkAiqAlgoProcAwbInt*)mProcInParam;
    RkAiqAlgoProcResAwbInt* awb_proc_res_int = (RkAiqAlgoProcResAwbInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqProcResComb* comb = &shared->procResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAwbHandle::processing();
    if (ret) {
        comb->awb_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "awb handle processing failed");
    }

    comb->awb_proc_res = NULL;


    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "awb algo processing failed");
    // set result to mAiqCore
    comb->awb_proc_res = (RkAiqAlgoProcResAwb*)awb_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAwbHandleInt::postProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAwbInt* awb_post_int = (RkAiqAlgoPostAwbInt*)mPostInParam;
    RkAiqAlgoPostResAwbInt* awb_post_res_int = (RkAiqAlgoPostResAwbInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqPostResComb* comb = &shared->postResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAwbHandle::postProcess();
    if (ret) {
        comb->awb_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "awb handle postProcess failed");
        return ret;
    }

    comb->awb_post_res = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "awb algo post_process failed");
    // set result to mAiqCore
    comb->awb_post_res = (RkAiqAlgoPostResAwb*)awb_post_res_int ;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

void
RkAiqAfHandleInt::init()
{
    ENTER_ANALYZER_FUNCTION();

    RkAiqAfHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAfInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAfInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAfInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAfInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAfInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAfInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAfInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn
RkAiqAfHandleInt::prepare()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqAfHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "af handle prepare failed");

    RkAiqAlgoConfigAfInt* af_config_int = (RkAiqAlgoConfigAfInt*)mConfig;

    af_config_int->af_config_com.af_mode = 6;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "af algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAfHandleInt::preProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAfInt* af_pre_int = (RkAiqAlgoPreAfInt*)mPreInParam;
    RkAiqAlgoPreResAfInt* af_pre_res_int = (RkAiqAlgoPreResAfInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqPreResComb* comb = &shared->preResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAfHandle::preProcess();
    if (ret) {
        comb->af_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "af handle preProcess failed");
    }

    comb->af_pre_res = NULL;
    af_pre_int->af_stats = ispStats->af_stats;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "af algo pre_process failed");
    // set result to mAiqCore
    comb->af_pre_res = (RkAiqAlgoPreResAf*)af_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAfHandleInt::processing()
{
    ENTER_ANALYZER_FUNCTION();


    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAfInt* af_proc_int = (RkAiqAlgoProcAfInt*)mProcInParam;
    RkAiqAlgoProcResAfInt* af_proc_res_int = (RkAiqAlgoProcResAfInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqProcResComb* comb = &shared->procResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAfHandle::processing();
    if (ret) {
        comb->af_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "af handle processing failed");
    }

    comb->af_proc_res = NULL;
    af_proc_int->af_proc_com.af_stats = ispStats->af_stats;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "af algo processing failed");

    comb->af_proc_res = (RkAiqAlgoProcResAf*)af_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAfHandleInt::postProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAfInt* af_post_int = (RkAiqAlgoPostAfInt*)mPostInParam;
    RkAiqAlgoPostResAfInt* af_post_res_int = (RkAiqAlgoPostResAfInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqPostResComb* comb = &shared->postResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAfHandle::postProcess();
    if (ret) {
        comb->af_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "af handle postProcess failed");
        return ret;
    }

    comb->af_post_res = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "af algo post_process failed");
    // set result to mAiqCore
    comb->af_post_res = (RkAiqAlgoPostResAf*)af_post_res_int ;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

void
RkAiqAnrHandleInt::init()
{
    ENTER_ANALYZER_FUNCTION();

    RkAiqAnrHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAnrInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAnrInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAnrInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAnrInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAnrInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAnrInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAnrInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn
RkAiqAnrHandleInt::prepare()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqAnrHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "anr handle prepare failed");

    RkAiqAlgoConfigAnrInt* anr_config_int = (RkAiqAlgoConfigAnrInt*)mConfig;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    ANRConfig_t *pANRConfig = &anr_config_int->stANRConfig;

#if RK_SIMULATOR_HW
    rkaiq_anr_htmlparmas_t* pAnrHtmlParams = (rkaiq_anr_htmlparmas_t*) malloc(sizeof(rkaiq_anr_htmlparmas_t));;
#if 1
    FILE *fp2 = fopen("rkaiq_anr_html_params.bin", "rb");
    if(fp2 != NULL) {
        memset(&pAnrHtmlParams->stBayernrParams, 0, sizeof(RKAnr_Bayernr_Params_t));
        fread(&pAnrHtmlParams->stBayernrParams, 1, sizeof(RKAnr_Bayernr_Params_t), fp2);
        memset(&pAnrHtmlParams->stMfnrParams, 0, sizeof(RKAnr_Mfnr_Params_t));
        fread(&pAnrHtmlParams->stMfnrParams, 1, sizeof(RKAnr_Mfnr_Params_t), fp2);
        memset(&pAnrHtmlParams->stUvnrParams, 0, sizeof(RKAnr_Uvnr_Params_t));
        fread(&pAnrHtmlParams->stUvnrParams, 1, sizeof(RKAnr_Uvnr_Params_t), fp2);
        memset(&pAnrHtmlParams->stYnrParams, 0, sizeof(RKAnr_Ynr_Params_t));
        fread(&pAnrHtmlParams->stYnrParams, 1, sizeof(RKAnr_Ynr_Params_t), fp2);
        LOGD_ANR("oyyf: %s:(%d) read anr param file sucess! \n", __FUNCTION__, __LINE__);
    } else {
        LOGE_ANR("oyyf: %s:(%d) read anr param file failed! \n", __FUNCTION__, __LINE__);
        return XCAM_RETURN_ERROR_FAILED;
    }
#endif
    //convert html params to anr config params
    if(pAnrHtmlParams != NULL)
    {
        pANRConfig->eMode = ANR_OP_MODE_AUTO;
        memcpy(&pANRConfig->stHtmlParams.stBayernrParams, &pAnrHtmlParams->stBayernrParams, sizeof(RKAnr_Bayernr_Params_t));
        memcpy(&pANRConfig->stHtmlParams.stMfnrParams, &pAnrHtmlParams->stMfnrParams, sizeof(RKAnr_Mfnr_Params_t));
        memcpy(&pANRConfig->stHtmlParams.stUvnrParams, &pAnrHtmlParams->stUvnrParams, sizeof(RKAnr_Uvnr_Params_t));
        memcpy(&pANRConfig->stHtmlParams.stYnrParams, &pAnrHtmlParams->stYnrParams, sizeof(RKAnr_Ynr_Params_t));

        pANRConfig->refYuvBit = 8;
    } else {
        LOGE_ANR("oyyf: %s:(%d) exit \n", __FUNCTION__, __LINE__);
        return XCAM_RETURN_ERROR_FAILED;
    }
#endif

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "anr algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAnrHandleInt::preProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAnrInt* anr_pre_int = (RkAiqAlgoPreAnrInt*)mPreInParam;
    RkAiqAlgoPreResAnrInt* anr_pre_res_int = (RkAiqAlgoPreResAnrInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqIspStats* ispStats = &shared->ispStats;
    RkAiqPreResComb* comb = &shared->preResComb;

    ret = RkAiqAnrHandle::preProcess();
    if (ret) {
        comb->anr_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "anr handle preProcess failed");
    }

    comb->anr_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "anr algo pre_process failed");

    // set result to mAiqCore
    comb->anr_pre_res = (RkAiqAlgoPreResAnr*)anr_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAnrHandleInt::processing()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAnrInt* anr_proc_int = (RkAiqAlgoProcAnrInt*)mProcInParam;
    RkAiqAlgoProcResAnrInt* anr_proc_res_int = (RkAiqAlgoProcResAnrInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqProcResComb* comb = &shared->procResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;
    static int anr_proc_framecnt = 0;
    anr_proc_framecnt++;

    ret = RkAiqAnrHandle::processing();
    if (ret) {
        comb->anr_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "anr handle processing failed");
    }
    comb->anr_proc_res = NULL;

    // TODO: fill procParam
    anr_proc_int->iso = shared->iso;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "anr algo processing failed");

    comb->anr_proc_res = (RkAiqAlgoProcResAnr*)anr_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAnrHandleInt::postProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAnrInt* anr_post_int = (RkAiqAlgoPostAnrInt*)mPostInParam;
    RkAiqAlgoPostResAnrInt* anr_post_res_int = (RkAiqAlgoPostResAnrInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqPostResComb* comb = &shared->postResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAnrHandle::postProcess();
    if (ret) {
        comb->anr_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "anr handle postProcess failed");
        return ret;
    }

    comb->anr_post_res = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "anr algo post_process failed");
    // set result to mAiqCore
    comb->anr_post_res = (RkAiqAlgoPostResAnr*)anr_post_res_int ;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

void
RkAiqAsharpHandleInt::init()
{
    ENTER_ANALYZER_FUNCTION();

    RkAiqAsharpHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAsharpInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAsharpInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAsharpInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAsharpInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAsharpInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAsharpInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAsharpInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn
RkAiqAsharpHandleInt::prepare()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqAsharpHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "asharp handle prepare failed");

    RkAiqAlgoConfigAsharpInt* asharp_config_int = (RkAiqAlgoConfigAsharpInt*)mConfig;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    AsharpConfig_t *pAsharpConfig = &asharp_config_int->stAsharpConfig;

#if RK_SIMULATOR_HW
    rkaiq_asharp_htmlparmas_t* pAsharpHtmlParams = (rkaiq_asharp_htmlparmas_t *)malloc(sizeof(rkaiq_asharp_htmlparmas_t));
#if 1
    FILE *fp2 = fopen("rkaiq_asharp_html_params.bin", "rb");
    if(fp2 != NULL) {
        memset(&pAsharpHtmlParams->stSharpParam, 0, sizeof(RKAsharp_Sharp_Params_t));
        fread(&pAsharpHtmlParams->stSharpParam, 1, sizeof(RKAsharp_Sharp_Params_t), fp2);
        memset(&pAsharpHtmlParams->stEdgefilterParams, 0, sizeof(RKAsharp_EdgeFilter_Params_t));
        fread(&pAsharpHtmlParams->stEdgefilterParams, 1, sizeof(RKAsharp_EdgeFilter_Params_t), fp2);
        fclose(fp2);
        LOGD_ASHARP("oyyf: %s:(%d) read sharp param file sucess! \n", __FUNCTION__, __LINE__);
    } else {
        LOGE_ASHARP("oyyf: %s:(%d) read sharp param file failed! \n", __FUNCTION__, __LINE__);
        return XCAM_RETURN_ERROR_FAILED;
    }
#endif
    //convert html params to anr config params
    if(pAsharpHtmlParams != NULL)
    {
        pAsharpConfig->eMode = ASHARP_OP_MODE_AUTO;
        memcpy(&pAsharpConfig->stHtmlParams.stSharpParam, &pAsharpHtmlParams->stSharpParam, sizeof(RKAsharp_Sharp_Params_t));
        memcpy(&pAsharpConfig->stHtmlParams.stEdgefilterParams, &pAsharpHtmlParams->stEdgefilterParams, sizeof(RKAsharp_EdgeFilter_Params_t));
    } else {
        LOGE_ASHARP("oyyf: %s:(%d) exit \n", __FUNCTION__, __LINE__);
        return XCAM_RETURN_ERROR_FAILED;
    }
#endif

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "asharp algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAsharpHandleInt::preProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAsharpInt* asharp_pre_int = (RkAiqAlgoPreAsharpInt*)mPreInParam;
    RkAiqAlgoPreResAsharpInt* asharp_pre_res_int = (RkAiqAlgoPreResAsharpInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqIspStats* ispStats = &shared->ispStats;
    RkAiqPreResComb* comb = &shared->preResComb;

    ret = RkAiqAsharpHandle::preProcess();
    if (ret) {
        comb->asharp_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "asharp handle preProcess failed");
    }

    comb->asharp_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "asharp algo pre_process failed");
    // set result to mAiqCore
    comb->asharp_pre_res = (RkAiqAlgoPreResAsharp*)asharp_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAsharpHandleInt::processing()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAsharpInt* asharp_proc_int = (RkAiqAlgoProcAsharpInt*)mProcInParam;
    RkAiqAlgoProcResAsharpInt* asharp_proc_res_int = (RkAiqAlgoProcResAsharpInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqProcResComb* comb = &shared->procResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;
    static int asharp_proc_framecnt = 0;
    asharp_proc_framecnt++;

    ret = RkAiqAsharpHandle::processing();
    if (ret) {
        comb->asharp_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "asharp handle processing failed");
    }

    comb->asharp_proc_res = NULL;

    // TODO: fill procParam
    asharp_proc_int->iso = shared->iso;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "asharp algo processing failed");

    comb->asharp_proc_res = (RkAiqAlgoProcResAsharp*)asharp_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAsharpHandleInt::postProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAsharpInt* asharp_post_int = (RkAiqAlgoPostAsharpInt*)mPostInParam;
    RkAiqAlgoPostResAsharpInt* asharp_post_res_int = (RkAiqAlgoPostResAsharpInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqPostResComb* comb = &shared->postResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAsharpHandle::postProcess();
    if (ret) {
        comb->asharp_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "asharp handle postProcess failed");
        return ret;
    }

    comb->asharp_post_res = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "asharp algo post_process failed");
    // set result to mAiqCore
    comb->asharp_post_res = (RkAiqAlgoPostResAsharp*)asharp_post_res_int ;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

void
RkAiqAdhazHandleInt::init()
{
    ENTER_ANALYZER_FUNCTION();

    RkAiqAdhazHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAdhazInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAdhazInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAdhazInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAdhazInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAdhazInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAdhazInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAdhazInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn
RkAiqAdhazHandleInt::prepare()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqAdhazHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "adhaz handle prepare failed");

    RkAiqAlgoConfigAdhazInt* adhaz_config_int = (RkAiqAlgoConfigAdhazInt*)mConfig;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;

    adhaz_config_int->calib = shared->calib;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "adhaz algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAdhazHandleInt::preProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAdhazInt* adhaz_pre_int = (RkAiqAlgoPreAdhazInt*)mPreInParam;
    RkAiqAlgoPreResAdhazInt* adhaz_pre_res_int = (RkAiqAlgoPreResAdhazInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqIspStats* ispStats = &shared->ispStats;
    RkAiqPreResComb* comb = &shared->preResComb;

    ret = RkAiqAdhazHandle::preProcess();
    if (ret) {
        comb->adhaz_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "adhaz handle preProcess failed");
    }

    comb->adhaz_pre_res = NULL;

#ifdef RK_SIMULATOR_HW
    //nothing todo
#endif
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "adhaz algo pre_process failed");

    // set result to mAiqCore
    comb->adhaz_pre_res = (RkAiqAlgoPreResAdhaz*)adhaz_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAdhazHandleInt::processing()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAdhazInt* adhaz_proc_int = (RkAiqAlgoProcAdhazInt*)mProcInParam;
    RkAiqAlgoProcResAdhazInt* adhaz_proc_res_int = (RkAiqAlgoProcResAdhazInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqProcResComb* comb = &shared->procResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAdhazHandle::processing();
    if (ret) {
        comb->adhaz_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "adhaz handle processing failed");
    }

    adhaz_proc_int->pCalibDehaze = shared->calib;

    comb->adhaz_proc_res = NULL;

#ifdef RK_SIMULATOR_HW
    //nothing todo
#endif
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "adhaz algo processing failed");

    comb->adhaz_proc_res = (RkAiqAlgoProcResAdhaz*)adhaz_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAdhazHandleInt::postProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAdhazInt* adhaz_post_int = (RkAiqAlgoPostAdhazInt*)mPostInParam;
    RkAiqAlgoPostResAdhazInt* adhaz_post_res_int = (RkAiqAlgoPostResAdhazInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqPostResComb* comb = &shared->postResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAdhazHandle::postProcess();
    if (ret) {
        comb->adhaz_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "adhaz handle postProcess failed");
        return ret;
    }

    comb->adhaz_post_res = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "adhaz algo post_process failed");
    // set result to mAiqCore
    comb->adhaz_post_res = (RkAiqAlgoPostResAdhaz*)adhaz_post_res_int ;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

void
RkAiqAhdrHandleInt::init()
{
    ENTER_ANALYZER_FUNCTION();

    RkAiqAhdrHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAhdrInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAhdrInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAhdrInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAhdrInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAhdrInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAhdrInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAhdrInt());

    EXIT_ANALYZER_FUNCTION();
}
XCamReturn
RkAiqAhdrHandleInt::updateConfig()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    //TODO
    mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt = mNewAtt;
        updateAtt = false;
        rk_aiq_uapi_ahdr_SetAttrib(mAlgoCtx, mCurAtt, false);
    }
    mCfgMutex.unlock();

    // TODO
    //rk_aiq_uapi_ahdr_SetAttrib(mAlgoCtx, mCurAtt, false);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAhdrHandleInt::setAttrib(ahdr_attrib_t att)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    //TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    updateAtt = true;
    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAhdrHandleInt::prepare()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqAhdrHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "ahdr handle prepare failed");

    RkAiqAlgoConfigAhdrInt* ahdr_config_int = (RkAiqAlgoConfigAhdrInt*)mConfig;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;

    //TODO
    ahdr_config_int->rawHeight = shared->snsDes.sensor_output_height;
    ahdr_config_int->rawWidth = shared->snsDes.sensor_output_width;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "ahdr algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAhdrHandleInt::preProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAhdrInt* ahdr_pre_int = (RkAiqAlgoPreAhdrInt*)mPreInParam;
    RkAiqAlgoPreResAhdrInt* ahdr_pre_res_int = (RkAiqAlgoPreResAhdrInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqIspStats* ispStats = &shared->ispStats;
    RkAiqPreResComb* comb = &shared->preResComb;

    ret = RkAiqAhdrHandle::preProcess();
    if (ret) {
        comb->ahdr_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "ahdr handle preProcess failed");
    }

    if(!shared->ispStats.ahdr_stats_valid && !shared->init) {
        LOGD("no ahdr stats, ignore!");
        // TODO: keep last result ?
        //         comb->ahdr_proc_res = NULL;
        //
        return XCAM_RETURN_BYPASS;
    }

    comb->ahdr_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "ahdr algo pre_process failed");

    // set result to mAiqCore
    comb->ahdr_pre_res = (RkAiqAlgoPreResAhdr*)ahdr_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAhdrHandleInt::processing()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAhdrInt* ahdr_proc_int = (RkAiqAlgoProcAhdrInt*)mProcInParam;
    RkAiqAlgoProcResAhdrInt* ahdr_proc_res_int = (RkAiqAlgoProcResAhdrInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqProcResComb* comb = &shared->procResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAhdrHandle::processing();
    if (ret) {
        comb->ahdr_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "ahdr handle processing failed");
    }

    if(!shared->ispStats.ahdr_stats_valid && !shared->init) {
        LOGD("no ahdr stats, ignore!");
        // TODO: keep last result ?
        //         comb->ahdr_proc_res = NULL;
        //
        return XCAM_RETURN_BYPASS;
    } else {
        memcpy(&ahdr_proc_int->ispAhdrStats, &ispStats->ahdr_stats, sizeof(rkisp_ahdr_stats_t));
    }

    comb->ahdr_proc_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "ahdr algo processing failed");

    comb->ahdr_proc_res = (RkAiqAlgoProcResAhdr*)ahdr_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAhdrHandleInt::postProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAhdrInt* ahdr_post_int = (RkAiqAlgoPostAhdrInt*)mPostInParam;
    RkAiqAlgoPostResAhdrInt* ahdr_post_res_int = (RkAiqAlgoPostResAhdrInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqPostResComb* comb = &shared->postResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAhdrHandle::postProcess();
    if (ret) {
        comb->ahdr_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "ahdr handle postProcess failed");
        return ret;
    }

    if(!shared->ispStats.ahdr_stats_valid && !shared->init) {
        LOGD("no ahdr stats, ignore!");
        // TODO: keep last result ?
        //         comb->ahdr_proc_res = NULL;
        //
        return XCAM_RETURN_BYPASS;
    }

    comb->ahdr_post_res = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "ahdr algo post_process failed");
    // set result to mAiqCore
    comb->ahdr_post_res = (RkAiqAlgoPostResAhdr*)ahdr_post_res_int ;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

void
RkAiqAsdHandleInt::init()
{
    ENTER_ANALYZER_FUNCTION();

    RkAiqAsdHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAsdInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAsdInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAsdInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAsdInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAsdInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAsdInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAsdInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn
RkAiqAsdHandleInt::prepare()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqAsdHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "asd handle prepare failed");

    RkAiqAlgoConfigAsdInt* asd_config_int = (RkAiqAlgoConfigAsdInt*)mConfig;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "asd algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAsdHandleInt::preProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAsdInt* asd_pre_int = (RkAiqAlgoPreAsdInt*)mPreInParam;
    RkAiqAlgoPreResAsdInt* asd_pre_res_int = (RkAiqAlgoPreResAsdInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqIspStats* ispStats = &shared->ispStats;
    RkAiqPreResComb* comb = &shared->preResComb;

    ret = RkAiqAsdHandle::preProcess();
    if (ret) {
        comb->asd_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "asd handle preProcess failed");
    }

    comb->asd_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "asd algo pre_process failed");

    // set result to mAiqCore
    comb->asd_pre_res = (RkAiqAlgoPreResAsd*)asd_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAsdHandleInt::processing()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAsdInt* asd_proc_int = (RkAiqAlgoProcAsdInt*)mProcInParam;
    RkAiqAlgoProcResAsdInt* asd_proc_res_int = (RkAiqAlgoProcResAsdInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqProcResComb* comb = &shared->procResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAsdHandle::processing();
    if (ret) {
        comb->asd_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "asd handle processing failed");
    }

    comb->asd_proc_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "asd algo processing failed");

    comb->asd_proc_res = (RkAiqAlgoProcResAsd*)asd_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAsdHandleInt::postProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAsdInt* asd_post_int = (RkAiqAlgoPostAsdInt*)mPostInParam;
    RkAiqAlgoPostResAsdInt* asd_post_res_int = (RkAiqAlgoPostResAsdInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqPostResComb* comb = &shared->postResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAsdHandle::postProcess();
    if (ret) {
        comb->asd_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "asd handle postProcess failed");
        return ret;
    }

    comb->asd_post_res = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "asd algo post_process failed");
    // set result to mAiqCore
    comb->asd_post_res = (RkAiqAlgoPostResAsd*)asd_post_res_int ;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

void
RkAiqAcpHandleInt::init()
{
    ENTER_ANALYZER_FUNCTION();

    RkAiqAcpHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAcpInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAcpInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAcpInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAcpInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAcpInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAcpInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAcpInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn
RkAiqAcpHandleInt::prepare()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqAcpHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "acp handle prepare failed");

    RkAiqAlgoConfigAcpInt* acp_config_int = (RkAiqAlgoConfigAcpInt*)mConfig;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "acp algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAcpHandleInt::preProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAcpInt* acp_pre_int = (RkAiqAlgoPreAcpInt*)mPreInParam;
    RkAiqAlgoPreResAcpInt* acp_pre_res_int = (RkAiqAlgoPreResAcpInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqIspStats* ispStats = &shared->ispStats;
    RkAiqPreResComb* comb = &shared->preResComb;

    ret = RkAiqAcpHandle::preProcess();
    if (ret) {
        comb->acp_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "acp handle preProcess failed");
    }

    comb->acp_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "acp algo pre_process failed");

    // set result to mAiqCore
    comb->acp_pre_res = (RkAiqAlgoPreResAcp*)acp_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAcpHandleInt::processing()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAcpInt* acp_proc_int = (RkAiqAlgoProcAcpInt*)mProcInParam;
    RkAiqAlgoProcResAcpInt* acp_proc_res_int = (RkAiqAlgoProcResAcpInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqProcResComb* comb = &shared->procResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAcpHandle::processing();
    if (ret) {
        comb->acp_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "acp handle processing failed");
    }

    comb->acp_proc_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "acp algo processing failed");

    comb->acp_proc_res = (RkAiqAlgoProcResAcp*)acp_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAcpHandleInt::postProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAeInt* ae_post_int = (RkAiqAlgoPostAeInt*)mPostInParam;
    RkAiqAlgoPostResAeInt* ae_post_res_int = (RkAiqAlgoPostResAeInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqPostResComb* comb = &shared->postResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAcpHandle::postProcess();
    if (ret) {
        comb->ae_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "ae handle postProcess failed");
        return ret;
    }

    comb->ae_post_res = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "ae algo post_process failed");
    // set result to mAiqCore
    comb->ae_post_res = (RkAiqAlgoPostResAe*)ae_post_res_int ;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

void
RkAiqA3dlutHandleInt::init()
{
    ENTER_ANALYZER_FUNCTION();

    RkAiqA3dlutHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigA3dlutInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreA3dlutInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResA3dlutInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcA3dlutInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResA3dlutInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostA3dlutInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResA3dlutInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn
RkAiqA3dlutHandleInt::prepare()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqA3dlutHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "a3dlut handle prepare failed");

    RkAiqAlgoConfigA3dlutInt* a3dlut_config_int = (RkAiqAlgoConfigA3dlutInt*)mConfig;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "a3dlut algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqA3dlutHandleInt::preProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreA3dlutInt* a3dlut_pre_int = (RkAiqAlgoPreA3dlutInt*)mPreInParam;
    RkAiqAlgoPreResA3dlutInt* a3dlut_pre_res_int = (RkAiqAlgoPreResA3dlutInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqIspStats* ispStats = &shared->ispStats;
    RkAiqPreResComb* comb = &shared->preResComb;

    ret = RkAiqA3dlutHandle::preProcess();
    if (ret) {
        comb->a3dlut_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "a3dlut handle preProcess failed");
    }

    comb->a3dlut_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "a3dlut algo pre_process failed");

    // set result to mAiqCore
    comb->a3dlut_pre_res = (RkAiqAlgoPreResA3dlut*)a3dlut_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqA3dlutHandleInt::processing()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcA3dlutInt* a3dlut_proc_int = (RkAiqAlgoProcA3dlutInt*)mProcInParam;
    RkAiqAlgoProcResA3dlutInt* a3dlut_proc_res_int = (RkAiqAlgoProcResA3dlutInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqProcResComb* comb = &shared->procResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqA3dlutHandle::processing();
    if (ret) {
        comb->a3dlut_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "a3dlut handle processing failed");
    }

    comb->a3dlut_proc_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "a3dlut algo processing failed");

    comb->a3dlut_proc_res = (RkAiqAlgoProcResA3dlut*)a3dlut_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqA3dlutHandleInt::postProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostA3dlutInt* a3dlut_post_int = (RkAiqAlgoPostA3dlutInt*)mPostInParam;
    RkAiqAlgoPostResA3dlutInt* a3dlut_post_res_int = (RkAiqAlgoPostResA3dlutInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqPostResComb* comb = &shared->postResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqA3dlutHandle::postProcess();
    if (ret) {
        comb->a3dlut_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "a3dlut handle postProcess failed");
        return ret;
    }

    comb->a3dlut_post_res = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "a3dlut algo post_process failed");
    // set result to mAiqCore
    comb->a3dlut_post_res = (RkAiqAlgoPostResA3dlut*)a3dlut_post_res_int ;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

void
RkAiqAblcHandleInt::init()
{
    ENTER_ANALYZER_FUNCTION();

    RkAiqAblcHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAblcInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAblcInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAblcInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAblcInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAblcInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAblcInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAblcInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn
RkAiqAblcHandleInt::prepare()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqAblcHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "ablc handle prepare failed");

    RkAiqAlgoConfigAblcInt* ablc_config_int = (RkAiqAlgoConfigAblcInt*)mConfig;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "ablc algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAblcHandleInt::preProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAblcInt* ablc_pre_int = (RkAiqAlgoPreAblcInt*)mPreInParam;
    RkAiqAlgoPreResAblcInt* ablc_pre_res_int = (RkAiqAlgoPreResAblcInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqIspStats* ispStats = &shared->ispStats;
    RkAiqPreResComb* comb = &shared->preResComb;

    ret = RkAiqAblcHandle::preProcess();
    if (ret) {
        comb->ablc_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "ablc handle preProcess failed");
    }

    comb->ablc_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "ablc algo pre_process failed");

    // set result to mAiqCore
    comb->ablc_pre_res = (RkAiqAlgoPreResAblc*)ablc_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAblcHandleInt::processing()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAblcInt* ablc_proc_int = (RkAiqAlgoProcAblcInt*)mProcInParam;
    RkAiqAlgoProcResAblcInt* ablc_proc_res_int = (RkAiqAlgoProcResAblcInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqProcResComb* comb = &shared->procResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAblcHandle::processing();
    if (ret) {
        comb->ablc_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "ablc handle processing failed");
    }

    comb->ablc_proc_res = NULL;
    ablc_proc_int->iso = shared->iso;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "ablc algo processing failed");

    comb->ablc_proc_res = (RkAiqAlgoProcResAblc*)ablc_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAblcHandleInt::postProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAblcInt* ablc_post_int = (RkAiqAlgoPostAblcInt*)mPostInParam;
    RkAiqAlgoPostResAblcInt* ablc_post_res_int = (RkAiqAlgoPostResAblcInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqPostResComb* comb = &shared->postResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAblcHandle::postProcess();
    if (ret) {
        comb->ablc_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "ablc handle postProcess failed");
        return ret;
    }

    comb->ablc_post_res = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "ablc algo post_process failed");
    // set result to mAiqCore
    comb->ablc_post_res = (RkAiqAlgoPostResAblc*)ablc_post_res_int ;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

void
RkAiqAccmHandleInt::init()
{
    ENTER_ANALYZER_FUNCTION();

    RkAiqAccmHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAccmInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAccmInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAccmInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAccmInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAccmInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAccmInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAccmInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn
RkAiqAccmHandleInt::prepare()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqAccmHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "accm handle prepare failed");

    RkAiqAlgoConfigAccmInt* accm_config_int = (RkAiqAlgoConfigAccmInt*)mConfig;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "accm algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAccmHandleInt::preProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAccmInt* accm_pre_int = (RkAiqAlgoPreAccmInt*)mPreInParam;
    RkAiqAlgoPreResAccmInt* accm_pre_res_int = (RkAiqAlgoPreResAccmInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqIspStats* ispStats = &shared->ispStats;
    RkAiqPreResComb* comb = &shared->preResComb;

    ret = RkAiqAccmHandle::preProcess();
    if (ret) {
        comb->accm_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "accm handle preProcess failed");
    }

    comb->accm_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "accm algo pre_process failed");

    // set result to mAiqCore
    comb->accm_pre_res = (RkAiqAlgoPreResAccm*)accm_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAccmHandleInt::processing()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAccmInt* accm_proc_int = (RkAiqAlgoProcAccmInt*)mProcInParam;
    RkAiqAlgoProcResAccmInt* accm_proc_res_int = (RkAiqAlgoProcResAccmInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqProcResComb* comb = &shared->procResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAccmHandle::processing();
    if (ret) {
        comb->accm_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "accm handle processing failed");
    }

    comb->accm_proc_res = NULL;
    // TODO should check if the rk awb algo used
    RkAiqAlgoProcResAwb* awb_res =
        (RkAiqAlgoProcResAwb*)(shared->procResComb.awb_proc_res);
    RkAiqAlgoProcResAwbInt* awb_res_int =
        (RkAiqAlgoProcResAwbInt*)(shared->procResComb.awb_proc_res);

    if(awb_res ) {
        if(awb_res->awb_gain_algo.grgain < DIVMIN ||
                awb_res->awb_gain_algo.gbgain < DIVMIN ) {
            ret = XCAM_RETURN_ERROR_FAILED;
        } else {
            accm_proc_int->accm_sw_info.awbGain[0] =
                awb_res->awb_gain_algo.rgain / awb_res->awb_gain_algo.grgain;

            accm_proc_int->accm_sw_info.awbGain[1] = awb_res->awb_gain_algo.bgain / awb_res->awb_gain_algo.gbgain;
            ret = XCAM_RETURN_NO_ERROR;
        }
        accm_proc_int->accm_sw_info.awbIIRDampCoef =  awb_res_int->awb_smooth_factor;
    }
    RKAIQCORE_CHECK_RET(ret, "fail to get awb_gain_algo");
#if 0
    RkAiqAlgoPreResAeInt *ae_int = (RkAiqAlgoPreResAeInt*)shared->preResComb.ae_pre_res;
    ret = XCAM_RETURN_ERROR_FAILED;
    if( shared->preResComb.ae_pre_res) {
        int fNormalIndex =  ae_int->aecPreResult.NormalIndex;
        if(shared->working_mode == RK_AIQ_WORKING_MODE_NORMAL || shared->working_mode == RK_AIQ_WORKING_MODE_SENSOR_HDR) {
            accm_proc_int->accm_sw_info.sensorGain = ae_int->aecPreResult.LinearExp.exp_real_params.analog_gain;
        } else {
            accm_proc_int->accm_sw_info.sensorGain = ae_int->aecPreResult.HdrExp[fNormalIndex].exp_real_params.analog_gain;
        }
        ret = XCAM_RETURN_NO_ERROR;
    }
    RKAIQCORE_CHECK_RET(ret, "fail to get sensor gain ");
#else
    // to do
    accm_proc_int->accm_sw_info.sensorGain = 1.0;
#endif
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "accm algo processing failed");

    comb->accm_proc_res = (RkAiqAlgoProcResAccm*)accm_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAccmHandleInt::postProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAccmInt* accm_post_int = (RkAiqAlgoPostAccmInt*)mPostInParam;
    RkAiqAlgoPostResAccmInt* accm_post_res_int = (RkAiqAlgoPostResAccmInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqPostResComb* comb = &shared->postResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAccmHandle::postProcess();
    if (ret) {
        comb->accm_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "accm handle postProcess failed");
        return ret;
    }

    comb->accm_post_res = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "accm algo post_process failed");
    // set result to mAiqCore
    comb->accm_post_res = (RkAiqAlgoPostResAccm*)accm_post_res_int ;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

void
RkAiqAcgcHandleInt::init()
{
    ENTER_ANALYZER_FUNCTION();

    RkAiqAcgcHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAcgcInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAcgcInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAcgcInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAcgcInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAcgcInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAcgcInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAcgcInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn
RkAiqAcgcHandleInt::prepare()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqAcgcHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "acgc handle prepare failed");

    RkAiqAlgoConfigAcgcInt* acgc_config_int = (RkAiqAlgoConfigAcgcInt*)mConfig;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "acgc algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAcgcHandleInt::preProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAcgcInt* acgc_pre_int = (RkAiqAlgoPreAcgcInt*)mPreInParam;
    RkAiqAlgoPreResAcgcInt* acgc_pre_res_int = (RkAiqAlgoPreResAcgcInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqIspStats* ispStats = &shared->ispStats;
    RkAiqPreResComb* comb = &shared->preResComb;

    ret = RkAiqAcgcHandle::preProcess();
    if (ret) {
        comb->acgc_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "acgc handle preProcess failed");
    }

    comb->acgc_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "acgc algo pre_process failed");

    // set result to mAiqCore
    comb->acgc_pre_res = (RkAiqAlgoPreResAcgc*)acgc_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAcgcHandleInt::processing()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAcgcInt* acgc_proc_int = (RkAiqAlgoProcAcgcInt*)mProcInParam;
    RkAiqAlgoProcResAcgcInt* acgc_proc_res_int = (RkAiqAlgoProcResAcgcInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqProcResComb* comb = &shared->procResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAcgcHandle::processing();
    if (ret) {
        comb->acgc_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "acgc handle processing failed");
    }

    comb->acgc_proc_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "acgc algo processing failed");

    comb->acgc_proc_res = (RkAiqAlgoProcResAcgc*)acgc_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAcgcHandleInt::postProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAcgcInt* acgc_post_int = (RkAiqAlgoPostAcgcInt*)mPostInParam;
    RkAiqAlgoPostResAcgcInt* acgc_post_res_int = (RkAiqAlgoPostResAcgcInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqPostResComb* comb = &shared->postResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAcgcHandle::postProcess();
    if (ret) {
        comb->acgc_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "acgc handle postProcess failed");
        return ret;
    }

    comb->acgc_post_res = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "acgc algo post_process failed");
    // set result to mAiqCore
    comb->acgc_post_res = (RkAiqAlgoPostResAcgc*)acgc_post_res_int ;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

void
RkAiqAdebayerHandleInt::init()
{
    ENTER_ANALYZER_FUNCTION();

    RkAiqAdebayerHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAdebayerInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAdebayerInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAdebayerInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAdebayerInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAdebayerInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAdebayerInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAdebayerInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn
RkAiqAdebayerHandleInt::updateConfig()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    //TODO
    mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt = mNewAtt;
        updateAtt = false;
        rk_aiq_uapi_adebayer_SetAttrib(mAlgoCtx, mCurAtt, false);
    }
    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAdebayerHandleInt::setAttrib(adebayer_attrib_t att)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    //TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore
    if (0 != memcmp(&mCurAtt, &att, sizeof(adebayer_attrib_t))) {
        mNewAtt = att;
        updateAtt = true;
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}


XCamReturn
RkAiqAdebayerHandleInt::prepare()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqAdebayerHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "adebayer handle prepare failed");

    RkAiqAlgoConfigAdebayerInt* adebayer_config_int = (RkAiqAlgoConfigAdebayerInt*)mConfig;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "adebayer algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAdebayerHandleInt::preProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAdebayerInt* adebayer_pre_int = (RkAiqAlgoPreAdebayerInt*)mPreInParam;
    RkAiqAlgoPreResAdebayerInt* adebayer_pre_res_int = (RkAiqAlgoPreResAdebayerInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqIspStats* ispStats = &shared->ispStats;
    RkAiqPreResComb* comb = &shared->preResComb;

    ret = RkAiqAdebayerHandle::preProcess();
    if (ret) {
        comb->adebayer_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "adebayer handle preProcess failed");
    }

    comb->adebayer_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "adebayer algo pre_process failed");

    // set result to mAiqCore
    comb->adebayer_pre_res = (RkAiqAlgoPreResAdebayer*)adebayer_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAdebayerHandleInt::processing()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAdebayerInt* adebayer_proc_int = (RkAiqAlgoProcAdebayerInt*)mProcInParam;
    RkAiqAlgoProcResAdebayerInt* adebayer_proc_res_int = (RkAiqAlgoProcResAdebayerInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqProcResComb* comb = &shared->procResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAdebayerHandle::processing();
    if (ret) {
        comb->adebayer_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "adebayer handle processing failed");
    }

    comb->adebayer_proc_res = NULL;
    // TODO: fill procParam
    adebayer_proc_int->iso = shared->iso;
    adebayer_proc_int->pCalibDb = shared->calib;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "adebayer algo processing failed");

    comb->adebayer_proc_res = (RkAiqAlgoProcResAdebayer*)adebayer_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAdebayerHandleInt::postProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAdebayerInt* adebayer_post_int = (RkAiqAlgoPostAdebayerInt*)mPostInParam;
    RkAiqAlgoPostResAdebayerInt* adebayer_post_res_int = (RkAiqAlgoPostResAdebayerInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqPostResComb* comb = &shared->postResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAdebayerHandle::postProcess();
    if (ret) {
        comb->adebayer_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "adebayer handle postProcess failed");
        return ret;
    }

    comb->adebayer_post_res = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "adebayer algo post_process failed");
    // set result to mAiqCore
    comb->adebayer_post_res = (RkAiqAlgoPostResAdebayer*)adebayer_post_res_int ;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

void
RkAiqAdpccHandleInt::init()
{
    ENTER_ANALYZER_FUNCTION();

    RkAiqAdpccHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAdpccInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAdpccInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAdpccInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAdpccInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAdpccInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAdpccInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAdpccInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn
RkAiqAdpccHandleInt::prepare()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqAdpccHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "adpcc handle prepare failed");

    RkAiqAlgoConfigAdpccInt* adpcc_config_int = (RkAiqAlgoConfigAdpccInt*)mConfig;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "adpcc algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAdpccHandleInt::preProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAdpccInt* adpcc_pre_int = (RkAiqAlgoPreAdpccInt*)mPreInParam;
    RkAiqAlgoPreResAdpccInt* adpcc_pre_res_int = (RkAiqAlgoPreResAdpccInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqIspStats* ispStats = &shared->ispStats;
    RkAiqPreResComb* comb = &shared->preResComb;

    ret = RkAiqAdpccHandle::preProcess();
    if (ret) {
        comb->adpcc_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "adpcc handle preProcess failed");
    }

    comb->adpcc_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "adpcc algo pre_process failed");

    // set result to mAiqCore
    comb->adpcc_pre_res = (RkAiqAlgoPreResAdpcc*)adpcc_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAdpccHandleInt::processing()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAdpccInt* adpcc_proc_int = (RkAiqAlgoProcAdpccInt*)mProcInParam;
    RkAiqAlgoProcResAdpccInt* adpcc_proc_res_int = (RkAiqAlgoProcResAdpccInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqProcResComb* comb = &shared->procResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAdpccHandle::processing();
    if (ret) {
        comb->adpcc_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "adpcc handle processing failed");
    }

    comb->adpcc_proc_res = NULL;
    // TODO: fill procParam
    adpcc_proc_int->iso = shared->iso;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "adpcc algo processing failed");

    comb->adpcc_proc_res = (RkAiqAlgoProcResAdpcc*)adpcc_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAdpccHandleInt::postProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAsdInt* asd_post_int = (RkAiqAlgoPostAsdInt*)mPostInParam;
    RkAiqAlgoPostResAsdInt* asd_post_res_int = (RkAiqAlgoPostResAsdInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqPostResComb* comb = &shared->postResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAdpccHandle::postProcess();
    if (ret) {
        comb->asd_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "asd handle postProcess failed");
        return ret;
    }

    comb->asd_post_res = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "asd algo post_process failed");
    // set result to mAiqCore
    comb->asd_post_res = (RkAiqAlgoPostResAsd*)asd_post_res_int ;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

void
RkAiqAfecHandleInt::init()
{
    ENTER_ANALYZER_FUNCTION();

    RkAiqAfecHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAfecInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAfecInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAfecInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAfecInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAfecInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAfecInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAfecInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn
RkAiqAfecHandleInt::prepare()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqAfecHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "afec handle prepare failed");

    RkAiqAlgoConfigAfecInt* afec_config_int = (RkAiqAlgoConfigAfecInt*)mConfig;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;

    afec_config_int->output_width = shared->snsDes.sensor_output_width;
    afec_config_int->output_height = shared->snsDes.sensor_output_height;

    memcpy(&afec_config_int->afec_calib_cfg, &shared->calib->afec, sizeof(CalibDb_FEC_t));

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "afec algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAfecHandleInt::preProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAfecInt* afec_pre_int = (RkAiqAlgoPreAfecInt*)mPreInParam;
    RkAiqAlgoPreResAfecInt* afec_pre_res_int = (RkAiqAlgoPreResAfecInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqIspStats* ispStats = &shared->ispStats;
    RkAiqPreResComb* comb = &shared->preResComb;

    ret = RkAiqAfecHandle::preProcess();
    if (ret) {
        comb->afec_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "afec handle preProcess failed");
    }

    comb->afec_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "afec algo pre_process failed");

    // set result to mAiqCore
    comb->afec_pre_res = (RkAiqAlgoPreResAfec*)afec_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAfecHandleInt::processing()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAfecInt* afec_proc_int = (RkAiqAlgoProcAfecInt*)mProcInParam;
    RkAiqAlgoProcResAfecInt* afec_proc_res_int = (RkAiqAlgoProcResAfecInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqProcResComb* comb = &shared->procResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAfecHandle::processing();
    if (ret) {
        comb->afec_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "afec handle processing failed");
    }

    comb->afec_proc_res = NULL;
    //fill procParam
    afec_proc_int->output_width = shared->snsDes.sensor_output_width;
    afec_proc_int->output_height = shared->snsDes.sensor_output_height;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "afec algo processing failed");

    comb->afec_proc_res = (RkAiqAlgoProcResAfec*)afec_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAfecHandleInt::postProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAfecInt* afec_post_int = (RkAiqAlgoPostAfecInt*)mPostInParam;
    RkAiqAlgoPostResAfecInt* afec_post_res_int = (RkAiqAlgoPostResAfecInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqPostResComb* comb = &shared->postResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAfecHandle::postProcess();
    if (ret) {
        comb->afec_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "afec handle postProcess failed");
        return ret;
    }

    comb->afec_post_res = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "afec algo post_process failed");
    // set result to mAiqCore
    comb->afec_post_res = (RkAiqAlgoPostResAfec*)afec_post_res_int ;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

void
RkAiqAgammaHandleInt::init()
{
    ENTER_ANALYZER_FUNCTION();

    RkAiqAgammaHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAgammaInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAgammaInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAgammaInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAgammaInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAgammaInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAgammaInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAgammaInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn
RkAiqAgammaHandleInt::prepare()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqAgammaHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "agamma handle prepare failed");

    RkAiqAlgoConfigAgammaInt* agamma_config_int = (RkAiqAlgoConfigAgammaInt*)mConfig;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;

    agamma_config_int->calib = shared ->calib;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "agamma algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAgammaHandleInt::preProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAgammaInt* agamma_pre_int = (RkAiqAlgoPreAgammaInt*)mPreInParam;
    RkAiqAlgoPreResAgammaInt* agamma_pre_res_int = (RkAiqAlgoPreResAgammaInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqIspStats* ispStats = &shared->ispStats;
    RkAiqPreResComb* comb = &shared->preResComb;

    ret = RkAiqAgammaHandle::preProcess();
    if (ret) {
        comb->agamma_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "agamma handle preProcess failed");
    }

    comb->agamma_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "agamma algo pre_process failed");

    // set result to mAiqCore
    comb->agamma_pre_res = (RkAiqAlgoPreResAgamma*)agamma_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAgammaHandleInt::processing()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAgammaInt* agamma_proc_int = (RkAiqAlgoProcAgammaInt*)mProcInParam;
    RkAiqAlgoProcResAgammaInt* agamma_proc_res_int = (RkAiqAlgoProcResAgammaInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqProcResComb* comb = &shared->procResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAgammaHandle::processing();
    if (ret) {
        comb->agamma_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "agamma handle processing failed");
    }

    comb->agamma_proc_res = NULL;
    agamma_proc_int->calib = shared->calib;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "agamma algo processing failed");

    comb->agamma_proc_res = (RkAiqAlgoProcResAgamma*)agamma_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAgammaHandleInt::postProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAgammaInt* agamma_post_int = (RkAiqAlgoPostAgammaInt*)mPostInParam;
    RkAiqAlgoPostResAgammaInt* agamma_post_res_int = (RkAiqAlgoPostResAgammaInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqPostResComb* comb = &shared->postResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAgammaHandle::postProcess();
    if (ret) {
        comb->agamma_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "agamma handle postProcess failed");
        return ret;
    }

    comb->agamma_post_res = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "agamma algo post_process failed");
    // set result to mAiqCore
    comb->agamma_post_res = (RkAiqAlgoPostResAgamma*)agamma_post_res_int ;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

void
RkAiqAgicHandleInt::init()
{
    ENTER_ANALYZER_FUNCTION();

    RkAiqAgicHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAgicInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAgicInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAgicInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAgicInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAgicInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAgicInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAgicInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn
RkAiqAgicHandleInt::prepare()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqAgicHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "agic handle prepare failed");

    RkAiqAlgoConfigAgicInt* agic_config_int = (RkAiqAlgoConfigAgicInt*)mConfig;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "agic algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAgicHandleInt::preProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAgicInt* agic_pre_int = (RkAiqAlgoPreAgicInt*)mPreInParam;
    RkAiqAlgoPreResAgicInt* agic_pre_res_int = (RkAiqAlgoPreResAgicInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqIspStats* ispStats = &shared->ispStats;
    RkAiqPreResComb* comb = &shared->preResComb;

    ret = RkAiqAgicHandle::preProcess();
    if (ret) {
        comb->agic_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "agic handle preProcess failed");
    }

    comb->agic_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "agic algo pre_process failed");

    // set result to mAiqCore
    comb->agic_pre_res = (RkAiqAlgoPreResAgic*)agic_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAgicHandleInt::processing()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAgicInt* agic_proc_int = (RkAiqAlgoProcAgicInt*)mProcInParam;
    RkAiqAlgoProcResAgicInt* agic_proc_res_int = (RkAiqAlgoProcResAgicInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqProcResComb* comb = &shared->procResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAgicHandle::processing();
    if (ret) {
        comb->agic_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "agic handle processing failed");
    }

    comb->agic_proc_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "agic algo processing failed");

    comb->agic_proc_res = (RkAiqAlgoProcResAgic*)agic_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAgicHandleInt::postProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAgicInt* agic_post_int = (RkAiqAlgoPostAgicInt*)mPostInParam;
    RkAiqAlgoPostResAgicInt* agic_post_res_int = (RkAiqAlgoPostResAgicInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqPostResComb* comb = &shared->postResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAgicHandle::postProcess();
    if (ret) {
        comb->agic_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "agic handle postProcess failed");
        return ret;
    }

    comb->agic_post_res = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "agic algo post_process failed");
    // set result to mAiqCore
    comb->agic_post_res = (RkAiqAlgoPostResAgic*)agic_post_res_int ;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

void
RkAiqAieHandleInt::init()
{
    ENTER_ANALYZER_FUNCTION();

    RkAiqAieHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAieInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAieInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAieInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAieInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAieInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAieInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAieInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn
RkAiqAieHandleInt::prepare()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqAieHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "aie handle prepare failed");

    RkAiqAlgoConfigAieInt* aie_config_int = (RkAiqAlgoConfigAieInt*)mConfig;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "aie algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAieHandleInt::preProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAieInt* aie_pre_int = (RkAiqAlgoPreAieInt*)mPreInParam;
    RkAiqAlgoPreResAieInt* aie_pre_res_int = (RkAiqAlgoPreResAieInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqIspStats* ispStats = &shared->ispStats;
    RkAiqPreResComb* comb = &shared->preResComb;

    ret = RkAiqAieHandle::preProcess();
    if (ret) {
        comb->aie_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "aie handle preProcess failed");
    }

    comb->aie_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "aie algo pre_process failed");

    // set result to mAiqCore
    comb->aie_pre_res = (RkAiqAlgoPreResAie*)aie_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAieHandleInt::processing()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAieInt* aie_proc_int = (RkAiqAlgoProcAieInt*)mProcInParam;
    RkAiqAlgoProcResAieInt* aie_proc_res_int = (RkAiqAlgoProcResAieInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqProcResComb* comb = &shared->procResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAieHandle::processing();
    if (ret) {
        comb->aie_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "aie handle processing failed");
    }

    comb->aie_proc_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "aie algo processing failed");

    comb->aie_proc_res = (RkAiqAlgoProcResAie*)aie_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAieHandleInt::postProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAieInt* aie_post_int = (RkAiqAlgoPostAieInt*)mPostInParam;
    RkAiqAlgoPostResAieInt* aie_post_res_int = (RkAiqAlgoPostResAieInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqPostResComb* comb = &shared->postResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAieHandle::postProcess();
    if (ret) {
        comb->aie_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "aie handle postProcess failed");
        return ret;
    }

    comb->aie_post_res = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "aie algo post_process failed");
    // set result to mAiqCore
    comb->aie_post_res = (RkAiqAlgoPostResAie*)aie_post_res_int ;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

void
RkAiqAldchHandleInt::init()
{
    ENTER_ANALYZER_FUNCTION();

    RkAiqAldchHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAldchInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAldchInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAldchInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAldchInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAldchInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAldchInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAldchInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn
RkAiqAldchHandleInt::prepare()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqAldchHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "aldch handle prepare failed");

    RkAiqAlgoConfigAldchInt* aldch_config_int = (RkAiqAlgoConfigAldchInt*)mConfig;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    // build configs
    aldch_config_int->output_width = shared->snsDes.sensor_output_width;
    aldch_config_int->output_height = shared->snsDes.sensor_output_height;

    memcpy(&aldch_config_int->aldch_calib_cfg, &shared->calib->aldch, sizeof(CalibDb_LDCH_t));

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "aldch algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAldchHandleInt::preProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAldchInt* aldch_pre_int = (RkAiqAlgoPreAldchInt*)mPreInParam;
    RkAiqAlgoPreResAldchInt* aldch_pre_res_int = (RkAiqAlgoPreResAldchInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqIspStats* ispStats = &shared->ispStats;
    RkAiqPreResComb* comb = &shared->preResComb;

    ret = RkAiqAldchHandle::preProcess();
    if (ret) {
        comb->aldch_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "aldch handle preProcess failed");
    }

    comb->aldch_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "aldch algo pre_process failed");

    // set result to mAiqCore
    comb->aldch_pre_res = (RkAiqAlgoPreResAldch*)aldch_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAldchHandleInt::processing()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAldchInt* aldch_proc_int = (RkAiqAlgoProcAldchInt*)mProcInParam;
    RkAiqAlgoProcResAldchInt* aldch_proc_res_int = (RkAiqAlgoProcResAldchInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqProcResComb* comb = &shared->procResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAldchHandle::processing();
    if (ret) {
        comb->aldch_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "aldch handle processing failed");
    }

    comb->aldch_proc_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "aldch algo processing failed");

    comb->aldch_proc_res = (RkAiqAlgoProcResAldch*)aldch_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAldchHandleInt::postProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAldchInt* aldch_post_int = (RkAiqAlgoPostAldchInt*)mPostInParam;
    RkAiqAlgoPostResAldchInt* aldch_post_res_int = (RkAiqAlgoPostResAldchInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqPostResComb* comb = &shared->postResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAldchHandle::postProcess();
    if (ret) {
        comb->aldch_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "aldch handle postProcess failed");
        return ret;
    }

    comb->aldch_post_res = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "aldch algo post_process failed");
    // set result to mAiqCore
    comb->aldch_post_res = (RkAiqAlgoPostResAldch*)aldch_post_res_int ;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

void
RkAiqAlscHandleInt::init()
{
    ENTER_ANALYZER_FUNCTION();

    RkAiqAlscHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAlscInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAlscInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAlscInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAlscInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAlscInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAlscInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAlscInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn
RkAiqAlscHandleInt::prepare()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqAlscHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "alsc handle prepare failed");

    RkAiqAlgoConfigAlscInt* alsc_config_int = (RkAiqAlgoConfigAlscInt*)mConfig;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "alsc algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAlscHandleInt::preProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAlscInt* alsc_pre_int = (RkAiqAlgoPreAlscInt*)mPreInParam;
    RkAiqAlgoPreResAlscInt* alsc_pre_res_int = (RkAiqAlgoPreResAlscInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqIspStats* ispStats = &shared->ispStats;
    RkAiqPreResComb* comb = &shared->preResComb;

    ret = RkAiqAlscHandle::preProcess();
    if (ret) {
        comb->alsc_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "alsc handle preProcess failed");
    }

    comb->alsc_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "alsc algo pre_process failed");

    // set result to mAiqCore
    comb->alsc_pre_res = (RkAiqAlgoPreResAlsc*)alsc_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAlscHandleInt::processing()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAlscInt* alsc_proc_int = (RkAiqAlgoProcAlscInt*)mProcInParam;
    RkAiqAlgoProcResAlscInt* alsc_proc_res_int = (RkAiqAlgoProcResAlscInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqProcResComb* comb = &shared->procResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAlscHandle::processing();
    if (ret) {
        comb->alsc_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "alsc handle processing failed");
    }

    comb->alsc_proc_res = NULL;

    // TODO should check if the rk awb algo used
    RkAiqAlgoProcResAwb* awb_res =
        (RkAiqAlgoProcResAwb*)(shared->procResComb.awb_proc_res);
    RkAiqAlgoProcResAwbInt* awb_res_int =
        (RkAiqAlgoProcResAwbInt*)(shared->procResComb.awb_proc_res);
    if(awb_res) {
        if(awb_res->awb_gain_algo.grgain < DIVMIN ||
                awb_res->awb_gain_algo.gbgain < DIVMIN ) {
            ret = XCAM_RETURN_ERROR_FAILED;
        } else {
            alsc_proc_int->alsc_sw_info.awbGain[0] =
                awb_res->awb_gain_algo.rgain / awb_res->awb_gain_algo.grgain;

            alsc_proc_int->alsc_sw_info.awbGain[1] =
                awb_res->awb_gain_algo.bgain / awb_res->awb_gain_algo.gbgain;
            ret = XCAM_RETURN_NO_ERROR;
        }
        alsc_proc_int->alsc_sw_info.awbIIRDampCoef = awb_res_int->awb_smooth_factor;
    }
#if 0
    //sprintf(alsc_proc_int->alsc_sw_info.resName, "%d_%d", shared->width, shared->height);
    RkAiqAlgoPreResAeInt *ae_int = (RkAiqAlgoPreResAeInt*)shared->preResComb.ae_pre_res;
    ret = XCAM_RETURN_ERROR_FAILED;
    if( shared->preResComb.ae_pre_res) {
        int fNormalIndex =  ae_int->aecPreResult.NormalIndex;
        if(shared->working_mode == RK_AIQ_WORKING_MODE_NORMAL || shared->working_mode == RK_AIQ_WORKING_MODE_SENSOR_HDR) {
            alsc_proc_int->alsc_sw_info.sensorGain = ae_int->aecPreResult.LinearExp.exp_real_params.analog_gain;
        } else {
            alsc_proc_int->alsc_sw_info.sensorGain = ae_int->aecPreResult.HdrExp[fNormalIndex].exp_real_params.analog_gain;
        }
        ret = XCAM_RETURN_NO_ERROR;
    }
    RKAIQCORE_CHECK_RET(ret, "fail to get sensor gain ");
#else
    // to do
    alsc_proc_int->alsc_sw_info.sensorGain = 1.0;
    //strcpy(alsc_proc_int->alsc_sw_info.resName, "2712x1536");
#endif
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "alsc algo processing failed");

    comb->alsc_proc_res = (RkAiqAlgoProcResAlsc*)alsc_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAlscHandleInt::postProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAlscInt* alsc_post_int = (RkAiqAlgoPostAlscInt*)mPostInParam;
    RkAiqAlgoPostResAlscInt* alsc_post_res_int = (RkAiqAlgoPostResAlscInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqPostResComb* comb = &shared->postResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAlscHandle::postProcess();
    if (ret) {
        comb->alsc_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "alsc handle postProcess failed");
        return ret;
    }

    comb->alsc_post_res = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "alsc algo post_process failed");
    // set result to mAiqCore
    comb->alsc_post_res = (RkAiqAlgoPostResAlsc*)alsc_post_res_int ;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

void
RkAiqAorbHandleInt::init()
{
    ENTER_ANALYZER_FUNCTION();

    RkAiqAorbHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAorbInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAorbInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAorbInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAorbInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAorbInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAorbInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAorbInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn
RkAiqAorbHandleInt::prepare()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqAorbHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "aorb handle prepare failed");

    RkAiqAlgoConfigAorbInt* aorb_config_int = (RkAiqAlgoConfigAorbInt*)mConfig;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;

    memcpy(&aorb_config_int->orb_calib_cfg, &shared->calib->orb, sizeof(CalibDb_ORB_t));

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "aorb algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAorbHandleInt::preProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAorbInt* aorb_pre_int = (RkAiqAlgoPreAorbInt*)mPreInParam;
    RkAiqAlgoPreResAorbInt* aorb_pre_res_int = (RkAiqAlgoPreResAorbInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqIspStats* ispStats = &shared->ispStats;
    RkAiqPreResComb* comb = &shared->preResComb;

    ret = RkAiqAorbHandle::preProcess();
    if (ret) {
        comb->aorb_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "aorb handle preProcess failed");
    }

    comb->aorb_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "aorb algo pre_process failed");

    // set result to mAiqCore
    comb->aorb_pre_res = (RkAiqAlgoPreResAorb*)aorb_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAorbHandleInt::processing()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAorbInt* aorb_proc_int = (RkAiqAlgoProcAorbInt*)mProcInParam;
    RkAiqAlgoProcResAorbInt* aorb_proc_res_int = (RkAiqAlgoProcResAorbInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqProcResComb* comb = &shared->procResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAorbHandle::processing();
    if (ret) {
        comb->aorb_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "aorb handle processing failed");
    }

    comb->aorb_proc_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "aorb algo processing failed");

    comb->aorb_proc_res = (RkAiqAlgoProcResAorb*)aorb_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAorbHandleInt::postProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAorbInt* aorb_post_int = (RkAiqAlgoPostAorbInt*)mPostInParam;
    RkAiqAlgoPostResAorbInt* aorb_post_res_int = (RkAiqAlgoPostResAorbInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqPostResComb* comb = &shared->postResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAorbHandle::postProcess();
    if (ret) {
        comb->aorb_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "aorb handle postProcess failed");
        return ret;
    }

    comb->aorb_post_res = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "aorb algo post_process failed");
    // set result to mAiqCore
    comb->aorb_post_res = (RkAiqAlgoPostResAorb*)aorb_post_res_int ;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

void
RkAiqAr2yHandleInt::init()
{
    ENTER_ANALYZER_FUNCTION();

    RkAiqAr2yHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAr2yInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAr2yInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAr2yInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAr2yInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAr2yInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAr2yInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAr2yInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn
RkAiqAr2yHandleInt::prepare()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqAr2yHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "ar2y handle prepare failed");

    RkAiqAlgoConfigAr2yInt* ar2y_config_int = (RkAiqAlgoConfigAr2yInt*)mConfig;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "ar2y algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAr2yHandleInt::preProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAr2yInt* ar2y_pre_int = (RkAiqAlgoPreAr2yInt*)mPreInParam;
    RkAiqAlgoPreResAr2yInt* ar2y_pre_res_int = (RkAiqAlgoPreResAr2yInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqIspStats* ispStats = &shared->ispStats;
    RkAiqPreResComb* comb = &shared->preResComb;

    ret = RkAiqAr2yHandle::preProcess();
    if (ret) {
        comb->ar2y_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "ar2y handle preProcess failed");
    }

    comb->ar2y_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "ar2y algo pre_process failed");

    // set result to mAiqCore
    comb->ar2y_pre_res = (RkAiqAlgoPreResAr2y*)ar2y_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAr2yHandleInt::processing()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAr2yInt* ar2y_proc_int = (RkAiqAlgoProcAr2yInt*)mProcInParam;
    RkAiqAlgoProcResAr2yInt* ar2y_proc_res_int = (RkAiqAlgoProcResAr2yInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqProcResComb* comb = &shared->procResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAr2yHandle::processing();
    if (ret) {
        comb->ar2y_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "ar2y handle processing failed");
    }

    comb->ar2y_proc_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "ar2y algo processing failed");

    comb->ar2y_proc_res = (RkAiqAlgoProcResAr2y*)ar2y_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAr2yHandleInt::postProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAr2yInt* ar2y_post_int = (RkAiqAlgoPostAr2yInt*)mPostInParam;
    RkAiqAlgoPostResAr2yInt* ar2y_post_res_int = (RkAiqAlgoPostResAr2yInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqPostResComb* comb = &shared->postResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAr2yHandle::postProcess();
    if (ret) {
        comb->ar2y_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "ar2y handle postProcess failed");
        return ret;
    }

    comb->ar2y_post_res = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "ar2y algo post_process failed");
    // set result to mAiqCore
    comb->ar2y_post_res = (RkAiqAlgoPostResAr2y*)ar2y_post_res_int ;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAwdrHandleInt::prepare()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqAwdrHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "awdr handle prepare failed");

    RkAiqAlgoConfigAwdrInt* awdr_config_int = (RkAiqAlgoConfigAwdrInt*)mConfig;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "awdr algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

void
RkAiqAwdrHandleInt::init()
{
    ENTER_ANALYZER_FUNCTION();

    RkAiqAwdrHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAwdrInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAwdrInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAwdrInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAwdrInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAwdrInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAwdrInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAwdrInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn
RkAiqAwdrHandleInt::preProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAwdrInt* awdr_pre_int = (RkAiqAlgoPreAwdrInt*)mPreInParam;
    RkAiqAlgoPreResAwdrInt* awdr_pre_res_int = (RkAiqAlgoPreResAwdrInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqIspStats* ispStats = &shared->ispStats;
    RkAiqPreResComb* comb = &shared->preResComb;

    ret = RkAiqAwdrHandle::preProcess();
    if (ret) {
        comb->awdr_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "awdr handle preProcess failed");
    }

    comb->awdr_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "awdr algo pre_process failed");

    // set result to mAiqCore
    comb->awdr_pre_res = (RkAiqAlgoPreResAwdr*)awdr_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAwdrHandleInt::processing()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAwdrInt* awdr_proc_int = (RkAiqAlgoProcAwdrInt*)mProcInParam;
    RkAiqAlgoProcResAwdrInt* awdr_proc_res_int = (RkAiqAlgoProcResAwdrInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqProcResComb* comb = &shared->procResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAwdrHandle::processing();
    if (ret) {
        comb->awdr_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "awdr handle processing failed");
    }

    comb->awdr_proc_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "awdr algo processing failed");

    comb->awdr_proc_res = (RkAiqAlgoProcResAwdr*)awdr_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAwdrHandleInt::postProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAwdrInt* awdr_post_int = (RkAiqAlgoPostAwdrInt*)mPostInParam;
    RkAiqAlgoPostResAwdrInt* awdr_post_res_int = (RkAiqAlgoPostResAwdrInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosShared_t* shared = &mAiqCore->mAlogsSharedParams;
    RkAiqPostResComb* comb = &shared->postResComb;
    RkAiqIspStats* ispStats = &shared->ispStats;

    ret = RkAiqAwdrHandle::postProcess();
    if (ret) {
        comb->awdr_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "awdr handle postProcess failed");
        return ret;
    }

    comb->awdr_post_res = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "awdr algo post_process failed");
    // set result to mAiqCore
    comb->awdr_post_res = (RkAiqAlgoPostResAwdr*)awdr_post_res_int ;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

}; //namespace RkCam