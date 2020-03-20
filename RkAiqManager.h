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

#ifndef _RK_AIQ_MANAGER_H_
#define _RK_AIQ_MANAGER_H_

#include "ICamHw.h"
#include "RkAiqCore.h"
#include "RkAiqCalibDb.h"
#include "RkLumaCore.h"
#include "rk_aiq.h"

namespace RkCam {

class RkAiqManager;
class RkAiqRstApplyThread
    : public Thread {
public:
    RkAiqRstApplyThread(RkAiqManager* aiqMng)
        : Thread("RkAiqRstApplyThread")
        , mAiqMng(aiqMng) {};
    ~RkAiqRstApplyThread() {};

    void triger_stop() {
        mAiqRstQueue.pause_pop ();
    };

    bool push_results (SmartPtr<RkAiqFullParamsProxy> aiqRst) {
        return mAiqRstQueue.push(aiqRst);
    };

protected:
    virtual void stopped () {
        mAiqRstQueue.clear ();
    };

    virtual bool loop ();

private:
    RkAiqManager* mAiqMng;
    SafeList<RkAiqFullParamsProxy>  mAiqRstQueue;
};

class RkAiqManager
    : public IspStatsListener
    , public IspLumaListener
    , public IspEvtsListener
    , public RkAiqAnalyzerCb
    , public RkLumaAnalyzerCb {
    friend RkAiqRstApplyThread;
public:
    explicit RkAiqManager(const char* sns_ent_name,
                          rk_aiq_error_cb err_cb,
                          rk_aiq_metas_cb metas_cb);
    virtual ~RkAiqManager();
    static XCamReturn getAiqStaticInfos();
    void setCamHw(SmartPtr<ICamHw>& camhw);
    void setAnalyzer(SmartPtr<RkAiqCore> analyzer);
    void setAiqCalibDb(const CamCalibDbContext_t* calibDb);
    void setLumaAnalyzer(SmartPtr<RkLumaCore> analyzer);
    XCamReturn init();
    XCamReturn prepare(uint32_t width, uint32_t height, rk_aiq_working_mode_t mode);
    XCamReturn start();
    XCamReturn stop();
    XCamReturn deInit();
    // from IspLumaListener
    XCamReturn ispLumaCb(SmartPtr<VideoBuffer>& ispLuma);
    // from IspStatsListener
    XCamReturn ispStatsCb(SmartPtr<VideoBuffer>& ispStats);
    // from IspEvtsListener
    XCamReturn ispEvtsCb(ispHwEvt_t* evt);
    // from RkAiqAnalyzerCb
    void rkAiqCalcDone(SmartPtr<RkAiqFullParamsProxy>& results);
    void rkAiqCalcFailed(const char* msg);
    // from RkLumaAnalyzerCb
    void rkLumaCalcDone(int frame_id, int count);
    void rkLumaCalcFailed(const char* msg);

protected:
    XCamReturn applyAnalyzerResult(SmartPtr<RkAiqFullParamsProxy>& results);
private:
    XCAM_DEAD_COPY (RkAiqManager);
private:
    SmartPtr<ICamHw> mCamHw;
    SmartPtr<RkAiqCore> mRkAiqAnalyzer;
    SmartPtr<RkAiqRstApplyThread> mAiqRstAppTh;
    SmartPtr<RkLumaCore> mRkLumaAnalyzer;
    rk_aiq_error_cb mErrCb;
    rk_aiq_metas_cb mMetasCb;
    const char* mSnsEntName;
    const CamCalibDbContext_t* mCalibDb;
    rk_aiq_working_mode_t mWorkingMode;
};

}; //namespace RkCam

#endif //_RK_AIQ_MANAGER_H_