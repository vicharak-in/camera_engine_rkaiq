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

#include "shared_item_pool.h"
#include "rk_aiq_types.h"

#ifndef RK_AIQ_POOL_H
#define RK_AIQ_POOL_H

namespace RkCam {

#if 0
class RkAiqPartResults {
public:
    explicit RkAiqPartResults() {
        mIspParams = NULL;
        mExposureParams = NULL;
        mFocusParams = NULL;
    };
    ~RkAiqPartResults() {};

    rk_aiq_isp_params_t* mIspParams;
    rk_aiq_exposure_params_comb_t* mExposureParams;
    rk_aiq_focus_params_t* mFocusParams;

private:
    XCAM_DEAD_COPY (RkAiqPartResults);
};
#endif

typedef SharedItemPool<rk_aiq_exposure_params_t> RkAiqExpParamsPool;
typedef SharedItemProxy<rk_aiq_exposure_params_t> RkAiqExpParamsProxy;
typedef SharedItemPool<rk_aiq_isp_params_t> RkAiqIspParamsPool;
typedef SharedItemProxy<rk_aiq_isp_params_t> RkAiqIspParamsProxy;
typedef SharedItemPool<rk_aiq_focus_params_t> RkAiqFocusParamsPool;
typedef SharedItemProxy<rk_aiq_focus_params_t> RkAiqFocusParamsProxy;

class RkAiqFullParams {
public:
    explicit RkAiqFullParams()
        : mExposureParams(NULL)
        , mIspParams(NULL)
        , mFocusParams(NULL) {
    };
    ~RkAiqFullParams() {};

    void reset() {
        mExposureParams.release();
        mIspParams.release();
        mFocusParams.release();
    };
    SmartPtr<RkAiqExpParamsProxy> mExposureParams;
    SmartPtr<RkAiqIspParamsProxy> mIspParams;
    SmartPtr<RkAiqFocusParamsProxy> mFocusParams;

private:
    XCAM_DEAD_COPY (RkAiqFullParams);
};

typedef SharedItemPool<RkAiqFullParams> RkAiqFullParamsPool;

/*
 * specific template instance for RkAiqFullParams proxy.
 * When the proxy returns the _data to its owner pool, the
 * _data is not been cleared(reset). It will cause the resources
 * in _data are not been recycled.
 * RkAiqFullParams contains other proxy's SmartPtr, so we will
 * clear it explicitly befor it is returned to pool so that the
 * containd resouces can be recycled correctly.
 */
template<> class SharedItemProxy<RkAiqFullParams>
{
public:
    explicit SharedItemProxy<RkAiqFullParams>(const SmartPtr<RkAiqFullParams> &data) : _data(data) {};
    ~SharedItemProxy<RkAiqFullParams>() {
        _data->reset();
        if (_pool.ptr())
            _pool->release(_data);
        _data.release();
    };

    void set_buf_pool (SmartPtr<SharedItemPool<RkAiqFullParams>> pool) {
        _pool = pool;
    }

    SmartPtr<RkAiqFullParams> &data() {
        return _data;
    }

private:
    XCAM_DEAD_COPY (SharedItemProxy);

private:
    SmartPtr<RkAiqFullParams>                       _data;
    SmartPtr<SharedItemPool<RkAiqFullParams>>       _pool;
};

typedef SharedItemProxy<RkAiqFullParams> RkAiqFullParamsProxy;

};

#endif //RK_AIQ_POOL_H