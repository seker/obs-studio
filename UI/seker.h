#pragma once

#include <obs.h>

#ifdef _DEBUG
void log_all_item_types(void);
void log_all_async_video_source_active_fps(void);
void log_all_property(obs_source_t *source);
void log_all_settting(obs_source_t *source);
#endif
