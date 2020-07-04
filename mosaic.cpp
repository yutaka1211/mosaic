#include "vec3.h"
#include "mesh.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <math.h>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

#define THICKNESS 1 //持ち手部分の長さ
#define AMP 10 //スタンプの凹凸の長さ

#define N (1)	//モザイクの大きさ
#define M (2)	//モザイクの大きさ
#define L (3)
#define O (4)

int main() {
	unsigned char *image;
	int width, height;
	int n;
	image = stbi_load("images/NO_138×190.png", &width, &height, &n, 1);

	printf("%d, %d \n", width, height);


	/*メッシュ1*/
	Mesh mesh_cube1, mesh_cube_mv1;
	Mesh mesh_stamp1;
	
	mesh_cube1 = create_cube();
	int work;	//計算結果
	int i, j;
	for(int y=0, j=0;y<height;y+=N, j++){
		for(int x=0, i=0;x<width;x+=N, i++){
			work=0;
			for(int z=0;z<N;z++){
				for(int k=0;k<N;k++){
					work+=image[(y*width)+(z*width)+x+k];
				}
			}
			mesh_cube_mv1 = mesh_cube1;
			mesh_cube_mv1.translate(Vec3(i, j, 0));
			mesh_cube_mv1.scale(Vec3(1, 1, (256-work/(int)pow(N,2))/10));
			mesh_stamp1 += mesh_cube_mv1;
		}
	}

	
	/*メッシュ2*/
	Mesh mesh_cube2, mesh_cube_mv2;
	Mesh mesh_stamp2;	

	mesh_cube2 = create_cube();
	for(int y=0, j=0;y<height;y+=M, j++){
		for(int x=0, i=0;x<width;x+=M, i++){
			work=0;
			for(int z=0;z<M;z++){
				for(int k=0;k<M;k++){
					work+=image[(y*width)+(z*width)+x+k];
				}
			}
			mesh_cube_mv2 = mesh_cube2;
			mesh_cube_mv2.translate(Vec3(i, j, 0));
			mesh_cube_mv2.scale(Vec3(1, 1, (256-work/(int)pow(M,2))/10));
			mesh_stamp2 += mesh_cube_mv2;
		}
	}
	mesh_stamp2.translate(Vec3(-0.5*(width-1), 0.25, 0));
	mesh_stamp2.scale(Vec3(M, M, 1));

	
	/*メッシュ3*/
	Mesh mesh_cube3, mesh_cube_mv3;
	Mesh mesh_stamp3;	

	mesh_cube3 = create_cube();
	for(int y=0, j=0;y<height;y+=L, j++){
		for(int x=0, i=0;x<width;x+=L, i++){
			work=0;
			for(int z=0;z<L;z++){
				for(int k=0;k<L;k++){
					work+=image[(y*width)+(z*width)+x+k];
				}
			}
			mesh_cube_mv3 = mesh_cube3;
			mesh_cube_mv3.translate(Vec3(i, j, 0));
			mesh_cube_mv3.scale(Vec3(1, 1, (256-work/(int)pow(L,2))/10));
			mesh_stamp3 += mesh_cube_mv3;
		}
	}
	mesh_stamp3.translate(Vec3(0.25, 0.3333*(height-1), 0));
	mesh_stamp3.scale(Vec3(L, L, 1));


	/*メッシュ4*/
	Mesh mesh_cube4, mesh_cube_mv4;
	Mesh mesh_stamp4;	

	mesh_cube4 = create_cube();
	for(int y=0, j=0;y<height;y+=O, j++){
		for(int x=0, i=0;x<width;x+=O, i++){
			work=0;
			for(int z=0;z<O;z++){
				for(int k=0;k<O;k++){
					work+=image[(y*width)+(z*width)+x+k];
				}
			}
			mesh_cube_mv4 = mesh_cube2;
			mesh_cube_mv4.translate(Vec3(i, j, 0));
			mesh_cube_mv4.scale(Vec3(1, 1, (256-work/(int)pow(O,2))/10));
			mesh_stamp4 += mesh_cube_mv4;
		}
	}
	mesh_stamp4.translate(Vec3(-0.25*(width-1)+0.25, 0.25*(height-1), 0));
	mesh_stamp4.scale(Vec3(O, O, 1));


	Mesh mesh_stamp = mesh_stamp1 + mesh_stamp2 + mesh_stamp3 + mesh_stamp4;


	/*名前代入*/
	Mesh mesh_char, mesh_char_mv;
	Mesh mesh_char_stamp;

	/*UTF-16*/
	mesh_char = create_cube();
	for(int i=0;i<16;i++){
		int x;
		mesh_char_mv = mesh_char;
		mesh_char_mv.translate(Vec3(8-i, 22, 0));
		printf("input[%d]:", i);
		scanf("%d", &x);
		mesh_char_mv.scale(Vec3(17.25, 17.25, x+1));
		mesh_char_mv.translate(Vec3(-9.5, 8.625, 0));
		mesh_char_stamp += mesh_char_mv;
	}	
	mesh_stamp += mesh_char_stamp;

	/*S-JIS*/
	mesh_char = create_cube();
	for(int i=0;i<16;i++){
		int x;
		mesh_char_mv = mesh_char;
		mesh_char_mv.translate(Vec3(8-i, 23, 0));
		printf("input[%d]:", i);
		scanf("%d", &x);
		mesh_char_mv.scale(Vec3(17.25, 17.25, x+1));
		mesh_char_mv.translate(Vec3(-9.5, 8.625, 0));
		mesh_char_stamp += mesh_char_mv;
	}	
	mesh_stamp += mesh_char_stamp;

	
	/*EUC*/
	mesh_char = create_cube();
	for(int i=0;i<16;i++){
		int x;
		mesh_char_mv = mesh_char;
		mesh_char_mv.translate(Vec3(8-i, 24, 0));
		printf("input[%d]:", i);
		scanf("%d", &x);
		mesh_char_mv.scale(Vec3(17.25, 17.25, x+1));
		mesh_char_mv.translate(Vec3(-9.5, 8.625, 0));
		mesh_char_stamp += mesh_char_mv;
	}	
	mesh_stamp += mesh_char_stamp;

	mesh_stamp.stl_write("NO_mosaic_syc.stl");
}
// a:10 b:11 c:12 d:13 e:14 f:15