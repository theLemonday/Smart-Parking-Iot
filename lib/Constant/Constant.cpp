#include <Constant.h>

#if defined(DEBUG)

void SetupBaudRate() { Serial.begin(BAUD_RATE); }

#endif  // DEBUG