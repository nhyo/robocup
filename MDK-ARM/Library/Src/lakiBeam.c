/**
 * @file lakiBeam.c
 * @brief This file provides method to use 30Hz radar LakiBeam1
 * @author TangSong404
 */
#include "lakiBeam.h"

PointData Dataprocess[800];
PointData_Origin Dataprocess_origin[800];
PointData_Send Dataprocess_send[800];
uint16_t data_num = 0;
DEV_FUNC dev_func;

float test_angle = 0;

void lakibeam_init(DEV_FUNC func){
	dev_func = func;
	w5500_init();
}

uint8_t dev_cplt_flag = 0;
void lakibeam_parse(uint8_t* buff){
	uint16_t first_value = buff[2] | (buff[3] << 8);
	if(first_value<4800||first_value>19500){
		if(!dev_cplt_flag){
			dev_func();
			dev_cplt_flag=1;
		}
		data_num = 0;
		return;
	}else dev_cplt_flag = 0;
    for (uint8_t blockIndex = 0; blockIndex < 12; blockIndex++){
        uint16_t flag = buff[1] | (buff[0] << 8);
				uint16_t value = buff[2] | (buff[3] << 8);
				float azimuth = (((float)(int)value) / 100.0f)-48;
				if (flag != 0xFFEE){
					buff += 100;
					continue;
				}
        for (uint8_t i = 0; i < 16; i++) {
						uint16_t distance = buff[4 + i * 6] | (buff[5 + i * 6] << 8);
						float angle = azimuth + 0.25*i;
						if (distance == 0xFFFF||distance == 0x0000||distance>2000)continue;
						if (angle<0||angle>180)continue;
						Dataprocess_origin[data_num].angle = 180 - angle;
						Dataprocess_origin[data_num].distance = distance;
						data_num++;
        }
        buff += 100;
    }
}

void lakibeam_sampling(void){
	w5500_udp_statemachine(0,LAKI_LEN,lakibeam_parse);

}
