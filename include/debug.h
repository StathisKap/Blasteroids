#ifndef INCLUDE_DEBUG_H_
    #define INCLUDE_DEBUG_H_

    #define LOG_LEVEL 1

    #define DEBUG_ASTEROIDS_ALIVE(func_call) do { \
        if (LOG_LEVEL == 2) { \
            printf("\033[1;31mBefore %s \033[0mat %s:%d - asteroids_alive: %d\n", #func_call, __FILE__, __LINE__, global->asteroids_alive); \
        } \
        func_call; \
        if (LOG_LEVEL == 2) { \
            printf("\033[1;31mAfter %s \033[0mat %s:%d - asteroids_alive: %d\n", #func_call, __FILE__, __LINE__, global->asteroids_alive); \
        } \
    } while (0)



    #define LOG(level, message, ...) \
            do { \
                if (LOG_LEVEL >= level) { \
                    const char* color_code = ""; \
                    switch (level) { \
                        case 1: color_code = "\033[1;33m"; break; /* yellow */ \
                        case 2: color_code = "\033[1;35m"; break; /* orange */ \
                        case 3: color_code = "\033[1;31m"; break; /* red */ \
                        default: color_code = ""; break; \
                    } \
                    printf("%s[LOG][%d] %s:%s():%d - " message "\033[0m\n", \
                        color_code, LOG_LEVEL, __FILE__, __func__, __LINE__, ##__VA_ARGS__); \
                } \
            } while (0)
#endif  // INCLUDE_DEBUG_H_
