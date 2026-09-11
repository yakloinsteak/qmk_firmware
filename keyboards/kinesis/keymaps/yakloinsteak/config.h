#pragma once

// keyboards/kinesis/config.h sets its own mousekey tuning; users/yakloinsteak/config.h
// is included after this and redefines these, which is -Werror. Drop the board's.
#undef MOUSEKEY_DELAY
#undef MOUSEKEY_INTERVAL
#undef MOUSEKEY_MAX_SPEED
#undef MOUSEKEY_TIME_TO_MAX
