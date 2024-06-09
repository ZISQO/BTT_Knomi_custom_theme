#include <lvgl_gui.h>
#include <Arduino.h>
#include <lvgl.h>
#include <WiFi.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include <WiFiUser.h>
#include <lvgl_logo_btt.h>
#include <lvgl_gif.h>
#include <test.h>

// View Refresh Timer
lv_timer_t * update_timer=NULL;
uint8_t contne = 0;
uint8_t print_status = 0;  //0 Standby  1 Printing  2 Pause
uint8_t homing_status = 0;  
uint8_t levelling_status = 0;  
uint8_t timer_contne = 0;  // Show Timer
uint8_t standby_voron_dis_flg = 0;  // 0 standby 1 voron logo repeat
uint8_t display_step = 0;  // 단계 흐름 0 시작 애니메이션 2 대기 애니메이션 3 핫 베드 온도 4 헤드 온도 5 인쇄 중 6 인쇄 완료
                           // 9 인쇄 전 10 인쇄 완료 11 voron logo 12 homing 13 levelling
                           // 7 apconfig  8 no klipper

uint8_t exist_object_screen_flg = 0; //0 존재하는 화면 개체 없음
uint8_t screen_begin_dis_flg = 0; //0 while 루프 시작
uint8_t screen_no_klipper_dis_flg = 0; //0 klipper 연결 실패
uint8_t start_http_request_flg = 0; //0 HTTP 요청 시작
uint8_t wifi_ap_config_flg = 0; //0 wifi 설정
uint8_t First_connection_flg = 0; // 첫 연결 시

// 출력 인터페이스 설정
lv_obj_t * label_print_status;
lv_obj_t * label_print_progress;
lv_obj_t * arc_print_progress;

// 출력 인터페이스 스타일 설정
lv_style_t style_label_print_status;
lv_style_t style_label_print_progress;
lv_style_t style_arc_print_progress;

// 온도 인터페이스 설정
lv_obj_t * label_ext_actual_temp;
lv_obj_t * label_ext_target_temp;
lv_obj_t * label_bed_actual_temp; 
lv_obj_t * label_bed_target_temp; 

lv_obj_t * arc_extruder_temp; 
lv_obj_t * arc_heaterbed_temp; 

// 온도 인터페이스 스타일 설정
lv_style_t style_label_ext_actual_temp;
lv_style_t style_label_ext_target_temp;
lv_style_t style_label_bed_actual_temp;
lv_style_t style_label_bed_target_temp;

lv_style_t style_arc_extruder_temp; 
lv_style_t style_arc_heaterbed_temp; 

// 출력 파일 인터페이스 설정
lv_obj_t * label_print_file;
// 
lv_style_t style_label_print_file;

// apconfig 인터페이스 스타일 설정
lv_obj_t * label_ap_config;

// apconfig 스타일 설정
lv_style_t style_label_ap_config;

// klipper 연결 실패 인터페이스 설정
lv_obj_t * label_no_klipper;

// klipper 연결 실패 인터페이스 스타일 설정
lv_style_t style_label_no_klipper;

// 팬 속도 인터페이스 객체 설정
lv_obj_t * label_fan_speed;
lv_obj_t * bar_fan_speed;

// 팬 속도 인터페이스 스타일 설정
lv_style_t style_label_fan_speed;
lv_style_t style_bar_fan_speed;

lv_obj_t * label_open_anim;
lv_obj_t * open_anim_arc;
lv_obj_t * open_back;// 전원 켜기 배경
lv_obj_t * label_open;// 전원 켜기 와이파이 연결 알림 탭
lv_style_t style_label_open;
lv_style_t style_label_load;
lv_style_t style_spinner_open;
lv_style_t style_bc_spinner_open;

lv_timer_t * timer_open=NULL;// 전원 켜기 지연에 사용: 네트워크 연결과 애니메이션
lv_timer_t * timer_open_task1=NULL;
lv_timer_t * timer_open_task2=NULL;
lv_timer_t * timer_open_init=NULL;
lv_timer_t * timer_project_init=NULL;

int wifi_connect_ok = 0; // wifi 연결 성공 플래그
int wifi_connect_fail = 0; // wifi 연결 실패 플래그

static void set_angle(void * var, int32_t v)
{
    lv_arc_set_value((lv_obj_t *)var, v);
}

void Open_up_animation()
{
    lv_style_set_arc_color(&style_spinner_open, lv_color_hex(0x00E0FF)); // FF0000 스피너 색상
    lv_style_set_arc_width(&style_spinner_open, 16);            // 스피너 너비 설정 
    lv_style_set_arc_color(&style_bc_spinner_open, lv_color_hex(0x000000)); // 스피너 배경 색상
    lv_style_set_arc_width(&style_bc_spinner_open, 16);        // 스피너 배경 너비 설정
 
    open_anim_arc = lv_spinner_create(lv_scr_act(), 1000, 45);
 
    lv_obj_add_style(open_anim_arc, &style_spinner_open, LV_PART_INDICATOR);// 스피너 부분에 적용
    lv_obj_add_style(open_anim_arc, &style_bc_spinner_open, LV_PART_MAIN);// 스피너 배경에 적용
 
    lv_obj_set_size(open_anim_arc, 240, 240);
    lv_obj_align(open_anim_arc, LV_ALIGN_CENTER, 0, 0);
}

void project_task_init(lv_timer_t * timer){

    lv_obj_del(open_anim_arc);
    lv_obj_del(img_open_logo);

    display_step = 2; // 대체
    timer_contne = 1;

    delete_exist_object();
    update_timer = lv_timer_create(update_screen7, 0, NULL);
    lv_timer_set_repeat_count(update_timer,1);

    screen_begin_dis_flg = 1;
}

// 연결 성공 초기화 항목 삭제 애니메이션
void open_task_suc(lv_timer_t * timer){

    timer_project_init=lv_timer_create(project_task_init, 100, NULL);
    lv_timer_set_repeat_count(timer_project_init,1);
}

// 초기화 실패 다시 시작
void open_task_err(lv_timer_t * timer){
    //  ESP.restart();

    timer_project_init=lv_timer_create(project_task_init, 100, NULL);
    lv_timer_set_repeat_count(timer_project_init,1);
}

// 연결 성공 여부 확인
void open_task_1(lv_timer_t * timer){

// 와이파이에 연결
    if(wifi_connect_ok == 1){
        timer_open_task1=lv_timer_create(open_task_suc, 4000, NULL);
        lv_timer_set_repeat_count(timer_open_task1,1);
    }
// 와이파이에 연결할 수 없음
    if(wifi_connect_fail == 1){
        timer_open_task2=lv_timer_create(open_task_err, 4000, NULL);
        lv_timer_set_repeat_count(timer_open_task2,1);
    }
}

void open_task_conv(lv_timer_t * timer){

    // 와이파이 연결
    connectToWiFi(connectTimeOut_s);     // 와이파이를 연결하면 와이파이 연결 대기시간 15s로 설정

    if(test_mode_flag == 0){

        init_img_open_logo_display();

        Open_up_animation();

        timer_open=lv_timer_create(open_task_1, 100, NULL);
        lv_timer_set_repeat_count(timer_open,1); 

    }
}

void Open_display_init(){

    if(test_mode_flag == 1){

    }else if(wifi_ap_config_flg == 1){
        update_gif_AP_Config_back_display();
        update_gif_AP_Config_display();
        exist_object_screen_flg = 20;
        screen_begin_dis_flg = 1;
    }else{

        init_img_open_logo_display();

        timer_open_init=lv_timer_create(open_task_conv, 100, NULL);
        lv_timer_set_repeat_count(timer_open_init,1);
    }

} 

