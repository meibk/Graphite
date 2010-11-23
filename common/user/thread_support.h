#ifndef THREAD_SUPPORT_H
#define THREAD_SUPPORT_H

#include "fixed_types.h"

typedef SInt32 carbon_thread_t;

typedef void *(*thread_func_t)(void *);

typedef struct
{
   SInt32 msg_type;
   thread_func_t func;
   void *arg;
   SInt32 requester;
   tile_id_t tile_id;
   UInt64 time;
   bool is_helper_thread;
} ThreadSpawnRequest;

typedef struct 
{
   SInt32 msg_type;
   SInt32 sender;
   tile_id_t tile_id;
} ThreadJoinRequest;

#ifdef __cplusplus
extern "C" {
#endif

carbon_thread_t CarbonSpawnThread(thread_func_t func, void *arg);
carbon_thread_t CarbonSpawnHelperThread(thread_func_t func, void *arg);
void CarbonJoinThread(carbon_thread_t tid);

#ifdef __cplusplus
}
#endif

#endif
