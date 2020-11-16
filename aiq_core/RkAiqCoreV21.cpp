/*
 * RkAiqCoreV21.cpp
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
#include "RkAiqHandleIntV21.h"
#include "RkAiqCoreV21.h"
#include "v4l2_buffer_proxy.h"
#include "acp/rk_aiq_algo_acp_itf.h"
#include "ae/rk_aiq_algo_ae_itf.h"
#include "awb/rk_aiq_algo_awb_itf.h"
#include "af/rk_aiq_algo_af_itf.h"
#include "anr/rk_aiq_algo_anr_itf.h"
#include "asd/rk_aiq_algo_asd_itf.h"
#include "ahdr/rk_aiq_algo_ahdr_itf.h"
#include "asharp/rk_aiq_algo_asharp_itf.h"
#include "adehaze/rk_aiq_algo_adhaz_itf.h"
#include "ablc/rk_aiq_algo_ablc_itf.h"
#include "adpcc/rk_aiq_algo_adpcc_itf.h"
#include "alsc/rk_aiq_algo_alsc_itf.h"
#include "agic/rk_aiq_algo_agic_itf.h"
#include "adebayer/rk_aiq_algo_adebayer_itf.h"
#include "accm/rk_aiq_algo_accm_itf.h"
#include "agamma/rk_aiq_algo_agamma_itf.h"
#include "awdr/rk_aiq_algo_awdr_itf.h"
#include "a3dlut/rk_aiq_algo_a3dlut_itf.h"
#include "aldch/rk_aiq_algo_aldch_itf.h"
#include "ar2y/rk_aiq_algo_ar2y_itf.h"
#include "aie/rk_aiq_algo_aie_itf.h"
#include "aorb/rk_aiq_algo_aorb_itf.h"
#include "afec/rk_aiq_algo_afec_itf.h"
#include "acgc/rk_aiq_algo_acgc_itf.h"
#ifdef RK_SIMULATOR_HW
#include "simulator/isp20_hw_simulator.h"
#else
#include "isp20/Isp20StatsBuffer.h"
#include "isp20/rkisp2-config.h"
#include "isp21/rkisp21-config.h"
#endif
#include <fcntl.h>
#include <unistd.h>

namespace RkCam {
/*
 * isp/ispp pipeline algos ordered array, and the analyzer
 * will run these algos one by one.
 */
static struct RkAiqAlgoDesCommExt g_default_3a_des_v21[] = {
    { (RkAiqAlgoDesComm*)&g_RkIspAlgoDescAe, 0, 0, },
    { (RkAiqAlgoDesComm*)&g_RkIspAlgoDescAdebayer, 0, 0 },
    { (RkAiqAlgoDesComm*)&g_RkIspAlgoDescAwb, 0, 0 },
    { (RkAiqAlgoDesComm*)&g_RkIspAlgoDescAgamma, 0, 0 },
    { (RkAiqAlgoDesComm*)&g_RkIspAlgoDescAcp, 0, 0 },
    { (RkAiqAlgoDesComm*)&g_RkIspAlgoDescAie, 0, 0 },
    { (RkAiqAlgoDesComm*)&g_RkIspAlgoDescAdpcc, 0, 0 },
    { (RkAiqAlgoDesComm*)&g_RkIspAlgoDescAldch, 0, 0 },
    { (RkAiqAlgoDesComm*)&g_RkIspAlgoDescA3dlut, 0, 0 },
    { (RkAiqAlgoDesComm*)&g_RkIspAlgoDescAcgc, 0, 0 },
    { (RkAiqAlgoDesComm*)&g_RkIspAlgoDescAr2y, 0, 0 },
    { (RkAiqAlgoDesComm*)&g_RkIspAlgoDescAlsc, 0, 0 },
    { (RkAiqAlgoDesComm*)&g_RkIspAlgoDescAccm, 0, 0 },
    { (RkAiqAlgoDesComm*)&g_RkIspAlgoDescAf, 0, 0 },
    { (RkAiqAlgoDesComm*)&g_RkIspAlgoDescAblc, 0, 0 },
#if 0
    { (RkAiqAlgoDesComm*)&g_RkIspAlgoDescAhdr, 0, 0 },
    /* { (RkAiqAlgoDesComm*)&g_RkIspAlgoDescAnr,0, 0 }, */
    { (RkAiqAlgoDesComm*)&g_RkIspAlgoDescAgic, 0, 0 },
    { (RkAiqAlgoDesComm*)&g_RkIspAlgoDescAwdr, 0, 0 },
    { (RkAiqAlgoDesComm*)&g_RkIspAlgoDescAdhaz, 0, 0 },
    { (RkAiqAlgoDesComm*)&g_RkIspAlgoDescAsharp, 0, 0 },
    { (RkAiqAlgoDesComm*)&g_RkIspAlgoDescAsd, 0, 0 },
    // TODO
    /* { (RkAiqAlgoDesComm*)&g_RkIspAlgoDescAdrc, 0, 0 }, */
    /* { (RkAiqAlgoDesComm*)&g_RkIspAlgoDescArawnr, 0, 0 }, */
    /* { (RkAiqAlgoDesComm*)&g_RkIspAlgoDescAmfnr, 0, 0 }, */
    /* { (RkAiqAlgoDesComm*)&g_RkIspAlgoDescAynr, 0, 0 }, */
    /* { (RkAiqAlgoDesComm*)&g_RkIspAlgoDescAcnr, 0, 0 }, */
#endif
    { NULL, 0, 0 },
};

RkAiqCoreV21::RkAiqCoreV21()
    : RkAiqCore()
{
    ENTER_ANALYZER_FUNCTION();

    mHasPp = false;
    mIspHwVer = 1;
    mAlgosDesArray = g_default_3a_des_v21;

    EXIT_ANALYZER_FUNCTION();
}

RkAiqCoreV21::~RkAiqCoreV21()
{
    ENTER_ANALYZER_FUNCTION();

    EXIT_ANALYZER_FUNCTION();
}

SmartPtr<RkAiqHandle>
RkAiqCoreV21::newAlgoHandle(RkAiqAlgoDesComm* algo, bool generic, int version)
{
    if (version == 0)
        return RkAiqCore::newAlgoHandle(algo, generic, 0);

#define NEW_ALGO_HANDLE_WITH_V(lc, BC, v) \
    do {\
        if (algo->type == RK_AIQ_ALGO_TYPE_##BC) { \
            if (generic) { \
                return new RkAiq##lc##V##v##Handle(algo, this); \
            } else { \
                return new RkAiq##lc##V##v##HandleInt(algo, this); \
            }\
        }\
    } while(0)\

    /* NEW_ALGO_HANDLE_V2(Arawnr, ARAWNR); */
    /* NEW_ALGO_HANDLE_V2(Amfnr, AMFNR); */
    /* NEW_ALGO_HANDLE_V2(Aynr, AYNR); */
    /* NEW_ALGO_HANDLE_V2(Acnr, ACNR); */

    //TODO: need to define RkAiqAdrcV1Handle ?
    typedef RkAiqAdrcHandle RkAiqAdrcV1Handle;

    NEW_ALGO_HANDLE_WITH_V(Adrc, ADRC, 1);

    return NULL;
}

void
RkAiqCoreV21::copyIspStats(RkAiqIspStats* from, rk_aiq_isp_stats_t* to)
{
    to->aec_stats = from->aec_stats;
    to->awb_hw_ver = 1;
    to->awb_stats_v21 = from->awb_stats_v201;
    to->af_stats = from->af_stats;
    to->frame_id = from->frame_id;
}

XCamReturn
RkAiqCoreV21::convertIspstatsToAlgo(const SmartPtr<VideoBuffer> &buffer)
{
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
#ifndef RK_SIMULATOR_HW
    const SmartPtr<Isp20StatsBuffer> buf =
        buffer.dynamic_cast_ptr<Isp20StatsBuffer>();
    struct rkisp_isp21_stat_buffer *stats;

    SmartPtr<RkAiqExpParamsProxy> expParams = buf->get_exp_params();
	if (!buf->get_isp_params().ptr()) {
		LOGW("no effect isp params..");
		return ret;
	}
    rk_aiq_isp_params_v21_t* ispParams =
        static_cast<rk_aiq_isp_params_v21_t*>(buf->get_isp_params()->data().ptr());
    SmartPtr<RkAiqAfInfoProxy> afParams = buf->get_af_params();
    SmartPtr<RkAiqIrisParamsProxy> irisParams = buf->get_iris_params();

    stats = (struct rkisp_isp21_stat_buffer*)(buf->get_v4l2_userptr());
    if(stats == NULL) {
        LOGE("fail to get stats ,ignore\n");
        return XCAM_RETURN_BYPASS;
    }
    LOGI_ANALYZER("stats: frame_id: %d,  meas_type; 0x%x",
                  stats->frame_id, stats->meas_type);

    mAlogsSharedParams.frameId = stats->frame_id;

    if(ispParams == NULL) {
        LOGE("fail to get ispParams ,ignore\n");
        return XCAM_RETURN_BYPASS;
    }

    // TODO: do awb/ae/af/hdr stats convert

    //awb2.1

    mAlogsSharedParams.ispStats.awb_cfg_effect_v201 = ispParams->awb_cfg;
    mAlogsSharedParams.ispStats.awb_cfg_effect_valid = true;

    for(int i = 0; i < mAlogsSharedParams.ispStats.awb_cfg_effect_v201.lightNum; i++) {
        mAlogsSharedParams.ispStats.awb_stats_v201.light[i].xYType[RK_AIQ_AWB_XY_TYPE_NORMAL_V201].RgainValue =
            stats->params.rawawb.ro_rawawb_sum_rgain_nor[i];
        mAlogsSharedParams.ispStats.awb_stats_v201.light[i].xYType[RK_AIQ_AWB_XY_TYPE_NORMAL_V201].BgainValue =
            stats->params.rawawb.ro_rawawb_sum_bgain_nor[i];
        mAlogsSharedParams.ispStats.awb_stats_v201.light[i].xYType[RK_AIQ_AWB_XY_TYPE_NORMAL_V201].WpNo =
            stats->params.rawawb.ro_rawawb_wp_num_nor[i];
        mAlogsSharedParams.ispStats.awb_stats_v201.light[i].xYType[RK_AIQ_AWB_XY_TYPE_BIG_V201].RgainValue =
            stats->params.rawawb.ro_rawawb_sum_rgain_big[i];
        mAlogsSharedParams.ispStats.awb_stats_v201.light[i].xYType[RK_AIQ_AWB_XY_TYPE_BIG_V201].BgainValue =
            stats->params.rawawb.ro_rawawb_sum_bgain_big[i];
        mAlogsSharedParams.ispStats.awb_stats_v201.light[i].xYType[RK_AIQ_AWB_XY_TYPE_BIG_V201].WpNo =
            stats->params.rawawb.ro_rawawb_wp_num_big[i];

    }

    for(int i = 0; i < RK_AIQ_AWB_GRID_NUM_TOTAL; i++) {
        mAlogsSharedParams.ispStats.awb_stats_v201.blockResult[i].Rvalue = stats->params.rawawb.ramdata[i].r;
        mAlogsSharedParams.ispStats.awb_stats_v201.blockResult[i].Gvalue = stats->params.rawawb.ramdata[i].g;
        mAlogsSharedParams.ispStats.awb_stats_v201.blockResult[i].Bvalue = stats->params.rawawb.ramdata[i].b;
        mAlogsSharedParams.ispStats.awb_stats_v201.blockResult[i].WpNo = stats->params.rawawb.ramdata[i].wp;
    }

    for(int i = 0; i< RK_AIQ_AWB_WP_HIST_BIN_NUM; i++){
        mAlogsSharedParams.ispStats.awb_stats_v201.WpNoHist[i] = stats->params.rawawb.ro_yhist_bin[i];

    }
    //mAlogsSharedParams.ispStats.awb_stats_valid = ISP2X_STAT_RAWAWB(stats->meas_type)? true:false;
    mAlogsSharedParams.ispStats.awb_stats_valid = stats->meas_type >> 5 & 1;

    //ae stats v2.1

    mAlogsSharedParams.ispStats.aec_stats_valid = (stats->meas_type >> 11) & (0x01) ? true : false;

    /*rawae stats*/
    uint8_t AeSwapMode, AeSelMode;
    AeSwapMode = ispParams->aec_meas.rawae0.rawae_sel;
    AeSelMode = ispParams->aec_meas.rawae3.rawae_sel;

    switch(AeSwapMode) {
    case AEC_RAWSWAP_MODE_S_LITE:
        for(int i = 0; i < ISP2X_RAWAEBIG_MEAN_NUM; i++) {
            if(i < ISP2X_RAWAELITE_MEAN_NUM) {
                mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[0].rawae_lite.channelr_xy[i] = stats->params.rawae0.data[i].channelr_xy;
                mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[0].rawae_lite.channelg_xy[i] = stats->params.rawae0.data[i].channelg_xy;
                mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[0].rawae_lite.channelb_xy[i] = stats->params.rawae0.data[i].channelb_xy;
            }
            mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[1].rawae_big.channelr_xy[i] = stats->params.rawae1.data[i].channelr_xy;
            mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[1].rawae_big.channelg_xy[i] = stats->params.rawae1.data[i].channelg_xy;
            mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[1].rawae_big.channelb_xy[i] = stats->params.rawae1.data[i].channelb_xy;

            if(i < ISP2X_RAWAEBIG_SUBWIN_NUM) {
                mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[1].rawae_big.wndx_sumr[i] = stats->params.rawae1.sumr[i];
                mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[1].rawae_big.wndx_sumg[i] = stats->params.rawae1.sumg[i];
                mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[1].rawae_big.wndx_sumb[i] = stats->params.rawae1.sumb[i];
            }
        }
        memcpy(mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[0].rawhist_lite.bins, stats->params.rawhist0.hist_bin, ISP2X_HIST_BIN_N_MAX * sizeof(u32));
        memcpy(mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[1].rawhist_big.bins, stats->params.rawhist1.hist_bin, ISP2X_HIST_BIN_N_MAX * sizeof(u32));
        break;

    case AEC_RAWSWAP_MODE_M_LITE:
        for(int i = 0; i < ISP2X_RAWAEBIG_MEAN_NUM; i++) {
            if(i < ISP2X_RAWAELITE_MEAN_NUM) {
                mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[1].rawae_lite.channelr_xy[i] = stats->params.rawae0.data[i].channelr_xy;
                mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[1].rawae_lite.channelg_xy[i] = stats->params.rawae0.data[i].channelg_xy;
                mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[1].rawae_lite.channelb_xy[i] = stats->params.rawae0.data[i].channelb_xy;
            }
            mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[0].rawae_big.channelr_xy[i] = stats->params.rawae1.data[i].channelr_xy;
            mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[0].rawae_big.channelg_xy[i] = stats->params.rawae1.data[i].channelg_xy;
            mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[0].rawae_big.channelb_xy[i] = stats->params.rawae1.data[i].channelb_xy;

            if(i < ISP2X_RAWAEBIG_SUBWIN_NUM) {
                mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[0].rawae_big.wndx_sumr[i] = stats->params.rawae1.sumr[i];
                mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[0].rawae_big.wndx_sumg[i] = stats->params.rawae1.sumg[i];
                mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[0].rawae_big.wndx_sumb[i] = stats->params.rawae1.sumb[i];
            }
        }
        memcpy(mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[0].rawhist_big.bins, stats->params.rawhist1.hist_bin, ISP2X_HIST_BIN_N_MAX * sizeof(u32));
        memcpy(mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[1].rawhist_lite.bins, stats->params.rawhist0.hist_bin, ISP2X_HIST_BIN_N_MAX * sizeof(u32));
        break;

    default:
        LOGE("wrong AeSwapMode=%d\n", AeSwapMode);
        return XCAM_RETURN_ERROR_PARAM;
        break;
    }

    switch(AeSelMode) {
    case AEC_RAWSEL_MODE_CHN_0:
        for(int i = 0; i < ISP2X_RAWAEBIG_MEAN_NUM; i++) {

            mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[0].rawae_big.channelr_xy[i] = stats->params.rawae3.data[i].channelr_xy;
            mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[0].rawae_big.channelg_xy[i] = stats->params.rawae3.data[i].channelg_xy;
            mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[0].rawae_big.channelb_xy[i] = stats->params.rawae3.data[i].channelb_xy;

            if(i < ISP2X_RAWAEBIG_SUBWIN_NUM) {
                mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[0].rawae_big.wndx_sumr[i] = stats->params.rawae3.sumr[i];
                mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[0].rawae_big.wndx_sumg[i] = stats->params.rawae3.sumg[i];
                mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[0].rawae_big.wndx_sumb[i] = stats->params.rawae3.sumb[i];
            }
        }
        memcpy(mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[0].rawhist_big.bins, stats->params.rawhist3.hist_bin, ISP2X_HIST_BIN_N_MAX * sizeof(u32));
        break;

    case AEC_RAWSEL_MODE_CHN_1:
        for(int i = 0; i < ISP2X_RAWAEBIG_MEAN_NUM; i++) {

            mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[1].rawae_big.channelr_xy[i] = stats->params.rawae3.data[i].channelr_xy;
            mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[1].rawae_big.channelg_xy[i] = stats->params.rawae3.data[i].channelg_xy;
            mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[1].rawae_big.channelb_xy[i] = stats->params.rawae3.data[i].channelb_xy;

            if(i < ISP2X_RAWAEBIG_SUBWIN_NUM) {
                mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[1].rawae_big.wndx_sumr[i] = stats->params.rawae3.sumr[i];
                mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[1].rawae_big.wndx_sumg[i] = stats->params.rawae3.sumg[i];
                mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[1].rawae_big.wndx_sumb[i] = stats->params.rawae3.sumb[i];
            }
        }
        memcpy(mAlogsSharedParams.ispStats.aec_stats.ae_data.chn[1].rawhist_big.bins, stats->params.rawhist3.hist_bin, ISP2X_HIST_BIN_N_MAX * sizeof(u32));
        break;

    case AEC_RAWSEL_MODE_TMO:
        for(int i = 0; i < ISP2X_RAWAEBIG_MEAN_NUM; i++) {

            mAlogsSharedParams.ispStats.aec_stats.ae_data.extra.rawae_big.channelr_xy[i] = stats->params.rawae3.data[i].channelr_xy;
            mAlogsSharedParams.ispStats.aec_stats.ae_data.extra.rawae_big.channelg_xy[i] = stats->params.rawae3.data[i].channelg_xy;
            mAlogsSharedParams.ispStats.aec_stats.ae_data.extra.rawae_big.channelb_xy[i] = stats->params.rawae3.data[i].channelb_xy;

            if(i < ISP2X_RAWAEBIG_SUBWIN_NUM) {
                mAlogsSharedParams.ispStats.aec_stats.ae_data.extra.rawae_big.wndx_sumr[i] = stats->params.rawae3.sumr[i];
                mAlogsSharedParams.ispStats.aec_stats.ae_data.extra.rawae_big.wndx_sumg[i] = stats->params.rawae3.sumg[i];
                mAlogsSharedParams.ispStats.aec_stats.ae_data.extra.rawae_big.wndx_sumb[i] = stats->params.rawae3.sumb[i];
            }
        }
        memcpy(mAlogsSharedParams.ispStats.aec_stats.ae_data.extra.rawhist_big.bins, stats->params.rawhist3.hist_bin, ISP2X_HIST_BIN_N_MAX * sizeof(u32));
        break;

    default:
        LOGE("wrong AeSelMode=%d\n", AeSelMode);
        return XCAM_RETURN_ERROR_PARAM;
    }

    /*yuvae stats*/
    for(int i = 0; i < ISP2X_YUVAE_MEAN_NUM; i++) {
        mAlogsSharedParams.ispStats.aec_stats.ae_data.yuvae.mean[i] = stats->params.yuvae.mean[i];
        if(i < ISP2X_YUVAE_SUBWIN_NUM)
            mAlogsSharedParams.ispStats.aec_stats.ae_data.yuvae.ro_yuvae_sumy[i] = stats->params.yuvae.ro_yuvae_sumy[i];
    }

    /*
     *         unsigned long chn0_mean = 0, chn1_mean = 0;
     *         for(int i = 0; i < ISP2X_RAWAEBIG_MEAN_NUM; i++) {
     *             chn0_mean += stats->params.rawae1.data[i].channelg_xy;
     *             chn1_mean += stats->params.rawae3.data[i].channelg_xy;
     *         }
     *
     *
     *         printf("frame[%d]: chn[0-1]_g_mean_xy: %ld-%ld\n",
     *                 stats->frame_id, chn0_mean/ISP2X_RAWAEBIG_MEAN_NUM,
     *                 chn1_mean/ISP2X_RAWAEBIG_MEAN_NUM);
     */

    //expsoure params
    if (expParams.ptr()) {

        mAlogsSharedParams.ispStats.aec_stats.ae_exp = expParams->data()->aecExpInfo;
        /*
         * printf("%s: L: [0x%x-0x%x], M: [0x%x-0x%x], S: [0x%x-0x%x]\n",
         *        __func__,
         *        expParams->data()->aecExpInfo.HdrExp[2].exp_sensor_params.coarse_integration_time,
         *        expParams->data()->aecExpInfo.HdrExp[2].exp_sensor_params.analog_gain_code_global,
         *        expParams->data()->aecExpInfo.HdrExp[1].exp_sensor_params.coarse_integration_time,
         *        expParams->data()->aecExpInfo.HdrExp[1].exp_sensor_params.analog_gain_code_global,
         *        expParams->data()->aecExpInfo.HdrExp[0].exp_sensor_params.coarse_integration_time,
         *        expParams->data()->aecExpInfo.HdrExp[0].exp_sensor_params.analog_gain_code_global);
         */
    }

    //iris params
    if (irisParams.ptr()) {

        float sof_time = (float)irisParams->data()->sofTime / 1000000000.0f;
        float start_time = (float)irisParams->data()->PIris.StartTim.tv_sec + (float)irisParams->data()->PIris.StartTim.tv_usec / 1000000.0f;
        float end_time = (float)irisParams->data()->PIris.EndTim.tv_sec + (float)irisParams->data()->PIris.EndTim.tv_usec / 1000000.0f;
        float frm_intval = 1 / (mAlogsSharedParams.ispStats.aec_stats.ae_exp.pixel_clock_freq_mhz * 1000000.0f /
                                (float)mAlogsSharedParams.ispStats.aec_stats.ae_exp.line_length_pixels / (float)mAlogsSharedParams.ispStats.aec_stats.ae_exp.frame_length_lines);

        /*printf("%s: step=%d,last-step=%d,start-tim=%f,end-tim=%f,sof_tim=%f\n",
            __func__,
            mAlogsSharedParams.ispStats.aec_stats.ae_exp.Iris.PIris.step,
            irisParams->data()->PIris.laststep,start_time,end_time,sof_time);
        */

        if(sof_time < end_time + frm_intval)
            mAlogsSharedParams.ispStats.aec_stats.ae_exp.Iris.PIris.step = irisParams->data()->PIris.laststep;
        else
            mAlogsSharedParams.ispStats.aec_stats.ae_exp.Iris.PIris.step = irisParams->data()->PIris.step;
    }

    //af
    {
        mAlogsSharedParams.ispStats.af_stats_valid =
            (stats->meas_type >> 6) & (0x01) ? true : false;
        mAlogsSharedParams.ispStats.af_stats.roia_luminance =
            stats->params.rawaf.afm_lum[0];
        mAlogsSharedParams.ispStats.af_stats.roib_sharpness =
            stats->params.rawaf.afm_sum[1];
        mAlogsSharedParams.ispStats.af_stats.roib_luminance =
            stats->params.rawaf.afm_lum[1];
        memcpy(mAlogsSharedParams.ispStats.af_stats.global_sharpness,
               stats->params.rawaf.ramdata, ISP2X_RAWAF_SUMDATA_NUM * sizeof(u32));

        mAlogsSharedParams.ispStats.af_stats.roia_sharpness = 0LL;
        for (int i = 0; i < ISP2X_RAWAF_SUMDATA_NUM; i++)
            mAlogsSharedParams.ispStats.af_stats.roia_sharpness += stats->params.rawaf.ramdata[i];

        if(afParams.ptr()) {
            mAlogsSharedParams.ispStats.af_stats.focus_endtim = afParams->data()->focusEndTim;
            mAlogsSharedParams.ispStats.af_stats.focus_starttim = afParams->data()->focusStartTim;
            mAlogsSharedParams.ispStats.af_stats.zoom_endtim = afParams->data()->zoomEndTim;
            mAlogsSharedParams.ispStats.af_stats.zoom_starttim = afParams->data()->zoomStartTim;
            mAlogsSharedParams.ispStats.af_stats.sof_tim = afParams->data()->sofTime;
        }
    }
#endif
    return ret;
}

XCamReturn
RkAiqCoreV21::genIspArawnrResult(RkAiqFullParams* params)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

XCamReturn
RkAiqCoreV21::genIspAmfnrResult(RkAiqFullParams* params)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

XCamReturn
RkAiqCoreV21::genIspAynrResult(RkAiqFullParams* params)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

XCamReturn
RkAiqCoreV21::genIspAcnrResult(RkAiqFullParams* params)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

XCamReturn
RkAiqCoreV21::genIspAdrcResult(RkAiqFullParams* params)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

XCamReturn
RkAiqCoreV21::genIspAwbResult(RkAiqFullParams* params)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    RkAiqAlgoProcResAwb* awb_com =
        mAlogsSharedParams.procResComb.awb_proc_res;
    rk_aiq_isp_params_v21_t* isp_param =
        static_cast<rk_aiq_isp_params_v21_t*>(params->mIspParams->data().ptr());

    if (!awb_com) {
        LOGD_ANALYZER("no awb result");
        return XCAM_RETURN_NO_ERROR;
    }
    // TODO: gen awb common result
    RkAiqCore::genIspAwbResult(params);
    RkAiqAlgoProcResAwb* awb_rk = (RkAiqAlgoProcResAwb*)awb_com;
    isp_param->awb_cfg = awb_rk->awb_hw1_para;
    SmartPtr<RkAiqHandle>* handle = getCurAlgoTypeHandle(RK_AIQ_ALGO_TYPE_AWB);
    int algo_id = (*handle)->getAlgoId();

    // gen rk awb result
    if (algo_id == 0) {
        RkAiqAlgoProcResAwbInt* awb_rk_int = (RkAiqAlgoProcResAwbInt*)awb_com;
    }

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

XCamReturn
RkAiqCoreV21::genIspAblcResult(RkAiqFullParams* params)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcResAblc* ablc_com =
        mAlogsSharedParams.procResComb.ablc_proc_res;
    rk_aiq_isp_params_v21_t* isp_param =
        static_cast<rk_aiq_isp_params_v21_t*>(params->mIspParams->data().ptr());

    if (!ablc_com) {
        LOGD_ANALYZER("no ablc result");
        return XCAM_RETURN_NO_ERROR;
    }

    // TODO: gen ablc common result

    SmartPtr<RkAiqHandle>* handle = getCurAlgoTypeHandle(RK_AIQ_ALGO_TYPE_ABLC);
    int algo_id = (*handle)->getAlgoId();

    // gen rk ablc result
    if (algo_id == 0) {
        RkAiqAlgoProcResAblcInt* ablc_rk = (RkAiqAlgoProcResAblcInt*)ablc_com;

        memcpy(&isp_param->blc.v0, &ablc_rk->ablc_proc_res,
               sizeof(rk_aiq_isp_blc_t));
    }

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

XCamReturn
RkAiqCoreV21::genIspAgicResult(RkAiqFullParams* params)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

XCamReturn
RkAiqCoreV21::genIspAccmResult(RkAiqFullParams* params)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcResAccm* accm_com =
        mAlogsSharedParams.procResComb.accm_proc_res;
    rk_aiq_isp_params_v21_t*  isp_param =
        static_cast<rk_aiq_isp_params_v21_t*>(params->mIspParams->data().ptr());

    if (!accm_com) {
        LOGD_ANALYZER("no accm result");
        return XCAM_RETURN_NO_ERROR;
    }

    // TODO: gen accm common result
    RkAiqAlgoProcResAccm* accm_rk = (RkAiqAlgoProcResAccm*)accm_com;
    isp_param->ccm = accm_rk->accm_hw_conf;

    SmartPtr<RkAiqHandle>* handle = getCurAlgoTypeHandle(RK_AIQ_ALGO_TYPE_ACCM);
    int algo_id = (*handle)->getAlgoId();

    // gen rk accm result
    if (algo_id == 0) {
        RkAiqAlgoProcResAccmInt* accm_rk_int = (RkAiqAlgoProcResAccmInt*)accm_com;
    }

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

XCamReturn
RkAiqCoreV21::genIspAdhazResult(RkAiqFullParams* params)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

XCamReturn
RkAiqCoreV21::genIspAsharpResult(RkAiqFullParams* params)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    RkAiqAlgoProcResAsharp* asharp_com =
        mAlogsSharedParams.procResComb.asharp_proc_res;
    rk_aiq_isp_params_v21_t* isp_param =
        static_cast<rk_aiq_isp_params_v21_t*>(params->mIspParams->data().ptr());

    if (!asharp_com) {
        LOGD_ANALYZER("no asharp result");
        return XCAM_RETURN_NO_ERROR;
    }

    // TODO: gen asharp common result

    SmartPtr<RkAiqHandle>* handle = getCurAlgoTypeHandle(RK_AIQ_ALGO_TYPE_ASHARP);
    int algo_id = (*handle)->getAlgoId();

    // gen rk asharp result
    if (algo_id == 0) {
    }

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

} //namespace RkCam
