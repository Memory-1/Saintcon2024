#pragma once

typedef struct {
    uint32_t version;
    bool hw_pass;                     // Initial hardware tests passed
    bool registered;                  // User has registered
    badge_wrist_t wrist;              // Wrist preference
    uint8_t brightness;               // Display brightness preference
    uint32_t screen_timeout;          // Screen timeout in seconds
    int id;                           // Badge ID from the server
    char handle[BADGE_HANDLE_LENGTH]; // User handle
    int xp;                           // Experience points
    int level;                        // User level
    bool enabled;                     // Badge enabled
    bool badge_team;                  // Badge team member
    bool staff;                       // Staff member
    bool blackbadge;                  // Black badge
    bool can_level;                   // Can level up others
    bool custom_wifi;                 // Enable setting custom WiFi SSID and password
    char community[64];               // Community name if user is staff
    char api_url[64];                 // Allows for custom api url setting
    int community_levels;             // The number of levels the user has in their community
    int coins;                        // The number of coins the user has
} badge_config_v6_t;
// clang-format off
#define BADGE_DEFAULTS_V6                     \
    (badge_config_v6_t){                      \
        .version          = 6,                \
        .hw_pass          = false,            \
        .registered       = false,            \
        .wrist            = BADGE_WRIST_LEFT, \
        .brightness       = LCD_BACKLIGHT_ON, \
        .screen_timeout   = 30,               \
        .id               = 0,                \
        .handle           = "",               \
        .xp               = 0,                \
        .level            = 0,                \
        .enabled          = false,            \
        .badge_team       = false,            \
        .staff            = false,            \
        .blackbadge       = false,            \
        .can_level        = false,            \
        .custom_wifi      = true,             \
        .community        = "",               \
        .api_url          = "127.0.0.1",      \
        .community_levels = 0,                \
        .coins            = 0,                \
    }
// clang-format on
