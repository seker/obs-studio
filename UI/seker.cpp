#include "seker.h"

#ifdef _DEBUG

#define B2S(b)  (b ? "true" : "false")

void log_all_item_types(void)
{
    size_t idx = 0;
    const char *id = NULL;
    const char *unversioned_id = NULL;
    
    // 1. enum all obs_source: input, filter, transition, scene
    blog(LOG_INFO, "  1. enum all obs_source: input, filter, transition, scene");
    
    idx = 0;
    blog(LOG_INFO, "    1.0. obs_enum_source_types()");
    while(obs_enum_source_types(idx++,  &id)) {
        blog(LOG_INFO, "      [%02zd] id:%s, name:%s", idx, id, obs_source_get_display_name(id));
    }

    idx = 0;
    blog(LOG_INFO, "    1.1. obs_enum_input_types()");
    while (obs_enum_input_types(idx++,  &id)) {
        blog(LOG_INFO, "      [%02zd] id:%s, name:%s", idx, id, obs_source_get_display_name(id));
    }
    
    idx = 0;
    blog(LOG_INFO, "    1.2. obs_enum_input_types2()");
    while (obs_enum_input_types2(idx++,  &id, &unversioned_id)) {
        blog(LOG_INFO, "      [%02zd] id:%s, name:%s, unversioned_id:%s", idx, id, obs_source_get_display_name(id), unversioned_id);
    }
    
    idx = 0;
    blog(LOG_INFO, "    1.3. obs_enum_filter_types()");
    while (obs_enum_filter_types(idx++,  &id)) {
        blog(LOG_INFO, "      [%02zd] id:%s, name:%s", idx, id, obs_source_get_display_name(id));
    }
    
    idx = 0;
    blog(LOG_INFO, "    1.4. obs_enum_transition_types()");
    while (obs_enum_transition_types(idx++,  &id)) {
        blog(LOG_INFO, "      [%02zd] id:%s, name:%s", idx, id, obs_source_get_display_name(id));
    }
    
    // 2. enum all output
    blog(LOG_INFO, "  2. enum all output");
    
    idx = 0;
    blog(LOG_INFO, "    2.0. obs_enum_output_types()");
    while(obs_enum_output_types(idx++,  &id)) {
        blog(LOG_INFO, "      [%02zd] id:%s, name:%s", idx, id, obs_output_get_display_name(id));
    }
    
    // 3. enum all encoder
    blog(LOG_INFO, "  3. enum all encoder");
    
    idx = 0;
    blog(LOG_INFO, "    3.0. obs_enum_encoder_types()");
    while(obs_enum_encoder_types(idx++,  &id)) {
        blog(LOG_INFO, "      [%02zd] id:%s, name:%s", idx, id, obs_encoder_get_display_name(id));
    }
    
    // 4. enum all service
    blog(LOG_INFO, "  4. enum all service");
    
    idx = 0;
    blog(LOG_INFO, "    4.0. obs_enum_service_types()");
    while(obs_enum_service_types(idx++,  &id)) {
        blog(LOG_INFO, "      [%02zd] id:%s, name:%s", idx, id, obs_service_get_display_name(id));
    }
}

bool enum_proc_sources(void *thiz, obs_source_t *source)
{
	UNUSED_PARAMETER(thiz);

	if (OBS_SOURCE_TYPE_INPUT == obs_source_get_type(source)) {
		if (OBS_SOURCE_ASYNC_VIDEO == (obs_source_get_output_flags(source) & OBS_SOURCE_ASYNC_VIDEO)) {
			const char *name = obs_source_get_name(source);
			double active_fps = obs_source_get_active_fps(source);
			blog(LOG_INFO, "%s : fps=%lf", name, active_fps);
		}
	}

	return true;
}

void log_all_async_video_source_active_fps(void)
{
    blog(LOG_INFO, "------------ source_active_fps begin --------------");
    obs_enum_sources(enum_proc_sources, nullptr);
    blog(LOG_INFO, "------------ source_active_fps end   --------------");
}

// obs-properties.h
const char* PROP_TYPE_NAME[] = {
    "OBS_PROPERTY_INVALID",
    "OBS_PROPERTY_BOOL",
    "OBS_PROPERTY_INT",
    "OBS_PROPERTY_FLOAT",
    "OBS_PROPERTY_TEXT",
    "OBS_PROPERTY_PATH",
    "OBS_PROPERTY_LIST",
    "OBS_PROPERTY_COLOR",
    "OBS_PROPERTY_BUTTON",
    "OBS_PROPERTY_FONT",
    "OBS_PROPERTY_EDITABLE_LIST",
    "OBS_PROPERTY_FRAME_RATE",
    "OBS_PROPERTY_GROUP",
    "OBS_PROPERTY_COLOR_ALPHA",
};

const char* NUMBER_TYPE_NAME[] = {
    "OBS_NUMBER_SCROLLER",
    "OBS_NUMBER_SLIDER",
};

const char* TEXT_TYPE_NAME[] = {
    "OBS_TEXT_DEFAULT",
    "OBS_TEXT_PASSWORD",
    "OBS_TEXT_MULTILINE",
};

const char* PATH_TYPE_NAME[] = {
    "OBS_PATH_FILE",
    "OBS_PATH_FILE_SAVE",
    "OBS_PATH_DIRECTORY",
};

const char* COMBO_FORMAT_NAME[] = {
    "OBS_COMBO_FORMAT_INVALID",
    "OBS_COMBO_FORMAT_INT",
    "OBS_COMBO_FORMAT_FLOAT",
    "OBS_COMBO_FORMAT_STRING",
};

const char* COMBO_TYPE_NAME[] = {
    "OBS_COMBO_TYPE_INVALID",
    "OBS_COMBO_TYPE_EDITABLE",
    "OBS_COMBO_TYPE_LIST",
};

const char* EDITABLE_LIST_TYPE_NAME[] = {
    "OBS_EDITABLE_LIST_TYPE_STRINGS",
    "OBS_EDITABLE_LIST_TYPE_FILES",
    "OBS_EDITABLE_LIST_TYPE_FILES_AND_URLS",
};

const char* GROUP_TYPE_NAME[] = {
    "OBS_COMBO_INVALID",
    "OBS_GROUP_NORMAL",
    "OBS_GROUP_CHECKABLE",
};

const char* BUTTON_TYPE_NAME[] = {
    "OBS_BUTTON_DEFAULT",
    "OBS_BUTTON_URL",
};

void log_property(obs_property_t *property, uint32_t index)
{
    const char *name = obs_property_name(property);
    const char *description = obs_property_description(property);
    const char *long_description = obs_property_long_description(property);
    bool enable = obs_property_enabled(property);
    bool visible = obs_property_visible(property);
    obs_property_type type = obs_property_get_type(property);
    blog(LOG_INFO, "    [%u] property name: %s, type: %s, enable: %s, visible: %s, description: %s, long_description: %s",
         index, name, PROP_TYPE_NAME[type], B2S(enable), B2S(visible), description, long_description);
    
    switch (type) {
        case OBS_PROPERTY_INVALID:
            return;
        case OBS_PROPERTY_BOOL:
            break;
        case OBS_PROPERTY_INT: {
            int int_min = obs_property_int_min(property);
            int int_max = obs_property_int_max(property);
            int int_step = obs_property_int_step(property);
            obs_number_type int_type = obs_property_int_type(property);
            const char *int_suffix = obs_property_int_suffix(property);
            blog(LOG_INFO, "        int_min: %d, int_max:%d, int_step:%d, int_type:%s, int_suffix:%s",
                 int_min, int_max, int_step, NUMBER_TYPE_NAME[int_type], int_suffix);
        }
            break;
        case OBS_PROPERTY_FLOAT: {
            double float_min = obs_property_float_min(property);
            double float_max = obs_property_float_max(property);
            double float_step = obs_property_float_step(property);
            obs_number_type float_type = obs_property_float_type(property);
            const char *float_suffix = obs_property_float_suffix(property);
            blog(LOG_INFO, "        float_min: %lf, float_max:%lf, float_step:%lf, float_type:%s, float_suffix:%s",
                 float_min, float_max, float_step, NUMBER_TYPE_NAME[float_type], float_suffix);
      }
            break;
        case OBS_PROPERTY_TEXT: {
            obs_text_type text_type = obs_property_text_type(property);
            bool text_monospace = obs_property_text_monospace(property);
            blog(LOG_INFO, "        text_type: %s, text_monospace:%s",
                 TEXT_TYPE_NAME[text_type], B2S(text_monospace));
        }
            break;
        case OBS_PROPERTY_PATH: {
            obs_path_type path_type = obs_property_path_type(property);
            const char *path_filter = obs_property_path_filter(property);
            const char *path_default_path = obs_property_path_default_path(property);
            blog(LOG_INFO, "        path_type: %s, path_filter:%s, path_default_path:%s",
                 PATH_TYPE_NAME[path_type], path_filter, path_default_path);
        }
            break;
        case OBS_PROPERTY_LIST: {
            obs_combo_type list_type = obs_property_list_type(property);
            obs_combo_format list_format = obs_property_list_format(property);
            size_t list_item_count = obs_property_list_item_count(property);
            blog(LOG_INFO, "        list_type: %s, list_format:%s, list_item_count=%zd",
                 COMBO_TYPE_NAME[list_type], COMBO_FORMAT_NAME[list_format], list_item_count);
            
            for (size_t idx = 0; idx < list_item_count; idx ++) {
                const char *list_item_name = obs_property_list_item_name(property, idx);
                switch(list_format) {
                    case OBS_COMBO_FORMAT_INT: {
                        long long list_item_int = obs_property_list_item_int(property, idx);
                        blog(LOG_INFO, "        [%u.%zd] list_item_name:%s, list_item_int:%lld", index, idx + 1, list_item_name, list_item_int);
                    }
                        break;
                    case OBS_COMBO_FORMAT_FLOAT: {
                        double list_item_float = obs_property_list_item_float(property, idx);
                        blog(LOG_INFO, "        [%u.%zd] list_item_name:%s, list_item_float:%lf", index, idx + 1, list_item_name, list_item_float);
                    }
                        break;
                    case OBS_COMBO_FORMAT_STRING: {
                        const char *list_item_string = obs_property_list_item_string(property, idx);
                        blog(LOG_INFO, "        [%u.%zd] list_item_name:%s, list_item_string:%s", index, idx + 1, list_item_name, list_item_string);
                    }
                        break;
                    case OBS_COMBO_FORMAT_INVALID:
                    default:
                        break;
                }
            }
        }
            break;
        case OBS_PROPERTY_COLOR:
            break;
        case OBS_PROPERTY_FONT:
            break;
        case OBS_PROPERTY_BUTTON: {
            obs_button_type button_type = obs_property_button_type(property);
            const char *button_url = obs_property_button_url(property);
            blog(LOG_INFO, "        button_type: %s, button_url:%s", BUTTON_TYPE_NAME[button_type], button_url);
        }
            break;
        case OBS_PROPERTY_EDITABLE_LIST: {
            obs_editable_list_type editable_list_type = obs_property_editable_list_type(property);
            const char *editable_list_filter = obs_property_editable_list_filter(property);
            const char *editable_list_default_path = obs_property_editable_list_default_path(property);
            blog(LOG_INFO, "        editable_list_type: %s, editable_list_filter:%s, editable_list_default_path:%s",
                EDITABLE_LIST_TYPE_NAME[editable_list_type], editable_list_filter, editable_list_default_path);
        }
            break;
        case OBS_PROPERTY_FRAME_RATE: {
            size_t frame_rate_options_count = obs_property_frame_rate_options_count(property);
            blog(LOG_INFO, "        frame_rate_options_count: %zd", frame_rate_options_count);
            for (size_t idx = 0; idx < frame_rate_options_count; idx ++) {
                const char *frame_rate_option_name = obs_property_frame_rate_option_name(property, idx);
                const char *frame_rate_option_description = obs_property_frame_rate_option_description(property, idx);
                blog(LOG_INFO, "        [%u.%zd] frame_rate_option_name:%s, frame_rate_option_description:%s",
                     index, idx + 1, frame_rate_option_name, frame_rate_option_description);
            }

            size_t frame_rate_fps_ranges_count = obs_property_frame_rate_fps_ranges_count(property);
            blog(LOG_INFO, "        frame_rate_fps_ranges_count: %zd", frame_rate_fps_ranges_count);
            for (size_t idx = 0; idx <= frame_rate_fps_ranges_count; idx ++) {
                media_frames_per_second frame_rate_fps_range_min = obs_property_frame_rate_fps_range_min(property, idx);
                double min_fps = media_frames_per_second_to_fps(frame_rate_fps_range_min);
                media_frames_per_second frame_rate_fps_range_max = obs_property_frame_rate_fps_range_max(property, idx);
                double max_fps = media_frames_per_second_to_fps(frame_rate_fps_range_max);
                blog(LOG_INFO, "        [%u.%zd] frame_rate_fps_range_min:[%u,%u:%lf], frame_rate_fps_range_max:[%u,%u:%lf]",
                     index, idx + 1,
                     frame_rate_fps_range_min.denominator, frame_rate_fps_range_min.numerator, min_fps,
                     frame_rate_fps_range_max.denominator, frame_rate_fps_range_max.numerator, max_fps);
            }
        }
            break;
        case OBS_PROPERTY_GROUP: {
            obs_group_type group_type = obs_property_group_type(property);
            blog(LOG_INFO, "    [%u] group_type: %s", index, GROUP_TYPE_NAME[group_type]);
        }
            break;
        case OBS_PROPERTY_COLOR_ALPHA:
            break;
        default:
            break;
        }
}

void log_all_property(obs_source_t *source)
{
    obs_properties_t *properties = obs_source_properties(source);
    uint32_t flags = obs_properties_get_flags(properties);
    const char *source_name = obs_source_get_name(source);
    blog(LOG_INFO, "source name: %s, properties flags: %u", source_name, flags);
    
    uint32_t index = 0;
    obs_property_t *property = obs_properties_first(properties);
    while (property) {
        index ++;
        log_property(property, index);
        obs_property_next(&property);
    }
}
#endif
