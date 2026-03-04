#ifndef THREADS_H_
#define THREADS_H_

#include "defs.h"
#include "error.h"
#include <pthread.h>

typedef pthread_t Thread;
typedef pthread_mutex_t Mutex;
typedef pthread_cond_t CondVar;
typedef pthread_rwlock_t RWLock;
typedef pthread_key_t ThreadLocalKey;

static inline void Thread_create (Thread *t, void *(*func) (void *), void *arg,
                                  const char *file, u32 line);
static inline void Thread_join (Thread t, void **res, const char *file,
                                u32 line);
static inline void Thread_detach (Thread t, const char *file, u32 line);
static inline void Mutex_init (Mutex *m, const char *file, u32 line);
static inline void Mutex_lock (Mutex *m, const char *file, u32 line);
static inline void Mutex_unlock (Mutex *m, const char *file, u32 line);
static inline void Mutex_destroy (Mutex *m, const char *file, u32 line);
static inline void CondVar_init (CondVar *c, const char *file, u32 line);
static inline void CondVar_wait (CondVar *c, Mutex *m, const char *file,
                                 u32 line);
static inline void CondVar_signal (CondVar *c, const char *file, u32 line);
static inline void CondVar_broadcast (CondVar *c, const char *file, u32 line);
static inline void CondVar_destroy (CondVar *c, const char *file, u32 line);
static inline void RWLock_init (RWLock *rw, const char *file, u32 line);
static inline void RWLock_rdlock (RWLock *rw, const char *file, u32 line);
static inline void RWLock_wrlock (RWLock *rw, const char *file, u32 line);
static inline void RWLock_unlock (RWLock *rw, const char *file, u32 line);
static inline void RWLock_destroy (RWLock *rw, const char *file, u32 line);
static inline void TLS_key_create (ThreadLocalKey *key,
                                   void (*destructor) (void *),
                                   const char *file, u32 line);
static inline void TLS_set (ThreadLocalKey key, void *value, const char *file,
                            u32 line);
static inline void *TLS_get (ThreadLocalKey key, const char *file, u32 line);
static inline void TLS_key_delete (ThreadLocalKey key, const char *file,
                                   u32 line);

#define THREAD_CREATE(t, func, arg)                                           \
  Thread_create (&(t), (func), (arg), __FILE__, __LINE__)

#define THREAD_JOIN(t, res) Thread_join ((t), (res), __FILE__, __LINE__)

#define THREAD_DETACH(t) Thread_detach ((t), __FILE__, __LINE__)

#define MUTEX_INIT(m) Mutex_init (&(m), __FILE__, __LINE__)

#define MUTEX_LOCK(m) Mutex_lock (&(m), __FILE__, __LINE__)

#define MUTEX_UNLOCK(m) Mutex_unlock (&(m), __FILE__, __LINE__)

#define MUTEX_DESTROY(m) Mutex_destroy (&(m), __FILE__, __LINE__)

#define CONDVAR_INIT(c) CondVar_init (&(c), __FILE__, __LINE__)

#define CONDVAR_WAIT(c, m) CondVar_wait (&(c), &(m), __FILE__, __LINE__)

#define CONDVAR_SIGNAL(c) CondVar_signal (&(c), __FILE__, __LINE__)

#define CONDVAR_BROADCAST(c) CondVar_broadcast (&(c), __FILE__, __LINE__)

#define CONDVAR_DESTROY(c) CondVar_destroy (&(c), __FILE__, __LINE__)

#define RWLOCK_INIT(rw) RWLock_init (&(rw), __FILE__, __LINE__)

#define RWLOCK_RDLOCK(rw) RWLock_rdlock (&(rw), __FILE__, __LINE__)

#define RWLOCK_WRLOCK(rw) RWLock_wrlock (&(rw), __FILE__, __LINE__)

#define RWLOCK_UNLOCK(rw) RWLock_unlock (&(rw), __FILE__, __LINE__)

#define RWLOCK_DESTROY(rw) RWLock_destroy (&(rw), __FILE__, __LINE__)

#define TLS_KEY_CREATE(key, destructor)                                       \
  TLS_key_create (&(key), (destructor), __FILE__, __LINE__)

#define TLS_SET(key, value) TLS_set ((key), (value), __FILE__, __LINE__)

#define TLS_GET(key) TLS_get ((key), __FILE__, __LINE__)

#define TLS_KEY_DELETE(key) TLS_key_delete ((key), __FILE__, __LINE__)

static inline void
Thread_create (Thread *t, void *(*func) (void *), void *arg, const char *file,
               u32 line)
{
  assert (t && func);
  if (pthread_create (t, NULL, func, arg) != 0)
    panic_fl (file, line, "Thread creation failed");
}

static inline void
Thread_join (Thread t, void **res, const char *file, u32 line)
{
  if (pthread_join (t, res) != 0)
    panic_fl (file, line, "Thread join failed");
}

static inline void
Thread_detach (Thread t, const char *file, u32 line)
{
  if (pthread_detach (t) != 0)
    panic_fl (file, line, "Thread detach failed");
}

static inline void
Mutex_init (Mutex *m, const char *file, u32 line)
{
  assert (m);
  if (pthread_mutex_init (m, NULL) != 0)
    panic_fl (file, line, "Mutex init failed");
}

static inline void
Mutex_lock (Mutex *m, const char *file, u32 line)
{
  assert (m);
  if (pthread_mutex_lock (m) != 0)
    panic_fl (file, line, "Mutex lock failed");
}

static inline void
Mutex_unlock (Mutex *m, const char *file, u32 line)
{
  assert (m);
  if (pthread_mutex_unlock (m) != 0)
    panic_fl (file, line, "Mutex unlock failed");
}

static inline void
Mutex_destroy (Mutex *m, const char *file, u32 line)
{
  assert (m);
  if (pthread_mutex_destroy (m) != 0)
    panic_fl (file, line, "Mutex destroy failed");
}

static inline void
CondVar_init (CondVar *c, const char *file, u32 line)
{
  assert (c);
  if (pthread_cond_init (c, NULL) != 0)
    panic_fl (file, line, "CondVar init failed");
}

static inline void
CondVar_wait (CondVar *c, Mutex *m, const char *file, u32 line)
{
  assert (c && m);
  if (pthread_cond_wait (c, m) != 0)
    panic_fl (file, line, "CondVar wait failed");
}

static inline void
CondVar_signal (CondVar *c, const char *file, u32 line)
{
  assert (c);
  if (pthread_cond_signal (c) != 0)
    panic_fl (file, line, "CondVar signal failed");
}

static inline void
CondVar_broadcast (CondVar *c, const char *file, u32 line)
{
  assert (c);
  if (pthread_cond_broadcast (c) != 0)
    panic_fl (file, line, "CondVar broadcast failed");
}

static inline void
CondVar_destroy (CondVar *c, const char *file, u32 line)
{
  assert (c);
  if (pthread_cond_destroy (c) != 0)
    panic_fl (file, line, "CondVar destroy failed");
}

static inline void
RWLock_init (RWLock *rw, const char *file, u32 line)
{
  assert (rw);
  if (pthread_rwlock_init (rw, NULL) != 0)
    panic_fl (file, line, "RWLock init failed");
}

static inline void
RWLock_rdlock (RWLock *rw, const char *file, u32 line)
{
  assert (rw);
  if (pthread_rwlock_rdlock (rw) != 0)
    panic_fl (file, line, "RWLock rdlock failed");
}

static inline void
RWLock_wrlock (RWLock *rw, const char *file, u32 line)
{
  assert (rw);
  if (pthread_rwlock_wrlock (rw) != 0)
    panic_fl (file, line, "RWLock wrlock failed");
}

static inline void
RWLock_unlock (RWLock *rw, const char *file, u32 line)
{
  assert (rw);
  if (pthread_rwlock_unlock (rw) != 0)
    panic_fl (file, line, "RWLock unlock failed");
}

static inline void
RWLock_destroy (RWLock *rw, const char *file, u32 line)
{
  assert (rw);
  if (pthread_rwlock_destroy (rw) != 0)
    panic_fl (file, line, "RWLock destroy failed");
}

static inline void
TLS_key_create (ThreadLocalKey *key, void (*destructor) (void *),
                const char *file, u32 line)
{
  assert (key);
  if (pthread_key_create (key, destructor) != 0)
    panic_fl (file, line, "TLS key create failed");
}

static inline void
TLS_set (ThreadLocalKey key, void *value, const char *file, u32 line)
{
  if (pthread_setspecific (key, value) != 0)
    panic_fl (file, line, "TLS set failed");
}

static inline void *
TLS_get (ThreadLocalKey key, const char *file, u32 line)
{
  return pthread_getspecific (key);
}

static inline void
TLS_key_delete (ThreadLocalKey key, const char *file, u32 line)
{
  if (pthread_key_delete (key) != 0)
    panic_fl (file, line, "TLS key delete failed");
}

#endif // THREADS_H_
