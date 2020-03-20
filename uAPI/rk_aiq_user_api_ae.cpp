/******************************************************************************
 *
 * Copyright 2019, Fuzhou Rockchip Electronics Co.Ltd . All rights reserved.
 * No part of this work may be reproduced, modified, distributed, transmitted,
 * transcribed, or translated into any language or computer format, in any form
 * or by any means without written permission of:
 * Fuzhou Rockchip Electronics Co.Ltd .
 *
 *
 *****************************************************************************/

#include "base/xcam_common.h"
#include "rk_aiq_user_api_ae.h"
#include "RkAiqHandleInt.h"


XCamReturn rk_aiq_user_api_ae_setExpSwAttr
(
    const rk_aiq_sys_ctx_t* sys_ctx,
    const Uapi_ExpSwAttr_t*  pExpSwAttr
) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAeHandleInt* algo_handle =
        algoHandle<RkAiqAeHandleInt>(sys_ctx, RK_AIQ_ALGO_TYPE_AE);

    if (algo_handle) {
        return algo_handle->setExpSwAttr(pExpSwAttr);
    }

    return (ret);

}
XCamReturn rk_aiq_user_api_ae_getExpSwAttr
(
    const rk_aiq_sys_ctx_t* sys_ctx,
    Uapi_ExpSwAttr_t*        pExpSwAttr
) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAeHandleInt* algo_handle =
        algoHandle<RkAiqAeHandleInt>(sys_ctx, RK_AIQ_ALGO_TYPE_AE);

    if (algo_handle) {
        return algo_handle->getExpSwAttr(pExpSwAttr);
    }

    return (ret);
}
XCamReturn rk_aiq_user_api_ae_setLinAeRouteAttr
(
    const rk_aiq_sys_ctx_t* sys_ctx,
    const Uapi_LinAeRouteAttr_t* pLinAeRouteAttr
) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAeHandleInt* algo_handle =
        algoHandle<RkAiqAeHandleInt>(sys_ctx, RK_AIQ_ALGO_TYPE_AE);

    if (algo_handle) {
        return algo_handle->setLinAeRouteAttr(pLinAeRouteAttr);
    }

    return(ret);
}
XCamReturn rk_aiq_user_api_ae_getLinAeRouteAttr
(
    const rk_aiq_sys_ctx_t* sys_ctx,
    Uapi_LinAeRouteAttr_t* pLinAeRouteAttr
) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAeHandleInt* algo_handle =
        algoHandle<RkAiqAeHandleInt>(sys_ctx, RK_AIQ_ALGO_TYPE_AE);

    if (algo_handle) {
        return algo_handle->getLinAeRouteAttr(pLinAeRouteAttr);
    }

    return(ret);

}
XCamReturn rk_aiq_user_api_ae_setHdrAeRouteAttr
(
    const rk_aiq_sys_ctx_t* sys_ctx,
    const Uapi_HdrAeRouteAttr_t* pHdrAeRouteAttr
) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAeHandleInt* algo_handle =
        algoHandle<RkAiqAeHandleInt>(sys_ctx, RK_AIQ_ALGO_TYPE_AE);

    if (algo_handle) {
        return algo_handle->setHdrAeRouteAttr(pHdrAeRouteAttr);
    }

    return(ret);

}
XCamReturn rk_aiq_user_api_ae_getHdrAeRouteAttr
(
    const rk_aiq_sys_ctx_t* sys_ctx,
    Uapi_HdrAeRouteAttr_t* pHdrAeRouteAttr
) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAeHandleInt* algo_handle =
        algoHandle<RkAiqAeHandleInt>(sys_ctx, RK_AIQ_ALGO_TYPE_AE);

    if (algo_handle) {
        return algo_handle->getHdrAeRouteAttr(pHdrAeRouteAttr);
    }

    return(ret);

}
XCamReturn rk_aiq_user_api_ae_queryExpResInfo
(
    const rk_aiq_sys_ctx_t* sys_ctx,
    Uapi_ExpQueryInfo_t* pExpResInfo
) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAeHandleInt* algo_handle =
        algoHandle<RkAiqAeHandleInt>(sys_ctx, RK_AIQ_ALGO_TYPE_AE);

    if (algo_handle) {
        return algo_handle->queryExpResInfo(pExpResInfo);
    }

    return(ret);

}

XCamReturn rk_aiq_user_api_ae_setLinExpAttr
(
    const rk_aiq_sys_ctx_t* sys_ctx,
    const Uapi_LinExpAttr_t* pLinExpAttr
) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAeHandleInt* algo_handle =
        algoHandle<RkAiqAeHandleInt>(sys_ctx, RK_AIQ_ALGO_TYPE_AE);

    if (algo_handle) {
        return algo_handle->setLinExpAttr(pLinExpAttr);
    }

    return(ret);

}
XCamReturn rk_aiq_user_api_ae_getLinExpAttr
(
    const rk_aiq_sys_ctx_t* sys_ctx,
    Uapi_LinExpAttr_t* pLinExpAttr
) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAeHandleInt* algo_handle =
        algoHandle<RkAiqAeHandleInt>(sys_ctx, RK_AIQ_ALGO_TYPE_AE);

    if (algo_handle) {
        return algo_handle->getLinExpAttr(pLinExpAttr);
    }

    return(ret);

}
XCamReturn rk_aiq_user_api_ae_setHdrExpAttr
(
    const rk_aiq_sys_ctx_t* sys_ctx,
    const Uapi_HdrExpAttr_t* pHdrExpAttr
) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAeHandleInt* algo_handle =
        algoHandle<RkAiqAeHandleInt>(sys_ctx, RK_AIQ_ALGO_TYPE_AE);

    if (algo_handle) {
        return algo_handle->setHdrExpAttr(pHdrExpAttr);
    }

    return(ret);

}
XCamReturn rk_aiq_user_api_ae_getHdrExpAttr
(
    const rk_aiq_sys_ctx_t* sys_ctx,
    Uapi_HdrExpAttr_t* pHdrExpAttr
) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAeHandleInt* algo_handle =
        algoHandle<RkAiqAeHandleInt>(sys_ctx, RK_AIQ_ALGO_TYPE_AE);

    if (algo_handle) {
        return algo_handle->getHdrExpAttr(pHdrExpAttr);
    }

    return(ret);

}
