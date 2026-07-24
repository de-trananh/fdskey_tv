# FDSKeyTv Known issue list:
##  Version 1.3.5:
1) When number of file is over 256, ROM menu counter is reset to 0 (Rom counter overflow).
    + Rootcause: Number of ROM counter is using just only 1byte at offset 0x1ED6 for number of ROM couter while it is designed to use 2bytes at offset 0x1ED6 as Low byte and offset 0x1ED7 as High byte.
    + Solution: Use 2 bytes at offset 0x1ED6 as Low byte and offset 0x1ED7 as High byte for number of ROM counter.(Detailed in: MagicWildCardRom_Explaination.xlsx)
    + Fix version: 1.3.6
##  Version 1.3.4:
1) Bootloader updating in service menu is not possible due to Im using static RAM for FDS RAW DATA (Not dynamic). This cause the error about resoucre consumption when we select Bootloader update in service menu.
    + Solution: Changed to use dynamic RAM
    + Fix version: 1.3.5
##  Version 1.3.2:
1) When the number of ROM is a multiple of 24 (fills 1 screen page). A screen crash will appear when changing to last page.
    + Solution: Add 1 more  line to inform END OF MENU for next page and no impact when select that line.
    + Fix version: 1.3.4

# FDSKeyTv
* Please use STM32CubeProgrammer to flash the menu rom file "fdskey_tv_menu.bin" into 0x08070000
* FDSKeyTv's functions just like the original FDSKey.
* One new feature has been added to the settings list, allowing you to choose how to browse games:
  - On TV: The game list will appear on the TV.
  <img width="1044" height="426" alt="image" src="https://github.com/user-attachments/assets/5f57958c-ac6e-4bbc-ae0c-ced38ff20312" />
  <img width="539" height="533" alt="image" src="https://github.com/user-attachments/assets/71ecaed7-5de9-4d8e-a12b-35cf975f30a2" />

  - On OLED: Browse games on the OLED display, just like the original FDSKey.
  <img width="1192" height="495" alt="image" src="https://github.com/user-attachments/assets/065859bd-ec1a-4980-a8ae-57a0496fa157" />
* For details, please see this demonstration: https://www.youtube.com/watch?v=ZjAdUov6Ob8

## Keynotes:
* After select onTV mode of GAME LIST option, you need to reboot device to enter to on TV menu mode. The prevention for the failure of ROMS browsing after select onTV of GAME LIST option is now not available.
* In TV mode, the 'L' and 'R' buttons are disabled to preserve ''menu'' function's states.
* When the FDSKey is performing read/write operations to the FDS device, all button functions are restricted to prevent certain known state machine failures.
* To switch over to original FDSKey feature, just hold 'L' button during  power up.
* Due to limited of resource consumption of stm32g0 uC, rough estimation of num of ROMs can be browsed on TV currently is around 500 files.

# FDSKey
* Goto original repo of ClusterM for detail https://github.com/ClusterM/fdskey

