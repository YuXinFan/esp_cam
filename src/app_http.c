#include <esp_wifi.h>
#include <esp_event.h>
#include <esp_timer.h>
#include <esp_log.h>
#include <esp_system.h>
#include <nvs_flash.h>
#include <sys/param.h>

#include "app_http.h"

static const char *TAG="webserver";

// static esp_err_t jpg_httpd_handler(httpd_req_t *req){
//   camera_fb_t *fb = NULL;
//   esp_err_t res = ESP_OK;
//   size_t fb_len = 0;
//   int64_t fr_start = esp_timer_get_time();

//   fb = esp_camera_fb_get();
//   if (!fb)
//   {
//     ESP_LOGE(TAG, "Camera capture failed");
//     httpd_resp_send_500(req);
//     return ESP_FAIL;
//   }
//   res = httpd_resp_set_type(req, "image/jpeg");
//   if (res == ESP_OK)
//   {
//     res = httpd_resp_set_hdr(req, "Content-Disposition", "inline; filename=capture.jpg");
//   }

//   if (res == ESP_OK)
//   {
//     fb_len = fb->len;
//     res = httpd_resp_send(req, (const char *)fb->buf, fb->len);
//   }
//   esp_camera_fb_return(fb);
//   int64_t fr_end = esp_timer_get_time();
//   ESP_LOGI(TAG, "JPG: %uKB %ums", (uint32_t)(fb_len / 1024), (uint32_t)((fr_end - fr_start) / 1000));
//   return res;
// }

// httpd_uri_t uri_handler_jpg = {
//     .uri = "/jpg",
//     .method = HTTP_GET,
//     .handler = jpg_httpd_handler,
//     .user_ctx = NULL,
// };

// httpd_handle_t app_http_start_webserver(void)
// {
//   httpd_handle_t server = NULL;
//   httpd_config_t config = HTTPD_DEFAULT_CONFIG();

//   // Start the httpd server
//   ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
//   if (httpd_start(&server, &config) == ESP_OK)
//   {
//     // Set URI handlers
//     ESP_LOGI(TAG, "Registering URI handlers");
//     if (httpd_register_uri_handler(server, &uri_handler_jpg) != ESP_OK){
//         ESP_LOGI(TAG, "registering uri handler failed");
//     }
//     return server;
//   }

//   ESP_LOGI(TAG, "Error starting server!");
//   return NULL;
// }

// void app_http_stop_webserver(httpd_handle_t server)
// {
//   httpd_stop(server);
// }

// static esp_err_t http_event_handler_webserver(void *ctx, system_event_t *event)
// {
//   httpd_handle_t *server = (httpd_handle_t *)ctx;

//   switch (event->event_id)
//   {
//   case SYSTEM_EVENT_STA_START:
//     ESP_LOGI(TAG, "SYSTEM_EVENT_STA_START");
//     ESP_ERROR_CHECK(esp_wifi_connect());
//     break;
//   case SYSTEM_EVENT_STA_GOT_IP:
//     ESP_LOGI(TAG, "SYSTEM_EVENT_STA_GOT_IP");
//     ESP_LOGI(TAG, "Got IP: '%s'",
//              ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));

//     /* Start the web server */
//     if (*server == NULL)
//     {
//       *server = app_http_start_webserver();
//     }
//     break;
//   case SYSTEM_EVENT_STA_DISCONNECTED:
//     ESP_LOGI(TAG, "SYSTEM_EVENT_STA_DISCONNECTED");
//     ESP_ERROR_CHECK(esp_wifi_connect());

//     /* Stop the web server */
//     if (*server)
//     {
//       stop_webserver(*server);
//       *server = NULL;
//     }
//     break;
//   default:
//     break;
//   }
//   return ESP_OK;
// }

// const esp_event_loop_args_t event_args_http = {
//     .queue_size = 16,                         /**< size of the event loop queue */
//     .task_name = "http event handler",                      /**< name of the event loop task; if NULL,
//                                                         a dedicated task is not created for event loop*/
//     .task_priority = 5,                  /**< priority of the event loop task, ignored if task name is NULL */
//     .task_stack_size = 128 * 4,                   /**< stack size of the event loop task, ignored if task name is NULL */
// };


