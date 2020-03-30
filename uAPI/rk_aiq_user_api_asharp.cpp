#include "rk_aiq_user_api_asharp.h"
#include "RkAiqHandleInt.h"

XCamReturn
rk_aiq_user_api_asharp_SetAttrib(rk_aiq_sys_ctx_t* sys_ctx, rk_aiq_sharp_attrib_t *attr)
{
    RkAiqAsharpHandleInt* algo_handle =
        algoHandle<RkAiqAsharpHandleInt>(sys_ctx, RK_AIQ_ALGO_TYPE_ASHARP);

    if (algo_handle) {
        return algo_handle->setAttrib(attr);
    }

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
rk_aiq_user_api_asharp_GetAttrib(rk_aiq_sys_ctx_t* sys_ctx, rk_aiq_sharp_attrib_t *attr)
{
    RkAiqAsharpHandleInt* algo_handle =
        algoHandle<RkAiqAsharpHandleInt>(sys_ctx, RK_AIQ_ALGO_TYPE_ASHARP);

    if (algo_handle) {
        return algo_handle->getAttrib(attr);
    }

    return XCAM_RETURN_NO_ERROR;
}
