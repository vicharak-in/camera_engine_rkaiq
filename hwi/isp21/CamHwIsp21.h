
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

#ifndef _CAM_HW_ISP21_H_
#define _CAM_HW_ISP21_H_

#include "isp20/CamHwIsp20.h"
#include "Isp21Params.h"

namespace RkCam {

class CamHwIsp21
    : public CamHwIsp20
    , virtual public Isp21Params {
public:
    explicit CamHwIsp21();
    virtual ~CamHwIsp21();
    virtual XCamReturn init(const char* sns_ent_name);
    XCamReturn setIspParamsSync(int frameId);
    XCamReturn setIsppParamsSync(int frameId);
    XCamReturn setIsppParams(SmartPtr<RkAiqIsppParamsProxy>& isppParams);
private:
    void gen_full_isp_params(const struct isp21_isp_params_cfg* update_params,
                             struct isp21_isp_params_cfg* full_params);
	XCamReturn overrideExpRatioV21ToAiqResults(const sint32_t frameId, int module_id, SmartPtr<RkAiqIspParamsProxy>& aiq_results);
    struct isp21_isp_params_cfg _full_active_isp21_params;
};

};

#endif
