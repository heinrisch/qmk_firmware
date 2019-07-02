#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define _QWERTY 0
#define _SWEDISH 1
#define _LOWER 2
#define _RAISE 3
#define _ADJUST 4

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  SWEDISH,
  BACKLIT,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

enum unicode_names {
  AAU,
  AAL,
  AEU,
  AEL,
  OEU,
  OEL,
};

const uint32_t PROGMEM unicode_map[] = {
  [AAU]  = 0x00C5,
  [AAL] =  0x00E5,

  [AEU]  = 0x00C4,
  [AEL] =  0x00E4,

  [OEU]  = 0x00D6,
  [OEL] =  0x00F6,
};

#define KC______ KC_TRNS
#define KC_XOX   KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_SWEDISH SWEDISH
#define KC_XP    XP
#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
#define KC_CTLTB CTL_T(KC_TAB)
#define KC_GUIEI GUI_T(KC_LANG2)
#define KC_ALTKN ALT_T(KC_LANG1)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,BSLASH,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLTB,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,  QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH,  LALT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LOWER, GUIEI,  BSPC,      ENT, SPC, RAISE  \
                              //`--------------------'  `--------------------'
  ),

  [_SWEDISH] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
       XOX,   XOX,   XOX,   XOX,   XOX,   XOX,                   XOX,   XOX,   XOX,   XOX,   XOX,XP(AAL,AAU),\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       XOX,   XOX,   XOX,   XOX,   XOX,   XOX,                   XOX,   XOX,   XOX,   XOX,  XP(AEL,AEU),XP(OEL,OEU),\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       XOX,   XOX,   XOX,   XOX,   XOX,   XOX,                   XOX,   XOX,   XOX,   XOX,   XOX,SWEDISH,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   XOX,   XOX,   XOX,     XOX,   XOX,   XOX \
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      GRAVE,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0,BSLASH,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLTB,   XOX,   XOX,   XOX,   XOX,   XOX,                   LBRC,   XOX,   XOX,  MINS,   EQL,  RBRC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,    F1,    F2,    F3,    F4,    F5,                     F6,    F7,     F8,   F9,   F10,  LALT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                 XOX,   XOX,   XOX,     XOX,   XOX,   XOX  \
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,   XOX,   XOX,   XOX,   XOX,   XOX,                 LPRN,   XOX,   UP,  MINS,  EQL, RPRN,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLTB,   XOX,   XOX,   XOX,   XOX,   XOX,                  LBRC,  LEFT,  DOWN, RIGHT,   XOX,RBRC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,   XOX,   XOX,   XOX,   XOX,   XOX,                   LABK,  XOX,   XOX,   XOX,   XOX,   RABK,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                 XOX,   XOX,   XOX,     XOX,   XOX,   XOX  \
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        RST,  LRST,    NO,    NO,    NO,    NO,                     NO,    NO,    NO,    NO,    NO,    NO,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LTOG,  LHUI,  LSAI,  LVAI,    NO,    NO,                     NO,    NO,    NO,    NO,    NO,    NO,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LMOD,  LHUD,  LSAD,  LVAD,    NO,    NO,                     NO,    NO,    NO,    NO,    NO,SWEDISH,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                 XOX,   XOX,   XOX,     XOX,   XOX,   XOX  \
                              //`--------------------'  `--------------------'
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void eeconfig_init_user(void) {
  set_unicode_input_mode(UC_OSX);
}

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  eeconfig_init();
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
    case SWEDISH:
        if (record->event.pressed) {
          if (IS_LAYER_ON(_SWEDISH)) {
            layer_off(_SWEDISH);
          } else {
            layer_on(_SWEDISH);
          }
        }
        return false;
        break;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}
