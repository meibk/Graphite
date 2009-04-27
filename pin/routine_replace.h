#ifndef ROUTINE_REPLACE_H
#define ROUTINE_REPLACE_H

#include <string>
#include "pin.H"

bool replaceUserAPIFunction(RTN& rtn, string& name);

void setupCarbonSpawnThreadSpawnerStack (CONTEXT *ctx);

// Thread spawning and management
void replacementGetThreadToSpawn (CONTEXT *ctxt);
void replacementThreadStartNull (CONTEXT *ctxt);
void replacementThreadExitNull (CONTEXT *ctxt);
void replacementGetCoreId (CONTEXT *ctxt);
void replacementDequeueThreadSpawnRequest (CONTEXT *ctxt);

// Pin specific stack management
void replacementPthreadAttrInitOtherAttr (CONTEXT *ctxt);

// Carbon API
void replacementStartSimNull (CONTEXT *ctxt);
void replacementStopSimNull (CONTEXT *ctxt);
void replacementSpawnThread (CONTEXT *ctxt);
void replacementJoinThread (CONTEXT *ctxt);

void replacementMutexInit(CONTEXT *ctxt);
void replacementMutexLock(CONTEXT *ctxt);
void replacementMutexUnlock(CONTEXT *ctxt);

void replacementCondInit(CONTEXT *ctxt);
void replacementCondWait(CONTEXT *ctxt);
void replacementCondSignal(CONTEXT *ctxt);
void replacementCondBroadcast(CONTEXT *ctxt);

void replacementBarrierInit(CONTEXT *ctxt);
void replacementBarrierWait(CONTEXT *ctxt);

// CAPI
void replacement_CAPI_Initialize (CONTEXT *ctxt);
void replacement_CAPI_rank (CONTEXT *ctxt);
void replacement_CAPI_message_send_w (CONTEXT *ctxt);
void replacement_CAPI_message_receive_w (CONTEXT *ctxt);

// pthread
void replacementPthreadExitNull (CONTEXT *ctxt);

void initialize_replacement_args (CONTEXT *ctxt, ...);
void retFromReplacedRtn (CONTEXT *ctxt, ADDRINT ret_val);

#endif