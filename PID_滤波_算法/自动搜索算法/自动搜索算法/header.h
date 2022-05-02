#ifndef __HEADER_H
#define __HEADER_H
typedef unsigned int uint32;
typedef int int32;
extern unsigned int g_device_id[250];


void search_init(void);

int read_device(unsigned int device_id_in,unsigned int *pdevice_id_out);
#endif