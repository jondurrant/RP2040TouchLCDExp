/*
 * Widgets.c
 *
 *  Created on: 20 Aug 2024
 *      Author: jondurrant
 */

#include "lvgl.h"
#include "LVGL_example.h"


#define NUM_ARCS 5
void * arcs[NUM_ARCS];
uint16_t arcsStart[NUM_ARCS] = {0, 45, 90, 135, 180};

static void set_angle(void * obj, int32_t v)
{
   // lv_arc_set_value(obj, v);
	for (int i=0; i < NUM_ARCS; i++){
		uint16_t r = arcsStart[i];
		r = (r + v) % 360;
		if ( (i % 2) == 0){
			lv_arc_set_rotation(arcs[i], r);
		} else {
			lv_arc_set_rotation(arcs[i], 360 - r);
		}
	}
}


/********************************************************************************
function:	Initializes the layout of LVGL widgets
parameter:
********************************************************************************/
void Widgets_Init(void)
{
	 lv_group_t *group = LVGL_get_group();

    // /*Style Config*/
    static lv_style_t style_base;
    lv_style_init(&style_base);
    lv_style_set_bg_color(&style_base, lv_palette_main(LV_PALETTE_LIGHT_GREEN));
    lv_style_set_border_color(&style_base, lv_palette_darken(LV_PALETTE_LIGHT_GREEN, 3));
    lv_style_set_border_width(&style_base, 2);
    lv_style_set_radius(&style_base, 10);
    lv_style_set_shadow_width(&style_base, 10);
    lv_style_set_shadow_ofs_y(&style_base, 5);
    lv_style_set_shadow_opa(&style_base, LV_OPA_50);
    lv_style_set_text_color(&style_base, lv_color_white());
    lv_style_set_width(&style_base, 100);
    lv_style_set_height(&style_base, LV_SIZE_CONTENT);

    static lv_style_t style_press;
    lv_style_init(&style_press);
    lv_style_set_bg_color(&style_press, lv_palette_main(LV_PALETTE_GREEN));
    lv_style_set_border_color(&style_press, lv_palette_darken(LV_PALETTE_GREEN, 3));
    lv_style_set_border_width(&style_press, 2);
    lv_style_set_radius(&style_press, 10);
    lv_style_set_shadow_width(&style_press, 10);
    lv_style_set_shadow_ofs_y(&style_press, 5);
    lv_style_set_shadow_opa(&style_press, LV_OPA_50);
    lv_style_set_text_color(&style_press, lv_color_white());
    lv_style_set_width(&style_press, 100);
    lv_style_set_height(&style_press, LV_SIZE_CONTENT);

    static lv_style_t style_slider;
    lv_style_set_bg_color(&style_slider, lv_palette_main(LV_PALETTE_ORANGE));
    lv_style_set_border_color(&style_slider, lv_palette_darken(LV_PALETTE_ORANGE, 3));

    static lv_style_t style_indic;
    lv_style_init(&style_indic);
    lv_style_set_bg_color(&style_indic, lv_palette_lighten(LV_PALETTE_DEEP_ORANGE, 3));
    lv_style_set_bg_grad_color(&style_indic, lv_palette_main(LV_PALETTE_DEEP_ORANGE));
    lv_style_set_bg_grad_dir(&style_indic, LV_GRAD_DIR_HOR);

    static lv_style_t style_indic_pr;
    lv_style_init(&style_indic_pr);
    lv_style_set_shadow_color(&style_indic_pr, lv_palette_main(LV_PALETTE_DEEP_ORANGE));
    lv_style_set_shadow_width(&style_indic_pr, 10);
    lv_style_set_shadow_spread(&style_indic_pr, 3);

    static lv_style_t style_sw;
    lv_style_init(&style_sw);
    lv_style_set_bg_opa(&style_sw, LV_OPA_COVER);
    lv_style_set_bg_color(&style_sw, lv_palette_lighten(LV_PALETTE_RED, 1));
    lv_style_set_shadow_width(&style_sw, 55);
    lv_style_set_shadow_color(&style_sw, lv_palette_main(LV_PALETTE_PINK));

    static lv_style_t style_roller;
    lv_style_init(&style_roller);
    lv_style_set_border_color(&style_roller, lv_palette_darken(LV_PALETTE_BLUE, 3));
    lv_style_set_shadow_width(&style_roller, 55);
    lv_style_set_shadow_color(&style_roller, lv_palette_main(LV_PALETTE_BLUE_GREY));
    static lv_style_t style_list;
    lv_style_set_shadow_width(&style_list, 55);
    lv_style_set_shadow_color(&style_list, lv_palette_main(LV_PALETTE_GREY));

    static lv_style_t style_imu_label;
    lv_style_init(&style_imu_label);
    lv_style_set_text_color(&style_imu_label,lv_palette_main(LV_PALETTE_PURPLE));;

    // /*Create tileview*/
    lv_obj_t *tv = lv_tileview_create(lv_scr_act());
    lv_obj_set_scrollbar_mode(tv,  LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(group, tv);





    //Jon test Tile

    lv_obj_t *tileJD = lv_tileview_add_tile(tv, 0, 0, LV_DIR_TOP|LV_DIR_BOTTOM);



    lv_obj_t * arc = lv_arc_create(tileJD);
    lv_obj_set_size(arc, DISP_HOR_RES, DISP_VER_RES);
	lv_arc_set_rotation(arc, 270);
	lv_arc_set_bg_angles(arc, 0, 0);
	lv_obj_remove_style(arc, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
	//lv_obj_remove_flag(arc, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/
	lv_obj_clear_flag( arc,  LV_OBJ_FLAG_CLICKABLE);
	lv_obj_center(arc);

	lv_obj_t * arc1 = lv_arc_create(tileJD);
	lv_obj_set_size(arc1, DISP_HOR_RES-20, DISP_VER_RES-20);
	lv_arc_set_rotation(arc1, 15);
	lv_arc_set_bg_angles(arc1, 0, 0);
	lv_obj_remove_style(arc1, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
	//lv_obj_remove_flag(arc, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/
	lv_obj_clear_flag( arc1,  LV_OBJ_FLAG_CLICKABLE);
	lv_obj_center(arc1);
	lv_obj_set_style_arc_color(
			 arc1,
			 lv_palette_lighten(LV_PALETTE_RED, 1),
			 LV_PART_INDICATOR);

	lv_obj_t * arc2 = lv_arc_create(tileJD);
	lv_obj_set_size(arc2, DISP_HOR_RES-20*2, DISP_VER_RES-20*2);
	lv_arc_set_rotation(arc2, 45);
	lv_arc_set_bg_angles(arc2, 0, 0);
	lv_obj_remove_style(arc2, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
	//lv_obj_remove_flag(arc, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/
	lv_obj_clear_flag( arc2,  LV_OBJ_FLAG_CLICKABLE);
	lv_obj_center(arc2);
    lv_obj_set_style_arc_color(
			 arc2,
			 lv_palette_lighten(LV_PALETTE_RED, 3),
			 LV_PART_INDICATOR);

    lv_obj_t * arc3 = lv_arc_create(tileJD);
	lv_obj_set_size(arc3, DISP_HOR_RES-20*3, DISP_VER_RES-20*3);
	lv_arc_set_rotation(arc3, 45);
	lv_arc_set_bg_angles(arc3, 0, 0);
	lv_obj_remove_style(arc3, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
	//lv_obj_remove_flag(arc, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/
	lv_obj_clear_flag( arc3,  LV_OBJ_FLAG_CLICKABLE);
	lv_obj_center(arc3);
	lv_obj_set_style_arc_color(
			 arc3,
			 lv_palette_lighten(LV_PALETTE_GREEN, 3),
			 LV_PART_INDICATOR);


	lv_obj_t * arc4 = lv_arc_create(tileJD);
	lv_obj_set_size(arc4, DISP_HOR_RES-20*4, DISP_VER_RES-20*4);
	lv_arc_set_rotation(arc4, 45);
	lv_arc_set_bg_angles(arc4, 0, 0);
	lv_obj_remove_style(arc4, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
	//lv_obj_remove_flag(arc, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/
	lv_obj_clear_flag( arc4,  LV_OBJ_FLAG_CLICKABLE);
	lv_obj_center(arc4);
	lv_obj_set_style_arc_color(
			 arc4,
			 lv_palette_lighten(LV_PALETTE_GREEN, 1),
			 LV_PART_INDICATOR);


    arcs[0] = arc;
    arcs[1] = arc1;
    arcs[2] = arc2;
    arcs[3] = arc3;
    arcs[4] = arc4;

	lv_anim_t a;
	lv_anim_init(&a);
	//lv_anim_set_var(&a, arc);
	lv_anim_set_var(&a, arcs);
	lv_anim_set_exec_cb(&a, set_angle);
	lv_anim_set_time(&a, 2000);
	lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);    /*Just for the demo*/
	lv_anim_set_repeat_delay(&a, 0);
	lv_anim_set_values(&a, 0, 360);
	lv_anim_start(&a);


	lv_obj_t * label1 = lv_label_create(tileJD);
	lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP);     /*Break the long lines*/
	lv_label_set_text(label1, "Dr Jon EA");
	lv_obj_set_width(label1, 150);  /*Set smaller width to make the lines wrap*/
	lv_obj_set_style_text_align(label1, LV_TEXT_ALIGN_CENTER, 0);
	lv_obj_align(label1, LV_ALIGN_CENTER, 0, -40);

}



