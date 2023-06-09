/* std header */

/* sdk header */
#include "esp_log.h"
#include "esp_camera.h"

/* top level header */
#include "header.h"
/* module level header */

/* private level header */
#include "m_camera.h"
#include "sensor.h"

static const char *DEFALUT_TAG = "mCamera";

static camera_config_t default_camera_config = {
    .pin_pwdn = CAM_PIN_PWDN,
    .pin_reset = CAM_PIN_RESET,
    .pin_xclk = CAM_PIN_XCLK,
    .pin_sccb_sda = CAM_PIN_SIOD,
    .pin_sccb_scl = CAM_PIN_SIOC,

    .pin_d7 = CAM_PIN_D7,
    .pin_d6 = CAM_PIN_D6,
    .pin_d5 = CAM_PIN_D5,
    .pin_d4 = CAM_PIN_D4,
    .pin_d3 = CAM_PIN_D3,
    .pin_d2 = CAM_PIN_D2,
    .pin_d1 = CAM_PIN_D1,
    .pin_d0 = CAM_PIN_D0,
    .pin_vsync = CAM_PIN_VSYNC,
    .pin_href = CAM_PIN_HREF,
    .pin_pclk = CAM_PIN_PCLK,

    //XCLK 20MHz or 10MHz for OV2640 double FPS (Experimental)
    .xclk_freq_hz = 20000000,
    .ledc_timer = LEDC_TIMER_0,
    .ledc_channel = LEDC_CHANNEL_0,

    .pixel_format = PIXFORMAT_JPEG, //YUV422,GRAYSCALE,RGB565,JPEG
    .frame_size = FRAMESIZE_VGA,    //QQVGA-UXGA, For ESP32, do not use sizes above QVGA when not JPEG. The performance of the ESP32-S series has improved a lot, but JPEG mode always gives better frame rates.

    .jpeg_quality = 12, //0-63, for OV series camera sensors, lower number means higher quality
    .fb_count = 1,       //When jpeg mode is used, if fb_count more than one, the driver will work in continuous mode.
    .grab_mode = CAMERA_GRAB_WHEN_EMPTY,
};

esp_err_t m_camera_init_default(void){
    esp_err_t err = esp_camera_init(&default_camera_config);
    if (err != ESP_OK)
    {
        ESP_LOGE(DEFALUT_TAG, "Camera Init Failed");
        return err;
    }

    return ESP_OK;
}

esp_err_t m_camera_init(const camera_config_t *config){
    //initialize the camera
    esp_err_t err = esp_camera_init(config);
    if (err != ESP_OK)
    {
        ESP_LOGE(DEFALUT_TAG, "Camera Init Failed");
        return err;
    }

    return ESP_OK;
}

esp_err_t m_camera_capture_once(camera_fb_cb_t cb){
    esp_err_t ret = ESP_OK;
    //acquire a frame
    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) {
        ESP_LOGE(DEFALUT_TAG, "Camera Capture Failed");
        return ESP_FAIL;
    }
    //replace this with your own function
    if ( NULL != cb ){
        ret = (*cb)(fb);
    }
    //process_image(fb->width, fb->height, fb->format, fb->buf, fb->len);
  
    //return the frame buffer back to the driver for reuse
    esp_camera_fb_return(fb);
    return ret;
}

esp_err_t camera_capture(){
    //acquire a frame
    camera_fb_t * fb = esp_camera_fb_get();
    if (!fb) {
        ESP_LOGE(DEFALUT_TAG, "Camera Capture Failed");
        return ESP_FAIL;
    }
    //replace this with your own function
    //process_image(fb->width, fb->height, fb->format, fb->buf, fb->len);
  
    //return the frame buffer back to the driver for reuse
    esp_camera_fb_return(fb);
    return ESP_OK;
}