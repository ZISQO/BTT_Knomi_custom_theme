#ifndef LVGL_LOGO_BTT_H
#define LVGL_LOGO_BTT_H

#ifdef __cplusplus
extern "C" {  //extern "C"는 컴파일러에 의해 생성된 내부 기호명에 C 규약을 사용함을 나타냅니다.이렇게 하면 c++ 파일에서도 해당 c 함수를 호출할 수 있습니다.
#endif

#include <lvgl.h>

extern lv_obj_t * img_open_logo;


void init_img_open_logo_display();


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  
