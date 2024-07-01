/*
 * WDGM.h
 *
 *  Created on: Jun 17, 2024
 *  Author    : Rana Hany, Sarah Ibrahim, Salma Ashraf, Yasmin Tarek
 */

#ifndef WDGM_H
#define WDGM_H
typedef enum {OK = 0, NOK = 1}WDGM_StatusType;
void WDGM_Init(void);
void WDGM_MainFunction(void);
WDGM_StatusType WDGM_PovideSuppervisionStatus(void);
void WDGM_AlivenessIndication(void);
#endif
