#include "badge.h"
#include "test.h"
#include "theme.h"
#include "attack.h"

// The parameter for the settings
static int min_strategems = 4;      
static int max_strategems = 8;   
// The actual numbers submitted to the simulator   
static int min = 4;
static int max = 4;

static lv_obj_t* last_selected_min;
static lv_obj_t* last_selected_max; 

typedef struct {
    int index;
    int state;      // 1 for min row, 2 for max row... Should make an enum but this works for now.
} button_user_data;

static button_user_data min_row_data[5];        // These two rows should likely be replaced with malloc() within the respective loops
static button_user_data max_row_data[5];        // These two rows should likely be replaced with malloc() within the respective loops

// Creates a Style
static lv_style_t selected_style;
static lv_style_t extra_style;
static lv_style_t default_style;

static void button_cb(lv_event_t *e) {
    lv_obj_t *widget        = lv_event_get_current_target(e);
    button_user_data *res   = lv_event_get_user_data(e);

    // Min Row
    if ((res->state == 1) && (widget != last_selected_min)) {
        min = res->index;
        lv_obj_add_style(widget, &selected_style, LV_PART_MAIN);
        lv_obj_add_style(last_selected_min, &default_style, LV_PART_MAIN); 
        last_selected_min = widget;
        return;
    } 
    // Max Row
    if ((res->state == 2) && (widget != last_selected_max)) {
        max = res->index;
        lv_obj_add_style(widget, &extra_style, LV_PART_MAIN);
        lv_obj_add_style(last_selected_max, &default_style, LV_PART_MAIN); 
        last_selected_max = widget;
        return;
    }
}

static void start_game_cb(lv_event_t *e) {
    attack_config_t config;
    config.stratagem_min = min;
    config.stratagem_max = max;
    config.stratagem_count = 8;
    config.tower_health = 10;
    config.player_health = 100
    attack_create
    
}

void test_page_create(lv_obj_t *parent) {
    // Clear the content area
    lv_obj_clean(parent);

    // Container to hold the grid of stats
    lv_obj_t *container = lv_obj_create(parent);
    lv_obj_set_size(container, lv_pct(100), lv_pct(100));
    lv_obj_set_style_bg_opa(container, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_width(container, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(container, 0, LV_PART_MAIN);
    lv_obj_remove_flag(container, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_scrollbar_mode(container, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(container, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    // Create a grid layout
    lv_obj_t *grid = lv_obj_create(container);
    lv_obj_set_size(grid, lv_pct(100), lv_pct(100));
    lv_obj_set_style_pad_all(grid, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(grid, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_width(grid, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(grid, 0, LV_PART_MAIN);
    lv_obj_set_layout(grid, LV_LAYOUT_GRID);

    // Create a grid layout
    static lv_coord_t column_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[]    = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    lv_obj_set_grid_dsc_array(grid, column_dsc, row_dsc);

    // Minimun Difficulty Label
    lv_obj_t *title = lv_label_create(grid);
    lv_label_set_text(title, "Stratagem Simulator");
    lv_obj_set_style_text_font(title, &clarity_16, LV_PART_MAIN);
    lv_obj_set_style_text_color(title, lv_color_hex(WHITE), LV_PART_MAIN);
    lv_obj_set_grid_cell(title, LV_GRID_ALIGN_START, 0, 6, LV_GRID_ALIGN_CENTER, 0, 1);

    // Minimun Difficulty Label
    lv_obj_t *min_label = lv_label_create(grid);
    lv_label_set_text(min_label, "Min:");
    lv_obj_set_style_text_font(min_label, &clarity_16, LV_PART_MAIN);
    lv_obj_set_style_text_color(min_label, lv_color_hex(WHITE), LV_PART_MAIN);
    lv_obj_set_grid_cell(min_label, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, 1, 1);

    // ~~ Stylin' Section ~~ //
    lv_style_init(&selected_style);
    lv_style_set_bg_color(&selected_style, lv_color_hex(GREEN_MAIN));
    lv_style_init(&default_style);
    lv_style_set_bg_color(&default_style, lv_color_hex(BLUE_MAIN));
    lv_style_init(&extra_style);
    lv_style_set_bg_color(&extra_style, lv_color_hex(RED_MAIN));
    
    // ~~ Minimum Selector Row ~~ //
    bool first = true;
    for (int i = 0; i <= (max_strategems-min_strategems); i++) {
        lv_obj_t *button  = lv_btn_create(grid);
        lv_obj_t *button_label = lv_label_create(button);
                             
        min_row_data[i].index = min_strategems+i;                       // Helps us to set min/max accurately
        min_row_data[i].state = 1;                                      // Helps us know which row to modify in the callback
        char res[2];
        sprintf(res, "%d", min_strategems+i);                           // Converts the number to a string
        if (first) 
        {                                                               // Adds the style to the first button
            last_selected_min = button;
            lv_obj_add_style(button, &selected_style, LV_PART_MAIN);
            first = false;
        }
        lv_label_set_text(button_label, res);
        lv_obj_set_style_text_font(button_label, &clarity_16, LV_PART_MAIN);
        lv_obj_set_style_text_color(button_label, lv_color_hex(WHITE), LV_PART_MAIN);
        lv_obj_add_event_cb(button, button_cb, LV_EVENT_CLICKED, &min_row_data[i]);                 
        lv_obj_set_grid_cell(button, LV_GRID_ALIGN_START, i+1, 1, LV_GRID_ALIGN_CENTER, 1, 1); 
    }

    // Maximum Difficult Label
    lv_obj_t *max_label = lv_label_create(grid);
    lv_label_set_text(max_label, "Max: ");
    lv_obj_set_style_text_font(max_label, &clarity_16, LV_PART_MAIN);
    lv_obj_set_style_text_color(max_label, lv_color_hex(WHITE), LV_PART_MAIN);
    lv_obj_set_grid_cell(max_label, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, 2, 1);

    // ~~ Maximum Selector Row ~~ //
    first = true;
    for (int i = 0; i <= (max_strategems-min_strategems); i++) {
        lv_obj_t *button  = lv_btn_create(grid);
        lv_obj_t *button_label = lv_label_create(button);

        max_row_data[i].index = min_strategems+i;                   // Helps us to set min/max accurately
        max_row_data[i].state = 2;                                  // Helps us know which row to modify in the callback
        char res[2];
        sprintf(res, "%d", min_strategems+i);                       // Converts the number to a string
        if (first) 
        {                                                           // Adds the style to the first button
            last_selected_max = button;
            lv_obj_add_style(button, &extra_style, LV_PART_MAIN);
            first = false;
        }
        lv_label_set_text(button_label, res);
        lv_obj_set_style_text_font(button_label, &clarity_16, LV_PART_MAIN);
        lv_obj_set_style_text_color(button_label, lv_color_hex(WHITE), LV_PART_MAIN);
        lv_obj_add_event_cb(button, button_cb, LV_EVENT_CLICKED, &max_row_data[i]);
        lv_obj_set_grid_cell(button, LV_GRID_ALIGN_START, i+1, 1, LV_GRID_ALIGN_CENTER, 2, 1);
    }

    // ~~ Begin Button ~~ //
    lv_obj_t *start_button = lv_btn_create(grid);
    lv_obj_t *button_label = lv_label_create(start_button);
    lv_label_set_text(button_label, "BEGIN");
    lv_obj_set_style_text_font(button_label, &clarity_16, LV_PART_MAIN);
    lv_obj_set_style_text_color(button_label, lv_color_hex(WHITE), LV_PART_MAIN);
    lv_obj_set_grid_cell(start_button, LV_ALIGN_CENTER, 0, 6, LV_ALIGN_CENTER, 3, 1);
}
