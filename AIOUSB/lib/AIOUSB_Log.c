#include "AIOUSB_Log.h"
#include "AIOTypes.h"

#ifdef __cplusplus
namespace AIOUSB {
#endif

pthread_t cont_thread;
pthread_mutex_t message_lock = PTHREAD_MUTEX_INITIALIZER;
FILE *outfile = NULL;

#ifdef __cplusplus
}
#endif
