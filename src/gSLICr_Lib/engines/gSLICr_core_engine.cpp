// Copyright 2014-2015 Isis Innovation Limited and the authors of gSLICr

#pragma once
#include "gSLICr_core_engine.h"
#include "gSLICr_seg_engine_GPU.h"
#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
//ROOT LIb




#include <fstream>

using namespace gSLICr;
using namespace std;

gSLICr::engines::core_engine::core_engine(const objects::settings& in_settings)
{
	slic_seg_engine = new seg_engine_GPU(in_settings);
}

gSLICr::engines::core_engine::~core_engine()
{
		delete slic_seg_engine;
}

void gSLICr::engines::core_engine::Process_Frame(UChar4Image* in_img)
{
	slic_seg_engine->Perform_Segmentation(in_img);
}

const IntImage * gSLICr::engines::core_engine::Get_Seg_Res()
{
	return slic_seg_engine->Get_Seg_Mask();
}

void gSLICr::engines::core_engine::Draw_Segmentation_Result(UChar4Image* out_img)
{
	slic_seg_engine->Draw_Segmentation_Result(out_img);
}



void gSLICr::engines::core_engine::Write_Seg_Res_To_PGM(const char* fileName)
{
	const IntImage* idx_img = slic_seg_engine->Get_Seg_Mask();
	int width = idx_img->noDims.x;
	//X es la  cantidad de columnas
	//std::cout<< "X: "<< width <<std::endl;
	//Y es la cantidad de filas
	int height = idx_img->noDims.y;
	//std::cout<< " Y: " << height <<std::endl;
	const int* data_ptr = idx_img->GetData(MEMORYDEVICE_CPU);

	//std::cout<< "data: "<< data_ptr[100]  <<std::endl;

	ofstream f(fileName, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
	f << "P5\n" << width << " " << height << "\n65535\n";
	for (int i = 0; i < height * width; ++i)
	{
		ushort lable = (ushort)data_ptr[i];
		//std::cout<< lable;
		ushort lable_buffer = (lable << 8 | lable >> 8);
		//std::cout<< lable << std::endl;
		f.write((const char*)&lable_buffer, sizeof(ushort));

	}


	f.close();
}

