/*
 Copyright (c) 2017-2018 Leo McCormack
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <math.h>
#define CONVHULL_3D_ENABLE
//#define CONVHULL_3D_USE_FLOAT_PRECISION /* optional */
//#define CONVHULL_3D_USE_CBLAS /* optional */
#include "convhull_3d.h"
#include "uniform_sph.h"

#ifndef M_PI
#define M_PI 3.14159265359
#endif

#define PATH_LENGTH 256
#if _MSC_VER
const char* output_folder = "../output/convhull_";
const char* obj_folder = "../obj_files/";
#else
const char* output_folder = "output/convhull_";
const char* obj_folder = "obj_files/";
#endif

/* Input .obj files */
/* obtained from: https://people.sc.fsu.edu/~jburkardt/data/obj/obj.html */
/* https://graphics.cmlab.csie.ntu.edu.tw/~robin/courses/cg04/model/index.html */
#define N_OBJECT_FILES 24
const char* obj_test_files[N_OBJECT_FILES] =
{
    "airboat",
    "al",
    "ateneam",
    "cessna",
    "cube",
    "diamond",
    "dodecahedron",
    "gourd",
    "icosahedron",
    "lamp",
    "magnolia",
    "minicooper",
    "power_lines",
    "roi",
    "sandal",
    "shuttle",
    "skyscraper",
    "slot_machine",
    "symphysis",
    "teapot",
    "teddy",
    "trumpet",
    "venusm",
    "violin_case"
};

int main(int argc, const char * argv[])
{
    int o, i, nFAIL, nSUCCEEDED, nFaces, nVert;
    int* out_faces = NULL;
    char path[PATH_LENGTH];
    nFAIL = nSUCCEEDED = 0;
    
    printf("****************************\n");
    printf("* convhull_3d test program *\n");
    printf("****************************\n\n");
    
    /************************************************
     * TEST: random spherical distribution of points
     ***********************************************/
    int n = 936;
    ch_vertex* vertices;
    vertices = (ch_vertex*)malloc(n*sizeof(ch_vertex));
    for (i = 0; i < n; i++) {
        float elev = rand()/(float)RAND_MAX * M_PI * 2.0;
        float azi = rand()/(float)RAND_MAX * M_PI * 2.0;
        vertices[i].z = sin(elev);
        vertices[i].x = cos(azi) * cos(elev) * rand()/(float)RAND_MAX;
        vertices[i].y = sin(azi) * cos(elev) * rand()/(float)RAND_MAX;
    }
    printf("TEST: building convexhull of a random spherical distribution");
    convhull_3d_build(vertices, n, &out_faces, &nFaces); /* build hull */
    if(out_faces==NULL){
        printf("... FAILED!\n");
        nFAIL++;
    }
    else{
        memset(path,0, PATH_LENGTH*sizeof(char));
        path[0] = '\0';
        strncpy(path, output_folder, strlen(output_folder));
        strcat(path, "rand_sph");
        printf("... SUCCEEDED... exporting...\n");
        convhull_3d_export_obj(vertices, n, out_faces, nFaces, 1, path); /* export as .obj file */
        convhull_3d_export_m(vertices, n, out_faces, nFaces, path); /* export as .m file */
        free(out_faces);
        nSUCCEEDED++;
    }
    free(vertices);
    
    /******************************************************
     * TEST: uniform distribution of 180 points on a sphere
     *****************************************************/
    n = 180;
    vertices = (ch_vertex*)malloc(n*sizeof(ch_vertex));
    for (i = 0; i < n; i++) {
        vertices[i].z = sin(__Tdesign_degree_18_dirs_deg[i][1]*M_PI/180.0f);
        vertices[i].x = cos(__Tdesign_degree_18_dirs_deg[i][1]*M_PI/180.0f)*cos(__Tdesign_degree_18_dirs_deg[i][0]*M_PI/180.0f);
        vertices[i].y = cos(__Tdesign_degree_18_dirs_deg[i][1]*M_PI/180.0f)*sin(__Tdesign_degree_18_dirs_deg[i][0]*M_PI/180.0f);
    }
    printf("TEST: building convexhull of a 180 point t-design");
    convhull_3d_build(vertices, n, &out_faces, &nFaces); /* build hull */
    if(out_faces==NULL){
        printf("... FAILED!\n");
        nFAIL++;
    }
    else{
		memset(path, 0, PATH_LENGTH * sizeof(char));
        path[0] = '\0';
        strncpy(path, output_folder, strlen(output_folder));
        strcat(path, "tdesign_180_sph");
        printf("... SUCCEEDED... exporting...\n");
        convhull_3d_export_obj(vertices, n, out_faces, nFaces, 1, path); /* export as .obj file */
        convhull_3d_export_m(vertices, n, out_faces, nFaces, path); /* export as .m file */
        free(out_faces);
        nSUCCEEDED++;
    }
    free(vertices);
    
    /******************************************************
     * TEST: uniform distribution of 840 points on a sphere
     *****************************************************/
    n = 840;
    vertices = (ch_vertex*)malloc(n*sizeof(ch_vertex));
    for (i = 0; i < n; i++) {
        vertices[i].z = sin(__Tdesign_degree_40_dirs_deg[i][1]*M_PI/180.0f);
        vertices[i].x = cos(__Tdesign_degree_40_dirs_deg[i][1]*M_PI/180.0f)*cos(__Tdesign_degree_40_dirs_deg[i][0]*M_PI/180.0f);
        vertices[i].y = cos(__Tdesign_degree_40_dirs_deg[i][1]*M_PI/180.0f)*sin(__Tdesign_degree_40_dirs_deg[i][0]*M_PI/180.0f);
    }
    printf("TEST: building convexhull of a 840 point t-design");
    convhull_3d_build(vertices, n, &out_faces, &nFaces); /* build hull */
    if(out_faces==NULL){
        printf("... FAILED!\n");
        nFAIL++;
    }
    else{
		memset(path, 0, PATH_LENGTH * sizeof(char));
        path[0] = '\0';
        strncpy(path, output_folder, strlen(output_folder));
        strcat(path, "tdesign_840_sph");
        printf("... SUCCEEDED... exporting...\n");
        convhull_3d_export_obj(vertices, n, out_faces, nFaces, 1, path); /* export as .obj file */
        convhull_3d_export_m(vertices, n, out_faces, nFaces, path); /* export as .m file */
        free(out_faces);
        nSUCCEEDED++;
    }
    free(vertices);
    
    /*******************************************************
     * TEST: uniform distribution of 5100 points on a sphere
     ******************************************************/
    n = 5100;
    vertices = (ch_vertex*)malloc(n*sizeof(ch_vertex));
    for (i = 0; i < n; i++) {
        vertices[i].z = sin(__Tdesign_degree_100_dirs_deg[i][1]*M_PI/180.0f);
        vertices[i].x = cos(__Tdesign_degree_100_dirs_deg[i][1]*M_PI/180.0f)*cos(__Tdesign_degree_100_dirs_deg[i][0]*M_PI/180.0f);
        vertices[i].y = cos(__Tdesign_degree_100_dirs_deg[i][1]*M_PI/180.0f)*sin(__Tdesign_degree_100_dirs_deg[i][0]*M_PI/180.0f);
    }
    printf("TEST: building convexhull of a 5100 point t-design");
    convhull_3d_build(vertices, n, &out_faces, &nFaces); /* build hull */
    if(out_faces==NULL){
        printf("... FAILED!\n");
        nFAIL++;
    }
    else{
		memset(path, 0, PATH_LENGTH * sizeof(char));
        path[0] = '\0';
        strncpy(path, output_folder, strlen(output_folder));
        strcat(path, "tdesign_5100_sph");
        printf("... SUCCEEDED... exporting...\n");
        convhull_3d_export_obj(vertices, n, out_faces, nFaces, 1, path); /* export as .obj file */
        convhull_3d_export_m(vertices, n, out_faces, nFaces, path); /* export as .m file */
        free(out_faces);
        nSUCCEEDED++;
    }
    free(vertices);
    
    /******************
     * TEST: obj files
     *****************/
    for(o=0; o<N_OBJECT_FILES; o++){
		memset(path, 0, PATH_LENGTH * sizeof(char));
        path[0] = '\0';
        strcat(path, obj_folder);
        strcat(path, obj_test_files[o]);
        extractVerticesFromObjFile(path, &vertices, &nVert);
        printf("TEST: building convexhull of ");
        printf(path);
        convhull_3d_build(vertices, nVert, &out_faces, &nFaces); /* build hull */
        if(out_faces==NULL){
            printf("... FAILED!\n");
            nFAIL++;
        }
        else{
			memset(path, 0, PATH_LENGTH * sizeof(char));
            path[0] = '\0';
            strncpy(path, output_folder, strlen(output_folder));
            strcat(path, (char*)obj_test_files[o]);
            printf("... SUCCEEDED... exporting...\n");
            convhull_3d_export_obj(vertices, nVert, out_faces, nFaces, 1, path); /* export as .obj file */
            convhull_3d_export_m(vertices, nVert, out_faces, nFaces, path); /* export as .m file */
            free(vertices);
            free(out_faces);
            nSUCCEEDED++;
        }
    }
    
    /* results */
    char tmp_str[16];
    printf("\nSucess rate: ");
    sprintf(tmp_str, "%d", nSUCCEEDED);
    printf(tmp_str);
    printf("/");
    sprintf(tmp_str, "%d", nSUCCEEDED+nFAIL);
    printf(tmp_str);
    printf("\n");
    
    return 0;
}



