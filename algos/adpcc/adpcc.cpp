#include "adpcc.h"
#include "rk_aiq_algo_adpcc_itf.h"

#define DPCC_RK_MODE

AdpccResult_t html_params_init(Adpcc_html_param_t *pParams)
{
	AdpccResult_t ret = ADPCC_RET_SUCCESS;

	if(pParams == NULL){
		ret = ADPCC_RET_NULL_POINTER;
		LOGE_ADPCC("%s(%d): invalid input params\n", __FUNCTION__, __LINE__);
		return ret;
	}

	Adpcc_basic_params_t *pBasic = &pParams->stBasic;
	Adpcc_bpt_params_t *pBpt = &pParams->stBpt;
	Adpcc_pdaf_params_t *pPdaf = &pParams->stPdaf;
	int iso_base = 50;
	
	for(int i=0; i<MAX_ISO_LEVEL; i++){
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

	return ret;
	
}


AdpccResult_t dpcc_basic_params_init(Adpcc_basic_params_t *pBasic, CalibDb_Dpcc_t *pCalib)
{
	AdpccResult_t ret = ADPCC_RET_SUCCESS;

	if(pBasic == NULL){
		ret = ADPCC_RET_NULL_POINTER;
		LOGE_ADPCC("%s(%d): invalid input params\n", __FUNCTION__, __LINE__);
		return ret;
	}

	if(pCalib == NULL){
		ret = ADPCC_RET_NULL_POINTER;
		LOGE_ADPCC("%s(%d): invalid input params\n", __FUNCTION__, __LINE__);
		return ret;
	}
	
	for(int i=0; i<MAX_ISO_LEVEL; i++){
		pBasic->arBasic[i].iso = pCalib->iso[i];

		//mode 0x0000
		pBasic->arBasic[i].stage1_enable = pCalib->stage1_Enable[i];
		pBasic->arBasic[i].grayscale_mode = pCalib->grayscale_mode[i];
		pBasic->arBasic[i].enable = pCalib->enable;

		//output_mode 0x0004
		pBasic->arBasic[i].sw_rk_out_sel = pCalib->rk_out_sel[i];
		pBasic->arBasic[i].sw_dpcc_output_sel = pCalib->dpcc_out_sel[i];
		pBasic->arBasic[i].stage1_rb_3x3 = pCalib->stage1_rb_3x3[i];
		pBasic->arBasic[i].stage1_g_3x3 = pCalib->stage1_g_3x3[i];
		pBasic->arBasic[i].stage1_incl_rb_center = pCalib->stage1_inc_rb_center[i];
		pBasic->arBasic[i].stage1_incl_green_center = pCalib->stage1_inc_g_center[i];
		
		//set_use 0x0008
		pBasic->arBasic[i].stage1_use_fix_set = pCalib->stage1_use_fix_set[i];
		pBasic->arBasic[i].stage1_use_set_3 = pCalib->stage1_use_set3[i];
		pBasic->arBasic[i].stage1_use_set_2 = pCalib->stage1_use_set2[i];
		pBasic->arBasic[i].stage1_use_set_1 = pCalib->stage1_use_set1[i];

		//methods_set_1 0x000c
		pBasic->arBasic[i].sw_rk_red_blue1_en = pCalib->set[0].red_blue_enable[0][i];
		pBasic->arBasic[i].rg_red_blue1_enable = pCalib->set[0].red_blue_enable[1][i];
		pBasic->arBasic[i].rnd_red_blue1_enable = pCalib->set[0].red_blue_enable[2][i];
		pBasic->arBasic[i].ro_red_blue1_enable = pCalib->set[0].red_blue_enable[3][i];
		pBasic->arBasic[i].lc_red_blue1_enable = pCalib->set[0].red_blue_enable[4][i];
		pBasic->arBasic[i].pg_red_blue1_enable = pCalib->set[0].red_blue_enable[5][i];	
		pBasic->arBasic[i].sw_rk_green1_en = pCalib->set[0].green_enable[0][i];
		pBasic->arBasic[i].rg_green1_enable = pCalib->set[0].green_enable[1][i];
		pBasic->arBasic[i].rnd_green1_enable = pCalib->set[0].green_enable[2][i];
		pBasic->arBasic[i].ro_green1_enable = pCalib->set[0].green_enable[3][i];
		pBasic->arBasic[i].lc_green1_enable = pCalib->set[0].green_enable[4][i];
		pBasic->arBasic[i].pg_green1_enable = pCalib->set[0].green_enable[5][i];

		//methods_set_2 0x0010
		pBasic->arBasic[i].sw_rk_red_blue2_en = pCalib->set[1].red_blue_enable[0][i];
		pBasic->arBasic[i].rg_red_blue2_enable = pCalib->set[1].red_blue_enable[1][i];
		pBasic->arBasic[i].rnd_red_blue2_enable = pCalib->set[1].red_blue_enable[2][i];
		pBasic->arBasic[i].ro_red_blue2_enable = pCalib->set[1].red_blue_enable[3][i];
		pBasic->arBasic[i].lc_red_blue2_enable = pCalib->set[1].red_blue_enable[4][i];
		pBasic->arBasic[i].pg_red_blue2_enable = pCalib->set[1].red_blue_enable[5][i];	
		pBasic->arBasic[i].sw_rk_green2_en = pCalib->set[1].green_enable[0][i];
		pBasic->arBasic[i].rg_green2_enable = pCalib->set[1].green_enable[1][i];
		pBasic->arBasic[i].rnd_green2_enable = pCalib->set[1].green_enable[2][i];
		pBasic->arBasic[i].ro_green2_enable = pCalib->set[1].green_enable[3][i];
		pBasic->arBasic[i].lc_green2_enable = pCalib->set[1].green_enable[4][i];
		pBasic->arBasic[i].pg_green2_enable = pCalib->set[1].green_enable[5][i];

		//methods_set_3 0x0014
		pBasic->arBasic[i].sw_rk_red_blue3_en = pCalib->set[2].red_blue_enable[0][i];
		pBasic->arBasic[i].rg_red_blue3_enable = pCalib->set[2].red_blue_enable[1][i];
		pBasic->arBasic[i].rnd_red_blue3_enable = pCalib->set[2].red_blue_enable[2][i];
		pBasic->arBasic[i].ro_red_blue3_enable = pCalib->set[2].red_blue_enable[3][i];
		pBasic->arBasic[i].lc_red_blue3_enable = pCalib->set[2].red_blue_enable[4][i];
		pBasic->arBasic[i].pg_red_blue3_enable = pCalib->set[2].red_blue_enable[5][i];	
		pBasic->arBasic[i].sw_rk_green3_en = pCalib->set[2].green_enable[0][i];
		pBasic->arBasic[i].rg_green3_enable = pCalib->set[2].green_enable[1][i];
		pBasic->arBasic[i].rnd_green3_enable = pCalib->set[2].green_enable[2][i];
		pBasic->arBasic[i].ro_green3_enable = pCalib->set[2].green_enable[3][i];
		pBasic->arBasic[i].lc_green3_enable = pCalib->set[2].green_enable[4][i];
		pBasic->arBasic[i].pg_green3_enable = pCalib->set[2].green_enable[5][i];	
		
		//line_thresh_1 0x0018
		pBasic->arBasic[i].sw_mindis1_rb = pCalib->set[0].line_thresh[0][i];
		pBasic->arBasic[i].sw_mindis1_g = pCalib->set[0].line_thresh[1][i];
		pBasic->arBasic[i].line_thr_1_rb = pCalib->set[0].line_thresh[2][i];
		pBasic->arBasic[i].line_thr_1_g = pCalib->set[0].line_thresh[3][i];
		
		//line_mad_fac_1 0x001c
		pBasic->arBasic[i].sw_dis_scale_min1 = pCalib->set[0].line_mad_fac[0][i];
		pBasic->arBasic[i].sw_dis_scale_max1 = pCalib->set[0].line_mad_fac[1][i];
		pBasic->arBasic[i].line_mad_fac_1_rb = pCalib->set[0].line_mad_fac[2][i];
		pBasic->arBasic[i].line_mad_fac_1_g = pCalib->set[0].line_mad_fac[3][i];
		
		//pg_fac_1 0x0020
		pBasic->arBasic[i].pg_fac_1_rb = pCalib->set[0].pg_fac[0][i];
		pBasic->arBasic[i].pg_fac_1_g = pCalib->set[0].pg_fac[1][i];
		
		//rnd_thresh_1 0x0024
		pBasic->arBasic[i].rnd_thr_1_rb = pCalib->set[0].rnd_thresh[0][i];
		pBasic->arBasic[i].rnd_thr_1_g = pCalib->set[0].rnd_thresh[1][i];
		
		//rg_fac_1 0x0028
		pBasic->arBasic[i].rg_fac_1_rb = pCalib->set[0].rg_fac[0][i];
		pBasic->arBasic[i].rg_fac_1_g = pCalib->set[0].rg_fac[1][i];
			

		//line_thresh_2 0x002c
		pBasic->arBasic[i].sw_mindis2_rb = pCalib->set[1].line_thresh[0][i];
		pBasic->arBasic[i].sw_mindis2_g = pCalib->set[1].line_thresh[1][i];
		pBasic->arBasic[i].line_thr_2_rb = pCalib->set[1].line_thresh[2][i];
		pBasic->arBasic[i].line_thr_2_g = pCalib->set[1].line_thresh[3][i];
		
		//line_mad_fac_2 0x0030
		pBasic->arBasic[i].sw_dis_scale_min2 = pCalib->set[1].line_mad_fac[0][i];
		pBasic->arBasic[i].sw_dis_scale_max2 = pCalib->set[1].line_mad_fac[1][i];
		pBasic->arBasic[i].line_mad_fac_2_rb = pCalib->set[1].line_mad_fac[2][i];
		pBasic->arBasic[i].line_mad_fac_2_g = pCalib->set[1].line_mad_fac[3][i];
		
		//pg_fac_2 0x0034
		pBasic->arBasic[i].pg_fac_2_rb = pCalib->set[1].pg_fac[0][i];
		pBasic->arBasic[i].pg_fac_2_g = pCalib->set[1].pg_fac[1][i];
		
		//rnd_thresh_2 0x0038
		pBasic->arBasic[i].rnd_thr_2_rb = pCalib->set[1].rnd_thresh[0][i];
		pBasic->arBasic[i].rnd_thr_2_g = pCalib->set[1].rnd_thresh[1][i];
		
		//rg_fac_2 0x003c
		pBasic->arBasic[i].rg_fac_2_rb = pCalib->set[1].rg_fac[0][i];
		pBasic->arBasic[i].rg_fac_2_g = pCalib->set[1].rg_fac[1][i];

		
		//line_thresh_3 0x0040
		pBasic->arBasic[i].sw_mindis3_rb = pCalib->set[2].line_thresh[0][i];
		pBasic->arBasic[i].sw_mindis3_g = pCalib->set[2].line_thresh[1][i];
		pBasic->arBasic[i].line_thr_3_rb = pCalib->set[2].line_thresh[2][i];
		pBasic->arBasic[i].line_thr_3_g = pCalib->set[2].line_thresh[3][i];
		
		//line_mad_fac_3 0x0044
		pBasic->arBasic[i].sw_dis_scale_min3 = pCalib->set[2].line_mad_fac[0][i];
		pBasic->arBasic[i].sw_dis_scale_max3 = pCalib->set[2].line_mad_fac[1][i];
		pBasic->arBasic[i].line_mad_fac_3_rb = pCalib->set[2].line_mad_fac[2][i];
		pBasic->arBasic[i].line_mad_fac_3_g = pCalib->set[2].line_mad_fac[3][i];
		
		//pg_fac_3 0x0048
		pBasic->arBasic[i].pg_fac_3_rb = pCalib->set[2].pg_fac[0][i];
		pBasic->arBasic[i].pg_fac_3_g = pCalib->set[2].pg_fac[1][i];
		
		//rnd_thresh_3 0x004c
		pBasic->arBasic[i].rnd_thr_3_rb = pCalib->set[2].rnd_thresh[0][i];
		pBasic->arBasic[i].rnd_thr_3_g = pCalib->set[2].rnd_thresh[1][i];
		
		//rg_fac_3 0x0050
		pBasic->arBasic[i].rg_fac_3_rb = pCalib->set[2].rg_fac[0][i];
		pBasic->arBasic[i].rg_fac_3_g = pCalib->set[2].rg_fac[1][i];
		
		//ro_limits 0x0054
		pBasic->arBasic[i].ro_lim_3_rb = pCalib->set[2].rg_lim[0][i];
		pBasic->arBasic[i].ro_lim_3_g = pCalib->set[2].rg_lim[1][i];
		pBasic->arBasic[i].ro_lim_2_rb = pCalib->set[1].rg_lim[0][i];
		pBasic->arBasic[i].ro_lim_2_g = pCalib->set[1].rg_lim[1][i];
		pBasic->arBasic[i].ro_lim_1_rb = pCalib->set[0].rg_lim[0][i];
		pBasic->arBasic[i].ro_lim_1_g = pCalib->set[0].rg_lim[1][i];
		
		//rnd_offs 0x0058
		pBasic->arBasic[i].rnd_offs_3_rb = pCalib->set[2].rnd_offs[0][i];
		pBasic->arBasic[i].rnd_offs_3_g = pCalib->set[2].rnd_offs[1][i];
		pBasic->arBasic[i].rnd_offs_2_rb = pCalib->set[1].rnd_offs[0][i];
		pBasic->arBasic[i].rnd_offs_2_g = pCalib->set[1].rnd_offs[1][i];
		pBasic->arBasic[i].rnd_offs_1_rb = pCalib->set[0].rnd_offs[0][i];
		pBasic->arBasic[i].rnd_offs_1_g = pCalib->set[0].rnd_offs[1][i];

	}

	return ret;
	
}

AdpccResult_t dpcc_pdaf_params_init(Adpcc_pdaf_params_t *pPdaf, CalibDb_Dpcc_Pdaf_t *pCalib)
{
	AdpccResult_t ret = ADPCC_RET_SUCCESS;

	if(pPdaf == NULL){
		ret = ADPCC_RET_NULL_POINTER;
		LOGE_ADPCC("%s(%d): invalid input params\n", __FUNCTION__, __LINE__);
		return ret;
	}
	
	if(pCalib == NULL){
		ret = ADPCC_RET_NULL_POINTER;
		LOGE_ADPCC("%s(%d): invalid input params\n", __FUNCTION__, __LINE__);
		return ret;
	}

	pPdaf->sw_pdaf_en = pCalib->en;
	
	for(int i=0; i<16; i++){
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
	
}


AdpccResult_t select_basic_params_by_ISO(
	Adpcc_basic_params_t *pParams, 
	Adpcc_basic_params_select_t *pSelect, 
	int iso)
{
	AdpccResult_t ret = ADPCC_RET_SUCCESS;
	int lowLevel = 0;
	int highLevel = 0;
	int lowIso = 0;
	int highIso = 0;
	float ratio = 0.0;

	if(pParams == NULL){
		ret = ADPCC_RET_NULL_POINTER;
		LOGE_ADPCC("%s(%d): invalid inputparams\n", __FUNCTION__, __LINE__);
		return ret;
	}

	if(pSelect == NULL){
		ret = ADPCC_RET_NULL_POINTER;
		LOGE_ADPCC("%s(%d): invalid inputparams\n", __FUNCTION__, __LINE__);
		return ret;
	}

	for(int i=0; i<MAX_ISO_LEVEL-1; i++){
		printf("%s:(%d) iso:%d %d %d\n", __FUNCTION__, __LINE__,
			iso, pParams->arBasic[i].iso, pParams->arBasic[i+1].iso);
		if(iso >= pParams->arBasic[i].iso && iso <= pParams->arBasic[i+1].iso){
			lowLevel= i;
			highLevel = i+1;
			lowIso = pParams->arBasic[i].iso;
			highIso = pParams->arBasic[i+1].iso;
			//ratio = (iso -lowIso ) / (float)(highIso - lowIso);
			ratio = 0.0;
			break;
		}
	}

	if(iso < pParams->arBasic[0].iso ){
		lowLevel= 0;
		highLevel = 0;
		ratio = 0.0;
	}

	if(iso > pParams->arBasic[MAX_ISO_LEVEL - 1].iso ){
		lowLevel= MAX_ISO_LEVEL - 1;
		highLevel = MAX_ISO_LEVEL - 1;
		ratio = 1.0;
	}

	printf("%s:(%d) iso:%d lowLevel:%d hightLevel:%d lowIso:%d HighIso:%d ratio:%f\n",
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


	printf("%s:(%d) %d %d %d %d %d\n", __FUNCTION__, __LINE__, 
		pSelect->enable, pSelect->line_thr_2_g, pSelect->line_mad_fac_2_rb,
		pSelect->ro_lim_2_g, pSelect->rnd_offs_2_g);
	
	return ret;
}

AdpccResult_t select_bpt_params_by_ISO(
	Adpcc_bpt_params_t *pParams, 
	Adpcc_bpt_params_select_t *pSelect, 
	int iso)
{
	AdpccResult_t ret = ADPCC_RET_SUCCESS;
	
	if(pParams == NULL){
		ret = ADPCC_RET_NULL_POINTER;
		LOGE_ADPCC("%s(%d): invalid inputparams\n", __FUNCTION__, __LINE__);
		return ret;
	}

	if(pSelect == NULL){
		ret = ADPCC_RET_NULL_POINTER;
		LOGE_ADPCC("%s(%d): invalid inputparams\n", __FUNCTION__, __LINE__);
		return ret;
	}

	memcpy(pSelect, pParams, sizeof(Adpcc_bpt_params_select_t));

	return ret;
}

AdpccResult_t select_pdaf_params_by_ISO(
	Adpcc_pdaf_params_t *pParams, 
	Adpcc_pdaf_params_select_t *pSelect, 
	int iso)
{
	AdpccResult_t ret = ADPCC_RET_SUCCESS;
	
	if(pParams == NULL){
		ret = ADPCC_RET_NULL_POINTER;
		LOGE_ADPCC("%s(%d): invalid inputparams\n", __FUNCTION__, __LINE__);
		return ret;
	}

	if(pSelect == NULL){
		ret = ADPCC_RET_NULL_POINTER;
		LOGE_ADPCC("%s(%d): invalid inputparams\n", __FUNCTION__, __LINE__);
		return ret;
	}

	memcpy(pSelect, pParams, sizeof(Adpcc_pdaf_params_select_t));

	return ret;
}


AdpccResult_t AdpccInit(AdpccContext_t **ppAdpccCtx)
{
	AdpccContext_t * pAdpccCtx;
	
	LOGI_ADPCC("%s(%d): enter!\n", __FUNCTION__, __LINE__);
	
	pAdpccCtx = (AdpccContext_t *)malloc(sizeof(AdpccContext_t));
	if(pAdpccCtx == NULL){
		LOGE_ADPCC("%s(%d): invalid inputparams\n", __FUNCTION__, __LINE__);
		return ADPCC_RET_NULL_POINTER;
	}

	memset(pAdpccCtx, 0x00, sizeof(AdpccContext_t));
	pAdpccCtx->eState = ADPCC_STATE_INITIALIZED;

	*ppAdpccCtx = pAdpccCtx;
	
	LOGI_ADPCC("%s(%d): exit!\n", __FUNCTION__, __LINE__);
	return ADPCC_RET_SUCCESS;

}

AdpccResult_t AdpccRelease(AdpccContext_t *pAdpccCtx)
{
	LOGI_ADPCC("%s(%d): enter!\n", __FUNCTION__, __LINE__);
	if(pAdpccCtx == NULL){
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
	
	if(pAdpccCtx == NULL){
		LOGE_ADPCC("%s(%d): null pointer\n", __FUNCTION__, __LINE__);
		return ADPCC_RET_INVALID_PARM;
	}

	if(pAdpccConfig == NULL){
		LOGE_ADPCC("%s(%d): null pointer\n", __FUNCTION__, __LINE__);
		return ADPCC_RET_INVALID_PARM;
	}

#if 1
		//init fix param for algo
		pAdpccConfig->eMode = ADPCC_OP_MODE_AUTO;
		//html_params_init(&pAdpccConfig->stParams);
#endif

	if(pAdpccConfig->eMode == ADPCC_OP_MODE_AUTO){
		dpcc_basic_params_init(&pAdpccCtx->stAuto.stBasicParams, &pAdpccConfig->stDpccCalib);
		dpcc_pdaf_params_init(&pAdpccCtx->stAuto.stPdafParams, &pAdpccConfig->stDpccCalib.pdaf);
		memset(&pAdpccCtx->stAuto.stPdafParams, 0x00, sizeof(pAdpccCtx->stAuto.stPdafParams));
		
		//memcpy(&pAdpccCtx->stAuto.stBasicParams, &pAdpccConfig->stParams.stBasic, sizeof(Adpcc_basic_params_t));	
		//memcpy(&pAdpccCtx->stAuto.stBptParams, &pAdpccConfig->stParams.stBpt, sizeof(Adpcc_bpt_params_t));
		//memcpy(&pAdpccCtx->stAuto.stPdafParams, &pAdpccConfig->stParams.stPdaf, sizeof(Adpcc_pdaf_params_t));
	}

	pAdpccCtx->eMode = pAdpccConfig->eMode;
	pAdpccCtx->eState = pAdpccConfig->eState;

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

AdpccResult_t AdpccProcess(AdpccContext_t *pAdpccCtx, int iso)
{
	LOGI_ADPCC("%s(%d): enter!\n", __FUNCTION__, __LINE__);
	AdpccResult_t ret = ADPCC_RET_SUCCESS;
	
	if(pAdpccCtx == NULL){
		LOGE_ADPCC("%s(%d): null pointer\n", __FUNCTION__, __LINE__);
		return ADPCC_RET_INVALID_PARM;
	}

	if(iso < 0){
		LOGE_ADPCC("%s(%d): invalid iso:%d \n", __FUNCTION__, __LINE__, iso);
		return ADPCC_RET_INVALID_PARM;
	}

	printf("%s(%d): ISO:%d \n", __FUNCTION__, __LINE__, iso);
	
	if(pAdpccCtx->eMode == ADPCC_OP_MODE_AUTO){
		ret = select_basic_params_by_ISO(&pAdpccCtx->stAuto.stBasicParams, &pAdpccCtx->stAuto.stBasicSelect, iso);	
		ret = select_bpt_params_by_ISO(&pAdpccCtx->stAuto.stBptParams, &pAdpccCtx->stAuto.stBptSelect, iso);
		ret = select_pdaf_params_by_ISO(&pAdpccCtx->stAuto.stPdafParams, &pAdpccCtx->stAuto.stPdafSelect, iso);
		
	}else if(pAdpccCtx->eMode == ADPCC_OP_MODE_MANUAL){
		//TODO
		
	}
	
	LOGI_ADPCC("%s(%d): exit!\n", __FUNCTION__, __LINE__);
	return ret;
}

AdpccResult_t AdpccGetProcResult(AdpccContext_t *pAdpccCtx, AdpccProcResult_t* pAdpccResult)
{
	LOGI_ADPCC("%s(%d): enter!\n", __FUNCTION__, __LINE__);

	if(pAdpccCtx == NULL){
		LOGE_ADPCC("%s(%d): null pointer\n", __FUNCTION__, __LINE__);
		return ADPCC_RET_INVALID_PARM;
	}

	if(pAdpccResult == NULL){
		LOGE_ADPCC("%s(%d): null pointer\n", __FUNCTION__, __LINE__);
		return ADPCC_RET_INVALID_PARM;
	}
	
	if(pAdpccCtx->eMode == ADPCC_OP_MODE_AUTO){	
		pAdpccResult->stBasic = pAdpccCtx->stAuto.stBasicSelect;
		pAdpccResult->stBpt = pAdpccCtx->stAuto.stBptSelect;
		pAdpccResult->stPdaf = pAdpccCtx->stAuto.stPdafSelect;	
	}else if(pAdpccCtx->eMode == ADPCC_OP_MODE_MANUAL){
		//TODO
	}
	
	LOGI_ADPCC("%s(%d): exit!\n", __FUNCTION__, __LINE__);
	return ADPCC_RET_SUCCESS;
}

AdpccResult_t AdpccResultPrintf(AdpccProcResult_t* pAdpccResult)
{
	
}

