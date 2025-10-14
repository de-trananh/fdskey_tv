#ifndef INC_FDSEMU_H_
#define INC_FDSEMU_H_

#include "main.h"
#include "ff.h"
#include "settings.h"

//#define FDS_USE_DYNAMIC_MEMORY

// hardware settings
#define FDS_READ_PWM_TIMER htim3
#define FDS_READ_PWM_TIMER_CHANNEL 1
#define FDS_READ_DMA hdma_tim3_up
#define FDS_READ_IMPULSE_LENGTH 32

#define FDS_WRITE_CAPTURE_TIMER htim17
#define FDS_WRITE_CAPTURE_TIMER_CHANNEL 1
#define FDS_WRITE_DMA hdma_tim17_ch1
#define FDS_THRESHOLD_1 960
#define FDS_THRESHOLD_2 1120

// FDS emulation settings
#define FDS_MAX_SIDE_SIZE (65 * 1024) // 65000 + some space for gaps and crcs, largest ROM is 66080 bytes including gaps and crcs
#define FDS_MAX_FILE_PATH_LENGTH 4096
#define FDS_MAX_BLOCKS 256
#define FDS_MAX_BLOCK_SIZE FDS_MAX_SIDE_SIZE
#define FDS_READ_BUFFER_SIZE 128      // bits
#define FDS_WRITE_BUFFER_SIZE 32     // impulses
#define FDS_FIRST_GAP_READ_BITS 28300 // first gap size, bits
#define FDS_NEXT_GAPS_READ_BITS 976   // next gap size, bits
#define FDS_WRITE_GAP_SKIP_BITS 32     // dispose bits before writing
#define FDS_NOT_READY_TIME 1000       // disk rewind time, milliseconds
#define FDS_NOT_READY_TIME_ORIGINAL 5000 // disk rewind time for original speed mode
#define FDS_NOT_READY_BYTES 1024      // fast rewind after this amount of bytes of used data
#define FDS_MULTI_WRITE_UNLICENSED_BITS 32 // some unlicensed software can write multiple blocks at once
#define FDS_AUTOSAVE_DELAY 1000

// do not touch it
#define FDS_ROM_HEADER_SIZE 16    // header in ROM
#define FDS_ROM_SIDE_SIZE 65500   // disk side size in ROM

// special subdefines
#define FDS_GLUE(a, b) a##b
#define FDS_TIMER_CHANNEL_REG(v) FDS_GLUE(CCR, v)
#define FDS_TIMER_CHANNEL_CONST(v) FDS_GLUE(TIM_CHANNEL_, v)
#define FDS_TIMER_DMA_TRIGGER_CONST(v) FDS_GLUE(TIM_DMA_CC, v)
#define FDS_READ_PWM_TIMER_CHANNEL_REG FDS_TIMER_CHANNEL_REG(FDS_READ_PWM_TIMER_CHANNEL)
#define FDS_READ_PWM_TIMER_CHANNEL_CONST FDS_TIMER_CHANNEL_CONST(FDS_READ_PWM_TIMER_CHANNEL)
#define FDS_WRITE_CAPTURE_TIMER_CHANNEL_REG FDS_TIMER_CHANNEL_REG(FDS_WRITE_CAPTURE_TIMER_CHANNEL)
#define FDS_WRITE_CAPTURE_TIMER_CHANNEL_CONST FDS_TIMER_CHANNEL_CONST(FDS_WRITE_CAPTURE_TIMER_CHANNEL)
#define FDS_WRITE_CAPTURE_DMA_TRIGGER_CONST FDS_TIMER_DMA_TRIGGER_CONST(FDS_WRITE_CAPTURE_TIMER_CHANNEL)

#define FLASH_MENU_OFFSET      0x08070000
#define FLASH_LISTFILE_OFFSET  0x1EFE
#define FLASH_NUMFILE_OFFSET   0x1ED6
#define FLASH_FILELEN_H_OFFSET 0x1ED3
#define FLASH_FILELEN_L_OFFSET 0x1ED2

typedef enum {
  FDS_OFF,                    // disk image is not loaded
  FDS_IDLE,                   // disk stopped
  FDS_READ_WAIT_READY,        // waiting for disk rewinding
  FDS_READ_WAIT_READY_TIMER,  // not-ready timer
  FDS_READING,                // reading data
  FDS_WRITING_GAP,            // waiting for gap terminator before writing
  FDS_WRITING,                // writing data
  FDS_WRITING_STOPPING,       // end of useful data, writing garbage
  FDS_SAVE_PENDING            // saving image
} FDS_STATE;

#define FDSR_WRONG_CRC 0x80
#define FDSR_INVALID_ROM 0x81
#define FDSR_OUT_OF_MEMORY 0x82
#define FDSR_ROM_TOO_LARGE 0x83
#define FDSR_READ_ONLY 0x84
#define FDSR_CANCELLED 0x85

FRESULT fds_load_side(char *filename, uint8_t side, uint8_t ro);
FRESULT fds_close(uint8_t save);
FRESULT fds_save();
void fds_check_pins();
FDS_STATE fds_get_state();
uint8_t fds_is_changed();
int fds_get_block();
int fds_get_block_count();
int fds_get_head_position();
int fds_get_max_size();
int fds_get_used_space();

extern TIM_HandleTypeDef FDS_READ_PWM_TIMER;
extern DMA_HandleTypeDef FDS_READ_DMA;
extern TIM_HandleTypeDef FDS_WRITE_TIMER;
extern DMA_HandleTypeDef FDS_WRITE_DMA;
extern TIM_HandleTypeDef FDS_WRITE_CAPTURE_TIMER;


extern char fds_menu_selected_file[13];//12 Bytes of file name and 1 end of string
extern uint16_t fds_setup_menu_buffer(char* menu1in1_gamename);//return number of games in menu
typedef enum
{
	ON_TV_LIST_INI,
	ON_TV_LIST_SHOW,
	ON_TV_LIST_SELECTED,
	ON_TV_LIST_PLAY_GAME
} FDS_TV_MENU_STATE;
extern FDS_TV_MENU_STATE fds_menu_selection_state;

#endif /* INC_FDSEMU_H_ */
