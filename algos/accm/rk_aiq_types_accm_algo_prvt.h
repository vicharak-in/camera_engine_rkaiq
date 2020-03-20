/*
 *rk_aiq_types_accm_algo_prvt.h
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

#ifndef _RK_AIQ_TYPES_ACCM_ALGO_PRVT_H_
#define _RK_AIQ_TYPES_ACCM_ALGO_PRVT_H_
#include "RkAiqCalibDbTypes.h"
#include "accm/rk_aiq_types_accm_algo_int.h"
#include "xcam_log.h"
#include "xcam_common.h"


RKAIQ_BEGIN_DECLARE
#define CCM_CURVE_DOT_NUM 17


typedef struct accm_rest_s {
    float fSaturation;
    int dominateIlluProfileIdx;
    const CalibDb_CcmMatrixProfile_t *pCcmProfile1;
    const CalibDb_CcmMatrixProfile_t *pCcmProfile2;
    Cam3x3FloatMatrix_t undampedCcmMatrix;
    Cam3x3FloatMatrix_t dampedCcmMatrix;
    Cam1x3FloatMatrix_t undampedCcOffset;
    Cam1x3FloatMatrix_t dampedCcOffset;
} accm_rest_t;

typedef struct accm_context_s {
    const CalibDb_Ccm_t *calibCcm;//profile para
    const CalibDb_CcmMatrixProfile_t *pCcmMatrixAll[CCM_ILLUMINATION_MAX][CCM_PROFILES_NUM_MAX];// reorder para //to do, change to pointer
    accm_sw_info_t accmSwInfo;
    accm_rest_t accmRest;
    rk_aiq_ccm_cfg_t ccmHwConf; //hw para
    unsigned int count;
} accm_context_t ;

typedef accm_context_t* accm_handle_t ;


RKAIQ_END_DECLARE

#endif
