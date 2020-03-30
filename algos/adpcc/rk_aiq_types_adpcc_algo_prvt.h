/*
 *rk_aiq_types_alsc_algo_prvt.h
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

#ifndef _RK_AIQ_TYPES_ADPCC_ALGO_PRVT_H_
#define _RK_AIQ_TYPES_ADPCC_ALGO_PRVT_H_

#include "adpcc/rk_aiq_types_adpcc_algo_int.h"
#include "RkAiqCalibDbTypes.h"
#include "base/xcam_log.h"
#include "base/xcam_common.h"

RKAIQ_BEGIN_DECLARE

typedef struct AdpccContext_s{
	AdpccOPMode_t eMode;
	AdpccState_t eState;
	
	int iso;
	
	Adpcc_Auto_Attr_t stAuto;
	Adpcc_Manual_Attr_t stManual;

	//xml param
	CalibDb_Dpcc_t stDpccCalib;
	//html param
	Adpcc_html_param_t stParams;	
}AdpccContext_t;


RKAIQ_END_DECLARE

#endif

