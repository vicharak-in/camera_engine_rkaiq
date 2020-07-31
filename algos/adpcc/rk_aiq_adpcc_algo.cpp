#include "rk_aiq_adpcc_algo.h"
#include "rk_aiq_algo_adpcc_itf.h"

#define DPCC_RK_MODE

AdpccResult_t html_params_init(Adpcc_html_param_t *pParams)
{
    AdpccResult_t ret = ADPCC_RET_SUCCESS;
    LOGI_ADPCC("%s(%d): enter!\n", __FUNCTION__, __LINE__);

    if(pParams == NULL) {
        ret = ADPCC_RET_NULL_POINTER;
        LOGE_ADPCC("%s(%d): invalid input params\n", __FUNCTION__, __LINE__);
        return ret;
    }

    Adpcc_basic_params_t *pBasic = &pParams->stBasic;
    Adpcc_bpt_params_t *pBpt = &pParams->stBpt;
    Adpcc_pdaf_params_t *pPdaf = &pParams->stPdaf;
    int iso_base = 50;

    for(int i = 0; i < DPCC_MAX_ISO_LEVEL; i++) {
        pBasic->arBasic[i].iso = iso_base * ( 1 << i);

#ifdef DPCC_RK_MODE
        //mode 0x0000
        pBasic->arBasic[i].stage1_enable = 1;
        pBasic->arBasic[i].grayscale_mode = 0;
        pBasic->arBasic[i].enable = 1;

        //output_mode 0x0004
        pBasic->arBasic[i].sw_rk_out_sel = 1;
        pBasic->arBasic[i].sw_dpcc_output_sel = 1;
        pBasic->arBasic[i].stage1_rb_3x3 = 0;
        pBasic->arBasic[i].stage1_g_3x3 = 0;
        pBasic->arBasic[i].stage1_incl_rb_center = 1;
        pBasic->arBasic[i].stage1_incl_green_center = 1;

        //set_use 0x0008
        pBasic->arBasic[i].stage1_use_fix_set = 0;
        pBasic->arBasic[i].stage1_use_set_3 = 0;
        pBasic->arBasic[i].stage1_use_set_2 = 1;
        pBasic->arBasic[i].stage1_use_set_1 = 0;

        //methods_set_1 0x000c
        pBasic->arBasic[i].sw_rk_red_blue1_en = 0;
        pBasic->arBasic[i].rg_red_blue1_enable = 1;
        pBasic->arBasic[i].rnd_red_blue1_enable = 1;
        pBasic->arBasic[i].ro_red_blue1_enable = 1;
        pBasic->arBasic[i].lc_red_blue1_enable = 0;
        pBasic->arBasic[i].pg_red_blue1_enable = 1;
        pBasic->arBasic[i].sw_rk_green1_en = 0;
        pBasic->arBasic[i].rg_green1_enable = 1;
        pBasic->arBasic[i].rnd_green1_enable = 1;
        pBasic->arBasic[i].ro_green1_enable = 1;
        pBasic->arBasic[i].lc_green1_enable = 0;
        pBasic->arBasic[i].pg_green1_enable = 1;

        //methods_set_2 0x0010
        pBasic->arBasic[i].sw_rk_red_blue2_en = 1;
        pBasic->arBasic[i].rg_red_blue2_enable = 0;
        pBasic->arBasic[i].rnd_red_blue2_enable = 0;
        pBasic->arBasic[i].ro_red_blue2_enable = 1;
        pBasic->arBasic[i].lc_red_blue2_enable = 1;
        pBasic->arBasic[i].pg_red_blue2_enable = 1;
        pBasic->arBasic[i].sw_rk_green2_en = 1;
        pBasic->arBasic[i].rg_green2_enable = 0;
        pBasic->arBasic[i].rnd_green2_enable = 0;
        pBasic->arBasic[i].ro_green2_enable = 1;
        pBasic->arBasic[i].lc_green2_enable = 1;
        pBasic->arBasic[i].pg_green2_enable = 1;

        //methods_set_3 0x0014
        pBasic->arBasic[i].sw_rk_red_blue3_en = 0;
        pBasic->arBasic[i].rg_red_blue3_enable = 1;
        pBasic->arBasic[i].rnd_red_blue3_enable = 1;
        pBasic->arBasic[i].ro_red_blue3_enable = 1;
        pBasic->arBasic[i].lc_red_blue3_enable = 1;
        pBasic->arBasic[i].pg_red_blue3_enable = 1;
        pBasic->arBasic[i].sw_rk_green3_en = 0;
        pBasic->arBasic[i].rg_green3_enable = 1;
        pBasic->arBasic[i].rnd_green3_enable = 1;
        pBasic->arBasic[i].ro_green3_enable = 1;
        pBasic->arBasic[i].lc_green3_enable = 1;
        pBasic->arBasic[i].pg_green3_enable = 1;

        //line_thresh_1 0x0018
        pBasic->arBasic[i].sw_mindis1_rb = 0;
        pBasic->arBasic[i].sw_mindis1_g = 0;
        pBasic->arBasic[i].line_thr_1_rb = 8;
        pBasic->arBasic[i].line_thr_1_g = 8;

        //line_mad_fac_1 0x001c
        pBasic->arBasic[i].sw_dis_scale_min1 = 0;
        pBasic->arBasic[i].sw_dis_scale_max1 = 0;
        pBasic->arBasic[i].line_mad_fac_1_rb = 4;
        pBasic->arBasic[i].line_mad_fac_1_g = 4;

        //pg_fac_1 0x0020
        pBasic->arBasic[i].pg_fac_1_rb = 8;
        pBasic->arBasic[i].pg_fac_1_g = 8;

        //rnd_thresh_1 0x0024
        pBasic->arBasic[i].rnd_thr_1_rb = 10;
        pBasic->arBasic[i].rnd_thr_1_g = 10;

        //rg_fac_1 0x0028
        pBasic->arBasic[i].rg_fac_1_rb = 32;
        pBasic->arBasic[i].rg_fac_1_g = 32;


        //line_thresh_2 0x002c
        pBasic->arBasic[i].sw_mindis2_rb = 20;
        pBasic->arBasic[i].sw_mindis2_g = 20;
        pBasic->arBasic[i].line_thr_2_rb = 20;
        pBasic->arBasic[i].line_thr_2_g = 20;

        //line_mad_fac_2 0x0030
        pBasic->arBasic[i].sw_dis_scale_min2 = 12;
        pBasic->arBasic[i].sw_dis_scale_max2 = 12;
        pBasic->arBasic[i].line_mad_fac_2_rb = 10;
        pBasic->arBasic[i].line_mad_fac_2_g = 10;

        //pg_fac_2 0x0034
        pBasic->arBasic[i].pg_fac_2_rb = 5;
        pBasic->arBasic[i].pg_fac_2_g = 4;

        //rnd_thresh_2 0x0038
        pBasic->arBasic[i].rnd_thr_2_rb = 0;
        pBasic->arBasic[i].rnd_thr_2_g = 0;

        //rg_fac_2 0x003c
        pBasic->arBasic[i].rg_fac_2_rb = 0;
        pBasic->arBasic[i].rg_fac_2_g = 0;


        //line_thresh_3 0x0040
        pBasic->arBasic[i].sw_mindis3_rb = 0;
        pBasic->arBasic[i].sw_mindis3_g = 0;
        pBasic->arBasic[i].line_thr_3_rb = 32;
        pBasic->arBasic[i].line_thr_3_g = 32;

        //line_mad_fac_3 0x0044
        pBasic->arBasic[i].sw_dis_scale_min3 = 0;
        pBasic->arBasic[i].sw_dis_scale_max3 = 0;
        pBasic->arBasic[i].line_mad_fac_3_rb = 4;
        pBasic->arBasic[i].line_mad_fac_3_g = 4;

        //pg_fac_3 0x0048
        pBasic->arBasic[i].pg_fac_3_rb = 10;
        pBasic->arBasic[i].pg_fac_3_g = 10;

        //rnd_thresh_3 0x004c
        pBasic->arBasic[i].rnd_thr_3_rb = 8;
        pBasic->arBasic[i].rnd_thr_3_g = 6;

        //rg_fac_3 0x0050
        pBasic->arBasic[i].rg_fac_3_rb = 4;
        pBasic->arBasic[i].rg_fac_3_g = 4;

        //ro_limits 0x0054
        pBasic->arBasic[i].ro_lim_3_rb = 2;
        pBasic->arBasic[i].ro_lim_3_g = 1;
        pBasic->arBasic[i].ro_lim_2_rb = 2;
        pBasic->arBasic[i].ro_lim_2_g = 2;
        pBasic->arBasic[i].ro_lim_1_rb = 1;
        pBasic->arBasic[i].ro_lim_1_g = 1;

        //rnd_offs 0x0058
        pBasic->arBasic[i].rnd_offs_3_rb = 2;
        pBasic->arBasic[i].rnd_offs_3_g = 2;
        pBasic->arBasic[i].rnd_offs_2_rb = 0;
        pBasic->arBasic[i].rnd_offs_2_g = 0;
        pBasic->arBasic[i].rnd_offs_1_rb = 2;
        pBasic->arBasic[i].rnd_offs_1_g = 2;
#else

        //mode 0x0000
        pBasic->arBasic[i].stage1_enable = 1;
        pBasic->arBasic[i].grayscale_mode = 0;
        pBasic->arBasic[i].enable = 1;

        //output_mode 0x0004
        pBasic->arBasic[i].sw_rk_out_sel = 0;
        pBasic->arBasic[i].sw_dpcc_output_sel = 0;
        pBasic->arBasic[i].stage1_rb_3x3 = 0;
        pBasic->arBasic[i].stage1_g_3x3 = 0;
        pBasic->arBasic[i].stage1_incl_rb_center = 1;
        pBasic->arBasic[i].stage1_incl_green_center = 1;

        //set_use 0x0008
        pBasic->arBasic[i].stage1_use_fix_set = 0;
        pBasic->arBasic[i].stage1_use_set_3 = 1;
        pBasic->arBasic[i].stage1_use_set_2 = 1;
        pBasic->arBasic[i].stage1_use_set_1 = 1;

        //methods_set_1 0x000c
        pBasic->arBasic[i].sw_rk_red_blue1_en = 0;
        pBasic->arBasic[i].rg_red_blue1_enable = 1;
        pBasic->arBasic[i].rnd_red_blue1_enable = 1;
        pBasic->arBasic[i].ro_red_blue1_enable = 1;
        pBasic->arBasic[i].lc_red_blue1_enable = 0;
        pBasic->arBasic[i].pg_red_blue1_enable = 1;
        pBasic->arBasic[i].sw_rk_green1_en = 0;
        pBasic->arBasic[i].rg_green1_enable = 1;
        pBasic->arBasic[i].rnd_green1_enable = 1;
        pBasic->arBasic[i].ro_green1_enable = 1;
        pBasic->arBasic[i].lc_green1_enable = 0;
        pBasic->arBasic[i].pg_green1_enable = 1;

        //methods_set_2 0x0010
        pBasic->arBasic[i].sw_rk_red_blue2_en = 0;
        pBasic->arBasic[i].rg_red_blue2_enable = 0;
        pBasic->arBasic[i].rnd_red_blue2_enable = 0;
        pBasic->arBasic[i].ro_red_blue2_enable = 1;
        pBasic->arBasic[i].lc_red_blue2_enable = 1;
        pBasic->arBasic[i].pg_red_blue2_enable = 1;
        pBasic->arBasic[i].sw_rk_green2_en = 0;
        pBasic->arBasic[i].rg_green2_enable = 0;
        pBasic->arBasic[i].rnd_green2_enable = 0;
        pBasic->arBasic[i].ro_green2_enable = 1;
        pBasic->arBasic[i].lc_green2_enable = 1;
        pBasic->arBasic[i].pg_green2_enable = 1;

        //methods_set_3 0x0014
        pBasic->arBasic[i].sw_rk_red_blue3_en = 0;
        pBasic->arBasic[i].rg_red_blue3_enable = 1;
        pBasic->arBasic[i].rnd_red_blue3_enable = 1;
        pBasic->arBasic[i].ro_red_blue3_enable = 1;
        pBasic->arBasic[i].lc_red_blue3_enable = 1;
        pBasic->arBasic[i].pg_red_blue3_enable = 1;
        pBasic->arBasic[i].sw_rk_green3_en = 0;
        pBasic->arBasic[i].rg_green3_enable = 1;
        pBasic->arBasic[i].rnd_green3_enable = 1;
        pBasic->arBasic[i].ro_green3_enable = 1;
        pBasic->arBasic[i].lc_green3_enable = 1;
        pBasic->arBasic[i].pg_green3_enable = 1;

        //line_thresh_1 0x0018
        pBasic->arBasic[i].sw_mindis1_rb = 0;
        pBasic->arBasic[i].sw_mindis1_g = 0;
        pBasic->arBasic[i].line_thr_1_rb = 8;
        pBasic->arBasic[i].line_thr_1_g = 8;

        //line_mad_fac_1 0x001c
        pBasic->arBasic[i].sw_dis_scale_min1 = 0;
        pBasic->arBasic[i].sw_dis_scale_max1 = 0;
        pBasic->arBasic[i].line_mad_fac_1_rb = 4;
        pBasic->arBasic[i].line_mad_fac_1_g = 4;

        //pg_fac_1 0x0020
        pBasic->arBasic[i].pg_fac_1_rb = 8;
        pBasic->arBasic[i].pg_fac_1_g = 8;

        //rnd_thresh_1 0x0024
        pBasic->arBasic[i].rnd_thr_1_rb = 10;
        pBasic->arBasic[i].rnd_thr_1_g = 10;

        //rg_fac_1 0x0028
        pBasic->arBasic[i].rg_fac_1_rb = 32;
        pBasic->arBasic[i].rg_fac_1_g = 32;


        //line_thresh_2 0x002c
        pBasic->arBasic[i].sw_mindis2_rb = 0;
        pBasic->arBasic[i].sw_mindis2_g = 0;
        pBasic->arBasic[i].line_thr_2_rb = 20;
        pBasic->arBasic[i].line_thr_2_g = 20;

        //line_mad_fac_2 0x0030
        pBasic->arBasic[i].sw_dis_scale_min2 = 0;
        pBasic->arBasic[i].sw_dis_scale_max2 = 0;
        pBasic->arBasic[i].line_mad_fac_2_rb = 10;
        pBasic->arBasic[i].line_mad_fac_2_g = 10;

        //pg_fac_2 0x0034
        pBasic->arBasic[i].pg_fac_2_rb = 4;
        pBasic->arBasic[i].pg_fac_2_g = 5;

        //rnd_thresh_2 0x0038
        pBasic->arBasic[i].rnd_thr_2_rb = 0;
        pBasic->arBasic[i].rnd_thr_2_g = 0;

        //rg_fac_2 0x003c
        pBasic->arBasic[i].rg_fac_2_rb = 0;
        pBasic->arBasic[i].rg_fac_2_g = 0;


        //line_thresh_3 0x0040
        pBasic->arBasic[i].sw_mindis3_rb = 0;
        pBasic->arBasic[i].sw_mindis3_g = 0;
        pBasic->arBasic[i].line_thr_3_rb = 32;
        pBasic->arBasic[i].line_thr_3_g = 32;

        //line_mad_fac_3 0x0044
        pBasic->arBasic[i].sw_dis_scale_min3 = 0;
        pBasic->arBasic[i].sw_dis_scale_max3 = 0;
        pBasic->arBasic[i].line_mad_fac_3_rb = 4;
        pBasic->arBasic[i].line_mad_fac_3_g = 4;

        //pg_fac_3 0x0048
        pBasic->arBasic[i].pg_fac_3_rb = 10;
        pBasic->arBasic[i].pg_fac_3_g = 10;

        //rnd_thresh_3 0x004c
        pBasic->arBasic[i].rnd_thr_3_rb = 8;
        pBasic->arBasic[i].rnd_thr_3_g = 6;

        //rg_fac_3 0x0050
        pBasic->arBasic[i].rg_fac_3_rb = 4;
        pBasic->arBasic[i].rg_fac_3_g = 4;

        //ro_limits 0x0054
        pBasic->arBasic[i].ro_lim_3_rb = 2;
        pBasic->arBasic[i].ro_lim_3_g = 1;
        pBasic->arBasic[i].ro_lim_2_rb = 2;
        pBasic->arBasic[i].ro_lim_2_g = 2;
        pBasic->arBasic[i].ro_lim_1_rb = 1;
        pBasic->arBasic[i].ro_lim_1_g = 1;

        //rnd_offs 0x0058
        pBasic->arBasic[i].rnd_offs_3_rb = 2;
        pBasic->arBasic[i].rnd_offs_3_g = 2;
        pBasic->arBasic[i].rnd_offs_2_rb = 2;
        pBasic->arBasic[i].rnd_offs_2_g = 2;
        pBasic->arBasic[i].rnd_offs_1_rb = 2;
        pBasic->arBasic[i].rnd_offs_1_g = 2;
#endif
    }

    memset(pBpt, 0x00, sizeof(Adpcc_bpt_params_t));
    memset(pPdaf, 0x00, sizeof(Adpcc_pdaf_params_t));

    LOGI_ADPCC("%s(%d): exit!\n", __FUNCTION__, __LINE__);
    return ret;

}

AdpccResult_t dpcc_fast_mode_basic_params_init(Adpcc_fast_mode_params_t *pFasic, CalibDb_Dpcc_t *pCalib)
{
    AdpccResult_t ret = ADPCC_RET_SUCCESS;
    LOGI_ADPCC("%s(%d): enter!\n", __FUNCTION__, __LINE__);

    if(pFasic == NULL) {
        ret = ADPCC_RET_NULL_POINTER;
        LOGE_ADPCC("%s(%d): invalid input params\n", __FUNCTION__, __LINE__);
        return ret;
    }

    if(pCalib == NULL) {
        ret = ADPCC_RET_NULL_POINTER;
        LOGE_ADPCC("%s(%d): invalid input params\n", __FUNCTION__, __LINE__);
        return ret;
    }

    pFasic->fast_mode_en = pCalib->fast.fast_mode_en;
    pFasic->fast_mode_single_en = pCalib->fast.fast_mode_single_en;
    pFasic->fast_mode_double_en = pCalib->fast.fast_mode_double_en;
    pFasic->fast_mode_triple_en = pCalib->fast.fast_mode_triple_en;

    for(int i = 0; i < DPCC_MAX_ISO_LEVEL; i++) {
        pFasic->ISO[i] = pCalib->fast.ISO[i];
        pFasic->fast_mode_single_level[i] = pCalib->fast.fast_mode_single_level[i];
        pFasic->fast_mode_double_level[i] = pCalib->fast.fast_mode_double_level[i];
        pFasic->fast_mode_triple_level[i] = pCalib->fast.fast_mode_triple_level[i];
    }

    LOGI_ADPCC("%s(%d): exit!\n", __FUNCTION__, __LINE__);
    return ret;

}


AdpccResult_t dpcc_expert_mode_basic_params_init(Adpcc_basic_params_t *pBasic, CalibDb_Dpcc_t *pCalib)
{
    AdpccResult_t ret = ADPCC_RET_SUCCESS;
    LOGI_ADPCC("%s(%d): enter!\n", __FUNCTION__, __LINE__);

    if(pBasic == NULL) {
        ret = ADPCC_RET_NULL_POINTER;
        LOGE_ADPCC("%s(%d): invalid input params\n", __FUNCTION__, __LINE__);
        return ret;
    }

    if(pCalib == NULL) {
        ret = ADPCC_RET_NULL_POINTER;
        LOGE_ADPCC("%s(%d): invalid input params\n", __FUNCTION__, __LINE__);
        return ret;
    }

    for(int i = 0; i < DPCC_MAX_ISO_LEVEL; i++) {
        pBasic->arBasic[i].iso = pCalib->expert.iso[i];

        //mode 0x0000
        pBasic->arBasic[i].stage1_enable = pCalib->expert.stage1_Enable[i];
        pBasic->arBasic[i].grayscale_mode = pCalib->expert.grayscale_mode[i];
        pBasic->arBasic[i].enable = pCalib->enable;

        //output_mode 0x0004
        pBasic->arBasic[i].sw_rk_out_sel = pCalib->expert.rk_out_sel[i];
        pBasic->arBasic[i].sw_dpcc_output_sel = pCalib->expert.dpcc_out_sel[i];
        pBasic->arBasic[i].stage1_rb_3x3 = pCalib->expert.stage1_rb_3x3[i];
        pBasic->arBasic[i].stage1_g_3x3 = pCalib->expert.stage1_g_3x3[i];
        pBasic->arBasic[i].stage1_incl_rb_center = pCalib->expert.stage1_inc_rb_center[i];
        pBasic->arBasic[i].stage1_incl_green_center = pCalib->expert.stage1_inc_g_center[i];

        //set_use 0x0008
        pBasic->arBasic[i].stage1_use_fix_set = pCalib->expert.stage1_use_fix_set[i];
        pBasic->arBasic[i].stage1_use_set_3 = pCalib->expert.stage1_use_set3[i];
        pBasic->arBasic[i].stage1_use_set_2 = pCalib->expert.stage1_use_set2[i];
        pBasic->arBasic[i].stage1_use_set_1 = pCalib->expert.stage1_use_set1[i];

        //methods_set_1 0x000c
        pBasic->arBasic[i].sw_rk_red_blue1_en = pCalib->expert.set[0].red_blue_enable[0][i];
        pBasic->arBasic[i].rg_red_blue1_enable = pCalib->expert.set[0].red_blue_enable[1][i];
        pBasic->arBasic[i].rnd_red_blue1_enable = pCalib->expert.set[0].red_blue_enable[2][i];
        pBasic->arBasic[i].ro_red_blue1_enable = pCalib->expert.set[0].red_blue_enable[3][i];
        pBasic->arBasic[i].lc_red_blue1_enable = pCalib->expert.set[0].red_blue_enable[4][i];
        pBasic->arBasic[i].pg_red_blue1_enable = pCalib->expert.set[0].red_blue_enable[5][i];
        pBasic->arBasic[i].sw_rk_green1_en = pCalib->expert.set[0].green_enable[0][i];
        pBasic->arBasic[i].rg_green1_enable = pCalib->expert.set[0].green_enable[1][i];
        pBasic->arBasic[i].rnd_green1_enable = pCalib->expert.set[0].green_enable[2][i];
        pBasic->arBasic[i].ro_green1_enable = pCalib->expert.set[0].green_enable[3][i];
        pBasic->arBasic[i].lc_green1_enable = pCalib->expert.set[0].green_enable[4][i];
        pBasic->arBasic[i].pg_green1_enable = pCalib->expert.set[0].green_enable[5][i];

        //methods_set_2 0x0010
        pBasic->arBasic[i].sw_rk_red_blue2_en = pCalib->expert.set[1].red_blue_enable[0][i];
        pBasic->arBasic[i].rg_red_blue2_enable = pCalib->expert.set[1].red_blue_enable[1][i];
        pBasic->arBasic[i].rnd_red_blue2_enable = pCalib->expert.set[1].red_blue_enable[2][i];
        pBasic->arBasic[i].ro_red_blue2_enable = pCalib->expert.set[1].red_blue_enable[3][i];
        pBasic->arBasic[i].lc_red_blue2_enable = pCalib->expert.set[1].red_blue_enable[4][i];
        pBasic->arBasic[i].pg_red_blue2_enable = pCalib->expert.set[1].red_blue_enable[5][i];
        pBasic->arBasic[i].sw_rk_green2_en = pCalib->expert.set[1].green_enable[0][i];
        pBasic->arBasic[i].rg_green2_enable = pCalib->expert.set[1].green_enable[1][i];
        pBasic->arBasic[i].rnd_green2_enable = pCalib->expert.set[1].green_enable[2][i];
        pBasic->arBasic[i].ro_green2_enable = pCalib->expert.set[1].green_enable[3][i];
        pBasic->arBasic[i].lc_green2_enable = pCalib->expert.set[1].green_enable[4][i];
        pBasic->arBasic[i].pg_green2_enable = pCalib->expert.set[1].green_enable[5][i];

        //methods_set_3 0x0014
        pBasic->arBasic[i].sw_rk_red_blue3_en = pCalib->expert.set[2].red_blue_enable[0][i];
        pBasic->arBasic[i].rg_red_blue3_enable = pCalib->expert.set[2].red_blue_enable[1][i];
        pBasic->arBasic[i].rnd_red_blue3_enable = pCalib->expert.set[2].red_blue_enable[2][i];
        pBasic->arBasic[i].ro_red_blue3_enable = pCalib->expert.set[2].red_blue_enable[3][i];
        pBasic->arBasic[i].lc_red_blue3_enable = pCalib->expert.set[2].red_blue_enable[4][i];
        pBasic->arBasic[i].pg_red_blue3_enable = pCalib->expert.set[2].red_blue_enable[5][i];
        pBasic->arBasic[i].sw_rk_green3_en = pCalib->expert.set[2].green_enable[0][i];
        pBasic->arBasic[i].rg_green3_enable = pCalib->expert.set[2].green_enable[1][i];
        pBasic->arBasic[i].rnd_green3_enable = pCalib->expert.set[2].green_enable[2][i];
        pBasic->arBasic[i].ro_green3_enable = pCalib->expert.set[2].green_enable[3][i];
        pBasic->arBasic[i].lc_green3_enable = pCalib->expert.set[2].green_enable[4][i];
        pBasic->arBasic[i].pg_green3_enable = pCalib->expert.set[2].green_enable[5][i];

        //line_thresh_1 0x0018
        pBasic->arBasic[i].sw_mindis1_rb = pCalib->expert.set[0].line_thresh[0][i];
        pBasic->arBasic[i].sw_mindis1_g = pCalib->expert.set[0].line_thresh[1][i];
        pBasic->arBasic[i].line_thr_1_rb = pCalib->expert.set[0].line_thresh[2][i];
        pBasic->arBasic[i].line_thr_1_g = pCalib->expert.set[0].line_thresh[3][i];

        //line_mad_fac_1 0x001c
        pBasic->arBasic[i].sw_dis_scale_min1 = pCalib->expert.set[0].line_mad_fac[0][i];
        pBasic->arBasic[i].sw_dis_scale_max1 = pCalib->expert.set[0].line_mad_fac[1][i];
        pBasic->arBasic[i].line_mad_fac_1_rb = pCalib->expert.set[0].line_mad_fac[2][i];
        pBasic->arBasic[i].line_mad_fac_1_g = pCalib->expert.set[0].line_mad_fac[3][i];

        //pg_fac_1 0x0020
        pBasic->arBasic[i].pg_fac_1_rb = pCalib->expert.set[0].pg_fac[0][i];
        pBasic->arBasic[i].pg_fac_1_g = pCalib->expert.set[0].pg_fac[1][i];

        //rnd_thresh_1 0x0024
        pBasic->arBasic[i].rnd_thr_1_rb = pCalib->expert.set[0].rnd_thresh[0][i];
        pBasic->arBasic[i].rnd_thr_1_g = pCalib->expert.set[0].rnd_thresh[1][i];

        //rg_fac_1 0x0028
        pBasic->arBasic[i].rg_fac_1_rb = pCalib->expert.set[0].rg_fac[0][i];
        pBasic->arBasic[i].rg_fac_1_g = pCalib->expert.set[0].rg_fac[1][i];


        //line_thresh_2 0x002c
        pBasic->arBasic[i].sw_mindis2_rb = pCalib->expert.set[1].line_thresh[0][i];
        pBasic->arBasic[i].sw_mindis2_g = pCalib->expert.set[1].line_thresh[1][i];
        pBasic->arBasic[i].line_thr_2_rb = pCalib->expert.set[1].line_thresh[2][i];
        pBasic->arBasic[i].line_thr_2_g = pCalib->expert.set[1].line_thresh[3][i];

        //line_mad_fac_2 0x0030
        pBasic->arBasic[i].sw_dis_scale_min2 = pCalib->expert.set[1].line_mad_fac[0][i];
        pBasic->arBasic[i].sw_dis_scale_max2 = pCalib->expert.set[1].line_mad_fac[1][i];
        pBasic->arBasic[i].line_mad_fac_2_rb = pCalib->expert.set[1].line_mad_fac[2][i];
        pBasic->arBasic[i].line_mad_fac_2_g = pCalib->expert.set[1].line_mad_fac[3][i];

        //pg_fac_2 0x0034
        pBasic->arBasic[i].pg_fac_2_rb = pCalib->expert.set[1].pg_fac[0][i];
        pBasic->arBasic[i].pg_fac_2_g = pCalib->expert.set[1].pg_fac[1][i];

        //rnd_thresh_2 0x0038
        pBasic->arBasic[i].rnd_thr_2_rb = pCalib->expert.set[1].rnd_thresh[0][i];
        pBasic->arBasic[i].rnd_thr_2_g = pCalib->expert.set[1].rnd_thresh[1][i];

        //rg_fac_2 0x003c
        pBasic->arBasic[i].rg_fac_2_rb = pCalib->expert.set[1].rg_fac[0][i];
        pBasic->arBasic[i].rg_fac_2_g = pCalib->expert.set[1].rg_fac[1][i];


        //line_thresh_3 0x0040
        pBasic->arBasic[i].sw_mindis3_rb = pCalib->expert.set[2].line_thresh[0][i];
        pBasic->arBasic[i].sw_mindis3_g = pCalib->expert.set[2].line_thresh[1][i];
        pBasic->arBasic[i].line_thr_3_rb = pCalib->expert.set[2].line_thresh[2][i];
        pBasic->arBasic[i].line_thr_3_g = pCalib->expert.set[2].line_thresh[3][i];

        //line_mad_fac_3 0x0044
        pBasic->arBasic[i].sw_dis_scale_min3 = pCalib->expert.set[2].line_mad_fac[0][i];
        pBasic->arBasic[i].sw_dis_scale_max3 = pCalib->expert.set[2].line_mad_fac[1][i];
        pBasic->arBasic[i].line_mad_fac_3_rb = pCalib->expert.set[2].line_mad_fac[2][i];
        pBasic->arBasic[i].line_mad_fac_3_g = pCalib->expert.set[2].line_mad_fac[3][i];

        //pg_fac_3 0x0048
        pBasic->arBasic[i].pg_fac_3_rb = pCalib->expert.set[2].pg_fac[0][i];
        pBasic->arBasic[i].pg_fac_3_g = pCalib->expert.set[2].pg_fac[1][i];

        //rnd_thresh_3 0x004c
        pBasic->arBasic[i].rnd_thr_3_rb = pCalib->expert.set[2].rnd_thresh[0][i];
        pBasic->arBasic[i].rnd_thr_3_g = pCalib->expert.set[2].rnd_thresh[1][i];

        //rg_fac_3 0x0050
        pBasic->arBasic[i].rg_fac_3_rb = pCalib->expert.set[2].rg_fac[0][i];
        pBasic->arBasic[i].rg_fac_3_g = pCalib->expert.set[2].rg_fac[1][i];

        //ro_limits 0x0054
        pBasic->arBasic[i].ro_lim_3_rb = pCalib->expert.set[2].ro_lim[0][i];
        pBasic->arBasic[i].ro_lim_3_g = pCalib->expert.set[2].ro_lim[1][i];
        pBasic->arBasic[i].ro_lim_2_rb = pCalib->expert.set[1].ro_lim[0][i];
        pBasic->arBasic[i].ro_lim_2_g = pCalib->expert.set[1].ro_lim[1][i];
        pBasic->arBasic[i].ro_lim_1_rb = pCalib->expert.set[0].ro_lim[0][i];
        pBasic->arBasic[i].ro_lim_1_g = pCalib->expert.set[0].ro_lim[1][i];

        //rnd_offs 0x0058
        pBasic->arBasic[i].rnd_offs_3_rb = pCalib->expert.set[2].rnd_offs[0][i];
        pBasic->arBasic[i].rnd_offs_3_g = pCalib->expert.set[2].rnd_offs[1][i];
        pBasic->arBasic[i].rnd_offs_2_rb = pCalib->expert.set[1].rnd_offs[0][i];
        pBasic->arBasic[i].rnd_offs_2_g = pCalib->expert.set[1].rnd_offs[1][i];
        pBasic->arBasic[i].rnd_offs_1_rb = pCalib->expert.set[0].rnd_offs[0][i];
        pBasic->arBasic[i].rnd_offs_1_g = pCalib->expert.set[0].rnd_offs[1][i];

    }

    LOGI_ADPCC("%s(%d): exit!\n", __FUNCTION__, __LINE__);
    return ret;

}

AdpccResult_t dpcc_pdaf_params_init(Adpcc_pdaf_params_t *pPdaf, CalibDb_Dpcc_Pdaf_t *pCalib)
{
    AdpccResult_t ret = ADPCC_RET_SUCCESS;
    LOGI_ADPCC("%s(%d): enter!\n", __FUNCTION__, __LINE__);

    if(pPdaf == NULL) {
        ret = ADPCC_RET_NULL_POINTER;
        LOGE_ADPCC("%s(%d): invalid input params\n", __FUNCTION__, __LINE__);
        return ret;
    }

    if(pCalib == NULL) {
        ret = ADPCC_RET_NULL_POINTER;
        LOGE_ADPCC("%s(%d): invalid input params\n", __FUNCTION__, __LINE__);
        return ret;
    }

    pPdaf->sw_pdaf_en = pCalib->en;

    for(int i = 0; i < 16; i++) {
        pPdaf->pdaf_point_en[i] = pCalib->point_en[i];
        pPdaf->point[i].x = pCalib->point_x[i];
        pPdaf->point[i].y = pCalib->point_y[i];
    }

    pPdaf->pdaf_offsetx = pCalib->offsetx;
    pPdaf->pdaf_offsety  = pCalib->offsety;
    pPdaf->pdaf_wrapx = pCalib->wrapx;
    pPdaf->pdaf_wrapy = pCalib->wrapy;
    pPdaf->pdaf_wrapx_num = pCalib->wrapx_num;
    pPdaf->pdaf_wrapy_num = pCalib->wrapy_num;
    pPdaf->pdaf_forward_med = pCalib->forward_med;

    LOGI_ADPCC("%s(%d): exit!\n", __FUNCTION__, __LINE__);
    return ret;
}

AdpccResult_t Expert_mode_select_basic_params_by_ISO(
    Adpcc_basic_params_t *pParams,
    Adpcc_basic_params_select_t *pSelect,
    AdpccExpInfo_t *pExpInfo)
{
    AdpccResult_t ret = ADPCC_RET_SUCCESS;
    int lowLevel = 0;
    int highLevel = 0;
    int lowIso = 0;
    int highIso = 0;
    float ratio = 0.0;
    int iso = 50;

    LOGI_ADPCC("%s(%d): enter!\n", __FUNCTION__, __LINE__);

    if(pParams == NULL) {
        ret = ADPCC_RET_NULL_POINTER;
        LOGE_ADPCC("%s(%d): invalid inputparams\n", __FUNCTION__, __LINE__);
        return ret;
    }

    if(pSelect == NULL) {
        ret = ADPCC_RET_NULL_POINTER;
        LOGE_ADPCC("%s(%d): invalid inputparams\n", __FUNCTION__, __LINE__);
        return ret;
    }

    if(pExpInfo == NULL) {
        ret = ADPCC_RET_NULL_POINTER;
        LOGE_ADPCC("%s(%d): invalid inputparams\n", __FUNCTION__, __LINE__);
        return ret;
    }

    iso = pExpInfo->arPreResIso[pExpInfo->hdr_mode];

    for(int i = 0; i < DPCC_MAX_ISO_LEVEL - 1; i++) {
        LOGD_ADPCC("%s:(%d) iso:%d %d %d\n", __FUNCTION__, __LINE__,
                   iso, pParams->arBasic[i].iso, pParams->arBasic[i + 1].iso);
        if(iso >= pParams->arBasic[i].iso && iso <= pParams->arBasic[i + 1].iso) {
            lowLevel = i;
            highLevel = i + 1;
            lowIso = pParams->arBasic[i].iso;
            highIso = pParams->arBasic[i + 1].iso;
            //ratio = (iso -lowIso ) / (float)(highIso - lowIso);
            ratio = 0.0;
            break;
        }
    }

    if(iso < pParams->arBasic[0].iso ) {
        lowLevel = 0;
        highLevel = 0;
        ratio = 0.0;
    }

    if(iso > pParams->arBasic[DPCC_MAX_ISO_LEVEL - 1].iso ) {
        lowLevel = DPCC_MAX_ISO_LEVEL - 1;
        highLevel = DPCC_MAX_ISO_LEVEL - 1;
        ratio = 1.0;
    }

    LOGD_ADPCC("%s:(%d) iso:%d lowLevel:%d hightLevel:%d lowIso:%d HighIso:%d ratio:%f\n",
               __FUNCTION__, __LINE__, iso, lowLevel, highLevel, lowIso, highIso, ratio);

    //mode 0x0000
    pSelect->stage1_enable = pParams->arBasic[lowLevel].stage1_enable;
    pSelect->grayscale_mode = pParams->arBasic[lowLevel].grayscale_mode;
    pSelect->enable = pParams->arBasic[lowLevel].enable;

    //output_mode 0x0004
    pSelect->sw_rk_out_sel = pParams->arBasic[lowLevel].sw_rk_out_sel;
    pSelect->sw_dpcc_output_sel = pParams->arBasic[lowLevel].sw_dpcc_output_sel;
    pSelect->stage1_rb_3x3 = pParams->arBasic[lowLevel].stage1_rb_3x3;
    pSelect->stage1_g_3x3 = pParams->arBasic[lowLevel].stage1_g_3x3;
    pSelect->stage1_incl_rb_center = pParams->arBasic[lowLevel].stage1_incl_rb_center;
    pSelect->stage1_incl_green_center = pParams->arBasic[lowLevel].stage1_incl_green_center;

    //set_use 0x0008
    pSelect->stage1_use_fix_set = pParams->arBasic[lowLevel].stage1_use_fix_set;
    pSelect->stage1_use_set_3 = pParams->arBasic[lowLevel].stage1_use_set_3;
    pSelect->stage1_use_set_2 = pParams->arBasic[lowLevel].stage1_use_set_2;
    pSelect->stage1_use_set_1 = pParams->arBasic[lowLevel].stage1_use_set_1;

    //methods_set_1 0x000c
    pSelect->sw_rk_red_blue1_en = pParams->arBasic[lowLevel].sw_rk_red_blue1_en;
    pSelect->rg_red_blue1_enable = pParams->arBasic[lowLevel].rg_red_blue1_enable;
    pSelect->rnd_red_blue1_enable = pParams->arBasic[lowLevel].rnd_red_blue1_enable;
    pSelect->ro_red_blue1_enable = pParams->arBasic[lowLevel].ro_red_blue1_enable;
    pSelect->lc_red_blue1_enable = pParams->arBasic[lowLevel].lc_red_blue1_enable;
    pSelect->pg_red_blue1_enable = pParams->arBasic[lowLevel].pg_red_blue1_enable;
    pSelect->sw_rk_green1_en = pParams->arBasic[lowLevel].sw_rk_green1_en;
    pSelect->rg_green1_enable = pParams->arBasic[lowLevel].rg_green1_enable;
    pSelect->rnd_green1_enable = pParams->arBasic[lowLevel].rnd_green1_enable;
    pSelect->ro_green1_enable = pParams->arBasic[lowLevel].ro_green1_enable;
    pSelect->lc_green1_enable = pParams->arBasic[lowLevel].lc_green1_enable;
    pSelect->pg_green1_enable = pParams->arBasic[lowLevel].pg_green1_enable;

    //methods_set_2 0x0010
    pSelect->sw_rk_red_blue2_en = pParams->arBasic[lowLevel].sw_rk_red_blue2_en;
    pSelect->rg_red_blue2_enable = pParams->arBasic[lowLevel].rg_red_blue2_enable;
    pSelect->rnd_red_blue2_enable = pParams->arBasic[lowLevel].rnd_red_blue2_enable;
    pSelect->ro_red_blue2_enable = pParams->arBasic[lowLevel].ro_red_blue2_enable;
    pSelect->lc_red_blue2_enable = pParams->arBasic[lowLevel].lc_red_blue2_enable;
    pSelect->pg_red_blue2_enable = pParams->arBasic[lowLevel].pg_red_blue2_enable;
    pSelect->sw_rk_green2_en = pParams->arBasic[lowLevel].sw_rk_green2_en;
    pSelect->rg_green2_enable = pParams->arBasic[lowLevel].rg_green2_enable;
    pSelect->rnd_green2_enable = pParams->arBasic[lowLevel].rnd_green2_enable;
    pSelect->ro_green2_enable = pParams->arBasic[lowLevel].ro_green2_enable;
    pSelect->lc_green2_enable = pParams->arBasic[lowLevel].lc_green2_enable;
    pSelect->pg_green2_enable = pParams->arBasic[lowLevel].pg_green2_enable;

    //methods_set_3 0x0014
    pSelect->sw_rk_red_blue3_en = pParams->arBasic[lowLevel].sw_rk_red_blue3_en;
    pSelect->rg_red_blue3_enable = pParams->arBasic[lowLevel].rg_red_blue3_enable;
    pSelect->rnd_red_blue3_enable = pParams->arBasic[lowLevel].rnd_red_blue3_enable;
    pSelect->ro_red_blue3_enable = pParams->arBasic[lowLevel].ro_red_blue3_enable;
    pSelect->lc_red_blue3_enable = pParams->arBasic[lowLevel].lc_red_blue3_enable;
    pSelect->pg_red_blue3_enable = pParams->arBasic[lowLevel].pg_red_blue3_enable;
    pSelect->sw_rk_green3_en = pParams->arBasic[lowLevel].sw_rk_green3_en;
    pSelect->rg_green3_enable = pParams->arBasic[lowLevel].rg_green3_enable;
    pSelect->rnd_green3_enable = pParams->arBasic[lowLevel].rnd_green3_enable;
    pSelect->ro_green3_enable = pParams->arBasic[lowLevel].ro_green3_enable;
    pSelect->lc_green3_enable = pParams->arBasic[lowLevel].lc_green3_enable;
    pSelect->pg_green3_enable = pParams->arBasic[lowLevel].pg_green3_enable;

    //line_thresh_1 0x0018
    pSelect->sw_mindis1_rb = pParams->arBasic[lowLevel].sw_mindis1_rb;
    pSelect->sw_mindis1_g = pParams->arBasic[lowLevel].sw_mindis1_g;
    pSelect->line_thr_1_rb = pParams->arBasic[lowLevel].line_thr_1_rb;
    pSelect->line_thr_1_g = pParams->arBasic[lowLevel].line_thr_1_g;

    //line_mad_fac_1 0x001c
    pSelect->sw_dis_scale_min1 = pParams->arBasic[lowLevel].sw_dis_scale_min1;
    pSelect->sw_dis_scale_max1 = pParams->arBasic[lowLevel].sw_dis_scale_max1;
    pSelect->line_mad_fac_1_rb = pParams->arBasic[lowLevel].line_mad_fac_1_rb;
    pSelect->line_mad_fac_1_g = pParams->arBasic[lowLevel].line_mad_fac_1_g;

    //pg_fac_1 0x0020
    pSelect->pg_fac_1_rb = pParams->arBasic[lowLevel].pg_fac_1_rb;
    pSelect->pg_fac_1_g = pParams->arBasic[lowLevel].pg_fac_1_g;

    //rnd_thresh_1 0x0024
    pSelect->rnd_thr_1_rb = pParams->arBasic[lowLevel].rnd_thr_1_rb;
    pSelect->rnd_thr_1_g = pParams->arBasic[lowLevel].rnd_thr_1_g;

    //rg_fac_1 0x0028
    pSelect->rg_fac_1_rb = pParams->arBasic[lowLevel].rg_fac_1_rb;
    pSelect->rg_fac_1_g = pParams->arBasic[lowLevel].rg_fac_1_g;


    //line_thresh_2 0x002c
    pSelect->sw_mindis2_rb = pParams->arBasic[lowLevel].sw_mindis2_rb;
    pSelect->sw_mindis2_g = pParams->arBasic[lowLevel].sw_mindis2_g;
    pSelect->line_thr_2_rb = pParams->arBasic[lowLevel].line_thr_2_rb;
    pSelect->line_thr_2_g = pParams->arBasic[lowLevel].line_thr_2_g;

    //line_mad_fac_2 0x0030
    pSelect->sw_dis_scale_min2 = pParams->arBasic[lowLevel].sw_dis_scale_min2;
    pSelect->sw_dis_scale_max2 = pParams->arBasic[lowLevel].sw_dis_scale_max2;
    pSelect->line_mad_fac_2_rb = pParams->arBasic[lowLevel].line_mad_fac_2_rb;
    pSelect->line_mad_fac_2_g = pParams->arBasic[lowLevel].line_mad_fac_2_g;

    //pg_fac_2 0x0034
    pSelect->pg_fac_2_rb = pParams->arBasic[lowLevel].pg_fac_2_rb;
    pSelect->pg_fac_2_g = pParams->arBasic[lowLevel].pg_fac_2_g;

    //rnd_thresh_2 0x0038
    pSelect->rnd_thr_2_rb = pParams->arBasic[lowLevel].rnd_thr_2_rb;
    pSelect->rnd_thr_2_g = pParams->arBasic[lowLevel].rnd_thr_2_g;

    //rg_fac_2 0x003c
    pSelect->rg_fac_2_rb = pParams->arBasic[lowLevel].rg_fac_2_rb;
    pSelect->rg_fac_2_g = pParams->arBasic[lowLevel].rg_fac_2_g;


    //line_thresh_3 0x0040
    pSelect->sw_mindis3_rb = pParams->arBasic[lowLevel].sw_mindis3_rb;
    pSelect->sw_mindis3_g = pParams->arBasic[lowLevel].sw_mindis3_g;
    pSelect->line_thr_3_rb = pParams->arBasic[lowLevel].line_thr_3_rb;
    pSelect->line_thr_3_g = pParams->arBasic[lowLevel].line_thr_3_g;

    //line_mad_fac_3 0x0044
    pSelect->sw_dis_scale_min3 = pParams->arBasic[lowLevel].sw_dis_scale_min3;
    pSelect->sw_dis_scale_max3 = pParams->arBasic[lowLevel].sw_dis_scale_max3;
    pSelect->line_mad_fac_3_rb = pParams->arBasic[lowLevel].line_mad_fac_3_rb;
    pSelect->line_mad_fac_3_g = pParams->arBasic[lowLevel].line_mad_fac_3_g;

    //pg_fac_3 0x0048
    pSelect->pg_fac_3_rb = pParams->arBasic[lowLevel].pg_fac_3_rb;
    pSelect->pg_fac_3_g = pParams->arBasic[lowLevel].pg_fac_3_g;

    //rnd_thresh_3 0x004c
    pSelect->rnd_thr_3_rb = pParams->arBasic[lowLevel].rnd_thr_3_rb;
    pSelect->rnd_thr_3_g = pParams->arBasic[lowLevel].rnd_thr_3_g;

    //rg_fac_3 0x0050
    pSelect->rg_fac_3_rb = pParams->arBasic[lowLevel].rg_fac_3_rb;
    pSelect->rg_fac_3_g = pParams->arBasic[lowLevel].rg_fac_3_g;

    //ro_limits 0x0054
    pSelect->ro_lim_3_rb = pParams->arBasic[lowLevel].ro_lim_3_rb;
    pSelect->ro_lim_3_g = pParams->arBasic[lowLevel].ro_lim_3_g;
    pSelect->ro_lim_2_rb = pParams->arBasic[lowLevel].ro_lim_2_rb;
    pSelect->ro_lim_2_g = pParams->arBasic[lowLevel].ro_lim_2_g;
    pSelect->ro_lim_1_rb = pParams->arBasic[lowLevel].ro_lim_1_rb;
    pSelect->ro_lim_1_g = pParams->arBasic[lowLevel].ro_lim_1_g;

    //rnd_offs 0x0058
    pSelect->rnd_offs_3_rb = pParams->arBasic[lowLevel].rnd_offs_3_rb;
    pSelect->rnd_offs_3_g = pParams->arBasic[lowLevel].rnd_offs_3_g;
    pSelect->rnd_offs_2_rb = pParams->arBasic[lowLevel].rnd_offs_2_rb;
    pSelect->rnd_offs_2_g = pParams->arBasic[lowLevel].rnd_offs_2_g;
    pSelect->rnd_offs_1_rb = pParams->arBasic[lowLevel].rnd_offs_1_rb;
    pSelect->rnd_offs_1_g = pParams->arBasic[lowLevel].rnd_offs_1_g;


    LOGD_ADPCC("%s:(%d) %d %d %d %d %d\n", __FUNCTION__, __LINE__,
               pSelect->enable, pSelect->line_thr_2_g, pSelect->line_mad_fac_2_rb,
               pSelect->ro_lim_2_g, pSelect->rnd_offs_2_g);

    LOGI_ADPCC("%s(%d): exit!\n", __FUNCTION__, __LINE__);
    return ret;
}

void Fast_mode_Triple_Setting(
    AdpccContext_t *pParams,
    Adpcc_basic_params_select_t *pSelect,
    int iso)
{
    LOGI_ADPCC("%s(%d): enter!\n", __FUNCTION__, __LINE__);

    int level = 1;
    for(int i = 0; i < DPCC_MAX_ISO_LEVEL - 1; i++) {
        if(iso >= pParams->fast.ISO[i] && iso <= pParams->fast.ISO[i + 1]) {
            level = (pParams->fast.fast_mode_triple_level[i] - pParams->fast.fast_mode_triple_level[i + 1])
                    / (pParams->fast.ISO[i] - pParams->fast.ISO[i + 1]);
            level += pParams->fast.fast_mode_triple_level[i];
            break;
        }
    }

    if(iso < pParams->fast.ISO[0] ) {
        level = pParams->fast.fast_mode_triple_level[0];
    }

    if(iso > pParams->fast.ISO[DPCC_MAX_ISO_LEVEL - 1] ) {
        level = pParams->fast.fast_mode_triple_level[DPCC_MAX_ISO_LEVEL - 1];
    }

    if(pParams->fast.fast_mode_triple_en != 0)
        pSelect->stage1_use_set_3 = 0x1;
    else
        pSelect->stage1_use_set_3 = 0x0;

    switch (level)
    {
    case 1:
        pSelect->sw_rk_green3_en = 1;
        pSelect->sw_mindis3_rb = 0x5;
        pSelect->sw_mindis3_g = 0x5;
        pSelect->sw_dis_scale_min3 = 0x3;
        pSelect->sw_dis_scale_max3 = 0x3;

        pSelect->rg_red_blue3_enable = 0;
        pSelect->rg_green3_enable = 0;
        pSelect->rg_fac_3_rb = 0;
        pSelect->rg_fac_3_g = 0;

        pSelect->rnd_red_blue3_enable = 1;
        pSelect->rnd_green3_enable = 1;
        pSelect->rnd_thr_3_rb = 4;
        pSelect->rnd_thr_3_g = 4;
        pSelect->rnd_offs_3_rb = 2;
        pSelect->rnd_offs_3_g = 2;

        pSelect->ro_red_blue3_enable = 1;
        pSelect->ro_green3_enable = 1;
        pSelect->ro_lim_3_rb = 2;
        pSelect->ro_lim_3_g = 2;

        pSelect->lc_red_blue3_enable = 1;
        pSelect->lc_green3_enable = 0;
        pSelect->line_thr_3_rb = 0x3;
        pSelect->line_thr_3_g = 0;
        pSelect->line_mad_fac_3_rb = 0x3;
        pSelect->line_mad_fac_3_g = 0;

        pSelect->pg_red_blue3_enable = 1;
        pSelect->pg_green3_enable = 1;
        pSelect->pg_fac_3_rb = 0x3;
        pSelect->pg_fac_3_g = 0x3;
        break;
    case 2:
        pSelect->sw_rk_green3_en = 1;
        pSelect->sw_mindis3_rb = 0x5;
        pSelect->sw_mindis3_g = 0x5;
        pSelect->sw_dis_scale_min3 = 0x3;
        pSelect->sw_dis_scale_max3 = 0x3;

        pSelect->rg_red_blue3_enable = 0;
        pSelect->rg_green3_enable = 0;
        pSelect->rg_fac_3_rb = 0;
        pSelect->rg_fac_3_g = 0;

        pSelect->rnd_red_blue3_enable = 1;
        pSelect->rnd_green3_enable = 1;
        pSelect->rnd_thr_3_rb = 4;
        pSelect->rnd_thr_3_g = 4;
        pSelect->rnd_offs_3_rb = 2;
        pSelect->rnd_offs_3_g = 2;

        pSelect->ro_red_blue3_enable = 1;
        pSelect->ro_green3_enable = 1;
        pSelect->ro_lim_3_rb = 2;
        pSelect->ro_lim_3_g = 2;

        pSelect->lc_red_blue3_enable = 1;
        pSelect->lc_green3_enable = 0;
        pSelect->line_thr_3_rb = 0x2;
        pSelect->line_thr_3_g = 0;
        pSelect->line_mad_fac_3_rb = 0x2;
        pSelect->line_mad_fac_3_g = 0;

        pSelect->pg_red_blue3_enable = 1;
        pSelect->pg_green3_enable = 1;
        pSelect->pg_fac_3_rb = 0x3;
        pSelect->pg_fac_3_g = 0x3;
        break;
    case 3:
        pSelect->sw_rk_green3_en = 1;
        pSelect->sw_mindis3_rb = 0x5;
        pSelect->sw_mindis3_g = 0x5;
        pSelect->sw_dis_scale_min3 = 0x3;
        pSelect->sw_dis_scale_max3 = 0x3;

        pSelect->rg_red_blue3_enable = 0;
        pSelect->rg_green3_enable = 0;
        pSelect->rg_fac_3_rb = 0;
        pSelect->rg_fac_3_g = 0;

        pSelect->rnd_red_blue3_enable = 1;
        pSelect->rnd_green3_enable = 1;
        pSelect->rnd_thr_3_rb = 4;
        pSelect->rnd_thr_3_g = 4;
        pSelect->rnd_offs_3_rb = 2;
        pSelect->rnd_offs_3_g = 2;

        pSelect->ro_red_blue3_enable = 1;
        pSelect->ro_green3_enable = 1;
        pSelect->ro_lim_3_rb = 2;
        pSelect->ro_lim_3_g = 2;

        pSelect->lc_red_blue3_enable = 0;
        pSelect->lc_green3_enable = 0;
        pSelect->line_thr_3_rb = 0;
        pSelect->line_thr_3_g = 0;
        pSelect->line_mad_fac_3_rb = 0;
        pSelect->line_mad_fac_3_g = 0;

        pSelect->pg_red_blue3_enable = 1;
        pSelect->pg_green3_enable = 1;
        pSelect->pg_fac_3_rb = 0x3;
        pSelect->pg_fac_3_g = 0x3;
        break;
    case 4:
        pSelect->sw_rk_green3_en = 1;
        pSelect->sw_mindis3_rb = 0x5;
        pSelect->sw_mindis3_g = 0x5;
        pSelect->sw_dis_scale_min3 = 0x3;
        pSelect->sw_dis_scale_max3 = 0x3;

        pSelect->rg_red_blue3_enable = 0;
        pSelect->rg_green3_enable = 0;
        pSelect->rg_fac_3_rb = 0;
        pSelect->rg_fac_3_g = 0;

        pSelect->rnd_red_blue3_enable = 1;
        pSelect->rnd_green3_enable = 1;
        pSelect->rnd_thr_3_rb = 4;
        pSelect->rnd_thr_3_g = 4;
        pSelect->rnd_offs_3_rb = 2;
        pSelect->rnd_offs_3_g = 2;

        pSelect->ro_red_blue3_enable = 1;
        pSelect->ro_green3_enable = 1;
        pSelect->ro_lim_3_rb = 2;
        pSelect->ro_lim_3_g = 2;

        pSelect->lc_red_blue3_enable = 0;
        pSelect->lc_green3_enable = 0;
        pSelect->line_thr_3_rb = 0;
        pSelect->line_thr_3_g = 0;
        pSelect->line_mad_fac_3_rb = 0;
        pSelect->line_mad_fac_3_g = 0;

        pSelect->pg_red_blue3_enable = 1;
        pSelect->pg_green3_enable = 1;
        pSelect->pg_fac_3_rb = 0x2;
        pSelect->pg_fac_3_g = 0x2;
        break;
    case 5:
        pSelect->sw_rk_green3_en = 1;
        pSelect->sw_mindis3_rb = 0x5;
        pSelect->sw_mindis3_g = 0x5;
        pSelect->sw_dis_scale_min3 = 0x3;
        pSelect->sw_dis_scale_max3 = 0x3;

        pSelect->rg_red_blue3_enable = 0;
        pSelect->rg_green3_enable = 0;
        pSelect->rg_fac_3_rb = 0;
        pSelect->rg_fac_3_g = 0;

        pSelect->rnd_red_blue3_enable = 1;
        pSelect->rnd_green3_enable = 1;
        pSelect->rnd_thr_3_rb = 4;
        pSelect->rnd_thr_3_g = 4;
        pSelect->rnd_offs_3_rb = 2;
        pSelect->rnd_offs_3_g = 2;

        pSelect->ro_red_blue3_enable = 1;
        pSelect->ro_green3_enable = 1;
        pSelect->ro_lim_3_rb = 2;
        pSelect->ro_lim_3_g = 2;

        pSelect->lc_red_blue3_enable = 0;
        pSelect->lc_green3_enable = 0;
        pSelect->line_thr_3_rb = 0;
        pSelect->line_thr_3_g = 0;
        pSelect->line_mad_fac_3_rb = 0;
        pSelect->line_mad_fac_3_g = 0;

        pSelect->pg_red_blue3_enable = 0;
        pSelect->pg_green3_enable = 0;
        pSelect->pg_fac_3_rb = 0;
        pSelect->pg_fac_3_g = 0;
        break;
    case 6:
        pSelect->stage1_use_fix_set = 0x1;
        pSelect->sw_rk_red_blue3_en = 1;
        pSelect->sw_rk_green3_en = 1;
        pSelect->sw_mindis3_rb = 0x5;
        pSelect->sw_mindis3_g = 0x5;
        pSelect->sw_dis_scale_min3 = 0x3;
        pSelect->sw_dis_scale_max3 = 0x3;

        pSelect->rg_red_blue3_enable = 0;
        pSelect->rg_green3_enable = 0;
        pSelect->rg_fac_3_rb = 0;
        pSelect->rg_fac_3_g = 0;

        pSelect->rnd_red_blue3_enable = 1;
        pSelect->rnd_green3_enable = 1;
        pSelect->rnd_thr_3_rb = 4;
        pSelect->rnd_thr_3_g = 4;
        pSelect->rnd_offs_3_rb = 2;
        pSelect->rnd_offs_3_g = 2;

        pSelect->ro_red_blue3_enable = 1;
        pSelect->ro_green3_enable = 1;
        pSelect->ro_lim_3_rb = 2;
        pSelect->ro_lim_3_g = 2;

        pSelect->lc_red_blue3_enable = 0;
        pSelect->lc_green3_enable = 0;
        pSelect->line_thr_3_rb = 0;
        pSelect->line_thr_3_g = 0;
        pSelect->line_mad_fac_3_rb = 0;
        pSelect->line_mad_fac_3_g = 0;

        pSelect->pg_red_blue3_enable = 0;
        pSelect->pg_green3_enable = 0;
        pSelect->pg_fac_3_rb = 0;
        pSelect->pg_fac_3_g = 0;
        break;
    case 7:
        pSelect->stage1_use_fix_set = 0x1;
        pSelect->sw_rk_red_blue3_en = 1;
        pSelect->sw_rk_green3_en = 1;
        pSelect->sw_mindis3_rb = 0x5;
        pSelect->sw_mindis3_g = 0x5;
        pSelect->sw_dis_scale_min3 = 0x3;
        pSelect->sw_dis_scale_max3 = 0x3;

        pSelect->rg_red_blue3_enable = 0;
        pSelect->rg_green3_enable = 0;
        pSelect->rg_fac_3_rb = 0;
        pSelect->rg_fac_3_g = 0;

        pSelect->rnd_red_blue3_enable = 1;
        pSelect->rnd_green3_enable = 1;
        pSelect->rnd_thr_3_rb = 4;
        pSelect->rnd_thr_3_g = 4;
        pSelect->rnd_offs_3_rb = 2;
        pSelect->rnd_offs_3_g = 2;

        pSelect->ro_red_blue3_enable = 1;
        pSelect->ro_green3_enable = 1;
        pSelect->ro_lim_3_rb = 2;
        pSelect->ro_lim_3_g = 2;

        pSelect->lc_red_blue3_enable = 0;
        pSelect->lc_green3_enable = 0;
        pSelect->line_thr_3_rb = 0;
        pSelect->line_thr_3_g = 0;
        pSelect->line_mad_fac_3_rb = 0;
        pSelect->line_mad_fac_3_g = 0;

        pSelect->pg_red_blue3_enable = 0;
        pSelect->pg_green3_enable = 0;
        pSelect->pg_fac_3_rb = 0;
        pSelect->pg_fac_3_g = 0;
        break;
    case 8:
        pSelect->stage1_use_fix_set = 0x1;
        pSelect->sw_rk_red_blue3_en = 1;
        pSelect->sw_rk_green3_en = 1;
        pSelect->sw_mindis3_rb = 0x3;
        pSelect->sw_mindis3_g = 0x3;
        pSelect->sw_dis_scale_min3 = 0x2;
        pSelect->sw_dis_scale_max3 = 0x2;

        pSelect->rg_red_blue3_enable = 0;
        pSelect->rg_green3_enable = 0;
        pSelect->rg_fac_3_rb = 0;
        pSelect->rg_fac_3_g = 0;

        pSelect->rnd_red_blue3_enable = 1;
        pSelect->rnd_green3_enable = 1;
        pSelect->rnd_thr_3_rb = 0x4;
        pSelect->rnd_thr_3_g = 0x4;
        pSelect->rnd_offs_3_rb = 0x2;
        pSelect->rnd_offs_3_g = 0x2;

        pSelect->ro_red_blue3_enable = 1;
        pSelect->ro_green3_enable = 1;
        pSelect->ro_lim_3_rb = 0x2;
        pSelect->ro_lim_3_g = 0x2;

        pSelect->lc_red_blue3_enable = 0;
        pSelect->lc_green3_enable = 0;
        pSelect->line_thr_3_rb = 0;
        pSelect->line_thr_3_g = 0;
        pSelect->line_mad_fac_3_rb = 0;
        pSelect->line_mad_fac_3_g = 0;

        pSelect->pg_red_blue3_enable = 0;
        pSelect->pg_green3_enable = 0;
        pSelect->pg_fac_3_rb = 0;
        pSelect->pg_fac_3_g = 0;
        break;
    case 9:
        pSelect->stage1_use_fix_set = 0x1;
        pSelect->sw_rk_red_blue3_en = 0;
        pSelect->sw_rk_green3_en = 0;
        pSelect->sw_mindis3_rb = 0;
        pSelect->sw_mindis3_g = 0;
        pSelect->sw_dis_scale_min3 = 0;
        pSelect->sw_dis_scale_max3 = 0;

        pSelect->rg_red_blue3_enable = 0;
        pSelect->rg_green3_enable = 0;
        pSelect->rg_fac_3_rb = 0;
        pSelect->rg_fac_3_g = 0;

        pSelect->rnd_red_blue3_enable = 1;
        pSelect->rnd_green3_enable = 1;
        pSelect->rnd_thr_3_rb = 0x4;
        pSelect->rnd_thr_3_g = 0x4;
        pSelect->rnd_offs_3_rb = 0x2;
        pSelect->rnd_offs_3_g = 0x2;

        pSelect->ro_red_blue3_enable = 1;
        pSelect->ro_green3_enable = 1;
        pSelect->ro_lim_3_rb = 0x2;
        pSelect->ro_lim_3_g = 0x2;

        pSelect->lc_red_blue3_enable = 0;
        pSelect->lc_green3_enable = 0;
        pSelect->line_thr_3_rb = 0;
        pSelect->line_thr_3_g = 0;
        pSelect->line_mad_fac_3_rb = 0;
        pSelect->line_mad_fac_3_g = 0;

        pSelect->pg_red_blue3_enable = 0;
        pSelect->pg_green3_enable = 0;
        pSelect->pg_fac_3_rb = 0;
        pSelect->pg_fac_3_g = 0;
        break;
    case 10:
        pSelect->stage1_use_fix_set = 0x1;
        pSelect->sw_rk_red_blue3_en = 0;
        pSelect->sw_rk_green3_en = 0;
        pSelect->sw_mindis3_rb = 0;
        pSelect->sw_mindis3_g = 0;
        pSelect->sw_dis_scale_min3 = 0;
        pSelect->sw_dis_scale_max3 = 0;

        pSelect->rg_red_blue3_enable = 0;
        pSelect->rg_green3_enable = 0;
        pSelect->rg_fac_3_rb = 0;
        pSelect->rg_fac_3_g = 0;

        pSelect->rnd_red_blue3_enable = 1;
        pSelect->rnd_green3_enable = 1;
        pSelect->rnd_thr_3_rb = 0x3;
        pSelect->rnd_thr_3_g = 0x3;
        pSelect->rnd_offs_3_rb = 0x1;
        pSelect->rnd_offs_3_g = 0x1;

        pSelect->ro_red_blue3_enable = 1;
        pSelect->ro_green3_enable = 1;
        pSelect->ro_lim_3_rb = 0x2;
        pSelect->ro_lim_3_g = 0x1;

        pSelect->lc_red_blue3_enable = 0;
        pSelect->lc_green3_enable = 0;
        pSelect->line_thr_3_rb = 0;
        pSelect->line_thr_3_g = 0;
        pSelect->line_mad_fac_3_rb = 0;
        pSelect->line_mad_fac_3_g = 0;

        pSelect->pg_red_blue3_enable = 0;
        pSelect->pg_green3_enable = 0;
        pSelect->pg_fac_3_rb = 0;
        pSelect->pg_fac_3_g = 0;
        break;
    default:
        LOGE_ADPCC("%s(%d): Wrong fast mode level!!!\n", __FUNCTION__, __LINE__);
        break;
    }

    LOGI_ADPCC("%s(%d): exit!\n", __FUNCTION__, __LINE__);

}

void Fast_mode_Double_Setting(
    AdpccContext_t *pParams,
    Adpcc_basic_params_select_t *pSelect,
    int iso)
{
    LOGI_ADPCC("%s(%d): enter!\n", __FUNCTION__, __LINE__);

    int level = 1;
    for(int i = 0; i < DPCC_MAX_ISO_LEVEL - 1; i++) {
        if(iso >= pParams->fast.ISO[i] && iso <= pParams->fast.ISO[i + 1]) {
            level = (pParams->fast.fast_mode_double_level[i] - pParams->fast.fast_mode_double_level[i + 1])
                    / (pParams->fast.ISO[i] - pParams->fast.ISO[i + 1]);
            level += pParams->fast.fast_mode_double_level[i];
            break;
        }
    }

    if(iso < pParams->fast.ISO[0] ) {
        level = pParams->fast.fast_mode_double_level[0];
    }

    if(iso > pParams->fast.ISO[DPCC_MAX_ISO_LEVEL - 1] ) {
        level = pParams->fast.fast_mode_double_level[DPCC_MAX_ISO_LEVEL - 1];
    }

    if(pParams->fast.fast_mode_double_en != 0)
        pSelect->stage1_use_set_2 = 0x1;
    else
        pSelect->stage1_use_set_2 = 0x0;

    switch (level)
    {
    case 1:
        pSelect->sw_rk_red_blue2_en = 1;
        pSelect->sw_rk_green2_en = 1;
        pSelect->sw_mindis2_rb = 0x15;
        pSelect->sw_mindis2_g = 0x20;
        pSelect->sw_dis_scale_min2 = 0x10;
        pSelect->sw_dis_scale_max2 = 0x12;

        pSelect->rg_red_blue2_enable = 1;
        pSelect->rg_green2_enable = 1;
        pSelect->rg_fac_2_rb = 0x15;
        pSelect->rg_fac_2_g = 0x20;

        pSelect->rnd_red_blue2_enable = 1;
        pSelect->rnd_green2_enable = 1;
        pSelect->rnd_thr_2_rb = 0x9;
        pSelect->rnd_thr_2_g = 0xa;
        pSelect->rnd_offs_2_rb = 0x1;
        pSelect->rnd_offs_2_g = 0x1;

        pSelect->ro_red_blue2_enable = 1;
        pSelect->ro_green2_enable = 1;
        pSelect->ro_lim_2_rb = 0x1;
        pSelect->ro_lim_2_g = 0x2;

        pSelect->lc_red_blue2_enable = 1;
        pSelect->lc_green2_enable = 1;
        pSelect->line_thr_2_rb = 0x6;
        pSelect->line_thr_2_g = 0x8;
        pSelect->line_mad_fac_2_rb = 0x3;
        pSelect->line_mad_fac_2_g = 0x4;

        pSelect->pg_red_blue2_enable = 1;
        pSelect->pg_green1_enable = 1;
        pSelect->pg_fac_2_rb = 0x6;
        pSelect->pg_fac_2_g = 0x8;
        break;
    case 2:
        pSelect->sw_rk_red_blue2_en = 1;
        pSelect->sw_rk_green2_en = 1;
        pSelect->sw_mindis2_rb = 0x12;
        pSelect->sw_mindis2_g = 0x16;
        pSelect->sw_dis_scale_min2 = 0x6;
        pSelect->sw_dis_scale_max2 = 0x8;

        pSelect->rg_red_blue2_enable = 1;
        pSelect->rg_green2_enable = 1;
        pSelect->rg_fac_2_rb = 0x7;
        pSelect->rg_fac_2_g = 0x10;

        pSelect->rnd_red_blue2_enable = 1;
        pSelect->rnd_green2_enable = 1;
        pSelect->rnd_thr_2_rb = 0x5;
        pSelect->rnd_thr_2_g = 0x6;
        pSelect->rnd_offs_2_rb = 0x1;
        pSelect->rnd_offs_2_g = 0x1;

        pSelect->ro_red_blue2_enable = 1;
        pSelect->ro_green2_enable = 1;
        pSelect->ro_lim_2_rb = 0x3;
        pSelect->ro_lim_2_g = 0x2;

        pSelect->lc_red_blue2_enable = 1;
        pSelect->lc_green2_enable = 1;
        pSelect->line_thr_2_rb = 0x12;
        pSelect->line_thr_2_g = 0x16;
        pSelect->line_mad_fac_2_rb = 0x8;
        pSelect->line_mad_fac_2_g = 0x10;

        pSelect->pg_red_blue2_enable = 1;
        pSelect->pg_green2_enable = 1;
        pSelect->pg_fac_2_rb = 0x5;
        pSelect->pg_fac_2_g = 0x6;
        break;
    case 3:
        pSelect->sw_rk_red_blue2_en = 1;
        pSelect->sw_rk_green2_en = 1;
        pSelect->sw_mindis2_rb = 0x12;
        pSelect->sw_mindis2_g = 0x16;
        pSelect->sw_dis_scale_min2 = 0x6;
        pSelect->sw_dis_scale_max2 = 0x8;

        pSelect->rg_red_blue2_enable = 0;
        pSelect->rg_green2_enable = 0;
        pSelect->rg_fac_2_rb = 0;
        pSelect->rg_fac_2_g = 0;

        pSelect->rnd_red_blue2_enable = 1;
        pSelect->rnd_green2_enable = 1;
        pSelect->rnd_thr_2_rb = 0x5;
        pSelect->rnd_thr_2_g = 0x6;
        pSelect->rnd_offs_2_rb = 0x1;
        pSelect->rnd_offs_2_g = 0x1;

        pSelect->ro_red_blue2_enable = 1;
        pSelect->ro_green2_enable = 1;
        pSelect->ro_lim_2_rb = 0x3;
        pSelect->ro_lim_2_g = 0x2;

        pSelect->lc_red_blue2_enable = 1;
        pSelect->lc_green2_enable = 1;
        pSelect->line_thr_2_rb = 0x12;
        pSelect->line_thr_2_g = 0x16;
        pSelect->line_mad_fac_2_rb = 0x8;
        pSelect->line_mad_fac_2_g = 0x10;

        pSelect->pg_red_blue2_enable = 1;
        pSelect->pg_green2_enable = 1;
        pSelect->pg_fac_2_rb = 0x5;
        pSelect->pg_fac_2_g = 0x6;
        break;
    case 4:
        pSelect->sw_rk_red_blue2_en = 1;
        pSelect->sw_rk_green2_en = 1;
        pSelect->sw_mindis2_rb = 0x12;
        pSelect->sw_mindis2_g = 0x16;
        pSelect->sw_dis_scale_min2 = 0x6;
        pSelect->sw_dis_scale_max2 = 0x8;

        pSelect->rg_red_blue2_enable = 0;
        pSelect->rg_green2_enable = 0;
        pSelect->rg_fac_2_rb = 0;
        pSelect->rg_fac_2_g = 0;

        pSelect->rnd_red_blue2_enable = 0;
        pSelect->rnd_green2_enable = 0;
        pSelect->rnd_thr_2_rb = 0;
        pSelect->rnd_thr_2_g = 0;
        pSelect->rnd_offs_2_rb = 0;
        pSelect->rnd_offs_2_g = 0;

        pSelect->ro_red_blue2_enable = 1;
        pSelect->ro_green2_enable = 1;
        pSelect->ro_lim_2_rb = 0x3;
        pSelect->ro_lim_2_g = 0x2;

        pSelect->lc_red_blue2_enable = 1;
        pSelect->lc_green2_enable = 1;
        pSelect->line_thr_2_rb = 0x12;
        pSelect->line_thr_2_g = 0x16;
        pSelect->line_mad_fac_2_rb = 0x8;
        pSelect->line_mad_fac_2_g = 0x10;

        pSelect->pg_red_blue2_enable = 1;
        pSelect->pg_green2_enable = 1;
        pSelect->pg_fac_2_rb = 0x5;
        pSelect->pg_fac_2_g = 0x6;
        break;
    case 5:
        pSelect->sw_rk_red_blue2_en = 1;
        pSelect->sw_rk_green2_en = 1;
        pSelect->sw_mindis2_rb = 0x10;
        pSelect->sw_mindis2_g = 0x14;
        pSelect->sw_dis_scale_min2 = 0x6;
        pSelect->sw_dis_scale_max2 = 0xc;

        pSelect->rg_red_blue2_enable = 0;
        pSelect->rg_green2_enable = 0;
        pSelect->rg_fac_2_rb = 0;
        pSelect->rg_fac_2_g = 0;

        pSelect->rnd_red_blue2_enable = 0;
        pSelect->rnd_green2_enable = 0;
        pSelect->rnd_thr_2_rb = 0;
        pSelect->rnd_thr_2_g = 0;
        pSelect->rnd_offs_2_rb = 0;
        pSelect->rnd_offs_2_g = 0;

        pSelect->ro_red_blue2_enable = 1;
        pSelect->ro_green2_enable = 1;
        pSelect->ro_lim_2_rb = 0x3;
        pSelect->ro_lim_2_g = 0x3;

        pSelect->lc_red_blue2_enable = 1;
        pSelect->lc_green2_enable = 1;
        pSelect->line_thr_2_rb = 0x7;
        pSelect->line_thr_2_g = 0xc;
        pSelect->line_mad_fac_2_rb = 0x7;
        pSelect->line_mad_fac_2_g = 0x9;

        pSelect->pg_red_blue2_enable = 1;
        pSelect->pg_green2_enable = 1;
        pSelect->pg_fac_2_rb = 0x3;
        pSelect->pg_fac_2_g = 0x4;
        break;
    case 6:
        pSelect->sw_rk_red_blue2_en = 1;
        pSelect->sw_rk_green2_en = 1;
        pSelect->sw_mindis2_rb = 0x7;
        pSelect->sw_mindis2_g = 0x10;
        pSelect->sw_dis_scale_min2 = 0x6;
        pSelect->sw_dis_scale_max2 = 0x8;

        pSelect->rg_red_blue2_enable = 0;
        pSelect->rg_green2_enable = 0;
        pSelect->rg_fac_2_rb = 0;
        pSelect->rg_fac_2_g = 0;

        pSelect->rnd_red_blue2_enable = 0;
        pSelect->rnd_green2_enable = 0;
        pSelect->rnd_thr_2_rb = 0;
        pSelect->rnd_thr_2_g = 0;
        pSelect->rnd_offs_2_rb = 0;
        pSelect->rnd_offs_2_g = 0;

        pSelect->ro_red_blue2_enable = 1;
        pSelect->ro_green2_enable = 1;
        pSelect->ro_lim_2_rb = 0x3;
        pSelect->ro_lim_2_g = 0x3;

        pSelect->lc_red_blue2_enable = 1;
        pSelect->lc_green2_enable = 1;
        pSelect->line_thr_2_rb = 0x7;
        pSelect->line_thr_2_g = 0x9;
        pSelect->line_mad_fac_2_rb = 0x5;
        pSelect->line_mad_fac_2_g = 0x7;

        pSelect->pg_red_blue2_enable = 1;
        pSelect->pg_green2_enable = 1;
        pSelect->pg_fac_2_rb = 0x3;
        pSelect->pg_fac_2_g = 0x4;
        break;
    case 7:
        pSelect->sw_rk_red_blue2_en = 1;
        pSelect->sw_rk_green2_en = 1;
        pSelect->sw_mindis2_rb = 0x5;
        pSelect->sw_mindis2_g = 0x8;
        pSelect->sw_dis_scale_min2 = 0x3;
        pSelect->sw_dis_scale_max2 = 0x6;

        pSelect->rg_red_blue2_enable = 0;
        pSelect->rg_green2_enable = 0;
        pSelect->rg_fac_2_rb = 0;
        pSelect->rg_fac_2_g = 0;

        pSelect->rnd_red_blue2_enable = 0;
        pSelect->rnd_green2_enable = 0;
        pSelect->rnd_thr_2_rb = 0;
        pSelect->rnd_thr_2_g = 0;
        pSelect->rnd_offs_2_rb = 0;
        pSelect->rnd_offs_2_g = 0;

        pSelect->ro_red_blue2_enable = 1;
        pSelect->ro_green2_enable = 1;
        pSelect->ro_lim_2_rb = 0x4;
        pSelect->ro_lim_2_g = 0x3;

        pSelect->lc_red_blue2_enable = 1;
        pSelect->lc_green2_enable = 1;
        pSelect->line_thr_2_rb = 0x5;
        pSelect->line_thr_2_g = 0x7;
        pSelect->line_mad_fac_2_rb = 0x3;
        pSelect->line_mad_fac_2_g = 0x5;

        pSelect->pg_red_blue2_enable = 1;
        pSelect->pg_green2_enable = 1;
        pSelect->pg_fac_2_rb = 0x2;
        pSelect->pg_fac_2_g = 0x1;
        break;
    case 8:
        pSelect->sw_rk_red_blue2_en = 1;
        pSelect->sw_rk_green2_en = 1;
        pSelect->sw_mindis2_rb = 0x5;
        pSelect->sw_mindis2_g = 0x8;
        pSelect->sw_dis_scale_min2 = 0x3;
        pSelect->sw_dis_scale_max2 = 0x6;

        pSelect->rg_red_blue2_enable = 0;
        pSelect->rg_green2_enable = 0;
        pSelect->rg_fac_2_rb = 0;
        pSelect->rg_fac_2_g = 0;

        pSelect->rnd_red_blue2_enable = 0;
        pSelect->rnd_green2_enable = 0;
        pSelect->rnd_thr_2_rb = 0;
        pSelect->rnd_thr_2_g = 0;
        pSelect->rnd_offs_2_rb = 0;
        pSelect->rnd_offs_2_g = 0;

        pSelect->ro_red_blue2_enable = 1;
        pSelect->ro_green2_enable = 1;
        pSelect->ro_lim_2_rb = 0x1;
        pSelect->ro_lim_2_g = 0x3;

        pSelect->lc_red_blue2_enable = 1;
        pSelect->lc_green2_enable = 1;
        pSelect->line_thr_2_rb = 0x5;
        pSelect->line_thr_2_g = 0x7;
        pSelect->line_mad_fac_2_rb = 0x3;
        pSelect->line_mad_fac_2_g = 0x5;

        pSelect->pg_red_blue2_enable = 0;
        pSelect->pg_green2_enable = 0;
        pSelect->pg_fac_2_rb = 0;
        pSelect->pg_fac_2_g = 0;
        break;
    case 9:
        pSelect->sw_rk_red_blue2_en = 1;
        pSelect->sw_rk_green2_en = 1;
        pSelect->sw_mindis2_rb = 0x4;
        pSelect->sw_mindis2_g = 0x8;
        pSelect->sw_dis_scale_min2 = 0x2;
        pSelect->sw_dis_scale_max2 = 0x6;

        pSelect->rg_red_blue2_enable = 0;
        pSelect->rg_green2_enable = 0;
        pSelect->rg_fac_2_rb = 0;
        pSelect->rg_fac_2_g = 0;

        pSelect->rnd_red_blue2_enable = 0;
        pSelect->rnd_green2_enable = 0;
        pSelect->rnd_thr_2_rb = 0;
        pSelect->rnd_thr_2_g = 0;
        pSelect->rnd_offs_2_rb = 0;
        pSelect->rnd_offs_2_g = 0;

        pSelect->ro_red_blue2_enable = 1;
        pSelect->ro_green2_enable = 1;
        pSelect->ro_lim_2_rb = 0x4;
        pSelect->ro_lim_2_g = 0x3;

        pSelect->lc_red_blue2_enable = 1;
        pSelect->lc_green2_enable = 1;
        pSelect->line_thr_2_rb = 0x1;
        pSelect->line_thr_2_g = 0x3;
        pSelect->line_mad_fac_2_rb = 0x2;
        pSelect->line_mad_fac_2_g = 0x2;

        pSelect->pg_red_blue2_enable = 0;
        pSelect->pg_green2_enable = 0;
        pSelect->pg_fac_2_rb = 0;
        pSelect->pg_fac_2_g = 0;
        break;
    case 10:
        pSelect->sw_rk_red_blue2_en = 1;
        pSelect->sw_rk_green2_en = 1;
        pSelect->sw_mindis2_rb = 0x4;
        pSelect->sw_mindis2_g = 0x8;
        pSelect->sw_dis_scale_min2 = 0x3;
        pSelect->sw_dis_scale_max2 = 0x6;

        pSelect->rg_red_blue2_enable = 0;
        pSelect->rg_green2_enable = 0;
        pSelect->rg_fac_2_rb = 0;
        pSelect->rg_fac_2_g = 0;

        pSelect->rnd_red_blue2_enable = 0;
        pSelect->rnd_green2_enable = 0;
        pSelect->rnd_thr_2_rb = 0;
        pSelect->rnd_thr_2_g = 0;
        pSelect->rnd_offs_2_rb = 0;
        pSelect->rnd_offs_2_g = 0;

        pSelect->ro_red_blue2_enable = 1;
        pSelect->ro_green2_enable = 1;
        pSelect->ro_lim_2_rb = 0x4;
        pSelect->ro_lim_2_g = 0x3;

        pSelect->lc_red_blue2_enable = 0;
        pSelect->lc_green2_enable = 0;
        pSelect->line_thr_2_rb = 0;
        pSelect->line_thr_2_g = 0;
        pSelect->line_mad_fac_2_rb = 0;
        pSelect->line_mad_fac_2_g = 0;

        pSelect->pg_red_blue2_enable = 0;
        pSelect->pg_green2_enable = 0;
        pSelect->pg_fac_2_rb = 0;
        pSelect->pg_fac_2_g = 0;
        break;
    default:
        LOGE_ADPCC("%s(%d): Wrong fast mode level!!!\n", __FUNCTION__, __LINE__);
        break;
    }


    LOGI_ADPCC("%s(%d): exit!\n", __FUNCTION__, __LINE__);

}

void Fast_mode_Single_Setting(
    AdpccContext_t *pParams,
    Adpcc_basic_params_select_t *pSelect,
    int iso)
{
    LOG1_ADPCC("%s(%d): enter!\n", __FUNCTION__, __LINE__);

    int level = 1;
    for(int i = 0; i < DPCC_MAX_ISO_LEVEL - 1; i++) {
        if(iso >= pParams->fast.ISO[i] && iso <= pParams->fast.ISO[i + 1]) {
            level = (pParams->fast.fast_mode_single_level[i] - pParams->fast.fast_mode_single_level[i + 1])
                    / (pParams->fast.ISO[i] - pParams->fast.ISO[i + 1]);
            level += pParams->fast.fast_mode_single_level[i];
            break;
        }
    }

    if(iso < pParams->fast.ISO[0] ) {
        level = pParams->fast.fast_mode_single_level[0];
    }

    if(iso > pParams->fast.ISO[DPCC_MAX_ISO_LEVEL - 1] ) {
        level = pParams->fast.fast_mode_single_level[DPCC_MAX_ISO_LEVEL - 1];
    }

    if(pParams->fast.fast_mode_single_en != 0)
        pSelect->stage1_use_set_1 = 0x1;
    else
        pSelect->stage1_use_set_1 = 0x0;


    switch (level)
    {
    case 1:
        pSelect->sw_rk_red_blue1_en = 1;
        pSelect->sw_rk_green1_en = 1;
        pSelect->sw_mindis1_rb = 0x20;
        pSelect->sw_mindis1_g = 0x20;
        pSelect->sw_dis_scale_min1 = 0x12;
        pSelect->sw_dis_scale_max1 = 0x12;

        pSelect->rg_red_blue1_enable = 1;
        pSelect->rg_green1_enable = 1;
        pSelect->rg_fac_1_rb = 0x20;
        pSelect->rg_fac_1_g = 0x20;

        pSelect->rnd_red_blue1_enable = 1;
        pSelect->rnd_green1_enable = 1;
        pSelect->rnd_thr_1_rb = 0xa;
        pSelect->rnd_thr_1_g = 0xa;
        pSelect->rnd_offs_1_rb = 0x1;
        pSelect->rnd_offs_1_g = 0x1;

        pSelect->ro_red_blue1_enable = 1;
        pSelect->ro_green1_enable = 1;
        pSelect->ro_lim_1_rb = 0x2;
        pSelect->ro_lim_1_g = 0x2;

        pSelect->lc_red_blue1_enable = 1;
        pSelect->lc_green1_enable = 1;
        pSelect->line_thr_1_rb = 0x8;
        pSelect->line_thr_1_g = 0x8;
        pSelect->line_mad_fac_1_rb = 0x4;
        pSelect->line_mad_fac_1_g = 0x4;

        pSelect->pg_red_blue1_enable = 1;
        pSelect->pg_green1_enable = 1;
        pSelect->pg_fac_1_rb = 0x8;
        pSelect->pg_fac_1_g = 0x8;
        break;
    case 2:
        pSelect->sw_rk_red_blue1_en = 1;
        pSelect->sw_rk_green1_en = 1;
        pSelect->sw_mindis1_rb = 0x16;
        pSelect->sw_mindis1_g = 0x16;
        pSelect->sw_dis_scale_min1 = 0x8;
        pSelect->sw_dis_scale_max1 = 0x8;

        pSelect->rg_red_blue1_enable = 1;
        pSelect->rg_green1_enable = 1;
        pSelect->rg_fac_1_rb = 0x10;
        pSelect->rg_fac_1_g = 0x10;

        pSelect->rnd_red_blue1_enable = 1;
        pSelect->rnd_green1_enable = 1;
        pSelect->rnd_thr_1_rb = 0x6;
        pSelect->rnd_thr_1_g = 0x6;
        pSelect->rnd_offs_1_rb = 0x1;
        pSelect->rnd_offs_1_g = 0x1;

        pSelect->ro_red_blue1_enable = 1;
        pSelect->ro_green1_enable = 1;
        pSelect->ro_lim_1_rb = 0x2;
        pSelect->ro_lim_1_g = 0x2;

        pSelect->lc_red_blue1_enable = 1;
        pSelect->lc_green1_enable = 1;
        pSelect->line_thr_1_rb = 0x16;
        pSelect->line_thr_1_g = 0x16;
        pSelect->line_mad_fac_1_rb = 0x10;
        pSelect->line_mad_fac_1_g = 0x10;

        pSelect->pg_red_blue1_enable = 1;
        pSelect->pg_green1_enable = 1;
        pSelect->pg_fac_1_rb = 0x6;
        pSelect->pg_fac_1_g = 0x6;
        break;
    case 3:
        pSelect->sw_rk_red_blue1_en = 1;
        pSelect->sw_rk_green1_en = 1;
        pSelect->sw_mindis1_rb = 0x16;
        pSelect->sw_mindis1_g = 0x16;
        pSelect->sw_dis_scale_min1 = 0x8;
        pSelect->sw_dis_scale_max1 = 0x8;

        pSelect->rg_red_blue1_enable = 0;
        pSelect->rg_green1_enable = 0;
        pSelect->rg_fac_1_rb = 0;
        pSelect->rg_fac_1_g = 0;

        pSelect->rnd_red_blue1_enable = 1;
        pSelect->rnd_green1_enable = 1;
        pSelect->rnd_thr_1_rb = 0x6;
        pSelect->rnd_thr_1_g = 0x6;
        pSelect->rnd_offs_1_rb = 0x1;
        pSelect->rnd_offs_1_g = 0x1;

        pSelect->ro_red_blue1_enable = 1;
        pSelect->ro_green1_enable = 1;
        pSelect->ro_lim_1_rb = 0x2;
        pSelect->ro_lim_1_g = 0x2;

        pSelect->lc_red_blue1_enable = 1;
        pSelect->lc_green1_enable = 1;
        pSelect->line_thr_1_rb = 0x16;
        pSelect->line_thr_1_g = 0x16;
        pSelect->line_mad_fac_1_rb = 0x10;
        pSelect->line_mad_fac_1_g = 0x10;

        pSelect->pg_red_blue1_enable = 1;
        pSelect->pg_green1_enable = 1;
        pSelect->pg_fac_1_rb = 0x6;
        pSelect->pg_fac_1_g = 0x6;
        break;
    case 4:
        pSelect->sw_rk_red_blue1_en = 1;
        pSelect->sw_rk_green1_en = 1;
        pSelect->sw_mindis1_rb = 0x16;
        pSelect->sw_mindis1_g = 0x16;
        pSelect->sw_dis_scale_min1 = 0x8;
        pSelect->sw_dis_scale_max1 = 0x8;

        pSelect->rg_red_blue1_enable = 0;
        pSelect->rg_green1_enable = 0;
        pSelect->rg_fac_1_rb = 0;
        pSelect->rg_fac_1_g = 0;

        pSelect->rnd_red_blue1_enable = 0;
        pSelect->rnd_green1_enable = 0;
        pSelect->rnd_thr_1_rb = 0;
        pSelect->rnd_thr_1_g = 0;
        pSelect->rnd_offs_1_rb = 0;
        pSelect->rnd_offs_1_g = 0;

        pSelect->ro_red_blue1_enable = 1;
        pSelect->ro_green1_enable = 1;
        pSelect->ro_lim_1_rb = 0x2;
        pSelect->ro_lim_1_g = 0x2;

        pSelect->lc_red_blue1_enable = 1;
        pSelect->lc_green1_enable = 1;
        pSelect->line_thr_1_rb = 0x16;
        pSelect->line_thr_1_g = 0x16;
        pSelect->line_mad_fac_1_rb = 0x10;
        pSelect->line_mad_fac_1_g = 0x10;

        pSelect->pg_red_blue1_enable = 1;
        pSelect->pg_green1_enable = 1;
        pSelect->pg_fac_1_rb = 0x6;
        pSelect->pg_fac_1_g = 0x6;
        break;
    case 5:
        pSelect->sw_rk_red_blue1_en = 1;
        pSelect->sw_rk_green1_en = 1;
        pSelect->sw_mindis1_rb = 0x14;
        pSelect->sw_mindis1_g = 0x14;
        pSelect->sw_dis_scale_min1 = 0xc;
        pSelect->sw_dis_scale_max1 = 0xc;

        pSelect->rg_red_blue1_enable = 0;
        pSelect->rg_green1_enable = 0;
        pSelect->rg_fac_1_rb = 0;
        pSelect->rg_fac_1_g = 0;

        pSelect->rnd_red_blue1_enable = 0;
        pSelect->rnd_green1_enable = 0;
        pSelect->rnd_thr_1_rb = 0;
        pSelect->rnd_thr_1_g = 0;
        pSelect->rnd_offs_1_rb = 0;
        pSelect->rnd_offs_1_g = 0;

        pSelect->ro_red_blue1_enable = 1;
        pSelect->ro_green1_enable = 1;
        pSelect->ro_lim_1_rb = 0x3;
        pSelect->ro_lim_1_g = 0x3;

        pSelect->lc_red_blue1_enable = 1;
        pSelect->lc_green1_enable = 1;
        pSelect->line_thr_1_rb = 0xc;
        pSelect->line_thr_1_g = 0xc;
        pSelect->line_mad_fac_1_rb = 0x9;
        pSelect->line_mad_fac_1_g = 0x9;

        pSelect->pg_red_blue1_enable = 1;
        pSelect->pg_green1_enable = 1;
        pSelect->pg_fac_1_rb = 0x5;
        pSelect->pg_fac_1_g = 0x4;
        break;
    case 6:
        pSelect->sw_rk_red_blue1_en = 1;
        pSelect->sw_rk_green1_en = 1;
        pSelect->sw_mindis1_rb = 0x10;
        pSelect->sw_mindis1_g = 0x10;
        pSelect->sw_dis_scale_min1 = 0x8;
        pSelect->sw_dis_scale_max1 = 0x8;

        pSelect->rg_red_blue1_enable = 0;
        pSelect->rg_green1_enable = 0;
        pSelect->rg_fac_1_rb = 0;
        pSelect->rg_fac_1_g = 0;

        pSelect->rnd_red_blue1_enable = 0;
        pSelect->rnd_green1_enable = 0;
        pSelect->rnd_thr_1_rb = 0;
        pSelect->rnd_thr_1_g = 0;
        pSelect->rnd_offs_1_rb = 0;
        pSelect->rnd_offs_1_g = 0;

        pSelect->ro_red_blue1_enable = 1;
        pSelect->ro_green1_enable = 1;
        pSelect->ro_lim_1_rb = 0x3;
        pSelect->ro_lim_1_g = 0x3;

        pSelect->lc_red_blue1_enable = 1;
        pSelect->lc_green1_enable = 1;
        pSelect->line_thr_1_rb = 0x9;
        pSelect->line_thr_1_g = 0x9;
        pSelect->line_mad_fac_1_rb = 0x7;
        pSelect->line_mad_fac_1_g = 0x7;

        pSelect->pg_red_blue1_enable = 1;
        pSelect->pg_green1_enable = 1;
        pSelect->pg_fac_1_rb = 0x5;
        pSelect->pg_fac_1_g = 0x4;
        break;
    case 7:
        pSelect->sw_rk_red_blue1_en = 1;
        pSelect->sw_rk_green1_en = 1;
        pSelect->sw_mindis1_rb = 0x8;
        pSelect->sw_mindis1_g = 0x8;
        pSelect->sw_dis_scale_min1 = 0x6;
        pSelect->sw_dis_scale_max1 = 0x6;

        pSelect->rg_red_blue1_enable = 0;
        pSelect->rg_green1_enable = 0;
        pSelect->rg_fac_1_rb = 0;
        pSelect->rg_fac_1_g = 0;

        pSelect->rnd_red_blue1_enable = 0;
        pSelect->rnd_green1_enable = 0;
        pSelect->rnd_thr_1_rb = 0;
        pSelect->rnd_thr_1_g = 0;
        pSelect->rnd_offs_1_rb = 0;
        pSelect->rnd_offs_1_g = 0;

        pSelect->ro_red_blue1_enable = 1;
        pSelect->ro_green1_enable = 1;
        pSelect->ro_lim_1_rb = 0x3;
        pSelect->ro_lim_1_g = 0x3;

        pSelect->lc_red_blue1_enable = 1;
        pSelect->lc_green1_enable = 1;
        pSelect->line_thr_1_rb = 0x7;
        pSelect->line_thr_1_g = 0x7;
        pSelect->line_mad_fac_1_rb = 0x5;
        pSelect->line_mad_fac_1_g = 0x5;

        pSelect->pg_red_blue1_enable = 1;
        pSelect->pg_green1_enable = 1;
        pSelect->pg_fac_1_rb = 0x3;
        pSelect->pg_fac_1_g = 0x1;
        break;
    case 8:
        pSelect->sw_rk_red_blue1_en = 1;
        pSelect->sw_rk_green1_en = 1;
        pSelect->sw_mindis1_rb = 0x8;
        pSelect->sw_mindis1_g = 0x8;
        pSelect->sw_dis_scale_min1 = 0x6;
        pSelect->sw_dis_scale_max1 = 0x6;

        pSelect->rg_red_blue1_enable = 0;
        pSelect->rg_green1_enable = 0;
        pSelect->rg_fac_1_rb = 0;
        pSelect->rg_fac_1_g = 0;

        pSelect->rnd_red_blue1_enable = 0;
        pSelect->rnd_green1_enable = 0;
        pSelect->rnd_thr_1_rb = 0;
        pSelect->rnd_thr_1_g = 0;
        pSelect->rnd_offs_1_rb = 0;
        pSelect->rnd_offs_1_g = 0;

        pSelect->ro_red_blue1_enable = 1;
        pSelect->ro_green1_enable = 1;
        pSelect->ro_lim_1_rb = 0x3;
        pSelect->ro_lim_1_g = 0x3;

        pSelect->lc_red_blue1_enable = 1;
        pSelect->lc_green1_enable = 1;
        pSelect->line_thr_1_rb = 0x7;
        pSelect->line_thr_1_g = 0x7;
        pSelect->line_mad_fac_1_rb = 0x5;
        pSelect->line_mad_fac_1_g = 0x5;

        pSelect->pg_red_blue1_enable = 0;
        pSelect->pg_green1_enable = 0;
        pSelect->pg_fac_1_rb = 0;
        pSelect->pg_fac_1_g = 0;
        break;
    case 9:
        pSelect->sw_rk_red_blue1_en = 1;
        pSelect->sw_rk_green1_en = 1;
        pSelect->sw_mindis1_rb = 0x8;
        pSelect->sw_mindis1_g = 0x8;
        pSelect->sw_dis_scale_min1 = 0x6;
        pSelect->sw_dis_scale_max1 = 0x6;

        pSelect->rg_red_blue1_enable = 0;
        pSelect->rg_green1_enable = 0;
        pSelect->rg_fac_1_rb = 0;
        pSelect->rg_fac_1_g = 0;

        pSelect->rnd_red_blue1_enable = 0;
        pSelect->rnd_green1_enable = 0;
        pSelect->rnd_thr_1_rb = 0;
        pSelect->rnd_thr_1_g = 0;
        pSelect->rnd_offs_1_rb = 0;
        pSelect->rnd_offs_1_g = 0;

        pSelect->ro_red_blue1_enable = 1;
        pSelect->ro_green1_enable = 1;
        pSelect->ro_lim_1_rb = 0x3;
        pSelect->ro_lim_1_g = 0x3;

        pSelect->lc_red_blue1_enable = 1;
        pSelect->lc_green1_enable = 1;
        pSelect->line_thr_1_rb = 0x3;
        pSelect->line_thr_1_g = 0x3;
        pSelect->line_mad_fac_1_rb = 0x2;
        pSelect->line_mad_fac_1_g = 0x2;

        pSelect->pg_red_blue1_enable = 0;
        pSelect->pg_green1_enable = 0;
        pSelect->pg_fac_1_rb = 0;
        pSelect->pg_fac_1_g = 0;
        break;
    case 10:
        pSelect->sw_rk_red_blue1_en = 1;
        pSelect->sw_rk_green1_en = 1;
        pSelect->sw_mindis1_rb = 0x8;
        pSelect->sw_mindis1_g = 0x8;
        pSelect->sw_dis_scale_min1 = 0x6;
        pSelect->sw_dis_scale_max1 = 0x6;

        pSelect->rg_red_blue1_enable = 0;
        pSelect->rg_green1_enable = 0;
        pSelect->rg_fac_1_rb = 0;
        pSelect->rg_fac_1_g = 0;

        pSelect->rnd_red_blue1_enable = 0;
        pSelect->rnd_green1_enable = 0;
        pSelect->rnd_thr_1_rb = 0;
        pSelect->rnd_thr_1_g = 0;
        pSelect->rnd_offs_1_rb = 0;
        pSelect->rnd_offs_1_g = 0;

        pSelect->ro_red_blue1_enable = 1;
        pSelect->ro_green1_enable = 1;
        pSelect->ro_lim_1_rb = 0x3;
        pSelect->ro_lim_1_g = 0x3;

        pSelect->lc_red_blue1_enable = 0;
        pSelect->lc_green1_enable = 0;
        pSelect->line_thr_1_rb = 0;
        pSelect->line_thr_1_g = 0;
        pSelect->line_mad_fac_1_rb = 0;
        pSelect->line_mad_fac_1_g = 0;

        pSelect->pg_red_blue1_enable = 0;
        pSelect->pg_green1_enable = 0;
        pSelect->pg_fac_1_rb = 0;
        pSelect->pg_fac_1_g = 0;
        break;
    default:
        LOGE_ADPCC("%s(%d): Wrong fast mode level!!!\n", __FUNCTION__, __LINE__);
        break;
    }

    LOGD_ADPCC("%s(%d): Dpcc fast mode level:%\n", __FUNCTION__, __LINE__, level);
    LOGV_ADPCC("%s(%d): Dpcc fast mode level:%\n", __FUNCTION__, __LINE__, level);

    LOG1_ADPCC("%s(%d): exit!\n", __FUNCTION__, __LINE__);

}

AdpccResult_t Fast_mode_select_basic_params_by_ISO(
    AdpccContext_t *pParams,
    Adpcc_basic_params_select_t *pSelect,
    AdpccExpInfo_t *pExpInfo)
{
    AdpccResult_t ret = ADPCC_RET_SUCCESS;
    int iso = 50;

    LOGI_ADPCC("%s(%d): enter!\n", __FUNCTION__, __LINE__);

    if(pParams == NULL) {
        ret = ADPCC_RET_NULL_POINTER;
        LOGE_ADPCC("%s(%d): invalid inputparams\n", __FUNCTION__, __LINE__);
        return ret;
    }

    if(pSelect == NULL) {
        ret = ADPCC_RET_NULL_POINTER;
        LOGE_ADPCC("%s(%d): invalid inputparams\n", __FUNCTION__, __LINE__);
        return ret;
    }

    if(pExpInfo == NULL) {
        ret = ADPCC_RET_NULL_POINTER;
        LOGE_ADPCC("%s(%d): invalid inputparams\n", __FUNCTION__, __LINE__);
        return ret;
    }

    iso = pExpInfo->arPreResIso[pExpInfo->hdr_mode];

    //set dpcc ctrl params
    //mode 0x0000
    pSelect->stage1_enable = 1;

    if(pParams->isBlackSensor)
        pSelect->grayscale_mode = 0x1;
    else
        pSelect->grayscale_mode = 0x0;

    pSelect->enable = 0x1;

    //output_mode 0x0004
    pSelect->sw_rk_out_sel = 1;
    pSelect->sw_dpcc_output_sel = 1;
    pSelect->stage1_rb_3x3 = 0;
    pSelect->stage1_g_3x3 = 0;
    pSelect->stage1_incl_rb_center = 1;
    pSelect->stage1_incl_green_center = 1;

    //set_use 0x0008
    pSelect->stage1_use_fix_set = 0x0;

    //get current fast mode single level
    Fast_mode_Single_Setting(pParams, pSelect, iso);

    //get current fast mode double level
    Fast_mode_Double_Setting(pParams, pSelect, iso);

    //get current fast mode triple level
    Fast_mode_Triple_Setting(pParams, pSelect, iso);


    LOGI_ADPCC("%s(%d): exit!\n", __FUNCTION__, __LINE__);
    return ret;
}

AdpccResult_t select_bpt_params_by_ISO(
    Adpcc_bpt_params_t *pParams,
    Adpcc_bpt_params_select_t *pSelect,
    AdpccExpInfo_t *pExpInfo)
{
    AdpccResult_t ret = ADPCC_RET_SUCCESS;

    LOGI_ADPCC("%s(%d): enter!\n", __FUNCTION__, __LINE__);

    if(pParams == NULL) {
        ret = ADPCC_RET_NULL_POINTER;
        LOGE_ADPCC("%s(%d): invalid inputparams\n", __FUNCTION__, __LINE__);
        return ret;
    }

    if(pSelect == NULL) {
        ret = ADPCC_RET_NULL_POINTER;
        LOGE_ADPCC("%s(%d): invalid inputparams\n", __FUNCTION__, __LINE__);
        return ret;
    }

    if(pExpInfo == NULL) {
        ret = ADPCC_RET_NULL_POINTER;
        LOGE_ADPCC("%s(%d): invalid inputparams\n", __FUNCTION__, __LINE__);
        return ret;
    }

    memcpy(pSelect, pParams, sizeof(Adpcc_bpt_params_select_t));

    LOGI_ADPCC("%s(%d): exit!\n", __FUNCTION__, __LINE__);
    return ret;
}

AdpccResult_t select_pdaf_params_by_ISO(
    Adpcc_pdaf_params_t *pParams,
    Adpcc_pdaf_params_select_t *pSelect,
    AdpccExpInfo_t *pExpInfo)
{
    AdpccResult_t ret = ADPCC_RET_SUCCESS;

    LOGI_ADPCC("%s(%d): enter!\n", __FUNCTION__, __LINE__);

    if(pParams == NULL) {
        ret = ADPCC_RET_NULL_POINTER;
        LOGE_ADPCC("%s(%d): invalid inputparams\n", __FUNCTION__, __LINE__);
        return ret;
    }

    if(pSelect == NULL) {
        ret = ADPCC_RET_NULL_POINTER;
        LOGE_ADPCC("%s(%d): invalid inputparams\n", __FUNCTION__, __LINE__);
        return ret;
    }

    if(pExpInfo == NULL) {
        ret = ADPCC_RET_NULL_POINTER;
        LOGE_ADPCC("%s(%d): invalid inputparams\n", __FUNCTION__, __LINE__);
        return ret;
    }

    memcpy(pSelect, pParams, sizeof(Adpcc_pdaf_params_select_t));

    LOGI_ADPCC("%s(%d): exit!\n", __FUNCTION__, __LINE__);
    return ret;
}

AdpccResult_t DpccExpertMode(
    Adpcc_pdaf_params_t *pParams,
    Adpcc_pdaf_params_select_t *pSelect,
    AdpccExpInfo_t *pExpInfo)
{
    AdpccResult_t ret = ADPCC_RET_SUCCESS;

    LOGI_ADPCC("%s(%d): enter!\n", __FUNCTION__, __LINE__);

    if(pParams == NULL) {
        ret = ADPCC_RET_NULL_POINTER;
        LOGE_ADPCC("%s(%d): invalid inputparams\n", __FUNCTION__, __LINE__);
        return ret;
    }

    if(pSelect == NULL) {
        ret = ADPCC_RET_NULL_POINTER;
        LOGE_ADPCC("%s(%d): invalid inputparams\n", __FUNCTION__, __LINE__);
        return ret;
    }

    if(pExpInfo == NULL) {
        ret = ADPCC_RET_NULL_POINTER;
        LOGE_ADPCC("%s(%d): invalid inputparams\n", __FUNCTION__, __LINE__);
        return ret;
    }

    memcpy(pSelect, pParams, sizeof(Adpcc_pdaf_params_select_t));

    LOGI_ADPCC("%s(%d): exit!\n", __FUNCTION__, __LINE__);
    return ret;
}

int GetCurrDpccValue
(
    int           inPara,
    float           max,
    float         inMatrixX[13],
    float         inMatrixY[13]
) {
    LOG1_AHDR( "%s:enter!\n", __FUNCTION__);
    float x1 = 0.0f;
    float x2 = 0.0f;
    float value1 = 0.0f;
    float value2 = 0.0f;
    float outPara = 0.0f;

    for(int i = 0; i < 12; i++)
        inMatrixY[i] > max ? inMatrixY[i] = max : inMatrixY[i] = inMatrixY[i] ;

    if(inPara < inMatrixX[0])
        outPara = inMatrixY[0];
    else if (inPara >= inMatrixX[12])
        outPara = inMatrixY[12];
    else
        for(int i = 0 ; i < 11;)
        {
            if(inPara >= inMatrixX[i] && inPara < inMatrixX[i + 1])
            {
                x1 = inMatrixX[i];
                x2 = inMatrixX[i + 1];
                value1 = inMatrixY[i];
                value2 = inMatrixY[i + 1];
                outPara = value1 + (inPara - x1) * (value1 - value2) / (x1 - x2);
                break;
            }
            else
                i++;
        }

    int out = (int)(outPara + 0.5);

    return out;
    LOG1_AHDR( "%s:exit!\n", __FUNCTION__);
}

void Sensor_dpcc_process(AdpccContext_t *pAdpccCtx)
{


    LOGI_ADPCC("%s(%d): enter!\n", __FUNCTION__, __LINE__);
    int iso = 0;
    if(pAdpccCtx->stExpInfo.hdr_mode == 0)
        iso = pAdpccCtx->stExpInfo.arProcResIso[0];
    else if(pAdpccCtx->stExpInfo.hdr_mode == 1)
        iso = pAdpccCtx->stExpInfo.arProcResIso[1];
    else if(pAdpccCtx->stExpInfo.hdr_mode == 2)
        iso = pAdpccCtx->stExpInfo.arProcResIso[2];

    float sensor_dpcc_level_single = GetCurrDpccValue(iso, pAdpccCtx->stDpccCalib.sensor_dpcc.max_level,
                                     pAdpccCtx->stDpccCalib.sensor_dpcc.iso, pAdpccCtx->stDpccCalib.sensor_dpcc.level_single);
    float sensor_dpcc_level_multi = GetCurrDpccValue(iso, pAdpccCtx->stDpccCalib.sensor_dpcc.max_level,
                                    pAdpccCtx->stDpccCalib.sensor_dpcc.iso, pAdpccCtx->stDpccCalib.sensor_dpcc.level_multiple);

    pAdpccCtx->SenDpccRes.enable = pAdpccCtx->stDpccCalib.sensor_dpcc.en;
    pAdpccCtx->SenDpccRes.cur_single_dpcc = (int)(sensor_dpcc_level_single + 0.5);
    pAdpccCtx->SenDpccRes.cur_multiple_dpcc = (int)(sensor_dpcc_level_multi + 0.5);
    pAdpccCtx->SenDpccRes.total_dpcc = (int)(pAdpccCtx->stDpccCalib.sensor_dpcc.max_level + 0.5);

    if(pAdpccCtx->SenDpccRes.enable == false)
        LOGD_ADPCC("%s(%d):sensor dpcc setting off!!\n", __FUNCTION__, __LINE__);
    else
        LOGD_ADPCC("%s(%d):sensor dpcc setting on!!\n", __FUNCTION__, __LINE__);

    LOGD_ADPCC("%s(%d):ISO:%d sensor dpcc cur_s_dpcc:%d cur_m_dpcc:%d total_dpcc:%d!!\n", __FUNCTION__, __LINE__, iso,
               pAdpccCtx->SenDpccRes.cur_single_dpcc, pAdpccCtx->SenDpccRes.cur_multiple_dpcc, pAdpccCtx->SenDpccRes.total_dpcc);

    LOGI_ADPCC("%s(%d): exit!\n", __FUNCTION__, __LINE__);

}


AdpccResult_t AdpccInit(AdpccContext_t **ppAdpccCtx, CamCalibDbContext_t *pCalibDb)
{
    AdpccContext_t * pAdpccCtx;

    LOGI_ADPCC(" %s(%d): enter!\n", __FUNCTION__, __LINE__);

    pAdpccCtx = (AdpccContext_t *)malloc(sizeof(AdpccContext_t));
    if(pAdpccCtx == NULL) {
        LOGE_ADPCC("%s(%d): invalid inputparams\n", __FUNCTION__, __LINE__);
        return ADPCC_RET_NULL_POINTER;
    }

    memset(pAdpccCtx, 0x00, sizeof(AdpccContext_t));
    pAdpccCtx->eState = ADPCC_STATE_INITIALIZED;

    *ppAdpccCtx = pAdpccCtx;

    pAdpccCtx->eMode = ADPCC_OP_MODE_AUTO;

#if 1
    //init fix param for algo
    pAdpccCtx->stDpccCalib = pCalibDb->dpcc;
    dpcc_expert_mode_basic_params_init(&pAdpccCtx->stAuto.stBasicParams, &pAdpccCtx->stDpccCalib);
    dpcc_fast_mode_basic_params_init(&pAdpccCtx->fast, &pAdpccCtx->stDpccCalib);
    dpcc_pdaf_params_init(&pAdpccCtx->stAuto.stPdafParams, &pAdpccCtx->stDpccCalib.pdaf);
    memset(&pAdpccCtx->stAuto.stPdafParams, 0x00, sizeof(pAdpccCtx->stAuto.stPdafParams));
#else
    //static init
    html_params_init(&pAdpccCtx->stParams);
    memcpy(&pAdpccCtx->stAuto.stBasicParams, &pAdpccCtx->stParams.stBasic, sizeof(Adpcc_basic_params_t));
    memcpy(&pAdpccCtx->stAuto.stBptParams, &pAdpccCtx->stParams.stBpt, sizeof(Adpcc_bpt_params_t));
    memcpy(&pAdpccCtx->stAuto.stPdafParams, &pAdpccCtx->stParams.stPdaf, sizeof(Adpcc_pdaf_params_t));
#endif

    for(int i = 0; i < 3; i++) {
        pAdpccCtx->PreAe.arProcResIso[i] = 50;
        pAdpccCtx->PreAe.arProcResAGain[i] = 1.0;
        pAdpccCtx->PreAe.arProcResDGain[i] = 1.0;
        pAdpccCtx->PreAe.arProcResTime[i] = 0.01;
    }

    LOGI_ADPCC("%s(%d): exit!\n", __FUNCTION__, __LINE__);
    return ADPCC_RET_SUCCESS;

}

AdpccResult_t AdpccRelease(AdpccContext_t *pAdpccCtx)
{
    LOGI_ADPCC("%s(%d): enter!\n", __FUNCTION__, __LINE__);
    if(pAdpccCtx == NULL) {
        LOGE_ADPCC("%s(%d): null pointer\n", __FUNCTION__, __LINE__);
        return ADPCC_RET_NULL_POINTER;
    }

    memset(pAdpccCtx, 0x00, sizeof(AdpccContext_t));
    free(pAdpccCtx);

    LOGI_ADPCC("%s(%d): exit!\n", __FUNCTION__, __LINE__);
    return ADPCC_RET_SUCCESS;
}

AdpccResult_t AdpccConfig(AdpccContext_t *pAdpccCtx, AdpccConfig_t* pAdpccConfig)
{
    LOGI_ADPCC("%s(%d): enter!\n", __FUNCTION__, __LINE__);

    if(pAdpccCtx == NULL) {
        LOGE_ADPCC("%s(%d): null pointer\n", __FUNCTION__, __LINE__);
        return ADPCC_RET_INVALID_PARM;
    }

    if(pAdpccConfig == NULL) {
        LOGE_ADPCC("%s(%d): null pointer\n", __FUNCTION__, __LINE__);
        return ADPCC_RET_INVALID_PARM;
    }

    //pAdpccCtx->eMode = pAdpccConfig->eMode;
    //pAdpccCtx->eState = pAdpccConfig->eState;

    LOGI_ADPCC("%s(%d): exit!\n", __FUNCTION__, __LINE__);
    return ADPCC_RET_SUCCESS;
}

AdpccResult_t AdpccReConfig(AdpccContext_t *pAdpccCtx, AdpccConfig_t* pAdpccConfig)
{
    LOGI_ADPCC("%s(%d): enter!\n", __FUNCTION__, __LINE__);
    //need todo what?

    LOGI_ADPCC("%s(%d): exit!\n", __FUNCTION__, __LINE__);
    return ADPCC_RET_SUCCESS;
}

AdpccResult_t AdpccPreProcess(AdpccContext_t *pAdpccCtx)
{
    LOGI_ADPCC("%s(%d): enter!\n", __FUNCTION__, __LINE__);
    //need todo what?

    LOGI_ADPCC("%s(%d): exit!\n", __FUNCTION__, __LINE__);
    return ADPCC_RET_SUCCESS;
}

AdpccResult_t AdpccProcess(AdpccContext_t *pAdpccCtx, AdpccExpInfo_t *pExpInfo)
{
    LOGI_ADPCC("%s(%d): enter!\n", __FUNCTION__, __LINE__);
    AdpccResult_t ret = ADPCC_RET_SUCCESS;

    if(pAdpccCtx == NULL) {
        LOGE_ADPCC("%s(%d): null pointer\n", __FUNCTION__, __LINE__);
        return ADPCC_RET_INVALID_PARM;
    }

    if(pExpInfo == NULL) {
        LOGE_ADPCC("%s(%d): null pointer\n", __FUNCTION__, __LINE__);
        return ADPCC_RET_INVALID_PARM;
    }

    memcpy(&pAdpccCtx->stExpInfo, pExpInfo, sizeof(AdpccExpInfo_t));

    bool fast_enable = pAdpccCtx->stDpccCalib.fast.fast_mode_en == 0 ? false : true;

    if(pAdpccCtx->eMode == ADPCC_OP_MODE_AUTO) {
        if(fast_enable == false)
            ret = Expert_mode_select_basic_params_by_ISO(&pAdpccCtx->stAuto.stBasicParams, &pAdpccCtx->stAuto.stBasicSelect, pExpInfo);
        else
            ret = Fast_mode_select_basic_params_by_ISO(pAdpccCtx, &pAdpccCtx->stAuto.stBasicSelect, pExpInfo);

        ret = select_bpt_params_by_ISO(&pAdpccCtx->stAuto.stBptParams, &pAdpccCtx->stAuto.stBptSelect, pExpInfo);
        ret = select_pdaf_params_by_ISO(&pAdpccCtx->stAuto.stPdafParams, &pAdpccCtx->stAuto.stPdafSelect, pExpInfo);
    } else if(pAdpccCtx->eMode == ADPCC_OP_MODE_MANUAL) {
        //TODO

    }


    //sensor dpcc
    if(pAdpccCtx->stDpccCalib.sensor_dpcc.en != 0 )
        Sensor_dpcc_process(pAdpccCtx);


    LOGI_ADPCC("%s(%d): exit!\n", __FUNCTION__, __LINE__);
    return ret;
}

AdpccResult_t AdpccGetProcResult(AdpccContext_t *pAdpccCtx, AdpccProcResult_t* pAdpccResult)
{
    LOGI_ADPCC("%s(%d): enter!\n", __FUNCTION__, __LINE__);

    if(pAdpccCtx == NULL) {
        LOGE_ADPCC("%s(%d): null pointer\n", __FUNCTION__, __LINE__);
        return ADPCC_RET_INVALID_PARM;
    }

    if(pAdpccResult == NULL) {
        LOGE_ADPCC("%s(%d): null pointer\n", __FUNCTION__, __LINE__);
        return ADPCC_RET_INVALID_PARM;
    }

    if(pAdpccCtx->eMode == ADPCC_OP_MODE_AUTO) {
        pAdpccResult->stBasic = pAdpccCtx->stAuto.stBasicSelect;
        pAdpccResult->stBpt = pAdpccCtx->stAuto.stBptSelect;
        pAdpccResult->stPdaf = pAdpccCtx->stAuto.stPdafSelect;
    } else if(pAdpccCtx->eMode == ADPCC_OP_MODE_MANUAL) {
        //TODO
        pAdpccResult->stBasic = pAdpccCtx->stManual.stBasic;
        pAdpccResult->stBpt = pAdpccCtx->stManual.stBpt;
        pAdpccResult->stPdaf = pAdpccCtx->stManual.stPdaf;
    }


    LOGI_ADPCC("%s(%d): exit!\n", __FUNCTION__, __LINE__);
    return ADPCC_RET_SUCCESS;
}


