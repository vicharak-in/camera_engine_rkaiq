/*
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

#ifndef _ISP20_HW_SIMULATOR_H_
#define _ISP20_HW_SIMULATOR_H_

#include "awb/rk_aiq_types_awb_algo_int.h"
#include "ae/rk_aiq_types_ae_algo.h"
#include "af/rk_aiq_af_hw_v200.h"
#include "anr/anr.h"
#include "asharp/asharp.h"
#include "adehaze/dehaze.h"
#include "adebayer/rk_aiq_types_algo_adebayer.h"
#include "aorb/rk_aiq_orb.h"
#include "ahdr/rk_aiq_types_ahdr_algo_int.h"
#include "ahdr/rk_aiq_types_ahdr_algo.h"
#include "agamma/agamma.h"
#include "adpcc/adpcc.h"
#include "ablc/ablc.h"
#include "alsc/rk_aiq_types_alsc_algo.h"
#include "accm/rk_aiq_types_accm_algo.h"
#include "rk_aiq_luma.h"
#include "a3dlut/rk_aiq_types_a3dlut_algo_int.h"
typedef struct rk_sim_isp_v200_luma_s {
    //luma
    bool valid_luma;
    isp_luma_stat_t image_luma_result;
} rk_sim_isp_v200_luma_t;

typedef struct rk_sim_isp_v200_stats_s {
    //awb
    bool valid_awb;
    rk_aiq_awb_stat_res_v200_t awb;
    rk_aiq_awb_stat_res_v201_t awb_v201;
    //ae
    bool valid_ae;
    RKAiqAecStats_t ae;
    //af
    bool valid_af;
    rawaf_isp_af_stat_t af;
    //anr html params
    int iso;
    //orb
    bool valid_orb;
    orb_stat_t orb;
    //ahdr
    unsigned short  rawWidth;               // rawÍ¼¿í
    unsigned short  rawHeight;
    bool valid_ahdr;
    rkisp_ahdr_stats_t ahdr;
} rk_sim_isp_v200_stats_t;

typedef struct rk_sim_isp_v200_params_s {
    float awb_smooth_factor;
    rk_aiq_wb_gain_t awb_gain_algo;
    rk_aiq_awb_stat_cfg_v200_t awb_hw0_para;
    rk_aiq_awb_stat_cfg_v201_t awb_hw1_para;
    //ae
    RkAiqAecHwConfig_t ae_hw_config;
    //anr
    rkaiq_anr_procRes_t rkaiq_anr_proc_res;
    rkaiq_asharp_procRes_t rkaiq_asharp_proc_res;
    //adhaz
    RKAiqAdhazConfig_t adhaz_config;
    //agamma
    RKAiqAgammaHwConfig_t agamma_config;
    //ahdr
    RkAiqAhdrProcResult_t ahdr_proc_res;
    //adpcc
    rk_aiq_isp_dpcc_t   dpcc;
    //adebayer
    AdebayerConfig_t adebayer_config;
    //ablc
    rk_aiq_isp_blc_t blc;

    rk_aiq_lsc_cfg_t lscHwConf;
    rk_aiq_ccm_cfg_t ccmHwConf;

    rk_aiq_lut3d_cfg_t lut3d_hw_conf;
} rk_sim_isp_v200_params_t;

#endif
