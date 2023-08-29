/*
 * dbg.h
 *
 *  Created on: Aug 25, 2023
 *      Author: nhat.tranminh
 */

#ifndef DEBUGPACKAGE_DBG_H_
#define DEBUGPACKAGE_DBG_H_

/* generic headers */
#include <SEGGER_RTT.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* Debug levels */
#define DB_LEVEL_INFO       0
#define DB_LEVEL_WARN       1
#define DB_LEVEL_CRITICAL   2


#define RESET_VALUE             (0x00)

#define SEGGER_INDEX            (0)
#define LVL_ERR      (1u)       /* error conditions   */


#define DB_PRINTF(fn_, ...)      SEGGER_RTT_printf (SEGGER_INDEX,(fn_), ##__VA_ARGS__);

#define DB_ERR_PRINTF(fn_, ...)  if(LVL_ERR)\
        SEGGER_RTT_printf (SEGGER_INDEX, "[ERR] In Function: %s(), %s",__FUNCTION__,(fn_),##__VA_ARGS__);

#define DB_ERR_TRAP(err)        if(err) {\
        SEGGER_RTT_printf(SEGGER_INDEX, "\r\nReturned Error Code: 0x%x  \r\n", err);\
        __asm("BKPT #0\n");} /* trap upon the error  */

#define DB_READ(read_data)     SEGGER_RTT_Read (SEGGER_INDEX, read_data, sizeof(read_data));

#define DB_CHECK_DATA          SEGGER_RTT_HasKey()


#endif /* DEBUGPACKAGE_DBG_H_ */
