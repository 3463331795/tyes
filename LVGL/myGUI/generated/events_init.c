/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER


#endif


static void page_1_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_label_set_text(guider_ui.page_1_label_1, "LED1亮");
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        break;
    }
    default:
        break;
    }
}

static void page_1_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.page_2, guider_ui.page_2_del, &guider_ui.page_1_del, setup_scr_page_2, LV_SCR_LOAD_ANIM_OVER_LEFT, 200, 200, true, false);
        break;
    }
    default:
        break;
    }
}

void events_init_page_1 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->page_1_btn_1, page_1_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->page_1_btn_2, page_1_btn_2_event_handler, LV_EVENT_ALL, ui);
}

static void page_2_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.page_1, guider_ui.page_1_del, &guider_ui.page_2_del, setup_scr_page_1, LV_SCR_LOAD_ANIM_OVER_RIGHT, 200, 200, true, false);
        break;
    }
    default:
        break;
    }
}

void events_init_page_2 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->page_2_btn_1, page_2_btn_1_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
