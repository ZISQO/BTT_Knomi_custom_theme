#ifndef LVGL_GUI_H
#define LVGL_GUI_H

#ifdef __cplusplus
extern "C" {  //extern "C"는 컴파일러에 의해 생성된 내부 기호명에 C 규약을 사용함을 나타냅니다.이렇게 하면 c++ 파일에서도 해당 c 함수를 호출할 수 있습니다
#endif

#include <lvgl.h>

extern int wifi_connect_ok; // wifi 연결 성공 플래그
extern int wifi_connect_fail;  // wifi 연결 실패 플래그

void Open_up_animation();    
void Open_display_init();


//显示刷新定时器
extern lv_timer_t * update_timer;
extern uint8_t contne;
extern uint8_t print_status; 
extern uint8_t homing_status;  
extern uint8_t levelling_status; 
extern uint8_t timer_contne;
extern uint8_t display_step;
extern uint8_t standby_voron_dis_flg; 

extern uint8_t exist_object_screen_flg; //0 존재하는 화면 개체 없음
extern uint8_t screen_begin_dis_flg;
extern uint8_t screen_no_klipper_dis_flg; //0 klipper 연결 실패
extern uint8_t start_http_request_flg; //0 HTTP 요청 시작
extern uint8_t wifi_ap_config_flg; //0 wifi 연결중
extern uint8_t First_connection_flg;

// 출력 인터페이스 설정
extern lv_obj_t * label_print_status;
extern lv_obj_t * label_print_progress;
extern lv_obj_t * arc_print_progress;
// 출력 인터페이스의 스타일 설정
extern lv_style_t style_label_print_status;
extern lv_style_t style_label_print_progress;
extern lv_style_t style_arc_print_progress;

// 온도 인터페이스 설정
extern lv_obj_t * label_ext_actual_temp;
extern lv_obj_t * label_ext_target_temp;
extern lv_obj_t * label_bed_actual_temp; 
extern lv_obj_t * label_bed_target_temp; 

extern lv_obj_t * arc_extruder_temp; 
extern lv_obj_t * arc_heaterbed_temp; 
// 온도 인터페이스 스타일 설정
extern lv_style_t style_label_ext_actual_temp;
extern lv_style_t style_label_ext_target_temp;
extern lv_style_t style_label_bed_actual_temp;
extern lv_style_t style_label_bed_target_temp;

extern lv_style_t style_arc_extruder_temp; 
extern lv_style_t style_arc_heaterbed_temp; 

// 출력 파일 인터페이스 설정
extern lv_obj_t * label_print_file;
// 출력 파일 인터페이스 스타일 설정
extern lv_style_t style_label_print_file;

// apconfig 인터페이스 설정
extern lv_obj_t * label_ap_config;
// apconfig 인터페이스 스타일 설정
extern lv_style_t style_label_ap_config;

// klipper 연결 실패 인터페이스 설정
extern lv_obj_t * label_no_klipper;
// klipper 연결 실패 인터페이스 스타일 설정
extern lv_style_t style_label_no_klipper;

// 팬 속도 인터페이스 설정
extern lv_obj_t * label_fan_speed;
extern lv_obj_t * bar_fan_speed;
// 팬 속도 인터페이스 스타일 설정
extern lv_style_t style_label_fan_speed;
extern lv_style_t style_bar_fan_speed;

// 인터페이스 및 스타일 초기화 함수 설정
//---------screen1---------------//
void init_label_print_status();
void init_label_print_progress();
void init_arc_print_progress();
//---------screen2---------------//
void init_label_extruder_actual_temp();
void init_label_heaterbed_actual_temp();
void init_label_extruder_target_temp();
void init_label_heaterbed_target_temp();
void init_arc_extruder_temp();
void init_arc_heaterbed_temp();
//---------screen3---------------//
void init_label_print_file();
//---------screen4---------------//
void init_label_ap_config();
//---------screen5---------------//
void init_label_no_klipper();
//---------screen6---------------//
void init_label_fan_speed();

// 인터페이스 새로 고침 처리 함수 정의
//---------screen1---------------//
void update_label_print_status();
void update_label_print_progress();
void update_arc_print_progress();
//---------screen2---------------//
void update_label_extruder_actual_temp();
void update_label_heaterbed_actual_temp();
void update_label_extruder_target_temp();
void update_label_heaterbed_target_temp();
void update_arc_extruder_temp();
void update_arc_heaterbed_temp();
//---------screen3---------------//
void update_label_print_file();
//---------screen4---------------//
void update_label_ap_config();
//---------screen5---------------//
void update_label_no_klipper();
//---------screen6---------------//
void update_label_fan_speed();

// 인터페이스 새로 고침 처리 함수 정의
void update_screen1(lv_timer_t * timer);
void update_screen2(lv_timer_t * timer);
void update_screen3(lv_timer_t * timer);
void update_screen4(lv_timer_t * timer);
void update_screen5(lv_timer_t * timer);
void update_screen6(lv_timer_t * timer);
void update_screen7(lv_timer_t * timer);
void update_screen8(lv_timer_t * timer);
void update_screen9(lv_timer_t * timer);
void update_screen10(lv_timer_t * timer);
void update_screen11(lv_timer_t * timer);
void update_screen12(lv_timer_t * timer);
void update_screen13(lv_timer_t * timer);

// 인터페이스 삭제
void delete_exist_object();

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  
