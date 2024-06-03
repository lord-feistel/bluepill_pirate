#!/bin/bash
SCRIPT_DIR=/usr/share/openocd/scripts
openocd -f $SCRIPT_DIR/interface/stlink-v2.cfg  -f $SCRIPT_DIR/target/stm32f1x.cfg

