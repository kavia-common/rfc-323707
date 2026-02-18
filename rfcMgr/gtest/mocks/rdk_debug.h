/*##############################################################################
 # If not stated otherwise in this file or this component's LICENSE file the
 # following copyright and licenses apply:
 #
 # Copyright 2024 RDK Management
 #
 # Licensed under the Apache License, Version 2.0 (the "License");
 # you may not use this file except in compliance with the License.
 # You may obtain a copy of the License at
 #
 # http://www.apache.org/licenses/LICENSE-2.0
 #
 # Unless required by applicable law or agreed to in writing, software
 # distributed under the License is distributed on an "AS IS" BASIS,
 # WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 # See the License for the specific language governing permissions and
 # limitations under the License.
 ##############################################################################
 */

#ifndef RDK_DEBUG_H_
#define RDK_DEBUG_H_

#include <stdio.h>

#define LOG_RFCMGR "LOG.RDK.RFCMGR"
#define RDK_LOG_TRACE1 1
#define RDK_LOG_DEBUG 2
#define RDK_LOG_INFO 3
#define RDK_LOG_WARN 4
#define RDK_LOG_ERROR 5

/**
 * Minimal RDK common return codes expected by production code paths.
 * We define only what's required for unit-test compilation/linking.
 */
#define RDK_SUCCESS 0

/**
 * Minimal set of extended logger enums used by rfcMgr/rfc_manager.cpp.
 * Values are not important for unit tests; they just need to compile.
 *
 * NOTE: The build error referenced an earlier broken version where enum
 * entries incorrectly ended with ';' instead of ',' (or nothing).
 */
typedef enum
{
    /* Trailing comma is intentional (avoids enum-item parsing issues). */
    RDKLOG_OUTPUT_CONSOLE = 0,
} rdk_logger_ext_output_t;

typedef enum
{
    /* Trailing comma is intentional (avoids enum-item parsing issues). */
    RDKLOG_FORMAT_WITH_TS = 0,
} rdk_logger_ext_format_t;

/**
 * Configuration struct used by rdk_logger_ext_init() in rfc_manager.cpp.
 * This must match the field names used in designated initializers:
 *   .pModuleName, .loglevel, .output, .format, .pFilePolicy
 */
typedef struct
{
    const char* pModuleName;
    int loglevel;
    rdk_logger_ext_output_t output;
    rdk_logger_ext_format_t format;
    void* pFilePolicy;
} rdk_logger_ext_config_t;

#define rdk_logger_init(DEBUG_INI_NAME) ;

/**
 * Initialize the extended logger.
 * In unit tests we stub this out to always succeed.
 */
// PUBLIC_INTERFACE
static inline int rdk_logger_ext_init(const rdk_logger_ext_config_t* /*config*/)
{
    /** Stubbed gtest implementation of rdk_logger_ext_init(). */
    return RDK_SUCCESS;
}

/* The macro to convert RDK_LOG to printf */
#define RDK_LOG(level, module, ...)          \
    do {                                     \
        if ((level == RDK_LOG_DEBUG)) {      \
            printf("DEBUG: %s: ", module);   \
        } else if ((level == RDK_LOG_INFO)) {\
            printf("INFO: %s: ", module);    \
        } else if ((level == RDK_LOG_ERROR)) {\
            printf("ERROR: %s: ", module);   \
        }                                    \
        printf(__VA_ARGS__);                 \
    } while (0)

#endif
