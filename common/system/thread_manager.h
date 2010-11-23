#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include <vector>
#include <queue>
#include <map>

#include "semaphore.h"
#include "core.h"
#include "fixed_types.h"
#include "message_types.h"
#include "lock.h"

#include "thread_support.h"

class TileManager;

class ThreadManager
{
public:
   ThreadManager(TileManager*);
   ~ThreadManager();

   // services
   SInt32 spawnThread(thread_func_t func, void *arg);
   void joinThread(tile_id_t core_id);
   
   SInt32 spawnHelperThread(thread_func_t func, void *arg);

   void getThreadToSpawn(ThreadSpawnRequest *req);
   ThreadSpawnRequest* getThreadSpawnReq();
   void dequeueThreadSpawnReq (ThreadSpawnRequest *req);

   void terminateThreadSpawners ();

   // events
   void onThreadStart(ThreadSpawnRequest *req);
   void onThreadExit();

   // misc
   void stallThread(tile_id_t core_id);
   void resumeThread(tile_id_t core_id);
   bool isThreadRunning(tile_id_t core_id);
   bool isThreadInitializing(tile_id_t core_id);
   
   bool areAllCoresRunning();

private:

   friend class LCP;
   friend class MCP;

   void masterSpawnThread(ThreadSpawnRequest*);
   void slaveSpawnThread(ThreadSpawnRequest*);
   void masterSpawnThreadReply(ThreadSpawnRequest*);

   void masterSpawnHelperThread(ThreadSpawnRequest*);

   void masterOnThreadExit(tile_id_t core_id, UInt64 time);

   void slaveTerminateThreadSpawnerAck (tile_id_t);
   void slaveTerminateThreadSpawner ();
   void updateTerminateThreadSpawner ();

   void masterJoinThread(ThreadJoinRequest *req, UInt64 time);
   void wakeUpWaiter(tile_id_t core_id, UInt64 time);

   void insertThreadSpawnRequest (ThreadSpawnRequest *req);

   struct ThreadState
   {
      Core::State status;
      SInt32 waiter;

      ThreadState()
         : status(Core::IDLE)
         , waiter(-1)
      {} 
   };

   bool m_master;
   std::vector<ThreadState> m_thread_state;
   std::queue<ThreadSpawnRequest*> m_thread_spawn_list;
   Semaphore m_thread_spawn_sem;
   Lock m_thread_spawn_lock;

   TileManager *m_tile_manager;

   Lock m_thread_spawners_terminated_lock;
   UInt32 m_thread_spawners_terminated;
};

#endif // THREAD_MANAGER_H
