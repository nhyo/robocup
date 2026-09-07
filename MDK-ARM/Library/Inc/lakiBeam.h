#ifndef LAKIBEAM_H
#define LAKIBEAM_H
#include "w5500.h"
#include "math.h"

typedef struct PointData{
	uint16_t distance;
	float angle;
	float X;
	float Y;
}PointData;

typedef struct PointData_XY{
	float X;
	float Y;
}PointData_XY;

typedef struct PointData_Origin{
	uint16_t distance;
	float angle;
}PointData_Origin;

typedef struct PointData_Send{
	uint8_t X;
	uint8_t Y;
}PointData_Send;

typedef void (*DEV_FUNC)(void);

void lakibeam_init(DEV_FUNC func);
void lakibeam_sampling(void);

extern PointData_Send Dataprocess_send[800];
extern PointData_Origin Dataprocess_origin[800];
extern PointData Dataprocess[800];
extern uint16_t data_num;

#define LAKI_LEN 1206

#endif
