###############################################################################
#
# Copyright 2014, ACSE & CADIEEL
#    ACSE   : http://www.sase.com.ar/asociacion-civil-sistemas-embebidos/ciaa/
#    CADIEEL: http://www.cadieel.org.ar
#
# This file is part of CIAA Firmware.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its
#    contributors may be used to endorse or promote products derived from this
#    software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
###############################################################################
# library
LIBS 				    += ext_usblib
# library path
ext_usblib_PATH			= $(ROOT_DIR)$(DS)externals$(DS)usblib
# library source path
ext_usblib_SRC_PATH		= $(ext_usblib_PATH)$(DS)src
   
# library include path
ext_usblib_INC_PATH   = $(ext_usblib_PATH)$(DS)inc					\
						$(ext_usblib_PATH)$(DS)inc$(DS)Common  	
CFLAGS +=	-std=gnu11
# library source files
ext_usblib_SRC_FILES += $(wildcard $(ext_usblib_SRC_PATH)$(DS)*.c)	\
   	$(wildcard $(ext_usblib_SRC_PATH)$(DS)Drivers$(DS)*.c) \
   	$(wildcard $(ext_usblib_SRC_PATH)$(DS)Drivers$(DS)USB$(DS)*.c) \
   	$(wildcard $(ext_usblib_SRC_PATH)$(DS)Drivers$(DS)USB$(DS)Class$(DS)*.c) \
   	$(wildcard $(ext_usblib_SRC_PATH)$(DS)Drivers$(DS)USB$(DS)Class$(DS)Common$(DS)*.c) \
   	$(wildcard $(ext_usblib_SRC_PATH)$(DS)Drivers$(DS)USB$(DS)Class$(DS)Device$(DS)*.c) \
   	$(wildcard $(ext_usblib_SRC_PATH)$(DS)Drivers$(DS)USB$(DS)Class$(DS)Host$(DS)*.c) \
   	$(wildcard $(ext_usblib_SRC_PATH)$(DS)Drivers$(DS)USB$(DS)Core$(DS)*.c) \
   	$(wildcard $(ext_usblib_SRC_PATH)$(DS)Drivers$(DS)USB$(DS)Core$(DS)LPC$(DS)*.c) \
   	$(wildcard $(ext_usblib_SRC_PATH)$(DS)Drivers$(DS)USB$(DS)Core$(DS)LPC$(DS)DCD$(DS)*.c) \
   	$(wildcard $(ext_usblib_SRC_PATH)$(DS)Drivers$(DS)USB$(DS)Core$(DS)LPC$(DS)DCD$(DS)LPC11UXX$(DS)*.c) \
   	$(wildcard $(ext_usblib_SRC_PATH)$(DS)Drivers$(DS)USB$(DS)Core$(DS)LPC$(DS)DCD$(DS)LPC17XX$(DS)*.c) \
   	$(wildcard $(ext_usblib_SRC_PATH)$(DS)Drivers$(DS)USB$(DS)Core$(DS)LPC$(DS)DCD$(DS)LPC18XX$(DS)*.c) \
   	$(wildcard $(ext_usblib_SRC_PATH)$(DS)Drivers$(DS)USB$(DS)Core$(DS)LPC$(DS)DCD$(DS)USBRom$(DS)*.c) \
   	$(wildcard $(ext_usblib_SRC_PATH)$(DS)Drivers$(DS)USB$(DS)Core$(DS)LPC$(DS)HAL$(DS)*.c) \
   	$(wildcard $(ext_usblib_SRC_PATH)$(DS)Drivers$(DS)USB$(DS)Core$(DS)LPC$(DS)HAL$(DS)LPC11UXX$(DS)*.c) \
   	$(wildcard $(ext_usblib_SRC_PATH)$(DS)Drivers$(DS)USB$(DS)Core$(DS)LPC$(DS)HAL$(DS)LPC17XX$(DS)*.c) \
   	$(wildcard $(ext_usblib_SRC_PATH)$(DS)Drivers$(DS)USB$(DS)Core$(DS)LPC$(DS)HAL$(DS)LPC18XX$(DS)*.c) \
   	$(wildcard $(ext_usblib_SRC_PATH)$(DS)Drivers$(DS)USB$(DS)Core$(DS)LPC$(DS)HCD$(DS)*.c) \
   	$(wildcard $(ext_usblib_SRC_PATH)$(DS)Drivers$(DS)USB$(DS)Core$(DS)LPC$(DS)HCD$(DS)EHCI$(DS)*.c) \
   	$(wildcard $(ext_usblib_SRC_PATH)$(DS)Drivers$(DS)USB$(DS)Core$(DS)LPC$(DS)HCD$(DS)OHCI$(DS)*.c)